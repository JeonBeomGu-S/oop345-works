//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include "logger.h"

namespace seneca {
    logger::logger() {

    }

    logger::~logger() {
        delete[] m_eventArr;
    }

    logger &logger::operator=(logger &&src) {
        if (this != &src) {
            delete[] m_eventArr;
            m_eventArr = src.m_eventArr;
            src.m_eventArr = nullptr;

            m_numOfEvents = src.m_numOfEvents;
            src.m_numOfEvents = 0;
        }

        return *this;
    }

    void logger::addEvent(const event &e) {
        m_numOfEvents++;
        event* tmp = new event[m_numOfEvents];
        for (int i = 0; i < m_numOfEvents - 1; ++i) {
            tmp[i] = m_eventArr[i];
        }
        delete[] m_eventArr;
        m_eventArr = tmp;
        m_eventArr[m_numOfEvents - 1] = e;
    }

    event* logger::getEventArr() const {
        return m_eventArr;
    }

    int logger::getEventArrSize() const {
        return m_numOfEvents;
    }

    std::ostream& operator<<(std::ostream& os, const logger& logger) {
        event* eventArr = logger.getEventArr();
        for (int i = 0; i < logger.getEventArrSize(); ++i) {
            os << eventArr[i] << std::endl;
        }
        return os;
    }
}