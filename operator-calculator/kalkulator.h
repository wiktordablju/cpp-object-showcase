#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <iostream>
#include <memory>
#include <string>

class Wartosc {
private:
    double wartosc;

public:
    Wartosc() : wartosc(0.0) {}
    Wartosc(double w) : wartosc(w) {}
    
    double getWartosc() const { return wartosc; }
    void setWartosc(double w) { wartosc = w; }
    
    Wartosc operator+(const Wartosc& w) const {
        return Wartosc(wartosc + w.wartosc);
    }
    
    Wartosc operator-(const Wartosc& w) const {
        return Wartosc(wartosc - w.wartosc);
    }
    
    Wartosc operator*(const Wartosc& w) const {
        return Wartosc(wartosc * w.wartosc);
    }
    
    Wartosc operator/(const Wartosc& w) const {
        if (w.wartosc == 0) {
            std::cout << "Dzielenie przez zero!" << std::endl;
            return Wartosc(0);
        }
        return Wartosc(wartosc / w.wartosc);
    }
    
    Wartosc& operator+=(const Wartosc& w) {
        wartosc += w.wartosc;
        return *this;
    }
    
    Wartosc& operator-=(const Wartosc& w) {
        wartosc -= w.wartosc;
        return *this;
    }
    
    Wartosc& operator*=(const Wartosc& w) {
        wartosc *= w.wartosc;
        return *this;
    }
    
    Wartosc& operator/=(const Wartosc& w) {
        if (w.wartosc == 0) {
            std::cout << "Dzielenie przez zero!" << std::endl;
            return *this;
        }
        wartosc /= w.wartosc;
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Wartosc& w);
};

class Element {
public:
    Wartosc wartosc;         
    std::string operacja;     
    std::unique_ptr<Element> nastepny;
    
    Element(const Wartosc& w, const std::string& op) : wartosc(w), operacja(op), nastepny(nullptr) {}
};

class Lista {
private:
    std::unique_ptr<Element> glowa;
    Element* ogon; 

public:
    Lista() : glowa(nullptr), ogon(nullptr) {}
    void dodaj(const Wartosc& wartosc, const std::string& operacja);
    Wartosc pobierzOstatni() const;
    void wyswietl() const;
};

class Kalkulator {
private:
    Lista wyniki;

public:
    ~Kalkulator() {}
    
    void dodaj(const Wartosc& a, const Wartosc& b);
    void odejmij(const Wartosc& a, const Wartosc& b);
    void pomnoz(const Wartosc& a, const Wartosc& b);
    void podziel(const Wartosc& a, const Wartosc& b);
    void historia();
};

#endif // KALKULATOR_H