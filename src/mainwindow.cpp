#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "panstwo.h"
#include "biblioteki.h"
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <set>
#include "qmessagebox.h"
#include <ctype.h>
#include "metody.h"
#include "pomocwindow.h"
#include "oknoz32druzynami.h"
/*


                    URUCHOMIENIE PROGRAMU!

*/


// konstruktor MainWindow - czyli okna głównego
// konstruktor odpala się w momencie włączenia programu
// dziedziczy z QMainWindow

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	

	//do losowania sił
    srand(time(NULL));


	// metoda pobiera WSZYSTKIE komponenty z UI 
	// pobiera nazwy panstw, guziki 'Dodaj', pola 'Siła'
	// ORAZ wskaźniki do tych pól z licznikami kontynentów
    pobierzButtony();



	// przy pierwszym uruchomieniu trzeba wylosować MIEJSCA W RANKINGU
	//losujMiejscaWRankingu();


	// funkcja connect w QT podpina komponent (tutaj guziki) do funkcji w kodzie

	//dla wszystkich 4 guzików
    connect(ui->clearButton, SIGNAL (released()), this, SLOT (clearInput()));
    connect(ui->losujButton, SIGNAL (released()), this, SLOT (losujMiejscaWRankingu()));
    connect(ui->symulacjaButton, SIGNAL (released()), this, SLOT (init()));
	connect(ui->selectAll, SIGNAL(released()), this, SLOT(selectRandom()));
	connect(ui->pomocButton, SIGNAL(released()), this, SLOT(openPomocWindow()));
	

    for(int i=0;i<calkowita_ilosc_druzyn;i++){

		// lacze kazdy guziczek Z JEDNĄ, TĄ SAMĄ FUNKCJĄ handleButton().
		// w handleButton sprawdzam sobie funkcją sender() który guzik został kliknięty
        connect(panstwa[i].button, SIGNAL (released()), this, SLOT (handleButton()));
    }



	// program sie dopiero odpala, więc koloruje guziczki na zielono:

    for(auto it = panstwa.begin(); it != panstwa.end(); it++){

		// sciagam palete kolorów z guziczka
        QPalette pal = it->button->palette();
		// wstawiam, że paleta jest teraz zielona
        pal.setColor(QPalette::Button, QColor(Qt::green));
	
        it->button->setAutoFillBackground(true);
		// ustawiam mu tę paletę ponownie
        it->button->setPalette(pal);
		// ODŚWIEŻAM GUZIK NA EKRANIE
        it->button->update();
    }



	// aplikacja zamiera i czeka na odczyt użytkownika który ma do dyspozycji guziczki i metody do nich podpięte.

}

void MainWindow::otworzOknoPowitalne(){
	oknoPowitalne = new OknoPowitalne();
	oknoPowitalne->show();
	oknoPowitalne->setAttribute(Qt::WA_DeleteOnClose);
	oknoPowitalne->raise();
}

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::openPomocWindow(){
	window = new pomocWindow();
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->show();
}


void MainWindow::losujMiejscaWRankingu(){
	

	// pętla do 6
	// set z intami
	// zliczam panstwa
	// generuje liczby
	// shuffle
	// przypisuje popując.
	int liczniki_kontynentow[6];
	for (int i = 0; i < 6; i++) liczniki_kontynentow[i] = 0;
	for (int i = 0; i < 6; i++){
		for (auto it = panstwa.begin(); it != panstwa.end(); it++)
			if (it->kontynent == (i + 1))
				liczniki_kontynentow[i]++;
	}

	for (int i = 0; i < 6; i++){

		set<int> indexes;
		while (indexes.size() < liczniki_kontynentow[i])
			indexes.insert(rand() % liczniki_kontynentow[i] + 1);


		vector<int> out;
		std::copy(indexes.begin(), indexes.end(), std::back_inserter(out));
	
		random_shuffle(out.begin(), out.end());
		
	

		for (auto it = panstwa.begin(); it != panstwa.end(); it++){
			if (it->kontynent == i + 1){
				if (out.size() == 0) break;
				it->miejsceWRankingu = out.back();
				
				out.pop_back();
			}
		}
	}


	for (auto it : panstwa){
		it.rankingTextEdit->setText(QString::number(it.miejsceWRankingu));
	}


	wybrane_panstwa.clear();
	for (auto it = panstwa.begin(); it != panstwa.end(); it++){
		if (it->button->text() == "Usuń")
			wybrane_panstwa.push_back(*it);
	}

	
}



// INIT - czyli metoda rozpoczynająca symulacje
// sprawdza druzyny i jeśli 32 z nich są zaznaczone i 'gotowe' otwiera nowe okno i odpala w nim metode 'rozpocznijSymulacje'
// chwile wczesniej bierze gotowe druzyny, wsadza je do listy 'przygotowane druzyny' i wsadza je do tej metody
void MainWindow::init(){


	oknoZ32Druzynami = new OknoZ32Druzynami();




	// usuwam wszystko z listy 'przygotowane_druzyny' - przydatne tylko jak odpalam symulacje po raz drugi.
    przygotowane_druzyny.clear();
	
	// kopiuje wszystkie 'gotowe' panstwa do listy 'przygotowane_druzyny'
	// klasa Druzyna to klasa juz w symulacji, posiada pola na bramki, szanse itd
	// jak druzyna sie tworzy, przekazuje jej SILE i na jej podstawie ona sobie sama liczy szanse na bramki
    for(auto it = panstwa.begin(); it != panstwa.end(); it++){
        if(it->gotowa){
            przygotowane_druzyny.push_back(Druzyna(it->nazwa, it->kontynent, it->miejsceWRankingu));
        }
    }

	


	// POKAZUJEMY OKNO SYMULACJI
	oknoZ32Druzynami->show();
	oknoZ32Druzynami->rozpisz32Druzyny(przygotowane_druzyny);
	oknoZ32Druzynami->setAttribute(Qt::WA_DeleteOnClose);
	setEnabled(false);
	

	// metoda clearInput czysci guziki (zmienia na zielone Dodaj), zeruje liczniki itd
	clearInput();

}




// pobiera nam wszystkie komponenty 
void MainWindow::pobierzButtony(){

	// do wektora liczniki_kont dodaje wskazniki wszystkich tych pól '0' z licznikami kontynentow, zeby je sobie potem zwiekszac/zmniejszac/czyscic
	liczniki_kontynentow.push_back(ui->liczba_druzyn_1);
	liczniki_kontynentow.push_back(ui->liczba_druzyn_2);
	liczniki_kontynentow.push_back(ui->liczba_druzyn_3);
	liczniki_kontynentow.push_back(ui->liczba_druzyn_4);
	liczniki_kontynentow.push_back(ui->liczba_druzyn_5);
	liczniki_kontynentow.push_back(ui->liczba_druzyn_6);

	panstwa.push_back(Panstwo(1, ui->dodaj1, ui->sila1, ui->nazwa1, 1));
	panstwa.push_back(Panstwo(2, ui->dodaj2, ui->sila2, ui->nazwa2, 6));
	panstwa.push_back(Panstwo(3, ui->dodaj3, ui->sila3, ui->nazwa3, 2));
	panstwa.push_back(Panstwo(4, ui->dodaj4, ui->sila4, ui->nazwa4, 6));
	panstwa.push_back(Panstwo(5, ui->dodaj5, ui->sila5, ui->nazwa5, 6));
	panstwa.push_back(Panstwo(6, ui->dodaj6, ui->sila6, ui->nazwa6, 2));
	panstwa.push_back(Panstwo(7, ui->dodaj7, ui->sila7, ui->nazwa7, 3));
	panstwa.push_back(Panstwo(8, ui->dodaj8, ui->sila8, ui->nazwa8, 3));
	panstwa.push_back(Panstwo(9, ui->dodaj9, ui->sila9, ui->nazwa9, 1));
	panstwa.push_back(Panstwo(10, ui->dodaj10, ui->sila10, ui->nazwa10, 4));

	panstwa.push_back(Panstwo(11, ui->dodaj11, ui->sila11, ui->nazwa11, 1));
	panstwa.push_back(Panstwo(12, ui->dodaj12, ui->sila12, ui->nazwa12, 3));
	panstwa.push_back(Panstwo(13, ui->dodaj13, ui->sila13, ui->nazwa13, 5));
	panstwa.push_back(Panstwo(14, ui->dodaj14, ui->sila14, ui->nazwa14, 6));
	panstwa.push_back(Panstwo(15, ui->dodaj15, ui->sila15, ui->nazwa15, 1));
	panstwa.push_back(Panstwo(16, ui->dodaj16, ui->sila16, ui->nazwa16, 3));
	panstwa.push_back(Panstwo(17, ui->dodaj17, ui->sila17, ui->nazwa17, 1));
	panstwa.push_back(Panstwo(18, ui->dodaj18, ui->sila18, ui->nazwa18, 1));
	panstwa.push_back(Panstwo(19, ui->dodaj19, ui->sila19, ui->nazwa19, 3));
	panstwa.push_back(Panstwo(20, ui->dodaj20, ui->sila20, ui->nazwa20, 6));

	panstwa.push_back(Panstwo(21, ui->dodaj21, ui->sila21, ui->nazwa21, 3));
	panstwa.push_back(Panstwo(22, ui->dodaj22, ui->sila22, ui->nazwa22, 2));
	panstwa.push_back(Panstwo(23, ui->dodaj23, ui->sila23, ui->nazwa23, 3));
	panstwa.push_back(Panstwo(24, ui->dodaj24, ui->sila24, ui->nazwa24, 1));
	panstwa.push_back(Panstwo(25, ui->dodaj25, ui->sila25, ui->nazwa25, 6));
	panstwa.push_back(Panstwo(26, ui->dodaj26, ui->sila26, ui->nazwa26, 4));
	panstwa.push_back(Panstwo(27, ui->dodaj27, ui->sila27, ui->nazwa27, 6));
	panstwa.push_back(Panstwo(28, ui->dodaj28, ui->sila28, ui->nazwa28, 2));
	panstwa.push_back(Panstwo(29, ui->dodaj29, ui->sila29, ui->nazwa29, 4));
	panstwa.push_back(Panstwo(30, ui->dodaj30, ui->sila30, ui->nazwa30, 1));

	panstwa.push_back(Panstwo(31, ui->dodaj31, ui->sila31, ui->nazwa31, 3));
	panstwa.push_back(Panstwo(32, ui->dodaj32, ui->sila32, ui->nazwa32, 6));
	panstwa.push_back(Panstwo(33, ui->dodaj33, ui->sila33, ui->nazwa33, 2));
	panstwa.push_back(Panstwo(34, ui->dodaj34, ui->sila34, ui->nazwa34, 2));
	panstwa.push_back(Panstwo(35, ui->dodaj35, ui->sila35, ui->nazwa35, 4));
	panstwa.push_back(Panstwo(36, ui->dodaj36, ui->sila36, ui->nazwa36, 1));
	panstwa.push_back(Panstwo(37, ui->dodaj37, ui->sila37, ui->nazwa37, 6));
	panstwa.push_back(Panstwo(38, ui->dodaj38, ui->sila38, ui->nazwa38, 4));
	panstwa.push_back(Panstwo(39, ui->dodaj39, ui->sila39, ui->nazwa39, 6));
	panstwa.push_back(Panstwo(40, ui->dodaj40, ui->sila40, ui->nazwa40, 2));

	panstwa.push_back(Panstwo(41, ui->dodaj41, ui->sila41, ui->nazwa41, 6));
	panstwa.push_back(Panstwo(42, ui->dodaj42, ui->sila42, ui->nazwa42, 6));
	panstwa.push_back(Panstwo(43, ui->dodaj43, ui->sila43, ui->nazwa43, 6));
	panstwa.push_back(Panstwo(44, ui->dodaj44, ui->sila44, ui->nazwa44, 2));
	panstwa.push_back(Panstwo(45, ui->dodaj45, ui->sila45, ui->nazwa45, 3));
	panstwa.push_back(Panstwo(46, ui->dodaj46, ui->sila46, ui->nazwa46, 3));
	panstwa.push_back(Panstwo(47, ui->dodaj47, ui->sila47, ui->nazwa47, 2));
	panstwa.push_back(Panstwo(48, ui->dodaj48, ui->sila48, ui->nazwa48, 2));
	panstwa.push_back(Panstwo(49, ui->dodaj49, ui->sila49, ui->nazwa49, 4));
	panstwa.push_back(Panstwo(50, ui->dodaj50, ui->sila50, ui->nazwa50, 2));

	panstwa.push_back(Panstwo(51, ui->dodaj51, ui->sila51, ui->nazwa51, 6));
	panstwa.push_back(Panstwo(52, ui->dodaj52, ui->sila52, ui->nazwa52, 2));
	panstwa.push_back(Panstwo(53, ui->dodaj53, ui->sila53, ui->nazwa53, 5));
	panstwa.push_back(Panstwo(54, ui->dodaj54, ui->sila54, ui->nazwa54, 1));
	panstwa.push_back(Panstwo(55, ui->dodaj55, ui->sila55, ui->nazwa55, 6));
	panstwa.push_back(Panstwo(56, ui->dodaj56, ui->sila56, ui->nazwa56, 6));
	panstwa.push_back(Panstwo(57, ui->dodaj57, ui->sila57, ui->nazwa57, 2));
	panstwa.push_back(Panstwo(58, ui->dodaj58, ui->sila58, ui->nazwa58, 2));
	panstwa.push_back(Panstwo(59, ui->dodaj59, ui->sila59, ui->nazwa59, 2));
	panstwa.push_back(Panstwo(60, ui->dodaj60, ui->sila60, ui->nazwa60, 6));

	panstwa.push_back(Panstwo(61, ui->dodaj61, ui->sila61, ui->nazwa61, 3));
	panstwa.push_back(Panstwo(62, ui->dodaj62, ui->sila62, ui->nazwa62, 1));
	panstwa.push_back(Panstwo(63, ui->dodaj63, ui->sila63, ui->nazwa63, 5));
	panstwa.push_back(Panstwo(64, ui->dodaj64, ui->sila64, ui->nazwa64, 4));
	panstwa.push_back(Panstwo(65, ui->dodaj65, ui->sila65, ui->nazwa65, 3));
	panstwa.push_back(Panstwo(66, ui->dodaj66, ui->sila66, ui->nazwa66, 2));
	panstwa.push_back(Panstwo(67, ui->dodaj67, ui->sila67, ui->nazwa67, 2));
	panstwa.push_back(Panstwo(68, ui->dodaj68, ui->sila68, ui->nazwa68, 2));
	panstwa.push_back(Panstwo(69, ui->dodaj69, ui->sila69, ui->nazwa69, 3));
	panstwa.push_back(Panstwo(70, ui->dodaj70, ui->sila70, ui->nazwa70, 6));

	panstwa.push_back(Panstwo(71, ui->dodaj71, ui->sila71, ui->nazwa71, 6));
	panstwa.push_back(Panstwo(72, ui->dodaj72, ui->sila72, ui->nazwa72, 3));
	panstwa.push_back(Panstwo(73, ui->dodaj73, ui->sila73, ui->nazwa73, 1));
	panstwa.push_back(Panstwo(74, ui->dodaj74, ui->sila74, ui->nazwa74, 1));
	panstwa.push_back(Panstwo(75, ui->dodaj75, ui->sila75, ui->nazwa75, 1));
	panstwa.push_back(Panstwo(76, ui->dodaj76, ui->sila76, ui->nazwa76, 1));
	panstwa.push_back(Panstwo(77, ui->dodaj77, ui->sila77, ui->nazwa77, 1));
	panstwa.push_back(Panstwo(78, ui->dodaj78, ui->sila78, ui->nazwa78, 6));
	panstwa.push_back(Panstwo(79, ui->dodaj79, ui->sila79, ui->nazwa79, 6));
	panstwa.push_back(Panstwo(80, ui->dodaj80, ui->sila80, ui->nazwa80, 6));

	panstwa.push_back(Panstwo(81, ui->dodaj81, ui->sila81, ui->nazwa81, 1));
	panstwa.push_back(Panstwo(82, ui->dodaj82, ui->sila82, ui->nazwa82, 3));
	panstwa.push_back(Panstwo(83, ui->dodaj83, ui->sila83, ui->nazwa83, 1));
	panstwa.push_back(Panstwo(84, ui->dodaj84, ui->sila84, ui->nazwa84, 1));
	panstwa.push_back(Panstwo(85, ui->dodaj85, ui->sila85, ui->nazwa85, 1));
	panstwa.push_back(Panstwo(86, ui->dodaj86, ui->sila86, ui->nazwa86, 3));
	panstwa.push_back(Panstwo(87, ui->dodaj87, ui->sila87, ui->nazwa87, 1));
	panstwa.push_back(Panstwo(88, ui->dodaj88, ui->sila88, ui->nazwa88, 2));
	panstwa.push_back(Panstwo(89, ui->dodaj89, ui->sila89, ui->nazwa89, 3));
	panstwa.push_back(Panstwo(90, ui->dodaj90, ui->sila90, ui->nazwa90, 1));

	panstwa.push_back(Panstwo(91, ui->dodaj91, ui->sila91, ui->nazwa91, 1));
	panstwa.push_back(Panstwo(92, ui->dodaj92, ui->sila92, ui->nazwa92, 2));
	panstwa.push_back(Panstwo(93, ui->dodaj93, ui->sila93, ui->nazwa93, 1));
	panstwa.push_back(Panstwo(94, ui->dodaj94, ui->sila94, ui->nazwa94, 4));
	panstwa.push_back(Panstwo(95, ui->dodaj95, ui->sila95, ui->nazwa95, 2));
	panstwa.push_back(Panstwo(96, ui->dodaj96, ui->sila96, ui->nazwa96, 2));
	panstwa.push_back(Panstwo(97, ui->dodaj97, ui->sila97, ui->nazwa97, 1));
	panstwa.push_back(Panstwo(98, ui->dodaj98, ui->sila98, ui->nazwa98, 1));
	panstwa.push_back(Panstwo(99, ui->dodaj99, ui->sila99, ui->nazwa99, 3));
	panstwa.push_back(Panstwo(100, ui->dodaj100, ui->sila100, ui->nazwa100, 3));

	panstwa.push_back(Panstwo(101, ui->dodaj101, ui->sila101, ui->nazwa101, 1));
	panstwa.push_back(Panstwo(102, ui->dodaj102, ui->sila102, ui->nazwa102, 1));
	panstwa.push_back(Panstwo(103, ui->dodaj103, ui->sila103, ui->nazwa103, 2));
	panstwa.push_back(Panstwo(104, ui->dodaj104, ui->sila104, ui->nazwa104, 1));
	panstwa.push_back(Panstwo(105, ui->dodaj105, ui->sila105, ui->nazwa105, 2));
	panstwa.push_back(Panstwo(106, ui->dodaj106, ui->sila106, ui->nazwa106, 2));
	panstwa.push_back(Panstwo(107, ui->dodaj107, ui->sila107, ui->nazwa107, 6));
	panstwa.push_back(Panstwo(108, ui->dodaj108, ui->sila108, ui->nazwa108, 6));
	panstwa.push_back(Panstwo(109, ui->dodaj109, ui->sila109, ui->nazwa109, 6));
	panstwa.push_back(Panstwo(110, ui->dodaj110, ui->sila110, ui->nazwa110, 6));

	panstwa.push_back(Panstwo(111, ui->dodaj111, ui->sila111, ui->nazwa111, 6));
	panstwa.push_back(Panstwo(112, ui->dodaj112, ui->sila112, ui->nazwa112, 2));
	panstwa.push_back(Panstwo(113, ui->dodaj113, ui->sila113, ui->nazwa113, 1));
	panstwa.push_back(Panstwo(114, ui->dodaj114, ui->sila114, ui->nazwa114, 2));
	panstwa.push_back(Panstwo(115, ui->dodaj115, ui->sila115, ui->nazwa115, 1));
	panstwa.push_back(Panstwo(116, ui->dodaj116, ui->sila116, ui->nazwa116, 1));
	panstwa.push_back(Panstwo(117, ui->dodaj117, ui->sila117, ui->nazwa117, 2));
	panstwa.push_back(Panstwo(118, ui->dodaj118, ui->sila118, ui->nazwa118, 6));
	panstwa.push_back(Panstwo(119, ui->dodaj119, ui->sila119, ui->nazwa119, 2));
	panstwa.push_back(Panstwo(120, ui->dodaj120, ui->sila120, ui->nazwa120, 2));

	panstwa.push_back(Panstwo(121, ui->dodaj121, ui->sila121, ui->nazwa121, 2));
	panstwa.push_back(Panstwo(122, ui->dodaj122, ui->sila122, ui->nazwa122, 3));
	panstwa.push_back(Panstwo(123, ui->dodaj123, ui->sila123, ui->nazwa123, 1));
	panstwa.push_back(Panstwo(124, ui->dodaj124, ui->sila124, ui->nazwa124, 6));
	panstwa.push_back(Panstwo(125, ui->dodaj125, ui->sila125, ui->nazwa125, 1));
	panstwa.push_back(Panstwo(126, ui->dodaj126, ui->sila126, ui->nazwa126, 3));
	panstwa.push_back(Panstwo(127, ui->dodaj127, ui->sila127, ui->nazwa127, 2));
	panstwa.push_back(Panstwo(128, ui->dodaj128, ui->sila128, ui->nazwa128, 2));
	panstwa.push_back(Panstwo(129, ui->dodaj129, ui->sila129, ui->nazwa129, 1));
	panstwa.push_back(Panstwo(130, ui->dodaj130, ui->sila130, ui->nazwa130, 6));

	panstwa.push_back(Panstwo(131, ui->dodaj131, ui->sila131, ui->nazwa131, 2));
	panstwa.push_back(Panstwo(132, ui->dodaj132, ui->sila132, ui->nazwa132, 2));
	panstwa.push_back(Panstwo(133, ui->dodaj133, ui->sila133, ui->nazwa133, 2));
	panstwa.push_back(Panstwo(134, ui->dodaj134, ui->sila134, ui->nazwa134, 6));
	panstwa.push_back(Panstwo(135, ui->dodaj135, ui->sila135, ui->nazwa135, 5));
	panstwa.push_back(Panstwo(136, ui->dodaj136, ui->sila136, ui->nazwa136, 5));
	panstwa.push_back(Panstwo(137, ui->dodaj137, ui->sila137, ui->nazwa137, 1));
	panstwa.push_back(Panstwo(138, ui->dodaj138, ui->sila138, ui->nazwa138, 1));
	panstwa.push_back(Panstwo(139, ui->dodaj139, ui->sila139, ui->nazwa139, 1));
	panstwa.push_back(Panstwo(140, ui->dodaj140, ui->sila140, ui->nazwa140, 3));

	panstwa.push_back(Panstwo(141, ui->dodaj141, ui->sila141, ui->nazwa141, 5));
	panstwa.push_back(Panstwo(142, ui->dodaj142, ui->sila142, ui->nazwa142, 4));
	panstwa.push_back(Panstwo(143, ui->dodaj143, ui->sila143, ui->nazwa143, 4));
	panstwa.push_back(Panstwo(144, ui->dodaj144, ui->sila144, ui->nazwa144, 6));
	panstwa.push_back(Panstwo(145, ui->dodaj145, ui->sila145, ui->nazwa145, 2));
	panstwa.push_back(Panstwo(146, ui->dodaj146, ui->sila146, ui->nazwa146, 3));
	panstwa.push_back(Panstwo(147, ui->dodaj147, ui->sila147, ui->nazwa147, 6));
	panstwa.push_back(Panstwo(148, ui->dodaj148, ui->sila148, ui->nazwa148, 2));
	panstwa.push_back(Panstwo(149, ui->dodaj149, ui->sila149, ui->nazwa149, 2));
	panstwa.push_back(Panstwo(150, ui->dodaj150, ui->sila150, ui->nazwa150, 6));

	panstwa.push_back(Panstwo(151, ui->dodaj151, ui->sila151, ui->nazwa151, 6));
	panstwa.push_back(Panstwo(152, ui->dodaj152, ui->sila152, ui->nazwa152, 2));
	panstwa.push_back(Panstwo(153, ui->dodaj153, ui->sila153, ui->nazwa153, 3));
	panstwa.push_back(Panstwo(154, ui->dodaj154, ui->sila154, ui->nazwa154, 3));
	panstwa.push_back(Panstwo(155, ui->dodaj155, ui->sila155, ui->nazwa155, 3));
	panstwa.push_back(Panstwo(156, ui->dodaj156, ui->sila156, ui->nazwa156, 3));
	panstwa.push_back(Panstwo(157, ui->dodaj157, ui->sila157, ui->nazwa157, 5));
	panstwa.push_back(Panstwo(158, ui->dodaj158, ui->sila158, ui->nazwa158, 5));
	panstwa.push_back(Panstwo(159, ui->dodaj159, ui->sila159, ui->nazwa159, 6));
	panstwa.push_back(Panstwo(160, ui->dodaj160, ui->sila160, ui->nazwa160, 2));

	panstwa.push_back(Panstwo(161, ui->dodaj161, ui->sila161, ui->nazwa161, 6));
	panstwa.push_back(Panstwo(162, ui->dodaj162, ui->sila162, ui->nazwa162, 2));
	panstwa.push_back(Panstwo(163, ui->dodaj163, ui->sila163, ui->nazwa163, 2));
	panstwa.push_back(Panstwo(164, ui->dodaj164, ui->sila164, ui->nazwa164, 1));
	panstwa.push_back(Panstwo(165, ui->dodaj165, ui->sila165, ui->nazwa165, 6));
	panstwa.push_back(Panstwo(166, ui->dodaj166, ui->sila166, ui->nazwa166, 6));
	panstwa.push_back(Panstwo(167, ui->dodaj167, ui->sila167, ui->nazwa167, 2));
	panstwa.push_back(Panstwo(168, ui->dodaj168, ui->sila168, ui->nazwa168, 1));
	panstwa.push_back(Panstwo(169, ui->dodaj169, ui->sila169, ui->nazwa169, 3));
	panstwa.push_back(Panstwo(170, ui->dodaj170, ui->sila170, ui->nazwa170, 2));

	panstwa.push_back(Panstwo(171, ui->dodaj171, ui->sila171, ui->nazwa171, 2));
	panstwa.push_back(Panstwo(172, ui->dodaj172, ui->sila172, ui->nazwa172, 2));
	panstwa.push_back(Panstwo(173, ui->dodaj173, ui->sila173, ui->nazwa173, 4));
	panstwa.push_back(Panstwo(174, ui->dodaj174, ui->sila174, ui->nazwa174, 1));
	panstwa.push_back(Panstwo(175, ui->dodaj175, ui->sila175, ui->nazwa175, 6));
	panstwa.push_back(Panstwo(176, ui->dodaj176, ui->sila176, ui->nazwa176, 6));
	panstwa.push_back(Panstwo(177, ui->dodaj177, ui->sila177, ui->nazwa177, 6));
	panstwa.push_back(Panstwo(178, ui->dodaj178, ui->sila178, ui->nazwa178, 1));
	panstwa.push_back(Panstwo(179, ui->dodaj179, ui->sila179, ui->nazwa179, 5));
	panstwa.push_back(Panstwo(180, ui->dodaj180, ui->sila180, ui->nazwa180, 1));

	panstwa.push_back(Panstwo(181, ui->dodaj181, ui->sila181, ui->nazwa181, 1));
	panstwa.push_back(Panstwo(182, ui->dodaj182, ui->sila182, ui->nazwa182, 2));
	panstwa.push_back(Panstwo(183, ui->dodaj183, ui->sila183, ui->nazwa183, 1));
	panstwa.push_back(Panstwo(184, ui->dodaj184, ui->sila184, ui->nazwa184, 2));
	panstwa.push_back(Panstwo(185, ui->dodaj185, ui->sila185, ui->nazwa185, 5));
	panstwa.push_back(Panstwo(186, ui->dodaj186, ui->sila186, ui->nazwa186, 3));
	panstwa.push_back(Panstwo(187, ui->dodaj187, ui->sila187, ui->nazwa187, 2));
	panstwa.push_back(Panstwo(188, ui->dodaj188, ui->sila188, ui->nazwa188, 1));
	panstwa.push_back(Panstwo(189, ui->dodaj189, ui->sila189, ui->nazwa189, 1));
	panstwa.push_back(Panstwo(190, ui->dodaj190, ui->sila190, ui->nazwa190, 3));

	panstwa.push_back(Panstwo(191, ui->dodaj191, ui->sila191, ui->nazwa191, 2));
	panstwa.push_back(Panstwo(192, ui->dodaj192, ui->sila192, ui->nazwa192, 6));
	panstwa.push_back(Panstwo(193, ui->dodaj193, ui->sila193, ui->nazwa193, 4));
	panstwa.push_back(Panstwo(194, ui->dodaj194, ui->sila194, ui->nazwa194, 1));
	panstwa.push_back(Panstwo(195, ui->dodaj195, ui->sila195, ui->nazwa195, 6));
	panstwa.push_back(Panstwo(196, ui->dodaj196, ui->sila196, ui->nazwa196, 4));
	panstwa.push_back(Panstwo(197, ui->dodaj197, ui->sila197, ui->nazwa197, 6));
	panstwa.push_back(Panstwo(198, ui->dodaj198, ui->sila198, ui->nazwa198, 1));
	panstwa.push_back(Panstwo(199, ui->dodaj199, ui->sila199, ui->nazwa199, 6));
	panstwa.push_back(Panstwo(200, ui->dodaj200, ui->sila200, ui->nazwa200, 2));

	panstwa.push_back(Panstwo(201, ui->dodaj201, ui->sila201, ui->nazwa201, 5));
	panstwa.push_back(Panstwo(202, ui->dodaj202, ui->sila202, ui->nazwa202, 3));
	panstwa.push_back(Panstwo(203, ui->dodaj203, ui->sila203, ui->nazwa203, 6));
	panstwa.push_back(Panstwo(204, ui->dodaj204, ui->sila204, ui->nazwa204, 5));
	panstwa.push_back(Panstwo(205, ui->dodaj205, ui->sila205, ui->nazwa205, 2));
	panstwa.push_back(Panstwo(206, ui->dodaj206, ui->sila206, ui->nazwa206, 5));
	panstwa.push_back(Panstwo(207, ui->dodaj207, ui->sila207, ui->nazwa207, 2));
	panstwa.push_back(Panstwo(208, ui->dodaj208, ui->sila208, ui->nazwa208, 2));
	panstwa.push_back(Panstwo(209, ui->dodaj209, ui->sila209, ui->nazwa209, 1));

	
	
	// zmienna która nam odpowiada za ilosc wczytanych druzyn.
	calkowita_ilosc_druzyn = panstwa.size();
}


bool comparator(int i, int j) { return (i<j); }


void showMessage(string title, string message){
	QMessageBox Msgbox;
	Msgbox.setWindowTitle(QString::fromStdString(title));
	Msgbox.setText(QString::fromStdString(message));
	Msgbox.exec();

}


bool is_number(const std::string &s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}


void MainWindow::handleButton()
{
	// iteruje po panstwach i sprawdzam, czy guzik który został kliknięty do ten w kolejnym panstwie
	for (auto it = panstwa.begin(); it != panstwa.end(); it++){

		// METODA sender() zwraca guzik, który został kliknięty
		// jeśli sender() czyli aktualnie klikniety guzik == guzikowi danego panstwa 
		if (sender() == it->button){


			// dwa przypadki, albo guzik ma na sobie 'Dodaj', albo ma na sobie 'Usun'.
			if (it->button->text() == "Dodaj"){
				

				// pobieram wartosc z pola 'Ranking' danej druzyny
				string value = it->rankingTextEdit->toPlainText().toUtf8().constData();
				
				// jeśli string nie jest liczba
				if (!is_number(value)){
					showMessage("Błąd", "Proszę podać prawidłową wartość numeryczną w polu 'Miejsce w rankingu'");
					return;
				}

				// rzutuje na inta
				int liczba = stoi(value);
				

				// warunek, czy liczba jest większa od zera i mniejsza o maksymalnej
				// maksymalna liczba to ilość druzyn na danym kontynencie 


				// obl maksymalne miejsce

				int maksymalne_miejsce_w_rankingu = 0;

				// iteruje po wszystkich państwach
				for (auto it2 : panstwa){
					// jeśli dane państwo ma taki sam kontynent jak wybrane, to zwiększamy licznik
					if (it2.kontynent == it->kontynent)
						maksymalne_miejsce_w_rankingu++;
				}


				// spr czy liczba jest < lub >
				if (liczba < 1 || liczba > maksymalne_miejsce_w_rankingu){
					string error = "Proszę podać prawidłową wartość numeryczną z zakresu 1 - " + to_string(maksymalne_miejsce_w_rankingu);
					showMessage("Błąd", error);
					return;
				}


				// miejsce przeszło podstawowe testy, terazspr, czy inna 'Dodana' druzyna nie ma już wpisanego tego miejsca

				// od razu nadpisuje tej druzynie to miejsce
				it->miejsceWRankingu = it->rankingTextEdit->toPlainText().toInt();


				// i lece po liście 'wybranych rankingów'
				bool zawiera = false;
				Panstwo duplikat;
				for (auto it2 : wybrane_panstwa){
					// jeśli druzyna jest na tym samym kontynencie i ma to samo miejsce w rankingu ustawiam ją, że jest DUPLIKATEM żeby potem wypisać userowi, która to drużyna ma już dane miejsce
					if (it->kontynent == it2.kontynent && it->miejsceWRankingu == it2.miejsceWRankingu){
						zawiera = true;
						duplikat = it2;
					}
				}

				// był duplikat, to trzeba teraz znaleźć wszystkie wolne indeksy, które user może sobie ustawić i mu je wypisać razem z duplikatem
				if (zawiera){

					// z listy 'wybranych rankingów' wybieram wszystkie zajęte rankingi danego kontynentu
					set<int> wszystkie_miejsca_z_kontynentu;

					// tutaj na końcu wpisze wszystkie 'wolne miejsca' żeby je wypisać userowi
					vector<int> wolne_indeksy;
					

					// najpierw trzeba policzyć ile druzyn jest na kontynencie naszego 'Duplikatu'
					int ilosc_druzyn_na_kontynencie = 0;
					for (auto it2 : panstwa){
						if (it2.kontynent == duplikat.kontynent)
							ilosc_druzyn_na_kontynencie++;
					}

					/*
						Zakladam, że lista wybranych drużyn ma w sobie 3 druzyny z Europy z rankingami 1, 4, 8
						Załóżmy, że Europa ma 10 drużyn łącznie
					
						Więc trzeba wypisać użytkownikowi wszystkie POZOSTAŁE LICZBY czyli:
						2,3,5,6,7,9,10
					
					*/

					// iteruje po wybranych państwach i jeśli kontynent == kontynent duplikatu, dodaje jego miejsce w rankingu do Setu
					for (auto it2 : wybrane_panstwa){
						if (it2.kontynent == duplikat.kontynent){
							wszystkie_miejsca_z_kontynentu.insert(it2.miejsceWRankingu);
						}
					}

					/*
						Czyli lista wybranych zawierała 3 drużyny z Europy z miejscami kolejno 1, 4, 8
						Czyli Set posiada teraz 3 wartości: 1, 4, 8
					*/



					/*
						Wiem ile drużyn jest na danym kontynencie i  jakie miejsca są już zajęte, więc teraz trzeba pobrać te, które nie są zajęte.

						Pętla od 0 do ilość_druzyn_na_kont
						I spr, czy set z zajętymi miejscami (ten 1,4,8) zawiera i+1, czyli kolejno 1,2,3,4,5,6,7 aż do ilosc_druzyn_na_kontynencie.
						
						Jeśli NIE ZAWIERA, to znaczy, że miejsce i+1 jest wolne i dodaje i+1 do wolne_indeksy
						Jeśli zawiera, nic sie nie dzieje
					*/
					for (int i = 0; i < ilosc_druzyn_na_kontynencie; i++){
						if (std::find(wszystkie_miejsca_z_kontynentu.begin(), wszystkie_miejsca_z_kontynentu.end(), i + 1) == wszystkie_miejsca_z_kontynentu.end())
							wolne_indeksy.push_back(i + 1);
					}

					// wszystkie wolne indeksy, więc je teraz łącze w 1 stringa
					string liczby;
					for (int i = 0; i < wolne_indeksy.size(); i++){
						// po każdej liczbie dodaje przecinek i spacje
						liczby += to_string(wolne_indeksy[i]) + ", ";
					}


					// więc na końcu stringa tez jest przecinek i spacja, więc usuwam 2 chary 
					if (liczby.size() > 2){
						liczby.pop_back();
						liczby.pop_back();
					}

					// wyświetlam okno
					QMessageBox Msgbox;
					Msgbox.setWindowTitle("Nie można dodać drużyny");
					// i wypisuje info oraz nazwę duplikatu (tej, która już ma podane miejsce w rankingu) i całą listę 'wolnych' miejsc, które można sobie wybrać
					string out = "Następująca drużyna posiada już dane miejsce w rankingu: " + duplikat.nazwa + "\nProszę wybrać inną drużynę.\n\nDostępne miejsca: " + liczby;
					Msgbox.setText(QString::fromStdString(out));
					Msgbox.exec();

					// nie dodaje danej drużyny, bo to duplikat, return całą metodę
					return;
				}
				else{
					// JEŚLI wybrana drużyna nie zawiera się w 'wybranych państwach' to ją tam dodaje
					wybrane_panstwa.push_back(*it);
		
				}

				// wzkaźniki do licznikow kontynentów są w wektorze liczniki_kontynentów
				// państwo na którym właśnie jestem ma w sobie ID swojego kontynentu
				// więc mozna sie odwolac do wektora 'liczniki_kontynentow' po tym ID i dostac odpowiadajacy temu panstwu licznik

				// sciagam wartosc ktora tam jest do jakiegos inta 'temp'
				int temp = (liczniki_kontynentow[(it->kontynent) - 1]->text()).toInt();
				temp++;
				// i ustawiam tekst w liczniku tego kontynentu na temp (od razu go zwiększając).
				// konwertuje inta na QStringa metodą number z klasy 

				liczniki_kontynentow[(it->kontynent) - 1]->setText(QString::number(temp));

				// jest też licznik RAZEM WYBRANYCH (ile łącznie)
				//  też sciagam i dodajac zwiększam
				int razem = ui->liczba_druzyn_razem->text().toInt();
				razem++;
				ui->liczba_druzyn_razem->setText(QString::number(razem));


				// ustawiam guzikowi kolor na czerwony
				QPalette pal = it->button->palette();
				pal.setColor(QPalette::Button, QColor(Qt::red));
				it->button->setAutoFillBackground(true);
				it->button->setPalette(pal);
				it->button->update();


				it->button->setText("Usuń");


				// blokuje bloczek 'Siła' - zmieniam na szaro, bo druzyna jest 'gotowa' - nie mozna jej zmienic sily.
				it->rankingTextEdit->setEnabled(false);

				// spr, czy to, co jest wpisane w sile jest liczbą 1-99

				// druzyna teraz juz spelnia wymagania, zaznaczam 'gotowa'.
				it->gotowa = true;

				// zwiększam ilosc wybranych druzyn.
				ilosc_wybranych_druzyn++;


				// SPR
				// jeśli ilosc jest rowna 32 - mozna odblokowac guzik 'Rozpocznij Symulacje'
				if (ilosc_wybranych_druzyn == 32){
					ui->symulacjaButton->setEnabled(true);
				}
				// jeśli ilosc jest RÓŻNA - blokuje guzik - drużyn jest mniej albo więcej!
				else{
					ui->symulacjaButton->setEnabled(false);
				}



			}
			else{
				
				for (auto it2 = wybrane_panstwa.begin(); it2 != wybrane_panstwa.end();) {
					if (it2->nazwa == it->nazwa) {
						it2 = wybrane_panstwa.erase(it2);
						break;
					}
					else {
						++it2;
					}
				}

				// PRZYPADEK, JAK GUZIK MA NAPIS 'USUŃ' - czyli usuwam ją z 'gotowych'.

				// sciagam liczbe z liczników kontynentów i wsadzam 'zmniejszoną'.

				int temp = (liczniki_kontynentow[(it->kontynent) - 1]->text()).toInt();
				temp--;
				liczniki_kontynentow[(it->kontynent) - 1]->setText(QString::number(temp));


				// liczbe kontynentów łącznie też zmniejszam
				int razem = ui->liczba_druzyn_razem->text().toInt();
				razem--;
				ui->liczba_druzyn_razem->setText(QString::number(razem));

				// zmieniam kolorek ponownie na zielony
				QPalette pal = it->button->palette();
				pal.setColor(QPalette::Button, QColor(Qt::green));
				it->button->setAutoFillBackground(true);
				it->button->setPalette(pal);
				it->button->update();

				// napis na dodaj i odblokowuje pole 'Siła'
				it->button->setText("Dodaj");
				it->rankingTextEdit->setEnabled(true);

				//  niegotowa
				it->gotowa = false;

				// zmniejszam ilosc druzyn
				ilosc_wybranych_druzyn--;

				// sprawdzam, czy po odznaczeniu druzyny ilosc rowna sie 32
				// jak tak - odblokowuje symulacje, jak nie - nie.
				if (ilosc_wybranych_druzyn == 32){
					ui->symulacjaButton->setEnabled(true);
				}
				else{
					ui->symulacjaButton->setEnabled(false);
				}
			}
		}
	}
}





// ta metoda zaznacza losowe 32 druzyny

void MainWindow::selectRandom(){

	losujMiejscaWRankingu();

	ui->liczba_druzyn_razem->setText(QString::number(32));


	// będe losować 32 druzyny
	// dlatego też potrzebny jest set


	set<int> wylosowane_druzyny;

	ilosc_wybranych_druzyn = 0;


	// czyszcze input
	// czyszcze, bo losujemy 32 druzyny. Nie mozna miec zadnej wczesniej zaznaczonej

	for (auto it = panstwa.begin(); it != panstwa.end(); it++){
		liczniki_kontynentow[(it->kontynent) - 1]->setText(QString::number(0));
		it->gotowa = false;

		QPalette pal = it->button->palette();
		pal.setColor(QPalette::Button, QColor(Qt::green));
		it->button->setAutoFillBackground(true);
		it->button->setPalette(pal);
		it->button->update();
		it->button->setText("Dodaj");

		it->rankingTextEdit->setEnabled(true);
	}





	
	// losowanie numerkow
	// Dopóki wielkość seta nie będzie równa 32, losuje do niego nową wartość i probuje wstawić
	// losuje z zakresu 1...całkowita ilość druzyn

	while (wylosowane_druzyny.size() < 32){
		wylosowane_druzyny.insert(rand() % calkowita_ilosc_druzyn + 1);
	}

	// kopiuje numerki do tablicy
	int wylosowane[32];
	copy(wylosowane_druzyny.begin(), wylosowane_druzyny.end(), wylosowane);



	// każda druzyna w 'panstwach' ma swoje ID, 1,2,3,4,5,6,7...calkowita_ilosc
	// lece po panstwach i porownuje je z kolejnymi elementami wylosowanych.
	// jeśli ID panstwa zgodzi sie z 'Wylosowanym' - zaznaczam to panstwo - tak jakby kliknac 'dodaj'.

	// pierwsza pętla leci po państwach
	for (auto it = panstwa.begin(); it != panstwa.end(); it++){

		// ta pętla leci po wylosowanych liczbach
		for (int k = 0; k < 32; k++){

			// jeśli dane panstwo zostało wylosowane
			if (wylosowane[k] == it->ID){

				// KLASYCZNE DODANIE PANSTWA, sprawdzenie warunków i tak dalej. Dokladnie tak, jakby kliknac 'Dodaj'.
				int temp = (liczniki_kontynentow[(it->kontynent) - 1]->text()).toInt();
				temp++;
				liczniki_kontynentow[(it->kontynent) - 1]->setText(QString::number(temp));

				QPalette pal = it->button->palette();
				pal.setColor(QPalette::Button, QColor(Qt::red));
				it->button->setAutoFillBackground(true);
				it->button->setPalette(pal);
				it->button->update();
				it->button->setText("Usuń");

				it->rankingTextEdit->setEnabled(false);


				it->gotowa = true;
				ilosc_wybranych_druzyn++;
				wybrane_panstwa.push_back(*it);
				if (ilosc_wybranych_druzyn == 32)
					ui->symulacjaButton->setEnabled(true);
				else ui->symulacjaButton->setEnabled(false);



				
				// znalezione panstwo, wiec dalej na 100% nie ma juz takiego panstwa, break petli wew i spr
				// kolejny numerek z 'Wylosowanych'.
				break;
			}
		}
	}
}



// guzik 'czyszczący wprowadzone dane'.
void MainWindow::clearInput(){

	wybrane_panstwa.clear();
	// ustawiam liczbe 'wybranych łącznie' na 0.
	ui->liczba_druzyn_razem->setText(QString::number(0));

	// WSZYSTKIM PANSTWOM I ODPOWIADAJACYM IM LICZNIKOM KONTYNENTOW
	// zmieniam wartosci


    for(auto it = panstwa.begin(); it != panstwa.end(); it++){

		it->rankingTextEdit->setText("");

		// wszystkie liczniki zeruje
        liczniki_kontynentow[(it->kontynent)-1]->setText(QString::number(0));


		// wszystkie kolorki ustawiam na zielony
        QPalette pal = it->button->palette();
        pal.setColor(QPalette::Button, QColor(Qt::green));
        it->button->setAutoFillBackground(true);
        it->button->setPalette(pal);
        it->button->update();

		// guziki na Dodaj
        it->button->setText("Dodaj");
		// brak gotowosci
        it->gotowa = false;
		// odblokowuje guziki 'Sila'
        it->rankingTextEdit->setEnabled(true);
    }


	// blokuje guzik 'Rozpocznij Symulacje'
	ui->symulacjaButton->setEnabled(false);

	// zmieniam ilosc wybranych druzyn na 0.
    ilosc_wybranych_druzyn = 0;


	// wszystko wyczyszczone
}

