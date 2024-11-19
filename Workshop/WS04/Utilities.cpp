//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include "Utilities.h"

namespace seneca {
    std::string Utilities::m_delimiter = {};

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        size_t index = str.find(m_delimiter, next_pos);
        std::string result{};

        if (index == next_pos) {
            more = false;
            throw "No token.";
        }

        if (index != std::string::npos) {
            result = str.substr(next_pos, index - next_pos);
            Utilities::trim(result);
            next_pos = index + 1;
            more = true;
        } else {
            result = str.substr(next_pos);
            Utilities::trim(result);
            more = false;
        }

        m_widthField = result.length() > m_widthField ? result.length() : m_widthField;

        return result;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter.c_str()[0];
    }

    void Utilities::trim(std::string &str) {
        size_t i = 0u;
        for (i = 0u; i < str.length() && str[i] == ' '; ++i);
        str = str.substr(i);

        for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
        str = str.substr(0, i);
    }
}