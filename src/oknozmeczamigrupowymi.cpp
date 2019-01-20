#include "oknozmeczamigrupowymi.h"
#include "biblioteki.h"
#include "qscrollarea.h"
#include <qtablewidget.h>
#include "grupowaWindow.h"

void OknoZMeczamiGrupowymi::closeEvent(QCloseEvent *bar)
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

void OknoZMeczamiGrupowymi::wstecz(){
	foreach(QWidget *widget, qApp->topLevelWidgets())
		if (widget->windowTitle() == "Rozklad druzyn")
			widget->raise();
}
OknoZMeczamiGrupowymi::OknoZMeczamiGrupowymi(grupowaWindow *p, QWidget *parent)
	: QWidget(parent)
{
	this->parentWindow = dynamic_cast<grupowaWindow*>(p);

	ui.setupUi(this);
	
	connect(ui.dalejButton, SIGNAL(released()), this, SLOT(odpalZParenta()));
	connect(ui.wsteczButton, SIGNAL(released()), this, SLOT(wstecz()));
	
	this->setWindowTitle("Mecze Fazy Grupowej");
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	int COL = 3, ROW = 8;

	// literki do grup
	string grupy = { "ABCDEFGH" };
	
	// dwie osobne czcionki
	QFont fontNaglowka("Helvetica", 10, QFont::Bold);
	QFont fontNazw("Helvetica", 8, QFont::Bold);

	this->setMaximumWidth(650);
	this->setMaximumHeight(630);

	QColor kolorki[8];
	kolorki[0] = Qt::red;
	kolorki[1] = Qt::darkCyan;
	kolorki[2] = Qt::darkMagenta;
	kolorki[3] = Qt::green;
	kolorki[4] = Qt::cyan;
	kolorki[5] = Qt::darkRed;
	kolorki[6] = Qt::darkGreen;
	kolorki[7] = Qt::gray;


	// 8 TABELEK.
	for (int i = 0; i < 8; i++){

		// nowa tabelka o nazwie table
		QTableWidget* table = new QTableWidget();

		table->setMinimumHeight(180);
		table->setMaximumHeight(180);
		table->setMinimumWidth(287);
		table->setMaximumWidth(287);

		table->verticalHeader()->setVisible(false);
		table->horizontalHeader()->setVisible(false);

		table->setRowCount(ROW);
		table->setColumnCount(COL);
	
		table->horizontalHeader()->setDefaultSectionSize(65);
		table->verticalHeader()->setDefaultSectionSize(22);

		table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
		table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		table->setColumnWidth(0, 110);
		table->setColumnWidth(2, 110);

		
		string grupa = "GRUPA ";
		grupa.push_back(grupy[i]);

		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(grupa));
		QTableWidgetItem* one = new QTableWidgetItem("Druzyna");
		QTableWidgetItem* two = new QTableWidgetItem("Wynik");
		QTableWidgetItem* three = new QTableWidgetItem("Druzyna");


		table->setSpan(0, 0, 1, 7);

		table->setItem(0, 0, name);

		
		table->item(0, 0)->setTextAlignment(Qt::AlignCenter);

		table->item(0, 0)->setFont(fontNaglowka);

		table->item(0, 0)->setBackground(kolorki[i]);

		table->setItem(1, 0, one);
		table->setItem(1, 1, two);
		table->setItem(1, 2, three);


		for (int k = 0; k < 3; k++){
			table->item(1, k)->setTextAlignment(Qt::AlignCenter);
			table->item(1, k)->setFont(fontNazw);
		}



		// Ca³ej tabeli ustawiam flagê, ¿e nie mo¿na edytowaæ jej pól
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);


	
		
			//ui->grupowaLayout->setVerticalSpacing(110);
			if (i<2) ui.layoutZMeczamiGrupowymi->addWidget(table, 0, i % 2);
			else if (i >= 2 && i < 4)
				ui.layoutZMeczamiGrupowymi->addWidget(table, 1, i % 2);
			else if (i >= 4 && i < 6)
				ui.layoutZMeczamiGrupowymi->addWidget(table, 2, i % 2);
			else if (i >= 6 && i < 8)
				ui.layoutZMeczamiGrupowymi->addWidget(table, 3, i % 2);


			tabelki.push_back(table);
		}


}

void OknoZMeczamiGrupowymi::odpalZParenta(){
	
	if (parentWindow){
		if (parentWindow->wlaczona)
			parentWindow->raise();
		else
			parentWindow->odpalRozpiskeZeStatystykami();

	}
}

OknoZMeczamiGrupowymi::~OknoZMeczamiGrupowymi()
{
	
}
