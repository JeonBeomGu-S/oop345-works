//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include "guild.h"

namespace seneca {
    Guild::Guild() {

    }

    Guild::Guild(const char* name) {
        m_name = name;
    }

    Guild::Guild(const Guild& src) {
        *this = src;
    }
    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            delete[] m_characters;

            m_name = src.m_name;
            m_characters = new Character*[src.m_numberOfCharacters];
            m_numberOfCharacters = src.m_numberOfCharacters;

            for (int i = 0; i < m_numberOfCharacters; ++i) {
                m_characters[i] = src.m_characters[i];
            }
        }

        return *this;
    }

    Guild::~Guild() {
        delete[] m_characters;
    }
    Guild::Guild(Guild&& src) {
        *this = std::move(src);
    }

    Guild& Guild::operator=(Guild&& src) {
        if (this != &src) {
            delete[] m_characters;
            m_name = src.m_name;
            m_characters = src.m_characters;
            m_numberOfCharacters = src.m_numberOfCharacters;

            src.m_name = "";
            src.m_characters = nullptr;
            src.m_numberOfCharacters = 0;
        }
        return *this;
    }

    int Guild::findMember(const std::string &name) {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            if (m_characters[i]->getName() == name) {
                return i;
            }
        }

        return -1;
    }

    void Guild::addMember(Character* c) {
        int idx = findMember(c->getName());
        if (idx >= 0)
            return;

        m_numberOfCharacters++;
        Character** characters = new Character*[m_numberOfCharacters];
        for (int i = 0; i < m_numberOfCharacters - 1; ++i) {
            characters[i] = m_characters[i];
        }
        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());
        characters[m_numberOfCharacters - 1] = c;
        delete[] m_characters;

        m_characters = characters;
    }

    void Guild::removeMember(const std::string& c) {
        int idx = findMember(c);
        if (idx < 0)
            return;

        m_characters[idx]->setHealthMax(m_characters[idx]->getHealthMax() - 300);
        m_characters[idx]->setHealth(m_characters[idx]->getHealthMax());

        for (int i = idx; i < m_numberOfCharacters - 1; ++i) {
            m_characters[i] = m_characters[i + 1];
        }

        m_numberOfCharacters--;
    }

    Character* Guild::operator[](size_t idx) const {
        if (idx > size_t(m_numberOfCharacters - 1))
            return nullptr;
        return m_characters[idx];
    }

    void Guild::showMembers() const {
        if (m_name.empty() && m_numberOfCharacters == 0)
            std::cout << "No guild." << std::endl;
        else {
            std::cout << "[Guild] " << m_name << std::endl;
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_characters[i]) << std::endl;
            }
        }
    }
}