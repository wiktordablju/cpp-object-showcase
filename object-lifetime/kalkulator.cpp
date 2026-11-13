 #include "kalkulator.h"

void Lista::dodaj(double wartosc) {
    auto nowy = std::make_unique<Element>(wartosc);
    if (!glowa) {
        glowa = std::move(nowy);
        ogon = glowa.get();
    } else {
        ogon->nastepny = std::move(nowy);
        ogon = ogon->nastepny.get();
    }
}

double Lista::pobierzOstatni() const {
    if (!ogon) {
        std::cout<<"Brak wyników w pamięci!"<<std::endl;
    }
    return ogon->wartosc;
}

void Lista::wyswietl() const {
    Element* current = glowa.get();
    while (current) {
        std::cout << current->wartosc << " -> ";
        current = current->nastepny.get();
    }
    std::cout << std::endl;
}

void Kalkulator::dodaj(double a, double b) {
    double wynik = a + b;
    wyniki.dodaj(wynik);
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::odejmij(double a, double b) {
    double wynik = a - b;
    wyniki.dodaj(wynik);
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::pomnoz(double a, double b) {
    double wynik = a * b;
    wyniki.dodaj(wynik);
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::podziel(double a, double b) {
    if (b == 0) {
        std::cout << "Błąd: Dzielenie przez zero!" << std::endl;
        return;
    }
    double wynik = a / b;
    wyniki.dodaj(wynik);
    std::cout << "Wynik: " << wynik << std::endl;
}

void Kalkulator::historia() {
    std::cout << "Historia wyników: ";
    wyniki.wyswietl();
}
