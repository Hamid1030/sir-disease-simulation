#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include <string>
#include "disease.h"

using namespace std;

class Person
{
private:
	string personName;
	string diseaseName;
	bool susceptibleStatus;
	bool infectiousStatus;
	bool recoveredStatus;
	bool vaccinatedStatus;
	int daysToRecover;
public:
	string getHealthStatus();
	void one_more_day();
	void transmitinfection(string diseaseName);
	bool Susceptible();
	bool Infectious();
	bool Recovered();
	bool Vaccinated();

	void setVaccinated(bool value);
	void setRecovered(bool value);
	void setInfectious(bool value);
	void setSusceptible(bool value);
	void setDaysToRecover(int noOfDays);
	
    int getDaysToRecover();
    string getDiseaseName();
	bool getVaccinated();
	bool getRecovered();
	bool getInfectious();
	bool getSusceptible();
};

#endif


