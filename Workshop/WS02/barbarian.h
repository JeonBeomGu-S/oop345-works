//
// Created by Beomgu Jeon on 2024-10-06.
// Name: Beomgu Jeon
// Email: bgjeon@myseneca.ca
// Student ID: 126428234

//

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "character.h"
#include "characterTpl.h"

namespace seneca {
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2]{};

    public:
        Barbarian(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon,
                                                     Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        Barbarian(const Barbarian& src) : CharacterTpl<T>(src){
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_weapon[0] = src.m_weapon[0];
            m_weapon[1] = src.m_weapon[1];
            m_ability = src.m_ability;
        }

        int getAttackAmnt() const override {
            return m_baseAttack + (static_cast<double>(m_weapon[0]) / 2) + (static_cast<double>(m_weapon[1]) / 2);
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_ability.useAbility(this);
            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}


#endif // SENECA_BARBARIAN_H
