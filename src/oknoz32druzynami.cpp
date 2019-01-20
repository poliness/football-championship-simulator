#include "oknoz32druzynami.h"
#include "biblioteki.h"
#include "druzyna.h"
#include "metody.h"
#include <qtablewidget.h>



void OknoZ32Druzynami::closeEvent(QCloseEvent *bar)
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

OknoZ32Druzynami::OknoZ32Druzynami(QWidget *parent)
	: QWidget(parent)
{
	
	window = 0;
	ui.setupUi(this);
	this->setWindowTitle("Spis druzyn");
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui.dalejButton, SIGNAL(released()), this, SLOT(odpalOknoMeczowGrupowych()));
	this->setMaximumHeight(550);
	this->setMaximumWidth(350);

	int COL = 3, ROW = 33;
	
	// literki do grup
	
	// dwie osobne czcionki
	QFont fontNaglowka("Helvetica", 10, QFont::Bold);
	QFont fontNazw("Helvetica", 8, QFont::Bold);


	QColor kolorki[8];
	kolorki[0] = Qt::red;
	kolorki[1] = Qt::darkCyan;
	kolorki[2] = Qt::darkMagenta;
	kolorki[3] = Qt::green;
	kolorki[4] = Qt::cyan;
	kolorki[5] = Qt::darkRed;
	kolorki[6] = Qt::darkGreen;
	kolorki[7] = Qt::gray;


		 table = new QTableWidget();

	
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


		table->setColumnWidth(1, 123);
		table->setColumnWidth(2, 123);
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);

		QTableWidgetItem* numer = new QTableWidgetItem("Nr.");
		QTableWidgetItem* nazwa = new QTableWidgetItem("Nazwa");
		QTableWidgetItem* kontynent = new QTableWidgetItem("Kontynent");


	
		table->setItem(0, 0, numer);
		table->setItem(0, 1, nazwa);
		table->setItem(0, 2, kontynent);

		for (int i = 0; i < 3; i++){
			table->item(0, i)->setTextAlignment(Qt::AlignCenter);
			table->item(0, i)->setFont(fontNaglowka);
			table->item(0, i)->setBackground(kolorki[0]);
		}


		ui.kolumnaDruzynLayout->addWidget(table);
		table->setContentsMargins(0, 0, 0, 0);
		
		


}


void OknoZ32Druzynami::odpalOknoMeczowGrupowych(){

	
	if (window == 0){
		window = new rankingwindow();
		window->show();
		window->rozpiszMiejscaWRankingu(druzyny);
		window->setAttribute(Qt::WA_DeleteOnClose);
	}
	else window->raise();
}

OknoZ32Druzynami::~OknoZ32Druzynami()
{
	delete table;
}

void OknoZ32Druzynami::rozpisz32Druzyny(list<Druzyna> lista){
	this->druzyny.clear();

	this->druzyny = lista;
	vector<Druzyna> temp;
	for (auto it : lista)
		temp.push_back(it);

	for (int i = 0; i < 32; i++){
		table->setItem(i+1, 0, new QTableWidgetItem(QString(QString::number(i + 1))));
		table->setItem(i + 1, 1, new QTableWidgetItem(QString::fromStdString(temp[i].nazwa)));

		string kontynent;
		switch (temp[i].kontynent)
		{
			case 1: kontynent = "Azja";
				break;
			case 6: kontynent = "Europa";
				break;
			case 2: kontynent = "Afryka";
				break;
			case 3: kontynent = "Ameryka Pln.";
				break;
			case 4: kontynent = "Ameryka Pld.";
				break;
			case 5: kontynent = "Australia i Oc.";
				break;
		}
		table->setItem(i+1, 2, new QTableWidgetItem(QString::fromStdString(kontynent)));

	}

	for (int k = 0; k < 33; k++)
		for (int j = 0; j < 3; j++)
			table->item(k, j)->setTextAlignment(Qt::AlignCenter);

		
	

}
