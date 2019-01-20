#pragma once
#include "grupowawindow.h"
#include "ui_grupowawindow.h"
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
#include "metody.h"


class OknoZMeczamiGrupowymi;
grupowaWindow::~grupowaWindow()
{
	delete ui;
}


void grupowaWindow::closeEvent(QCloseEvent *bar)
{

	foreach(QWidget *widget, qApp->topLevelWidgets()) {

		if (widget->windowTitle() == "Spis druzyn" || widget->windowTitle() == "Rozklad druzyn" || widget->windowTitle() == "Podsumowanie Fazy Grupowej" ||
			widget->windowTitle() == "Mecze Fazy Grupowej" || widget->windowTitle() == "Faza grupowa" || widget->windowTitle() == "Faza Pucharowa" ||
			widget->windowTitle() == "Zakonczenie Mistrzostw")
			widget->close();

		if (widget->inherits("QMainWindow"))
			(widget)->setEnabled(true);
	}
}

void grupowaWindow::wstecz(){
	foreach(QWidget *widget, qApp->topLevelWidgets())
		if (widget->windowTitle() == "Mecze Fazy Grupowej")
			widget->raise();
}

grupowaWindow::grupowaWindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::grupowaWindow)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	ui->setupUi(this);
	wlaczona = false;
	oknoFinalowe = 0;
	connect(ui->dalejButton, SIGNAL(released()), this, SLOT(odpalOknoFinalowe()));
	connect(ui->wsteczButton, SIGNAL(released()), this, SLOT(wstecz()));
	this->setWindowTitle("Podsumowanie Fazy Grupowej");

	setAttribute(Qt::WA_DeleteOnClose);
	int COL = 7, ROW = 6;

	// literki do grup
	string grupy = { "ABCDEFGH" };

	// dwie osobne czcionki
	QFont fontNaglowka("Helvetica", 10, QFont::Bold);
	QFont fontNazw("Helvetica", 8, QFont::Bold);

	// max wymiary okna w pikselach
	this->setMaximumHeight(715);
	this->setMaximumWidth(1080);

	// do tabelki 8 kolork�w
	QColor kolorki[8];
	kolorki[0] = Qt::red;
	kolorki[1] = Qt::darkCyan;
	kolorki[2] = Qt::darkMagenta;
	kolorki[3] = Qt::green;
	kolorki[4] = Qt::cyan;
	kolorki[5] = Qt::darkRed;
	kolorki[6] = Qt::darkGreen;
	kolorki[7] = Qt::gray;


	// rysowanie 8 tabel
	for (int i = 0; i<8; i++){

		// nowa tabelka o nazwie table
		QTableWidget* table = new QTableWidget();

		// szerokosc i wysokosc na stale wartosci
		table->setMinimumHeight(135);
		table->setMaximumHeight(135);
		table->setMinimumWidth(502);
		table->setMaximumWidth(502);

		// usuwa nag�owek na g�rze i z prawej
		table->verticalHeader()->setVisible(false);
		table->horizontalHeader()->setVisible(false);


		// ustawiam w tabelce 6 wierszy i 7 kolumn
		table->setRowCount(ROW);
		table->setColumnCount(COL);

		// i kazdej kolumnie i wierszowi odpowiednie 'domyslne' szerokosci
		table->horizontalHeader()->setDefaultSectionSize(65);
		table->verticalHeader()->setDefaultSectionSize(22);

		table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


		// kolumna 0 na szerokosc 110
		table->setColumnWidth(0, 110);

		// generuj� 8 nag��wk�w
		// w kom�rki wstawiam QTableWidgetItemy
		// do nich string i do table

		// do grupy dodaj� literk�: A,B,C....
		string grupa = "GRUPA ";
		grupa.push_back(grupy[i]);

		// 8 widget�w, Grupa A, Miejsce, Zwyc. i nazwywam
		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(grupa));
		QTableWidgetItem* one = new QTableWidgetItem("Miejsce");
		QTableWidgetItem* two = new QTableWidgetItem("Zwyc.");
		QTableWidgetItem* three = new QTableWidgetItem("Rem.");
		QTableWidgetItem* four = new QTableWidgetItem("Por.");
		QTableWidgetItem* five = new QTableWidgetItem("Bramki");
		QTableWidgetItem* six = new QTableWidgetItem("Pkt.");
		QTableWidgetItem* seven = new QTableWidgetItem("Cwierc.");




		// SCALAM CA�Y PIERWSZY WIERSZ - od nazwy grupy i wstawiam do niego GRUPA A...
		table->setSpan(0, 0, 1, 7);

		//scalona kom�rka jest w wierszu zero i kolumnie zero
		//do tabeli, na pozycje 0,0 wstawiam 'name' czyli Widget z "GRUPA A"
		table->setItem(0, 0, name);

		// ustawiam tam wy�rodkowany tekst
		table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		// ustawiam czcionke na fontNaglowka
		table->item(0, 0)->setFont(fontNaglowka);
		// ustawiam mu kolor t�a na kolejny z tablicy kolork�w
		table->item(0, 0)->setBackground(kolorki[i]);


		// wstawiam nag��wki do tabeli w wierszu 1
		// kolejno w kolumnie 0 wstawiam 'Miejsce', w kolumnie 1 wstawiamy 'Zwyc'...
		table->setItem(1, 0, one);
		table->setItem(1, 1, two);
		table->setItem(1, 2, three);
		table->setItem(1, 3, four);
		table->setItem(1, 4, five);
		table->setItem(1, 5, six);
		table->setItem(1, 6, seven);


		// wy�rodkowanie wszystkich 7 nag��wk�w
		// ustawiam font dla nazw
		for (int k = 0; k<7; k++){
			table->item(1, k)->setTextAlignment(Qt::AlignCenter);
			table->item(1, k)->setFont(fontNazw);
		}



		// Ca�ej tabeli ustawiam flag�, �e nie mo�na edytowa� jej p�l
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);





		// w oknie tabelka na ma�e tabelki, wstawiam w 2 kolumny i 4 wiersze (wszystkie 8 grup).
		// tabelka - symulacja
		// ma wygl�da�
		/*
		A B
		C D
		E F
		G H
		*/

		// w p�tli, do dyspozycji zmienna i kt�ra przyjmuje wartosc 0-7.
		// 4 przypadki:

		// jak i jest == 0, albo i == 1 wstawiam tabelke na pozycj� (0,i%2)
		// czyli dla i r�wnego 0 wsadzi na (0,0%2) czyli (0,0) << w pierwsz� kom�rk� po lewej na g�rze
		// dla i r�wnego 1 na (0,1%2) czyli (0,1) << czyli w drug� kom�rk� od lewej na g�rze
		// dla i r�wnego 2 na (1,2%2) czyli (1,0) << drugi wiersz, pierwsza komorka
		// dla i r�wnego 3 na (1,3%2) czyli (1,1)  << drugi wiersz, druga komorka

		//do 8.


		//ui->grupowaLayout->setVerticalSpacing(110);
		if (i<2) ui->grupowaLayout->addWidget(table, 0, i % 2);
		else if (i >= 2 && i < 4)
			ui->grupowaLayout->addWidget(table, 1, i % 2);
		else if (i >= 4 && i < 6)
			ui->grupowaLayout->addWidget(table, 2, i % 2);
		else if (i >= 6 && i < 8)
			ui->grupowaLayout->addWidget(table, 3, i % 2);


		// tabelka do wektora tabelki, �eby je pozniej wszystkie usunac z pamieci.
		// potrzebne do wpisywania wartosci do tych tabelek. Odwo�anie do tego wektora przy wpisywaniu wynik�w mecz�w.
		tabelki.push_back(table);


	}

	

	oknoZMeczamiGrupowymi = new OknoZMeczamiGrupowymi(this);
	oknoZMeczamiGrupowymi->show();

	_TABELA = 0;


}


void grupowaWindow::odpalOknoFinalowe(){
	if (oknoFinalowe == 0){
		oknoFinalowe = new pucharowaWindow();
		oknoFinalowe->show();
		oknoFinalowe->wypiszFazePucharowa(grupyMeczowe);
		oknoFinalowe->setAttribute(Qt::WA_DeleteOnClose);
	}
	else oknoFinalowe->raise();

}

void grupowaWindow::rozpiszFazeGrupowa(vector<GrupaMeczowa>& grupy){
	
	
	this->grupyMeczowe = grupy;

	
	cout << FAZA << endl;
	int k = 0;
	for (int i = 0; i < 8; i++){
		_TABELA = i;
		_WIERSZ = 2;
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[1]);
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[2]);
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[0], grupyMeczowe[i].druzyny_w_grupie[3]);
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[2]);
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[1], grupyMeczowe[i].druzyny_w_grupie[3]);
		symulujMecz(grupyMeczowe[i].druzyny_w_grupie[2], grupyMeczowe[i].druzyny_w_grupie[3]);
		
	}
	cout << endl;

	//KONIEC FAZY GRUPOWEJ, metoda 'symulujMecz' b�dzie dzia�a� inaczej, przechodzimy do FAZY PRZEDCWIERCFINALOWEJ
	FAZA++;

	//sortuj� wszystkie grupy meczowe wg ilo�ci zdobytych punkt�w (od najwi�kszej do najmniejszej)
	for (int i = 0; i < 8; i++){
		sort(grupyMeczowe[i].druzyny_w_grupie.begin(), grupyMeczowe[i].druzyny_w_grupie.end(), compIloscPunktow);
	}

	

}


void grupowaWindow::wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe){

	// 8 tabelek, wi�c iteracja 8 razy
	for (int i = 0; i < 8; i++){
		string d1 = "1: " + grupyMeczowe[i].druzyny_w_grupie[0].nazwa;
		string d2 = "2: " + grupyMeczowe[i].druzyny_w_grupie[1].nazwa;
		string d3 = "3: " + grupyMeczowe[i].druzyny_w_grupie[2].nazwa;
		string d4 = "4: " + grupyMeczowe[i].druzyny_w_grupie[3].nazwa;

		// to tworzy stosunek bramek trafionych do straconych
		string bramki1 = to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[0].bramki_stracone);
		string bramki2 = to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[1].bramki_stracone);
		string bramki3 = to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[2].bramki_stracone);
		string bramki4 = to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_strzelone) + " : " + to_string(grupyMeczowe[i].druzyny_w_grupie[3].bramki_stracone);




		

		// w zerowej kolumnie na miejscach 2,3,4,5 wstawiamy nazwy te z g�ry np. 1: Kolumbia
		tabelki[i]->setItem(2, 0, new QTableWidgetItem(QString::fromStdString(d1)));
		tabelki[i]->setItem(3, 0, new QTableWidgetItem(QString::fromStdString(d2)));
		tabelki[i]->setItem(4, 0, new QTableWidgetItem(QString::fromStdString(d3)));
		tabelki[i]->setItem(5, 0, new QTableWidgetItem(QString::fromStdString(d4)));


		// w pierwszej kolumnie ilosc wygranych
		tabelki[i]->setItem(2, 1, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].zwyciestwa)));
		tabelki[i]->setItem(3, 1, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].zwyciestwa)));
		tabelki[i]->setItem(4, 1, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].zwyciestwa)));
		tabelki[i]->setItem(5, 1, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].zwyciestwa)));

		// w drugiej remisow
		tabelki[i]->setItem(2, 2, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].remisy)));
		tabelki[i]->setItem(3, 2, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].remisy)));
		tabelki[i]->setItem(4, 2, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].remisy)));
		tabelki[i]->setItem(5, 2, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].remisy)));

		// w trzeciej porazek
		tabelki[i]->setItem(2, 3, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].porazki)));
		tabelki[i]->setItem(3, 3, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].porazki)));
		tabelki[i]->setItem(4, 3, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].porazki)));
		tabelki[i]->setItem(5, 3, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].porazki)));

		// w czwartek stosunek bramek
		tabelki[i]->setItem(2, 4, new QTableWidgetItem(QString::fromStdString(bramki1)));
		tabelki[i]->setItem(3, 4, new QTableWidgetItem(QString::fromStdString(bramki2)));
		tabelki[i]->setItem(4, 4, new QTableWidgetItem(QString::fromStdString(bramki3)));
		tabelki[i]->setItem(5, 4, new QTableWidgetItem(QString::fromStdString(bramki4)));

		// w piatej ilosc pkt w fazie grupowej
		tabelki[i]->setItem(2, 5, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[0].ilosc_pkt_w_fazie_grupowej)));
		tabelki[i]->setItem(3, 5, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[1].ilosc_pkt_w_fazie_grupowej)));
		tabelki[i]->setItem(4, 5, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[2].ilosc_pkt_w_fazie_grupowej)));
		tabelki[i]->setItem(5, 5, new QTableWidgetItem(QString::number(grupyMeczowe[i].druzyny_w_grupie[3].ilosc_pkt_w_fazie_grupowej)));


		// no i kt�ra przesz�a do przedcwier�fina�u, a kt�ra nie.
		tabelki[i]->setItem(2, 6, new QTableWidgetItem(QString::fromStdString("TAK")));
		tabelki[i]->setItem(3, 6, new QTableWidgetItem(QString::fromStdString("TAK")));
		tabelki[i]->setItem(4, 6, new QTableWidgetItem(QString::fromStdString("NIE")));
		tabelki[i]->setItem(5, 6, new QTableWidgetItem(QString::fromStdString("NIE")));
	}
}

void grupowaWindow::symulujMecz(Druzyna &pierwsza, Druzyna &druga){

	//losuje liczb� od 0.00 do 1.00
	double losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
	double losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);

	//ustawiam ilo�� goli obu dru�yn na 0
	int ile_goli_pierwsza = 0;
	int ile_goli_druga = 0;
	int ile_goli_karne_pierwsza = 0;
	int ile_goli_karne_druga = 0;


	// LOSOWANIE CZERWONYCH KARTEK:

	// zmienna do losowania liczby od 0 do 1, np 0.42
	double losowanko;

	// szansa na jedn� czerwon� kartk�. Jak ju� kto� j� zdob�dzie,
	// dzielimy szans� na 2, czyli szansa na drug� b�dzie ju� wynosi�a 2.5%
	double szansa_pierwsza = 0.05;
	double szansa_druga = 0.05;

	// zaznaczam boola, czy kt�ra� dru�yna dosta�a kartk�
	// je�li tak, dodaje jej 'os�abienie' na dwa mecze (��cznie z aktualnym)
	bool lewa_dostala = false, prawa_dostala = false;


	// petla po wszystkich zawodnikach z obu dru�yn
	for (int i = 0; i < 11; i++) {

		// PIERWSZA DRUZYNA
		// losuje liczb� od 0.00 do 1.00
		losowanko = (double)rand() / ((double)RAND_MAX);

		// je�li liczba jest mniejsza od 'szansy' czyli na pocz�tku 0.05 - mam czerwon� kartk�
		if (losowanko < szansa_pierwsza) {
			// wi�c zmniejszam szanse na gole o 10%
			for (int k = 0; k < 5; k++) {
				pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] -= 0.1;
				if (pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] < 0)
					pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] = 0;
			}
			lewa_dostala = true;
			szansa_pierwsza /= 2;
		}

		// DRUGA DRU�YNA
		losowanko = (double)rand() / ((double)RAND_MAX);
		if (losowanko < szansa_druga) { 
			for (int k = 0; k < 5; k++) {
				druga.druzynowe_szanse_na_gole_w_oslabieniu[k] -= 0.1;
				if (druga.druzynowe_szanse_na_gole_w_oslabieniu[k] < 0)
					druga.druzynowe_szanse_na_gole_w_oslabieniu[k] = 0;
			}
			prawa_dostala = true;
			szansa_druga /= 2;
		}
	}

	// je�li kt�ra� dru�yna dosta�a jak�kolwiek kartk� (nawet 11 kartek), na kolejne 2 mecze (��cznie z tym) pozostaje os�abiona
	if (lewa_dostala) pierwsza.ile_meczy_w_oslabieniu += 2;
	if (prawa_dostala) druga.ile_meczy_w_oslabieniu += 2;


	vector<double> druzynowe_szanse_pierwsza = vector<double>(5, 0);
	vector<double> druzynowe_szanse_druga = vector<double>(5, 0);


	// dalej grany jest mecz, wi�c trzeba wybra�, czy dru�yna jest os�abiona i u�ywam 'os�abionych' statystyk,
	// czy jest 'nieos�abiona' i u�ywam 'nieos�abionych'
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

	//warto�ci, kt�re zmieniam w danej dru�ynie
	bool wygrywa_pierwsza = false;
	bool wygrywa_druga = false;
	bool remis = false;
	bool karne = false;

	//sprawdzam remisy, wygrane i karne
	if (ile_goli_pierwsza == ile_goli_druga)
		remis = true;
	else if (ile_goli_pierwsza > ile_goli_druga)
		wygrywa_pierwsza = true;
	else if (ile_goli_druga > ile_goli_pierwsza)
		wygrywa_druga = true;

	//karne i dogrywka - kiedy jest remis i faza jest wi�ksza ni� grupowa



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

			//5 rzut�w karnych dla pierwszej dru�yny
			for (int i = 0; i < 5; i++){
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);

				if (losowa_liczba < pierwsza.szansa_na_gola_graczy)
					ile_goli_karne_pierwsza++;
			}


			//5 rzut�w karnych dla drugiej dru�yny
			for (int i = 0; i < 5; i++){
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);

				if (losowa_liczba < druga.szansa_na_gola_graczy)
					ile_goli_karne_druga++;
			}

			//kiedy w karnych jest remis
			//dop�ki ilo�� goli jest taka sama
			while (ile_goli_karne_pierwsza == ile_goli_karne_druga){
				//losuje liczb� od 0 do 1
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);
				//je�eli liczba jest mniejsza od 0.5 - pierwsza dru�yna strzela gola
				if (losowa_liczba < 0.5)
					ile_goli_karne_pierwsza++;
				//dla drugiej dru�yny
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


	//FAZA jest zwi�kszana na r�nych etapach programu
	switch (FAZA){

	case 0:
	{
		//FAZA 0 - faza grupowa. Dru�yny zbieraj� punkty za wygrane i remisy, nie dostaj� za przegrane
		if (remis){
			//je�li remis, dodaje ka�dej dru�ynie po 1 punkcie
			pierwsza.ilosc_pkt_w_fazie_grupowej += 1;
			druga.ilosc_pkt_w_fazie_grupowej += 1;
			//zwi�kszam obu dru�ynom ilo�� remis�w
			pierwsza.remisy++;
			druga.remisy++;
		}
		else if (wygrywa_pierwsza){
			//pierwsza dru�yna wygrywa
			pierwsza.zwyciestwa++;
			//dostaje 3 pkt w fazie grupowej
			pierwsza.ilosc_pkt_w_fazie_grupowej += 3;
			//drugiej dru�ynie zwi�kszam pora�ki i nie dodaje punkt�w
			druga.porazki++;
		}
		else if (wygrywa_druga){
			druga.zwyciestwa++;
			druga.ilosc_pkt_w_fazie_grupowej += 3;
			pierwsza.porazki++;
		}
		//zwi�kszam ilo�� wszystkich strzelonych bramek o t� ilo��, kt�r� strzeli�a w danym meczu
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
		// FAZA 1 - przed�wier�fina�owa
		if (wygrywa_pierwsza)
			pierwsza.wygrala_przedcwiercfinal = true;
		else if (wygrywa_druga)
			druga.wygrala_przedcwiercfinal = true;
		break;
	}
	case 2:
	{
		//FAZA 2 - �wier�fina�
		if (wygrywa_pierwsza)
			pierwsza.wygrala_cwiercfinal = true;
		else if (wygrywa_druga)
			druga.wygrala_cwiercfinal = true;
		break;
	}
	case 3:
	{
		//FAZA 3 - p�fina�
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

	// wypisywanie przedcwier� a� do fina�u.

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	//liczniki:

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	// np. tabelka cwiercfinalowa kt�ra nazywa sie cwiercfinalTable.
	// pierwszy wiersz jaki mozna wypelnic meczem to 2,
	// bo wiersz 0 ma napis CWIERCFINAL a wiersz 1 ma nag��wki Druzyna, Wynik, Druzyna itp.

	// DLATEGO TE� zmienna �WIER� jest ustawiona na 2, wi�c pierwszy mecz wpisuje w wiersz dwa i zwi�kszam �WIER�.
	// nastepny mecz wpisze w wiersz �WIER� r�wny trzy...

	// mecz si� sko�czy�, wi�c je�li dru�yna by�a na nim os�abiona, odejmuje jej 'os�abienie' na jeden mecz
	if (pierwsza.ile_meczy_w_oslabieniu > 0) pierwsza.ile_meczy_w_oslabieniu--;
	if (druga.ile_meczy_w_oslabieniu > 0) druga.ile_meczy_w_oslabieniu--;

	// je�li dru�yna nie jest ju� os�abiona, cofam jej zmiany w 'szansach os�abionych'
	if (pierwsza.ile_meczy_w_oslabieniu == 0)
		pierwsza.druzynowe_szanse_na_gole_w_oslabieniu = pierwsza.druzynowe_szanse_na_gole;

	if (druga.ile_meczy_w_oslabieniu == 0)
		druga.druzynowe_szanse_na_gole_w_oslabieniu = druga.druzynowe_szanse_na_gole;

	string temp = to_string(ile_goli_pierwsza) + " : " + to_string(ile_goli_druga);
	QString wynik = QString::fromStdString(temp);

	oknoZMeczamiGrupowymi->tabelki[_TABELA]->setItem(_WIERSZ, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
	oknoZMeczamiGrupowymi->tabelki[_TABELA]->setItem(_WIERSZ, 1, new QTableWidgetItem(wynik));
	oknoZMeczamiGrupowymi->tabelki[_TABELA]->setItem(_WIERSZ, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));

	_WIERSZ++;
}

void grupowaWindow::odpalRozpiskeZeStatystykami(){

	wlaczona = true;
	this->setVisible(true);
	wypiszFazeGrupowa(grupyMeczowe);
}


