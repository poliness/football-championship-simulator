#include "rankingWindow.h"
#include "ui_rankingwindow.h"
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

rankingwindow::~rankingwindow()
{
	delete ui;
}


void rankingwindow::closeEvent(QCloseEvent *bar)
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

void rankingwindow::wstecz(){
	foreach(QWidget *widget, qApp->topLevelWidgets())
		if (widget->windowTitle() == "Spis druzyn")
			widget->raise();
}

rankingwindow::rankingwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::rankingwindow)
{
	ui->setupUi(this);
	oknoGrupowe = 0;
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setAttribute(Qt::WA_DeleteOnClose);
	for (GrupaMeczowa gr : grupyMeczowe)
		gr.druzyny_w_grupie.clear();
	
	connect(ui->dalejButton, SIGNAL(released()), this, SLOT(odpalOknoGrupowe()));
	connect(ui->wsteczButton, SIGNAL(released()), this, SLOT(wstecz()));
	this->setWindowTitle("Rozklad druzyn");

	int COL = 2, ROW = 6;

	// literki do grup
	string grupy = { "ABCDEFGH" };

	// dwie osobne czcionki
	QFont fontNaglowka("Helvetica", 10, QFont::Bold);
	QFont fontNazw("Helvetica", 8, QFont::Bold);

	// MAKSYMALNE WYMIARY W PIXELACH
	this->setMaximumHeight(450);
	this->setMaximumWidth(750);

	QColor kolorki[8];
	kolorki[0] = Qt::red;
	kolorki[1] = Qt::darkCyan;
	kolorki[2] = Qt::darkMagenta;
	kolorki[3] = Qt::green;
	kolorki[4] = Qt::cyan;
	kolorki[5] = Qt::darkRed;
	kolorki[6] = Qt::darkGreen;
	kolorki[7] = Qt::gray;


	//8 TABELEK.
	for (int i = 0; i<8; i++){

		//nowa tabelka o nazwie table
		QTableWidget* table = new QTableWidget();

		// ustawiam od razu jej szerokosc i wysokosc na stale wartosci
		table->setMinimumHeight(137);
		table->setMaximumHeight(137);
		table->setMinimumWidth(177);
		table->setMaximumWidth(177);

		table->verticalHeader()->setVisible(false);
		table->horizontalHeader()->setVisible(false);


		table->setRowCount(ROW);
		table->setColumnCount(COL);

		// i kazdej kolumnie i wierszowi odpowiednie 'domyslne' szerokosci.
		table->horizontalHeader()->setDefaultSectionSize(65);
		table->verticalHeader()->setDefaultSectionSize(22);

		table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


		// USTAWIAM KOLUMN� 0 na szerokosc 110
		table->setColumnWidth(0, 110);


		string grupa = "GRUPA ";
		grupa.push_back(grupy[i]);


		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(grupa));
		QTableWidgetItem* one = new QTableWidgetItem("Nazwa");
		QTableWidgetItem* two = new QTableWidgetItem("Sila");


		table->setSpan(0, 0, 1, 7);

	
		table->setItem(0, 0, name);
	
		table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		
		table->item(0, 0)->setFont(fontNaglowka);
	
		table->item(0, 0)->setBackground(kolorki[i]);


		//nag��wki do tabeli w wierszu 1
		table->setItem(1, 0, one);
		table->setItem(1, 1, two);


		for (int k = 0; k<2; k++){
			table->item(1, k)->setTextAlignment(Qt::AlignCenter);
			table->item(1, k)->setFont(fontNazw);
		}


		//flaga, �e nie mo�na edytowa� jej p�l
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	
		ui->rankingLayout->setVerticalSpacing(20);
		if (i<4) ui->rankingLayout->addWidget(table, 0, i % 4);
		else 
			ui->rankingLayout->addWidget(table, 1, i % 4);
	

		
		tabelki.push_back(table);

	}


}


void rankingwindow::odpalOknoGrupowe(){

	if (oknoGrupowe == 0){
		oknoGrupowe = new grupowaWindow();
		oknoGrupowe->show();
		oknoGrupowe->setVisible(false);
		oknoGrupowe->rozpiszFazeGrupowa(grupyMeczowe);
		oknoGrupowe->setAttribute(Qt::WA_DeleteOnClose);
	}
	else{
		int k = 0;
		if (oknoGrupowe->oknoZMeczamiGrupowymi)
			oknoGrupowe->oknoZMeczamiGrupowymi->raise();
		oknoGrupowe->raise();
		int p = 0;
	}
}


void rankingwindow::rozpiszMiejscaWRankingu(list<Druzyna> zaladowane){

	//lista, do ktorej wczytam druzyny z pliku
	list<Druzyna> druzyny_z_pliku;

	srand(time(NULL));

	//vector, kt�ry b�dzie zawiera� 6 kontynent�w
	vector<Kontynent>kontynenty;

	//vector zawieraj�cy 8 grup meczowych do fazy grupowej

	//rozpycham vectory
	for (int i = 0; i < 8; i++)
		grupyMeczowe.push_back(GrupaMeczowa());

	for (int i = 0; i < 6; i++)
		kontynenty.push_back(Kontynent());


	// przepisanie zaladowanych druzny, pierwotnie byly wczytywane z piku
	druzyny_z_pliku = zaladowane;

	//wrzucam dru�yny do odpowiednich kontynent�w
	//p�tla przechodzi przez ca�� list� 32 dru�yn
	//iteratorem jest 'dru�yna'
	for (list<Druzyna>::iterator it = druzyny_z_pliku.begin(); it != druzyny_z_pliku.end(); it++){
		//dru�yn� z listy dodaje do wektora 'kontynenty'
		//ka�da z dru�yn zawiera ju� w sobie nazw� kontynentu
		//dodaje do kontynenty[druzyna.kontynent - 1], poniewa� kontynenty liczone s� od 1, a wektory i tablice maj� numeracj� od 0
		//ka�dy kontynent zawiera list� dru�yn na tym kontynencie (druzyny_na_kontynencie) i to do niej dodaje dru�yn�, na kt�rej aktualnie si� znajduje
		kontynenty[it->kontynent - 1].druzyny_na_kontynencie.push_back(*it);
	}

	//sortuje wszystkie dru�yny na ka�dym kontynencie
	for (int i = 0; i < 6; i++){
		kontynenty[i].druzyny_na_kontynencie.sort(compRanking);
	}

	//LOSOWANIE DRUZYN DO GRUP
	//8 tabel po 4 miejsca
	//zewn�trzna p�tla wype�nia 4 wiersze
	//wewn�trz tej p�tli jest p�tla iterowana do 6:
	//wybieram po najlepszej druzynie z kontynentu, 2 pozosta�e dobieram z puli wszystkich kontynent�w

	//zmienne pomocnicze
	//k_i b�dzie zwi�kszane ca�y czas (ale nigdy nie przekroczy 5)
	int k_i = 0;
	//zmienna do losowania grupy, losuje j� do czasu, a� nie spotkam grupy z 'wolnym miejscem'
	int wylosowana_grupa;
	//4 fazy wyboru = 4 wiersze w tabeli, z ka�d� iteracj� p�tli najbardziej zewn�trznej, zwi�kszam t� zmienn�
	//wstawiaj�c dru�yn� do odpowiedniej grupy wstawiam j� na miejsce 'faza', pierwsze dru�yny na miejsce 0,
	//drugie na miejsce 1, trzecie na miejsce 2 i czwarte na miesjce 3
	int faza_wyboru = 0;
	//zewn�trzna p�tla, iterowana do 4
	for (int k = 0; k < 4; k++){
		//pierwsze 6 dru�yn wybieram z ka�dego kontynetu (jest ich 6)
		//uprzednio zosta�y one posortowane wg 'miejsca w rankingu' dlatego �ci�gam je z pocz�tku listy
		for (int i = 0; i < 6; i++){
			//przypadek: w Australii mam tylko 1 dru�yn�
			//przechodze po kontynentach p�tl� while i szukam NIEPUSTEGO kontynentu;
			//po pierwszej iteracji Autralia b�dzie pusta, program przesta�by dzia�a�
			//k_i % 6 dzia�a w taki spos�b:
			//zaczyna si� od 0, potem po kolei 1,2,3,4,5,6,7,8,9 itd, st�d modulo:
			//dla 0%6 wynik 0
			//dla 1%6 wynik 1
			//dla 5%6 wynik 5
			//dla 6%6 wynik 0 i w ten spos�b zataczam ko�o, zmienna nie wyjdzie poza zakres (poza 5);
			while (kontynenty[k_i % 6].druzyny_na_kontynencie.size() == 0){
				k_i++;
			}
			//tworze tymczasowy obiekt klasy Druzyna i przypisuje do niego dru�yn� z kontynetu z pocz�tku listy (front())
			Druzyna najlepsza = kontynenty[k_i % 6].druzyny_na_kontynencie.front();
			//usuwam powy�sz� dru�yn� z pierwotnej listy
			kontynenty[k_i % 6].druzyny_na_kontynencie.pop_front();

			//
			//GRUPY DLA DRU�YNY
			//losuj� liczb� od 0 do 7 a� do momentu, kiedy dana grupa z tym indeksem b�dzie mie� miejsce
			//kiedy znajd� tak� grup�, zwi�kszam jej zmienn� 'zape�nienie', bo w tej fazie dosta�a ju� dru�yn�
			//przyk�ad:
			//grupy 1, 3 i 5 maj� ju� po 1 dru�ynie
			//wylosowali�my 3
			//sprawdzamy czy grupyMeczowe[3].zapelnienie_grupy > faza_wyboru
			//zapelnienie tej grupy jest wi�ksze, bo zosta�o wcze�niej zwi�kszone
			//losujemy ponownie

			do{
				wylosowana_grupa = rand() % 8;
			} while (grupyMeczowe[wylosowana_grupa].zapelnienie_grupy > faza_wyboru);

			//dodaj� dru�yn� do wylosowanej grupy
			grupyMeczowe[wylosowana_grupa].druzyny_w_grupie.push_back(najlepsza);

			//zwi�kszam zape�nienie tej grupy, w ka�dej fazie tylko jedna
			grupyMeczowe[wylosowana_grupa].zapelnienie_grupy++;
			k_i++;
		}

		//grupy 7 i 8 zosta�y bez dru�yn, p�tla dzia�a od 6 do 8
		for (int i = 6; i < 8; i++){
			//losujemy liczb� od 0 do 7
			do{
				wylosowana_grupa = rand() % 8;
			} while (grupyMeczowe[wylosowana_grupa].zapelnienie_grupy > faza_wyboru);

			//do wylosowanej grupy wrzucam dru�yn�, ZWR�CON� przez metod� 'wybierzNajlepszaZeWszystkichKontynentow();
			grupyMeczowe[wylosowana_grupa].druzyny_w_grupie.push_back(wybierzNajlepszaZeWszystkichKontynentow(kontynenty));

			//zwi�kszam zap�enienie grupy, do kt�rej dodano dru�yn�
			grupyMeczowe[wylosowana_grupa].zapelnienie_grupy++;
		}

		//pierwsze wiersze w tabelkach zosta�y wype�nione, zwi�kszamy faza_wyboru
		faza_wyboru++;
	}



	for (int i = 0; i < grupyMeczowe.size(); i++){

		sort(grupyMeczowe[i].druzyny_w_grupie.begin(), grupyMeczowe[i].druzyny_w_grupie.end(), compRanking);

		string d1 = grupyMeczowe[i].druzyny_w_grupie[0].nazwa;
		string d2 = grupyMeczowe[i].druzyny_w_grupie[1].nazwa;
		string d3 = grupyMeczowe[i].druzyny_w_grupie[2].nazwa;
		string d4 = grupyMeczowe[i].druzyny_w_grupie[3].nazwa;

		
		tabelki[i]->setItem(2, 0, new QTableWidgetItem(QString::fromStdString(d1)));
		tabelki[i]->setItem(3, 0, new QTableWidgetItem(QString::fromStdString(d2)));
		tabelki[i]->setItem(4, 0, new QTableWidgetItem(QString::fromStdString(d3)));
		tabelki[i]->setItem(5, 0, new QTableWidgetItem(QString::fromStdString(d4)));


		tabelki[i]->setItem(2, 1, new QTableWidgetItem(QString::number(4)));
		tabelki[i]->setItem(3, 1, new QTableWidgetItem(QString::number(3)));
		tabelki[i]->setItem(4, 1, new QTableWidgetItem(QString::number(2)));
		tabelki[i]->setItem(5, 1, new QTableWidgetItem(QString::number(1)));



		
	}

	
}
