#include <iostream>
#include <cstring>
#include "klasy.h"


int main() {
    Radio radio1(true, 95);
    Radio radio2(false, 105);
    Silnik silnik1(true, 1000, 101);    
    Samolot sam1(radio1);
    sam1.paliwo = 1000;
    sam1.dystans = 2000;
    sam1.x = 10;
    sam1.y = 20;
    sam1.z = 30;
    sam1.wysokosc = 1000;
    
    Silnik silnik2(true, 1200, 102);
    Samolot sam2(100, 200, 5, 15, 25, 800, 2000, silnik2, radio2, "ABC123");
    
    std::cout << "Sam1:" << std::endl;
    wyswietlWartosci(sam1);
    std::cout << "Sam2:" << std::endl;
    wyswietlWartosci(sam2);
    Samolot sam3 = zmniejszWysokosc(sam1, 100);
    
    Samolot sam4(radio1);
    sam4 = sam2; 
    
    return 0;
}