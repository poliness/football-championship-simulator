#ifndef OKNOPOWITALNE_H
#define OKNOPOWITALNE_H

#include <QWidget>
#include "ui_oknopowitalne.h"

class OknoPowitalne : public QWidget
{
	Q_OBJECT

public:
	OknoPowitalne(QWidget *parent = 0);
	~OknoPowitalne();

private:
	Ui::OknoPowitalne ui;
};

#endif // OKNOPOWITALNE_H
