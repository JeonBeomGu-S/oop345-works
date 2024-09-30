//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include <cstring>
#include "event.h"

namespace seneca {
    Event::Event() {

    }

    Event::Event(const char *name, const std::chrono::nanoseconds &duration) {
        if (name) {
            m_name = name;
        }
        m_duration = duration;
    }

    std::string Event::getName() const {
        return m_name;
    }

    std::chrono::nanoseconds Event::getDuration() const {
        return m_duration;
    }

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static int counter = 0;
        counter++;
        os.width(2);
        os << std::right << counter << ": ";
        os.width(40);
        os << std::right << event.getName();
        os << " -> ";
        std::string timeUnits = g_settings.m_time_units;
        if (timeUnits == "seconds") {
            os.width(2);
            os << std::chrono::duration_cast<std::chrono::seconds>(event.getDuration()).count();
        } else if (timeUnits == "milliseconds") {
            os.width(5);
            os << std::chrono::duration_cast<std::chrono::milliseconds>(event.getDuration()).count();
        } else if (timeUnits == "microseconds") {
            os.width(8);
            os << std::chrono::duration_cast<std::chrono::microseconds>(event.getDuration()).count();
        } else if (timeUnits == "nanoseconds") {
            os.width(11);
            os << event.getDuration().count();
        }

        os << " " << g_settings.m_time_units;

        return os;
    }
}