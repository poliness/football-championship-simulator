#pragma once
#include "biblioteki.h"
#include "druzyna.h"
#include "kontynent.h"
#include "qtablewidget.h"
#include "grupameczowa.h"

//faza rozgrywek
extern int FAZA;

extern int PRZED, CWIERC, POL, FINAL;



Druzyna wybierzNajlepszaZeWszystkichKontynentow(vector<Kontynent>& k);



inline bool compDouble(const double &d1, const double &d2){
	return d1 < d2;
}

inline bool compIloscPunktow(const Druzyna &d1, const Druzyna &d2){
	return d1.ilosc_pkt_w_fazie_grupowej > d2.ilosc_pkt_w_fazie_grupowej;
}

inline bool compRanking(const Druzyna &d1, const Druzyna &d2){
	return d1.miejsce_w_rankingu < d2.miejsce_w_rankingu;
}
