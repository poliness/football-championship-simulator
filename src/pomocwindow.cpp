#include "pomocwindow.h"

pomocWindow::pomocWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle("Pomoc");
}

pomocWindow::~pomocWindow()
{

}
