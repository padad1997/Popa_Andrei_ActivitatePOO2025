#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Avion {
private:
    string model;
    int locuri;

public:
    Avion() : model(""), locuri(0) {}
    Avion(string m, int l) : model(m), locuri(l) {}

    string getModel() const { return model; }
    int getLocuri() const { return locuri; }

    void setModel(string m) { model = m; }
    void setLocuri(int l) { locuri = l; }

    friend ostream& operator<<(ostream& os, const Avion& a) {
        os << "Avion: " << a.model << ", Locuri: " << a.locuri;
        return os;
    }
};

class Pasager {
private:
    string nume;
    bool business;

public:
    Pasager() : nume(""), business(false) {}
    Pasager(string n, bool b) : nume(n), business(b) {}

    string getNume() const { return nume; }
    bool isBusiness() const { return business; }

    void setNume(string n) { nume = n; }
    void setBusiness(bool b) { business = b; }

    friend ostream& operator<<(ostream& os, const Pasager& p) {
        os << "Pasager: " << p.nume
           << " (" << (p.business ? "Business" : "Economy") << ")";
        return os;
    }
};

class Pilot {
private:
    string nume;
    int oreZbor;

public:
    Pilot() : nume(""), oreZbor(0) {}
    Pilot(string n, int ore) : nume(n), oreZbor(ore) {}

    string getNume() const { return nume; }
    int getOreZbor() const { return oreZbor; }

    void setNume(string n) { nume = n; }
    void setOreZbor(int o) { oreZbor = o; }

    friend ostream& operator<<(ostream& os, const Pilot& p) {
        os << "Pilot: " << p.nume << ", Ore zbor: " << p.oreZbor;
        return os;
    }
};

class Zbor {
private:
    string codZbor;
    string destinatie;
    Avion avion;                  
    Pilot pilot;                     
    vector<Pasager> pasageri;       

public:
   
    Zbor() : codZbor(""), destinatie("") {}

    Zbor(string cod, string dest, Avion a, Pilot p)
        : codZbor(cod), destinatie(dest), avion(a), pilot(p) {}

    string getCodZbor() const { return codZbor; }
    string getDestinatie() const { return destinatie; }
    Avion getAvion() const { return avion; }
    Pilot getPilot() const { return pilot; }
    vector<Pasager> getPasageri() const { return pasageri; }

    void setCodZbor(string cod) { codZbor = cod; }
    void setDestinatie(string dest) { destinatie = dest; }
    void setAvion(const Avion& a) { avion = a; }
    void setPilot(const Pilot& p) { pilot = p; }
    void setPasageri(const vector<Pasager>& p) { pasageri = p; }

    Zbor& operator+=(const Pasager& p) {
        pasageri.push_back(p);
        return *this;
    }

    bool operator==(const Zbor& other) const {
        return codZbor == other.codZbor &&
               destinatie == other.destinatie;
    }

    friend ostream& operator<<(ostream& os, const Zbor& z) {
        os << "Zbor " << z.codZbor
           << " -> " << z.destinatie << endl;
        os << z.avion << endl;
        os << z.pilot << endl;
        os << "Pasageri:" << endl;
        for (const auto& p : z.pasageri) {
            os << "  - " << p << endl;
        }
        return os;
    }
};

int main() {

    Avion a1("Boeing 737", 180);
    Pilot p1("Andrei Popescu", 2400);

    Pasager pa1("Ion Ionescu", false);
    Pasager pa2("Maria Popa", true);
    Pasager pa3("Alex Dinu", false);

    Zbor z1("RO101", "Roma", a1, p1);

    z1 += pa1;
    z1 += pa2;
    z1 += pa3;

    cout << "=== ZBOR 1 ===" << endl;
    cout << z1 << endl;

    Zbor z2("RO101", "Roma", a1, p1);

    cout << "Zborurile sunt egale? "
         << (z1 == z2 ? "DA" : "NU") << endl;

    return 0;
}
