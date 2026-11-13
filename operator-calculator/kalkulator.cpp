#include "kalkulator.h"
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Wartosc& w) {
    os << w.getWartosc();
    return os;
}

void Lista::dodaj(const Wartosc& wartosc, const std::string& operacja) {
    auto nowy = std::make_unique<Element>(wartosc, operacja);
    if (!glowa) {
        glowa = std::move(nowy);
        ogon = glowa.get();
    } else {
        ogon->nastepny = std::move(nowy);
        ogon = ogon->nastepny.get();
    }
}

Wartosc Lista::pobierzOstatni() const {
    if (!ogon) {
        std::cout << "Brak wyników w pamięci" << std::endl;
        return Wartosc(0.0);
    }
    return ogon->wartosc;
}

void Lista::wyswietl() const {
    Element* current = glowa.get();
    if (!current) {
        std::cout << "Historia jest pusta" << std::endl;
        return;
    }
    
    while (current) {
        std::cout << current->operacja << std::endl;
        current = current->nastepny.get();
    }
}

void Kalkulator::dodaj(const Wartosc& a, const Wartosc& b) {
    Wartosc wynik = a + b;
    std::stringstream ss;
    ss << a << " + " << b << " = " << wynik;
    wyniki.dodaj(wynik, ss.str());
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::odejmij(const Wartosc& a, const Wartosc& b) {
    Wartosc wynik = a - b;
    std::stringstream ss;
    ss << a << " - " << b << " = " << wynik;
    wyniki.dodaj(wynik, ss.str());
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::pomnoz(const Wartosc& a, const Wartosc& b) {
    Wartosc wynik = a * b;
    std::stringstream ss;
    ss << a << " * " << b << " = " << wynik;
    wyniki.dodaj(wynik, ss.str());
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::podziel(const Wartosc& a, const Wartosc& b) {
    try {
        Wartosc wynik = a / b;
        std::stringstream ss;
        ss << a << " / " << b << " = " << wynik;
        wyniki.dodaj(wynik, ss.str());
        std::cout << "Wynik: " << wynik << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Błąd: " << e.what() << std::endl;
    }
}

void Kalkulator::historia() {
    std::cout << "Historia operacji:" << std::endl;
    wyniki.wyswietl();
}