#ifndef LICZBA_ZESPOLONA_H
#define LICZBA_ZESPOLONA_H

#include <iostream>

class LiczbaZespolona {

private:
    double im, re;
    static int licznik;

public:
    void setRe(double rea) { re = rea; }
    double getRe() const { return re; }
    void setIm(double ima) { im = ima; }
    double getIm() const { return im; }

    LiczbaZespolona() : re(0), im(0) {
        ++licznik;
        std::cout << "Konstruktor bezargumentowy został wywołany" << std::endl;
    }

    LiczbaZespolona(double rea) : re(rea), im(0) {
        ++licznik;
        std::cout << "Konstruktor jednoargumentowy został wywołany" << std::endl;
    }

    LiczbaZespolona(double rea, double ima) : re(rea), im(ima) {
        ++licznik;
        std::cout << "Konstruktor wieloargumentowy został wywołany" << std::endl;
    }

    LiczbaZespolona(const LiczbaZespolona& lz) : re(lz.re), im(lz.im) {
        ++licznik;    
        std::cout << "Konstruktor kopiujący został wywołany" << std::endl;
    }

    ~LiczbaZespolona() {
        --licznik;
        std::cout << "Destruktor został wywołany" << std::endl;
    }
    
};

class Tablica{
private:
    LiczbaZespolona** tablica;
    int wiersze, kolumny;

public:
    Tablica(int w, int k) : wiersze(w), kolumny(k) {
        tablica = new LiczbaZespolona*[wiersze];
        for (int i = 0; i < wiersze; ++i) {
            tablica[i] = new LiczbaZespolona[kolumny];
        }
    }

    Tablica(Tablica&& tab) : tablica(tab.tablica), wiersze(tab.wiersze), kolumny(tab.kolumny) {
        tab.tablica = nullptr;
        tab.wiersze = 0;
        tab.kolumny = 0;
    }

    Tablica& operator=(Tablica&& tab) {
        if (this != &tab) {
            for (int i = 0; i < wiersze; ++i) {
                delete[] tablica[i];
            }
            delete[] tablica;

            tablica = tab.tablica;
            wiersze = tab.wiersze;
            kolumny = tab.kolumny;

            tab.tablica = nullptr;
            tab.wiersze = 0;
            tab.kolumny = 0;
        }
        return *this;
    }

    ~Tablica() {
        if (tablica) {
            for (int i = 0; i < wiersze; ++i) {
                delete[] tablica[i];
            }
            delete[] tablica;
        }
    }

};
#endif // LICZBA_ZESPOLONA_H
