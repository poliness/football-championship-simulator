#include "oknopowitalne.h"

OknoPowitalne::OknoPowitalne(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle("Powitanie");
}

OknoPowitalne::~OknoPowitalne()
{

}
