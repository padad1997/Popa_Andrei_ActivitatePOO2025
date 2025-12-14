#include <iostream>
#include <fstream>
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

    friend ofstream& operator<<(ofstream& fout, const Avion& a) {
        fout << a.model << endl << a.locuri << endl;
        return fout;
    }

    friend ifstream& operator>>(ifstream& fin, Avion& a) {
        getline(fin, a.model);
        fin >> a.locuri;
        fin.ignore(); // consumam newline
        return fin;
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
        os << "Pasager: " << p.nume << " (" << (p.business ? "Business" : "Economy") << ")";
        return os;
    }

    friend ofstream& operator<<(ofstream& fout, const Pasager& p) {
        fout << p.nume << endl << p.business << endl;
        return fout;
    }

    friend ifstream& operator>>(ifstream& fin, Pasager& p) {
        getline(fin, p.nume);
        fin >> p.business;
        fin.ignore(); 
        return fin;
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

    friend ofstream& operator<<(ofstream& fout, const Pilot& p) {
        size_t len = p.nume.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(p.nume.c_str(), len);
        fout.write(reinterpret_cast<const char*>(&p.oreZbor), sizeof(p.oreZbor));
        return fout;
    }

    friend ifstream& operator>>(ifstream& fin, Pilot& p) {
        size_t len;
        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        char* buffer = new char[len + 1];
        fin.read(buffer, len);
        buffer[len] = '\0';
        p.nume = buffer;
        delete[] buffer;
        fin.read(reinterpret_cast<char*>(&p.oreZbor), sizeof(p.oreZbor));
        return fin;
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

    void adaugaPasager(const Pasager& p) { pasageri.push_back(p); }

    friend ostream& operator<<(ostream& os, const Zbor& z) {
        os << "Zbor " << z.codZbor << " -> " << z.destinatie << endl;
        os << z.avion << endl;
        os << z.pilot << endl;
        os << "Pasageri:" << endl;
        for (auto& p : z.pasageri)
            os << "  - " << p << endl;
        return os;
    }

    friend ofstream& operator<<(ofstream& fout, const Zbor& z) {
        size_t len;

        // codZbor
        len = z.codZbor.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(z.codZbor.c_str(), len);

        // destinatie
        len = z.destinatie.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(z.destinatie.c_str(), len);

        // avion
        fout << z.avion;

        // pilot
        fout << z.pilot;

        // pasageri
        size_t nr = z.pasageri.size();
        fout.write(reinterpret_cast<const char*>(&nr), sizeof(nr));
        for (auto& p : z.pasageri)
            fout << p; // supraincarcare text pentru fiecare pasager
        return fout;
    }

    friend ifstream& operator>>(ifstream& fin, Zbor& z) {
        size_t len;

        // codZbor
        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        char* buffer = new char[len + 1];
        fin.read(buffer, len);
        buffer[len] = '\0';
        z.codZbor = buffer;
        delete[] buffer;

        // destinatie
        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        buffer = new char[len + 1];
        fin.read(buffer, len);
        buffer[len] = '\0';
        z.destinatie = buffer;
        delete[] buffer;

        // avion
        fin >> z.avion;

        // pilot
        fin >> z.pilot;

        // pasageri
        size_t nr;
        fin.read(reinterpret_cast<char*>(&nr), sizeof(nr));
        z.pasageri.clear();
        for (size_t i = 0; i < nr; i++) {
            Pasager p;
            fin >> p;
            z.pasageri.push_back(p);
        }

        return fin;
    }
};


int main() {
    cout << "=== FAZA 6 – TEST SUPRAINCARCARE ===\n";

    // ===== Avion text =====
    Avion a1("Boeing 747", 200);
    ofstream foutAv("avion.txt");
    foutAv << a1;
    foutAv.close();

    Avion a2;
    ifstream finAv("avion.txt");
    finAv >> a2;
    finAv.close();
    cout << "Avion citit text: " << a2 << endl;

    // ===== Pasager text =====
    Pasager p1("Maria Ionescu", true);
    ofstream foutP("pasager.txt");
    foutP << p1;
    foutP.close();

    Pasager p2;
    ifstream finP("pasager.txt");
    finP >> p2;
    finP.close();
    cout << "Pasager citit text: " << p2 << endl;

    // ===== Pilot binar =====
    Pilot pi1("Andrei Popescu", 2500);
    ofstream foutPi("pilot.bin", ios::binary);
    foutPi << pi1;
    foutPi.close();

    Pilot pi2;
    ifstream finPi("pilot.bin", ios::binary);
    finPi >> pi2;
    finPi.close();
    cout << "Pilot citit binar: " << pi2 << endl;

    // ===== Zbor binar =====
    Zbor z1("RO101", "Paris", a1, pi1);
    z1.adaugaPasager(p1);
    z1.adaugaPasager(p2);

    ofstream foutZ("zbor.bin", ios::binary);
    foutZ << z1;
    foutZ.close();

    Zbor z2;
    ifstream finZ("zbor.bin", ios::binary);
    finZ >> z2;
    finZ.close();
    cout << "Zbor citit binar:\n" << z2 << endl;

    return 0;
}
