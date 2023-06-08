#include "Team2.hpp"
using namespace std;
using namespace ariel;

Team2::Team2 (Character* leader) : Team(leader) {

}

void Team2::attack (Team* enemy) {
    if (enemy == nullptr) {
        throw invalid_argument("the enemy team is not excist");
    }
    else if (this == enemy) {
        throw runtime_error("you cannot attack yourself");
    }
    else if (enemy->stillAlive() == 0) {
        throw runtime_error("all the enemy characters is dead");
    }
    else if (this->stillAlive() == 0) {
        throw runtime_error("the attack team is dead");
    }

    if (!(this->getLeader()->isAlive())) {
        this->setLeaderIfThePrevDead();
    }
    Character* toAttack = Team::passOverTheEnemyTeam(enemy);
    for (Character* Character: this->getTheTeam()) {
        if (!(Character->isAlive())) {
            continue;
        }
        if (!(toAttack->isAlive())) {
            toAttack = Team::passOverTheEnemyTeam(enemy);
        }
        if (toAttack == nullptr) {
            return;
        }
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(Character)) {
            if (!(cowboy->isAlive())) {
                continue;
            }
            if (cowboy->hasboolets()) {
                cowboy->shoot(toAttack);
            }
            else {
                cowboy->reload();
            }  
        }
        else if (OldNinja* o1 = dynamic_cast<OldNinja*>(Character)) {
            if (o1->distance(toAttack) <= 1) {
                o1->slash(toAttack);
            }
            else {
                o1->move(toAttack);
            }
        }
        else if (YoungNinja* y1 = dynamic_cast<YoungNinja*>(Character)) {
            if (y1->distance(toAttack) <= 1) {
                y1->slash(toAttack);
            }
            else {
                y1->move(toAttack);
            }
        }
        else if (TrainedNinja* t1 = dynamic_cast<TrainedNinja*>(Character)) {
            if (t1->distance(toAttack) <= 1) {
                t1->slash(toAttack);
            }
            else {
                t1->move(toAttack);
            }
        }
    }
}

int Team2::stillAlive () {
    int count = 0;
    for (Character* character : this->getTheTeam()) {
        if (character->isAlive()) {
            count++;
        }
    }
    return count;
}

void Team2::print () {
    for (Character* Character: this->getTheTeam()) {
        if (Cowboy* c1 = dynamic_cast<Cowboy*>(Character)) {
            cout << c1->print() << endl;
        }
        else if (OldNinja* o1 = dynamic_cast<OldNinja*>(Character)) {
            cout << o1->print() << endl;
        }
        else if (YoungNinja* y1 = dynamic_cast<YoungNinja*>(Character)) {
            cout << y1->print() << endl;
        }
        else if (TrainedNinja* t1 = dynamic_cast<TrainedNinja*>(Character)) {
            cout << t1->print() << endl;
        }
    }
}