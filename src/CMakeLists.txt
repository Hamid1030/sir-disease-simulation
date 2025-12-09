cmake_minimum_required(VERSION 3.21)
project(hpc_disease_simulation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(hpc_disease_simulation
        simulation/main.cpp
        simulation/simulation.cpp
        simulation/disease.cpp
        simulation/interaction.cpp
        simulation/person.cpp
        simulation/population.cpp
        )

