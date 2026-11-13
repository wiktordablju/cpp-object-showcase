#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <iostream>
#include <memory>

class Element {
public:
    double wartosc;
    std::unique_ptr<Element> nastepny;

    explicit Element(double war) : wartosc(war), nastepny(nullptr) {}
};

class Lista {
private:
    std::unique_ptr<Element> glowa;
    Element* ogon; 

public:
    Lista() : glowa(nullptr), ogon(nullptr) {}
    void dodaj(double wartosc);
    double pobierzOstatni() const;
    void wyswietl() const;
};

class Kalkulator {
private:
    Lista wyniki;

public:
        ~Kalkulator(){};
    void dodaj(double a, double b);
    void odejmij(double a, double b);
    void pomnoz(double a, double b);
    void podziel(double a, double b);
    void historia();
};

#endif // KALKULATOR_H
