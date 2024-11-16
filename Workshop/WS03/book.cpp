//
// Created by Beomgu Jeon on 2024-11-05.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include "settings.h"
#include "book.h"

namespace seneca {
    Book::Book(const std::string &author, const std::string &title, const std::string &country, double price,
               unsigned short year, const std::string &summary) : MediaItem(title, summary, year) {
        m_author = author;
        m_country = country;
        m_price = price;
    }

    void Book::display(std::ostream &out) const {
        if (g_settings.m_tableView) {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            } else
                out << this->getSummary();
            out << std::endl;
        } else {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    Book *Book::createItem(const std::string &strBook) {
        if (strBook.empty() || strBook.front() == '#') {
            throw "Not a valid book.";
        }

        size_t start{};
        size_t end{};
        size_t index = 0;
        std::string str[6];

        while (end != std::string::npos) {
            if (index > 5) {
                break;
            }
            start = end != 0 ? end + 1 : 0;
            end = strBook.find(',', start);
            std::string temp;
            if (index != 5) {
                temp = strBook.substr(start, (end - start));
            } else {
                temp = strBook.substr(start);
            }
            trim(temp);
            str[index] = temp;
            index++;
        }

        return new Book(str[0], str[1], str[2], std::stod(str[3]), std::stoi(str[4]), str[5]);
    }
}