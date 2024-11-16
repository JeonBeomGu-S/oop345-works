//
// Created by Beomgu Jeon on 2024-11-10.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <iostream>
#include <string>

namespace seneca {
    class SpellChecker {
        std::string m_badWords[6]{};
        std::string m_goodWords[6]{};
        int m_changedCnt[6]{};
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}

#endif // SENECA_SPELLCHECKER_H