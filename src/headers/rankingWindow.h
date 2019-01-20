#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H
#include <biblioteki.h>
#include <QDialog>
#include "druzyna.h"
#include "grupameczowa.h"
#include "kontynent.h"
#include <QTableWidget>
#include "grupowaWindow.h"
namespace Ui {
	class rankingwindow;
}

class rankingwindow : public QDialog
{
	Q_OBJECT

public:
	explicit rankingwindow(QWidget *parent = 0);
	~rankingwindow();

	std::vector<QTableWidget*> tabelki;
	void rozpiszMiejscaWRankingu(list<Druzyna> lista);

private slots:
	void odpalOknoGrupowe();
	void wstecz();
private:
	Ui::rankingwindow *ui;
	grupowaWindow *oknoGrupowe = nullptr;
	vector<GrupaMeczowa>grupyMeczowe;
	void closeEvent(QCloseEvent *bar);

};

#endif // SIMULATIONWINDOW_H
