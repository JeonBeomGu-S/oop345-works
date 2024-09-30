//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include "logger.h"

namespace seneca {
    Logger::Logger() {

    }

    Logger::~Logger() {
        delete[] m_eventArr;
    }

    Logger &Logger::operator=(Logger &&src) {
        if (this != &src) {
            delete[] m_eventArr;
            m_eventArr = src.m_eventArr;
            src.m_eventArr = nullptr;

            m_numOfEvents = src.m_numOfEvents;
            src.m_numOfEvents = 0;
        }

        return *this;
    }

    void Logger::addEvent(const Event &e) {
        m_numOfEvents++;
        Event* tmp = new Event[m_numOfEvents];
        for (int i = 0; i < m_numOfEvents - 1; ++i) {
            tmp[i] = m_eventArr[i];
        }
        delete[] m_eventArr;
        m_eventArr = tmp;
        m_eventArr[m_numOfEvents - 1] = e;
    }

    Event* Logger::getEventArr() const {
        return m_eventArr;
    }

    int Logger::getEventArrSize() const {
        return m_numOfEvents;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        Event* eventArr = logger.getEventArr();
        for (int i = 0; i < logger.getEventArrSize(); ++i) {
            os << eventArr[i] << std::endl;
        }
        return os;
    }
}