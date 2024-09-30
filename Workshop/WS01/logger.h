//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca {
    class logger {
        event* m_eventArr{};
        int m_numOfEvents{};
    public:
        logger();
        ~logger();
        logger& operator=(logger&& src);
        // disable copy operations
        logger& operator=(logger& src) = delete;
        logger(logger& src) = delete;
        void addEvent(const event& event);
        event* getEventArr() const;
        int getEventArrSize() const;
    };

    std::ostream& operator<<(std::ostream& os, const logger& logger);
}


#endif //SENECA_LOGGER_H
