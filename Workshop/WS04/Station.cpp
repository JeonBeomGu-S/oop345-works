//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& str) {
        Utilities util;
        size_t nextPos = 0;
        bool more = true;

        for (int i = 0; i < 4; ++i) {
            if (i == 3) {
                more = false;
                Station::m_widthField = util.getFieldWidth() > Station::m_widthField ? util.getFieldWidth() : Station::m_widthField;
            }
            std::string temp = util.extractToken(str, nextPos, more);
            switch (i) {
                case 0:
                    m_name = temp;
                    break;
                case 1:
                    m_serial = std::stoi(temp);
                    break;
                case 2:
                    m_numberOfItems = std::stoi(temp);
                    break;
                case 3:
                    m_desc = temp;
                    break;
            }
        }

        m_id = ++id_generator;
    }

    const std::string& Station::getItemName() const {
        return m_name;
    }
    size_t Station::getNextSerialNumber() {
        return m_serial++;
    }
    size_t Station::getQuantity() const {
        return m_numberOfItems;
    }
    void Station::updateQuantity() {
        if (m_numberOfItems >= 1)
            m_numberOfItems -= 1;
    }
    void Station::display(std::ostream& os, bool full) const {
        std::cout << std::setfill('0');
        os << std::right << std::setw(3) << m_id;
        std::cout << std::setfill(' ');
        os << " | ";
        os << std::left << std::setw(m_widthField) << m_name;
        os << " | ";
        std::cout << std::setfill('0');
        os << std::right << std::setw(6) << m_serial;
        std::cout << std::setfill(' ');
        os << " | ";
        if (!full) {
             os << std::endl;
        } else {
            os << std::setw(4) << m_numberOfItems;
            os << " | " << m_desc << std::endl;
        }
    }

}