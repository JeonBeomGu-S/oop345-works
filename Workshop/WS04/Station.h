//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>

namespace seneca {
    class Station {
        int m_id{};
        std::string m_name{};
        std::string m_desc{};
        size_t m_serial{};
        size_t m_numberOfItems;
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const std::string& str);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SENECA_STATION_H
