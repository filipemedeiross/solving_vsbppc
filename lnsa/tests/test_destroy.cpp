#include <gtest/gtest.h>
#include <fstream>
#include "instance.h"
#include "solution.h"
#include "greedy.h"
#include "destroy.h"
#include "constants.h"

using namespace std;

class DestroyTest : public ::testing::Test {
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

const char* DestroyTest::TEST_FILE         = "test_destroy_instance.txt";
const int   DestroyTest::TEST_BIN_COSTS[5] = {60, 80, 100, 120, 150}    ;


TEST_F (DestroyTest, MaxGapEmptySolution) {
    Solution solution(5, TEST_BIN_COSTS);

    EXPECT_EQ(max_gap(solution), 0);
}

TEST_F (DestroyTest, MaxGapMultipleBins) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);
    solution.new_bin(2);

    solution.alloc(0, 0, 1, 20);
    solution.alloc(1, 1, 2, 30);
    solution.alloc(2, 2, 3, 70);

    EXPECT_EQ(max_gap(solution), 50);
}

TEST_F (DestroyTest, MaxGapFullyUsedBin) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.alloc(0, 1, 1, 80);

    EXPECT_EQ(max_gap(solution), 0);
}

TEST_F (DestroyTest, ProbWeightZeroGap) {
    Bin bin(1);
    bin.s = 80;

    EXPECT_FLOAT_EQ(prob_weight(bin, 0), 0.1f);
}

TEST_F (DestroyTest, ProbWeightMaxGap) {
    int max_gap = 80;

    Bin bin(1);
    bin.s =  0;

    EXPECT_FLOAT_EQ(prob_weight(bin, max_gap), 1.0f);
}

TEST_F (DestroyTest, DestroySolutionEmptySolution) {
    Solution solution(5, TEST_BIN_COSTS);

    vector <int> result = destroy_solution(solution, 0.5f);

    EXPECT_EQ(solution.size(), 0);
    EXPECT_EQ(result  .size(), 0);
}

TEST_F (DestroyTest, DestroySolutionZeroProbability) {
    Instance instance(TEST_FILE);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy2);

    Solution solution = greedy.initial_solution();

    int size = solution.size();
    vector <int> result = destroy_solution(solution, 0.0f);

    EXPECT_EQ(result  .size(), 0   );
    EXPECT_EQ(solution.size(), size);
}

TEST_F (DestroyTest, DestroySolutionFullProbability) {
    Instance instance(TEST_FILE);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy2);

    Solution solution = greedy.initial_solution();

    int size = solution.size();
    vector <int> result = destroy_solution(solution, 1.0f);

    EXPECT_GE(result  .size(), 0   );
    EXPECT_LE(solution.size(), size);
}

TEST_F (DestroyTest, DestroySolutionWeightedProbability) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(2);
    solution.alloc(0, 0, 1, 10);
    solution.alloc(1, 2, 2, 90);

    vector <int> result = destroy_solution(solution, 0.8f);

    EXPECT_GE(result  .size(), 0);
    EXPECT_LE(result  .size(), 2);
    EXPECT_EQ(solution.size(), 2 - result.size());
}