#include <iostream>
#include <vector>
#include <cmath>

struct Tch {
    double x, y;
    Tch() : x(0), y(0) {}
    Tch(double a, double b) : x(a), y(b) {}
};

class Fig {
public:
    virtual ~Fig() = default;
    virtual Tch center() const = 0;
    virtual double square() const = 0;
};

class Romb : public Fig {
    Tch p1, p2, p3, p4;
public:
    Romb(Tch a, Tch b, Tch c, Tch d) : p1(a), p2(b), p3(c), p4(d) {}
    
    Tch center() const override {
        return Tch((p1.x + p3.x)/2, (p1.y + p3.y)/2);
    }
    
    double square() const override {
        double d1 = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
        double d2 = sqrt(pow(p2.x - p4.x, 2) + pow(p2.y - p4.y, 2));
        return d1 * d2 / 2;
    }
};

class Five : public Fig {
    std::vector<Tch> points;
public:
    Five(std::vector<Tch> p) : points(p) {}
    
    Tch center() const override {
        Tch c;
        for(auto& p : points) {
            c.x += p.x;
            c.y += p.y;
        }
        c.x /= points.size();
        c.y /= points.size();
        return c;
    }
    
    double square() const override {
        double s = 0;
        for(int i = 0; i < points.size(); i++) {
            int j = (i+1) % points.size();
            s += points[i].x * points[j].y - points[j].x * points[i].y;
        }
        return abs(s) / 2;
    }
};

class Six : public Fig {
    Tch pts[6];
public:
    Six(Tch p0, Tch p1, Tch p2, Tch p3, Tch p4, Tch p5) {
        pts[0] = p0; pts[1] = p1; pts[2] = p2;
        pts[3] = p3; pts[4] = p4; pts[5] = p5;
    }
    
    Tch center() const override {
        Tch c;
        for(int i = 0; i < 6; i++) {
            c.x += pts[i].x;
            c.y += pts[i].y;
        }
        c.x /= 6;
        c.y /= 6;
        return c;
    }
    
    double square() const override {
        double s = 0;
        for(int i = 0; i < 6; i++) {
            int j = (i+1) % 6;
            s += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
        }
        return abs(s) / 2;
    }
};

class Storage {
    std::vector<Fig*> figs;
public:
    void add(Fig* f) {
        figs.push_back(f);
    }
    
    double total() const {
        double sum = 0;
        for(auto f : figs) {
            sum += f->square();
        }
        return sum;
    }
    
    int count() const {
        return figs.size();
    }
    
    ~Storage() {
        for(auto f : figs) delete f;
    }
};

int main() {
    Storage s;
    s.add(new Romb(Tch(0,0), Tch(3,4), Tch(6,0), Tch(3,-4)));
    
    std::vector<Tch> fivePoints = {
        Tch(0,0), Tch(2,0), Tch(3,1), Tch(2,2), Tch(0,2)
    };
    s.add(new Five(fivePoints));
    
    s.add(new Six(
        Tch(0,0), Tch(2,0), Tch(3,1),
        Tch(2,2), Tch(0,2), Tch(-1,1)
    ));
    
    std::cout << "Figures: " << s.count() << " Total area: " << s.total() << std::endl;
    
    return 0;
}
