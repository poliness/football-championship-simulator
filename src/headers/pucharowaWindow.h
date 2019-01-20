#ifndef PUCHAROWAWINDOW_H
#define PUCHAROWAWINDOW_H
#include <biblioteki.h>
#include <QDialog>
#include "druzyna.h"
#include "grupameczowa.h"
#include "kontynent.h"
#include <QTableWidget>
#include "zakonczeniewindow.h"
namespace Ui {
	class pucharowaWindow;
}

class pucharowaWindow : public QDialog
{
    Q_OBJECT

public:
	explicit pucharowaWindow(QWidget *parent = 0);
	~pucharowaWindow();

	// wektor na tabelki grupowe
	// kaøda tabelka to wskaünik, tak jak guziki 
    std::vector<QTableWidget*> tabelki;
	std::vector<Druzyna> zwyciezcy;
	// 4 osobne tabelki
    QTableWidget* przedcwiercfinalTable;
    QTableWidget* cwiercfinalTable;
    QTableWidget* polfinalTable;
    QTableWidget* finalTable;
	QTableWidget* trzecie_miejsce_Table;

	// wskaüniki do czyszczenia
	vector<QTableWidgetItem*> wskazniki;

	
	void wypiszFazePucharowa(vector<GrupaMeczowa>& grupyMeczowe);
	

    void symulujMecz(Druzyna &pierwsza, Druzyna &druga);


	private slots:
	void odpalZakonczenie();
	void wstecz();
private:
	ZakonczenieWindow *zakonczenieWindow;
	Ui::pucharowaWindow *ui;
	void closeEvent(QCloseEvent *bar);
};

#endif // SIMULATIONWINDOW_H
