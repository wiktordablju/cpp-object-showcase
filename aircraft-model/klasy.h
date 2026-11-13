#ifndef KLASY_H
#define KLASY_H
#include <iostream>
#include <cstring>

class Radio {
public:
    bool stan;
    int kanal;
};

class Silnik {
    public:
    bool stan;
    int szybkosc;
    int identyfikator;    

    // private:
    Silnik& operator=(const Silnik& other) {
        if (this != &other) {
            stan = other.stan;
            szybkosc = other.szybkosc;
            identyfikator = other.identyfikator;
        }
        return *this;
    }
};

class Samolot {
    // private:
    //     double x, y, z;

    public:
    double paliwo;    
    double dystans;   
    double x;         
    double y;         
    double z;         
    double wysokosc;
    char* sygnatura;
    const int masa;  
    Silnik psilnik;   
    Radio& radio;    
    
    Samolot(Radio& r) : paliwo(0), dystans(0), x(0), y(0), z(0), wysokosc(0), masa(1000), psilnik(), radio(r), sygnatura(nullptr) {}
    
    Samolot(double p, double d, double x1, double y1, double z1, double w, int m, Silnik s, Radio& r, const char* sig = nullptr) : paliwo(p), dystans(d), x(x1), y(y1), z(z1), wysokosc(w), masa(m), psilnik(s), radio(r), sygnatura(nullptr) {
        if (sig) {
            sygnatura = new char[strlen(sig) + 1];
            strcpy(sygnatura, sig);
        }
    }
    
    Samolot(const Samolot& other) : paliwo(other.paliwo), dystans(other.dystans), x(other.x), y(other.y), z(other.z), wysokosc(other.wysokosc), masa(other.masa), psilnik(other.psilnik), radio(other.radio), sygnatura(nullptr) {
        if (other.sygnatura) {
            sygnatura = new char[strlen(other.sygnatura) + 1];
            strcpy(sygnatura, other.sygnatura);
        }
    }
    
    Samolot& operator=(const Samolot& other) {
        if (this != &other) {
            paliwo = other.paliwo;
            dystans = other.dystans;
            x = other.x;
            y = other.y;
            z = other.z;
            wysokosc = other.wysokosc;
            psilnik = other.psilnik; 
            delete[] sygnatura;
            sygnatura = nullptr;
            if (other.sygnatura) {
                sygnatura = new char[strlen(other.sygnatura) + 1];
                strcpy(sygnatura, other.sygnatura);
            }
        }
        return *this;
    }
    
    ~Samolot() {
        delete[] sygnatura;
    }
};

void wyswietlWartosci(Samolot samolot) {
    std::cout << "Paliwo: " << samolot.paliwo << std::endl;
    std::cout << "Dystans: " << samolot.dystans << std::endl;
    std::cout << "X: " << samolot.x << std::endl;
    std::cout << "Y: " << samolot.y << std::endl;
    std::cout << "Z: " << samolot.z << std::endl;
    std::cout << "Wysokosc: " << samolot.wysokosc << std::endl;
    std::cout << "Masa: " << samolot.masa << std::endl;
    std::cout << "Silnik stan: " << samolot.psilnik.stan << std::endl;
    std::cout << "Silnik szybkosc: " << samolot.psilnik.szybkosc << std::endl;
    std::cout << "Silnik identyfikator: " << samolot.psilnik.identyfikator << std::endl;
    std::cout << "Radio stan: " << samolot.radio.stan << std::endl;
    std::cout << "Radio kanal: " << samolot.radio.kanal << std::endl;
    if (samolot.sygnatura)
        std::cout << "Sygnatura: " << samolot.sygnatura << std::endl;
    else
        std::cout << "Sygnatura: brak" << std::endl;
}

Samolot zmniejszWysokosc(Samolot samolot, double korekta) {
    samolot.wysokosc -= korekta;
    return samolot;
}

#endif // KLASY_H