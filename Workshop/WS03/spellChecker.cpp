//
// Created by Beomgu Jeon on 2024-11-10.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include <fstream>
#include "spellChecker.h"

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream ifs(filename);
        std::string str;
        if (ifs.is_open()) {
            for (int i = 0; i < 6; ++i) {
                ifs >> m_badWords[i] >> m_goodWords[i];
            }
            ifs.close();
        } else {
            throw "Bad file name!";
        }
    }
    void SpellChecker::operator()(std::string& text) {
        for (int i = 0; i < 6; ++i) {
            size_t start{};
            size_t end{};

            while (end != std::string::npos) {
                start = end != 0 ? end + 1 : 0;
                end = text.find(m_badWords[i], start);
                if (end != std::string::npos) {
                    text.replace(end, m_badWords[i].length(), m_goodWords[i]);
                    m_changedCnt[i]++;
                }
            }
        }
    }
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics" << std::endl;
        for (int i = 0; i < 6; ++i) {
            out << std::left << std::setw(15)<< m_badWords[i];
            out << ": " << m_changedCnt[i] << " replacements" << std::endl;
        }
    }
}