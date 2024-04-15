#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class IOInterface {
public:
	virtual ostream& citireVehicul(ostream&) = 0;
	virtual istream& afisareVehicul(istream&) const = 0;
};

//class InterfataVehicul {
//
//public:
//
//};

class Vehicul : public IOInterface {

protected:
	string marca;
	string model;
	int anFabricatie;
	bool disponibil;
	double pret;

public:
	
	// CONSTRUCTOR FARA PARAMETRI
	Vehicul();

	// CONSTRUCTOR CU PARAMETRI
	Vehicul(string, string, int, bool, double);

	// COPY CONSTRUCTOR
	Vehicul(const Vehicul&);

	// OPERATOR =
	Vehicul& operator=(const Vehicul&);

	// DESTRUCTOR
	~Vehicul() {}

	// OPERATORI >> SI <<
	friend istream& operator >>(istream&, Vehicul&);
	friend ostream& operator <<(ostream&, const Vehicul&);

	virtual istream& citireVehicul(istream& in) override;
	virtual ostream& afisareVehicul(ostream& out) const override; // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
};

// CONSTRUCTOR FARA PARAMETRI
Vehicul::Vehicul() : marca("Anonim"), model("Anonim"), anFabricatie(0), disponibil(false), pret(0) {}

// CONSTRUCTOR CU PARAMETRI
Vehicul::Vehicul(string marca, string model, int anFabricatie, bool disponibil, double pret) :marca(marca), model(model), anFabricatie(anFabricatie), disponibil(disponibil), pret(pret){}

// COPY CONSTRUCTOR
Vehicul::Vehicul(const Vehicul& obj) : marca(obj.marca), model(obj.model), anFabricatie(obj.anFabricatie), disponibil(obj.disponibil), pret(obj.pret) {}

// OPERATOR =
Vehicul& Vehicul::operator=(const Vehicul& obj) 
{
	if (this != &obj) 
	{
		this->marca = obj.marca;
		this->model = obj.model;
		this->anFabricatie = obj.anFabricatie;
		this->disponibil = obj.disponibil;
		this->pret = obj.pret;
	}
	return *this;
}

// OPERATOR >>
istream& Vehicul::citireVehicul(istream& in)
{
	cout << "Marca: ";
	in >> marca;
	cout << "Model: ";
	in >> model;
	cout << "An fabricatie: ";
	in >> anFabricatie;
	cout << "Disponibil: ";
	in >> disponibil;
	cout << "Pret: ";
	in >> pret;
	return in;
}

istream& operator >>(istream& in, Vehicul& obj) { return obj.citireVehicul(in); }

// OPERATOR <<
ostream& Vehicul::afisareVehicul(ostream& out) const
{
	out << "Marca: " << marca << endl;
	out << "Model: " << model << endl;
	out << "An fabricatie: " << anFabricatie << endl;
	out << "Disponibil: " << disponibil << endl;
	out << "Pret: " << pret << endl;
	return out;
}

ostream& operator <<(ostream& out, const Vehicul& obj) { return obj.afisareVehicul(out); }
	



class VehiculCarburant : virtual public Vehicul {

protected:
	string tipCarburant;
	double consum;

public:

	VehiculCarburant()
	{
		cout << endl << "Constructor VehiculCarburant" << endl;
	}
	~VehiculCarburant()
	{
		cout << endl << "Destructor VehiculCarburant" << endl;
	}
};

class VehiculElectric : virtual public Vehicul {

protected:
	double autonomie;
	double timpIncarcare; // pana la 100%

public:

	VehiculElectric()
	{
		cout << endl << "Constructor VehiculElectric" << endl;
	}
	~VehiculElectric()
	{
		cout << endl << "Destructor VehiculElectric" << endl;
	}
};

class VehiculHibrid : public VehiculCarburant, public VehiculElectric {

protected:
	string tipCarburant;
	double autonomieElectrica;

public:

	VehiculHibrid()
	{
		cout << endl << "Constructor VehiculHibrid" << endl;
	}
	~VehiculHibrid()
	{
		cout << endl << "Destructor VehiculHibrid" << endl;
	}
};

class Client {
	string nume;
	vector<Vehicul*> vehiculeCumparate;
	/*
	double plataRamasa;
	double creditMaxim;
	*/
};

class Showroom {
	string adresa;
	vector<Vehicul*> vehiculeDisponibile;
};

int main()
{
	Vehicul v1;
	cin >> v1;
	cout << v1;
	return 0;
}
