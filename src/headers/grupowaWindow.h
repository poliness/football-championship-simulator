#ifndef GRUPOWAWINDOW_H
#define GRUPOWAWINDOW_H
#include <biblioteki.h>
#include <QDialog>
#include "druzyna.h"
#include "grupameczowa.h"
#include "kontynent.h"
#include <QTableWidget>
#include "pucharowaWindow.h"
#include "oknozmeczamigrupowymi.h"

namespace Ui {
	class grupowaWindow;
}

class grupowaWindow : public QDialog
{
	Q_OBJECT

public:
	explicit grupowaWindow(QWidget *parent = 0);
	~grupowaWindow();

	
	std::vector<QTableWidget*> tabelki;
	void rozpiszFazeGrupowa(vector<GrupaMeczowa>& grupyMeczowe);
	void wypiszFazeGrupowa(vector<GrupaMeczowa> &grupyMeczowe);
	void symulujMecz(Druzyna &pierwsza, Druzyna &druga);
	void odpalRozpiskeZeStatystykami();

	OknoZMeczamiGrupowymi * oknoZMeczamiGrupowymi;

	bool wlaczona;
	private slots:
	void odpalOknoFinalowe();
	void wstecz();
	

	
private:
	int _TABELA = 0;
	int _WIERSZ = 2;
	Ui::grupowaWindow *ui;
	pucharowaWindow *oknoFinalowe;
	vector<GrupaMeczowa> grupyMeczowe;
	void closeEvent(QCloseEvent *bar);

};

#endif // SIMULATIONWINDOW_H
