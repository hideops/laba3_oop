#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Tochka {
    double x, y;
    Tochka() : x(0), y(0) {}
    Tochka(double x_val, double y_val) : x(x_val), y(y_val) {}
    
    bool operator==(const Tochka& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }
};

std::ostream& operator<<(std::ostream& os, const Tochka& t) {
    return os << "(" << t.x << ", " << t.y << ")";
}

class Figura {
public:
    virtual ~Figura() = default;
    virtual Tochka centr() const = 0;
    virtual double ploshad() const = 0;
    virtual bool ravno(const Figura& other) const = 0;
    virtual std::unique_ptr<Figura> klon() const = 0;
};

class Romb : public Figura {
private:
    Tochka a, b, c, d;

public:
    Romb() = default;
    Romb(Tochka a_, Tochka b_, Tochka c_, Tochka d_) : a(a_), b(b_), c(c_), d(d_) {}

    std::unique_ptr<Figura> klon() const override { 
        return std::make_unique<Romb>(*this); 
    }

    Tochka centr() const override {
        return Tochka((a.x + c.x) / 2, (a.y + c.y) / 2);
    }

    double ploshad() const override {
        double d1 = std::sqrt(std::pow(a.x - c.x, 2) + std::pow(a.y - c.y, 2));
        double d2 = std::sqrt(std::pow(b.x - d.x, 2) + std::pow(b.y - d.y, 2));
        return (d1 * d2) / 2;
    }

    bool ravno(const Figura& other) const override {
        auto* r = dynamic_cast<const Romb*>(&other);
        if (!r) return false;
        return a == r->a && b == r->b && c == r->c && d == r->d;
    }
};

class Pjatiugolnik : public Figura {
private:
    std::vector<Tochka> tochki;

public:
    Pjatiugolnik() : tochki(5) {}
    Pjatiugolnik(const std::vector<Tochka>& t) : tochki(t) {}

    std::unique_ptr<Figura> klon() const override { 
        return std::make_unique<Pjatiugolnik>(*this); 
    }

    Tochka centr() const override {
        Tochka c;
        for (const auto& t : tochki) {
            c.x += t.x;
            c.y += t.y;
        }
        c.x /= tochki.size();
        c.y /= tochki.size();
        return c;
    }

    double ploshad() const override {
        double s = 0;
        for (size_t i = 0; i < tochki.size(); ++i) {
            const auto& p1 = tochki[i];
            const auto& p2 = tochki[(i + 1) % tochki.size()];
            s += p1.x * p2.y - p2.x * p1.y;
        }
        return std::abs(s) / 2;
    }

    bool ravno(const Figura& other) const override {
        auto* p = dynamic_cast<const Pjatiugolnik*>(&other);
        if (!p) return false;
        return tochki == p->tochki;
    }
};

class Shestiugolnik : public Figura {
private:
    std::vector<Tochka> tochki;

public:
    Shestiugolnik() : tochki(6) {}
    Shestiugolnik(const std::vector<Tochka>& t) : tochki(t) {}

    std::unique_ptr<Figura> klon() const override { 
        return std::make_unique<Shestiugolnik>(*this); 
    }

    Tochka centr() const override {
        Tochka c;
        for (const auto& t : tochki) {
            c.x += t.x;
            c.y += t.y;
        }
        c.x /= tochki.size();
        c.y /= tochki.size();
        return c;
    }

    double ploshad() const override {
        double s = 0;
        for (size_t i = 0; i < tochki.size(); ++i) {
            const auto& p1 = tochki[i];
            const auto& p2 = tochki[(i + 1) % tochki.size()];
            s += p1.x * p2.y - p2.x * p1.y;
        }
        return std::abs(s) / 2;
    }

    bool ravno(const Figura& other) const override {
        auto* h = dynamic_cast<const Shestiugolnik*>(&other);
        if (!h) return false;
        return tochki == h->tochki;
    }
};

class Kollektsiya {
private:
    std::vector<std::unique_ptr<Figura>> figury;

public:
    void dobavit(std::unique_ptr<Figura> fig) {
        figury.push_back(std::move(fig));
    }

    void udalit(size_t index) {
        if (index < figury.size()) {
            figury.erase(figury.begin() + index);
        }
    }

    double obshayaPloshad() const {
        double sum = 0;
        for (const auto& fig : figury) {
            sum += fig->ploshad();
        }
        return sum;
    }

    size_t razmer() const {
        return figury.size();
    }

    const Figura* poluchit(size_t index) const {
        if (index < figury.size()) {
            return figury[index].get();
        }
        return nullptr;
    }
};

int main() {
    Kollektsiya kol;
    
    Tochka r1(0, 0), r2(5, 5), r3(10, 0), r4(5, -5);
    kol.dobavit(std::make_unique<Romb>(r1, r2, r3, r4));
    
    std::vector<Tochka> pPoints = {
        Tochka(0, 0), Tochka(2, 1), Tochka(1, 3), 
        Tochka(-1, 3), Tochka(-2, 1)
    };
    kol.dobavit(std::make_unique<Pjatiugolnik>(pPoints));
    
    std::vector<Tochka> hPoints = {
        Tochka(0, 0), Tochka(2, 0), Tochka(3, 1),
        Tochka(2, 2), Tochka(0, 2), Tochka(-1, 1)
    };
    kol.dobavit(std::make_unique<Shestiugolnik>(hPoints));
    
    std::cout << "Vsego figur: " << kol.razmer() << std::endl;
    std::cout << "Obshaya ploshad: " << kol.obshayaPloshad() << std::endl;
    
    return 0;
}
