#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "main.cpp"

TEST(RombTest, Area) {
    Romb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    EXPECT_NEAR(r.square(), 24.0, 0.01);
}

TEST(RombTest, Center) {
    Romb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    Tch c = r.center();
    EXPECT_NEAR(c.x, 3.0, 0.01);
    EXPECT_NEAR(c.y, 0.0, 0.01);
}

TEST(FiveTest, Area) {
    std::vector<Tch> points = {
        Tch(0,0), Tch(4,0), Tch(5,2), Tch(3,4), Tch(0,3)
    };
    Five f(points);
    EXPECT_GT(f.square(), 0);
}

TEST(FiveTest, Center) {
    std::vector<Tch> points = {
        Tch(0,0), Tch(4,0), Tch(4,4), Tch(2,6), Tch(0,4)
    };
    Five f(points);
    Tch c = f.center();
    EXPECT_NEAR(c.x, 2.0, 0.01);
    EXPECT_NEAR(c.y, 2.8, 0.01);
}

TEST(SixTest, Area) {
    Six s(Tch(0,0), Tch(2,0), Tch(3,1), Tch(2,2), Tch(0,2), Tch(-1,1));
    EXPECT_NEAR(s.square(), 6.0, 0.5);
}

TEST(SixTest, Center) {
    Six s(Tch(0,0), Tch(2,0), Tch(3,1), Tch(2,2), Tch(0,2), Tch(-1,1));
    Tch c = s.center();
    EXPECT_NEAR(c.x, 1.0, 0.01);
    EXPECT_NEAR(c.y, 1.0, 0.01);
}

TEST(StorageTest, Empty) {
    Storage s;
    EXPECT_EQ(s.count(), 0);
    EXPECT_DOUBLE_EQ(s.total(), 0.0);
}

TEST(StorageTest, AddOne) {
    Storage s;
    s.add(new Romb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    EXPECT_EQ(s.count(), 1);
    EXPECT_GT(s.total(), 0);
}

TEST(StorageTest, AddMultiple) {
    Storage s;
    s.add(new Romb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    
    std::vector<Tch> points = {
        Tch(0,0), Tch(2,0), Tch(3,1), Tch(2,2), Tch(0,2)
    };
    s.add(new Five(points));
    
    EXPECT_EQ(s.count(), 2);
    EXPECT_GT(s.total(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
