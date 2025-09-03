#include <gtest/gtest.h>
#include "bin.h"
#include "solution.h"

class SolutionTest : public ::testing::Test {
    protected:
        static const int TEST_BIN_COSTS[5];

        void SetUp   () override {}
        void TearDown() override {}
};

const int SolutionTest::TEST_BIN_COSTS[5] = {
    60 ,
    80 ,
    100,
    120,
    150,
};

TEST_F (SolutionTest, ConstructorTest) {
    Solution solution(10, TEST_BIN_COSTS);

    EXPECT_EQ(solution.size   (), 0);
    EXPECT_EQ(solution.get_obj(), 0);
}

TEST_F (SolutionTest, NewBinTest) {
    Bin*     bin;
    Solution solution(5, TEST_BIN_COSTS);

    bin = solution.new_bin(2);

    ASSERT_EQ(bin->k, 2);
    ASSERT_EQ(bin->s, 0);

    EXPECT_EQ(solution.size   (), 1  );
    EXPECT_EQ(solution.get_obj(), 100);
}

TEST_F (SolutionTest, MultipleBinsTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);
    solution.new_bin(3);

    EXPECT_EQ(solution.size   (), 3            );
    EXPECT_EQ(solution.get_obj(), 60 + 80 + 120);
}

TEST_F (SolutionTest, OperatorBracketTest) {
    Solution solution(5, TEST_BIN_COSTS);

    Bin* bin1 = solution.new_bin(1);
    Bin* bin2 = solution.new_bin(2);

    EXPECT_EQ(solution[0], bin1);
    EXPECT_EQ(solution[1], bin2);

    EXPECT_THROW(solution[2], std::out_of_range);
}

TEST_F (SolutionTest, EraseBinTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);
    solution.new_bin(2);
    solution.erase_bin(1);

    EXPECT_EQ(solution.size   (), 2       );
    EXPECT_EQ(solution.get_obj(), 60 + 100);
}

TEST_F (SolutionTest, EraseBinLastTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);
    solution.erase_bin(1);

    EXPECT_EQ(solution.size   (), 1 );
    EXPECT_EQ(solution.get_obj(), 60);
}

TEST_F (SolutionTest, AllocTest) {
    Bin* bin;
    Solution solution(5, TEST_BIN_COSTS);

    bin = solution.new_bin(1);
    solution.alloc(0, 2, 5, 30);

    ASSERT_EQ(solution.get_obj(), 100);

    EXPECT_EQ  (bin->k, 2 );
    EXPECT_EQ  (bin->s, 30);
    EXPECT_TRUE(bin->has_item(5));
}

TEST_F (SolutionTest, AllocNewBinTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.alloc(0, 2, 5, 30);

    ASSERT_EQ(solution.size   (),   1);
    ASSERT_EQ(solution.get_obj(), 100);
}

TEST_F (SolutionTest, DeallocTest) {
    Bin* bin;
    Solution solution(5, TEST_BIN_COSTS);

    bin = solution.new_bin(0);

    solution.alloc  (0, 1, 4, 30);
    solution.alloc  (0, 2, 5, 30);
    solution.dealloc(0, 1, 5, 30);

    ASSERT_EQ(solution.get_obj(), 80);

    EXPECT_EQ(bin->k, 1 );
    EXPECT_EQ(bin->s, 30);
    EXPECT_TRUE (bin->has_item(4));
    EXPECT_FALSE(bin->has_item(5));
}

TEST_F (SolutionTest, ReinsertTest) {
    int item;
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);

    solution.alloc(0, 0, 5, 30);
    solution.alloc(1, 1, 6, 40);

    item = solution.reinsert(0, 1, 0, 1, 5, 30);

    ASSERT_EQ(item, 5);

    EXPECT_EQ(solution[0]->s, 0 );
    EXPECT_EQ(solution[1]->s, 70);
    EXPECT_FALSE(solution[0]->has_item(5));
    EXPECT_TRUE (solution[1]->has_item(5));
}

TEST_F (SolutionTest, SwapTest) {
    int item;
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);

    solution.alloc(0, 0, 5, 30);
    solution.alloc(1, 1, 6, 40);

    item = solution.swap(0, 1, 0, 1, 5, 6, 30, 40);

    ASSERT_EQ(item, 6);

    EXPECT_EQ(solution[0]->s, 40);
    EXPECT_EQ(solution[1]->s, 30);
    EXPECT_TRUE (solution[0]->has_item(6));
    EXPECT_TRUE (solution[1]->has_item(5));
    EXPECT_FALSE(solution[0]->has_item(5));
    EXPECT_FALSE(solution[1]->has_item(6));
}

TEST_F (SolutionTest, RelocBinTest) {
    bool has5, has6;
    std::vector<int> items;
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);

    solution.alloc(0, 0, 5, 30);
    solution.alloc(0, 0, 6, 20);
    solution.reloc_bin(0, &items);

    ASSERT_EQ(solution.size   (), 1 );
    ASSERT_EQ(solution.get_obj(), 80);

    has5 = has6 = false;
    for (int item : items) {
        if (item == 5) has5 = true;
        if (item == 6) has6 = true;
    }

    EXPECT_TRUE(has5);
    EXPECT_TRUE(has6);
    EXPECT_EQ(items.size(), 2);
}

TEST_F (SolutionTest, AssignmentOperatorTest) {
    Solution solution1(5, TEST_BIN_COSTS);
    Solution solution2(5, TEST_BIN_COSTS);

    solution1.new_bin(0);
    solution1.new_bin(2);
    solution1.alloc(0, 0, 5, 30);
    solution1.alloc(1, 2, 6, 40);

    solution2 = solution1;

    EXPECT_EQ(solution2.size   (), 2  );
    EXPECT_EQ(solution2.get_obj(), 160);

    EXPECT_EQ(solution2[0]->k, 0);
    EXPECT_EQ(solution2[1]->k, 2);
    EXPECT_TRUE(solution2[0]->has_item(5));
    EXPECT_TRUE(solution2[1]->has_item(6));
}

TEST_F (SolutionTest, ClearTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(1);
    solution.alloc(0, 0, 5, 30);
    solution.alloc(1, 1, 6, 40);

    ASSERT_EQ(solution.size   (), 2  );
    ASSERT_EQ(solution.get_obj(), 140);

    solution.clear();

    EXPECT_EQ(solution.size   (), 0);
    EXPECT_EQ(solution.get_obj(), 0);
}

TEST_F (SolutionTest, LargeSolutionTest) {
    Solution solution(1000, TEST_BIN_COSTS);

    for (int i = 0; i < 50; i++)
        solution.new_bin(i % 5);

    EXPECT_EQ(solution.size(), 50);

    for (int i = 49; i >= 40; i--)
        solution.erase_bin(i);

    EXPECT_EQ(solution.size(), 40);
}

TEST_F (SolutionTest, DescribeTest) {
    Solution solution(5, TEST_BIN_COSTS);

    solution.new_bin(0);
    solution.new_bin(2);
    solution.alloc(0, 0, 5, 30);
    solution.alloc(1, 2, 6, 40);

    EXPECT_NO_THROW(solution.describe());
}