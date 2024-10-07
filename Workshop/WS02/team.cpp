//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#include "team.h"

namespace seneca {
    Team::Team() {

    }

    Team::Team(const char* name) {
        m_name = name;
    }

    Team::Team(const Team& src) {
        *this = src;
    }

    Team& Team::operator=(const Team& src) {
        if (this != &src) {
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                delete m_characters[i];
            }
            delete[] m_characters;

            m_name = src.m_name;
            m_characters = new Character*[src.m_numberOfCharacters];
            m_numberOfCharacters = src.m_numberOfCharacters;
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                m_characters[i] = src.m_characters[i]->clone();
            }
        }

        return *this;
    }

    Team::~Team() {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            delete m_characters[i];
        }
        delete[] m_characters;
    }

    Team::Team(Team&& src) {
        *this = std::move(src);
    }

    Team& Team::operator=(Team&& src) {
        if (this != &src) {
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                delete m_characters[i];
            }
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

    int Team::findMember(const std::string &name) {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            if (m_characters[i]->getName() == name) {
                return i;
            }
        }

        return -1;
    }

    void Team::addMember(const Character* c) {
        int idx = findMember(c->getName());
        if (idx >= 0)
            return;

        m_numberOfCharacters++;
        Character** characters = new Character*[m_numberOfCharacters];
        for (int i = 0; i < m_numberOfCharacters - 1; ++i) {
            characters[i] = m_characters[i];
        }
        characters[m_numberOfCharacters - 1] = c->clone();
        delete[] m_characters;

        m_characters = characters;
    }

    void Team::removeMember(const std::string& c) {
        int idx = findMember(c);
        if (idx < 0)
            return;

        delete m_characters[idx];
        for (int i = idx; i < m_numberOfCharacters - 1; ++i) {
            m_characters[i] = m_characters[i + 1];
        }

        m_numberOfCharacters--;
    }

    Character* Team::operator[](size_t idx) const {
        if (idx > size_t(m_numberOfCharacters - 1))
            return nullptr;
        return m_characters[idx];
    }

    void Team::showMembers() const {
        if (m_name.empty() && m_numberOfCharacters == 0)
            std::cout << "No team." << std::endl;
        else {
            std::cout << "[Team] " << m_name << std::endl;
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_characters[i]) << std::endl;
            }
        }
    }
}