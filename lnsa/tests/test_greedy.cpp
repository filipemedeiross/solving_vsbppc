#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "instance.h"
#include "solution.h"
#include "greedy.h"

using namespace std;


class GreedyTest : public ::testing::Test {
    protected:
        static const char* TEST_FILE;
        static const int   TEST_BIN_COSTS[5];

        static void SetUpTestSuite() {
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

const char* GreedyTest::TEST_FILE         = "test_greedy_instance.txt";
const int   GreedyTest::TEST_BIN_COSTS[5] = {60, 80, 100, 120, 150};


TEST_F (GreedyTest, ChooserGreedy1Test) {
    Instance instance(TEST_FILE);

    Bin bin(1);
    bin.add(1, 10, 2);

    GreedyF f = chooser_greedy1(instance);

    float result   = f       (5, 2, bin, TEST_BIN_COSTS);
    float expected = greedy1 (5, 2, bin, TEST_BIN_COSTS);

    EXPECT_FLOAT_EQ(result, expected);
}

TEST_F (GreedyTest, ChooserGreedy2Test) {
    Instance instance(TEST_FILE);

    Bin bin(1);
    bin.add(1, 10, 2);

    GreedyF f = chooser_greedy2(instance);

    float result   = f       (5, 2, bin, TEST_BIN_COSTS);
    float expected = greedy2 (5, 2, bin, TEST_BIN_COSTS);

    EXPECT_FLOAT_EQ (result, expected);
}

TEST_F (GreedyTest, BestAllocDefaultConstructor) {
    BestAlloc alloc;

    EXPECT_EQ(alloc.i, 0);
    EXPECT_EQ(alloc.t, 0);
    EXPECT_EQ(alloc.k, 0);
    EXPECT_FLOAT_EQ(alloc.cost, 0.0f);
}

TEST_F (GreedyTest, BestAllocParamConstructor) {
    BestAlloc alloc(1, 2, 3, 4.5f);

    EXPECT_EQ(alloc.i, 1);
    EXPECT_EQ(alloc.t, 2);
    EXPECT_EQ(alloc.k, 3);
    EXPECT_FLOAT_EQ(alloc.cost, 4.5f);
}

TEST_F (GreedyTest, BestAllocOperatorTest) {
    BestAlloc alloc;

    alloc(5, 6, 7, 8.9f);

    EXPECT_EQ(alloc.i, 5);
    EXPECT_EQ(alloc.t, 6);
    EXPECT_EQ(alloc.k, 7);
    EXPECT_FLOAT_EQ(alloc.cost, 8.9f);
}

TEST_F (GreedyTest, InitialSolutionTest) {
    int total_items;
    Instance instance(TEST_FILE);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy1);

    Solution solution = greedy.initial_solution();

    ASSERT_GE(solution.size()   , 0);
    ASSERT_GE(solution.get_obj(), 0);

    total_items = 0;
    for (int i = 0; i < solution.size(); i++)
        total_items += solution[i]->n;

    EXPECT_EQ(total_items, instance.size());
}

TEST_F (GreedyTest, GreedySolutionWithEmptyVector) {
    Instance instance(TEST_FILE);
    Solution solution(instance.size(), TEST_BIN_COSTS);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy1);

    vector<int> empty_vector;
    greedy.greedy_solution(solution, empty_vector);

    EXPECT_EQ(solution.size()   , 0);
    EXPECT_EQ(solution.get_obj(), 0);
}

TEST_F (GreedyTest, GreedySolutionWithSingleItem) {
    Instance instance(TEST_FILE);
    Solution solution(instance.size(), TEST_BIN_COSTS);
    Greedy   greedy  (instance, 5, TEST_BIN_COSTS, chooser_greedy1);

    vector<int> single_item = {0};
    greedy.greedy_solution(solution, single_item);

    EXPECT_GE(solution.size()   , 1);
    EXPECT_GT(solution.get_obj(), 0);
}

TEST_F (GreedyTest, BestAllocAssignmentTest) {
    BestAlloc alloc1(1, 2, 3, 4.0f);
    BestAlloc alloc2;

    alloc2 = alloc1;

    EXPECT_EQ(alloc2.i, alloc1.i);
    EXPECT_EQ(alloc2.t, alloc1.t);
    EXPECT_EQ(alloc2.k, alloc1.k);
    EXPECT_FLOAT_EQ(alloc2.cost, alloc1.cost);
}