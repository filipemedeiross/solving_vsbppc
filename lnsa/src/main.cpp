#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include "instance.h"
#include "solution.h"
#include "greedy.h"
#include "lnsa.h"
#include "constants.h"

#define PATIENCE 150
#define VERBOSE  0
#define P        0.25f

using namespace std;
using namespace std::chrono;


int elapsed_seconds(time_point <high_resolution_clock> start) {
    time_point <high_resolution_clock> stop = high_resolution_clock::now();

    return duration_cast <seconds> (stop - start).count();
}


int main (int argc, char** argv) {
    if (argc < 2) {
        cerr << "Using: ./vsbppc <file_instance> [file_results]"      << endl
             << "Options:"                                            << endl
             << "  -pa <int>   patience (default " << PATIENCE << ")" << endl
             << "  -v  <int>   verbose  (default " << VERBOSE  << ")" << endl
             << "  -p  <float> p        (default " << P        << ")" << endl;

        return -1;
	}

    int   patience = PATIENCE;
    int   verbose  = VERBOSE ;
    float p        = P;
    const char* output_file = NULL;

    for (int i = 2; i < argc; i++) {
        if      (strcmp(argv[i], "-pa") == 0 && i + 1 < argc)
            patience = atoi(argv[++i]);
        else if (strcmp(argv[i], "-v" ) == 0 && i + 1 < argc)
            verbose  = atoi(argv[++i]);
        else if (strcmp(argv[i], "-p" ) == 0 && i + 1 < argc)
            p = (float) (atof(argv[++i]));
        else
            output_file = argv[i];
    }

    srand (static_cast <unsigned> (time(nullptr)));

    ofstream write_file;
    if (output_file) {
        write_file.open(output_file, ios_base::app);

        if (!write_file.is_open()) {
            cerr << "Error: could not open output file '" << output_file << "'." << endl;
            return -1;
        }
    }

    cout << "Reading the instance..." << endl;
    Instance instance (argv[1]);
    Greedy   greedy   (instance, BIN_TYPES, BIN_SIZE, chooser_greedy2);

    int time_greedy, time_lnsa;
    time_point <high_resolution_clock> start;

    // Greedy algorithm
    start       = high_resolution_clock::now();
    Solution greedy_solution = greedy.initial_solution();
    time_greedy = elapsed_seconds(start);

    // LNSA
    start     = high_resolution_clock::now();
    Solution best_solution = lnsa(instance, patience, p, chooser_greedy1, verbose);
    time_lnsa = elapsed_seconds(start);

    if (output_file != NULL) {
        write_file << argv[1]                   << " "
                   << greedy_solution.get_obj() << " "
                   << time_greedy               << " "
                   << best_solution.get_obj()   << " "
                   << time_lnsa                 << endl;

        write_file.close();
    }

    // Print the best solution
    cout << endl;
    cout << "Final solution:" << endl;
    best_solution.describe();

    cout << endl;
    cout << greedy_solution.get_obj() << endl;
    cout << best_solution  .get_obj() << endl;

    return 0;
}