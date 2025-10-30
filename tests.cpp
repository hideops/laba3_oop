#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "main.cpp"

TEST(TchTest, Default) {
    Tch t;
    EXPECT_DOUBLE_EQ(0.0, t.x_);
    EXPECT_DOUBLE_EQ(0.0, t.y_);
}

TEST(TchTest, WithValues) {
    Tch t(1.5, -2.5);
    EXPECT_DOUBLE_EQ(1.5, t.x_);
    EXPECT_DOUBLE_EQ(-2.5, t.y_);
}

TEST(TchTest, Equal) {
    Tch t1(1, 2), t2(1, 2), t3(1, 3);
    EXPECT_TRUE(t1.eq(t2));
    EXPECT_FALSE(t1.eq(t3));
}

TEST(RbTest, AreaSimple) {
    Rb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    EXPECT_NEAR(24.0, r.area(), 0.001);
}

TEST(RbTest, Center) {
    Rb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    Tch c = r.cent();
    EXPECT_NEAR(3.0, c.x_, 0.001);
    EXPECT_NEAR(0.0, c.y_, 0.001);
}

TEST(RbTest, Copy) {
    Rb r1(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1));
    Fg* r2 = r1.copy();
    EXPECT_TRUE(r1.same(r2));
    delete r2;
}

TEST(RbTest, Different) {
    Rb r1(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1));
    Rb r2(Tch(0,0), Tch(2,2), Tch(4,0), Tch(2,-2));
    EXPECT_FALSE(r1.same(&r2));
}

TEST(PtTest, Area) {
    std::vector<Tch> pts;
    pts.push_back(Tch(0,0));
    pts.push_back(Tch(4,0));
    pts.push_back(Tch(5,2));
    pts.push_back(Tch(3,4));
    pts.push_back(Tch(0,3));
    Pt p(pts);
    EXPECT_GT(p.area(), 0);
}

TEST(PtTest, Center) {
    std::vector<Tch> pts;
    pts.push_back(Tch(0,0));
    pts.push_back(Tch(4,0));
    pts.push_back(Tch(4,4));
    pts.push_back(Tch(2,6));
    pts.push_back(Tch(0,4));
    Pt p(pts);
    Tch c = p.cent();
    EXPECT_NEAR(2.0, c.x_, 0.001);
    EXPECT_NEAR(2.8, c.y_, 0.001);
}

TEST(HxTest, Area) {
    std::vector<Tch> pts;
    pts.push_back(Tch(0,0));
    pts.push_back(Tch(2,0));
    pts.push_back(Tch(3,1));
    pts.push_back(Tch(2,2));
    pts.push_back(Tch(0,2));
    pts.push_back(Tch(-1,1));
    Hx h(pts);
    double a = h.area();
    EXPECT_GT(a, 5.0);
    EXPECT_LT(a, 7.0);
}

TEST(ColTest, Empty) {
    Col c;
    EXPECT_EQ(0, c.size());
    EXPECT_DOUBLE_EQ(0.0, c.total_area());
}

TEST(ColTest, AddOne) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    EXPECT_EQ(1, c.size());
}

TEST(ColTest, AddTwo) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    
    std::vector<Tch> pts;
    pts.push_back(Tch(0,0));
    pts.push_back(Tch(2,0));
    pts.push_back(Tch(3,1));
    pts.push_back(Tch(2,2));
    pts.push_back(Tch(0,2));
    c.add(new Pt(pts));
    
    EXPECT_EQ(2, c.size());
}

TEST(ColTest, Remove) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    c.add(new Pt(std::vector<Tch>(5)));
    
    EXPECT_EQ(2, c.size());
    c.remove(0);
    EXPECT_EQ(1, c.size());
}

TEST(ColTest, RemoveBadIndex) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    
    c.remove(-1);
    c.remove(10);
    
    EXPECT_EQ(1, c.size());
}

TEST(ColTest, TotalArea) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4)));
    
    std::vector<Tch> pts;
    pts.push_back(Tch(0,0));
    pts.push_back(Tch(2,0));
    pts.push_back(Tch(3,1));
    pts.push_back(Tch(2,2));
    pts.push_back(Tch(0,2));
    c.add(new Pt(pts));
    
    double total = c.total_area();
    EXPECT_GT(total, 27.0);
}

TEST(ColTest, ThreeFigures) {
    Col c;
    
    c.add(new Rb(Tch(0,0), Tch(2,3), Tch(4,0), Tch(2,-3)));
    
    std::vector<Tch> pent;
    pent.push_back(Tch(0,0));
    pent.push_back(Tch(3,0));
    pent.push_back(Tch(4,2));
    pent.push_back(Tch(2,4));
    pent.push_back(Tch(0,3));
    c.add(new Pt(pent));
    
    std::vector<Tch> hex;
    hex.push_back(Tch(0,0));
    hex.push_back(Tch(2,0));
    hex.push_back(Tch(3,1));
    hex.push_back(Tch(2,2));
    hex.push_back(Tch(0,2));
    hex.push_back(Tch(-1,1));
    c.add(new Hx(hex));
    
    EXPECT_EQ(3, c.size());
    EXPECT_GT(c.total_area(), 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
