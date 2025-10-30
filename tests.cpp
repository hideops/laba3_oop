#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "main.cpp"

TEST(TchkTest, Basic) {
    Tchk t1;
    EXPECT_DOUBLE_EQ(t1.dx, 0);
    EXPECT_DOUBLE_EQ(t1.dy, 0);
    
    Tchk t2(2.5, 3.7);
    EXPECT_DOUBLE_EQ(t2.dx, 2.5);
    EXPECT_DOUBLE_EQ(t2.dy, 3.7);
}

TEST(TchkTest, Comparison) {
    Tchk t1(1.1, 2.2), t2(1.1, 2.2), t3(1.1, 2.3);
    EXPECT_TRUE(t1.eq(t2));
    EXPECT_FALSE(t1.eq(t3));
}

TEST(RmbTest, SquareCalculation) {
    Tchk a(0,0), b(3,4), c(6,0), d(3,-4);
    Rmb r(a,b,c,d);
    
    double expected = 24.0;
    EXPECT_NEAR(r.sqr(), expected, 0.001);
}

TEST(RmbTest, CenterCalculation) {
    Tchk a(1,1), b(2,4), c(5,1), d(2,-2);
    Rmb r(a,b,c,d);
    
    Tchk center = r.cntr();
    EXPECT_NEAR(center.dx, 3.0, 0.001);
    EXPECT_NEAR(center.dy, 1.0, 0.001);
}

TEST(RmbTest, CopyAndCompare) {
    Tchk a(0,0), b(2,3), c(4,0), d(2,-3);
    Rmb r1(a,b,c,d);
    Rmb* r2 = dynamic_cast<Rmb*>(r1.cpy());
    
    EXPECT_TRUE(r1.same(r2));
    delete r2;
}

TEST(RmbTest, DifferentRhombus) {
    Tchk a1(0,0), b1(2,3), c1(4,0), d1(2,-3);
    Tchk a2(0,0), b2(3,4), c2(6,0), d2(3,-4);
    Rmb r1(a1,b1,c1,d1), r2(a2,b2,c2,d2);
    
    EXPECT_FALSE(r1.same(&r2));
}

TEST(PngTest, AreaPositive) {
    std::vector<Tchk> v = {
        Tchk(0,0), Tchk(4,0), Tchk(5,2), 
        Tchk(3,4), Tchk(0,3)
    };
    Png p(v);
    
    EXPECT_GT(p.sqr(), 0);
}

TEST(PngTest, CenterLocation) {
    std::vector<Tchk> v = {
        Tchk(0,0), Tchk(4,0), Tchk(4,4), 
        Tchk(2,6), Tchk(0,4)
    };
    Png p(v);
    
    Tchk center = p.cntr();
    EXPECT_NEAR(center.dx, 2.0, 0.001);
    EXPECT_NEAR(center.dy, 2.8, 0.001);
}

TEST(PngTest, SelfComparison) {
    std::vector<Tchk> v = {
        Tchk(1,1), Tchk(3,1), Tchk(4,3), 
        Tchk(2,5), Tchk(0,3)
    };
    Png p1(v);
    Png p2(v);
    
    EXPECT_TRUE(p1.same(&p2));
}

TEST(ShgTest, RegularHexagonArea) {
    std::vector<Tchk> v = {
        Tchk(0,0), Tchk(2,0), Tchk(3,1), 
        Tchk(2,2), Tchk(0,2), Tchk(-1,1)
    };
    Shg s(v);
    
    double area = s.sqr();
    EXPECT_GT(area, 0);
    EXPECT_LT(area, 10);
}

TEST(ShgTest, CenterSymmetry) {
    std::vector<Tchk> v = {
        Tchk(-1,0), Tchk(0,1), Tchk(1,1),
        Tchk(2,0), Tchk(1,-1), Tchk(0,-1)
    };
    Shg s(v);
    
    Tchk center = s.cntr();
    EXPECT_NEAR(center.dx, 0.5, 0.001);
    EXPECT_NEAR(center.dy, 0.0, 0.001);
}

TEST(ShgTest, DifferentHexagons) {
    std::vector<Tchk> v1 = {
        Tchk(0,0), Tchk(1,0), Tchk(1,1),
        Tchk(0,1), Tchk(-1,1), Tchk(-1,0)
    };
    std::vector<Tchk> v2 = {
        Tchk(0,0), Tchk(2,0), Tchk(3,1),
        Tchk(2,2), Tchk(0,2), Tchk(-1,1)
    };
    Shg s1(v1), s2(v2);
    
    EXPECT_FALSE(s1.same(&s2));
}

TEST(FArrTest, EmptyCollection) {
    FArr fa;
    EXPECT_EQ(fa.sz(), 0);
    EXPECT_DOUBLE_EQ(fa.total(), 0.0);
}

TEST(FArrTest, AddMultipleFigures) {
    FArr fa;
    
    Tchk a(0,0), b(1,1), c(2,0), d(1,-1);
    fa.add(new Rmb(a,b,c,d));
    
    std::vector<Tchk> v = {
        Tchk(0,0), Tchk(2,0), Tchk(3,1), 
        Tchk(2,2), Tchk(0,2)
    };
    fa.add(new Png(v));
    
    EXPECT_EQ(fa.sz(), 2);
    EXPECT_GT(fa.total(), 0);
}

TEST(FArrTest, AddRemoveOperations) {
    FArr fa;
    
    Tchk a(0,0), b(1,1), c(2,0), d(1,-1);
    fa.add(new Rmb(a,b,c,d));
    
    std::vector<Tchk> v = {
        Tchk(0,0), Tchk(2,0), Tchk(3,1), 
        Tchk(2,2), Tchk(0,2)
    };
    fa.add(new Png(v));
    
    EXPECT_EQ(fa.sz(), 2);
    fa.del(0);
    EXPECT_EQ(fa.sz(), 1);
    fa.del(0);
    EXPECT_EQ(fa.sz(), 0);
}

TEST(FArrTest, InvalidIndexHandling) {
    FArr fa;
    
    Tchk a(0,0), b(1,1), c(2,0), d(1,-1);
    fa.add(new Rmb(a,b,c,d));
    
    fa.del(5);
    fa.del(-1);
    
    EXPECT_EQ(fa.sz(), 1);
}

TEST(FArrTest, MixedFiguresArea) {
    FArr fa;
    
    Tchk r1(0,0), r2(2,3), r3(4,0), r4(2,-3);
    fa.add(new Rmb(r1,r2,r3,r4));
    
    std::vector<Tchk> pv = {
        Tchk(0,0), Tchk(3,0), Tchk(4,2), 
        Tchk(2,4), Tchk(0,3)
    };
    fa.add(new Png(pv));
    
    std::vector<Tchk> hv = {
        Tchk(0,0), Tchk(2,0), Tchk(3,1),
        Tchk(2,2), Tchk(0,2), Tchk(-1,1)
    };
    fa.add(new Shg(hv));
    
    double total = fa.total();
    EXPECT_GT(total, 0);
    EXPECT_LT(total, 50);
}

TEST(IntegrationTest, ComplexOperations) {
    FArr fa;
    
    Tchk a1(0,0), b1(1,2), c1(2,0), d1(1,-2);
    fa.add(new Rmb(a1,b1,c1,d1));
    
    std::vector<Tchk> v1 = {
        Tchk(1,1), Tchk(3,1), Tchk(4,3), 
        Tchk(2,5), Tchk(0,3)
    };
    fa.add(new Png(v1));
    
    double area1 = fa.total();
    
    std::vector<Tchk> v2 = {
        Tchk(5,5), Tchk(7,5), Tchk(8,6),
        Tchk(7,7), Tchk(5,7), Tchk(4,6)
    };
    fa.add(new Shg(v2));
    
    double area2 = fa.total();
    EXPECT_GT(area2, area1);
    
    fa.del(1);
    double area3 = fa.total();
    EXPECT_LT(area3, area2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
