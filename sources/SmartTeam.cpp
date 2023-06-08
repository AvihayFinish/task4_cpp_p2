#include "SmartTeam.hpp"
using namespace std;
using namespace ariel;

Character* SmartTeam::findEnemyForNinja (Team* enemy, Character* theNinja) {
    if(!enemy)
	{
		return nullptr;
	}

	Character* theEnemy = nullptr;
	double minDis = numeric_limits<double>::max();
	vector <Character*> CandidatesEnemies;

	for (Character* enemy1 : enemy->getTheTeam())
	{
		if (enemy1->isAlive() && theNinja->distance(enemy1) < minDis)
		{
			minDis = theNinja->distance(enemy1);
			theEnemy = enemy1;
			if(theNinja->distance(enemy1) <= 1)
			{
				CandidatesEnemies.push_back(enemy1);
			}
		}
	}

	int tempSmallFrom_40 = 0;
	int tempBigFrom_40 = 0;
	
	if(CandidatesEnemies.size())
	{
		for(Character* enemy1 : CandidatesEnemies)
		{
			if(enemy1->getPointsLive() == 40)
			{
				return enemy1;
			}
			else if(enemy1->getPointsLive() < 40 && (tempBigFrom_40 == 0))
			{
				if(enemy1->getPointsLive() > tempSmallFrom_40)
				{
					tempSmallFrom_40 = enemy1->getPointsLive();
					theEnemy = enemy1;
				}
			}
			else if(enemy1->getPointsLive() > 40)
			{
				if((tempBigFrom_40 != 0) && (enemy1->getPointsLive() < tempBigFrom_40))
				{
					tempBigFrom_40 = enemy1->getPointsLive();
					theEnemy = enemy1;
				}
			}
		}
	}
	return theEnemy;
}

void SmartTeam::attack (Team* enemy) {
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

    if(!(this->getLeader()->isAlive()))
    {
		this->setLeaderIfThePrevDead();
	}

	vector<Ninjas *> myNinja;
	vector<Cowboy *> myCowboy;

	for (Character* fighter: this->getTheTeam())
	{
		Cowboy* theCowboy = dynamic_cast<Cowboy*>(fighter);
		Ninjas* theNinja = dynamic_cast<Ninjas*>(fighter);

		if (theCowboy != nullptr && theCowboy->isAlive())
			myCowboy.push_back(theCowboy);

		else if (theNinja != nullptr && theNinja->isAlive())
			myNinja.push_back(theNinja);
	}

	Character* enemy1 = nullptr;

	for (Ninjas* ninja: myNinja)
	{
		if (enemy->stillAlive() == 0)
			return;
		
		enemy1 = findEnemyForNinja(enemy, ninja);

		if (ninja->distance(enemy1) <= 1)
			ninja->slash(enemy1);

		else
			ninja->move(enemy1);
	}
	for (Cowboy* cowboy: myCowboy)
	{
		if (enemy->stillAlive() == 0)
			return;
			
		enemy1 = passOverTheEnemyTeam(enemy);
		if (cowboy->hasboolets())
			cowboy->shoot(enemy1);
		else
			cowboy->reload();
	}
}

void SmartTeam::print () {
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