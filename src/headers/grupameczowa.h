#ifndef GRUPAMECZOWA
#define GRUPAMECZOWA
#include "biblioteki.h"
#include "druzyna.h"

class GrupaMeczowa {
public:
    std::vector<Druzyna>druzyny_w_grupie;
    int zapelnienie_grupy = 0;

    GrupaMeczowa();
};
#endif // GRUPAMECZOWA

