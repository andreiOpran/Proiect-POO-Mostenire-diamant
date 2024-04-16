#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class IOInterface {
public:
    virtual ostream& afisare(ostream&) const = 0;
    virtual istream& citire(istream&) = 0;
};


class Produs : public IOInterface
{
protected: // vom folosi protected de acum incolo
    static int CONTOR;
    const int id;
    string numeProdus;
    float pretBrut;
public:

    /// Constructori
    Produs();
    Produs(string, float);
    /// Copy Constructor
    Produs(const Produs&);

    /// Operatorul =
    Produs& operator = (const Produs&);

    friend ostream& operator << (ostream&, const Produs&);
    friend istream& operator >> (istream&, Produs&);

    virtual float calculeazaPret() = 0; /// metoda virtuala pura
    virtual ~Produs() {};

    virtual istream& citire(istream& in)
    {
        cout << "Introduceti numele produsului: ";
        in >> this->numeProdus;
        cout << "Introduceti pretul brut al produsului: ";
        in >> this->pretBrut;

        return in;
    }

    virtual ostream& afisare(ostream& out) const // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
    {
        // const de dupa inseamna ca this este constant, ca aici
        out << "Id produs: " << id << endl;
        out << "Nume produs: " << numeProdus << endl;
        out << "Pret brut produs: " << pretBrut << endl;

        return out;
    }
};

class ProdusPerisabil :public Produs // vom folosi protected de acum incolo
{
private:
    string dataExp;
public:
    /*ProdusPerisabil:id(CONTOR)
    {
        this->numeProdus="Anonim";
        this->pretBrut=0;
        this->dataExp="dd/mm/yyyy";
    }*/ /// - gresit!!

    ProdusPerisabil() :Produs() /// Daca nu chem constructorul din parinte, e chemat automat cel FARA PARAMETRI
    {
        this->dataExp = "dd/mm/yyyy";
    }
    ProdusPerisabil(string numeProdus, float pretBrut, string dataExp) :Produs(numeProdus, pretBrut)
    {
        this->dataExp = dataExp;
    }

    ProdusPerisabil(const ProdusPerisabil& obj) :Produs(obj)  ///Daca nu pun nimic, ia constructorul default, in cazul meu face up-cast
    {
        this->dataExp = dataExp;
    }

    ProdusPerisabil& operator = (const ProdusPerisabil& obj)
    {
        if (this != &obj)
        {
            /*this->numeProdus=obj.numeProdus;  // metoda corecta, dar nu cea mai buna
            this->pretBrut=obj.pretBrut;*/

            Produs::operator=(obj);
            this->dataExp = obj.dataExp;
        }
        return *this;
    }

    friend istream& operator >> (istream& in, ProdusPerisabil& obj)
    {
        cout << "Produs: ";
        in >> (Produs&)obj;
        cout << "Data expirare: ";
        in >> obj.dataExp;

        return in;
    }
    friend ostream& operator << (ostream& out, const ProdusPerisabil& obj)
    {
        out << (Produs&)obj;
        out << "Data expirare: " << obj.dataExp << endl;
        return out;
    }

    float calculeazaPret()
    {
        return /*Produs::calculeazaPret()*/pretBrut * 1.10 * 1.10;
    }

    ostream& afisare(ostream& out)
    {
        this->Produs::afisare(out);
        out << "Data expirare: " << this->dataExp << endl;
        return out;
    }
    // ... 

};

class ProdusNeperisabil :public Produs // vom folosi protected de acum incolo
{
private:
    int aniGarantie;
public:
    /*ProdusNeperisabil:id(CONTOR)
    {
        this->numeProdus="Anonim";
        this->pretBrut=0;
        this->aniGarantie="dd/mm/yyyy";
    }*/ /// - gresit!!

    ProdusNeperisabil() :Produs() /// Daca nu chem constructorul din parinte, e chemat automat cel FARA PARAMETRI
    {
        this->aniGarantie = 0;
    }
    ProdusNeperisabil(string numeProdus, float pretBrut, int aniGarantie) :Produs(numeProdus, pretBrut)
    {
        this->aniGarantie = aniGarantie;
    }

    ProdusNeperisabil(const ProdusNeperisabil& obj) :Produs(obj)  ///Daca nu pun nimic, ia constructorul default, in cazul meu face up-cast
    {
        this->aniGarantie = aniGarantie;
    }

    ProdusNeperisabil& operator = (const ProdusNeperisabil& obj)
    {
        if (this != &obj)
        {
            /*this->numeProdus=obj.numeProdus;  // metoda corecta, dar nu cea mai buna
            this->pretBrut=obj.pretBrut;*/

            Produs::operator=(obj);
            this->aniGarantie = obj.aniGarantie;
        }
        return *this;
    }

    friend istream& operator >> (istream& in, ProdusNeperisabil& obj)
    {
        /*cout << "Produs: ";
        in >> (Produs&)obj;
        cout << "Ani garantie: ";
        in >> obj.aniGarantie;

        return in;*/
        return obj.citire(in);
    }
    friend ostream& operator << (ostream& out, const ProdusNeperisabil& obj)
    {
        /*out << (Produs&)obj;
        out << "Ani garantie: " << obj.aniGarantie << endl;
        return out;*/
        return obj.afisare(out);
    }

    float calculeazaPret()
    {
        if (aniGarantie < 6)
            return /*Produs::calculeazaPret()*/pretBrut * 1.20;
        return /*Produs::calculeazaPret()*/ pretBrut;
    }


    ostream& afisare(ostream& out) const /*override*/
    {
        this->Produs::afisare(out);

        /*out << (Produs&)(*this);*/ // loop infinit

        out << "Ani garantie: " << this->aniGarantie << endl;
        return out;
    }

    istream& citire(istream& in) // ?
    {
        this->Produs::citire(in);
        cout << "Ani garantie: ";
        in >> this->aniGarantie;
        return in;
    }
    
};


int Produs::CONTOR = 1000;

Produs::Produs() :id(CONTOR++), numeProdus("Anonim"), pretBrut(0) {}

Produs::Produs(string numeProdus, float pretBrut) : id(CONTOR++), numeProdus(numeProdus), pretBrut(pretBrut) {}

Produs::Produs(const Produs& obj) : id(obj.id), numeProdus(obj.numeProdus), pretBrut(obj.pretBrut) {}

Produs& Produs :: operator = (const Produs& obj)
{
    if (this != &obj)
    {
        this->numeProdus = obj.numeProdus;
        this->pretBrut = obj.pretBrut;
    }
    return *this;
}

ostream& operator << (ostream& out, const Produs& obj)
{
    /*out << "Id produs: " << obj.id << endl;
    out << "Nume produs: " << obj.numeProdus << endl;
    out << "Pret brut produs: " << obj.pretBrut << endl;

    return out;*/
    return obj.afisare(out);
}

istream& operator >> (istream& in, Produs& obj)
{
    /*cout << "Introduceti numele produsului: ";
    in >> obj.numeProdus;
    cout << "Introduceti pretul brut al produsului: ";
    in >> obj.pretBrut;*/

    // in loc de toate liniile de sus:
    // return obj.citire(in);
    return obj.citire(in);
}

int main()
{
    vector <Produs*> produse;
    int k = 1;
    // Produs p; - clasa produs e abstracta acum (contine o functie virtuala pura)

    while (k == 1)
    {
        cout << "1. Introducere produs perisabil" << endl << "2. Introducere produs neperisabil" << endl;
        cout << "3. Afisare toate produsele" << endl << "4. Afisare suma totala a preturilor" << endl;
        int val;
        cin >> val;
        switch (val)
        {
        case 1:
        {
            Produs* p = new ProdusPerisabil;
            cin >> static_cast<ProdusPerisabil&>(*p);
            produse.push_back(p); // p e pointer
            break;
        }
        case 2:
        {
            Produs* p = new ProdusNeperisabil;
            /*cin >> static_cast<ProdusNeperisabil&>(*p);*/

            cin >> *p;
            produse.push_back(p); // p e pointer
            break;
        }
        case 3:
        {

            for (int i = 0; i < produse.size(); i++)
                if (typeid(ProdusPerisabil) == typeid((*produse[i])))
                    cout << static_cast<ProdusPerisabil&>(*produse[i]) << endl;
                else cout << static_cast<ProdusNeperisabil&>(*produse[i]) << endl;
            break;
        }
        case 4:
        {
            float s = 0;
            for (int i = 0; i < produse.size(); i++)
                s = s + produse[i]->calculeazaPret();
            cout << "Suma totala: " << s << endl;
            break;
        }
        }
    }

    return 0;
}
/*
parinte f()

copil f()

main()
parinte *p = new copil
p.f va apela functia din parinte




---------------------------------------------------------------------------------------------------------------------------------------------------------



parinte cu functiile <<(parinte&),>>(parinte&)

copil cu functiile >>(copil&),<<(copil&)


parinte *p = new copil;
*p este o adresa de parinte


<<*p va fi parinte -> se va lua functia de la parinte
*/


//
//
//// nou cod
//
//#include<iostream>
//#include<cstring>
//#include<vector>
//using namespace std;
//
//class Parinte {
//protected:
//	int at1;
//public:
//	Parinte() {
//		at1 = 0;
//		cout << "\nParinte\n";
//	}
//	~Parinte() {
//		cout << "\nDes Parinte\n";
//	}
//};
//
//class Parinte2 {
//protected:
//	int at12;
//public:
//	Parinte2() {
//		at12 = 0;
//		cout << "\nParinte2\n";
//	}
//	~Parinte2() {
//		cout << "\nDes Parinte2\n";
//	}
//};
//
//class Copil2 : virtual public Parinte {
//protected:
//	int at12;
//public:
//	Copil2() {
//		at12 = 0;
//		cout << "\nCopil2\n";
//	}
//	~Copil2() {
//		cout << "\nDes Copil2\n";
//	}
//};
//
//class Copil : virtual public Parinte/*, public Parinte2*/ {
//protected:
//	int at1;
//public:
//	Copil():Parinte()/*,Parinte2()*/ { // nu conteaza ce pui dupa :, pt ca constructorii se apeleaza in functie de in ce ordine sunt mostenite clasele (class Copil : public Parinte, public Parinte2)
//		at1 = 0;
//		cout << "\nCopil\n";
//	}
//	~Copil() {
//		cout << "\nDes Copil\n";
//	}
//	void r() {
//		// ...
//	}
//};
//
//
//class Nepot:virtual public Copil,virtual public Copil2 {
//protected:
//	int att5;
//public:
//	Nepot() {
//		cout << "\nNepot\n";
//
//	}
//	~Nepot() {
//		cout << "\nDes Nepot\n";
//	}
//	void f()
//	{
//		cout << "\nf din Nepot\n";
//		cout << endl << Copil::at1 << endl;
//		cout << endl << Copil2::at1 << endl;
//	}
//};
//int main()
//{
//	/*Copil a;*/
//	Nepot a;
//	a.r();
//	return 0;
//}
//
//
//
//
///*
//https://dontpad.com/produs
//*/
//
////#include <iostream>
////#include <cstring>
////#include <vector>
////using namespace std;
////class IOInterface // Interfata - are doar functii virtuale PURE
////{
////public:
////    virtual ostream& Afisare(ostream&) const = 0;
////    virtual istream& Citire(istream&) = 0;
////};
////class Produs : public IOInterface
////{
////protected: // vom folosi protected de acum incolo
////    static int CONTOR;
////    const int id;
////    string numeProdus;
////    float pretBrut;
////public:
////
////    /// Constructori
////    Produs();
////    Produs(string, float);
////    /// Copy Constructor
////    Produs(const Produs&);
////
////    /// Operatorul =
////    Produs& operator = (const Produs&);
////
////    friend ostream& operator << (ostream&, const Produs&);
////    friend istream& operator >> (istream&, Produs&);
////
////    virtual float calculeazaPret()=0; /// metoda virtuala pura
////     istream& Citire(istream& in)
////    {
////        cout << "Nume produs: ";
////        in >> this->numeProdus;
////        cout << "Pret brut: ";
////        in >> this->pretBrut;
////        return in;
////    }
////     ostream& Afisare(ostream& out) const
////    {
////        out<<"Id produs: "<<id<<endl;
////        out<<"Nume produs: "<<numeProdus<<endl;
////        out<<"Pret brut produs: "<<pretBrut<<endl;
////        return out;
////    }
////    virtual ~Produs(){};
////
////};
////
////class ProdusPerisabil :public Produs // vom folosi protected de acum incolo
////{
////private:
////    string dataExp;
////public:
////    /*ProdusPerisabil:id(CONTOR)
////    {
////        this->numeProdus="Anonim";
////        this->pretBrut=0;
////        this->dataExp="dd/mm/yyyy";
////    }*/ /// - gresit!!
////
////ProdusPerisabil() :Produs() /// Daca nu chem constructorul din parinte, e chemat automat cel FARA PARAMETRI
////{
////    this->dataExp = "dd/mm/yyyy";
////}
////ProdusPerisabil(string numeProdus, float pretBrut, string dataExp) :Produs(numeProdus, pretBrut)
////{
////    this->dataExp = dataExp;
////}
////
////ProdusPerisabil(const ProdusPerisabil& obj) :Produs(obj)  ///Daca nu pun nimic, ia constructorul default, in cazul meu face up-cast
////{
////    this->dataExp = dataExp;
////}
////
////ProdusPerisabil& operator = (const ProdusPerisabil& obj)
////{
////    if (this != &obj)
////    {
////        /*this->numeProdus=obj.numeProdus;  // metoda corecta, dar nu cea mai buna
////        this->pretBrut=obj.pretBrut;*/
////
////        Produs::operator=(obj);
////        this->dataExp = obj.dataExp;
////    }
////    return *this;
////}
////ostream& Afisare(ostream& out) const
////{
////    this->Produs::Afisare(out);
////    out << "Data expirare: " << this->dataExp;
////    return out;
////}
////istream& Citire(istream& in)
////{
////    this->Produs::Citire(in);
////    cout << "Data expirare: ";
////    in >> this->dataExp;
////    return in;
////}
////float calculeazaPret()
////{
////    return /*Produs::calculeazaPret()*/pretBrut * 1.10 * 1.10;
////}
////
////};
////
////class ProdusNeperisabil :public Produs // vom folosi protected de acum incolo
////{
////private:
////    int aniGarantie;
////public:
////    /*ProdusNeperisabil:id(CONTOR)
////    {
////        this->numeProdus="Anonim";
////        this->pretBrut=0;
////        this->aniGarantie="dd/mm/yyyy";
////    }*/ /// - gresit!!
////
////    ProdusNeperisabil() :Produs() /// Daca nu chem constructorul din parinte, e chemat automat cel FARA PARAMETRI
////    {
////        this->aniGarantie = 0;
////    }
////    ProdusNeperisabil(string numeProdus, float pretBrut, int aniGarantie) :Produs(numeProdus, pretBrut)
////    {
////        this->aniGarantie = aniGarantie;
////    }
////
////    ProdusNeperisabil(const ProdusNeperisabil& obj) :Produs(obj)  ///Daca nu pun nimic, ia constructorul default, in cazul meu face up-cast
////    {
////        this->aniGarantie = aniGarantie;
////    }
////
////    ProdusNeperisabil& operator = (const ProdusNeperisabil& obj)
////    {
////        if (this != &obj)
////        {
////            /*this->numeProdus=obj.numeProdus;  // metoda corecta, dar nu cea mai buna
////            this->pretBrut=obj.pretBrut;*/
////
////            Produs::operator=(obj);
////            this->aniGarantie = obj.aniGarantie;
////        }
////        return *this;
////    }
////    ostream& Afisare(ostream& out) const
////    {
////        this->Produs::Afisare(out);
////        out << "Ani garantie: " << this->aniGarantie << endl;
////        return out;
////    }
////    istream& Citire(istream& in)
////    {
////        this->Produs::Citire(in);
////        in >> this->aniGarantie;
////        return in;
////    }
////    float calculeazaPret()
////    {
////        if (aniGarantie < 6)
////            return /*Produs::calculeazaPret()*/pretBrut * 1.20;
////        return /*Produs::calculeazaPret()*/ pretBrut;
////    }
////};
////
////
////int Produs::CONTOR = 1000;
////
////Produs::Produs() :id(CONTOR++), numeProdus("Anonim"), pretBrut(0) {}
////
////Produs::Produs(string numeProdus, float pretBrut) : id(CONTOR++), numeProdus(numeProdus), pretBrut(pretBrut) {}
////
////Produs::Produs(const Produs& obj) : id(obj.id), numeProdus(obj.numeProdus), pretBrut(obj.pretBrut) {}
////
////Produs& Produs :: operator = (const Produs& obj)
////{
////    if (this != &obj)
////    {
////        this->numeProdus = obj.numeProdus;
////        this->pretBrut = obj.pretBrut;
////    }
////    return *this;
////}
////
////ostream& operator << (ostream& out, const Produs& obj)
////{
////    return obj.Afisare(out);
////}
////
////istream& operator >> (istream& in, Produs& obj)
////{
////    return obj.Citire(in);
////}
////
////int main()
////{
////    vector <Produs*> produse;
////    int k = 1;
////    // Produs p; - clasa produs e abstracta acum (contine o functie virtuala pura)
////
////    while (k == 1)
////    {
////        cout << "1. Introducere produs perisabil" << endl << "2. Introducere produs neperisabil" << endl;
////        cout << "3. Afisare toate produsele" << endl << "4. Afisare suma totala a preturilor" << endl;
////        int val;
////        cin >> val;
////        switch (val)
////        {
////        case 1:
////        {
////            Produs* p = new ProdusPerisabil;
////            cin >> *p;
////            produse.push_back(p); // p e pointer
////            break;
////        }
////        case 2:
////        {
////            Produs* p = new ProdusNeperisabil;
////            cin >> *p;
////            produse.push_back(p); // p e pointer
////            break;
////        }
////        case 3:
////        {
////
////            for (int i = 0; i < produse.size(); i++)
////                cout << *produse[i] << endl;
////            break;
////        }
////        case 4:
////        {
////            float s = 0;
////            for (int i = 0; i < produse.size(); i++)
////                s = s + produse[i]->calculeazaPret();
////            cout << "Suma totala: " << s << endl;
////            break;
////        }
////        }
////    }
////    return 0;
////}
//
//
