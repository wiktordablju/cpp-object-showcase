#ifndef INSTRUMENTY_H
#define INSTRUMENTY_H
#include <string>
#include <iostream>

class instrumentKlasyczny {
    int wiek;
    std::string material;
    std::string dzwiek;
    public:
    instrumentKlasyczny() : wiek(0), material(""), dzwiek("") {
        std::cout << "Konstruktor klasy InstrumentKlasyczny" << std::endl;
    }
    void graj() {
        std::cout << "Granie na instrumencie klasycznym" << std::endl;
    }
};

class instrumentPrzetworzony : public virtual instrumentKlasyczny {
    std::string typPrzetworzenia;
    std::string dzwiek;

    public:
    instrumentPrzetworzony() : typPrzetworzenia(""), dzwiek("") {
        std::cout << "Konstruktor klasy instrumentPrzetworzony" << std::endl;
    }
    
    void graj() {
        std::cout << "Granie na instrumencie przetworzonym" << std::endl;
    }
};

class instrumentAi {
    std::string modelAi;
    std::string dzwiek;
    public:
    instrumentAi() : modelAi(""), dzwiek("") {
        std::cout << "Konstruktor klasy InstrumentAI" << std::endl;
    }
    
    void graj() {
        std::cout << "Granie na instrumencie generowanym przez AI" << std::endl;
    }
};

class instrument : public virtual instrumentKlasyczny, public instrumentPrzetworzony, public instrumentAi {
    public:
    instrument() {
        std::cout << "Konstruktor klasy instrument" << std::endl;
    }
};
#endif // INSTRUMENTY_H
