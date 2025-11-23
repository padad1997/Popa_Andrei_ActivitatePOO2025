#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Avion {
public:
    string model;
    static int* NumarAvioane;
    static int TotalLocuri;
    int LocuriEconomy;
    int LocuriBusiness;

    // Constructor cu parametri 
    Avion(string m, int locuriEco, int locuriBus) : model(m), LocuriEconomy(locuriEco), LocuriBusiness(locuriBus) {
        TotalLocuri += (LocuriEconomy + LocuriBusiness);
        if (NumarAvioane == nullptr) {
            NumarAvioane = new int(1);  
        } else {
            (*NumarAvioane)++;
        }
    }

    // Constructor cu parametri (doar modelul)
    Avion(string m) : model(m), LocuriEconomy(0), LocuriBusiness(0) {
        TotalLocuri += (LocuriEconomy + LocuriBusiness);
        if (NumarAvioane == nullptr) {
            NumarAvioane = new int(1);  
        } else {
            (*NumarAvioane)++;
        }
    }

    // Constructor cu parametri (doar numărul total de locuri)
    Avion(int totalLocuri) : model("Unknown"), LocuriEconomy(totalLocuri / 2), LocuriBusiness(totalLocuri / 2) {
        TotalLocuri += (LocuriEconomy + LocuriBusiness);
        if (NumarAvioane == nullptr) {
            NumarAvioane = new int(1);  // Inițializăm NumarAvioane doar dacă este nullptr
        } else {
            (*NumarAvioane)++;
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
};

// Inițializarea variabilelor statice
int* Avion::NumarAvioane = nullptr;
int Avion::TotalLocuri = 0;


class Pasager {
public:
    string* nume;
    static unsigned int Loc;
    const unsigned int NumarMaximPasageri;
    bool Business;
    string locEconomy;
    string locBusiness;

    // Constructor cu parametri (nume, NumarMaxim, Business)
    Pasager(string* n, unsigned int numarMaxim, bool business = false) : nume(n), NumarMaximPasageri(numarMaxim), Business(business) {
        Loc++;
        locEconomy = "Economy-" + to_string(Loc);
        locBusiness = "Business-" + to_string(Loc);
    }

    // Constructor cu parametri (doar nume)
    Pasager(string* n) : nume(n), NumarMaximPasageri(0), Business(false), locEconomy("Economy-1"), locBusiness("Business-1") {
        Loc++;
    }

    // Constructor cu parametri (doar numărul maxim de pasageri)
    Pasager(unsigned int numarMaxim) : nume(nullptr), NumarMaximPasageri(numarMaxim), Business(false), locEconomy("Economy-1"), locBusiness("Business-1") {
        Loc++;
    }

    // Funcție statică pentru calculul totalului de pasageri
    static unsigned int calculeazaTotalPasageri() {
        return Loc;
    }

    // Funcție statică pentru obținerea numărului total de locuri disponibile
    static int getLocuriDisponibile() {
        return Loc; // numărul de locuri disponibile poate fi calculat pe baza numărului de pasageri adăugați
    }

    // Funcție statică pentru compararea unui pasager de la business cu unul de la economy
    static bool comparaPasageri(Pasager& pasager1, Pasager& pasager2) {
        if (pasager1.Business && !pasager2.Business) {
            return true;  
        } else {
            return false;
        }
    }
};


unsigned int Pasager::Loc = 0;


class Pilot {
public:
    string NumePilot;
    static unsigned int Varsta;
    const unsigned int* OreDeZbor;

    // Constructor cu parametri (nume, OreDeZbor)
    Pilot(string nume, unsigned int* oreDeZbor) : NumePilot(nume), OreDeZbor(oreDeZbor) {}

    // Constructor cu parametri (doar Numele)
    Pilot(string nume) : NumePilot(nume), OreDeZbor(nullptr) {}

    // Constructor cu parametri (doar Orele de zbor)
    Pilot(unsigned int* oreDeZbor) : NumePilot("Unknown"), OreDeZbor(oreDeZbor) {}

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

    // Funcție statică pentru compararea a două ore de zbor
    static bool comparaOreDeZbor(Pilot& pilot1, Pilot& pilot2) {
        unsigned int ore1 = *pilot1.OreDeZbor;
        unsigned int ore2 = *pilot2.OreDeZbor;
        return ore1 > ore2;
    }
};

unsigned int Pilot::Varsta = 0;


int main() {


    // Avioane
    Avion a1("Boeing 747", 200, 50);
    Avion a2("Airbus A380", 250, 70);
    Avion a3("Boeing 737");
    Avion a4(500);  // Constructor cu numărul total de locuri

    // Comparare avioane
    cout << "Avionul 1 este mai mare ca Avionul 2? " << (Avion::comparaAvioane(a1, a2) ? "Da" : "Nu") << endl;

    // Pasageri
    string nume1 = "Ion Popescu";
    Pasager p1(&nume1, 5, false);
    string nume2 = "Maria Ionescu";
    Pasager p2(&nume2, 5, true);
    Pasager p3(&nume2); 
    Pasager p4(10);  

    // Comparare pasageri
    cout << "Pasagerul 1 este la Business și Pasagerul 2 este la Economy? " << (Pasager::comparaPasageri(p1, p2) ? "Da" : "Nu") << endl;

    // Piloți
    unsigned int oreZbor1 = 1200;
    unsigned int oreZbor2 = 1500;
    unsigned int oreZbor3 = 2000;
    unsigned int varstePiloți[] = {45, 50, 55};

    Pilot pi1("George", &oreZbor1);
    Pilot pi2("Andrei", &oreZbor2);
    Pilot pi3("Alexandra", &oreZbor3);
    Pilot pi4("Ion");  
    Pilot pi5(&oreZbor3);  

    // Comparare ore de zbor
    cout << "Pilotul 1 are mai multe ore de zbor decât Pilotul 2? " << (Pilot::comparaOreDeZbor(pi1, pi2) ? "Da" : "Nu") << endl;

    return 0;
}
