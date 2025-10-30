#include <iostream>
#include <vector>
#include <cmath>

struct Tch {
    double x_, y_;
    Tch() { x_ = 0; y_ = 0; }
    Tch(double x, double y) { x_ = x; y_ = y; }
    
    bool eq(const Tch& o) const {
        return fabs(x_ - o.x_) < 0.001 && fabs(y_ - o.y_) < 0.001;
    }
};

class Fg {
public:
    virtual ~Fg() {}
    virtual Tch cent() const = 0;
    virtual double area() const = 0;
    virtual Fg* copy() const = 0;
    virtual bool same(const Fg* o) const = 0;
};

class Rb : public Fg {
    Tch a_, b_, c_, d_;

public:
    Rb() {}
    Rb(Tch a, Tch b, Tch c, Tch d) : a_(a), b_(b), c_(c), d_(d) {}

    Fg* copy() const override { 
        return new Rb(a_, b_, c_, d_); 
    }

    Tch cent() const override {
        double x = (a_.x_ + c_.x_) / 2;
        double y = (a_.y_ + c_.y_) / 2;
        return Tch(x, y);
    }

    double area() const override {
        double dx1 = a_.x_ - c_.x_;
        double dy1 = a_.y_ - c_.y_;
        double dx2 = b_.x_ - d_.x_;
        double dy2 = b_.y_ - d_.y_;
        double d1 = sqrt(dx1*dx1 + dy1*dy1);
        double d2 = sqrt(dx2*dx2 + dy2*dy2);
        return (d1 * d2) * 0.5;
    }

    bool same(const Fg* o) const override {
        const Rb* r = dynamic_cast<const Rb*>(o);
        if (!r) return false;
        return a_.eq(r->a_) && b_.eq(r->b_) && c_.eq(r->c_) && d_.eq(r->d_);
    }
};

class Pt : public Fg {
    std::vector<Tch> points;

public:
    Pt() { points.resize(5); }
    Pt(const std::vector<Tch>& p) { points = p; }

    Fg* copy() const override { 
        return new Pt(points); 
    }

    Tch cent() const override {
        Tch c;
        for (size_t i = 0; i < points.size(); i++) {
            c.x_ += points[i].x_;
            c.y_ += points[i].y_;
        }
        c.x_ /= points.size();
        c.y_ /= points.size();
        return c;
    }

    double area() const override {
        double s = 0;
        int n = points.size();
        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n;
            s += points[i].x_ * points[next].y_ - points[next].x_ * points[i].y_;
        }
        return fabs(s) / 2.0;
    }

    bool same(const Fg* o) const override {
        const Pt* p = dynamic_cast<const Pt*>(o);
        if (!p || points.size() != p->points.size()) return false;
        for (size_t i = 0; i < points.size(); i++) {
            if (!points[i].eq(p->points[i])) return false;
        }
        return true;
    }
};

class Hx : public Fg {
    std::vector<Tch> pts;

public:
    Hx() { pts.resize(6); }
    Hx(const std::vector<Tch>& p) { pts = p; }

    Fg* copy() const override { 
        return new Hx(pts); 
    }

    Tch cent() const override {
        Tch c;
        for (const auto& p : pts) {
            c.x_ += p.x_;
            c.y_ += p.y_;
        }
        c.x_ /= pts.size();
        c.y_ /= pts.size();
        return c;
    }

    double area() const override {
        double sum = 0;
        int n = pts.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            sum += pts[i].x_ * pts[j].y_ - pts[j].x_ * pts[i].y_;
        }
        return fabs(sum) * 0.5;
    }

    bool same(const Fg* o) const override {
        const Hx* h = dynamic_cast<const Hx*>(o);
        if (!h) return false;
        if (pts.size() != h->pts.size()) return false;
        for (size_t i = 0; i < pts.size(); i++) {
            if (!pts[i].eq(h->pts[i])) return false;
        }
        return true;
    }
};

class Col {
    std::vector<Fg*> figs;

public:
    void add(Fg* f) {
        figs.push_back(f);
    }

    void remove(int idx) {
        if (idx < 0 || idx >= figs.size()) return;
        delete figs[idx];
        figs.erase(figs.begin() + idx);
    }

    double total_area() const {
        double total = 0;
        for (Fg* f : figs) {
            total = total + f->area();
        }
        return total;
    }

    int size() const {
        return figs.size();
    }

    ~Col() {
        for (Fg* f : figs) {
            delete f;
        }
    }
};

int main() {
    Col col;
    
    // Ромб
    Tch p1(0,0), p2(3,4), p3(6,0), p4(3,-4);
    col.add(new Rb(p1, p2, p3, p4));
    
    // Пятиугольник
    std::vector<Tch> pent_pts;
    pent_pts.push_back(Tch(0,0));
    pent_pts.push_back(Tch(2,0));
    pent_pts.push_back(Tch(3,1));
    pent_pts.push_back(Tch(2,2));
    pent_pts.push_back(Tch(0,2));
    col.add(new Pt(pent_pts));
    
    // Шестиугольник  
    std::vector<Tch> hex_pts;
    hex_pts.push_back(Tch(0,0));
    hex_pts.push_back(Tch(2,0));
    hex_pts.push_back(Tch(3,1));
    hex_pts.push_back(Tch(2,2));
    hex_pts.push_back(Tch(0,2));
    hex_pts.push_back(Tch(-1,1));
    col.add(new Hx(hex_pts));
    
    std::cout << "Count: " << col.size() << " Area: " << col.total_area() << std::endl;
    
    return 0;
}
