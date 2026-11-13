#include <iostream>
#include <string>
#include "tinyfiledialogs.h"
#include "correction_system.h"

int main() {
    try {
        GrammarCorrector corrector("dictionary.txt");
        
        const char* filepath_cstr = tinyfd_openFileDialog(
            "Wybierz plik do korekty",
            "",
            0,
            nullptr,
            nullptr,
            0
        );

        if (!filepath_cstr) {
            std::cout << "Nie wybrano pliku." << std::endl;
            return 0;
        }

        std::string inputPath(filepath_cstr);
        std::cout << "Wybrany plik: " << inputPath << std::endl;

        std::string outputPath;
        size_t lastDot = inputPath.find_last_of('.');
        if (lastDot != std::string::npos) {
            outputPath = inputPath.substr(0, lastDot) + "_poprawione" + inputPath.substr(lastDot);
        } else {
            outputPath = inputPath + "_poprawione.txt";
        }

        std::cout << "Plik wyjściowy: " << outputPath << std::endl << std::endl;

        corrector.correctFile(inputPath, outputPath);
        
        corrector.displayStatistics();
        
        // to jest tylko dla testu
        corrector + "noweSlowo";
        std::cout << "Dodano nowe słowo do słownika." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Błąd: " << e.what() << std::endl;
        return 0;
    }

    return 0;
}