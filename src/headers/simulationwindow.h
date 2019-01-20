#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H
#include <biblioteki.h>
#include <QDialog>
#include "druzyna.h"
#include "grupameczowa.h"
#include "kontynent.h"
#include <QTableWidget>
namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationWindow(QWidget *parent = 0);
    ~SimulationWindow();

	// wektor na tabelki grupowe
	// ka¿da tabelka to wskaŸnik, tak jak guziczki i tak dalej
    std::vector<QTableWidget*> tabelki;

	// 4 osobne tabelki, nazwy mówi¹ same za siebie
    QTableWidget* przedcwiercfinalTable;
    QTableWidget* cwiercfinalTable;
    QTableWidget* polfinalTable;
    QTableWidget* finalTable;

	// tu sobie przechowamy wskaŸniki, ¿eby je potem wyczyœciæ, nieistotne
	vector<QTableWidgetItem*> wskazniki;

	// metoda rozpocznij symulacje - to do niej przekazujemy liste 32 druzyn z okna glownego
	// ta metoda to taki jakby main z poprzedniego programu, robi WSZYSTKO.
    void rozpocznijSymulacje(list<Druzyna> zaladowane);
	
	// no i nasze stare dwie metody
    void wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe);
    void symulujMecz(Druzyna &pierwsza, Druzyna &druga);

private:
    Ui::SimulationWindow *ui;
};

#endif // SIMULATIONWINDOW_H
