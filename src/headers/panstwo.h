#ifndef PANSTWO_H
#define PANSTWO_H
#include <biblioteki.h>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

class Panstwo
{
public:

    Panstwo(int ID, QPushButton *button, QTextEdit* ranking, QLabel* nazwa, int kontynent);
	Panstwo();

    int ID;
    QPushButton * button;
    QTextEdit *rankingTextEdit;
    QLabel *nazwaLabel;
    string nazwa;
    int kontynent;
	int miejsceWRankingu;

    bool gotowa = false;

};

#endif // PANSTWO_H
