#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "disease.h"
#include "person.h"
#include "population.h"
#include "interaction.h"
#include "../include/INIReader.h"

using namespace std;

Population createPopulationFromINI(const std::string& section, const INIReader& reader) {
    std::string pop_name = reader.Get(section, "name", "UNKNOWN");
    int pop_size = reader.GetInteger(section, "size", 0);
    float pop_vaccination_rate = reader.GetFloat(section, "vaccination_rate", 0.0);
    bool pop_patient0 = reader.GetBoolean(section, "patient_0", false);

    Population population(pop_name, pop_size, pop_vaccination_rate, pop_patient0);
    population.susceptible = pop_size;
    return population;
}

double maximum(const std::vector<int>& maxvec) {
    if (maxvec.empty()){
         return 0;
        }
    double max = maxvec[0];
    for (size_t i = 1; i < maxvec.size(); ++i) {
        if (max < maxvec[i]) {
            max = maxvec[i];
        }
    }
    return max;
}

void runSimulation(Population basePopulation, Disease disease, int runIndex,
                   std::ofstream& details_file, std::ofstream& stats_file) {
          
    Population pop = basePopulation;  
    pop.assignVaccinationToPop(pop, pop.vaccinated, pop.susceptible);

    if (pop.getNumPatients() == 1 && pop.vaccinated < pop.people.size()) {
        pop.random_infection(pop, disease, 1);
    }

    Interaction interact;
    Population inspectPop;
    Population inspectRemainPop;
    
    std::vector<bool> inspectRemainlist;
    unsigned int steps_counter = 0;
    bool simulation_runs = false;

    details_file << pop.getPopulationName() << "," << pop.infected << "," << pop.recovered << "," << pop.susceptible << "," << pop.vaccinated << "\n";
    
    while (true) {
        
        steps_counter++;

        interact.simulateInternalSpread(pop, pop.infectedIDs, disease.getTransmissionProb(), disease.getsicknessDuration(), pop.infected, pop.susceptible, pop.peakInfectOvertime);

        inspectPop.EnhancerecoverTime(pop, pop.infectedIDs,pop.recoveredIDs,pop.recovered, pop.infected);

        inspectRemainlist.clear();
        bool inspectRemainlist1 = inspectRemainPop.surveyremainInfect(
            pop, pop.infectedIDs);
            inspectRemainlist.push_back(inspectRemainlist1);

        simulation_runs = std::all_of(inspectRemainlist.begin(), inspectRemainlist.end(), [](bool v) { return v; });

        details_file << pop.getPopulationName() << "," //<< runIndex << "," << steps_counter << ","
                     << pop.infected << "," << pop.recovered << "," << pop.susceptible << "," << pop.vaccinated << "\n";
        
        if (simulation_runs) {
            int maxInfect = pop.peakInfectOvertime.empty() ? 0 : maximum(pop.peakInfectOvertime);
            
            std::cout << "Run #" << runIndex << " for Population: " << pop.getPopulationName() << "\n";
            std::cout << "Total steps: " << steps_counter << "\n";
            std::cout << "Infected: " << pop.totalInfected
                      << ", Recovered: " << pop.recovered
                      << ", Susceptible: " << pop.susceptible
                      << ", Vaccinated: " << pop.vaccinated << "\n";

            stats_file << "Key, Value"<<endl;
            stats_file << "Population_name, "<<pop.getPopulationName() <<std::endl;
            stats_file << "Simulation_Run, " << runIndex<< endl;
            //stats_file << "Run #" << runIndex << " for Population: " << pop.getPopulationName() << "\n";
            stats_file << "total_steps, " << steps_counter << "\n";
           // stats_file << "Infected_persons, " << pop.infected<< "\n";
            stats_file << "Susceptible_persons, " << pop.susceptible<< "\n";
            stats_file << "Recovered_persons, " << pop.recovered<< "\n";
            stats_file << "Vaccinated_persons, " << pop.vaccinated<< "\n";
            stats_file << endl; 
            break;
        }
    }
}

int main() {
    std::cout << "Simulation Started!\n";

    INIReader reader("./configExample/disease_in.ini");
    if (reader.ParseError() < 0) {
        std::cerr << "Error abadjfadsjf loading 'disease_in.ini' file \n";
        return 1;
    }

    Disease disease(reader.GetInteger("disease", "duration", 0),
                    reader.GetFloat("disease", "transmissability", 0));
    disease.setDiseaseName(reader.Get("disease", "name", "UNKNOWN"));

    std::set<std::string> sections = reader.Sections();
    std::vector<Population> population_vector;

    for (const auto& section : sections) {
        if (section.rfind("population_", 0) == 0) {
            Population population = createPopulationFromINI(section, reader);
            population_vector.push_back(population);
        }
    }

    // Open global output files
    std::ofstream details_file("disease_details.csv");
    std::ofstream stats_file("disease_stats.csv");

    details_file << "Population,Infectious,Recovered,Susceptible,Vaccinated\n";
  
    for (auto& pop : population_vector) {
        for (int run = 1; run <= 5; ++run) {
            runSimulation(pop, disease, run, details_file, stats_file);
        }
        details_file << "--------------------------------------------"<<endl;
        stats_file << endl;
    }

    details_file.close();
    stats_file.close();

    std::cout << "Simulation completed. Results saved to disease_details.csv and disease_stats.csv\n";
    return 0;
}
