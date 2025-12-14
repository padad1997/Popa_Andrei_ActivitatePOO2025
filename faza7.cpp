#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Avion {
protected:
    string model;
    int locuri;

public:
    Avion() : model(""), locuri(0) {}
    Avion(string m, int l) : model(m), locuri(l) {}

    string getModel() const { return model; }
    int getLocuri() const { return locuri; }
    void setModel(string m) { model = m; }
    void setLocuri(int l) { locuri = l; }

    virtual void afiseazaInfo() const {
        cout << "Avion: " << model << ", Locuri: " << locuri << endl;
    }

    virtual ~Avion() {}
};

class Pilot {
protected:
    string nume;
    int oreZbor;

public:
    Pilot() : nume(""), oreZbor(0) {}
    Pilot(string n, int ore) : nume(n), oreZbor(ore) {}

    string getNume() const { return nume; }
    int getOreZbor() const { return oreZbor; }
    void setNume(string n) { nume = n; }
    void setOreZbor(int o) { oreZbor = o; }

    virtual void afiseazaInfo() const {
        cout << "Pilot: " << nume << ", Ore zbor: " << oreZbor << endl;
    }

    virtual ~Pilot() {}
};

class Pasager {
protected:
    string nume;
    bool business;

public:
    Pasager() : nume(""), business(false) {}
    Pasager(string n, bool b) : nume(n), business(b) {}

    string getNume() const { return nume; }
    bool isBusiness() const { return business; }
    void setNume(string n) { nume = n; }
    void setBusiness(bool b) { business = b; }

    virtual void afiseazaInfo() const {
        cout << "Pasager: " << nume << " (" << (business ? "Business" : "Economy") << ")" << endl;
    }

    virtual ~Pasager() {}
};

class Zbor {
protected:
    string codZbor;
    string destinatie;

public:
    Zbor() : codZbor(""), destinatie("") {}
    Zbor(string cod, string dest) : codZbor(cod), destinatie(dest) {}

    string getCodZbor() const { return codZbor; }
    string getDestinatie() const { return destinatie; }
    void setCodZbor(string cod) { codZbor = cod; }
    void setDestinatie(string dest) { destinatie = dest; }

    virtual void afiseazaInfo() const {
        cout << "Zbor " << codZbor << " -> " << destinatie << endl;
    }

    virtual ~Zbor() {}
};

class AvionDeLux : public Avion {
private:
    int nrScauneVIP;

public:
    AvionDeLux() : Avion(), nrScauneVIP(0) {}
    AvionDeLux(string m, int l, int vip) : Avion(m, l), nrScauneVIP(vip) {}

    int getNrScauneVIP() const { return nrScauneVIP; }
    void setNrScauneVIP(int vip) { nrScauneVIP = vip; }

    void afiseazaInfo() const override {
        cout << "Avion de Lux: " << model << ", Locuri: " << locuri
             << ", Locuri VIP: " << nrScauneVIP << endl;
    }
};

class PilotComercial : public Pilot {
private:
    string companie;

public:
    PilotComercial() : Pilot(), companie("") {}
    PilotComercial(string n, int ore, string comp) : Pilot(n, ore), companie(comp) {}

    string getCompanie() const { return companie; }
    void setCompanie(string c) { companie = c; }

    void afiseazaInfo() const override {
        cout << "Pilot Comercial: " << nume << ", Ore zbor: " << oreZbor
             << ", Companie: " << companie << endl;
    }
};


int main() {
    cout << "=== FAZA 7 TEST MOSTENIRE SI UPCASTING ===\n";

    // Creare obiecte derivate
    AvionDeLux aLux("Boeing 777", 300, 20);
    PilotComercial pCom("Ion Popescu", 4000, "BlueAir");

    // Test afisare direct
    aLux.afiseazaInfo();
    pCom.afiseazaInfo();

    // Upcasting: folosim pointeri la clasele de baza
    Avion* ptrAvion = &aLux;
    Pilot* ptrPilot = &pCom;

    cout << "\n=== Afisare prin upcasting ===\n";
    ptrAvion->afiseazaInfo();  // apeleaza AvionDeLux::afiseazaInfo() (polimorfism)
    ptrPilot->afiseazaInfo();  // apeleaza PilotComercial::afiseazaInfo()

    // Vector de Avioane pentru test polymorphism
    vector<Avion*> flota;
    flota.push_back(&aLux);
    flota.push_back(new Avion("Airbus A320", 180));

    cout << "\n Afisare flota \n";
    for (auto av : flota) {
        av->afiseazaInfo();
    }

    // Curatare memorie dinamica
    delete flota[1];

    return 0;
}
