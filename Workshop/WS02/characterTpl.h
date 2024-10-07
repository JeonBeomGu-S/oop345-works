//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include "weapons.h"
#include "health.h"
#include "abilities.h"

namespace seneca {
    template <typename T>
    class CharacterTpl : public Character {
        T m_health{};
        int m_healthMax{};

    public:
        CharacterTpl(const char* name, int maxHealth) : Character(name) {
            m_healthMax = maxHealth;
            m_health = maxHealth;
        }
        CharacterTpl(const CharacterTpl& src) : Character(src.getName().c_str()){
            m_health = src.m_health;
            m_healthMax = src.m_healthMax;
        }
        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (m_health <= 0) {
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << "    " << getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
            }
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override {
            return m_healthMax;
        }

        void setHealth(int health) override {
            m_health = health;
        }

        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };

}


#endif // SENECA_CHARACTERTPL_H
