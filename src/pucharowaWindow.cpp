#include "pucharowaWindow.h"
#include "ui_pucharowaWindow.h"
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
//#include "biblioteki.h"
#include "metody.h"

pucharowaWindow::~pucharowaWindow()
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

void pucharowaWindow::closeEvent(QCloseEvent *bar)
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

void pucharowaWindow::wstecz(){
	foreach(QWidget *widget, qApp->topLevelWidgets())
		if (widget->windowTitle() == "Podsumowanie Fazy Grupowej")
			widget->raise();
}

void pucharowaWindow::odpalZakonczenie(){
	if (zakonczenieWindow == 0){
		zakonczenieWindow = new ZakonczenieWindow();
		zakonczenieWindow->show();
		zakonczenieWindow->wpiszDruzyny(zwyciezcy);
	}
	else zakonczenieWindow->raise();
}

pucharowaWindow::pucharowaWindow(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::pucharowaWindow)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
	zakonczenieWindow = 0;
	connect(ui->dalejButton, SIGNAL(released()), this, SLOT(odpalZakonczenie()));
	connect(ui->wsteczButton, SIGNAL(released()), this, SLOT(wstecz()));
	this->setWindowTitle("Faza Pucharowa");



	// dwie osobne czcionki
    QFont fontNaglowka("Helvetica", 10, QFont::Bold);
    QFont fontNazw("Helvetica", 8, QFont::Bold);
	
	//MAKSYMALNE WYMIARY W PIXELACH
	this->setMaximumHeight(650);
	this->setMaximumWidth(1080);




    /*
     *
     *
     * PRZEDCWIERCFINAL
     *
     * */




		// Teraz będą wszystkie 4 pozostałe tabelki - przed, cwierc, pol i final.
		// np. layout od polfinalu nazywa sie po prostu 'polfinal'.
		// wstawić tabelke polfinalowa do polfinalu
		// ui->polfinal->addWidget(polfinalTable);


		// tab przedcwiercfinalowa
        przedcwiercfinalTable = new QTableWidget();

        przedcwiercfinalTable->verticalHeader()->setVisible(false);
        przedcwiercfinalTable->horizontalHeader()->setVisible(false);

        // ustawiam ilosc wierszy na 10, kolumn na 5
        przedcwiercfinalTable->setRowCount(10);
        przedcwiercfinalTable->setColumnCount(5);

        przedcwiercfinalTable->horizontalHeader()->setDefaultSectionSize(65);
        przedcwiercfinalTable->verticalHeader()->setDefaultSectionSize(22);


        przedcwiercfinalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
        przedcwiercfinalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
        przedcwiercfinalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        przedcwiercfinalTable->setColumnWidth(0, 118);
        przedcwiercfinalTable->setRowHeight(0, 29);

		
        // naglowki
        QTableWidgetItem* name1 = new QTableWidgetItem("PRZEDĆWIERĆFINAŁ");
        QTableWidgetItem* one1 = new QTableWidgetItem("Drużyna");
        QTableWidgetItem* two1 = new QTableWidgetItem("Wynik");
        QTableWidgetItem* three1 = new QTableWidgetItem("Drużyna");
        QTableWidgetItem* four1 = new QTableWidgetItem("Dogrywka");
        QTableWidgetItem* five1 = new QTableWidgetItem("Karne");

		// całej tabelce ustawiam MINIMALNĄ SZEROKOŚĆ I WYSOKOŚ
		// dzięki temu pojawi się suwak
		przedcwiercfinalTable->setMinimumWidth(380);
		przedcwiercfinalTable->setMinimumHeight(230);

		// scalam pierwszy wiersz
        przedcwiercfinalTable->setSpan(0,0,1,5);

		// wstawiam do niego napis w 'name1' czyli PRZEDCWIERCFINAL
        przedcwiercfinalTable->setItem(0, 0, name1);
		// i ustawiam kolor tla na szary
        przedcwiercfinalTable->item(0,0)->setBackground(Qt::lightGray);

		// wstawiam reszte naglowkow do 1 wiersza (nie do zerowego, bo w zerowym jest napis PRZEDCWIERCFINAL)
        przedcwiercfinalTable->setItem(1, 0, one1);
        przedcwiercfinalTable->setItem(1, 1, two1);
        przedcwiercfinalTable->setItem(1, 2, three1);
        przedcwiercfinalTable->setItem(1, 3, four1);
        przedcwiercfinalTable->setItem(1, 4, five1);


		// ustawiam, żeby user nie mogl edytować wartości w tabelce
		przedcwiercfinalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

		// wstawiam tabelkę do layoutu w komórkę (0,0)
		// ustawiam też AlignCenter, żeby tabelki przedcwierc, cwierc itp były na środku okna (layout jest rozciagniety na cale okno).
		ui->przedcwiercfinal->addWidget(przedcwiercfinalTable, 0, 0, Qt::AlignCenter);



		// środkujem tekst w nagłówku ("PRZEDCWIERCFINAL") i ustawiam jego czcionke
        przedcwiercfinalTable->item(0,0)->setTextAlignment(Qt::AlignCenter);
        przedcwiercfinalTable->item(0,0)->setFont(fontNaglowka);

		//mniejszym naglowkom - Druzyna, Wynik, Druzyna... też ustawiamy wyśrodkowanie i czcionke
        for(int k=0;k<5;k++){
            przedcwiercfinalTable->item(1,k)->setTextAlignment(Qt::AlignCenter);
            przedcwiercfinalTable->item(1,k)->setFont(fontNazw);
        }

        //CWIERCFINAL
        
       
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




             // POLFINAL
            



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


             
                QTableWidgetItem* name3 = new QTableWidgetItem("PÓŁFINAŁ");
                QTableWidgetItem* one3 = new QTableWidgetItem("Drużyna");
                QTableWidgetItem* two3 = new QTableWidgetItem("Wynik");
                QTableWidgetItem* three3 = new QTableWidgetItem("Drużyna");
                QTableWidgetItem* four3 = new QTableWidgetItem("Dogrywka");
                QTableWidgetItem* five3 = new QTableWidgetItem("Karne");


                polfinalTable->setSpan(0,0,1,5);
              
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


				//3 miejsce
				
				
				trzecie_miejsce_Table = new QTableWidget();
				trzecie_miejsce_Table->verticalHeader()->setVisible(false);
				trzecie_miejsce_Table->horizontalHeader()->setVisible(false);
			
				trzecie_miejsce_Table->setRowCount(3);
				trzecie_miejsce_Table->setColumnCount(5);
				trzecie_miejsce_Table->horizontalHeader()->setDefaultSectionSize(65);
				trzecie_miejsce_Table->verticalHeader()->setDefaultSectionSize(22);

				trzecie_miejsce_Table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
				trzecie_miejsce_Table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

				trzecie_miejsce_Table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

				trzecie_miejsce_Table->setColumnWidth(0, 118);
				trzecie_miejsce_Table->setRowHeight(0, 29);


			
				QTableWidgetItem* name5 = new QTableWidgetItem("3 miejsce");
				QTableWidgetItem* one5 = new QTableWidgetItem("Drużyna");
				QTableWidgetItem* two5 = new QTableWidgetItem("Wynik");
				QTableWidgetItem* three5 = new QTableWidgetItem("Drużyna");
				QTableWidgetItem* four5 = new QTableWidgetItem("Dogrywka");
				QTableWidgetItem* five5 = new QTableWidgetItem("Karne");

				trzecie_miejsce_Table->setSpan(0, 0, 1, 5);
				
				trzecie_miejsce_Table->setItem(0, 0, name5);
				trzecie_miejsce_Table->item(0, 0)->setBackground(Qt::darkGreen);
				trzecie_miejsce_Table->setItem(1, 0, one5);
				trzecie_miejsce_Table->setItem(1, 1, two5);
				trzecie_miejsce_Table->setItem(1, 2, three5);
				trzecie_miejsce_Table->setItem(1, 3, four5);
				trzecie_miejsce_Table->setItem(1, 4, five5);
				trzecie_miejsce_Table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
				trzecie_miejsce_Table->item(0, 0)->setFont(fontNaglowka);

				trzecie_miejsce_Table->setMinimumWidth(380);
				trzecie_miejsce_Table->setMinimumHeight(78);
				trzecie_miejsce_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
				ui->trzecieMiejsce->addWidget(trzecie_miejsce_Table, 0, 0, Qt::AlignCenter);
				
				trzecie_miejsce_Table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
				trzecie_miejsce_Table->item(0, 0)->setFont(fontNaglowka);
				for (int k = 0; k<5; k++){
					trzecie_miejsce_Table->item(1, k)->setTextAlignment(Qt::AlignCenter);
					trzecie_miejsce_Table->item(1, k)->setFont(fontNazw);
				}

                 // FINAL
            

                    finalTable = new QTableWidget();
                    finalTable->verticalHeader()->setVisible(false);
                    finalTable->horizontalHeader()->setVisible(false);
                   
                    finalTable->setRowCount(3);
                    finalTable->setColumnCount(5);
                    finalTable->horizontalHeader()->setDefaultSectionSize(65);
                    finalTable->verticalHeader()->setDefaultSectionSize(22);

                    finalTable->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
                    finalTable->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

                    finalTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                    finalTable->setColumnWidth(0, 118);
                    finalTable->setRowHeight(0, 29);


             
                    QTableWidgetItem* name4 = new QTableWidgetItem("FINAŁ");
                    QTableWidgetItem* one4 = new QTableWidgetItem("Drużyna");
                    QTableWidgetItem* two4 = new QTableWidgetItem("Wynik");
                    QTableWidgetItem* three4 = new QTableWidgetItem("Drużyna");
                    QTableWidgetItem* four4 = new QTableWidgetItem("Dogrywka");
                    QTableWidgetItem* five4 = new QTableWidgetItem("Karne");

                    finalTable->setSpan(0,0,1,5);
               
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


void pucharowaWindow::symulujMecz(Druzyna &pierwsza, Druzyna &druga){

	//losuje liczbe od 0.00 do 1.00
	double losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
	double losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);

	//ustawiam ilość goli obu drużyn na 0
	int ile_goli_pierwsza = 0;
	int ile_goli_druga = 0;
	int ile_goli_w_dogrywce_pierwsza = 0;
	int ile_goli_w_dogrywce_druga = 0;
	int ile_goli_karne_pierwsza = 0;
	int ile_goli_karne_druga = 0;


	// LOSOWANIE CZERWONYCH KARTEK:

	// zmienna do losowania liczby od 0 do 1, np 0.42
	double losowanko;

	// szansa na jedną czerwoną kartkę. Jak już ktoś ją zdobędzie,
	// dziele szansę na 2, czyli szansa na drugą będzie już wynosiła 2.5%
	double szansa_pierwsza = 0.05;
	double szansa_druga = 0.05;

	// zaznaczam boola, czy któraś drużyna dostała kartkę
	// jeśli tak, dodaje jej 'osłabienie' na dwa mecze (łącznie z aktualnym)
	bool lewa_dostala = false, prawa_dostala = false;


	// lece po wszystkich zawodnikach z obu drużyn
	for (int i = 0; i < 11; i++) {

		// PIERWSZA DRUZYNA
		// losuje sobie tę liczbę od 0.00 do 1.00
		losowanko = (double)rand() / ((double)RAND_MAX);

		// jeśli liczba jest mniejsza od 'szansy' czyli na początku 0.05 -  czerwona kartka
		if (losowanko < szansa_pierwsza) {
			// więc zmniejszam szanse na gole o 10%
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

	// jeśli któraś drużyna dostała jakąkolwiek kartkę (nawet 11 kartek), na kolejne 2 mecze (łącznie z tym) pozostaje osłabiona
	if (lewa_dostala) pierwsza.ile_meczy_w_oslabieniu += 2;
	if (prawa_dostala) druga.ile_meczy_w_oslabieniu += 2;


	vector<double> druzynowe_szanse_pierwsza = vector<double>(5, 0);
	vector<double> druzynowe_szanse_druga = vector<double>(5, 0);


	// dalej będzie rozgrywany mecz, więc trzeba wybrać, czy drużyna jest osłabiona i użyc 'osłabionych' statystyk,
	// czy jest 'nieosłabiona' i użyc 'nieosłabionych'
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

	//wartości, które zmieniam w danej drużynie
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

	//karne i dogrywka - kiedy remis i faza jest większa niż grupowa



	if (remis && FAZA > 0){
		//dogrywka
		losowanie_goli_pierwszej = (double)rand() / ((double)RAND_MAX);
		losowanie_goli_drugiej = (double)rand() / ((double)RAND_MAX);
		for (int i = 0; i < 5; i++){
			if (losowanie_goli_pierwszej < druzynowe_szanse_pierwsza[i]){
				ile_goli_pierwsza++;
				ile_goli_w_dogrywce_pierwsza++;
			}
			if (losowanie_goli_drugiej < druzynowe_szanse_druga[i]){
				ile_goli_druga++;
				ile_goli_w_dogrywce_druga++;
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
				//losuje liczbę od 0 do 1
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
			//jeśli mam remis, dodaje każdej drużynie po 1 punkcie
			pierwsza.ilosc_pkt_w_fazie_grupowej += 1;
			druga.ilosc_pkt_w_fazie_grupowej += 1;
			//zwiększam obu drużynom ilość remisów
			pierwsza.remisy++;
			druga.remisy++;
		}
		else if (wygrywa_pierwsza){
			//pierwsza drużyna wygrywa
			pierwsza.zwyciestwa++;
			//dostaje 3 pkt w fazie grupowej
			pierwsza.ilosc_pkt_w_fazie_grupowej += 3;
			//drugiej drużynie zwiększam porażki i nie dodaje punktów
			druga.porazki++;
		}
		else if (wygrywa_druga){
			druga.zwyciestwa++;
			druga.ilosc_pkt_w_fazie_grupowej += 3;
			pierwsza.porazki++;
		}
		//zwiększam ilość wszystkich strzelonych bramek o tę ilość, którą strzeliła w danym meczu
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
	case 5:
	{
		if (wygrywa_pierwsza)
			pierwsza.wygrala_3_miejsce = true;
		else if (wygrywa_druga)
			druga.wygrala_3_miejsce = true;
		break;
	}
	}

	

	// faza > 0, grupowa nie interesuje
	if (FAZA > 0){

		// ładuje wynik do postaci '3 : 2'
		string wynik = to_string(ile_goli_pierwsza - ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_druga - ile_goli_w_dogrywce_druga);

		// JEŚLI PRZEDCWIERCFINAL
		if (FAZA == 1){
			// do trzech pierwszych komórek dodaje:
			/*
			nazwe pierwszej druzyny
			wynik
			nazwe drugiej druzyny

			*/

			// wstawiam ją na wiersz PRZED (czyli za pierwszym razem drugi wiersz)
			// i do komórek po kolei 0, 1, 2.

			przedcwiercfinalTable->setItem(PRZED, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
			przedcwiercfinalTable->setItem(PRZED, 1, new QTableWidgetItem(QString::fromStdString(wynik)));
			przedcwiercfinalTable->setItem(PRZED, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));

			// i teraz wpisywanie wynikow.

			// jak jest remis:
			if (remis){
				// do komórki trzeciej wpisuje TAK
				string gole_w_dogrywce = to_string(ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_w_dogrywce_druga);
				przedcwiercfinalTable->setItem(PRZED, 3, new QTableWidgetItem(QString::fromStdString(gole_w_dogrywce)));
				// jeśli są jeszcze karne, wpisuje karne do komórki czwartej
				if (karne){
					string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
					przedcwiercfinalTable->setItem(PRZED, 4, new QTableWidgetItem(QString::fromStdString(ilekarnych)));
				}
				// jeśli nie ma karnych wpisuje NIE w czwartej
				else
					przedcwiercfinalTable->setItem(PRZED, 4, new QTableWidgetItem(QString::fromStdString("--------")));

			}
			else{
				// NIE MA REMISU
				przedcwiercfinalTable->setItem(PRZED, 3, new QTableWidgetItem(QString::fromStdString("--------")));
				przedcwiercfinalTable->setItem(PRZED, 4, new QTableWidgetItem(QString::fromStdString("--------")));
			}
			// i zwiększam PRZED zeby nastepny przed PRZEDCWIERCFINALOWY wpisywał do 3 wiersza, a nie do drugiego. 
			PRZED++;
		}
		// IDENTYCZNA SYTUACJA DLA cwierc, pol i finalu. 
		// zmienia sie tylko:

		else if (FAZA == 2){
			// to
			// nie wpisuje do przedcwiercfinaltable tylko do cwiercfinaltable
			// no i uzywam zmiennej CWIERC, a nie PRZED.
			cwiercfinalTable->setItem(CWIERC, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
			cwiercfinalTable->setItem(CWIERC, 1, new QTableWidgetItem(QString::fromStdString(wynik)));
			cwiercfinalTable->setItem(CWIERC, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


			if (remis){
				string gole_w_dogrywce = to_string(ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_w_dogrywce_druga);
				cwiercfinalTable->setItem(CWIERC, 3, new QTableWidgetItem(QString::fromStdString(gole_w_dogrywce)));
				if (karne){
					string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
					cwiercfinalTable->setItem(CWIERC, 4, new QTableWidgetItem(QString::fromStdString(ilekarnych)));
				}
				else
					cwiercfinalTable->setItem(CWIERC, 4, new QTableWidgetItem(QString::fromStdString("--------")));

			}
			else{
				cwiercfinalTable->setItem(CWIERC, 3, new QTableWidgetItem(QString::fromStdString("--------")));
				cwiercfinalTable->setItem(CWIERC, 4, new QTableWidgetItem(QString::fromStdString("--------")));
			}
			CWIERC++;
		}
		else if (FAZA == 3){
			polfinalTable->setItem(POL, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
			polfinalTable->setItem(POL, 1, new QTableWidgetItem(QString::fromStdString(wynik)));
			polfinalTable->setItem(POL, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


			if (remis){
				string gole_w_dogrywce = to_string(ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_w_dogrywce_druga);
				polfinalTable->setItem(POL, 3, new QTableWidgetItem(QString::fromStdString(gole_w_dogrywce)));
				if (karne){
					string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
					polfinalTable->setItem(POL, 4, new QTableWidgetItem(QString::fromStdString(ilekarnych)));
				}
				else
					polfinalTable->setItem(POL, 4, new QTableWidgetItem(QString::fromStdString("--------")));

			}
			else{
				polfinalTable->setItem(POL, 3, new QTableWidgetItem(QString::fromStdString("--------")));
				polfinalTable->setItem(POL, 4, new QTableWidgetItem(QString::fromStdString("--------")));
			}
			POL++;
		}
		else if (FAZA == 4){
			finalTable->setItem(2, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
			finalTable->setItem(2, 1, new QTableWidgetItem(QString::fromStdString(wynik)));
			finalTable->setItem(2, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


			if (remis){
				string gole_w_dogrywce = to_string(ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_w_dogrywce_druga);
				finalTable->setItem(2, 3, new QTableWidgetItem(QString::fromStdString(gole_w_dogrywce)));
				if (karne){
					string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
					finalTable->setItem(2, 4, new QTableWidgetItem(QString::fromStdString(ilekarnych)));
				}
				else
					finalTable->setItem(2, 4, new QTableWidgetItem(QString::fromStdString("--------")));

			}
			else{
				finalTable->setItem(2, 3, new QTableWidgetItem(QString::fromStdString("--------")));
				finalTable->setItem(2, 4, new QTableWidgetItem(QString::fromStdString("--------")));
			}
		}
		else if (FAZA == 5){
			trzecie_miejsce_Table->setItem(2, 0, new QTableWidgetItem(QString::fromStdString(pierwsza.nazwa)));
			trzecie_miejsce_Table->setItem(2, 1, new QTableWidgetItem(QString::fromStdString(wynik)));
			trzecie_miejsce_Table->setItem(2, 2, new QTableWidgetItem(QString::fromStdString(druga.nazwa)));


			if (remis){
				string gole_w_dogrywce = to_string(ile_goli_w_dogrywce_pierwsza) + " : " + to_string(ile_goli_w_dogrywce_druga);
				trzecie_miejsce_Table->setItem(2, 3, new QTableWidgetItem(QString::fromStdString(gole_w_dogrywce)));
				if (karne){
					string ilekarnych = to_string(ile_goli_karne_pierwsza) + " : " + to_string(ile_goli_karne_druga);
					trzecie_miejsce_Table->setItem(2, 4, new QTableWidgetItem(QString::fromStdString(ilekarnych)));
				}
				else
					trzecie_miejsce_Table->setItem(2, 4, new QTableWidgetItem(QString::fromStdString("--------")));

			}
			else{
				trzecie_miejsce_Table->setItem(2, 3, new QTableWidgetItem(QString::fromStdString("--------")));
				trzecie_miejsce_Table->setItem(2, 4, new QTableWidgetItem(QString::fromStdString("--------")));
			}
		}



	}




	// mecz się skończył, więc jeśli drużyna była na nim osłabiona, odejmuje jej 'osłabienie' na jeden mecz
	if (pierwsza.ile_meczy_w_oslabieniu > 0) pierwsza.ile_meczy_w_oslabieniu--;
	if (druga.ile_meczy_w_oslabieniu > 0) druga.ile_meczy_w_oslabieniu--;

	// jeśli drużyna nie jest już osłabiona, cofam jej zmiany w 'szansach osłabionych'
	if (pierwsza.ile_meczy_w_oslabieniu == 0)
		pierwsza.druzynowe_szanse_na_gole_w_oslabieniu = pierwsza.druzynowe_szanse_na_gole;

	if (druga.ile_meczy_w_oslabieniu == 0)
		druga.druzynowe_szanse_na_gole_w_oslabieniu = druga.druzynowe_szanse_na_gole;

}



void pucharowaWindow::wypiszFazePucharowa(vector<GrupaMeczowa>& grupyMeczowe){


	cout << FAZA << endl;
    //tworzę tablice par i jedną parę (finałową)
    vector<pair<Druzyna, Druzyna>> pary_przedcwiercfinalowe; // 16 drużyn, 8 meczów, 8 drużyn przechodzi do ćwierćfinału
    vector<pair<Druzyna, Druzyna>> pary_cwiercfinalowe; // 8 drużyn, 4 mecze
    vector<pair<Druzyna, Druzyna>> pary_polfinalowe; // 4 drużyny, 2 mecze
	pair<Druzyna, Druzyna> para_finalowa, para_3_miejsce;



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

	Druzyna wygrana, przegrana, trzecie, nietrzecie;
	if (para_finalowa.first.wygrala_final){
		przegrana = para_finalowa.second;
		wygrana = para_finalowa.first;
	}
	else{
		wygrana = para_finalowa.second;
		przegrana = para_finalowa.first;
	}


	// 3 miejsce
	FAZA++;


	para_3_miejsce = make_pair(pary_polfinalowe[0].second, pary_polfinalowe[1].second);

	//symulacja meczu
	symulujMecz(para_3_miejsce.first, para_3_miejsce.second);

	if (para_3_miejsce.first.wygrala_3_miejsce){
		nietrzecie = para_3_miejsce.second;
		trzecie = para_3_miejsce.first;
	}
	else{
		trzecie = para_3_miejsce.second;
		nietrzecie = para_3_miejsce.first;
	}

	zwyciezcy.push_back(wygrana);
	zwyciezcy.push_back(przegrana);
	zwyciezcy.push_back(trzecie);
	zwyciezcy.push_back(nietrzecie);


    FAZA = 0;
    PRZED = 2;
    CWIERC = 2;
    POL = 2;
    FINAL = 2;
	
}




