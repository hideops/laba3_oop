#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "main.cpp"

TEST(TchTest, Init) {
    Tch t;
    ASSERT_DOUBLE_EQ(t.x_, 0.0);
    ASSERT_DOUBLE_EQ(t.y_, 0.0);
    
    Tch t2(1.5, -2.5);
    ASSERT_DOUBLE_EQ(t2.x_, 1.5);
    ASSERT_DOUBLE_EQ(t2.y_, -2.5);
}

TEST(TchTest, Equal) {
    Tch t1(1.0, 2.0);
    Tch t2(1.0, 2.0);
    Tch t3(1.0, 2.1);
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(RbTest, Area1) {
    Rb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    EXPECT_NEAR(r.get_s(), 24.0, 1e-6);
}

TEST(RbTest, Area2) {
    Rb r(Tch(1,1), Tch(2,4), Tch(5,1), Tch(2,-2));
    EXPECT_NEAR(r.get_s(), 12.0, 1e-6);
}

TEST(RbTest, Center1) {
    Rb r(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4));
    Tch c = r.get_c();
    EXPECT_NEAR(c.x_, 3.0, 1e-6);
    EXPECT_NEAR(c.y_, 0.0, 1e-6);
}

TEST(RbTest, Center2) {
    Rb r(Tch(1,2), Tch(3,6), Tch(7,2), Tch(3,-2));
    Tch c = r.get_c();
    EXPECT_NEAR(c.x_, 4.0, 1e-6);
    EXPECT_NEAR(c.y_, 2.0, 1e-6);
}

TEST(RbTest, Copy) {
    Rb r1(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1));
    Fg* r2 = r1.make_copy();
    EXPECT_TRUE(r1.is_same(r2));
    delete r2;
}

TEST(RbTest, NotSame) {
    Rb r1(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1));
    Rb r2(Tch(0,0), Tch(2,2), Tch(4,0), Tch(2,-2));
    EXPECT_FALSE(r1.is_same(&r2));
}

TEST(PtTest, Area) {
    std::vector<Tch> pts = {
        Tch(0,0), Tch(4,0), Tch(5,2), 
        Tch(3,4), Tch(0,3)
    };
    Pt p(pts);
    double area = p.get_s();
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 20.0);
}

TEST(PtTest, Center) {
    std::vector<Tch> pts = {
        Tch(0,0), Tch(4,0), Tch(4,4), 
        Tch(2,6), Tch(0,4)
    };
    Pt p(pts);
    Tch c = p.get_c();
    EXPECT_NEAR(c.x_, 2.0, 1e-6);
    EXPECT_NEAR(c.y_, 2.8, 1e-6);
}

TEST(PtTest, Same) {
    std::vector<Tch> pts = {
        Tch(1,1), Tch(3,1), Tch(4,3), 
        Tch(2,5), Tch(0,3)
    };
    Pt p1(pts);
    Pt p2(pts);
    EXPECT_TRUE(p1.is_same(&p2));
}

TEST(HxTest, Area) {
    std::vector<Tch> pts = {
        Tch(0,0), Tch(2,0), Tch(3,1), 
        Tch(2,2), Tch(0,2), Tch(-1,1)
    };
    Hx h(pts);
    double area = h.get_s();
    EXPECT_NEAR(area, 6.0, 0.5);
}

TEST(HxTest, Center) {
    std::vector<Tch> pts = {
        Tch(-1,0), Tch(0,1), Tch(1,1),
        Tch(2,0), Tch(1,-1), Tch(0,-1)
    };
    Hx h(pts);
    Tch c = h.get_c();
    EXPECT_NEAR(c.x_, 0.5, 1e-6);
    EXPECT_NEAR(c.y_, 0.0, 1e-6);
}

TEST(HxTest, Different) {
    std::vector<Tch> pts1 = {
        Tch(0,0), Tch(1,0), Tch(1,1),
        Tch(0,1), Tch(-1,1), Tch(-1,0)
    };
    std::vector<Tch> pts2 = {
        Tch(0,0), Tch(2,0), Tch(3,1),
        Tch(2,2), Tch(0,2), Tch(-1,1)
    };
    Hx h1(pts1), h2(pts2);
    EXPECT_FALSE(h1.is_same(&h2));
}

TEST(ColTest, Empty) {
    Col c;
    EXPECT_EQ(c.count(), 0);
    EXPECT_DOUBLE_EQ(c.total_s(), 0.0);
}

TEST(ColTest, AddOne) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    EXPECT_EQ(c.count(), 1);
    EXPECT_GT(c.total_s(), 0.0);
}

TEST(ColTest, AddMultiple) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    
    std::vector<Tch> pts = {
        Tch(0,0), Tch(2,0), Tch(3,1), 
        Tch(2,2), Tch(0,2)
    };
    c.add(new Pt(pts));
    
    EXPECT_EQ(c.count(), 2);
}

TEST(ColTest, Remove) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    c.add(new Pt(std::vector<Tch>(5)));
    
    EXPECT_EQ(c.count(), 2);
    c.remove(0);
    EXPECT_EQ(c.count(), 1);
    c.remove(0);
    EXPECT_EQ(c.count(), 0);
}

TEST(ColTest, RemoveInvalid) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(1,1), Tch(2,0), Tch(1,-1)));
    
    c.remove(-1);
    c.remove(5);
    
    EXPECT_EQ(c.count(), 1);
}

TEST(ColTest, TotalArea) {
    Col c;
    c.add(new Rb(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4))); // 24
    c.add(new Pt(std::vector<Tch>{
        Tch(0,0), Tch(2,0), Tch(3,1), 
        Tch(2,2), Tch(0,2)
    })); // ~3.5
    
    double total = c.total_s();
    EXPECT_GT(total, 27.0);
    EXPECT_LT(total, 28.0);
}

TEST(ColTest, MixedTypes) {
    Col c;
    
    c.add(new Rb(Tch(0,0), Tch(2,3), Tch(4,0), Tch(2,-3)));
    
    std::vector<Tch> pent = {
        Tch(0,0), Tch(3,0), Tch(4,2), 
        Tch(2,4), Tch(0,3)
    };
    c.add(new Pt(pent));
    
    std::vector<Tch> hex = {
        Tch(0,0), Tch(2,0), Tch(3,1),
        Tch(2,2), Tch(0,2), Tch(-1,1)
    };
    c.add(new Hx(hex));
    
    EXPECT_EQ(c.count(), 3);
    EXPECT_GT(c.total_s(), 0.0);
}

TEST(Integration, Complex) {
    Col c;
    
    double area1 = c.total_s();
    
    c.add(new Rb(Tch(0,0), Tch(1,2), Tch(2,0), Tch(1,-2)));
    double area2 = c.total_s();
    EXPECT_GT(area2, area1);
    
    std::vector<Tch> pent = {
        Tch(1,1), Tch(3,1), Tch(4,3), 
        Tch(2,5), Tch(0,3)
    };
    c.add(new Pt(pent));
    double area3 = c.total_s();
    EXPECT_GT(area3, area2);
    
    c.remove(0);
    double area4 = c.total_s();
    EXPECT_LT(area4, area3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
