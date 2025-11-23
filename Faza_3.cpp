#include <iostream>
#include <string>
using namespace std;

class Avion {
private:
    string model;
    int LocuriEconomy;
    int LocuriBusiness;

public:
    // Constructori
    Avion() : model("Boeing 737"), LocuriEconomy(0), LocuriBusiness(0) {}
    Avion(string m, int locuriEco, int locuriBus) : model(m), LocuriEconomy(locuriEco), LocuriBusiness(locuriBus) {}

    // Constructor de copiere
    Avion(const Avion& other) : model(other.model), LocuriEconomy(other.LocuriEconomy), LocuriBusiness(other.LocuriBusiness) {}

    // Destructor
    ~Avion() {
    }

    // Metode pentru afisare
    void afiseazaInfo() {
        cout << "Model: " << model << ", Locuri Economy: " << LocuriEconomy << ", Locuri Business: " << LocuriBusiness << endl;
    }

    // Operator de atribuire
    Avion& operator=(const Avion& other) {
        if (this != &other) {
            model = other.model;
            LocuriEconomy = other.LocuriEconomy;
            LocuriBusiness = other.LocuriBusiness;
        }
        return *this;
    }

    // Operator de comparare
    bool operator==(const Avion& other) {
        return (model == other.model && LocuriEconomy == other.LocuriEconomy && LocuriBusiness == other.LocuriBusiness);
    }

    // Operator de incrementare
    Avion& operator++() {
        LocuriEconomy++;
        LocuriBusiness++;
        return *this;
    }

    // Operator << pentru afisare
    friend ostream& operator<<(ostream& os, const Avion& avion) {
        os << "Model: " << avion.model << ", Locuri Economy: " << avion.LocuriEconomy << ", Locuri Business: " << avion.LocuriBusiness;
        return os;
    }
};

class Pasager {
private:
    string* nume;
    const unsigned int NumarMaximPasageri;
    bool Business;
    string locEconomy;
    string locBusiness;

public:
    // Constructori
    Pasager() : nume(nullptr), NumarMaximPasageri(0), Business(false), locEconomy("Economy-1"), locBusiness("Business-1") {}
    Pasager(string* n, unsigned int numarMaxim, bool business = false)
        : nume(n), NumarMaximPasageri(numarMaxim), Business(business), locEconomy("Economy-" + to_string(numarMaxim)), locBusiness("Business-" + to_string(numarMaxim)) {}

    // Constructor de copiere
    Pasager(const Pasager& other)
        : nume(other.nume), NumarMaximPasageri(other.NumarMaximPasageri), Business(other.Business), locEconomy(other.locEconomy), locBusiness(other.locBusiness) {}

    // Destructor
    ~Pasager() {
    }

    // Metoda pentru afisare
    void afiseazaInfo() {
        cout << "Nume: " << *nume << ", Locuri disponibile: " << NumarMaximPasageri << ", Loc Economy: " << locEconomy << ", Loc Business: " << locBusiness << endl;
    }

    // Operator de atribuire
    Pasager& operator=(const Pasager& other) {
        if (this != &other) {
            nume = other.nume;
            Business = other.Business;
            locEconomy = other.locEconomy;
            locBusiness = other.locBusiness;
        }
        return *this;
    }

    // Operator de comparare
    bool operator==(const Pasager& other) {
        return (*nume == *other.nume && NumarMaximPasageri == other.NumarMaximPasageri);
    }

    // Operator << pentru afisare
    friend ostream& operator<<(ostream& os, const Pasager& pasager) {
        os << "Nume: " << *pasager.nume << ", Locuri disponibile: " << pasager.NumarMaximPasageri << ", Loc Economy: " << pasager.locEconomy << ", Loc Business: " << pasager.locBusiness;
        return os;
    }
};

class Pilot {
private:
    string NumePilot;
    unsigned int* OreDeZbor;

public:
    // Constructori
    Pilot() : NumePilot("Unknown"), OreDeZbor(nullptr) {}
    Pilot(string nume, unsigned int* oreDeZbor) : NumePilot(nume), OreDeZbor(oreDeZbor) {}

    // Constructor de copiere
    Pilot(const Pilot& other) : NumePilot(other.NumePilot), OreDeZbor(other.OreDeZbor) {}

    // Destructor
    ~Pilot() {
    }

    // Metoda pentru afisare
    void afiseazaInfo() {
        cout << "Pilot: " << NumePilot << ", Ore de zbor: " << *OreDeZbor << endl;
    }

    // Operator << pentru afisare
    friend ostream& operator<<(ostream& os, const Pilot& pilot) {
        os << "Pilot: " << pilot.NumePilot << ", Ore de zbor: " << *pilot.OreDeZbor;
        return os;
    }
};

// Functia friend pentru afisarea informatiilor
void afiseazaInfoAvion(const Avion& avion) {
    cout << avion << endl;
}

void afiseazaInfoPasager(const Pasager& pasager) {
    cout << pasager << endl;
}

void afiseazaInfoPilot(const Pilot& pilot) {
    cout << pilot << endl;
}

int main() {
    // Creare obiecte Avion
    Avion a1("Boeing 747", 200, 50);
    Avion a2("Airbus A380", 250, 70);
    Avion a3 = a1;  // Constructor de copiere
    Avion a4("Airbus A350", 250, 250);  // Corectat

    afiseazaInfoAvion(a1);
    afiseazaInfoAvion(a2);

    // Creare obiecte Pasager
    string nume1 = "Ion Popescu";
    Pasager p1(&nume1, 5, false);
    string nume2 = "Maria Ionescu";
    Pasager p2(&nume2, 5, true);
    string nume3 = "Alin Doru";
    Pasager p3(&nume3, 5);  // Corectat
    string nume4 = "Ana Popa";
    Pasager p4(&nume4, 10);  // Corectat

    afiseazaInfoPasager(p1);
    afiseazaInfoPasager(p2);

    // Creare obiecte Pilot
    unsigned int oreZbor1 = 1200;
    unsigned int oreZbor2 = 1500;
    unsigned int oreZbor3 = 2000;
    unsigned int varstePiloți[] = {45, 50, 55};

    string numePi1 = "George";
    Pilot pi1(numePi1, &oreZbor1);
    string numePi2 = "Andrei";
    Pilot pi2(numePi2, &oreZbor2);
    string numePi3 = "Alexandra";
    Pilot pi3(numePi3, &oreZbor3);
    Pilot pi4 = pi1;  
    string numePi5 = "Emil";
    Pilot pi5(numePi5, &oreZbor3);  

    afiseazaInfoPilot(pi1);
    afiseazaInfoPilot(pi2);

    return 0;
}
