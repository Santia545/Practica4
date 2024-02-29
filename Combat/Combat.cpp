//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include<cstdlib>
#include<time.h>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for (auto participant: participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player *> _partyMembers, vector<Enemy *> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character *>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character *>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if (participant->getIsPlayer()) {
        partyMembers.push_back((Player *) participant);
    } else {
        enemies.push_back((Enemy *) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}

string Combat::toString() {
    string result = "";
    vector<Character *>::iterator it;
    for (it = participants.begin(); it != participants.end(); it++) {
        result += (*it)->toString() + "\n";
    }
    cout << "====================" << endl;
    return result;
}

Character *Combat::getTarget(Character *attacker) {
    vector<Character *>::iterator it;
    for (it = participants.begin(); it != participants.end(); it++) {
        if ((*it)->getIsPlayer() != attacker->getIsPlayer()) {
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    cout << "Inicio del combate" << endl;
    combatPrep();
    while (participants.size() > 1) {
        vector<Character *>::iterator it = participants.begin();
        while (it != participants.end()) {
            (*it)->defend(false);

            int selectedAction;
            Character *target = nullptr;
            if ((*it)->getIsPlayer()) {
                selectedAction = selectAction();
                if (selectedAction == 0) {
                    target = ((Player *) *it)->selectTarget(enemies);
                }
            } else {
                /*
                 * debug couts
                cout << ((Enemy *) *it)->getTotalHealth() << endl;
                cout << ((Enemy *) *it)->getHealth() << endl;
                cout << (((double) (*it)->getHealth()) / ((double) ((Enemy *) *it)->getTotalHealth())) << endl;
                cout << (((((double) (*it)->getHealth()) / ((double) ((Enemy *) *it)->getTotalHealth())) < 0.15)?"true":"false" )<< endl;
                */
                if ((((double) (*it)->getHealth()) / ((double) ((Enemy *) *it)->getTotalHealth())) < 0.15) {
                    selectedAction = selectActionForIA();
                } else {
                    selectedAction = 0;
                }
                if (selectedAction == 0) {
                    target = ((Enemy *) *it)->selectTarget(partyMembers);
                }
            }
            if (selectedAction == 0) {
                cout << (*it)->getName() << " Choose Attack" << endl;
                (*it)->doAttack(target);
                if (target->getHealth() <= 0) {
                    it = participants.erase(remove(participants.begin(), participants.end(), target),
                                            participants.end());
                    if (target->getIsPlayer()) {
                        partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), target),
                                           partyMembers.end());
                        if (partyMembers.size() == 0) {
                            cout << "Game Over" << endl;
                            return;
                        }
                    } else {
                        cout << "You killed enemy " << target->getName() << endl;
                        enemies.erase(remove(enemies.begin(), enemies.end(), target), enemies.end());
                        if (enemies.size() == 0) {
                            cout << "Victory" << endl;
                            return;
                        }
                    }
                } else {
                    it++;
                }
            } else {
                cout << (*it)->getName() << " Choose Defense" << endl;
                (*it)->defend(true);
                it++;
            }
        }
    }
}

int Combat::selectAction() {
    int option;
    while (true) {
        cout << "Select an action: " << endl << "0-Attack" << endl << "1-Defend" << endl;
        cin >> option;
        if (option == 0 || option == 1) {
            break;
        } else {
            cout << "Nice try, enter a valid action id" << endl;
        }
    }
    return option;
}

int Combat::selectActionForIA() {
    if (getRandBetweenRange(0, 100) > 60) {
        return 0;
    } else {
        return 1;
    }

}

int Combat::getRandBetweenRange(int lowerBound, int upperBound) {
    srand(time(0)); // Use current time as seed for random generator0
    return (rand() % (upperBound - lowerBound + 1)) + lowerBound;
}
