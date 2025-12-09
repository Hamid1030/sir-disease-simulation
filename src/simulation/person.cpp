#include "person.h"

void Person::transmitinfection(string diseaseName){
	diseaseName = diseaseName;
	infectiousStatus = 1;
}

bool Person::Infectious(){
	if (infectiousStatus)
	{
		return true;
	}
	return false;
}

bool Person::Susceptible(){
	if (susceptibleStatus)
	{
		return true;
	}
	return false;
}

bool Person::Recovered(){
	if (recoveredStatus)
	{
		return true;
	}
	return false;
}

bool Person::Vaccinated(){
	if (vaccinatedStatus)
	{
		return true;
	}
	return false;
}


void Person::setInfectious(bool value){
	infectiousStatus = value;
}

void Person::setRecovered(bool value){
	recoveredStatus = value;
}

void Person::setSusceptible(bool value){
	susceptibleStatus = value;
}

void Person::setVaccinated(bool value){
	vaccinatedStatus = value;
}

void Person::setDaysToRecover(int noOfDays){
	daysToRecover = noOfDays;
}

int Person::getDaysToRecover(){
	return daysToRecover;
}

bool Person::getSusceptible(){
	return susceptibleStatus;
}

bool Person::getInfectious(){
	return infectiousStatus;
}

bool Person::getRecovered(){
	return recoveredStatus;
}

bool Person::getVaccinated(){
	return vaccinatedStatus;
}

string Person::getDiseaseName(){
	return diseaseName;
}
