#include <iostream>
#include "liczba_zespolona.h"
#include "element_listy.h"
#include "kalkulator.h"


int main() {
    // Kalkulator
    Kalkulator calc;
    calc.dodaj(5, 3);       
    calc.odejmij(10, 4);    
    calc.pomnoz(2, 3);      
    calc.podziel(8, 2);     
    calc.podziel(5, 0);     
    calc.historia();

    LiczbaZespolona liczba;
    liczba.setRe(3.5);
    liczba.setIm(-2.1);
    std::cout << "z = " << liczba.getRe() << " + " << liczba.getIm() << "i" << std::endl;

    LiczbaZespolona liczba1;
    std::cout << "z1 = " << liczba1.getRe() << " + " << liczba1.getIm() << "i" << std::endl;

    LiczbaZespolona liczba2(7.18);
    std::cout << "z2 = " << liczba2.getRe() << " + " << liczba2.getIm() << "i" << std::endl;

    LiczbaZespolona liczba3(-5, 14.123);  
    std::cout << "z3 = " << liczba3.getRe() << " + " << liczba3.getIm()<< "i" << std::endl;

    LiczbaZespolona liczba4 = liczba3;  
    std::cout << "z4 = " << liczba4.getRe() << " + " << liczba4.getIm() << "i" << std::endl;

    Tablica tab1(2, 3);
    Tablica tab2 = std::move(tab1); 
    Tablica tab3(1, 1); 
    tab3 = std::move(tab2);

    LiczbaZespolona lz1(1, 1);
    LiczbaZespolona lz2(2, 2);
    LiczbaZespolona lz3(3, 3);
    ElementListy e3(lz3, nullptr);
    ElementListy e2(lz2, &e3);
    ElementListy e1(lz1, &e2);

    return 0;
}
