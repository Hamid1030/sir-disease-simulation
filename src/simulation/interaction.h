#ifndef INTERACTION_H
#define INTERACTION_H
#include "population.h"

class Interaction{
public:
	Interaction();

	void overviewPop(Population population);
	int computeTransmissiblity(float transmission);
	Person simulateContact(Person infPerson,Person contact);
	void simulateInternalSpread(Population& population1, std::list<int>& listOfInfectedPersons, float transmissiblility,int timeDuration, int& infected, int& susceptible,vector<int> &peakInfectOvertime);
	
};

#endif

