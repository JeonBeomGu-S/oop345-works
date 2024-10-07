//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Guild {
        std::string m_name{};
        Character** m_characters{};
        int m_numberOfCharacters{};
    public:
        Guild();
        Guild(const char* name);

        Guild(const Guild& src);
        Guild& operator=(const Guild& src);
        ~Guild();
        Guild(Guild&& src);
        Guild& operator=(Guild&& src);

        int findMember(const std::string &name);
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}

#endif // SENECA_GUILD_H
