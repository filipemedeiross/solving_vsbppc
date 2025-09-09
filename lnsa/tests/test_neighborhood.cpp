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


TEST_F (NeighborhoodTest, VectorShuffledGeneratesDifferentOrder) {
    const int n = 100;

    vector <int> result1 = vector_shuffled(n);
    vector <int> result2 = vector_shuffled(n);

    EXPECT_TRUE(result1 != result2) << "vector_shuffled should generate different permutations";
}

TEST_F (NeighborhoodTest, VectorShuffledIsLimitated) {
    const int n = 5;
    vector<int> shuffled = vector_shuffled(n);

    for (int elem : shuffled) {
        EXPECT_GE(elem, 0) << "All elements should be non-negative";
        EXPECT_LT(elem, n) << "All elements should be less than n" ;
    }

    EXPECT_EQ(shuffled.size(), n) << "Shuffled vector should have size n";
}

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