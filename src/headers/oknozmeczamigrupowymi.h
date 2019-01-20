#ifndef OKNOZMECZAMIGRUPOWYMI_H
#define OKNOZMECZAMIGRUPOWYMI_H

#include <QWidget>
#include "ui_oknozmeczamigrupowymi.h"
#include "qtablewidget.h"

class grupowaWindow;

class OknoZMeczamiGrupowymi : public QWidget
{
	Q_OBJECT

public:
	OknoZMeczamiGrupowymi(grupowaWindow *p, QWidget *parent = 0);
	~OknoZMeczamiGrupowymi();
	std::vector<QTableWidget*> tabelki;

	grupowaWindow * parentWindow;
private slots:
	void odpalZParenta();
	void wstecz();
private:

	Ui::OknoZMeczamiGrupowymi ui;
	void closeEvent(QCloseEvent *bar);
};

#endif // OKNOZMECZAMIGRUPOWYMI_H
