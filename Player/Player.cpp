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
    health -= trueDamage;

    std::cout << name << " took " << trueDamage << " damage!" << endl;


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
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
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