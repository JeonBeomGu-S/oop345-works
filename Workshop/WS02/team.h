//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Team {
        std::string m_name{};
        Character** m_characters{};
        int m_numberOfCharacters{};

    public:
        Team();
        Team(const char* name);

        Team(const Team& src);
        Team& operator=(const Team& src);
        ~Team();
        Team(Team&& src);
        Team& operator=(Team&& src);

        int findMember(const std::string& name);
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}


#endif // SENECA_TEAM_H
