//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <iostream>
#include <string>

namespace seneca {
    class Utilities {
        size_t m_widthField {1};
        static std::string m_delimiter;

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        static void trim(std::string& str);
    };
}


#endif // SENECA_UTILITIES_H
