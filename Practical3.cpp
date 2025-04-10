#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <regex>

using namespace std;

unordered_set<string> keywords = {"int", "char", "return", "if", "else", "while", "for", "main"};
unordered_set<char> punctuation = {';', ',', '{', '}', '(', ')'};
unordered_set<string> operators = {"=", "+", "-", "*", "/"};
vector<string> symbolTable;
unordered_map<string, string> tokens;
vector<string> lexicalErrors;

bool isKeyword(const string &word) {
    return keywords.find(word) != keywords.end();
}

bool isIdentifier(const string &word) {
    return regex_match(word, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

bool isConstant(const string &word) {
    return regex_match(word, regex("[0-9]+"));
}

bool isCharConstant(const string &word) {
    return regex_match(word, regex("'.'"));
}

void addToSymbolTable(const string &identifier) {
    if (!isKeyword(identifier) && find(symbolTable.begin(), symbolTable.end(), identifier) == symbolTable.end()) {
        symbolTable.push_back(identifier);
    }
}

void tokenize(const string &word) {
    if (word.empty()) return;
    if (isKeyword(word)) {
        tokens[word] = "Keyword";
    } else if (isConstant(word)) {
        tokens[word] = "Constant";
    } else if (isCharConstant(word)) {
        tokens[word] = "Character Constant";
    } else if (isIdentifier(word)) {
        tokens[word] = "Identifier";
        addToSymbolTable(word);
    } else {
        lexicalErrors.push_back(word + " invalid lexeme");
    }
}

void processFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line, word;
    bool multiLineComment = false;
    bool inCharConstant = false;

    while (getline(file, line)) {
        size_t i = 0;
        while (i < line.length()) {
            if (multiLineComment) {
                if (line.substr(i, 2) == "*/") {
                    multiLineComment = false;
                    i += 2;
                } else {
                    i++;
                }
                continue;
            }

            if (line.substr(i, 2) == "/*") {
                multiLineComment = true;
                i += 2;
                continue;
            }
            
            if (line.substr(i, 2) == "//") break;
            
            if (line[i] == '\'') {
                if (!inCharConstant && i + 2 < line.length() && line[i+2] == '\'') {
                    tokenize(line.substr(i, 3));
                    i += 3;
                    continue;
                }
            }
            
            if (isspace(line[i])) {
                tokenize(word);
                word.clear();
            } else if (punctuation.find(line[i]) != punctuation.end()) {
                tokenize(word);
                word.clear();
                tokens[string(1, line[i])] = "Punctuation";
            } else if (operators.find(string(1, line[i])) != operators.end()) {
                tokenize(word);
                word.clear();
                tokens[string(1, line[i])] = "Operator";
            } else {
                word += line[i];
            }
            i++;
        }
        tokenize(word);
        word.clear();
    }

    file.close();
}

void displayResults() {
    cout << "TOKENS" << endl;
    for (const auto &pair : tokens) {
        cout << pair.second << ": " << pair.first << endl;
    }
    
    cout << "\nLEXICAL ERRORS" << endl;
    for (const auto &error : lexicalErrors) {
        cout << error << endl;
    }
    
    cout << "\nSYMBOL TABLE ENTRIES" << endl;
    for (size_t i = 0; i < symbolTable.size(); i++) {
        cout << i + 1 << ") " << symbolTable[i] << endl;
    }
}

int main() {
    string filename;
    cout << "Enter source code filename: ";
    cin >> filename;
    processFile(filename);
    displayResults();
    return 0;
}



// #include <bits/stdc++.h>
// using namespace std;

// // Predefined arrays for keywords, operators, and punctuations
// const unordered_set<string> keywords = {
//     "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
//     "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
//     "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
//     "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Bool",
//     "_Complex", "_Imaginary"
// };

// const unordered_set<string> operators = {
//     "+", "-", "", "/", "%", "++", "--", "=", "+=", "-=", "=", "/=", "%=", "==", "!=",
//     ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"
// };

// const unordered_set<string> punctuations = {
//     "(", ")", "{", "}", "[", "]", ";", ":", ",", ".", "->", "..."
// };

// // Function to classify a token
// string classifyToken(const string &token) {
//     if (keywords.count(token)) {
//         return "keyword";
//     }
//     if (operators.count(token)) {
//         return "operator";
//     }
//     if (punctuations.count(token)) {
//         return "punctuation";
//     }
//     if (isalpha(token[0]) || token[0] == '_') { // Starts with a letter or ''
//         return "identifier";
//     }
//     if (isdigit(token[0])) { // Starts with a digit
//         return "constant";
//     }
//     return "unknown";
// }

// int main() {
//     ifstream file("Pr_3_input.txt");
//     if (!file) {
//         cerr << "Error: Unable to open file!" << endl;
//         return 1;
//     }

//     string line;
//     int wordCount = 0;
//     vector<string> v;
//     bool inMultilineComment = false;

//     while (getline(file, line)) {
//         istringstream stream(line);
//         string word;

//         while (stream >> word) {
//             if (inMultilineComment) {
//                 if (word.find("*/") != string::npos) {
//                     inMultilineComment = false;
//                 }
//                 continue;
//             }

//             if (word.find("//") != string::npos) {
//                 break;
//             }
//             if (word.find("/*") != string::npos) {
//                 inMultilineComment = true;
//                 continue;
//             }

//             string temp;
//             for (char c : word) {
//                 if (isalnum(c) || c == '\'' || c == '_') {
//                     temp += c;
//                 } else {
//                     if (!temp.empty()) {
//                         v.push_back(temp);
//                         wordCount++;
//                         temp.clear();
//                     }
//                     v.push_back(string(1, c));
//                     wordCount++;
//                 }
//             }
//             if (!temp.empty()) {
//                 v.push_back(temp);
//                 wordCount++;
//             }
//         }
//     }

//     cout << "Total words: " << wordCount << endl;
//     cout << "\nClassified Tokens:\n";

//     // Classify and display tokens
//     for (const auto &token : v) {
//         cout << token << " = " << classifyToken(token) << endl;
//     }

//     file.close();
//     return 0;
// }
