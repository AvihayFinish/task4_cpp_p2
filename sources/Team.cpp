#include "Team.hpp"
#include <iostream>
using namespace ariel;
using namespace std;

Team::Team (Character* leader) {
    if (leader == nullptr) {
        throw invalid_argument("the leader isnt excist");
    }
    if(leader->getIsInTeam()) {
        throw runtime_error("this character already in a team");
    }
    this->theTeam.push_back(leader);
    this->leader = leader;
    leader->setIsInTeam(true);
}

Team::Team (Team& other) {
    if (Cowboy* c1 = dynamic_cast<Cowboy*>(other.getLeader())) {
        this->setLeader(c1);
    }
    else if (Ninjas* n1 = dynamic_cast<Ninjas*>(other.getLeader())) {
        this->setLeader(n1);
    }

    for (Character* character : this->theTeam) {
        if (Cowboy* c1 = dynamic_cast<Cowboy*>(other.getLeader())) {
            this->theTeam.push_back(c1);
        }
        else if (Ninjas* n1 = dynamic_cast<Ninjas*>(other.getLeader())) {
            this->theTeam.push_back(n1);
        }
    }
}

Team::Team (Team&& other) noexcept {
    this->theTeam = std::move(other.theTeam);
    this->setLeader(other.getLeader());
}

Team& Team::operator= (Team&& other) noexcept {
    if (this != &other) {
        this->theTeam = std::move(other.theTeam);
        this->setLeader(other.getLeader());
    }
    return *this;
}

Team::~Team () {
    for (Character* character: this->theTeam) {
        delete character;
    }
    theTeam.clear();
}

Team& Team::operator= (const Team& other) {
    if (this != &other) {
        this->~Team();
        if (Cowboy* c1 = dynamic_cast<Cowboy*>(other.leader)) {
            this->setLeader(c1);
        }
        else if (Ninjas* n1 = dynamic_cast<Ninjas*>(other.leader)) {
            this->setLeader(n1);
        }

        for (Character* character : this->theTeam) {
            if (Cowboy* c1 = dynamic_cast<Cowboy*>(other.leader)) {
                this->theTeam.push_back(c1);
            }
            else if (Ninjas* n1 = dynamic_cast<Ninjas*>(other.leader)) {
                this->theTeam.push_back(n1);
            }
        }
    }
    return *this;
}

void Team::add (Character* fri) {
    if (fri == nullptr) {
        throw invalid_argument("the character isnt excist");
    }
    if(fri->getIsInTeam()) {
        throw runtime_error("this character already in a team");
    }
    if(this->theTeam.size() == 10) {
        throw runtime_error("the team is full");
    }
    fri->setIsInTeam(true);
    this->theTeam.push_back(fri);
    
}

void Team::attack (Team* enemy) {
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

    Character* toAttack = passOverTheEnemyTeam(enemy);
    for (Character* character : this->theTeam) {
        if (!(toAttack->isAlive())) {
            toAttack = passOverTheEnemyTeam(enemy);
        }
        if (toAttack == nullptr) {
            return;
        }
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(character)) {
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
    }

    for (Character* character : this->theTeam) {
        if (!character->isAlive()) {
            continue;
        }
        if (!(toAttack->isAlive())) {
            toAttack = passOverTheEnemyTeam(enemy);
        }
        if (toAttack == nullptr) {
            return;
        }
        if (OldNinja* o1 = dynamic_cast<OldNinja*>(character)) {
            if (o1->distance(toAttack) <= 1) {
                o1->slash(toAttack);
            }
            else {
                o1->move(toAttack);
            }

        }
        else if (TrainedNinja* t1 = dynamic_cast<TrainedNinja*>(character)) {
            if (t1->distance(toAttack) <= 1) {
                t1->slash(toAttack);
            }
            else {
                t1->move(toAttack);
            }
        }
        else if (YoungNinja* y1 = dynamic_cast<YoungNinja*>(character)) {    
            if (y1->distance(toAttack) <= 1) {
                y1->slash(toAttack);
            }
            else {
                y1->move(toAttack);
            }
        }
    }
}
    
int Team::stillAlive () {
    int count = 0;
    for (Character* character : this->theTeam) {
        if (Cowboy* c1 = dynamic_cast<Cowboy*>(character)) {
            if (c1->isAlive()) {
                count++;
            }
        }
    }
    for (Character* character : this->theTeam) {
        if (Ninjas* o1 = dynamic_cast<Ninjas*>(character)) {
            if (o1->isAlive()) {
                count++;
            }
        }           
    }
    return count;
}

Character* Team::getLeader () {
    return this->leader;
}

void Team::setLeader (Character* leader) {
    this->leader = leader;
}

void Team::setLeaderIfThePrevDead () {
    if (this->stillAlive() == 0) {
        return;
    }
    double minDis = std::numeric_limits<double>::max();
    Character* tempLeader = nullptr;
    for (Character* character : this->theTeam) {
        if (character->isAlive() && character->distance(this->getLeader()) < minDis) {
            minDis = character->distance(this->getLeader());
            tempLeader = character;
        }
    }
    this->setLeader(tempLeader);
}

Character* Team::passOverTheEnemyTeam (Team* enemy) {
    if (!enemy) {
        return nullptr;
    }
    double minDis = std::numeric_limits<double>::max();
    Character* mostClose = nullptr;
    for (Character* character : enemy->theTeam) {
        if (character->isAlive() && character->distance(this->getLeader()) < minDis) {
            mostClose = character;
            minDis = character->distance(this->getLeader());
        }
    }
    return mostClose;
}

void Team::print () {
    for (Character* character : this->theTeam) {
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(character)) {
            cout << cowboy->print() << endl;
        }
    }

    for (Character* character : this->theTeam) {
        if (OldNinja* o1 = dynamic_cast<OldNinja*>(character)) {
            cout << o1->print() << endl;
        }
        else if (TrainedNinja* t1 = dynamic_cast<TrainedNinja*>(character)) {
            cout << t1->print() << endl;
        }
        else if (YoungNinja* y1 = dynamic_cast<YoungNinja*>(character)) { 
            cout << y1->print() << endl;
        }
    }   
} 

vector<Character*>& Team::getTheTeam () {
    return this->theTeam;
}