//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <iostream>
#include <chrono>
#include "event.h"

namespace seneca {
    class timeMonitor {
        std::string m_name{};
        std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    public:
        void startEvent(const char* name);
        event stopEvent();
    };
}


#endif //SENECA_TIMEMONITOR_H
