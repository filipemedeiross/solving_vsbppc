#include <gtest/gtest.h>
#include <fstream>
#include "instance.h"
#include "solution.h"
#include "greedy.h"
#include "neighborhood.h"
#include "constants.h"

using namespace std;

class NeighborhoodTest : public ::testing::Test {
    protected:
        static const char* TEST_FILE;
        static const int   TEST_BIN_COSTS[5];

        static void SetUpTestSuite   () {
            create_testfile();
        }

        static void TearDownTestSuite() {
            remove(TEST_FILE);
        }

        static void create_testfile() {
            ofstream file(TEST_FILE);

            file << "4"        << endl;
            file << "1 10 2 3" << endl;
            file << "2 15 4"   << endl;
            file << "3 20"     << endl;
            file << "4 25"     << endl;

            file.close();
        }
};

const char* NeighborhoodTest::TEST_FILE = "test_neighborhood_instance.txt";
const int   NeighborhoodTest::TEST_BIN_COSTS[5] = {60, 80, 100, 120, 150} ;


TEST_F (NeighborhoodTest, BestKReturnsCorrectIndex) {
    EXPECT_EQ(best_k(1)  , 0);
    EXPECT_EQ(best_k(59) , 0);
    EXPECT_EQ(best_k(60) , 0);
    EXPECT_EQ(best_k(100), 2);
}

TEST_F (NeighborhoodTest, IsFeasibleSingleItem) {
    Instance instance(TEST_FILE);

    Bin bin(0);
    bin.add(0, 10, 2);

    EXPECT_FALSE(
        is_feasible(&bin, 1, instance[1], instance)
    );
}

TEST_F (NeighborhoodTest, SearchPerformsMove) {
    Instance instance(TEST_FILE);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy2);

    Solution solution = greedy.initial_solution();

    EXPECT_GE(search(solution, instance), 0);
}