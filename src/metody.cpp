#include "metody.h"

int FAZA = 0;

int PRZED = 2, CWIERC = 2, POL = 2, FINAL = 2;
Druzyna wybierzNajlepszaZeWszystkichKontynentow(vector<Kontynent>& k){
	double max = INT_MAX, index;
	for (int i = 0; i < 6; i++){
		if (k[i].druzyny_na_kontynencie.size() > 0 && (k[i].druzyny_na_kontynencie.front().druzynowe_szanse_na_gole.front() < max)){
			index = i;
			max = k[i].druzyny_na_kontynencie.front().druzynowe_szanse_na_gole.front();
		}
	}

	Druzyna d = k[index].druzyny_na_kontynencie.front();
	k[index].druzyny_na_kontynencie.pop_front();
	return d;
}

