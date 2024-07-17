#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>
#include "instance.h"
#include "solution.h"
#include "greedy.h"
#include "lnsa.h"

#define FILE_OUT "out/results.txt"
#define PATIENCE 500
#define VERBOSE 0
#define P 0.25

using namespace std;
using namespace std::chrono;

int main (int argc, char** argv) {
    if (argc != 2) {
        cout << "Using: ./vsbppc <file_instance>" << endl;
		return -1;
	}

    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Reading the instance..." << endl;
    Instance instance = Instance(argv[1]);
    Greedy greedy     = Greedy (&instance);

    int time;
    time_point<high_resolution_clock> start, stop;
    ofstream write_file(FILE_OUT, ios_base::app);

    // Greedy algorithm
    start = high_resolution_clock::now();
    Solution *greedy_solution = greedy.initial_solution();
    stop = high_resolution_clock::now();

    time = duration_cast<seconds>(stop - start).count();
    write_file << argv[1] << " " <<
                  greedy_solution->obj << " " <<
                  time << " ";

    // LNSA
    start = high_resolution_clock::now();
    Solution *best_solution = lnsa(instance, PATIENCE, VERBOSE, P);
    stop = high_resolution_clock::now();

    time = duration_cast<seconds>(stop - start).count();
    write_file << best_solution->obj << " " <<
                  time << endl;
    
    // Save the results
    write_file.close();

    // Print the best solution
    cout << endl;
    cout << "Final solution:" << endl;
    best_solution->describe();    

    return 0;
}