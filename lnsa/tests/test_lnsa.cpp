#include <gtest/gtest.h>
#include <fstream>
#include "instance.h"
#include "solution.h"
#include "greedy.h"
#include "lnsa.h"
#include "constants.h"

using namespace std;

class LnsaTest : public ::testing::Test {
    protected:
        static const char* TEST_FILE;
        static const int   TEST_BIN_COSTS[5];

        static void SetUpTestSuite    () {
            create_testfile();
        }

        static void TearDownTestSuite () {
            remove(TEST_FILE);
        }

        static void create_testfile () {
            ofstream file(TEST_FILE);

            file << "4"        << endl;
            file << "1 10 2 3" << endl;
            file << "2 15 4"   << endl;
            file << "3 20"     << endl;
            file << "4 25"     << endl;

            file.close();
        }
};

const char* LnsaTest::TEST_FILE         = "test_lnsa_instance.txt";
const int   LnsaTest::TEST_BIN_COSTS[5] = {60, 80, 100, 120, 150} ;


TEST_F (LnsaTest, BasicLnsaExecution) {
    int verbose  =    0;
    int patience =   10;
    float      p = 0.3f;

    Instance instance(TEST_FILE);
    GreedyChooser g = chooser_greedy1;

    Solution result = lnsa(instance, patience, p, g, verbose);

    ASSERT_GT(result.size()   , 0);
    ASSERT_GT(result.get_obj(), 0);

    int total_items = 0;
    for (int i = 0; i < result.size(); i++)
        total_items += result[i]->n;

    EXPECT_EQ(total_items, instance.size());
}

TEST_F (LnsaTest, LnsaWithZeroPatience) {
    int patience =    0;
    int verbose  =    0;
    float      p = 0.2f;

    Instance instance(TEST_FILE);
    GreedyChooser g = chooser_greedy1;

    Solution result = lnsa(instance, patience, p, g, verbose);

    ASSERT_GT(result.size()   , 0);
    ASSERT_GT(result.get_obj(), 0);

    int total_items = 0;
    for (int i = 0; i < result.size(); i++)
        total_items += result[i]->n;

    EXPECT_EQ(total_items, instance.size());
}