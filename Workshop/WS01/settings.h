//
// Created by Beomgu Jeon on 2024-09-15.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <iostream>
#include <string>

namespace seneca {
    struct settings {
        bool m_show_all = false;
        bool m_verbose = false;
        std::string m_time_units = "nanoseconds";
    };
    extern settings g_settings;
}


#endif //SENECA_SETTINGS_H
