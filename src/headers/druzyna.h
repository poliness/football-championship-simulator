#ifndef DRUZYNA
#define DRUZYNA
#include "biblioteki.h"

class Druzyna {
    public:
        string nazwa;
        int kontynent;
		int miejsce_w_rankingu = 0;
        vector<double>druzynowe_szanse_na_gole;
        vector<double>druzynowe_szanse_na_gole_w_oslabieniu;
        double szansa_na_gola_graczy;

        bool wygrala_przedcwiercfinal = false;
        bool wygrala_cwiercfinal = false;
        bool wygrala_polfinal = false;
        bool wygrala_final = false;
		bool wygrala_3_miejsce = false;
        //statystyka fazy grupowej
        int ilosc_pkt_w_fazie_grupowej = 0;
        int zwyciestwa = 0;
        int porazki = 0;
        int remisy = 0;
        int bramki_strzelone = 0;
        int bramki_stracone = 0;

        int ile_meczy_w_oslabieniu = 0;

        //konstruktor (nazwa, kontynent, miejsce w rankingu)
        Druzyna(string n, int k, int miejsce_w_rankingu);
        Druzyna();
};
#endif // DRUZYNA

