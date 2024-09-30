//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <chrono>
#include "timeMonitor.h"

namespace seneca {
    void TimeMonitor::startEvent(const char* name) {
        m_name = name;
        m_startTime = std::chrono::steady_clock::now();
    }
    Event TimeMonitor::stopEvent() {
        std::chrono::time_point<std::chrono::steady_clock> endTime = std::chrono::steady_clock::now();
        std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);
        Event event(m_name.c_str(), duration);
        return event;
    }
}