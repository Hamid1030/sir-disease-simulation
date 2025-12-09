
#include "interaction.h"
#include <list>
#include <iostream>

Interaction::Interaction(){}

void Interaction::overviewPop(Population populationList){
	for (auto & element : populationList.getPeople()){
		element.setInfectious(element.getDaysToRecover()-1);

		if (element.getDaysToRecover() == 0){
			element.setRecovered(true);
		}
	}
}

void Interaction::simulateInternalSpread(Population& populationList, std::list<int>& listOfInfectedPersons, float transmissiblility, int timeDuration, int& infected , int& susceptible, vector<int> &peakInfectOvertime){
	int maxtransmissions = computeTransmissiblity(transmissiblility);
	vector<int> candidateIndices;
	
	int numInfectIds = populationList.infectedIDs.size();
		for (int j =0 ;j < numInfectIds ; j ++){
			candidateIndices.clear();
			int candidateCounter = 0;

		for (int i = 0; i < 6; i++){
			int random = (std::rand() % populationList.people.size());

			Person candidate = populationList.people[random];
			if (candidate.getSusceptible() == 1 ){
				candidateIndices.push_back(random);
				candidateCounter++;
			}
		}

		int suspectPersonListSize = candidateIndices.size();
		int targetCount = 0;

		if (suspectPersonListSize < maxtransmissions){
			targetCount = suspectPersonListSize;
		}
		else{
			targetCount = maxtransmissions;
		}
		if (susceptible > 0){
			for (int j = 0; j < targetCount; j++){
				Person target = populationList.people[candidateIndices[j]];
				target.setInfectious(1);
				target.setSusceptible(0);
				populationList.totalInfected = populationList.totalInfected + 1;

				target.setDaysToRecover(timeDuration);
				listOfInfectedPersons.push_back(candidateIndices[j]);
				infected = infected + 1;
				if (susceptible > 0){
					susceptible--;
				}
				populationList.updatePeople(target, candidateIndices[j]);
			}
		}
	}
}

Person Interaction::simulateContact(Person infPerson, Person contact){
	if (infPerson.getInfectious() == 1){
		if (contact.getSusceptible() == 1 && contact.getVaccinated() == 0 && contact.getRecovered() == 0){
			contact.setInfectious(1);
		}
	}
	return contact;
}

int Interaction::computeTransmissiblity(float transmission){
	float output = transmission * 6;
	int  transmisbility = 0;
	if (output < 1){
		transmisbility = 1;
	}
	else{
		transmisbility = output;
	}
	return transmisbility;

}