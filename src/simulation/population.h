#ifndef POPULATION_H
#define POPULATION_H
#include "disease.h"
#include "person.h"
#include <iostream>
#include <list>
#include <vector> 


using namespace std;

class Population{
private:
	std::string populationName;
	int population_size = 0;
	float vaccinationRate;
	int initialPatientcount;
	
public:
	Population();
	Population(string name, int populationSize, float vaccinationRate,bool noOfPatients);

	vector<Person> people;
	vector<Person> getPeople();

	std::list<int> infectedIDs;
	std::list<int> recoveredIDs;
	vector<int> peakInfectOvertime;

	int infected = 0;
	int recovered = 0;
	int vaccinated = 0;
	int susceptible = 0;
	int initialInfected = 0;
	int initialVaccinated = 0;
	int totalInfected = 0;
	
	int getNumPatients();
	int getPopSize();
	float getVaccinationRate();
	std::string getPopulationName();
	int count_infected(Population &Population);
	int count_recovered(Population &Population);
	int count_susceptible(Population &Population);
	int count_vaccinated(Population &Population);


	void random_vaccination();
	void random_infection(Population& population, Disease diseaseName, int initial_infect);

	void one_more_day();
	void updatePeople(Person person, int position);
	void assignVaccinationToPop(Population &population ,int& vaccinated,int& susceptible);
	void Recover(Population& population);
	void EnhancerecoverTime(Population& population,std::list<int>& listOfInfectedPersons , std::list<int>& listOfRecoveredPersons,int& recovered, int& infected);
	bool surveyremainInfect(Population& population , std::list<int>& listOfInfectedPersons);
	
};

#endif


