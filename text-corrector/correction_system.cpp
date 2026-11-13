#include "correction_system.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <limits>
#include <map>
#include <functional>

void Dictionary::insertRecursive(std::shared_ptr<TreeNode>& node, const std::string& word) {
    if (!node) {
        node = std::make_shared<TreeNode>(word);
        nodeCount++;
        return;
    }
    
    if (word < node->word) {
        insertRecursive(node->left, word);
    } else if (word > node->word) {
        insertRecursive(node->right, word);
    }
}

bool Dictionary::searchRecursive(const std::shared_ptr<TreeNode>& node, const std::string& word) const {
    if (!node) return false;
    
    if (word == node->word) return true;
    
    if (word < node->word) {
        return searchRecursive(node->left, word);
    } else {
        return searchRecursive(node->right, word);
    }
}

void Dictionary::collectWordsRecursive(const std::shared_ptr<TreeNode>& node, std::vector<std::string>& words) const {
    if (!node) return;
    collectWordsRecursive(node->left, words);
    words.push_back(node->word);
    collectWordsRecursive(node->right, words);
}

void Dictionary::insert(const std::string& word) {
    insertRecursive(root, word);
}

bool Dictionary::search(const std::string& word) const {
    return searchRecursive(root, word);
}

void Dictionary::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Nie można otworzyć pliku słownika: " << filepath << std::endl;
        return;
    }
    
    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            word.erase(word.find_last_not_of(" \n\r\t") + 1);
            if (!word.empty()) {
                insert(word);
            }
        }
    }
    
    file.close();
    std::cout << "Załadowano " << nodeCount << " słów do słownika." << std::endl;
}

std::vector<std::string> Dictionary::getAllWords() const {
    std::vector<std::string> words;
    collectWordsRecursive(root, words);
    return words;
}

void Dictionary::display() const {
    std::cout << "Słownik zawiera " << nodeCount << " słów:" << std::endl;
    std::cout << std::endl;
}

void WordLengthList::addWord(const std::string& word) {
    size_t length = word.length();
    
    while (wordsByLength.size() <= length) {
        wordsByLength.push_back(std::list<std::string>());
    }
    
    auto it = wordsByLength.begin();
    std::advance(it, length);
    it->push_back(word);
    totalWords++;
}

std::list<std::string> WordLengthList::getWordsByLength(size_t length) const {
    if (length < wordsByLength.size()) {
        auto it = wordsByLength.begin();
        std::advance(it, length);
        return *it;
    }
    return std::list<std::string>();
}

void WordLengthList::display() const {
    std::cout << "Lista słów według długości (łącznie " << totalWords << " słów):" << std::endl;
    size_t length = 0;
    for (const auto& list : wordsByLength) {
        if (!list.empty()) {
            std::cout << "Długość " << length << ": " << list.size() << " słów" << std::endl;
        }
        length++;
    }
}

int LevenshteinCalculator::calculateDistance(const std::string& str1, const std::string& str2) {
    const size_t len1 = str1.size();
    const size_t len2 = str2.size();
    
    std::vector<std::vector<int>> matrix(len1 + 1, std::vector<int>(len2 + 1));
    
    for (size_t i = 0; i <= len1; ++i) {
        matrix[i][0] = static_cast<int>(i);
    }
    for (size_t j = 0; j <= len2; ++j) {
        matrix[0][j] = static_cast<int>(j);
    }
    
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            int cost = (str1[i-1] == str2[j-1]) ? 0 : 1;
            
            matrix[i][j] = std::min({
                matrix[i-1][j] + 1,      
                matrix[i][j-1] + 1,     
                matrix[i-1][j-1] + cost 
            });
        }
    }
    
    return matrix[len1][len2];
}

std::vector<std::string> FileProcessor::readWords() const {
    std::vector<std::string> words;
    std::ifstream file(inputPath);
    
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << inputPath << std::endl;
        return words;
    }
    
    std::string word;
    while (file >> word) {
        //ispunct - sprawdza czy to znak interpunkcyjny
        while (!word.empty() && std::ispunct(word.back())) {
            word.pop_back();
        }
        
        while (!word.empty() && std::ispunct(word.front())) {
            word.erase(0, 1);
        }
        
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    
    file.close();
    return words;
}

void FileProcessor::writeResults(const std::vector<std::string>& correctedWords, const std::vector<Correction>& corrections) const {
    std::ofstream outFile(outputPath);
    if (outFile.is_open()) {
        for (size_t i = 0; i < correctedWords.size(); ++i) {
            outFile << correctedWords[i];
            if (i < correctedWords.size() - 1) {
                outFile << " ";
            }
        }
        outFile << std::endl;
        outFile.close();
        std::cout << "Poprawiony tekst zapisano do: " << outputPath << std::endl;
    }
    
    std::string reportPath = outputPath.substr(0, outputPath.find_last_of('.')) + "_zmiany.txt";
    std::ofstream reportFile(reportPath);
    if (reportFile.is_open()) {
        reportFile << "Poprawione słowa:\n";
        
        if (corrections.empty()) {
            reportFile << "Nie znaleziono błędów.\n";
        } else {
            for (const auto& corr : corrections) {
                reportFile << corr << "\n";
            }
        }
        
        reportFile.close();
        std::cout << "Wykres zmian zapisano do pliku: " << reportPath << std::endl;
    }
}

void FileProcessor::readFromStream(std::istream& is) {
    std::cout << "Podaj ścieżkę pliku wejściowego: ";
    is >> inputPath;
    std::cout << "Podaj ścieżkę pliku wyjściowego: ";
    is >> outputPath;
}

void FileProcessor::writeToStream(std::ostream& os) const {
    os << "Input: " << inputPath << ", Output: " << outputPath;
}

std::istream& operator>>(std::istream& is, FileProcessor& fp) {
    fp.readFromStream(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const FileProcessor& fp) {
    fp.writeToStream(os);
    return os;
}


GrammarCorrector::GrammarCorrector(const std::string& dictionaryPath) : dictionary(std::make_unique<Dictionary>()),
    wordStack(std::make_unique<WordStack>()),
    correctionQueue(std::make_unique<CorrectionQueue>()),
    wordLengthList(std::make_unique<WordLengthList>()),
    calculator(std::make_unique<LevenshteinCalculator>()) {
    std::cout << "Ładowanie słownika" << std::endl;
    dictionary->loadFromFile(dictionaryPath);
    preprocessDictionary();
}

void GrammarCorrector::preprocessDictionary() {
    std::cout << "Przetwarzanie słownika" << std::endl;
    auto words = dictionary->getAllWords();
    
    for (const auto& word : words) {
        wordLengthList->addWord(word);
    }
    
    std::cout << "Słownik przetworzony." << std::endl;
}

std::string GrammarCorrector::findBestMatch(const std::string& word) const {
    if (word.length() <= 1) {
        return word;
    }
    
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    
    if (dictionary->search(lowerWord)) {
        return word; 
    }
    
    std::vector<std::string> diacriticVariants = getAllDiacriticVariants(lowerWord);
    if (!diacriticVariants.empty()) {
        return preserveCase(word, diacriticVariants[0]);
    }
    std::string bestMatch = word;
    int minDistance = std::numeric_limits<int>::max();
    
    for (int lengthDiff = 0; lengthDiff <= 2; ++lengthDiff) {
        for (int sign : {-1, 1}) {
            if (lengthDiff == 0 && sign == 1) continue;
            
            size_t targetLength = lowerWord.length() + sign * lengthDiff;
            if (sign == -1 && targetLength > lowerWord.length()) continue;
            
            auto similarWords = wordLengthList->getWordsByLength(targetLength);
            
            for (const auto& dictWord : similarWords) {
                if (dictWord.length() <= 1) {
                    continue;
                }
                
                int distance = calculator->calculateDistance(lowerWord, dictWord);
                
                if (distance < minDistance) {
                    minDistance = distance;
                    bestMatch = preserveCase(word, dictWord);
                    
                    if (distance <= 1) {
                        return bestMatch;
                    }
                }
            }
        }
        
        if (minDistance <= 2) break;
    }
    
    return bestMatch;
}

// std::vector<std::string> GrammarCorrector::getAllDiacriticVariants(const std::string& word) const {
//     std::map<char, std::vector<std::string>> diacriticMap = {
//         {'a', {"ą"}}, {'e', {"ę"}}, {'c', {"ć"}}, 
//         {'l', {"ł"}}, {'n', {"ń"}}, {'o', {"ó"}}, 
//         {'s', {"ś"}}, {'z', {"ź", "ż"}}
//     };
    
//     std::vector<std::string> foundVariants;
    
//     std::function<void(std::string, size_t)> generateCombinations = [&](std::string current, size_t pos) {
//         if (pos >= word.length()) {
//             if (current != word && dictionary->search(current)) {
//                 foundVariants.push_back(current);
//             }
//             return;
//         }
        
//         char c = word[pos];
        
//         generateCombinations(current, pos + 1);
        
//         if (diacriticMap.find(c) != diacriticMap.end()) {
//             for (const std::string& variant : diacriticMap[c]) {
//                 std::string newCurrent = current;
//                 newCurrent.replace(pos, 1, variant);
//                 generateCombinations(newCurrent, pos + 1);
//             }
//         }
//     };
    
//     generateCombinations(word, 0);
//     return foundVariants;
// }

std::vector<std::string> GrammarCorrector::getAllDiacriticVariants(const std::string& word) const {
    std::map<char, std::vector<std::string>> diacriticMap = {
        {'a', {"ą"}}, {'e', {"ę"}}, {'c', {"ć"}}, 
        {'l', {"ł"}}, {'n', {"ń"}}, {'o', {"ó"}}, 
        {'s', {"ś"}}, {'z', {"ź", "ż"}}
    };
    
    std::vector<std::string> foundVariants;
    
    generateDiacriticCombinations(word, "", 0, diacriticMap, foundVariants);
    
    return foundVariants;
}

void GrammarCorrector::generateDiacriticCombinations(
    const std::string& word, 
    std::string current, 
    size_t pos,
    const std::map<char, std::vector<std::string>>& diacriticMap,
    std::vector<std::string>& foundVariants) const {
    
    if (pos >= word.length()) {
        if (current != word && dictionary->search(current)) {
            foundVariants.push_back(current);
        }
        return;
    }
    
    char c = word[pos];
    
    generateDiacriticCombinations(word, current + c, pos + 1, diacriticMap, foundVariants);
    
    if (diacriticMap.find(c) != diacriticMap.end()) {
        for (const std::string& variant : diacriticMap.at(c)) {
            generateDiacriticCombinations(word, current + variant, pos + 1, diacriticMap, foundVariants);
        }
    }
}

std::string GrammarCorrector::preserveCase(const std::string& original, const std::string& corrected) const {
    if (original.empty() || corrected.empty()) {
        return corrected;
    }
    
    std::string result = corrected;
    
    if (std::isupper(original[0])) {
        result[0] = std::toupper(result[0]);
    }
    
    return result;
}

std::string GrammarCorrector::correctPolishDiacritics(const std::string& word) const {
    auto variants = getAllDiacriticVariants(word);
    return variants.empty() ? word : variants[0];
}

void GrammarCorrector::correctFile(const std::string& inputPath, const std::string& outputPath) {
    fileProcessor = std::make_unique<FileProcessor>(inputPath, outputPath);
    
    std::cout << "Czytanie pliku" << std::endl;
    auto words = fileProcessor->readWords();
    
    if (words.empty()) {
        std::cout << "Plik jest pusty lub nie można go odczytać." << std::endl;
        return;
    }
    
    // Slowa na stos, ale w odwrotnej kolejnosci, bo ze stosu sciaga sie od gory, iteratory, rbegin- reverse begin iterator, rend-reverse end iterator
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        wordStack->push(*it);
    }
    
    std::vector<std::string> correctedWords;
    std::vector<Correction> corrections;
    
    std::cout << "Poprawianie tekstu" << std::endl;
    
    while (!wordStack->empty()) {
        std::string originalWord = wordStack->pop();
        std::string correctedWord = findBestMatch(originalWord);
        
        correctedWords.push_back(correctedWord);
        
        if (originalWord != correctedWord) {
            int distance = calculator->calculateDistance(originalWord, correctedWord);
            Correction corr(originalWord, correctedWord, distance);
            corrections.push_back(corr);
            correctionQueue->enqueue(corr);
            
            std::cout << "Poprawiono: " << corr << std::endl;
        }
    }
    
    std::cout << "Zapisywanie wyników" << std::endl;
    fileProcessor->writeResults(correctedWords, corrections);
    
    std::cout << "Korekta zakończona" << std::endl;
    std::cout << "Poprawiono " << corrections.size() << " słów z " << words.size() << " ogółem." << std::endl;
}

void GrammarCorrector::displayStatistics() const {
    std::cout << "\nStatystyki:" << std::endl;
    dictionary->display();
    wordLengthList->display();
    wordStack->display();
    correctionQueue->display();
}

GrammarCorrector& GrammarCorrector::operator+(const std::string& word) {
    dictionary->insert(word);
    wordLengthList->addWord(word);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Correction& corr) {
    corr.writeToStream(os);
    return os;
}