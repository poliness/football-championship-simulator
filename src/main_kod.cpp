
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Druzyna.h"
#include "GrupaMeczowa.h"
#include "Kontynent.h"


//faza rozgrywek
static int FAZA = 0;
// 0 - grupowa
// 1 - przedcwiercfinalowa (16 druzyn)
// 2 - cwiercfinal (8 druzyn)
// 3 - polfinal (4 druzyny)
// 4 - final (2 druzyny)



bool compDruzyny(const Druzyna &d1, const Druzyna &d2){
    return d1.miejsce_w_rankingu < d2.miejsce_w_rankingu;
}
bool compDouble(const double &d1, const double &d2){
    return d1 < d2;
}
bool compIloscPunktow(const Druzyna &d1, const Druzyna &d2){
    return d1.ilosc_pkt_w_fazie_grupowej > d2.ilosc_pkt_w_fazie_grupowej;
}

//funkcja wybiera najlepszą drużynę ze wszystkich kontynentów
Druzyna wybierzNajlepszaZeWszystkichKontynentow(vector<Kontynent>& k){
    int max = INT_MAX, index;
    for (int i = 0; i < 6; i++){
        if (k[i].druzyny_na_kontynencie.size() > 0 && (k[i].druzyny_na_kontynencie.front().miejsce_w_rankingu < max)){
            index = i;
            max = k[i].druzyny_na_kontynencie.front().miejsce_w_rankingu;
        }
    }

    Druzyna d = k[index].druzyny_na_kontynencie.front();
    k[index].druzyny_na_kontynencie.pop_front();
    return d;
}

void symulujMecz(ostream &out, Druzyna &pierwsza, Druzyna &druga){

    //losujemy liczbę od 0.00 do 1.00
    double losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
    double losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);

    //ustawiamy ilość goli obu drużyn na 0
    int ile_goli_pierwsza = 0;
    int ile_goli_druga = 0;
    int ile_goli_karne_pierwsza = 0;
    int ile_goli_karne_druga = 0;


    // LOSOWANIE CZERWONYCH KARTEK:

    // zmienna do losowania liczby od 0 do 1, np 0.42
    double losowanko;

    // szansa na jedną czerwoną kartkę. Jak już ktoś ją zdobędzie,
    // dzielimy szansę na 2, czyli szansa na drugą będzie już wynosiła 2.5%
    double szansa_pierwsza = 0.05;
    double szansa_druga = 0.05;

    // zaznaczamy sobie boola, czy któraś drużyna dostała kartkę
    // jeśli tak, dodajemy jej 'osłabienie' na dwa mecze (łącznie z aktualnym)
    bool lewa_dostala = false, prawa_dostala = false;


    // lecimy po wszystkich zawodnikach z obu drużyn
    for (int i = 0; i < 11; i++) {

        // PIERWSZA DRUZYNA
        // losujemy sobie tę liczbę od 0.00 do 1.00
        losowanko = (double)rand() / ((double)RAND_MAX);

        // jeśli liczba jest mniejsza od 'szansy' czyli na początku 0.05 - mamy czerwoną kartkę
        if (losowanko < szansa_pierwsza) {
            // więc zmniejszamy szanse na gole o 10%
            for (int k = 0; k < 5; k++) {
                pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] -= 0.1;
                if (pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] < 0)
                    pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] = 0;
            }
            lewa_dostala = true;
            szansa_pierwsza /= 2;
        }

        // DRUGA DRUŻYNA
        losowanko = (double)rand() / ((double)RAND_MAX);
        if (losowanko < szansa_druga) { // ktoś tu dostał karteczkę, heheszkę
            for (int k = 0; k < 5; k++) {
                druga.druzynowe_szanse_na_gole_w_oslabieniu[k] -= 0.1;
                if (druga.druzynowe_szanse_na_gole_w_oslabieniu[k] < 0)
                    druga.druzynowe_szanse_na_gole_w_oslabieniu[k] = 0;
            }
            prawa_dostala = true;
            szansa_druga /= 2;
        }
    }

    // jeśli któraś drużyna dostała jakąkolwiek kartkę (nawet 11 kartek), na kolejne 2 mecze (łącznie z tym) pozostaje osłabiona
    if (lewa_dostala) pierwsza.ile_meczy_w_oslabieniu += 2;
    if (prawa_dostala) druga.ile_meczy_w_oslabieniu += 2;


    vector<double> druzynowe_szanse_pierwsza = vector<double>(5, 0);
    vector<double> druzynowe_szanse_druga = vector<double>(5, 0);


    // dalej będziemy grać mecz, więc trzeba wybrać, czy drużyna jest osłabiona i używamy 'osłabionych' statystyk,
    // czy jest 'nieosłabiona' i używamy 'nieosłabionych'
    if (pierwsza.ile_meczy_w_oslabieniu > 0)
        druzynowe_szanse_pierwsza = pierwsza.druzynowe_szanse_na_gole_w_oslabieniu;
    else druzynowe_szanse_pierwsza = pierwsza.druzynowe_szanse_na_gole;

    if (druga.ile_meczy_w_oslabieniu > 0)
        druzynowe_szanse_pierwsza = druga.druzynowe_szanse_na_gole_w_oslabieniu;
    else druzynowe_szanse_pierwsza = druga.druzynowe_szanse_na_gole;




    for (int i = 0; i < 5; i++){
        if (losowanie_goli_pierwszej < druzynowe_szanse_pierwsza[i])
            ile_goli_pierwsza++;
        if (losowanie_goli_drugiej < druzynowe_szanse_druga[i])
            ile_goli_druga++;
    }

    //wartości, które zmieniamy w danej drużynie
    bool wygrywa_pierwsza = false;
    bool wygrywa_druga = false;
    bool remis = false;
    bool karne = false;

    //sprawdzamy remisy, wygrane i karne
    if (ile_goli_pierwsza == ile_goli_druga)
        remis = true;
    else if (ile_goli_pierwsza > ile_goli_druga)
        wygrywa_pierwsza = true;
    else if (ile_goli_druga > ile_goli_pierwsza)
        wygrywa_druga = true;

    //karne i dogrywka - kiedy mamy remis i faza jest większa niż grupowa



    if (remis && FAZA > 0){
        //dogrywka
        losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
        losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);
        for (int i = 0; i < 5; i++){
            if (losowanie_goli_pierwszej < druzynowe_szanse_pierwsza[i])
                ile_goli_pierwsza++;
            if (losowanie_goli_drugiej < druzynowe_szanse_druga[i])
                ile_goli_druga++;
        }

        //karne
        if (ile_goli_pierwsza == ile_goli_druga){
            karne = true;

            //5 rzutów karnych dla pierwszej drużyny
            for (int i = 0; i < 5; i++){
                double losowa_liczba = ((double)rand() / (double)RAND_MAX);

                if (losowa_liczba < pierwsza.szansa_na_gola_graczy)
                    ile_goli_karne_pierwsza++;
            }


            //5 rzutów karnych dla drugiej drużyny
            for (int i = 0; i < 5; i++){
                double losowa_liczba = ((double)rand() / (double)RAND_MAX);

                if (losowa_liczba < druga.szansa_na_gola_graczy)
                    ile_goli_karne_druga++;
            }

            //kiedy w karnych jest remis
            //dopóki ilość goli jest taka sama
            while (ile_goli_karne_pierwsza == ile_goli_karne_druga){
                //losujemy liczbę od 0 do 1
                double losowa_liczba = ((double)rand() / (double)RAND_MAX);
                //jeżeli liczba jest mniejsza od 0.5 - pierwsza drużyna strzela gola
                if (losowa_liczba < 0.5)
                    ile_goli_karne_pierwsza++;
                //dla drugiej drużyny
                losowa_liczba = ((double)rand() / (double)RAND_MAX);
                if (losowa_liczba < 0.5)
                    ile_goli_karne_druga++;
            }
        }
        if ((ile_goli_pierwsza > ile_goli_druga) && (ile_goli_karne_pierwsza > ile_goli_karne_druga))
            wygrywa_pierwsza = true;
        else
            wygrywa_druga = true;

    }


    //FAZA jest zwiększana na różnych etapach programu
    switch (FAZA){

    case 0:
        {
                  //FAZA 0 - faza grupowa. Drużyny zbierają punkty za wygrane i remisy, nie dostają za przegrane
                  if (remis){
                      //jeśli mamy remis, dodajemy każdej drużynie po 1 punkcie
                      pierwsza.ilosc_pkt_w_fazie_grupowej += 1;
                      druga.ilosc_pkt_w_fazie_grupowej += 1;
                      //zwiększamy obu drużynom ilość remisów
                      pierwsza.remisy++;
                      druga.remisy++;
                  }
                  else if (wygrywa_pierwsza){
                      //pierwsza drużyna wygrywa
                      pierwsza.zwyciestwa++;
                      //dostaje 3 pkt w fazie grupowej
                      pierwsza.ilosc_pkt_w_fazie_grupowej += 3;
                      //drugiej drużynie zwiększamy porażki i nie dodajemy punktów
                      druga.porazki++;
                  }
                  else if (wygrywa_druga){
                      druga.zwyciestwa++;
                      druga.ilosc_pkt_w_fazie_grupowej += 3;
                      pierwsza.porazki++;
                  }
                  //zwiększamy ilość wszystkich strzelonych bramek o tę ilość, którą strzeliła w danym meczu
                  pierwsza.bramki_strzelone += ile_goli_pierwsza;
                  //to samo ze straconymi
                  pierwsza.bramki_stracone += ile_goli_druga;
                  druga.bramki_strzelone += ile_goli_druga;
                  druga.bramki_stracone += ile_goli_pierwsza;
                  //wypisanie np. "Brazylia 4 - 3 Kamerun"
                //  cout << pierwsza.nazwa << " " << ile_goli_pierwsza << " - " << ile_goli_druga << " " << druga.nazwa << endl;
                  break;
        }
    case 1:
        {
                  // FAZA 1 - przedćwierćfinałowa
                  if (wygrywa_pierwsza)
                      pierwsza.wygrala_przedcwiercfinal = true;
                  else if (wygrywa_druga)
                      druga.wygrala_przedcwiercfinal = true;
                  break;
        }
    case 2:
        {
                  //FAZA 2 - ćwierćfinał
                  if (wygrywa_pierwsza)
                      pierwsza.wygrala_cwiercfinal = true;
                  else if (wygrywa_druga)
                      druga.wygrala_cwiercfinal = true;
                  break;
        }
    case 3:
        {
                  //FAZA 3 - półfinał
                  if (wygrywa_pierwsza)
                      pierwsza.wygrala_polfinal = true;
                  else if (wygrywa_druga)
                      druga.wygrala_polfinal = true;
                  break;
        }
    case 4:
        {
                  if (wygrywa_pierwsza)
                      pierwsza.wygrala_final = true;
                  else if (wygrywa_druga)
                      druga.wygrala_final = true;
                  break;
        }
    }

    if (FAZA > 0){
        string wynik = to_string(ile_goli_pierwsza) + " : " + to_string(ile_goli_druga);

        if (remis){
            if (karne)
                cout << setfill(' ') << setw(1) << "|" << setw(10) << left << pierwsza.nazwa << "|" << setw(15) << left << wynik << setw(1) << "|" << setw(10) << left << druga.nazwa << setw(1) << "|" << setw(12) << left << "TAK" << "|" << setw(8) << left << ile_goli_karne_pierwsza << " : " << ile_goli_karne_druga << "|" << endl;
            else
                cout << setfill(' ') << setw(1) << "|" << setw(10) << left << pierwsza.nazwa << "|" << setw(15) << left << wynik << setw(1) << "|" << setw(10) << left << druga.nazwa << setw(1) << "|" << setw(12) << left << "TAK" << "|" << setw(12) << left << "-" << "|" << endl;
        }

        else
            cout << setfill(' ') << setw(1) << "|" << setw(10) << left << pierwsza.nazwa << "|" << setw(15) << left << wynik << setw(1) << "|" << setw(10) << left << druga.nazwa << setw(1) << "|" << setw(12) << left << "NIE" << "|" << setw(12) << left << "-" << "|" << endl;

        cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;
    }




    // mecz się skończył, więc jeśli drużyna była na nim osłabiona, odejmujemy jej 'osłabienie' na jeden mecz
    if (pierwsza.ile_meczy_w_oslabieniu > 0) pierwsza.ile_meczy_w_oslabieniu--;
    if (druga.ile_meczy_w_oslabieniu > 0) druga.ile_meczy_w_oslabieniu--;

    // jeśli drużyna nie jest już osłabiona, musimy cofnąć jej zmiany w 'szansach osłabionych'
    if (pierwsza.ile_meczy_w_oslabieniu == 0)
        pierwsza.druzynowe_szanse_na_gole_w_oslabieniu = pierwsza.druzynowe_szanse_na_gole;

    if (druga.ile_meczy_w_oslabieniu == 0)
        druga.druzynowe_szanse_na_gole_w_oslabieniu = druga.druzynowe_szanse_na_gole;

}

void wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe, ostream &out){
    string grupy = { "ABCDEFGH" };

    for (int i = 0; i < 8; i++){
        string grupa = "GRUPA ";
        grupa.push_back(grupy[i]);

        //4 stringi, które będą nam odpowiadać za nazwy i łączymy je z numerkami 1,2,3,4
        string d1 = "1: " + grupyMeczowe[i].druzyny_w_grupie[0].nazwa;
        string d2 = "2: " + grupyMeczowe[i].druzyny_w_grupie[1].nazwa;
        string d3 = "3: " + grupyMeczowe[i].druzyny_w_grupie[2].nazwa;
        string d4 = "4: " + grupyMeczowe[i].druzyny_w_grupie[3].nazwa;


        string bramki1 = to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_stracone);
        string bramki2 = to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_stracone);
        string bramki3 = to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_stracone);
        string bramki4 = to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_stracone);

        //wypisujemy aktualną grupę nad tabelą
        cout << grupa << endl;

        //kreska
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;
        //wiersz z nazwami kolumn
        cout << setfill(' ') << setw(1) << "|" << setw(15) << left << "Miejsce w grupie" << "|" << setw(12) << left << "Zwyciestwa" << setw(1) << "|" << setw(9) << left << "Remisy" << setw(1) << "|" << setw(9) << left << "Porazki" << "|" << setw(9) << left << "Bramki" << "|" << setw(9) << left << "Pkt." << "|" << setw(9) << left << "Cwierc." << "|" << endl;
        //kreska oddzielająca
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;
        //statystyka pierwszej drużyny
        cout << setfill(' ') << setw(1) << "|" << setw(16) << left << d1 << "|" << setw(12) << left << grupyMeczowe[i].druzyny_w_grupie[0].zwyciestwa << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[0].remisy << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[0].porazki << "|" << setw(9) << left << bramki1 << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[0].ilosc_pkt_w_fazie_grupowej << "|" << setw(9) << left << "TAK" << "|" << endl;
        //kreska oddzielająca
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;

        //kolejne trzy drużyny
        cout << setfill(' ') << setw(1) << "|" << setw(16) << left << d2 << "|" << setw(12) << left << grupyMeczowe[i].druzyny_w_grupie[1].zwyciestwa << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[1].remisy << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[1].porazki << "|" << setw(9) << left << bramki2 << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[1].ilosc_pkt_w_fazie_grupowej << "|" << setw(9) << left << "TAK" << "|" << endl;
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;

        cout << setfill(' ') << setw(1) << "|" << setw(16) << left << d3 << "|" << setw(12) << left << grupyMeczowe[i].druzyny_w_grupie[2].zwyciestwa << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[2].remisy << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[2].porazki << "|" << setw(9) << left << bramki3 << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[2].ilosc_pkt_w_fazie_grupowej << "|" << setw(9) << left << "NIE" << "|" << endl;
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;

        cout << setfill(' ') << setw(1) << "|" << setw(16) << left << d4 << "|" << setw(12) << left << grupyMeczowe[i].druzyny_w_grupie[3].zwyciestwa << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[3].remisy << setw(1) << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[3].porazki << "|" << setw(9) << left << bramki4 << "|" << setw(9) << left << grupyMeczowe[i].druzyny_w_grupie[3].ilosc_pkt_w_fazie_grupowej << "|" << setw(9) << left << "NIE" << "|" << endl;
        cout << setfill('-') << setw(1) << "+" << setw(16) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;
        cout << endl << endl;
    }
}

int rozpocznijSymulacje(){

    //lista, do ktorej wczytamy druzyny z pliku
    list<Druzyna> druzyny_z_pliku;

    //strumienie
    fstream in;

    //do stringa będziemy wczytywać jedną linię z pliku, nazwę, kontynent, miejsce w ranku i szanse na strzelenie gola
    string read;

    srand(time(NULL));

    //vector, który będzie zawierać nasze 6 kontynentów
    vector<Kontynent>kontynenty;

    //vector zawierający 8 grup meczowych do fazy grupowej
    vector<GrupaMeczowa>grupyMeczowe;

    //rozpychamy vectory
    for (int i = 0; i < 8; i++)
        grupyMeczowe.push_back(GrupaMeczowa());

    for (int i = 0; i < 6; i++)
        kontynenty.push_back(Kontynent());

    //otwarcie plik
    in.open("in.txt");

    //w pliku są 32 drużyny, sprawdzamy kiedy wielkość naszej listy przekroczy 31
    while (druzyny_z_pliku.size() < 32){
        getline(in, read);

        stringstream stream(read);
        vector<string>dane_kraju;
        vector<double>druzynowe_szanse_na_gola;
        double szansa_na_gola_graczy;

        //mamy 8 rzeczy w 1 linicje
        for (int i = 0; i < 18; i++){
            //nazwa kraju, kontynent, nr w rankingu
            if (i < 3){
                string temp;
                stream >> temp;
                dane_kraju.push_back(temp);
            }
            //szanse na gola
            else if (i >= 3 && i < 8){
                double temp;
                stream >> temp;
                druzynowe_szanse_na_gola.push_back(temp);
            }
            else
                stream >> szansa_na_gola_graczy;
        }

        //sortujemy szanse na gola
        sort(druzynowe_szanse_na_gola.begin(), druzynowe_szanse_na_gola.begin() + 5);
        //odwracamy, od najwiekszej do najmniejszej
        reverse(druzynowe_szanse_na_gola.begin(), druzynowe_szanse_na_gola.end());

        druzyny_z_pliku.push_back(Druzyna(dane_kraju[0], stoi(dane_kraju[1]), stoi(dane_kraju[2]), druzynowe_szanse_na_gola, szansa_na_gola_graczy));
    }

    //wrzucamy drużyny do odpowiednich kontynentów
    //pętla przechodzi przez całą listę 32 drużyn
    //iteratorem jest 'drużyna'
    for (list<Druzyna>::iterator it = druzyny_z_pliku.begin(); it != druzyny_z_pliku.end(); it++){
        //drużynę z listy dodajemy do wektora 'kontynenty'
        //każda z drużyn zawiera już w sobie nazwę kontynentu
        //dodajemy do kontynenty[druzyna.kontynent - 1], ponieważ kontynenty liczone są od 1, a wektory i tablice mają numerację od 0
        //każdy kontynent zawiera listę drużyn na tym kontynencie (druzyny_na_kontynencie) i to do niej dodajemy drużynę, na której aktualnie się znajdujemy
        kontynenty[it->kontynent - 1].druzyny_na_kontynencie.push_back(*it);
    }

    //sortujemy wszystkie drużyny na każdym kontynencie
    for (int i = 0; i < 6; i++){
        kontynenty[i].druzyny_na_kontynencie.sort(compDruzyny);
    }

    //LOSOWANIE DRUZYN DO GRUP
    //8 tabel po 4 miejsca
    //zewnętrzna pętla wypełnia 4 wiersze
    //wewnątrz tej pętli jest pętla iterowana do 6:
    //wybieramy po najlepszej druzynie z kontynentu, 2 pozostałe dobieramy z puli wszystkich kontynentów

    //zmienne pomocnicze
    //k_i będzie zwiększane cały czas (ale nigdy nie przekroczy 5)
    int k_i = 0;
    //zmienna do losowania grupy, losujemy ją do czasu, aż nie spotkamy grupy z 'wolnym miejscem'
    int wylosowana_grupa;
    //4 fazy wyboru = 4 wiersze w tabeli, z każdą iteracją pętli najbardziej zewnętrznej, zwiększamy tę zmienną
    //wstawiająć drużynę do odpowiedniej grupy wstawiamy ją na miejsce 'faza', pierwsze drużyny na miejsce 0,
    //drugie na miejsce 1, trzecie na miejsce 2 i czwarte na miesjce 3
    int faza_wyboru = 0;
    //zewnętrzna pętla, iterowana do 4
    for (int k = 0; k < 4; k++){
        //pierwsze 6 drużyn wybieramy z każdego kontynetu (jest ich 6)
        //uprzednio zostały one posortowane wg 'miejsca w rankingu' dlatego ściągamy je z początku listy
        for (int i = 0; i < 6; i++){
            //przypadek: w Australii mamy tylko 1 drużynę
            //przechodzimy po kontynentach pętlą while i szukamy NIEPUSTEGO kontynentu;
            //po pierwszej iteracji Autralia będzie pusta, program przestałby działać
            //k_i % 6 działa w taki sposób:
            //zaczyna się od 0, potem po kolei 1,2,3,4,5,6,7,8,9 itd, stąd modulo:
            //dla 0%6 wynik 0
            //dla 1%6 wynik 1
            //dla 5%6 wynik 5
            //dla 6%6 wynik 0 i w ten sposób zataczamy koło, zmienna nie wyjdzie poza zakres (poza 5);
            while (kontynenty[k_i % 6].druzyny_na_kontynencie.size() == 0){
                k_i++;
            }
            //tworzymy tymczasowy obiekt klasy Druzyna i przypisujemy do niej drużynę z kontynetu z początku listy (front())
            Druzyna najlepsza = kontynenty[k_i % 6].druzyny_na_kontynencie.front();
            //usuwamy powyższą drużynę z pierwotnej listy
            kontynenty[k_i % 6].druzyny_na_kontynencie.pop_front();

            //LOSOWANIE GRUPY DLA DRUŻYNY
            //losuję liczbę od 0 do 7 aż do momentu, kiedy dana grupa z tym indeksem będzie mieć miejsce
            //kiedy znajdę taką grupę, zwiększam jej zmienną 'zapełnienie', bo w tej fazie dostała już drużynę
            //przykład:
            //grupy 1, 3 i 5 mają już po 1 drużynie
            //wylosowaliśmy 3
            //sprawdzamy czy grupyMeczowe[3].zapelnienie_grupy > faza_wyboru
            //zapelnienie tej grupy jest większe, bo zostało wcześniej zwiększone
            //losujemy ponownie

            do{
                wylosowana_grupa = rand() % 8;
            } while (grupyMeczowe[wylosowana_grupa].zapelnienie_grupy > faza_wyboru);

            //dodaję drużynę do wylosowanej grupy
            grupyMeczowe[wylosowana_grupa].druzyny_w_grupie.push_back(najlepsza);

            //zwiększam zapełnienie tej grupy, w każdej fazie tylko jedna
            grupyMeczowe[wylosowana_grupa].zapelnienie_grupy++;
            k_i++;
        }

        //grupy 7 i 8 zostały bez drużyn, pętla działa od 6 do 8
        for (int i = 6; i < 8; i++){
            //losujemy liczbę od 0 do 7
            do{
                wylosowana_grupa = rand() % 8;
            } while (grupyMeczowe[wylosowana_grupa].zapelnienie_grupy > faza_wyboru);

            //do wylosowanej grupy wrzucam drużynę, ZWRÓCONĄ przez metodę 'wybierzNajlepszaZeWszystkichKontynentow();
            grupyMeczowe[wylosowana_grupa].druzyny_w_grupie.push_back(wybierzNajlepszaZeWszystkichKontynentow(kontynenty));

            //zwiększam zapłenienie grupy, do której dodano drużynę
            grupyMeczowe[wylosowana_grupa].zapelnienie_grupy++;
        }

        //pierwsze wiersze w tabelkach zostały wypełnione, zwiększamy faza_wyboru
        faza_wyboru++;
    }

    //SYMULACJA FAZY GRUPOWEJ, symulacja meczów
    //ze string wczytuję nazwy grup
    //string literki_grup = { "ABCDEFGH" };

    //tworzę nazwy np 'GRUPA A', 'GRUPA B'
    //string nazwa_grupy = "GRUPA X";

    //wypisuję na ekran
    //cout << "##########    FAZA GRUPOWA    ##########" << endl << endl << endl;

    //iteruję po wszystkich grupach (8 razy)
    for (int i = 0; i < 8; i++){
        //usuwam znak ze stringa (usuwa X)
        //nazwa_grupy.pop_back();
        //dopisuję na koniec np A
        //nazwa_grupy.push_back(literki_grup[i]);

        //cout << "#################################" << endl;
        //cout << "############ " << nazwa_grupy << " ############" << endl;
        //cout << "#################################" << endl;

        //w fazie grupowej w grupie rozgrywam 6 meczów, każdy z każdym
        //symulacja meczu za pomocą metody 'symulujMecz', gdzie jako argumenty przekazujemy strumień wyjściowy i dwie drużyny
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[1]);
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[2]);
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[3]);
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[2]);
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[3]);
        symulujMecz(cout, grupyMeczowe[i].druzyny_w_grupie[2], grupyMeczowe[i].druzyny_w_grupie[3]);
    }
    cout << endl;

    //KONIEC FAZY GRUPOWEJ, metoda 'symulujMecz' będzie działać inaczej, przechodzimy do FAZY PRZEDCWIERCFINALOWEJ
    FAZA++;

    //sortuję wszystkie grupy meczowe wg ilości zdobytych punktów (od największej do najmniejszej)
    for (int i = 0; i < 8; i++){
        sort(grupyMeczowe[i].druzyny_w_grupie.begin(), grupyMeczowe[i].druzyny_w_grupie.end(), compIloscPunktow);
    }

    //metoda wypisuje tabelki grup wraz ze statystykami
    wypiszFazeGrupowa(grupyMeczowe, cout);


    //tworzę tablice par i jedną parę (finałową)
    vector<pair<Druzyna, Druzyna>> pary_przedcwiercfinalowe; // 16 drużyn, 8 meczów, 8 drużyn przechodzi do ćwierćfinału
    vector<pair<Druzyna, Druzyna>> pary_cwiercfinalowe; // 8 drużyn, 4 mecze
    vector<pair<Druzyna, Druzyna>> pary_polfinalowe; // 4 drużyny, 2 mecze
    pair<Druzyna, Druzyna> para_finalowa;

    //wypianie na ekran
    cout << endl << endl << "###############################################" << endl;
    cout << "#################### PRZEDCWIERCFINAL ####################" << endl;
    cout << "###############################################" << endl << endl;

    //wypisanie 3 pierwszych wierszy tabeli przedćwierćfinałowej do pliku
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;
    cout << setfill(' ') << setw(1) << "|" << setw(10) << left << "DRUZYNA" << "|" << setw(15) << left << "WYNIK" << setw(1) << "|" << setw(10) << left << "DRUZYNA" << setw(1) << "|" << setw(12) << left << "DOGRYWKA" << "|" << setw(12) << left << "KARNE" << "|" << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;

    //do fazy przedćwierćfinału wychodzą 2 najlepsze drużyny z grupy
    //grupy są posortowane, pobieram drużyny z indeksami 0 i 1, robię z nich parę i dodaję do wektora drużyn przedćwierćfinałowych
    //z każdej grupy wybieram jedną parę dlatego pętlę iterujemy do 8
    for (int i = 0; i < 8; i++){
        pary_przedcwiercfinalowe.push_back(make_pair(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[1]));
    }

    //SYMULACJA MECZÓW PRZEDĆWIERĆWINAŁOWYCH (8 SPOTKAŃ)
    for (int i = 0; i < 8; i++){
        symulujMecz(cout, pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i].second);

        //zamiana par miesjcami, aby mieć łatwiejszy dostęp do drużyny, która przechodzi dalej
        //wygrane drużyny znajdują się po lewej, na pozycji first
        if (pary_przedcwiercfinalowe[i].first.wygrala_przedcwiercfinal == false)
            swap(pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i].second);
    }

    //zwiększamy FAZĘ rozgrywek, metoda symulujMecz inaczej będzie działać
    FAZA++;

    //wypisanie na ekran poczatku tabelki
    cout << endl << endl << "###############################################" << endl;
    cout << "#################### CWIERCFINAL ####################" << endl;
    cout << "###############################################" << endl << endl;

    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;
    cout << setfill(' ') << setw(1) << "|" << setw(10) << left << "DRUZYNA" << "|" << setw(15) << left << "WYNIK" << setw(1) << "|" << setw(10) << left << "DRUZYNA" << setw(1) << "|" << setw(12) << left << "DOGRYWKA" << "|" << setw(12) << left << "KARNE" << "|" << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;

    //kopiuję wygrane drużyny z par przedćwierćwinałowych do par ćwierćfinałowych
    //pętlę iteruję do 8, ale zwiększam iterator co 2, w ten sposób wykona się 4 razy
    for (int i = 0; i < 8; i += 2){
        pary_cwiercfinalowe.push_back(make_pair(pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i + 1].first));
    }

    //symulacja 4 meczów ćwierćfinałowych
    for (int i = 0; i < 4; i++){
        symulujMecz(cout, pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i].second);
        if (pary_cwiercfinalowe[i].first.wygrala_cwiercfinal == false)
            swap(pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i].second);
    }

    //zwiększenie FAZY, PÓŁFINAŁ
    FAZA++;

    //wypisanie na ekran
    cout << endl << endl << "###############################################" << endl;
    cout << "#################### POLFINAL ####################" << endl;
    cout << "###############################################" << endl << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;
    cout << setfill(' ') << setw(1) << "|" << setw(10) << left << "DRUZYNA" << "|" << setw(15) << left << "WYNIK" << setw(1) << "|" << setw(10) << left << "DRUZYNA" << setw(1) << "|" << setw(12) << left << "DOGRYWKA" << "|" << setw(12) << left << "KARNE" << "|" << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;


    //potrzeba 4 drużyn, pętla jak wyżej
    for (int i = 0; i < 4; i += 2){
        pary_polfinalowe.push_back(make_pair(pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i + 1].first));
    }

    //symulacja 2óch meczów półfinałowych
    for (int i = 0; i < 2; i++){
        symulujMecz(cout, pary_polfinalowe[i].first, pary_polfinalowe[i].second);
        if (pary_polfinalowe[i].first.wygrala_polfinal == false)
            swap(pary_polfinalowe[i].first, pary_polfinalowe[i].second);
    }

    //FINAŁ
    FAZA++;

    cout << endl << endl << "###############################################" << endl;
    cout << "#################### FINAL ####################" << endl;
    cout << "###############################################" << endl << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;
    cout << setfill(' ') << setw(1) << "|" << setw(10) << left << "DRUZYNA" << "|" << setw(15) << left << "WYNIK" << setw(1) << "|" << setw(10) << left << "DRUZYNA" << setw(1) << "|" << setw(12) << left << "DOGRYWKA" << "|" << setw(12) << left << "KARNE" << "|" << endl;
    cout << setfill('-') << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(10) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << setw(12) << "-" << setw(1) << "+" << endl;

    para_finalowa = make_pair(pary_polfinalowe[0].first, pary_polfinalowe[1].first);

    //symulacja meczu
    symulujMecz(cout, para_finalowa.first, para_finalowa.second);

    cout << endl << endl;

    //tworzę tymczasową drużynę i przypisuję do niej wygraną z finałowej pary

    Druzyna wygrana;
    if (para_finalowa.first.wygrala_final)
        wygrana = para_finalowa.first;
    else
        wygrana = para_finalowa.second;

    //wypisanie kto zwyciężył turniej
    cout << "###########################" << endl;
    cout << "Zwyciezca: " << wygrana.nazwa << endl;
    cout << "###########################" << endl;

}
