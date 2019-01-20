#ifndef POMOCWINDOW_H
#define POMOCWINDOW_H

#include <QWidget>
#include "ui_pomocwindow.h"

class pomocWindow : public QWidget
{
	Q_OBJECT

public:
	pomocWindow(QWidget *parent = 0);
	~pomocWindow();

private:
	Ui::pomocWindow ui;
};

#endif // POMOCWINDOW_H
