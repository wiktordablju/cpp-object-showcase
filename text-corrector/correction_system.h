#ifndef CORRECTION_SYSTEM_H
#define CORRECTION_SYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <list>
#include <map>

class DataStructure {
public:
    virtual ~DataStructure() = default;
    virtual void display() const = 0;
    virtual size_t size() const = 0;
};

class TreeNode {
public:
    std::string word;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    
    TreeNode(const std::string& w) : word(w), left(nullptr), right(nullptr) {}
};

class Dictionary : public DataStructure {
private:
    std::shared_ptr<TreeNode> root;
    size_t nodeCount;
    
    void insertRecursive(std::shared_ptr<TreeNode>& node, const std::string& word);
    bool searchRecursive(const std::shared_ptr<TreeNode>& node, const std::string& word) const;
    void displayRecursive(const std::shared_ptr<TreeNode>& node) const;
    void collectWordsRecursive(const std::shared_ptr<TreeNode>& node, std::vector<std::string>& words) const;

public:
    Dictionary() : root(nullptr), nodeCount(0) {}
    void insert(const std::string& word);
    bool search(const std::string& word) const;
    void loadFromFile(const std::string& filepath);
    std::vector<std::string> getAllWords() const;
    void display() const override;
    size_t size() const override { return nodeCount; }
};

class Correction {
    public:
        std::string original;
        std::string corrected;
        int distance;
        
        Correction(const std::string& orig, const std::string& corr, int dist) : original(orig), corrected(corr), distance(dist) {}
        
        bool operator==(const Correction& other) const {
            return original == other.original && corrected == other.corrected;
        }
        
        void writeToStream(std::ostream& os) const {
            os << original << " -> " << corrected << " (distance: " << distance << ")";
        }
    };
    std::ostream& operator<<(std::ostream& os, const Correction& corr);

class WordStack : public DataStructure {
private:
    std::stack<std::string> words;
public:
    void push(const std::string& word) { words.push(word); }
    std::string pop() { 
        if (!words.empty()) {
            std::string word = words.top();
            words.pop();
            return word;
        }
        return "";
    }
    bool empty() const { return words.empty(); }
    
    void display() const override {
        std::cout << "Stack contains " << words.size() << " words\n";
    }
    
    size_t size() const override { return words.size(); }
};

class CorrectionQueue : public DataStructure {
private:
    std::queue<Correction> corrections;

public:
    void enqueue(const Correction& corr) { corrections.push(corr); }
    bool empty() const { return corrections.empty(); }
    
    void display() const override {
        std::cout << "Queue contains " << corrections.size() << " corrections\n";
    }
    
    size_t size() const override { return corrections.size(); }
};

class WordLengthList : public DataStructure {
private:
    std::list<std::list<std::string>> wordsByLength;
    size_t totalWords;

public:
    WordLengthList() : totalWords(0) {}
    
    void addWord(const std::string& word);
    std::list<std::string> getWordsByLength(size_t length) const;
    
    void display() const override;
    size_t size() const override { return totalWords; }
};

class LevenshteinCalculator {
public:
    static int calculateDistance(const std::string& str1, const std::string& str2);
    
    int operator()(const std::string& str1, const std::string& str2) const {
        return calculateDistance(str1, str2);
    }
};

class FileProcessor {
    private:
        std::string inputPath;
        std::string outputPath;
        
    public:
        FileProcessor(const std::string& input, const std::string& output) 
            : inputPath(input), outputPath(output) {}
        
        std::string getInputPath() const { return inputPath; }
        std::string getOutputPath() const { return outputPath; }
        void setInputPath(const std::string& path) { inputPath = path; }
        void setOutputPath(const std::string& path) { outputPath = path; }
        
        std::vector<std::string> readWords() const;
        void writeResults(const std::vector<std::string>& correctedWords, 
                         const std::vector<Correction>& corrections) const;
        
        void readFromStream(std::istream& is);
        void writeToStream(std::ostream& os) const;
    };
    
    std::istream& operator>>(std::istream& is, FileProcessor& fp);
    std::ostream& operator<<(std::ostream& os, const FileProcessor& fp);

class GrammarCorrector {
private:
    std::unique_ptr<Dictionary> dictionary;
    std::unique_ptr<WordStack> wordStack;
    std::unique_ptr<CorrectionQueue> correctionQueue;
    std::unique_ptr<WordLengthList> wordLengthList;
    std::unique_ptr<LevenshteinCalculator> calculator;
    std::unique_ptr<FileProcessor> fileProcessor;
    std::string preserveCase(const std::string& original, const std::string& corrected) const;
    std::string findBestMatch(const std::string& word) const;
    std::string correctPolishDiacritics(const std::string& word) const;
    std::vector<std::string> getAllDiacriticVariants(const std::string& word) const;
    void generateDiacriticCombinations(
        const std::string &word,
        std::string current,
        size_t pos,
        const std::map<char, std::vector<std::string>> &diacriticMap,
        std::vector<std::string> &foundVariants) const;
    void preprocessDictionary();

public:
    GrammarCorrector(const std::string& dictionaryPath);
    ~GrammarCorrector() = default;
    void correctFile(const std::string& inputPath, const std::string& outputPath);
    void displayStatistics() const;
    GrammarCorrector& operator+(const std::string& word);
};

#endif
