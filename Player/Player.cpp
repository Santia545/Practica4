//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include <cmath>

using namespace std;

Player::Player(const char _name[], int _health, int _attack, int _defense, int _speed) : Character(_name, _health,
                                                                                                   _attack,
                                                                                                   _defense, _speed,
                                                                                                   true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (isDefending) {
        trueDamage -= int(round((double) defense * .20));
    }
    health -= trueDamage >= 0 ? trueDamage : 0;

    std::cout << name << " took " << (trueDamage >= 0 ? trueDamage : 0) << " damage!" << endl;

    if (health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {
    level++;
    cout << "Player " << name << " is now level: " << level << " with an xp of " << experience << endl;
    cout << "as a reward " << name << " has been healed with an extra 20hp, current hp now is: " << getHealth() << endl;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        experience = experience - 100;
        levelUp();
    }
}

Character *Player::selectTarget(vector<Enemy *> possibleTargets) {
    int selectedTarget = 0;
    bool invalid = true;
    do {
        cout << "Select a target: " << endl;
        for (int i = 0; i < possibleTargets.size(); i++) {
            cout << i << ". " << possibleTargets[i]->getName() << endl;
        }
        cin >> selectedTarget;
        for (int i = 0; i < possibleTargets.size(); i++) {
            if (selectedTarget == i) {
                invalid = false;
                break;
            }
        }
        if (invalid) {
            cout << "Invalid option" << endl;
        }
    } while (invalid);
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    bool error;
    int action = 0;
    Action currentAction;
    do {
        error = false;
        cout << "Select an action: " << endl
             << "1. Attack" << endl
             << "2. Defend" << endl;
        cin >> action;
        Character *target = nullptr;
        defend(false);
        switch (action) {
            case 1:
                target = selectTarget(enemies);
                currentAction.target = target;
                currentAction.action = [this, target]() {
                    doAttack(target);
                    if (target->getHealth() <= 0) {
                        this->gainExperience(((Enemy *) target)->getExperience());
                    }
                };
                currentAction.speed = getSpeed();
                break;
            case 2:
                currentAction.target = this;
                currentAction.action = [this]() {
                    defend(true);
                };
                currentAction.speed = 999999;
                break;

            default:
                cout << "Invalid action" << endl;
                error = true;
                break;
        }
    } while (error);
    return currentAction;
}

Player *Player::unserialize(char *buffer) {
    char *iterator = buffer;
    int level, experience;
    char name[40];
    int health, attack, defense, speed;

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    memcpy(name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));

    return new Player(level, experience, name, health, attack, defense, speed);
}

void Player::serialize(char buffer[]) {
    char *iterator = buffer;

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));
    iterator += sizeof(experience);

    memcpy(iterator, name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &speed, sizeof(speed));
}

Player::Player(int _level, int _experience, char *_name, int _health, int _attack, int _defense, int _speed)
        : Character(_name, _health,
                    _attack,
                    _defense, _speed,
                    true) {
    level = _level;
    experience = _experience;
}

string Player::toString() {
    return Character::toString() + "\nLevel: " + to_string(level) + "\nExp: " + to_string(experience);
}
