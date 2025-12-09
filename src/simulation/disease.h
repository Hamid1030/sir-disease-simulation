#ifndef DISEASE_H
#define DISEASE_H
#include<iostream>
#include <string>

using namespace std;

class Disease
{
private: 
	string diseaseName;
	int duration;
	float transmissionProbability;
	
public:
	Disease(int duration, float transmissionProbability);
	void setDiseaseName(string name);
	string getDiseaseName();
	float getTransmissionProb();
	int getsicknessDuration();
	
};
#endif 

