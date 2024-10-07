//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon;

    public:
        Rogue(const char *name, int healthMax, int baseAttack, int baseDefense)
                : CharacterTpl<T>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
        }
        Rogue(const Rogue& src) : CharacterTpl<T>(src){
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_firstAbility = src.m_firstAbility;
            m_secondAbility = src.m_secondAbility;
            m_weapon = src.m_weapon;
        }

        int getAttackAmnt() const override {
            return m_baseAttack + 2 * m_weapon.m_damage;
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue(*this);
        }

        void attack(Character* enemy) override {
            std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int dmg = getAttackAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);
            std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}


#endif // SENECA_ROGUE_H
