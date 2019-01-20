#ifndef ZAKONCZENIEWINDOW_H
#define ZAKONCZENIEWINDOW_H

#include <QWidget>
#include "ui_zakonczeniewindow.h"
#include "qtablewidget.h"
#include "druzyna.h"
#include "biblioteki.h"
class ZakonczenieWindow : public QWidget
{
	Q_OBJECT

public:
	ZakonczenieWindow(QWidget *parent = 0);
	~ZakonczenieWindow();
	void wpiszDruzyny(vector<Druzyna> lista);

	private slots:
	void wstecz();
	void zamknijWszystkieIWrocDoMenu();
private:
	Ui::ZakonczenieWindow ui;
	QTableWidget * table;
	void closeEvent(QCloseEvent *bar);
};

#endif // ZAKONCZENIEWINDOW_H
