//
// Created by Victor Navarro on 15/02/24.
//

#include <iostream>
#include <cmath>
#include "Character.h"
Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}
void Character::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if(isDefending){
        trueDamage-=int(round((double)defense*.20));
        //if defense must last 1 round then comment this, if it must last till the character gets attacked then leave it as it is
        defend(false);
    }
    health-= trueDamage;

    std::cout << name << " took " << trueDamage << " damage!" << endl;

}
string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}

void Character::defend(bool state) {
    isDefending=state;
}


