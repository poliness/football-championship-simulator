#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLayout>
#include <QLayoutItem>
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
#include "biblioteki.h"


//faza rozgrywek
static int FAZA = 0;

static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

bool compDouble(const double &d1, const double &d2){
    return d1 < d2;
}

bool compIloscPunktow(const Druzyna &d1, const Druzyna &d2){
    return d1.ilosc_pkt_w_fazie_grupowej > d2.ilosc_pkt_w_fazie_grupowej;
}

bool compRanking(const Druzyna &d1, const Druzyna &d2){
    return d1.druzynowe_szanse_na_gole.front() > d2.druzynowe_szanse_na_gole.front();
}

SimulationWindow::~SimulationWindow()
{
	// czyszczenie tabelek, wszystkich, bo to wskaźniki
    for(auto it = tabelki.begin(); it != tabelki.end(); it++)
        delete *it;

    delete przedcwiercfinalTable;
    delete cwiercfinalTable;
    delete polfinalTable;
    delete finalTable;
    delete ui;
}

SimulationWindow::SimulationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);
	

	this->setWindowTitle("Symulacja");
	
	// Jesteśmy w oknie symulacji, zaczynamy rysować tabelki !!!!!!!!!!!!!!!!!!

	// ustawiamy parametry dla jednej tabelki grupowej, kazda tabelka będzie bardzo podobna (tylko inne wartosci i nazwy grup)

	// kazda tabela ma 7 kolumn i 6 wierszy
    int COL = 7, ROW = 6;

	// literki do grup
    string grupy = { "ABCDEFGH" };

	// dwie osobne czcionki - jedna dla GRUPA A, GRUPA B - fontNaglowka, a fontNazw jest do czegos tam innego (po prostu ma mniejsza czcionke)
    QFont fontNaglowka("Helvetica", 10, QFont::Bold);
    QFont fontNazw("Helvetica", 8, QFont::Bold);
	
	// na oknie ustawiamy MAKSYMALNE WYMIARY W PIXELACH
	this->setMaximumHeight(800);
	this->setMaximumWidth(1080);

	// wsadzamy sobie do tablicy kolorki 8 kolorków gotowych już w bibliotece
    QColor kolorki[8];
    kolorki[0] = Qt::red;
    kolorki[1] = Qt::darkCyan;
    kolorki[2] = Qt::darkMagenta;
    kolorki[3] = Qt::green;
    kolorki[4] = Qt::cyan;
    kolorki[5] = Qt::darkRed;
    kolorki[6] = Qt::darkGreen;
    kolorki[7] = Qt::gray;


	// NO I RYSUJEMY 8 TABELEK.
    for(int i=0;i<8;i++){

		// tworzymy nową tabelkę o nazwie table
        QTableWidget* table = new QTableWidget();

		// ustawiamy od razu jej szerokosc i wysokosc na stale wartosci
		table->setMinimumHeight(135);
		table->setMaximumHeight(135);
		table->setMinimumWidth(502);
		table->setMaximumWidth(502);

		// to usuwa nagłowek na górze i z prawej, totalnie nieistotne. Mozesz usunac i zobaczysz, co sie stanie.
        table->verticalHeader()->setVisible(false);
        table->horizontalHeader()->setVisible(false);


            // ustawiamy tabelce 6 wierszy i 7 kolumn
            table->setRowCount(ROW);
            table->setColumnCount(COL);

			// i kazdej kolumnie i wierszowi odpowiednie 'domyslne' szerokosci.
			// co jest teoretycznie niepotrzebne, bo tabelka ma stałą szer/wys, ale niech zostanie
            table->horizontalHeader()->setDefaultSectionSize(65);
            table->verticalHeader()->setDefaultSectionSize(22);

			// no za chiny nie pamiętam LOL. Przypomnę sobie
            table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
            table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
            table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


			// USTAWIAMY KOLUMNĘ 0 na szerokosc 110 - będzie ona najdłuższa
            table->setColumnWidth(0, 110);

			// generujemy 8 nagłówków
			// elementy które wsadza się w komórki to QTableWidgetItemy - po prostu takie komórki
			// wstawia się do nich stringa i potem je się wstawia do tabeli (table).

			// do grupy dopushowujemy literkę: A,B,C....
            string grupa = "GRUPA ";
            grupa.push_back(grupy[i]);

			// robimy sobie te 8 widgetów, Grupa A, Miejsce, Zwyc. i nazwywamy je odpowienio, zeby je potem dodać do tabeli.
            QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(grupa));
            QTableWidgetItem* one = new QTableWidgetItem("Miejsce");
            QTableWidgetItem* two = new QTableWidgetItem("Zwyc.");
            QTableWidgetItem* three = new QTableWidgetItem("Rem.");
            QTableWidgetItem* four = new QTableWidgetItem("Por.");
            QTableWidgetItem* five = new QTableWidgetItem("Bramki");
            QTableWidgetItem* six = new QTableWidgetItem("Pkt.");
            QTableWidgetItem* seven = new QTableWidgetItem("Cwierć.");

			


			// SCALAMY CAŁY PIERWSZY WIERSZ - ten od nazwy grupy i wstawiamy do niego GRUPA A, GRUPA B i tak dalej.
            table->setSpan(0,0,1,7);

			//teraz nasza scalona komórka jest w wierszu zero i kolumnie zero, czyli na pozycji 0,0.
			// no to do tabeli, na pozycje 0,0 wstawiamy 'name' czyli Widget z "GRUPA A".
            table->setItem(0, 0, name);

			// ustawiamy tam wyśrodkowany tekst
            table->item(0,0)->setTextAlignment(Qt::AlignCenter);
			// ustawiamy czcionke na fontNaglowka (tę większą)
            table->item(0,0)->setFont(fontNaglowka);
			// ustawiamy mu kolor tła na kolejny z tablicy kolorków (zadeklarowanej wyzej)
            table->item(0,0)->setBackground(kolorki[i]);


			// no i wstawiamy nasze nagłówki do tabeli w wierszu 1
			// kolejno w kolumnie 0 wstawiamy 'Miejsce', w kolumnie 1 wstawiamy 'Zwyc' itd.
            table->setItem(1, 0, one);
            table->setItem(1, 1, two);
            table->setItem(1, 2, three);
            table->setItem(1, 3, four);
            table->setItem(1, 4, five);
            table->setItem(1, 5, six);
            table->setItem(1, 6, seven);

			
			// wszystkie te 7 naglowkow WYŚRODKOWYWUJEMY/WYŚRODKOWUJEMY
			// i ustawiamy im fonta tego dla Nazw (mniejszego)
            for(int k=0;k<7;k++){
                table->item(1,k)->setTextAlignment(Qt::AlignCenter);
                table->item(1,k)->setFont(fontNazw);
            }
			
		

			// Całej tabeli ustawiamy flagę, że nie można edytować jej pól
			table->setEditTriggers(QAbstractItemView::NoEditTriggers);


     

			// no i teraz tak.

			// tam w tym oknie jest dodany taka jakby tabelka na te tabelki i my musimy je wstawić w 2 kolumny i 4 wiersze (wszystkie 8 grup).
			// ta tabelka sie nazywa symulacja
			// no to musimy jakoś rozkminić, jak wrzucić każdą kolejną w następną komórkę tej tabeli zeby to wyglądało:
			/*
			A B
			C D
			E F
			G H
			*/

			// jesteśmy w pętli, mamy do dyspozycji zmienną i która przyjmuje wartosc 0-7.
			// no to 4 przypadki:

			// jak i jest == 0, albo i == 1 wsadzamy naszą tabelką na pozycję (0,i%2)
			// czyli dla i równego 0 wsadzi nam na (0,0%2) czyli (0,0) << w pierwszą komórkę po lewej na górze
			// dla i równego 1 wsadzi nam na (0,1%2) czyli (0,1) << czyli w drugą komórkę od lewej na górze

			// SJUPER

			// dla i równego 2 wsadzi nam na (1,2%2) czyli (1,0) << drugi wiersz, pierwsza komorka
			// no i dla i równego 3 wsadzi nam na (1,3%2) czyli (1,1)  << drugi wiersz, druga komorka

			// no i tak aż do 8.



            if(i<2) ui->symulacja->addWidget(table,0,i%2);
            else if(i >= 2 && i < 4)
				ui->symulacja->addWidget(table, 1, i % 2);
            else if(i >= 4 && i < 6)
				ui->symulacja->addWidget(table, 2, i % 2);
            else if(i >= 6 && i < 8)
				ui->symulacja->addWidget(table, 3, i % 2);


			// puszujemy naszą tabelkę do wektora tabelki, żeby je pozniej wszystkie usunac z pamieci.
			// to jest tez potrzebne do wpisywania wartosci do tych tabelek. Będziemy się odwoływać do tego wektora jak będziemy chcieli wpisać wyniki meczów.
            tabelki.push_back(table);


			// I TYM SPOSOBEM MAMY NARYSOWANE WSZYSTKIE TABELKI GRUPOWE (jeszcze bez danych w srodku, ale z kolorkami, rozmiarami, nagłówkami itp.
        }

		// okno ustawiamy od razu na duze, zeby bylo duze.
		resize(1200, 1000);



    /*
     *
     *
     * PRZEDCWIERCFINAL
     *
     * */




		// Teraz będą wszystkie 4 pozostałe tabelki - przed, cwierc, pol i final.

		// O co chodzi z layoutami to Ci wytlumacze przy okazji, ale to banalnie proste. 

		// w tej aplikacji graficznej robi sie 5 takich prostokątów i nadaje sie im nazwy i wygląda to tak:

		/*
		----------------------------------------*
		*                                       *
		*               Grupowa                        
		*                                       *
		*---------------------------------------*
		----------------------------------------*
		*                                       *
		*               PRZEDCWIERC
		*                                       *
		*---------------------------------------*
		----------------------------------------*
		*                                       *
		*               CWIERC
		*                                       *
		*---------------------------------------*
		----------------------------------------*
		*                                       *
		*               POLFINAL
		*                                       *
		*---------------------------------------*
		----------------------------------------*
		*                                       *
		*               FINAL
		*                                       *
		*---------------------------------------*
		*/

		// kazdy z tych prostokątków to osobny 'layout' z wlasna nazwa.
		// u nas np. layout od polfinalu nazywa sie po prostu 'polfinal'.
		// więc jak chcemy wstawić tabelke polfinalowa do polfinalu (tego prostokąta na ekranie) piszemy:
		// ui->polfinal->addWidget(polfinalTable);
		// i tyle. tym sposobem mamy jedną część pod drugą, przedcwiercfinal pod grupową i tak dalej.


		// tworzymy tabelkę przedcwiercfinalową
        przedcwiercfinalTable = new QTableWidget();

		// chowamy jej te paski takie brzydkie, niewazne jakie
        przedcwiercfinalTable->verticalHeader()->setVisible(false);
        przedcwiercfinalTable->horizontalHeader()->setVisible(false);

        // ustawiamy ilosc wierszy na 10, kolumn na 5
        przedcwiercfinalTable->setRowCount(10);
        przedcwiercfinalTable->setColumnCount(5);

		// jakies domyślne szerokosci kolumn i wierszy (niepotrzebne, ale potrzebne)
        przedcwiercfinalTable->horizontalHeader()->setDefaultSectionSize(65);
        przedcwiercfinalTable->verticalHeader()->setDefaultSectionSize(22);


		// to samo, nie pamiętam po co to jest, ale sobie przypomnę LOL
        przedcwiercfinalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
        przedcwiercfinalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
        przedcwiercfinalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        przedcwiercfinalTable->setColumnWidth(0, 118);
        przedcwiercfinalTable->setRowHeight(0, 29);

		
        // i tak jak w tamtym przypadku, generujemy sobie naglowki
        QTableWidgetItem* name1 = new QTableWidgetItem("PRZEDĆWIERĆFINAŁ");
        QTableWidgetItem* one1 = new QTableWidgetItem("Drużyna");
        QTableWidgetItem* two1 = new QTableWidgetItem("Wynik");
        QTableWidgetItem* three1 = new QTableWidgetItem("Drużyna");
        QTableWidgetItem* four1 = new QTableWidgetItem("Dogrywka");
        QTableWidgetItem* five1 = new QTableWidgetItem("Karne");

		// całej tabelce ustawiamy MINIMALNĄ SZEROKOŚĆ I WYSOKOŚ - nigdy nie będize mniejsza, nawet jak zmniejszymy okno
		// dzięki temu pojawi nam się suwak, jak apka będzie mniejsza
		przedcwiercfinalTable->setMinimumWidth(380);
		przedcwiercfinalTable->setMinimumHeight(230);

		// scalamy pierwszy wiersz
        przedcwiercfinalTable->setSpan(0,0,1,5);

		// wstawiamy do niego napis w 'name1' czyli PRZEDCWIERCFINAL
        przedcwiercfinalTable->setItem(0, 0, name1);
		// i ustawiamy kolor tla na szary
        przedcwiercfinalTable->item(0,0)->setBackground(Qt::lightGray);

		// wstawiamy reszte naglowkow do 1 wiersza (nie do zerowego, bo w zerowym jest napis PRZEDCWIERCFINAL)
        przedcwiercfinalTable->setItem(1, 0, one1);
        przedcwiercfinalTable->setItem(1, 1, two1);
        przedcwiercfinalTable->setItem(1, 2, three1);
        przedcwiercfinalTable->setItem(1, 3, four1);
        przedcwiercfinalTable->setItem(1, 4, five1);


		// ustawiamy, żeby user nie mogl edytować wartości w tabelce
		przedcwiercfinalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

		// No i wstawiamy tabelkę do naszego layoutu w komórkę (0,0) << jest tylko jedna LOL
		// ustawiamy też AlignCenter, żeby tabelki przedcwierc, cwierc itp były na środku okna (bo layout jest rozciagniety na cale okno).
		ui->przedcwiercfinal->addWidget(przedcwiercfinalTable, 0, 0, Qt::AlignCenter);



		// środkujemy tekst w nagłówku ("PRZEDCWIERCFINAL") i ustawiamy jego czcionke na tę większą
        przedcwiercfinalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
        przedcwiercfinalTable->item(0,0)->setFont(fontNaglowka);

		// no i tym mniejszym naglowkom - Druzyna, Wynik, Druzyna... też ustawiamy wyśrodkowanie i czcionke (tę trochę mniejszą).
        for(int k=0;k<5;k++){
            przedcwiercfinalTable->item(1,k)->setTextAlignment(Qt::AlignCenter);
            przedcwiercfinalTable->item(1,k)->setFont(fontNazw);
        }




		/*
		
		POZOSTAŁE ANALOGICZNIE. 
		Jedyna różnica jest taka, że wysokość tabelki i ilość wierszy jest mniejsza
		no bo w polfinale gra mniej druzyn niz w cwiercfinale itp.
		
		*/

        /*
         *
         *
         * CWIERCFINAL
         *
         * */



            cwiercfinalTable = new QTableWidget();
            cwiercfinalTable->verticalHeader()->setVisible(false);
            cwiercfinalTable->horizontalHeader()->setVisible(false);
          
            cwiercfinalTable->setRowCount(6);
            cwiercfinalTable->setColumnCount(5);
            cwiercfinalTable->horizontalHeader()->setDefaultSectionSize(65);
            cwiercfinalTable->verticalHeader()->setDefaultSectionSize(22);

            cwiercfinalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
            cwiercfinalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

            cwiercfinalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            cwiercfinalTable->setColumnWidth(0, 118);
            cwiercfinalTable->setRowHeight(0, 29);


            
            QTableWidgetItem* name2 = new QTableWidgetItem("ĆWIERĆFINAŁ");
            QTableWidgetItem* one2 = new QTableWidgetItem("Drużyna");
            QTableWidgetItem* two2 = new QTableWidgetItem("Wynik");
            QTableWidgetItem* three2 = new QTableWidgetItem("Drużyna");
            QTableWidgetItem* four2 = new QTableWidgetItem("Dogrywka");
            QTableWidgetItem* five2 = new QTableWidgetItem("Karne");

            cwiercfinalTable->setSpan(0,0,1,5);
            
            cwiercfinalTable->setItem(0, 0, name2);
            cwiercfinalTable->item(0,0)->setBackground(Qt::lightGray);
            cwiercfinalTable->setItem(1, 0, one2);
            cwiercfinalTable->setItem(1, 1, two2);
            cwiercfinalTable->setItem(1, 2, three2);
            cwiercfinalTable->setItem(1, 3, four2);
            cwiercfinalTable->setItem(1, 4, five2);


			cwiercfinalTable->setMinimumWidth(380);
			cwiercfinalTable->setMinimumHeight(143);
			cwiercfinalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
			ui->cwiercfinal->addWidget(cwiercfinalTable,0,0, Qt::AlignCenter);


            cwiercfinalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
            cwiercfinalTable->item(0,0)->setFont(fontNaglowka);
            for(int k=0;k<5;k++){
                cwiercfinalTable->item(1,k)->setTextAlignment(Qt::AlignCenter);
                cwiercfinalTable->item(1,k)->setFont(fontNazw);
            }




            /*
             *
             *
             * POLFINAL
             *
             * */



                polfinalTable = new QTableWidget();
                polfinalTable->verticalHeader()->setVisible(false);
                polfinalTable->horizontalHeader()->setVisible(false);
                //Set table row count 1 and column count 3
                polfinalTable->setRowCount(4);
                polfinalTable->setColumnCount(5);
                polfinalTable->horizontalHeader()->setDefaultSectionSize(65);
                polfinalTable->verticalHeader()->setDefaultSectionSize(22);

                polfinalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
                polfinalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

                polfinalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                polfinalTable->setColumnWidth(0, 118);
                polfinalTable->setRowHeight(0, 29);


                // generate the table widgets
                QTableWidgetItem* name3 = new QTableWidgetItem("PÓŁFINAŁ");
                QTableWidgetItem* one3 = new QTableWidgetItem("Drużyna");
                QTableWidgetItem* two3 = new QTableWidgetItem("Wynik");
                QTableWidgetItem* three3 = new QTableWidgetItem("Drużyna");
                QTableWidgetItem* four3 = new QTableWidgetItem("Dogrywka");
                QTableWidgetItem* five3 = new QTableWidgetItem("Karne");


                polfinalTable->setSpan(0,0,1,5);
                //Add Table items here
                polfinalTable->setItem(0, 0, name3);
                polfinalTable->item(0,0)->setBackground(Qt::lightGray);
                polfinalTable->setItem(1, 0, one3);
                polfinalTable->setItem(1, 1, two3);
                polfinalTable->setItem(1, 2, three3);
                polfinalTable->setItem(1, 3, four3);
                polfinalTable->setItem(1, 4, five3);
                
				polfinalTable->setMinimumWidth(380);
				polfinalTable->setMinimumHeight(99);
				polfinalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
				ui->polfinal->addWidget(polfinalTable, 0, 0, Qt::AlignCenter);


                polfinalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
                polfinalTable->item(0,0)->setFont(fontNaglowka);
                for(int k=0;k<5;k++){
                    polfinalTable->item(1,k)->setTextAlignment(Qt::AlignCenter);
                    polfinalTable->item(1,k)->setFont(fontNazw);
                }


                /*
                 *
                 *
                 * FINAL
                 *
                 * */



                    finalTable = new QTableWidget();
                    finalTable->verticalHeader()->setVisible(false);
                    finalTable->horizontalHeader()->setVisible(false);
                    //Set table row count 1 and column count 3
                    finalTable->setRowCount(3);
                    finalTable->setColumnCount(5);
                    finalTable->horizontalHeader()->setDefaultSectionSize(65);
                    finalTable->verticalHeader()->setDefaultSectionSize(22);

                    finalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
                    finalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

                    finalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                    finalTable->setColumnWidth(0, 118);
                    finalTable->setRowHeight(0, 29);


                    // generate the table widgets
                    QTableWidgetItem* name4 = new QTableWidgetItem("FINAŁ");
                    QTableWidgetItem* one4 = new QTableWidgetItem("Drużyna");
                    QTableWidgetItem* two4 = new QTableWidgetItem("Wynik");
                    QTableWidgetItem* three4 = new QTableWidgetItem("Drużyna");
                    QTableWidgetItem* four4 = new QTableWidgetItem("Dogrywka");
                    QTableWidgetItem* five4 = new QTableWidgetItem("Karne");

                    finalTable->setSpan(0,0,1,5);
                    //Add Table items here
                    finalTable->setItem(0, 0, name4);
                    finalTable->item(0,0)->setBackground(Qt::yellow);
                    finalTable->setItem(1, 0, one4);
                    finalTable->setItem(1, 1, two4);
                    finalTable->setItem(1, 2, three4);
                    finalTable->setItem(1, 3, four4);
                    finalTable->setItem(1, 4, five4);
                    finalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
                    finalTable->item(0,0)->setFont(fontNaglowka);

					finalTable->setMinimumWidth(380);
					finalTable->setMinimumHeight(78);
					finalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
					ui->finau->addWidget(finalTable, 0, 0, Qt::AlignCenter);

                    finalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
                    finalTable->item(0,0)->setFont(fontNaglowka);
                    for(int k=0;k<5;k++){
                        finalTable->item(1,k)->setTextAlignment(Qt::AlignCenter);
                        finalTable->item(1,k)->setFont(fontNazw);
                    }




}

/*



CAŁY STARY KOD Z KILKOMA ZMIANAMI



*/
//funkcja wybiera najlepszą drużynę ze wszystkich kontynentów
Druzyna wybierzNajlepszaZeWszystkichKontynentow(vector<Kontynent>& k){
    double max = INT_MAX, index;
    for (int i = 0; i < 6; i++){
        if (k[i].druzyny_na_kontynencie.size() > 0 && (k[i].druzyny_na_kontynencie.front().druzynowe_szanse_na_gole.front() < max)){
            index = i;
            max = k[i].druzyny_na_kontynencie.front().druzynowe_szanse_na_gole.front();
        }
    }

    Druzyna d = k[index].druzyny_na_kontynencie.front();
    k[index].druzyny_na_kontynencie.pop_front();
    return d;
}


void SimulationWindow::symulujMecz(Druzyna &pierwsza, Druzyna &druga){

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
        druzynowe_szanse_druga = druga.druzynowe_szanse_na_gole_w_oslabieniu;
    else druzynowe_szanse_druga = druga.druzynowe_szanse_na_gole;




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
			if (losowanie_goli_pierwszej < druzynowe_szanse_pierwsza[i]){
				ile_goli_pierwsza++;
			}
			if (losowanie_goli_drugiej < druzynowe_szanse_druga[i]){
				ile_goli_druga++;
			}
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
        if (ile_goli_karne_pierwsza > ile_goli_karne_druga)
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

	// teraz zamiast wypisywać na ekran, musimy wypisywać do tabelek. Tutaj odbywa się wypisywanie przedcwierć aż do finału.
	// na samej górze pliku jest takie coś:

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	// jako, że my do metody symulujMecz() przekazujemy tylko druzyny, nie mozemy kontrolowac 
	// który mecz np. polfinalowy jest aktualnie rozgrywany i do którego wiersza mamy coś wpisać.
	// oczywiście, że będizemy je wpisywać po kolei, pierwszy mecz do pierwszego wolnego wiersza, drugi do drugiego, ale i tak nie wiemy, do którego wpisać, musimy mieć jakieś zmienne,
	// mowiące nam, do którego wiersza powinniśmy teraz wpisać.

	// dlatego mamy te liczniki:

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	// weźmy np. tabelke cwiercfinalowa która nazywa sie cwiercfinalTable.
	// pierwszy wiersz jaki mozemy wypelnic meczem to 2,
	// bo wiersz 0 ma napis CWIERCFINAL a wiersz 1 ma nagłówki Druzyna, Wynik, Druzyna itp.

	// DLATEGO TEŻ mamy zmienną ĆWIERĆ ustawioną na 2, więc pierwszy mecz wpiszemy w wiersz dwa i zwiększymy ĆWIERĆ.
	// nastepny mecz wpiszemy już w wiersz ĆWIERĆ równy trzy i tak dalej.




	 
	// faza > 0, grupowa nas nie interesuje
    if (FAZA > 0){

		// ładujemy wynik do postaci '3 : 2'
        string wynik = to_string(ile_goli_pierwsza) + " : " + to_string(ile_goli_druga);

		// JEŚLI MAMY PRZEDCWIERCFINAL
        if(FAZA == 1){
			// do trzech pierwszych komórek dodajemy:
			/*
				nazwe pierwszej druzyny
				wynik
				nazwe drugiej druzyny

			*/

			// Logicznie wstawiamy ją na wiersz PRZED (czyli za pierwszym razem drugi wiersz)
			// i do komórek po kolei 0, 1, 2.

            przedcwiercfinalTable->setItem(PRZED,0,new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
            przedcwiercfinalTable->setItem(PRZED,1,new QTableWidgetItem(QString::fromStdString(wynik)));
            przedcwiercfinalTable->setItem(PRZED,2,new QTableWidgetItem(QString::fromStdString(druga.nazwa)));

			// i teraz będziemy wpisywać wyniki.
			// wszystko jest na tej samej zasadzie

			// jak jest remis:
            if (remis){
				// do komórki trzeciej wpisujemy TAK
                  przedcwiercfinalTable->setItem(PRZED,3,new QTableWidgetItem(QString::fromStdString("TAK")));
				  // jeśli są jeszcze karne, wpisujemy karne do komórki czwartej
                if (karne){
                     string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
                     przedcwiercfinalTable->setItem(PRZED,4,new QTableWidgetItem(QString::fromStdString(ilekarnych)));
                }
				// jeśli nie ma karnych wpisujemy NIE w czwartej
                else
                   przedcwiercfinalTable->setItem(PRZED,4,new QTableWidgetItem(QString::fromStdString("NIE")));

            }
            else{
				// NIE MA REMISU
                przedcwiercfinalTable->setItem(PRZED,3,new QTableWidgetItem(QString::fromStdString("NIE")));
                przedcwiercfinalTable->setItem(PRZED,4,new QTableWidgetItem(QString::fromStdString("NIE")));
            }
			// i zwiększamy PRZED zeby nastepny przed PRZEDCWIERCFINALOWY wpisywał do 3 wiersza, a nie do drugiego. 
			// i tak dalej.
            PRZED++;
        }
		// IDENTYCZNA SYTUACJA DLA cwierc, pol i finalu. 
		// zmienia sie tylko:

        else if(FAZA == 2){
			// to
			// nie wpisujemy do przedcwiercfinaltable tylko do cwiercfinaltable
			// no i uzywamy zmienne CWIERC, a nie PRZED.
            cwiercfinalTable->setItem(CWIERC,0,new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
            cwiercfinalTable->setItem(CWIERC,1,new QTableWidgetItem(QString::fromStdString(wynik)));
            cwiercfinalTable->setItem(CWIERC,2,new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


            if (remis){
				
				cwiercfinalTable->setItem(CWIERC, 3, new QTableWidgetItem(QString::fromStdString("TAK")));
                if (karne){
                     string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
                     cwiercfinalTable->setItem(CWIERC,4,new QTableWidgetItem(QString::fromStdString(ilekarnych)));
                }
                else
                   cwiercfinalTable->setItem(CWIERC,4,new QTableWidgetItem(QString::fromStdString("NIE")));

            }
            else{
                cwiercfinalTable->setItem(CWIERC,3,new QTableWidgetItem(QString::fromStdString("NIE")));
                cwiercfinalTable->setItem(CWIERC,4,new QTableWidgetItem(QString::fromStdString("NIE")));
            }
            CWIERC++;
        }
        else if(FAZA == 3){
            polfinalTable->setItem(POL,0,new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
            polfinalTable->setItem(POL,1,new QTableWidgetItem(QString::fromStdString(wynik)));
            polfinalTable->setItem(POL,2,new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


            if (remis){
				polfinalTable->setItem(POL, 3, new QTableWidgetItem(QString::fromStdString("TAK")));
                if (karne){
                     string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
                     polfinalTable->setItem(POL,4,new QTableWidgetItem(QString::fromStdString(ilekarnych)));
                }
                else
                   polfinalTable->setItem(POL,4,new QTableWidgetItem(QString::fromStdString("NIE")));

            }
            else{
                polfinalTable->setItem(POL,3,new QTableWidgetItem(QString::fromStdString("NIE")));
                polfinalTable->setItem(POL,4,new QTableWidgetItem(QString::fromStdString("NIE")));
            }
            POL++;
        }
        else if(FAZA == 4){
            finalTable->setItem(FINAL,0,new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
            finalTable->setItem(FINAL,1,new QTableWidgetItem(QString::fromStdString(wynik)));
            finalTable->setItem(FINAL,2,new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


            if (remis){
				finalTable->setItem(FINAL, 3, new QTableWidgetItem(QString::fromStdString("TAK")));
                if (karne){
                     string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
                     finalTable->setItem(FINAL,4,new QTableWidgetItem(QString::fromStdString(ilekarnych)));
                }
                else
                   finalTable->setItem(FINAL,4,new QTableWidgetItem(QString::fromStdString("NIE")));

            }
            else{
                finalTable->setItem(FINAL,3,new QTableWidgetItem(QString::fromStdString("NIE")));
                finalTable->setItem(FINAL,4,new QTableWidgetItem(QString::fromStdString("NIE")));
            }
            FINAL++;
        }



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



// to coś wypisuje tabelki fazy grupowej:
void SimulationWindow::wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe){

	// 8 tabelek, więc iteracja 8 razy
    for (int i = 0; i < 8; i++){

		// to nam tworzy nazwy np.

		/*
		1: Kolumbia
		2: Kostaryka
		3: USA
		4: Watykan
		
		*/
        string d1 = "1: " + grupyMeczowe[i].druzyny_w_grupie[0].nazwa;
        string d2 = "2: " + grupyMeczowe[i].druzyny_w_grupie[1].nazwa;
        string d3 = "3: " + grupyMeczowe[i].druzyny_w_grupie[2].nazwa;
        string d4 = "4: " + grupyMeczowe[i].druzyny_w_grupie[3].nazwa;

		// to nam tworzy stosunek bramek trafionych do straconych
        string bramki1 = to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_stracone);
        string bramki2 = to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_stracone);
        string bramki3 = to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_stracone);
        string bramki4 = to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_stracone);




		// No i tu trochę rąbania:

		// w zerowej kolumnie na miejscach 2,3,4,5 wstawiamy nazwy te z góry np. 1: Kolumbia
        tabelki[i]->setItem(2,0,new QTableWidgetItem(QString::fromStdString(d1)));
        tabelki[i]->setItem(3,0,new QTableWidgetItem(QString::fromStdString(d2)));
        tabelki[i]->setItem(4,0,new QTableWidgetItem(QString::fromStdString(d3)));
        tabelki[i]->setItem(5,0,new QTableWidgetItem(QString::fromStdString(d4)));


		// w pierwszej kolumnie ilosc wygranych
        tabelki[i]->setItem(2,1,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].zwyciestwa)));
        tabelki[i]->setItem(3,1,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].zwyciestwa)));
        tabelki[i]->setItem(4,1,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].zwyciestwa)));
        tabelki[i]->setItem(5,1,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].zwyciestwa)));

		// w drugiej remisow
        tabelki[i]->setItem(2,2,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].remisy)));
        tabelki[i]->setItem(3,2,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].remisy)));
        tabelki[i]->setItem(4,2,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].remisy)));
        tabelki[i]->setItem(5,2,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].remisy)));

		// w trzeciej porazek
        tabelki[i]->setItem(2,3,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].porazki)));
        tabelki[i]->setItem(3,3,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].porazki)));
        tabelki[i]->setItem(4,3,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].porazki)));
        tabelki[i]->setItem(5,3,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].porazki)));

		// w czwartek stosunek bramek
        tabelki[i]->setItem(2,4,new QTableWidgetItem(QString::fromStdString(bramki1)));
        tabelki[i]->setItem(3,4,new QTableWidgetItem(QString::fromStdString(bramki2)));
        tabelki[i]->setItem(4,4,new QTableWidgetItem(QString::fromStdString(bramki3)));
        tabelki[i]->setItem(5,4,new QTableWidgetItem(QString::fromStdString(bramki4)));

		// w piatej ilosc pkt w fazie grupowej
        tabelki[i]->setItem(2,5,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].ilosc_pkt_w_fazie_grupowej)));
        tabelki[i]->setItem(3,5,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].ilosc_pkt_w_fazie_grupowej)));
        tabelki[i]->setItem(4,5,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].ilosc_pkt_w_fazie_grupowej)));
        tabelki[i]->setItem(5,5,new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].ilosc_pkt_w_fazie_grupowej)));


		// no i która przeszła do przedcwierćfinału, a która nie.
        tabelki[i]->setItem(2,6,new QTableWidgetItem(QString::fromStdString("TAK")));
        tabelki[i]->setItem(3,6,new QTableWidgetItem(QString::fromStdString("TAK")));
        tabelki[i]->setItem(4,6,new QTableWidgetItem(QString::fromStdString("NIE")));
        tabelki[i]->setItem(5,6,new QTableWidgetItem(QString::fromStdString("NIE")));
    }
}




// wtedy mieliśmy MAINA, teraz mamy tę metodę. 
// ona przyjmuje nasze 32 druzyny które przekazujemy z glownego okna

// kilka linii niżej przy wykrzyknikach przypisujemy sobie druzyny do druzyn i program działa IDENTYCZNIE JAK WTEDY.

// na samym koncu tej metody jeszcze czyscimy te statiki:

//static int FAZA = 0;
//static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

// bo jak user drugi raz zasymuluje, to musi to robić na czysto.


void SimulationWindow::rozpocznijSymulacje(list<Druzyna> zaladowane){

    //lista, do ktorej wczytamy druzyny z pliku
    list<Druzyna> druzyny_z_pliku;



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



    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/

	// tu je przypisujemy i cały program działa tak, jak działał.
    druzyny_z_pliku = zaladowane;

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
        kontynenty[i].druzyny_na_kontynencie.sort(compRanking);
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
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[1]);
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[2]);
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[3]);
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[2]);
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[3]);
        symulujMecz(grupyMeczowe[i].druzyny_w_grupie[2], grupyMeczowe[i].druzyny_w_grupie[3]);
    }
    cout << endl;

    //KONIEC FAZY GRUPOWEJ, metoda 'symulujMecz' będzie działać inaczej, przechodzimy do FAZY PRZEDCWIERCFINALOWEJ
    FAZA++;

    //sortuję wszystkie grupy meczowe wg ilości zdobytych punktów (od największej do najmniejszej)
    for (int i = 0; i < 8; i++){
        sort(grupyMeczowe[i].druzyny_w_grupie.begin(), grupyMeczowe[i].druzyny_w_grupie.end(), compIloscPunktow);
    }

    //metoda wypisuje tabelki grup wraz ze statystykami
    wypiszFazeGrupowa(grupyMeczowe);


    //tworzę tablice par i jedną parę (finałową)
    vector<pair<Druzyna, Druzyna>> pary_przedcwiercfinalowe; // 16 drużyn, 8 meczów, 8 drużyn przechodzi do ćwierćfinału
    vector<pair<Druzyna, Druzyna>> pary_cwiercfinalowe; // 8 drużyn, 4 mecze
    vector<pair<Druzyna, Druzyna>> pary_polfinalowe; // 4 drużyny, 2 mecze
    pair<Druzyna, Druzyna> para_finalowa;



    //do fazy przedćwierćfinału wychodzą 2 najlepsze drużyny z grupy
    //grupy są posortowane, pobieram drużyny z indeksami 0 i 1, robię z nich parę i dodaję do wektora drużyn przedćwierćfinałowych
    //z każdej grupy wybieram jedną parę dlatego pętlę iterujemy do 8
    for (int i = 0; i < 8; i++){
        pary_przedcwiercfinalowe.push_back(make_pair(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[1]));
    }

    //SYMULACJA MECZÓW PRZEDĆWIERĆWINAŁOWYCH (8 SPOTKAŃ)
    for (int i = 0; i < 8; i++){
        symulujMecz(pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i].second);

        //zamiana par miesjcami, aby mieć łatwiejszy dostęp do drużyny, która przechodzi dalej
        //wygrane drużyny znajdują się po lewej, na pozycji first
        if (pary_przedcwiercfinalowe[i].first.wygrala_przedcwiercfinal == false)
            swap(pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i].second);
    }

    //zwiększamy FAZĘ rozgrywek, metoda symulujMecz inaczej będzie działać
    FAZA++;


    //kopiuję wygrane drużyny z par przedćwierćwinałowych do par ćwierćfinałowych
    //pętlę iteruję do 8, ale zwiększam iterator co 2, w ten sposób wykona się 4 razy
    for (int i = 0; i < 8; i += 2){
        pary_cwiercfinalowe.push_back(make_pair(pary_przedcwiercfinalowe[i].first, pary_przedcwiercfinalowe[i + 1].first));
    }

    //symulacja 4 meczów ćwierćfinałowych
    for (int i = 0; i < 4; i++){
        symulujMecz(pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i].second);
        if (pary_cwiercfinalowe[i].first.wygrala_cwiercfinal == false)
            swap(pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i].second);
    }

    //zwiększenie FAZY, PÓŁFINAŁ
    FAZA++;



    //potrzeba 4 drużyn, pętla jak wyżej
    for (int i = 0; i < 4; i += 2){
        pary_polfinalowe.push_back(make_pair(pary_cwiercfinalowe[i].first, pary_cwiercfinalowe[i + 1].first));
    }

    //symulacja 2óch meczów półfinałowych
    for (int i = 0; i < 2; i++){
        symulujMecz(pary_polfinalowe[i].first, pary_polfinalowe[i].second);
        if (pary_polfinalowe[i].first.wygrala_polfinal == false)
            swap(pary_polfinalowe[i].first, pary_polfinalowe[i].second);
    }

    //FINAŁ
    FAZA++;


    para_finalowa = make_pair(pary_polfinalowe[0].first, pary_polfinalowe[1].first);

    //symulacja meczu
    symulujMecz(para_finalowa.first, para_finalowa.second);

    cout << endl << endl;

    //tworzę tymczasową drużynę i przypisuję do niej wygraną z finałowej pary

    Druzyna wygrana;
    if (para_finalowa.first.wygrala_final)
        wygrana = para_finalowa.first;
    else
        wygrana = para_finalowa.second;



    FAZA = 0;
    PRZED = 2;
    CWIERC = 2;
    POL = 2;
    FINAL = 2;
}




