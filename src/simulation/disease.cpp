#include "disease.h"


Disease::Disease(int duration, float transmissonProbability): duration(duration), 
transmissionProbability(transmissionProbability){}

void Disease::setDiseaseName(string name){
	diseaseName = name;
}

string Disease::getDiseaseName(){
	return diseaseName;
}

float Disease::getTransmissionProb(){
	return transmissionProbability;
}

int Disease::getsicknessDuration(){
	return duration;
}