#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Tchk {
    double dx, dy;
    Tchk() : dx(0), dy(0) {}
    Tchk(double xx, double yy) : dx(xx), dy(yy) {}
    
    bool eq(const Tchk& t) const {
        return fabs(dx - t.dx) < 0.0001 && fabs(dy - t.dy) < 0.0001;
    }
};

class Fig {
public:
    virtual ~Fig() {}
    virtual Tchk cntr() const = 0;
    virtual double sqr() const = 0;
    virtual bool same(const Fig* f) const = 0;
    virtual Fig* cpy() const = 0;
};

class Rmb : public Fig {
    Tchk p1, p2, p3, p4;

public:
    Rmb() {}
    Rmb(Tchk a, Tchk b, Tchk c, Tchk d) : p1(a), p2(b), p3(c), p4(d) {}

    Fig* cpy() const override { 
        return new Rmb(*this); 
    }

    Tchk cntr() const override {
        return Tchk((p1.dx + p3.dx) / 2, (p1.dy + p3.dy) / 2);
    }

    double sqr() const override {
        double dd1 = hypot(p1.dx - p3.dx, p1.dy - p3.dy);
        double dd2 = hypot(p2.dx - p4.dx, p2.dy - p4.dy);
        return dd1 * dd2 * 0.5;
    }

    bool same(const Fig* f) const override {
        auto r = dynamic_cast<const Rmb*>(f);
        if (!r) return 0;
        return p1.eq(r->p1) && p2.eq(r->p2) && p3.eq(r->p3) && p4.eq(r->p4);
    }
};

class Png : public Fig {
    std::vector<Tchk> pts;

public:
    Png() : pts(5) {}
    Png(const std::vector<Tchk>& t) : pts(t) {}

    Fig* cpy() const override { 
        return new Png(*this); 
    }

    Tchk cntr() const override {
        Tchk c;
        for (const auto& p : pts) {
            c.dx += p.dx;
            c.dy += p.dy;
        }
        c.dx /= pts.size();
        c.dy /= pts.size();
        return c;
    }

    double sqr() const override {
        double res = 0;
        int n = pts.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            res += pts[i].dx * pts[j].dy - pts[j].dx * pts[i].dy;
        }
        return fabs(res) * 0.5;
    }

    bool same(const Fig* f) const override {
        auto p = dynamic_cast<const Png*>(f);
        if (!p || pts.size() != p->pts.size()) return 0;
        for (size_t i = 0; i < pts.size(); i++) {
            if (!pts[i].eq(p->pts[i])) return 0;
        }
        return 1;
    }
};

class Shg : public Fig {
    std::vector<Tchk> pts;

public:
    Shg() : pts(6) {}
    Shg(const std::vector<Tchk>& t) : pts(t) {}

    Fig* cpy() const override { 
        return new Shg(*this); 
    }

    Tchk cntr() const override {
        Tchk c;
        for (const auto& p : pts) {
            c.dx += p.dx;
            c.dy += p.dy;
        }
        c.dx /= pts.size();
        c.dy /= pts.size();
        return c;
    }

    double sqr() const override {
        double res = 0;
        int n = pts.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            res += pts[i].dx * pts[j].dy - pts[j].dx * pts[i].dy;
        }
        return fabs(res) * 0.5;
    }

    bool same(const Fig* f) const override {
        auto h = dynamic_cast<const Shg*>(f);
        if (!h || pts.size() != h->pts.size()) return 0;
        for (size_t i = 0; i < pts.size(); i++) {
            if (!pts[i].eq(h->pts[i])) return 0;
        }
        return 1;
    }
};

class FArr {
    std::vector<Fig*> arr;

public:
    void add(Fig* f) {
        arr.push_back(f);
    }

    void del(int idx) {
        if (idx >= 0 && idx < arr.size()) {
            delete arr[idx];
            arr.erase(arr.begin() + idx);
        }
    }

    double total() const {
        double sum = 0;
        for (auto f : arr) {
            sum += f->sqr();
        }
        return sum;
    }

    int sz() const {
        return arr.size();
    }

    ~FArr() {
        for (auto f : arr) {
            delete f;
        }
    }
};

int main() {
    FArr fa;
    
    Tchk a1(0,0), a2(3,4), a3(6,0), a4(3,-4);
    fa.add(new Rmb(a1,a2,a3,a4));
    
    std::vector<Tchk> v1 = {Tchk(1,1), Tchk(3,1), Tchk(4,3), Tchk(2,5), Tchk(0,3)};
    fa.add(new Png(v1));
    
    std::vector<Tchk> v2 = {Tchk(0,0), Tchk(2,0), Tchk(3,1), Tchk(2,2), Tchk(0,2), Tchk(-1,1)};
    fa.add(new Shg(v2));
    
    std::cout << "Cnt: " << fa.sz() << " Area: " << fa.total() << std::endl;
    
    return 0;
}
