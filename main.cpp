#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include <fstream>

bool fileExists(const string &filename = "data.dat") {
    std::ifstream file(filename);
    return file.good();
}

Player *readPlayerFromFile() {
    char buffer[Player::BUFFER_SIZE];
    ifstream readStream;
    readStream.open("data.dat", ios::binary);
    readStream.read(buffer, Player::BUFFER_SIZE);
    readStream.close();
    return Player::unserialize(buffer);
}

void writeToFile(char buffer[], unsigned int bufferSize) {
    ofstream writeStream;
    writeStream.open("data.dat", ios::binary);
    //Escribe en el archivo desde la direccion donde apunta buffer hasta donde mide bufferSize
    writeStream.write(buffer, bufferSize);
    writeStream.close();
}


int main() {
    string resp = "";
    do {
        Player *player;
        if (fileExists()) {
            cout << "Savegame detected!!\n Load?? Y(yes) | any other char(no)" << endl;
            cin >> resp;
            if (resp == "Y" || resp == "y") {
                player = readPlayerFromFile();
                cout << "Player succesfully loaded:\n" << player->toString() << endl;
            } else {
                player = new Player("Victor", 100, 15, 4, 3);
            }
        } else {
            player = new Player("Victor", 100, 15, 4, 3);
        }

        Enemy *enemy = new Enemy("Goblin", 50, 6, 2, 5, 120);
        Enemy *enemy2 = new Enemy("Orc", 50, 6, 2, 5, 120);

        vector<Character *> participants;

        participants.push_back(player);
        participants.push_back(enemy);
        participants.push_back(enemy2);

        Combat *combat = new Combat(participants);
        combat->doCombat();
        if (player->getHealth() > 0) {
            cout
                    << "Want to save game?? Y(yes) | any other char(no) \n If you dont save the progress will be lost on the next round"
                    << endl;
            cin >> resp;
            if (resp == "Y" || resp == "y") {
                char buffer[Player::BUFFER_SIZE];
                player->serialize(buffer);
                writeToFile(buffer, Player::BUFFER_SIZE);
            }
        }
        delete player;
        delete enemy;
        delete combat;
        cout << "Want to continue?? Y(yes) | any other char(no)" << endl;
        cin >> resp;
    } while (resp == "Y" || resp == "y");
    return 0;
}
