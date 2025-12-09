# 🦠 Disease Simulation Using the SIR Model (C++)

This project implements an **individual-based SIR (Susceptible–Infectious–Recovered)** disease simulation in C++.  
Each person in the population is modeled explicitly, and the simulator tracks disease spread using daily interactions, transmission probability, vaccination, and recovery.

The project also includes a **Herd Immunity Investigation**, where the vaccination rate is varied to identify the herd immunity threshold and compare it to the theoretical expectation.

---

## 📌 Features

### ✔ Core Simulation
- Explicit simulation of **individual persons**  
- Four possible states: **Susceptible, Infectious, Vaccinated, Recovered**  
- Configurable vaccination rate per population  
- Each infectious person contacts **6 random individuals per day**  
- Transmission based on disease transmissibility  
- Continuous simulation until no infectious individuals remain  
- **Multiple runs** with mean & standard deviation calculation

### ✔ Input & Output
- Reads configuration from **disease_in.ini** (using INIReader)
- Writes:
  - **disease_stats.csv** → summary statistics
  - **disease_details.csv** → timestep-by-timestep population data
- Prints runtime information and summary results to STDOUT

### ✔ Experiment: Herd Immunity
- Runs multiple simulations with vaccination rates from **0% to 100%**
- Uses provided disease parameters (duration, transmissibility)
- Produces plots for:
  - Recovered persons vs vaccination rate
  - S/I/R curves over time for a single simulation
- Compares observed results with theoretical herd immunity threshold

### ✔ Engineering Requirements
- Implemented fully in **C++ (OOP design)**
- Uses **std::rand** for randomness
- Containerized using **Docker**; GitLab CI builds & runs the container

---

## 📂 Project Structure

