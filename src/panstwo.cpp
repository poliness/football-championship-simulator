#include "panstwo.h"

Panstwo::Panstwo(int ID, QPushButton *button, QTextEdit* rankingTextEdit, QLabel* nazwa, int kontynent)
{
    this->ID = ID;
    this->button = button;
    this->nazwa = nazwa->text().toStdString();
	this->rankingTextEdit = rankingTextEdit;
    this->nazwaLabel = nazwa;
    this->kontynent = kontynent;
	this->miejsceWRankingu = 0;
	
}

Panstwo::Panstwo(){
	this->ID = -1;
}

