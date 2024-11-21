//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace seneca {

    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };


    class CustomerOrder {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder& src); // throw error
        CustomerOrder& operator=(const CustomerOrder& src) = delete;
        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;


    };
}


#endif // SENECA_CUSTOMERORDER_H
