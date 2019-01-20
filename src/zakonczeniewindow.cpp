#include "zakonczeniewindow.h"
#include "biblioteki.h"
#include "druzyna.h"

void ZakonczenieWindow::closeEvent(QCloseEvent *bar)
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

void ZakonczenieWindow::zamknijWszystkieIWrocDoMenu(){
	foreach(QWidget *widget, qApp->topLevelWidgets()) {

		if (widget->windowTitle() == "Spis druzyn" || widget->windowTitle() == "Rozklad druzyn" || widget->windowTitle() == "Podsumowanie Fazy Grupowej" ||
			widget->windowTitle() == "Mecze Fazy Grupowej" || widget->windowTitle() == "Faza grupowa" || widget->windowTitle() == "Faza Pucharowa" ||
			widget->windowTitle() == "Zakonczenie Mistrzostw")
			widget->close();

		if (widget->inherits("QMainWindow"))
			(widget)->setEnabled(true);
	}
}
void ZakonczenieWindow::wstecz(){
	foreach(QWidget *widget, qApp->topLevelWidgets())
		if (widget->windowTitle() == "Faza Pucharowa")
			widget->raise();
}
ZakonczenieWindow::ZakonczenieWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui.pushButton_2, SIGNAL(released()), this, SLOT(zamknijWszystkieIWrocDoMenu()));
	connect(ui.wsteczButton, SIGNAL(released()), this, SLOT(wstecz()));
	this->setMaximumHeight(310);
	this->setMaximumWidth(410);
	this->setWindowTitle("Zakonczenie Mistrzostw");
	int COL = 2, ROW = 5;

	QFont fontNaglowka("Helvetica", 15, QFont::Bold);
	QFont fontNazw("Helvetica", 12, QFont::Bold);

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

	table->horizontalHeader()->setDefaultSectionSize(167);
	table->verticalHeader()->setDefaultSectionSize(41);

	table->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
	table->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
	table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	table->setColumnWidth(0, 174);
	table->setColumnWidth(1, 174);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	QTableWidgetItem* numer = new QTableWidgetItem("Miejsce");
	QTableWidgetItem* nazwa = new QTableWidgetItem("Nazwa");

	table->setItem(0, 0, numer);
	table->setItem(0, 1, nazwa);

	for (int i = 0; i < 2; i++){
		table->item(0, i)->setTextAlignment(Qt::AlignCenter);
		table->item(0, i)->setFont(fontNaglowka);
		table->item(0, i)->setBackground(kolorki[0]);
	}

	ui.zakonczenieLayout->addWidget(table);
	table->setContentsMargins(0, 0, 0, 0);

}

void ZakonczenieWindow::wpiszDruzyny(vector<Druzyna> druzyny){
	table->setItem(1, 0, new QTableWidgetItem("I"));
	table->setItem(2, 0, new QTableWidgetItem("II"));
	table->setItem(3, 0, new QTableWidgetItem("II"));
	table->setItem(4, 0, new QTableWidgetItem("IV"));
	for (int i = 0; i < 4;i++){
		 table->setItem(i+1, 1, new QTableWidgetItem(QString::fromStdString(druzyny[i].nazwa)));
	}


	QFont fontNazw("Helvetica", 12, QFont::Bold);

	for (int k = 0; k < 5; k++){
		for (int j = 0; j < 2; j++){
			table->item(k, j)->setTextAlignment(Qt::AlignCenter);
			table->item(k, j)->setFont(fontNazw);
		}
	}
}
ZakonczenieWindow::~ZakonczenieWindow()
{

}
