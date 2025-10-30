#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <memory>
#include "main.cpp"

TEST(TochkaTest, Sozdanie) {
    Tochka t1;
    EXPECT_DOUBLE_EQ(t1.x, 0);
    EXPECT_DOUBLE_EQ(t1.y, 0);
    
    Tochka t2(3.5, 2.1);
    EXPECT_DOUBLE_EQ(t2.x, 3.5);
    EXPECT_DOUBLE_EQ(t2.y, 2.1);
}

TEST(TochkaTest, Sravnenie) {
    Tochka t1(1.0, 2.0);
    Tochka t2(1.0, 2.0);
    Tochka t3(1.1, 2.0);
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(RombTest, Ploshad) {
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    Romb romb(a, b, c, d);
    
    double expected_area = (std::sqrt(100) * std::sqrt(100)) / 2;
    EXPECT_NEAR(romb.ploshad(), expected_area, 1e-9);
}

TEST(RombTest, Centr) {
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    Romb romb(a, b, c, d);
    
    Tochka center = romb.centr();
    EXPECT_DOUBLE_EQ(center.x, 5.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
}

TEST(RombTest, Klonirovanie) {
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    Romb romb(a, b, c, d);
    
    auto klon = romb.klon();
    EXPECT_TRUE(romb.ravno(*klon));
}

TEST(PjatiugolnikTest, Ploshad) {
    std::vector<Tochka> points = {
        Tochka(0, 0), Tochka(2, 0), Tochka(2, 1),
        Tochka(1, 2), Tochka(0, 1)
    };
    Pjatiugolnik pentagon(points);
    
    double area = pentagon.ploshad();
    EXPECT_GT(area, 0);
}

TEST(PjatiugolnikTest, Centr) {
    std::vector<Tochka> points = {
        Tochka(0, 0), Tochka(2, 0), Tochka(2, 2),
        Tochka(1, 3), Tochka(0, 2)
    };
    Pjatiugolnik pentagon(points);
    
    Tochka center = pentagon.centr();
    EXPECT_NEAR(center.x, 1.0, 1e-9);
    EXPECT_NEAR(center.y, 1.4, 1e-9);
}

TEST(ShestiugolnikTest, Ploshad) {
    std::vector<Tochka> points = {
        Tochka(0, 0), Tochka(2, 0), Tochka(3, 1),
        Tochka(2, 2), Tochka(0, 2), Tochka(-1, 1)
    };
    Shestiugolnik hexagon(points);
    
    double area = hexagon.ploshad();
    EXPECT_GT(area, 0);
}

TEST(KollektsiyaTest, Dobavlenie) {
    Kollektsiya kol;
    EXPECT_EQ(kol.razmer(), 0);
    
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    kol.dobavit(std::make_unique<Romb>(a, b, c, d));
    
    EXPECT_EQ(kol.razmer(), 1);
}

TEST(KollektsiyaTest, Udalenie) {
    Kollektsiya kol;
    
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    kol.dobavit(std::make_unique<Romb>(a, b, c, d));
    
    std::vector<Tochka> points = {
        Tochka(0, 0), Tochka(2, 0), Tochka(2, 1),
        Tochka(1, 2), Tochka(0, 1)
    };
    kol.dobavit(std::make_unique<Pjatiugolnik>(points));
    
    EXPECT_EQ(kol.razmer(), 2);
    kol.udalit(0);
    EXPECT_EQ(kol.razmer(), 1);
}

TEST(KollektsiyaTest, PloshadPustoy) {
    Kollektsiya kol;
    EXPECT_DOUBLE_EQ(kol.obshayaPloshad(), 0.0);
}

TEST(KollektsiyaTest, ObshayaPloshad) {
    Kollektsiya kol;
    
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    kol.dobavit(std::make_unique<Romb>(a, b, c, d));
    
    std::vector<Tochka> points = {
        Tochka(0, 0), Tochka(2, 0), Tochka(2, 1),
        Tochka(1, 2), Tochka(0, 1)
    };
    kol.dobavit(std::make_unique<Pjatiugolnik>(points));
    
    double total_area = kol.obshayaPloshad();
    EXPECT_GT(total_area, 0);
}

TEST(KollektsiyaTest, PoluchenieFigury) {
    Kollektsiya kol;
    
    Tochka a(0, 0), b(5, 5), c(10, 0), d(5, -5);
    kol.dobavit(std::make_unique<Romb>(a, b, c, d));
    
    const Figura* fig = kol.poluchit(0);
    EXPECT_NE(fig, nullptr);
    
    const Figura* invalid_fig = kol.poluchit(5);
    EXPECT_EQ(invalid_fig, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
