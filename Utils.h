//
// Created by Victor Navarro on 15/02/24.
//

#ifndef UTILS_H
#define UTILS_H

#include<cstdlib>
#include<time.h>

namespace combat_utils {
    int getRandBetweenRange(int lowerBound, int upperBound) {
        srand(time(0)); // Use current time as seed for random generator0
        return (rand() % (upperBound - lowerBound + 1)) + lowerBound;
    }

    int getRolledAttack(int attack) {
        int lowerLimit = attack * .80;
        return getRandBetweenRange(lowerLimit, attack);
    }


}
#endif //UTILS_H
