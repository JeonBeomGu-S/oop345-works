//
// Created by Beomgu Jeon on 2024-11-05.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {
    struct Settings {
        short m_maxSummaryWidth = 80;
        bool m_tableView = false;
    };
    extern Settings g_settings;
}


#endif //SENECA_SETTINGS_H
