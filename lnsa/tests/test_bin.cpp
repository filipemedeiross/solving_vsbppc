#include <gtest/gtest.h>
#include "bin.h"

class BinTest : public ::testing::Test {
    protected:
        void SetUp   () override {}
        void TearDown() override {}
};

TEST_F (BinTest, ConstructorInitialValues) {
    Bin b(1);

    EXPECT_EQ(b.k, 1);
    EXPECT_EQ(b.s, 0);
    EXPECT_EQ(b.n, 0);
    EXPECT_TRUE(b.get_items().empty());
}

TEST_F (BinTest, CopyConstructor) {
    Bin b1(1);

    b1.add(5, 10, 2);

    Bin b2(b1);

    EXPECT_EQ(b2.k,  2);
    EXPECT_EQ(b2.s, 10);
    EXPECT_EQ(b2.n,  1);
    EXPECT_TRUE(b2.has_item(5));
}

TEST_F (BinTest, AssignmentOperator) {
    Bin b1(1);
    Bin b2(2);

    b1.add(3, 15, 4);

    b2 = b1;

    EXPECT_EQ(b2.k,  4);
    EXPECT_EQ(b2.s, 15);
    EXPECT_EQ(b2.n,  1);
    EXPECT_TRUE(b2.has_item(3));
}

TEST_F (BinTest, RemoveItems) {
    Bin b(1);

    b.add(1, 10, 2);
    b.add(2, 20, 3);
    b.remove(1, 10, 5);

    EXPECT_EQ(b.k,  5);
    EXPECT_EQ(b.s, 20);
    EXPECT_EQ(b.n,  1);

    EXPECT_FALSE(b.has_item(1));
    EXPECT_TRUE (b.has_item(2));
}

TEST_F (BinTest, IsFeasible) {
    int conflicts1[5] = {};
    int conflicts2[5] = {0, 1};

    Bin b(1);

    b.add(1, 10, 2);
    b.add(2, 20, 2);

    EXPECT_TRUE (b.is_feasible(conflicts1));
    EXPECT_FALSE(b.is_feasible(conflicts2));
}

TEST_F (BinTest, IsFeasibleWithRemoval) {
    int conflicts[5] = {0, 1, 1};

    Bin b(1);

    b.add(0, 10, 2);
    b.add(1, 20, 2);

    EXPECT_FALSE(b.is_feasible(conflicts, 0));
    EXPECT_TRUE (b.is_feasible(conflicts, 1));
}

TEST_F (BinTest, GetItems) {
    Bin b(1);

    b.add(1, 10, 2);
    b.add(2, 20, 2);

    const std::list <int>& items = b.get_items();

    ASSERT_EQ(items.size(), 2);

    EXPECT_EQ(          *items.begin() , 1);
    EXPECT_EQ(*std::next(items.begin()), 2);
}

TEST_F (BinTest, BoundaryConditions) {
    Bin b(1);

    EXPECT_NO_THROW(b.add   (1, 10, 2));
    EXPECT_NO_THROW(b.remove(1, 10, 3));
    EXPECT_NO_THROW(b.get_items());
}