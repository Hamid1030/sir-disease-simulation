#include "population.h"
#include <iostream>
#include<list>
using namespace std;

Population::Population(){}

Population::Population(string name, int populationSize, float vaccinationRate, bool noOfPatients)
{
	populationName = name;
	population_size = populationSize;
	vaccinationRate = vaccinationRate;
	initialPatientcount = noOfPatients;
	

	for (int i = 0;i < populationSize; i++){
		Person p1;
		p1.setSusceptible(1);
		p1.setInfectious(0);
		p1.setRecovered(0);
		p1.setVaccinated(0);
		p1.setDaysToRecover(2);

		people.push_back(p1);
	}
}

void Population::random_infection(Population& population,Disease diseaseName,int initial_infect){
	
		Person p2;
		p2.transmitinfection(diseaseName.getDiseaseName());
		p2.setInfectious(1);
		p2.setRecovered(0);
		p2.setSusceptible(0);
		p2.setVaccinated(0);
		p2.setDaysToRecover(diseaseName.getsicknessDuration());
		int tempo = 0;
		Person p3;
		
		while (true)
		{
			 tempo = (std::rand() % people.size());
			 p3 = people[tempo];
			if (p3.getVaccinated() != 1)
			{
				people[tempo] = p2;
				population.susceptible = population.susceptible - 1;
				population.infected = 1;
				population.totalInfected = population.totalInfected + 1;
				break;
			}
		}
		infectedIDs.push_back(tempo);
}

vector<Person> Population::getPeople(){
	return people;
}

void Population::updatePeople(Person person, int position){
	people[position] = person;
}

int Population::getNumPatients(){
	return initialPatientcount;
}

int Population::count_infected(Population &Population){
	int sumInfected = 0;
	for (auto& element : Population.getPeople()) {
		if (element.getInfectious() == 1){
			sumInfected++;
		}
	}
	return sumInfected;
}

int Population::count_recovered(Population &Population){
	int sumRecovered = 0;
	for (auto& element : Population.getPeople()) {
		if (element.getRecovered() == 1){
			sumRecovered++;
		}
	}
	return sumRecovered;
}

int Population::count_susceptible(Population &Population)
{
	int sumSusceptible = 0;
	for (auto& element : Population.getPeople()) {
		if (element.getSusceptible() == 1){
			sumSusceptible++;
		}
	}
	return sumSusceptible;
}

int Population::count_vaccinated(Population &Population){
	int sumVaccinated = 0;
	
	for (auto& element : Population.getPeople()) {
		if (element.getVaccinated() == 1){
			sumVaccinated++;
		}
	}
	return sumVaccinated;
}

void Population::assignVaccinationToPop(Population &population, int &vaccinated, int& susceptible){
	int pop_size = 0;
	pop_size = population.getPopSize();
	float temp = population.getVaccinationRate() * 100;
	temp = temp / 100;
	
	int noOfVaccinatedPersons = temp * pop_size;
	Person p3;
	for (int i = 0; i < noOfVaccinatedPersons; i++){
		p3 = population.people[i];
		p3.setVaccinated(1);
		p3.setSusceptible(0);
		susceptible--;
		population.updatePeople(p3, i);
		vaccinated++;
	}
}

void Population::Recover(Population& population){
	Person p4;
	int recoveryday = 0;
	for(int i =0; i <  population.getPeople().size(); i++){
		 p4 = population.getPeople().at(i);
	
		if (p4.getInfectious() == 1 && p4.getRecovered() == 0){
			recoveryday = p4.getDaysToRecover();
			p4.setDaysToRecover(recoveryday - 1);
			if (p4.getDaysToRecover() == 0){
				p4.setRecovered(1);
				p4.setSusceptible(0);
			}
			population.updatePeople(p4, i);
		}
		std::cout << i << endl;

	}
}

bool Population::surveyremainInfect(Population& population, std::list<int>& listOfInfectedPersons){
	if (population.infectedIDs.size() == 0){
		return true;
	}
	return false;
}

string Population::getPopulationName(){
	return populationName;
}


void Population::EnhancerecoverTime(Population& population,std::list<int>& listOfInfectedPersons , std::list<int>& listOfRecoveredPersons , int &recovered, int& infected){
	Person p5;
	int recoveryday = 0;

	std::list<int>::iterator counter = listOfInfectedPersons.begin();
	while (counter != listOfInfectedPersons.end())	
	{	
		p5 = population.people[*counter];
		recoveryday = p5.getDaysToRecover();
			if (p5.getDaysToRecover() > 0){
				p5.setDaysToRecover(recoveryday - 1);
			}
			population.updatePeople(p5, *counter);

			if (p5.getDaysToRecover() == 0){
				p5.setRecovered(1);
				p5.setSusceptible(0);
				population.updatePeople(p5, *counter);
				recovered++;
				if (infected > 0){
					infected--;
				}
					counter = listOfInfectedPersons.erase(counter);
			}
			else{
				++counter;
			}
	}
	population.peakInfectOvertime.push_back(infected);
}

int Population::getPopSize(){
	return population_size;
}

float Population::getVaccinationRate(){
	return vaccinationRate;
}