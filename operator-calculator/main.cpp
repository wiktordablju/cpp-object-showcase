#include <iostream>
#include "liczba_zespolona.h"
#include "kalkulator.h"


int main() {
    LiczbaZespolona lz1(3, 4);
    LiczbaZespolona lz2(1, 2);
    LiczbaZespolona lz3;
    std::cout << "lz1 = " << lz1 << std::endl;
    std::cout << "lz2 = " << lz2 << std::endl;
    std::cout << "lz3 = " << lz3 << std::endl << std::endl;
    
    lz1 += lz2;
    std::cout << "1. lz1 += lz2: " << lz1 << std::endl;
    
    // LiczbaZespolona lz4 = operator+(lz1, lz2);
    // std::cout << "2. lz1 + lz2: " << lz4 << std::endl;
    
    LiczbaZespolona lz5 = lz1 + lz2;
    std::cout << "3. lz1 + lz2: " << lz5 << std::endl;
    
    LiczbaZespolona lz6 = lz1 - lz2;
    std::cout << "4. lz1 - lz2: " << lz6 << std::endl;
    
    std::cout << "5. lz1[0]: " << lz1[0] << ", lz1[1]: " << lz1[1] << std::endl;
    
    std::cout << "6. lz1 != lz2: " << (lz1 != lz2) << std::endl;
    
    lz3 = lz1;
    std::cout << "8. lz3 = lz1: " << lz3 << std::endl;
    
    std::cout << "9. lz3 == lz1: " << (lz3 == lz1) << std::endl;
    
    ++lz2;
    std::cout << "10. ++lz2: " << lz2 << std::endl;
    
    lz2 += 5.5;
    std::cout << "11. lz2 += 5.5: " << lz2 << std::endl;
    
    lz3(7, 8);
    std::cout << "12. lz3(7, 8): " << lz3 << std::endl;

    // ----------
    // Kalkulator
    Kalkulator kalk;
    Wartosc w1(10.5), w2(5.25), w3(0.0);
    std::cout << "w1: " << w1 << ", w2: " << w2 << ", w3: " << w3 << std::endl;
    
    std::cout << "Dodawanie: ";
    kalk.dodaj(w1, w2);
    
    std::cout << "Odejmowanie: ";
    kalk.odejmij(w1, w2);
    
    std::cout << "Mnożenie: ";
    kalk.pomnoz(w1, w2);
    
    std::cout << "Dzielenie: ";
    kalk.podziel(w1, w2);
    
    std::cout << "Dzielenie przez zero: ";
    kalk.podziel(w1, w3);
    
    kalk.historia();
    

    return 0;
}
