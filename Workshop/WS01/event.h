//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <string>
#include <chrono>
#include "settings.h"

namespace seneca {
    class Event {
        std::string m_name{};
        std::chrono::nanoseconds m_duration{};
    public:
        Event();
        Event(const char* name, const std::chrono::nanoseconds& duration);
        std::string getName() const;
        std::chrono::nanoseconds getDuration() const;
    };
    std::ostream &operator<<(std::ostream &os, const Event &event);
}

#endif //SENECA_EVENT_H
