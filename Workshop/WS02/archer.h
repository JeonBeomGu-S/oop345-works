//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"

namespace seneca {
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon;

    public:
        Archer(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
                : CharacterTpl<seneca::SuperHealth>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
            m_weapon = weapon;
        }

        Archer(const Archer<Weapon_t> &src) : CharacterTpl<seneca::SuperHealth>(src){
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_weapon = src.m_weapon;
        }

        int getAttackAmnt() const override {
            return 1.3 * m_baseAttack;
        }

        int getDefenseAmnt() const override {
            return 1.2 * m_baseDefense;
        }

        Character* clone() const override {
            return new Archer(*this);
        }

        void attack(Character* enemy) override {
            std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
            int dmg = getAttackAmnt();
            std::cout << "    Archer deals " << dmg << " ranged damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };
}


#endif // SENECA_ARCHER_H
