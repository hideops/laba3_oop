#include <iostream>
#include <vector>
#include <cmath>

struct Tch {
    double x_, y_;
    Tch() { x_ = 0; y_ = 0; }
    Tch(double x, double y) { x_ = x; y_ = y; }
    
    bool operator==(const Tch& o) const {
        return std::fabs(x_ - o.x_) < 1e-7 && std::fabs(y_ - o.y_) < 1e-7;
    }
};

class Fg {
public:
    virtual ~Fg() = default;
    virtual Tch get_c() const = 0;
    virtual double get_s() const = 0;
    virtual Fg* make_copy() const = 0;
    virtual bool is_same(const Fg* o) const = 0;
};

class Rb : public Fg {
    Tch a_, b_, c_, d_;

public:
    Rb() = default;
    Rb(Tch a, Tch b, Tch c, Tch d) : a_(a), b_(b), c_(c), d_(d) {}

    Fg* make_copy() const override { 
        return new Rb(*this); 
    }

    Tch get_c() const override {
        return Tch((a_.x_ + c_.x_) / 2.0, (a_.y_ + c_.y_) / 2.0);
    }

    double get_s() const override {
        double ac = std::sqrt((a_.x_ - c_.x_)*(a_.x_ - c_.x_) + (a_.y_ - c_.y_)*(a_.y_ - c_.y_));
        double bd = std::sqrt((b_.x_ - d_.x_)*(b_.x_ - d_.x_) + (b_.y_ - d_.y_)*(b_.y_ - d_.y_));
        return ac * bd / 2.0;
    }

    bool is_same(const Fg* o) const override {
        if (auto p = dynamic_cast<const Rb*>(o)) {
            return a_ == p->a_ && b_ == p->b_ && c_ == p->c_ && d_ == p->d_;
        }
        return false;
    }
};

class Pt : public Fg {
    std::vector<Tch> pts_;

public:
    Pt() : pts_(5) {}
    Pt(std::vector<Tch> p) : pts_(std::move(p)) {}

    Fg* make_copy() const override { 
        return new Pt(*this); 
    }

    Tch get_c() const override {
        Tch c;
        for (const auto& p : pts_) {
            c.x_ += p.x_;
            c.y_ += p.y_;
        }
        c.x_ /= pts_.size();
        c.y_ /= pts_.size();
        return c;
    }

    double get_s() const override {
        double sum = 0.0;
        int n = pts_.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            sum += pts_[i].x_ * pts_[j].y_ - pts_[j].x_ * pts_[i].y_;
        }
        return std::abs(sum) / 2.0;
    }

    bool is_same(const Fg* o) const override {
        if (auto p = dynamic_cast<const Pt*>(o)) {
            return pts_ == p->pts_;
        }
        return false;
    }
};

class Hx : public Fg {
    std::vector<Tch> pts_;

public:
    Hx() : pts_(6) {}
    Hx(std::vector<Tch> p) : pts_(std::move(p)) {}

    Fg* make_copy() const override { 
        return new Hx(*this); 
    }

    Tch get_c() const override {
        Tch c;
        for (const auto& p : pts_) {
            c.x_ += p.x_;
            c.y_ += p.y_;
        }
        c.x_ /= pts_.size();
        c.y_ /= pts_.size();
        return c;
    }

    double get_s() const override {
        double sum = 0.0;
        int n = pts_.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            sum += pts_[i].x_ * pts_[j].y_ - pts_[j].x_ * pts_[i].y_;
        }
        return std::abs(sum) / 2.0;
    }

    bool is_same(const Fg* o) const override {
        if (auto p = dynamic_cast<const Hx*>(o)) {
            return pts_ == p->pts_;
        }
        return false;
    }
};

class Col {
    std::vector<Fg*> items;

public:
    void add(Fg* f) {
        items.push_back(f);
    }

    void remove(int i) {
        if (i >= 0 && i < items.size()) {
            delete items[i];
            items.erase(items.begin() + i);
        }
    }

    double total_s() const {
        double s = 0.0;
        for (auto f : items) {
            s += f->get_s();
        }
        return s;
    }

    size_t count() const {
        return items.size();
    }

    ~Col() {
        for (auto f : items) {
            delete f;
        }
    }
};

int main() {
    Col c;
    
    Tch p1(0,0), p2(3,4), p3(6,0), p4(3,-4);
    c.add(new Rb(p1, p2, p3, p4));
    
    std::vector<Tch> pent_points = {
        Tch(0,0), Tch(2,0), Tch(3,1), 
        Tch(2,2), Tch(0,2)
    };
    c.add(new Pt(pent_points));
    
    std::vector<Tch> hex_points = {
        Tch(0,0), Tch(2,0), Tch(3,1),
        Tch(2,2), Tch(0,2), Tch(-1,1)
    };
    c.add(new Hx(hex_points));
    
    std::cout << "Figures: " << c.count() << " Area: " << c.total_s() << std::endl;
    
    return 0;
}
