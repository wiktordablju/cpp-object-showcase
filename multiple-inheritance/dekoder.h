#ifndef DEKODER_H
#define DEKODER_H
#include <iostream>

class radiofm {
    int kompresja;
    int crc;
    std::string format;
    std::string moc;

public:
    radiofm() : kompresja(0), crc(0), format("") {
        std::cout << "Konstruktor klasy radiofm" << std::endl;
    }
    void dekoduj() {
        std::cout << "Dekodowanie sygnalu radiofm" << std::endl;
    }

    void wypisz_format() {
        std::cout << "Format radiofm: " << format << std::endl;
    }
    void set_moc(const std::string& moc) {
        this->moc = moc;
    }

    void print_moc() {
        std::cout << "Moc radia: " << moc << std::endl;
    }
    
};

class MPG {
    int kompresja;
    int crc;
    std::string format;
    std::string moc;


    public:
    MPG() : kompresja(0), crc(0), format("") {
        std::cout << "Konstruktor klasy MPG" << std::endl;
    }

    void dekoduj() {
        std::cout << "Dekodowanie sygnalu MPG" << std::endl;
    }
    void wypisz_format() {
        std::cout << "Format MPG: " << format << std::endl;
    }
    void set_moc(const std::string& moc) {
        this->moc = moc;
    }
    void print_moc() {
        std::cout << "Moc MPG: " << moc << std::endl;
    }
};

class dabplus {
    int kompresja;
    int crc;
    std::string format;
    std::string moc;

    
    public:
    dabplus() : kompresja(0), crc(0), format("") {
        std::cout << "Konstruktor klasy dabplus" << std::endl;
    }
    void dekoduj() {
        std::cout << "Dekodowanie sygnalu dab+" << std::endl;
    }
    void wypisz_format() {
        std::cout << "Format dab+: " << format << std::endl;
    }
    void set_moc(const std::string& moc) {
        this->moc = moc;
    }
    void print_moc() {
        std::cout << "Moc dab+: " << moc << std::endl;
    }
};

class MP3 {
    int kompresja;
    int crc;
    std::string format;
    std::string moc;

    public:
    MP3() : kompresja(0), crc(0), format("") {
        std::cout << "Konstruktor klasy MP3" << std::endl;
    }
    void dekoduj() {
        std::cout << "Dekodowanie sygnalu MP3" << std::endl;
    }
    void wypisz_format() {
        std::cout << "Format MP3: " << format << std::endl;
    }
    void set_moc(const std::string& moc) {
        this->moc = moc;
    }
    void print_moc() {
        std::cout << "Moc MP3: " << moc << std::endl;
    }
};

class dekoder : public radiofm, public MPG, public dabplus, public MP3 {
    public:
    dekoder() {
        std::cout << "Konstruktor klasy dekoder" << std::endl;
    }
};


// tutaj wystepuje problem rombu, MPG4 dwa razy dziedziczy MPG, virtual
class MPG2 : public virtual MPG{
    public:
    MPG2() {    
        std::cout << "Konstruktor klasy MPG2" << std::endl;
    }
};

class MPG4 : public virtual MPG, public MPG2 {
    public:
    MPG4() {std::cout << "Konstruktor klasy MPG4" << std::endl;}
};

class odtwarzacz : public MPG4 {
    public:
    odtwarzacz() {
        std::cout << "Konstruktor klasy odtwarzacz" << std::endl;
    }
};

#endif // DEKODER_H