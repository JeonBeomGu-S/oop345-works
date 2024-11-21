//
// Created by Beomgu Jeon on 2024-11-19.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() {

    }

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities util;
        size_t nextPos {0};
        bool more = true;


        m_name = util.extractToken(str, nextPos, more);
        m_product = util.extractToken(str, nextPos, more);
        while (more) {
            std::string itemName = util.extractToken(str, nextPos, more);
            if (!itemName.empty()) {
                m_cntItem++;
                Item **lstItem = new Item*[m_cntItem];
                for (int i = 0; i < m_cntItem - 1; ++i) {
                    lstItem[i] = m_lstItem[i];
                }
                lstItem[m_cntItem - 1] = new Item(itemName);
                delete[] m_lstItem;

                m_lstItem = lstItem;
            }
        }

        m_widthField = util.getFieldWidth() > m_widthField ? util.getFieldWidth() : m_widthField;
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw "Custom Order Copy Constructor Exception";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            for (auto i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }

            delete[] m_lstItem;

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;
        }

        src.m_name = "";
        src.m_product = "";
        src.m_cntItem = 0;
        src.m_lstItem = nullptr;

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (int i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }

        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (auto i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled)
                return false;
        }

        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (auto i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName)
                return m_lstItem[i]->m_isFilled;
        }

        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        if (m_cntItem == 0)
            return;

        for (auto i = 0; i < m_cntItem; ++i) {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                    break;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                    break;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (auto i = 0; i < m_cntItem; ++i) {
            os << "[";
            os << std::setfill('0');
            os << std::setw(6) << m_lstItem[i]->m_serialNumber;
            os << std::setfill(' ');
            os << "] ";
            os << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}