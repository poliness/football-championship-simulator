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

	// do tabelki 8 kolorków
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

		// usuwa nag³owek na górze i z prawej
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

		// generujê 8 nag³ówków
		// w komórki wstawiam QTableWidgetItemy
		// do nich string i do table

		// do grupy dodajê literkê: A,B,C....
		string grupa = "GRUPA ";
		grupa.push_back(grupy[i]);

		// 8 widgetów, Grupa A, Miejsce, Zwyc. i nazwywam
		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(grupa));
		QTableWidgetItem* one = new QTableWidgetItem("Miejsce");
		QTableWidgetItem* two = new QTableWidgetItem("Zwyc.");
		QTableWidgetItem* three = new QTableWidgetItem("Rem.");
		QTableWidgetItem* four = new QTableWidgetItem("Por.");
		QTableWidgetItem* five = new QTableWidgetItem("Bramki");
		QTableWidgetItem* six = new QTableWidgetItem("Pkt.");
		QTableWidgetItem* seven = new QTableWidgetItem("Cwierc.");




		// SCALAM CA£Y PIERWSZY WIERSZ - od nazwy grupy i wstawiam do niego GRUPA A...
		table->setSpan(0, 0, 1, 7);

		//scalona komórka jest w wierszu zero i kolumnie zero
		//do tabeli, na pozycje 0,0 wstawiam 'name' czyli Widget z "GRUPA A"
		table->setItem(0, 0, name);

		// ustawiam tam wyœrodkowany tekst
		table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		// ustawiam czcionke na fontNaglowka
		table->item(0, 0)->setFont(fontNaglowka);
		// ustawiam mu kolor t³a na kolejny z tablicy kolorków
		table->item(0, 0)->setBackground(kolorki[i]);


		// wstawiam nag³ówki do tabeli w wierszu 1
		// kolejno w kolumnie 0 wstawiam 'Miejsce', w kolumnie 1 wstawiamy 'Zwyc'...
		table->setItem(1, 0, one);
		table->setItem(1, 1, two);
		table->setItem(1, 2, three);
		table->setItem(1, 3, four);
		table->setItem(1, 4, five);
		table->setItem(1, 5, six);
		table->setItem(1, 6, seven);


		// wyœrodkowanie wszystkich 7 nag³ówków
		// ustawiam font dla nazw
		for (int k = 0; k<7; k++){
			table->item(1, k)->setTextAlignment(Qt::AlignCenter);
			table->item(1, k)->setFont(fontNazw);
		}



		// Ca³ej tabeli ustawiam flagê, ¿e nie mo¿na edytowaæ jej pól
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);





		// w oknie tabelka na ma³e tabelki, wstawiam w 2 kolumny i 4 wiersze (wszystkie 8 grup).
		// tabelka - symulacja
		// ma wygl¹daæ
		/*
		A B
		C D
		E F
		G H
		*/

		// w pêtli, do dyspozycji zmienna i która przyjmuje wartosc 0-7.
		// 4 przypadki:

		// jak i jest == 0, albo i == 1 wstawiam tabelke na pozycjê (0,i%2)
		// czyli dla i równego 0 wsadzi na (0,0%2) czyli (0,0) << w pierwsz¹ komórkê po lewej na górze
		// dla i równego 1 na (0,1%2) czyli (0,1) << czyli w drug¹ komórkê od lewej na górze
		// dla i równego 2 na (1,2%2) czyli (1,0) << drugi wiersz, pierwsza komorka
		// dla i równego 3 na (1,3%2) czyli (1,1)  << drugi wiersz, druga komorka

		//do 8.


		//ui->grupowaLayout->setVerticalSpacing(110);
		if (i<2) ui->grupowaLayout->addWidget(table, 0, i % 2);
		else if (i >= 2 && i < 4)
			ui->grupowaLayout->addWidget(table, 1, i % 2);
		else if (i >= 4 && i < 6)
			ui->grupowaLayout->addWidget(table, 2, i % 2);
		else if (i >= 6 && i < 8)
			ui->grupowaLayout->addWidget(table, 3, i % 2);


		// tabelka do wektora tabelki, ¿eby je pozniej wszystkie usunac z pamieci.
		// potrzebne do wpisywania wartosci do tych tabelek. Odwo³anie do tego wektora przy wpisywaniu wyników meczów.
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

	//KONIEC FAZY GRUPOWEJ, metoda 'symulujMecz' bêdzie dzia³aæ inaczej, przechodzimy do FAZY PRZEDCWIERCFINALOWEJ
	FAZA++;

	//sortujê wszystkie grupy meczowe wg iloœci zdobytych punktów (od najwiêkszej do najmniejszej)
	for (int i = 0; i < 8; i++){
		sort(grupyMeczowe[i].druzyny_w_grupie.begin(), grupyMeczowe[i].druzyny_w_grupie.end(), compIloscPunktow);
	}

	

}


void grupowaWindow::wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe){

	// 8 tabelek, wiêc iteracja 8 razy
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




		

		// w zerowej kolumnie na miejscach 2,3,4,5 wstawiamy nazwy te z góry np. 1: Kolumbia
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


		// no i która przesz³a do przedcwieræfina³u, a która nie.
		tabelki[i]->setItem(2, 6, new QTableWidgetItem(QString::fromStdString("TAK")));
		tabelki[i]->setItem(3, 6, new QTableWidgetItem(QString::fromStdString("TAK")));
		tabelki[i]->setItem(4, 6, new QTableWidgetItem(QString::fromStdString("NIE")));
		tabelki[i]->setItem(5, 6, new QTableWidgetItem(QString::fromStdString("NIE")));
	}
}

void grupowaWindow::symulujMecz(Druzyna &pierwsza, Druzyna &druga){

	//losuje liczbê od 0.00 do 1.00
	double losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
	double losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);

	//ustawiam iloœæ goli obu dru¿yn na 0
	int ile_goli_pierwsza = 0;
	int ile_goli_druga = 0;
	int ile_goli_karne_pierwsza = 0;
	int ile_goli_karne_druga = 0;


	// LOSOWANIE CZERWONYCH KARTEK:

	// zmienna do losowania liczby od 0 do 1, np 0.42
	double losowanko;

	// szansa na jedn¹ czerwon¹ kartkê. Jak ju¿ ktoœ j¹ zdobêdzie,
	// dzielimy szansê na 2, czyli szansa na drug¹ bêdzie ju¿ wynosi³a 2.5%
	double szansa_pierwsza = 0.05;
	double szansa_druga = 0.05;

	// zaznaczam boola, czy któraœ dru¿yna dosta³a kartkê
	// jeœli tak, dodaje jej 'os³abienie' na dwa mecze (³¹cznie z aktualnym)
	bool lewa_dostala = false, prawa_dostala = false;


	// petla po wszystkich zawodnikach z obu dru¿yn
	for (int i = 0; i < 11; i++) {

		// PIERWSZA DRUZYNA
		// losuje liczbê od 0.00 do 1.00
		losowanko = (double)rand() / ((double)RAND_MAX);

		// jeœli liczba jest mniejsza od 'szansy' czyli na pocz¹tku 0.05 - mam czerwon¹ kartkê
		if (losowanko < szansa_pierwsza) {
			// wiêc zmniejszam szanse na gole o 10%
			for (int k = 0; k < 5; k++) {
				pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] -= 0.1;
				if (pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] < 0)
					pierwsza.druzynowe_szanse_na_gole_w_oslabieniu[k] = 0;
			}
			lewa_dostala = true;
			szansa_pierwsza /= 2;
		}

		// DRUGA DRU¯YNA
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

	// jeœli któraœ dru¿yna dosta³a jak¹kolwiek kartkê (nawet 11 kartek), na kolejne 2 mecze (³¹cznie z tym) pozostaje os³abiona
	if (lewa_dostala) pierwsza.ile_meczy_w_oslabieniu += 2;
	if (prawa_dostala) druga.ile_meczy_w_oslabieniu += 2;


	vector<double> druzynowe_szanse_pierwsza = vector<double>(5, 0);
	vector<double> druzynowe_szanse_druga = vector<double>(5, 0);


	// dalej grany jest mecz, wiêc trzeba wybraæ, czy dru¿yna jest os³abiona i u¿ywam 'os³abionych' statystyk,
	// czy jest 'nieos³abiona' i u¿ywam 'nieos³abionych'
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

	//wartoœci, które zmieniam w danej dru¿ynie
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

	//karne i dogrywka - kiedy jest remis i faza jest wiêksza ni¿ grupowa



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

			//5 rzutów karnych dla pierwszej dru¿yny
			for (int i = 0; i < 5; i++){
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);

				if (losowa_liczba < pierwsza.szansa_na_gola_graczy)
					ile_goli_karne_pierwsza++;
			}


			//5 rzutów karnych dla drugiej dru¿yny
			for (int i = 0; i < 5; i++){
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);

				if (losowa_liczba < druga.szansa_na_gola_graczy)
					ile_goli_karne_druga++;
			}

			//kiedy w karnych jest remis
			//dopóki iloœæ goli jest taka sama
			while (ile_goli_karne_pierwsza == ile_goli_karne_druga){
				//losuje liczbê od 0 do 1
				double losowa_liczba = ((double)rand() / (double)RAND_MAX);
				//je¿eli liczba jest mniejsza od 0.5 - pierwsza dru¿yna strzela gola
				if (losowa_liczba < 0.5)
					ile_goli_karne_pierwsza++;
				//dla drugiej dru¿yny
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


	//FAZA jest zwiêkszana na ró¿nych etapach programu
	switch (FAZA){

	case 0:
	{
		//FAZA 0 - faza grupowa. Dru¿yny zbieraj¹ punkty za wygrane i remisy, nie dostaj¹ za przegrane
		if (remis){
			//jeœli remis, dodaje ka¿dej dru¿ynie po 1 punkcie
			pierwsza.ilosc_pkt_w_fazie_grupowej += 1;
			druga.ilosc_pkt_w_fazie_grupowej += 1;
			//zwiêkszam obu dru¿ynom iloœæ remisów
			pierwsza.remisy++;
			druga.remisy++;
		}
		else if (wygrywa_pierwsza){
			//pierwsza dru¿yna wygrywa
			pierwsza.zwyciestwa++;
			//dostaje 3 pkt w fazie grupowej
			pierwsza.ilosc_pkt_w_fazie_grupowej += 3;
			//drugiej dru¿ynie zwiêkszam pora¿ki i nie dodaje punktów
			druga.porazki++;
		}
		else if (wygrywa_druga){
			druga.zwyciestwa++;
			druga.ilosc_pkt_w_fazie_grupowej += 3;
			pierwsza.porazki++;
		}
		//zwiêkszam iloœæ wszystkich strzelonych bramek o tê iloœæ, któr¹ strzeli³a w danym meczu
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
		// FAZA 1 - przedæwieræfina³owa
		if (wygrywa_pierwsza)
			pierwsza.wygrala_przedcwiercfinal = true;
		else if (wygrywa_druga)
			druga.wygrala_przedcwiercfinal = true;
		break;
	}
	case 2:
	{
		//FAZA 2 - æwieræfina³
		if (wygrywa_pierwsza)
			pierwsza.wygrala_cwiercfinal = true;
		else if (wygrywa_druga)
			druga.wygrala_cwiercfinal = true;
		break;
	}
	case 3:
	{
		//FAZA 3 - pó³fina³
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

	// wypisywanie przedcwieræ a¿ do fina³u.

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	//liczniki:

	// static int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;

	// np. tabelka cwiercfinalowa która nazywa sie cwiercfinalTable.
	// pierwszy wiersz jaki mozna wypelnic meczem to 2,
	// bo wiersz 0 ma napis CWIERCFINAL a wiersz 1 ma nag³ówki Druzyna, Wynik, Druzyna itp.

	// DLATEGO TE¯ zmienna ÆWIERÆ jest ustawiona na 2, wiêc pierwszy mecz wpisuje w wiersz dwa i zwiêkszam ÆWIERÆ.
	// nastepny mecz wpisze w wiersz ÆWIERÆ równy trzy...

	// mecz siê skoñczy³, wiêc jeœli dru¿yna by³a na nim os³abiona, odejmuje jej 'os³abienie' na jeden mecz
	if (pierwsza.ile_meczy_w_oslabieniu > 0) pierwsza.ile_meczy_w_oslabieniu--;
	if (druga.ile_meczy_w_oslabieniu > 0) druga.ile_meczy_w_oslabieniu--;

	// jeœli dru¿yna nie jest ju¿ os³abiona, cofam jej zmiany w 'szansach os³abionych'
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


