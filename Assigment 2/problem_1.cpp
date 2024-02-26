#include <iostream>
#include <cstdlib> // for rand() and RAND_MAX
#include <ctime>   // for time()
#include "DEQ.h"   // Header file for the DEQ (Double Ended Queue) implementation

using namespace std;

// Function prototypes
void Arrival(int& Tarrival, DEQ<int>& queue, int t, double Parrival, int& arrivalCount);
void Service(int& Trem, int t, int Ts, DEQ<int>& queue, int& waitTotal, int& ServiceCount);
void ExitLine(DEQ<int>& queue, int t, int& waitTotal, int& ServiceCount);
double AverageWait(int waitTotal, int arrivalCount);

int main() {
    // Constants for simulation parameters
    const int Tmax = 6 * 60; // Maximum time for the simulation (6 hours in minutes)
    const int Ts = 10;       // Service time for each job in minutes
    const double DeltaT = 6; // Time interval for job arrival (in minutes)
    const double Parrival = 1.0 / DeltaT; // Probability of job arrival within DeltaT
    int t = 0;               // Current time in the simulation
    int Trem = 0;            // Remaining service time for the current job
    int waitTotal = 0;       // Total wait time for all serviced jobs
    int ServiceCount = 0;    // Number of jobs serviced
    int arrivalCount = 0;    // Number of jobs arrived
    DEQ<int> queue;          // Queue of jobs

    // Seed the random number generator with current time
    srand(time(nullptr));

    cout << "Simulation Log:" << endl;

    // Main simulation loop
    while (t < Tmax) {
        // Test for arrival of a job
        int Tarrival = -1;
        Arrival(Tarrival, queue, t, Parrival, arrivalCount);

        // Test if server is ready to service a job
        Service(Trem, t, Ts, queue, waitTotal, ServiceCount);

        // Decrement remaining service time if a job is being serviced
        if (Trem > 0)
            Trem--;

        // Increment simulation time
        t++;
    }

    // Compute and display average wait time
    double avgWait = AverageWait(waitTotal, ServiceCount);
    cout << "Average wait time: " << avgWait << endl;

    return 0;
}

// Simulates job arrival
void Arrival(int& Tarrival, DEQ<int>& queue, int t, double Parrival, int& arrivalCount) {
    // Generate a random number between 0 and 1
    double R = rand() / static_cast<double>(RAND_MAX);
    // Check if a job arrives based on the probability Parrival
    if (R < Parrival) {
        Tarrival = t; // Set arrival time
        queue.add_Rear(Tarrival); // Add the job to the rear of the queue
        // Output arrival information
        cout << "Arrival# " << ++arrivalCount << " at: " << Tarrival << endl;
    }
}

// Simulates job service
void Service(int& Trem, int t, int Ts, DEQ<int>& queue, int& waitTotal, int& ServiceCount) {
    // Check if the server is free and there are jobs in the queue
    if ((Trem == 0) && (!queue.isEmpty())) {
        // Remove a job from the queue and begin service
        ExitLine(queue, t, waitTotal, ServiceCount);
        Trem = Ts; // Start service with the service time Ts
    }
}

// Simulates job exiting the line after service
void ExitLine(DEQ<int>& queue, int t, int& waitTotal, int& ServiceCount) {
    // Check if the queue is not empty
    if (!queue.isEmpty()) {
        int Tarrival = queue.view_Front(); // Get the arrival time of the job at the front of the queue
        int Twait = t - Tarrival; // Calculate the wait time
        waitTotal += Twait; // Update the total wait time
        queue.Remove_Front(); // Remove the serviced job from the front of the queue
        // Output service information
        cout << "Job# " << ++ServiceCount << " Service Started at: " << t << " wait = " << Twait << endl;
    }
}

// Computes average wait time
double AverageWait(int waitTotal, int serviceCount) {
    // Check if any jobs were serviced to avoid division by zero
    if (serviceCount == 0)
        return 0;
    else
        return static_cast<double>(waitTotal) / serviceCount; // Calculate and return the average wait time
}