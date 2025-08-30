#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "instance.h"

using namespace std;

class InstanceTest : public ::testing::Test {
    protected:
        static const char* TEST_FILE;
        static const char* LARGE_TEST_FILE;

        static void SetUpTestSuite () {
            create_testfile();
            create_large_testfile();
        }

        static void TearDownTestSuite () {
            remove(TEST_FILE      );
            remove(LARGE_TEST_FILE);
        }

        static void create_testfile () {
            ofstream file(TEST_FILE);

            file << "4" << endl;
            file << "1 10 2 3" << endl;
            file << "2 15 4"   << endl;
            file << "3 20"     << endl;
            file << "4 25"     << endl;

            file.close();
        }

        static void create_large_testfile () {
            ofstream file(LARGE_TEST_FILE);

            file << "6" << endl;
            file << "1 40 2 3 4" << endl;
            file << "2 50 5 6"   << endl;
            file << "3 60 5"     << endl;
            file << "4 70 6"     << endl;
            file << "5 80"       << endl;
            file << "6 90"       << endl;

            file.close();
        }
};

const char* InstanceTest::TEST_FILE       = "test_instance.txt";
const char* InstanceTest::LARGE_TEST_FILE = "large_test_instance.txt";

TEST_F (InstanceTest, ConstructorTest) {
    Instance instance(TEST_FILE);

    EXPECT_EQ(instance.size(), 4);
}

TEST_F (InstanceTest, ItemSizeAccessTest) {
    Instance instance(TEST_FILE);

    EXPECT_EQ(instance[0], 10);
    EXPECT_EQ(instance[1], 15);
    EXPECT_EQ(instance[2], 20);
    EXPECT_EQ(instance[3], 25);
}

TEST_F (InstanceTest, ConflictGraphTest) {
    Instance instance(TEST_FILE);

    EXPECT_TRUE(instance(0, 1));
    EXPECT_TRUE(instance(1, 0));
    EXPECT_TRUE(instance(0, 2));
    EXPECT_TRUE(instance(2, 0));
    EXPECT_TRUE(instance(1, 3));
    EXPECT_TRUE(instance(3, 1));

    EXPECT_FALSE(instance(2, 3));
    EXPECT_FALSE(instance(3, 2));

    EXPECT_FALSE(instance(0, 0));
    EXPECT_FALSE(instance(1, 1));
    EXPECT_FALSE(instance(2, 2));
    EXPECT_FALSE(instance(3, 3));
}

TEST_F (InstanceTest, ExtendedConflictGraphTest) {
    Instance instance(LARGE_TEST_FILE);

    ASSERT_EQ(instance.size(), 6);

    EXPECT_FALSE(instance(3, 4));
    EXPECT_TRUE (instance(4, 5));
}

TEST_F (InstanceTest, MinimumItemSizeTest) {
    Instance instance(TEST_FILE);

    EXPECT_EQ(instance.s, 10);
}

TEST_F (InstanceTest, DensityCalculationTest) {
    Instance instance(TEST_FILE);

    EXPECT_GE(instance.d, 0.0);
    EXPECT_LE(instance.d, 1.0);
}

TEST_F (InstanceTest, ConflictPointerTest) {
    Instance instance(TEST_FILE);

    int* conflict0 = instance(0);
    int* conflict1 = instance(1);

    ASSERT_NE(conflict0, nullptr);
    ASSERT_NE(conflict1, nullptr);

    EXPECT_NE(conflict0, conflict1);

    EXPECT_FALSE(conflict0[0]);
    EXPECT_TRUE (conflict0[1]);
    EXPECT_TRUE (conflict0[2]);
    EXPECT_FALSE(conflict0[3]);

    EXPECT_TRUE (conflict1[0]);
    EXPECT_FALSE(conflict1[1]);
    EXPECT_FALSE(conflict1[2]);
    EXPECT_TRUE (conflict1[3]);
}

TEST_F (InstanceTest, BoundaryConditionsTest) {
    Instance instance(TEST_FILE);

    EXPECT_NO_THROW(instance[0]);
    EXPECT_NO_THROW(instance[3]);
    EXPECT_NO_THROW(instance(0, 3));
    EXPECT_NO_THROW(instance(3, 0));
}

TEST_F (InstanceTest, LargeInstanceTest) {
    Instance instance(LARGE_TEST_FILE);

    ASSERT_EQ(instance.size(), 6);

    EXPECT_EQ(instance.s, 40);

    EXPECT_EQ(instance[0], 40);
    EXPECT_EQ(instance[5], 90);
    EXPECT_TRUE(instance(0, 1));
    EXPECT_TRUE(instance(2, 4));
    EXPECT_TRUE(instance(3, 5));
}

TEST_F (InstanceTest, PerformanceTest) {
    int i, j, n = 100;
    const char* TEST_PERFORMANCE = "test_performance.txt";

    ofstream file(TEST_PERFORMANCE);

    file << n << endl;
    for (i = 1; i <= n; i++) {
        file << i << " " << (i * 10) << " ";

        for (j = 1; j <= 5 && i + j <= n; j++)
            file << (i + j) << " ";

        file << endl;
    }

    file.close();

    auto start = chrono::high_resolution_clock::now();
    Instance instance(TEST_PERFORMANCE);
    auto end   = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds> (end - start);

    ASSERT_EQ(instance.size(), n);

    EXPECT_LT(duration.count(), 1000);

    remove(TEST_PERFORMANCE);
}
