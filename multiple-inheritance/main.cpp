#include "dekoder.h"
#include "instrumenty.h"

int main() {
    std::cout << "Formaty" << std::endl;
    radiofm radio1;
    MPG mpg1;
    dabplus dab1;
    MP3 mp3_1;
    radio1.wypisz_format(); 
    mpg1.dekoduj(); 
    std::cout << "----------" << std::endl;

    std::cout << "Dekoder" << std::endl;
    dekoder dek1;
    dek1.radiofm::set_moc("100Hz");
    dek1.radiofm::print_moc();
    dek1.MPG::set_moc("200Hz");
    dek1.MPG::print_moc();
    std::cout << "----------" << std::endl;

    // obiekty konstruowane sa "od dolu", w tym przypadku najpierw MPG, z ktorego dziedzicza MPG2 i MPG4, pozniej MPG2 z ktorego dziedziczy MPG4 i na koncu MPG4 z ktorego dziedziczy odtwarzacz
    std::cout << "Odtwarzacz" << std::endl;
    odtwarzacz odt1;
    odt1.dekoduj();
    std::cout << "----------" << std::endl;

    // Instrumenty
    // Przy zalozeniu ze instrument dziedziczy po klasycznych, przetworzonych i AI nie wystapi problem rombu, natomiast gdy przetworzony dziedziczy dodatkowo po klasycznym wystepuje juz ten problem. 
    // Po dodaniu dziedziczenia virtual w linijkach 19 i 46 problem znika
    std::cout << "Instrumenty" << std::endl;
    instrument instrument1;
    instrument1.instrumentKlasyczny::graj();
    std::cout << "-----------------" << std::endl;
    return 0;
}