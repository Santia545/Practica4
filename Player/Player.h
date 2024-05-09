//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player : public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
private:
    Player(int _level, int _experience, char _name[40], int _health, int _attack, int _defense, int _speed);

    int level;
    int experience;

    void levelUp();

public:
    Player(const char _name[], int _health, int _attack, int _defense, int _speed);
    string toString();

    void doAttack(Character *target) override;

    void takeDamage(int damage) override;

    Character *selectTarget(vector<Enemy *> possibleTargets);

    Action takeAction(vector<Enemy *> enemies);
    void gainExperience(int exp);

    void serialize(char buffer[]);

    static Player* unserialize(char buffer[]);

    static const unsigned int BUFFER_SIZE = sizeof(level) + sizeof(experience) + sizeof(name) + sizeof(
            health) + sizeof(attack) + sizeof(defense) + sizeof(speed) + sizeof(isPlayer) + sizeof(isDefending);

    //TODO: Implement use object
};


#endif //RPG_PLAYER_H
