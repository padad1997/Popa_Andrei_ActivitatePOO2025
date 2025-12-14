#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Avion {
private:
    string model;
    int LocuriEconomy;
    int LocuriBusiness;

public:
    Avion() : model(""), LocuriEconomy(0), LocuriBusiness(0) {}

    Avion(string m, int eco, int bus)
        : model(m), LocuriEconomy(eco), LocuriBusiness(bus) {}

    friend ostream& operator<<(ostream& os, const Avion& a) {
        os << "Model: " << a.model
           << ", Economy: " << a.LocuriEconomy
           << ", Business: " << a.LocuriBusiness;
        return os;
    }
};

class Pasager {
private:
    string nume;
    unsigned int NumarMaximPasageri;
    bool Business;

public:
    Pasager() : nume(""), NumarMaximPasageri(0), Business(false) {}

    Pasager(string n, unsigned int nr, bool b)
        : nume(n), NumarMaximPasageri(nr), Business(b) {}

    friend ostream& operator<<(ostream& os, const Pasager& p) {
        os << "Nume: " << p.nume
           << ", Max pasageri: " << p.NumarMaximPasageri
           << ", Clasa: " << (p.Business ? "Business" : "Economy");
        return os;
    }
};

class Pilot {
private:
    string NumePilot;
    unsigned int OreDeZbor;

public:
    Pilot() : NumePilot(""), OreDeZbor(0) {}

    Pilot(string n, unsigned int ore)
        : NumePilot(n), OreDeZbor(ore) {}

    friend ostream& operator<<(ostream& os, const Pilot& p) {
        os << "Pilot: " << p.NumePilot
           << ", Ore de zbor: " << p.OreDeZbor;
        return os;
    }
};

int main() {

    vector<Avion> avioane = {
        Avion("Boeing 737", 120, 20),
        Avion("Airbus A320", 150, 30),
        Avion("Boeing 747", 200, 50)
    };

    cout << "--- Avioane ---\n";
    for (const auto& a : avioane) {
        cout << a << endl;
    }

    vector<Pasager> pasageri = {
        Pasager("Ion Popescu", 5, false),
        Pasager("Maria Ionescu", 10, true),
        Pasager("Ana Popa", 8, false)
    };

    cout << "\n--- Pasageri ---\n";
    for (const auto& p : pasageri) {
        cout << p << endl;
    }

    vector<Pilot> piloti = {
        Pilot("George", 1200),
        Pilot("Andrei", 1800),
        Pilot("Alexandra", 2500)
    };

    cout << "\n--- Piloti ---\n";
    for (const auto& p : piloti) {
        cout << p << endl;
    }

    vector<vector<Avion>> matriceAvioane = {
        { Avion("Airbus A380", 250, 70), Avion("Embraer 190", 90, 10) },
        { Avion("ATR 72", 60, 8),       Avion("Boeing 787", 220, 40) }
    };

    cout << "\n--- Matrice Avioane ---\n";
    for (const auto& linie : matriceAvioane) {
        for (const auto& a : linie) {
            cout << a << " | ";
        }
        cout << endl;
    }

    return 0;
}
