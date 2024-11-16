//
// Created by Beomgu Jeon on 2024-11-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include "movie.h"
#include "settings.h"

namespace seneca {
    Movie::Movie(const std::string& title, unsigned short year, const std::string& summary) : MediaItem(title, summary, year) {

    }

    void Movie::display(std::ostream &out) const {
        if (g_settings.m_tableView) {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    Movie* Movie::createItem(const std::string& strMovie) {
        if (strMovie.empty() || strMovie.front() == '#') {
            throw "Not a valid movie.";
        }

        size_t start{};
        size_t end{};
        size_t index = 0;
        std::string str[3];

        while (end != std::string::npos) {
            if (index > 2) {
                break;
            }
            start = end != 0 ? end + 1 : 0;
            end = strMovie.find(',', start);
            std::string temp;
            if (index != 2) {
                temp = strMovie.substr(start, (end - start));
            } else {
                temp = strMovie.substr(start);
            }
            trim(temp);
            str[index] = temp;
            index++;
        }

        return new Movie(str[0], std::stoi(str[1]), str[2]);
    }
}