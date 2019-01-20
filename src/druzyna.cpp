#include "druzyna.h"
#include "biblioteki.h"

Druzyna::Druzyna(string n, int k, int miejsce_w_rankingu){
	

    this->nazwa = n;
    this->kontynent = k;
	this->miejsce_w_rankingu = miejsce_w_rankingu;

    this->szansa_na_gola_graczy = miejsce_w_rankingu;


	double temp = -0.012244897959184 * miejsce_w_rankingu + 0.91224489795918;

	// zabezpieczenie przed crashem
	if (miejsce_w_rankingu > 60)
		temp = 0.3;


    for(int i=0;i<5;i++){
        this->druzynowe_szanse_na_gole.push_back(temp);
        temp -= 0.05;
    }
   

    this->druzynowe_szanse_na_gole_w_oslabieniu = this->druzynowe_szanse_na_gole;



}

Druzyna::Druzyna(){

}
