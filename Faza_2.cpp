#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Avion {
private:
    string model;
    static int* NumarAvioane;
    static int TotalLocuri;
    int LocuriEconomy;
    int LocuriBusiness;

public:
    // Constructor cu parametri 
    Avion(string m, int locuriEco, int locuriBus) : model(m), LocuriEconomy(locuriEco), LocuriBusiness(locuriBus) {
        TotalLocuri += (LocuriEconomy + LocuriBusiness);
        if (NumarAvioane == nullptr) {
            NumarAvioane = new int(1);  
        } else {
            (*NumarAvioane)++;
        }
    }

    // Constructorul de copiere
    Avion(const Avion& other) : model(other.model), LocuriEconomy(other.LocuriEconomy), LocuriBusiness(other.LocuriBusiness) {
        TotalLocuri += (LocuriEconomy + LocuriBusiness);
        if (NumarAvioane == nullptr) {
            NumarAvioane = new int(1);
        } else {
            (*NumarAvioane)++;
        }
    }

    // Destructor
    ~Avion() {
        if (NumarAvioane != nullptr) {
            (*NumarAvioane)--;
            if (*NumarAvioane == 0) {
                delete NumarAvioane;
                NumarAvioane = nullptr;
            }
        }
    }

    // Funcție statică pentru calculul totalului de locuri
    static int calculeazaTotalLocuri() {
        return TotalLocuri;
    }

    // Funcție statică pentru a obține numărul total de avioane
    static int getNumarAvioane() {
        return *NumarAvioane;
    }

    // Funcție statică pentru a compara două avioane după numărul total de locuri
    static bool comparaAvioane(Avion& avion1, Avion& avion2) {
        int totalLocuriAvion1 = avion1.LocuriEconomy + avion1.LocuriBusiness;
        int totalLocuriAvion2 = avion2.LocuriEconomy + avion2.LocuriBusiness;
        return totalLocuriAvion1 > totalLocuriAvion2;
    }

    // Funcție prietena pentru a calcula media numărului total de locuri ale avioanelor
    friend double calculeazaMediaLocurilor(const Avion& avion1, const Avion& avion2);
};

// Inițializarea variabilelor statice
int* Avion::NumarAvioane = nullptr;
int Avion::TotalLocuri = 0;


class Pasager {
private:
    string* nume;
    static unsigned int Loc;
    const unsigned int NumarMaximPasageri;
    bool Business;
    string locEconomy;
    string locBusiness;

public:
    // Constructor cu parametri (nume, NumarMaxim, Business)
    Pasager(string* n, unsigned int numarMaxim, bool business = false) : nume(n), NumarMaximPasageri(numarMaxim), Business(business) {
        Loc++;
        locEconomy = "Economy-" + to_string(Loc);
        locBusiness = "Business-" + to_string(Loc);
    }

    // Constructorul de copiere
    Pasager(const Pasager& other) : nume(other.nume), NumarMaximPasageri(other.NumarMaximPasageri), Business(other.Business),
                                   locEconomy(other.locEconomy), locBusiness(other.locBusiness) {
        Loc++;
    }

    // Destructorul
    ~Pasager() {
    }

    // Funcție statică pentru calculul totalului de pasageri
    static unsigned int calculeazaTotalPasageri() {
        return Loc;
    }

    // Funcție statică pentru obținerea numărului total de locuri disponibile
    static int getLocuriDisponibile() {
        return Loc; 
    }

    // Funcție statică pentru compararea unui pasager de la business cu unul de la economy
    static bool comparaPasageri(Pasager& pasager1, Pasager& pasager2) {
        if (pasager1.Business && !pasager2.Business) {
            return true;  
        } else {
            return false;
        }
    }

    // Funcție prietenă pentru a compara numărul de pasageri la Business și Economy
    friend bool comparaNumarPasageri(const Pasager& p1, const Pasager& p2);
};

unsigned int Pasager::Loc = 0;


class Pilot {
private:
    string NumePilot;
    static unsigned int Varsta;
    const unsigned int* OreDeZbor;

public:
    // Constructor cu parametri (nume, OreDeZbor)
    Pilot(string nume, unsigned int* oreDeZbor) : NumePilot(nume), OreDeZbor(oreDeZbor) {}

    // Constructorul de copiere
    Pilot(const Pilot& other) : NumePilot(other.NumePilot), OreDeZbor(other.OreDeZbor) {}

    // Destructorul
    ~Pilot() {
    }

    // Funcție statică pentru calculul vârstei medii a piloților
    static unsigned int calculeazaVarstaMedie(unsigned int varste[], unsigned int numarPiloți) {
        unsigned int sumaVarste = 0;
        for (unsigned int i = 0; i < numarPiloți; ++i) {
            sumaVarste += varste[i];
        }
        return sumaVarste / numarPiloți;
    }

    // Funcție statică pentru obținerea vârstei minime a piloților
    static unsigned int getVarstaMinima(unsigned int varste[], unsigned int numarPiloți) {
        unsigned int varstaMinima = UINT_MAX;
        for (unsigned int i = 0; i < numarPiloți; ++i) {
            if (varste[i] < varstaMinima) {
                varstaMinima = varste[i];
            }
        }
        return varstaMinima;
    }

    // Funcție prietenă pentru a compara vârstele a doi piloți
    friend bool comparaVarste(const Pilot& pilot1, const Pilot& pilot2);
};

unsigned int Pilot::Varsta = 0;


// Funcție prietenă pentru a calcula media locurilor din două avioane
double calculeazaMediaLocurilor(const Avion& avion1, const Avion& avion2) {
    int totalLocuriAvion1 = avion1.LocuriEconomy + avion1.LocuriBusiness;
    int totalLocuriAvion2 = avion2.LocuriEconomy + avion2.LocuriBusiness;
    return (totalLocuriAvion1 + totalLocuriAvion2) / 2.0;
}

// Funcție prietenă pentru a compara numărul de pasageri business cu cei economy
bool comparaNumarPasageri(const Pasager& p1, const Pasager& p2) {
    if (p1.Business && !p2.Business) {
        return true; 
    }
    return false;
}

// Funcție prietenă pentru a compara vârstele a doi piloți
bool comparaVarste(const Pilot& pilot1, const Pilot& pilot2) {
    return pilot1.OreDeZbor < pilot2.OreDeZbor;
}

int main() {
    // Creare avioane
    Avion a1("Boeing 747", 200, 50);
    Avion a2("Airbus A380", 250, 70);
    // Calcul media locurilor din două avioane
    cout << "Media locurilor dintre Avionul 1 si Avionul 2: " << calculeazaMediaLocurilor(a1, a2) << endl;

    // Creare pasageri
    string nume1 = "Ion Popescu";
    Pasager p1(&nume1, 5, false);
    string nume2 = "Maria Ionescu";
    Pasager p2(&nume2, 5, true);

    // Comparare numar pasageri
    cout << "Pasagerul 1 este mai important decat Pasagerul 2? " << (comparaNumarPasageri(p1, p2) ? "Da" : "Nu") << endl;

    // Creare piloti
    unsigned int oreZbor1 = 1200;
    unsigned int oreZbor2 = 1500;
    Pilot pi1("George", &oreZbor1);
    Pilot pi2("Andrei", &oreZbor2);

    // Comparare varste
    cout << "Pilotul 1 are mai putine ore de zbor decat Pilotul 2? " << (comparaVarste(pi1, pi2) ? "Da" : "Nu") << endl;

    return 0;
}
