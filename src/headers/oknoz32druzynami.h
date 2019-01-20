#ifndef OKNOZ32DRUZYNAMI_H
#define OKNOZ32DRUZYNAMI_H

#include <QWidget>
#include "ui_oknoz32druzynami.h"
#include <list>
#include "druzyna.h"
#include "qtablewidget.h"
#include "rankingWindow.h"

class OknoZ32Druzynami : public QWidget
{
	Q_OBJECT

public:
	OknoZ32Druzynami(QWidget *parent = 0);
	~OknoZ32Druzynami();
	void rozpisz32Druzyny(list<Druzyna> druzyny);

	private slots:
	void odpalOknoMeczowGrupowych();


private:
	list<Druzyna> druzyny;
	Ui::OknoZ32Druzynami ui;
	QTableWidget* table;
	rankingwindow * window;
	void closeEvent(QCloseEvent *bar);
};

#endif // OKNOZ32DRUZYNAMI_H
