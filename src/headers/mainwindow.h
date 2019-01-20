#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "panstwo.h"
#include "rankingWindow.h"
#include "druzyna.h"
#include "list"
#include "pomocwindow.h"
#include "oknopowitalne.h"
#include "oknoz32druzynami.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	//  konstruktor okna
    explicit MainWindow(QWidget *parent = 0);

	// wczytywanie wszystkich druzyn z UI
    void pobierzButtony();

	void otworzOknoPowitalne();

    int ilosc_wybranych_druzyn = 0;
	int calkowita_ilosc_druzyn = 0;

    ~MainWindow();


	// w QT czwarty typ p�l - private slots, metody podpiete pod guziki
private slots:

// metody kt�re b�d� podpinane pod guziki 
    void handleButton();
    void clearInput();
    void selectRandom();
    void init();
	void losujMiejscaWRankingu();
	void openPomocWindow();

private:

	pomocWindow *  window;
	OknoPowitalne * oknoPowitalne;

    Ui::MainWindow *ui;

	// wektor na przetrzymywanie wska�nik�w do guzik�w 'Dodaj/Usu�' z UI
	// - jak kto� kliknie w guzik zmiana na 'Usu�', zrobi� czerwon� otoczk�, zmiana flagi druzyny na 'gotowa'
    vector<QPushButton*> buttony;

	// wektor na pa�stwa - wszystkie panstwa z UI
    vector<Panstwo> panstwa;



	std::vector<Panstwo*> kontynenty[6];
	vector<Panstwo> wybrane_panstwa;


	// w momencie, kiedy klikam 'rozpocznij symulacje' i warunki sa spelnione (zaznaczone 32 druzyny, poprawne sily)
	// kopiuje 32 'gotowe' druzyny do tej listy - przygotowane druzyny kt�r� przekazujemy do symulacji
	list<Druzyna> przygotowane_druzyny;

	// wska�niki 7 p�l z licznikami kontynent�w. 
	// np. jak klikn� na Polsce 'Dodaj'
	// p�tla sprawdzi jaki Polska ma kontynent i dla takiego kontynentu zinkrementuje licznik w liczniki_kontynentow.
    vector<QLabel *> liczniki_kontynentow;


	// okno symulacji - zwykly obiekt
	// nullptrem, bo za pierwszym razem trzeba je zainicjalizowa� 'new', a po sko�czonej symulacji uruchamiana jest nowa
	// nie tworze nowego obiektu :()

	//rankingwindow *oknoRankingu = nullptr;
	OknoZ32Druzynami *oknoZ32Druzynami = nullptr;

};

#endif // MAINWINDOW_H
