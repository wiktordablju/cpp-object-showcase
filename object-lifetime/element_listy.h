#ifndef ELEMENT_LISTY_H
#define ELEMENT_LISTY_H

#include "liczba_zespolona.h"

class ElementListy {
public:
    LiczbaZespolona liczba;
    ElementListy* nastepnyElement;   
    ElementListy(const LiczbaZespolona& lz, ElementListy* nasEl = nullptr) : liczba(lz), nastepnyElement(nasEl) {}
    ~ElementListy() {delete nastepnyElement;}
};

#endif // ELEMENT_LISTY_H
