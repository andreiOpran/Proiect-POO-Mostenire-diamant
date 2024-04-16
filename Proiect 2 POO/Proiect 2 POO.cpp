#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


//class InterfataVehicul {
//
//public:
//
//};


// --------- CLASA IOINTERFACEVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class IOInterfaceVehicul {

public:
	virtual ostream& afisareVehicul(ostream&) const = 0;
	virtual istream& citireVehicul(istream&) = 0;
};


// --------- CLASA VEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Vehicul : public IOInterfaceVehicul {

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

	// OPERATORIi >> SI <<
	friend istream& operator >>(istream&, Vehicul&);
	friend ostream& operator <<(ostream&, const Vehicul&);
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override; // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
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

// OPERATORIi >> SI <<
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
	

// --------- CLASA VEHICULCARBURANT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculCarburant : virtual public Vehicul {

protected:
	string tipCarburant;
	double consum;

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculCarburant();

	// CONSTRUCTOR CU PARAMETRI
	VehiculCarburant(string, string , int, bool, double, string, double);

	// COPY CONSTRUCTOR
	VehiculCarburant(const VehiculCarburant&);

	// OPERATOR =
	VehiculCarburant& operator=(const VehiculCarburant&);

	// DESTRUCTOR
	~VehiculCarburant() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculCarburant&);
	friend ostream& operator <<(ostream&, const VehiculCarburant&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override;
};

// CONSTRUCTOR FARA PARAMETRI
VehiculCarburant::VehiculCarburant() : Vehicul(), tipCarburant("Necunoscut"), consum(0) {}

// CONSTRUCTOR CU PARAMETRI
VehiculCarburant::VehiculCarburant(string marca, string model, int anFabricatie, bool disponibil, double pret, string tipCarburant, double consum) : Vehicul(marca, model, anFabricatie, disponibil, pret), tipCarburant(tipCarburant), consum(consum) {}

// COPY CONSTRUCTOR
VehiculCarburant::VehiculCarburant(const VehiculCarburant& obj) : Vehicul(obj), tipCarburant(obj.tipCarburant), consum(obj.consum) {}

// OPERATOR =
VehiculCarburant& VehiculCarburant::operator=(const VehiculCarburant& obj)
{
	if (this != &obj)
	{
		Vehicul::operator=(obj); // varianta mai buna decat sa copiezi fiecare atribut din clasa de baza
		this->tipCarburant = obj.tipCarburant;
		this->consum = obj.consum;
	}
	return *this;
}

// OPERATORII >> SI <<
istream& VehiculCarburant::citireVehicul(istream& in)
{
	Vehicul::citireVehicul(in);
	cout << "Tip carburant: ";
	in >> tipCarburant;
	cout << "Consum: ";
	in >> consum;
	return in;
}
istream& operator >>(istream& in, VehiculCarburant& obj) { return obj.citireVehicul(in); }
ostream& VehiculCarburant::afisareVehicul(ostream& out) const
{
	Vehicul::afisareVehicul(out);
	out << "Tip carburant: " << tipCarburant << endl;
	out << "Consum: " << consum << endl;
	return out;
}
ostream& operator <<(ostream& out, const VehiculCarburant& obj) { return obj.afisareVehicul(out); }


// --------- CLASA VEHICULELECTRIC ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculElectric : virtual public Vehicul {

protected:
	double autonomieKm;
	double timpIncarcare; // pana la 100%

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculElectric();

	// CONSTRUCTOR CU PARAMETRI
	VehiculElectric(string, string, int, bool, double, double, double);

	// COPY CONSTRUCTOR
	VehiculElectric(const VehiculElectric&);

	// OPERATOR =
	VehiculElectric& operator=(const VehiculElectric&);

	// DESTRUCTOR
	~VehiculElectric() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculElectric&);
	friend ostream& operator <<(ostream&, const VehiculElectric&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override;
};

// CONSTRUCTOR FARA PARAMETRI
VehiculElectric::VehiculElectric() : Vehicul(), autonomieKm(0), timpIncarcare(0) {}

// CONSTRUCTOR CU PARAMETRI
VehiculElectric::VehiculElectric(string marca, string model, int anFabricatie, bool disponibil, double pret, double autonomieKm, double timpIncarcare) : Vehicul(marca, model, anFabricatie, disponibil, pret), autonomieKm(autonomieKm), timpIncarcare(timpIncarcare) {}

// COPY CONSTRUCTOR
VehiculElectric::VehiculElectric(const VehiculElectric& obj) : Vehicul(obj), autonomieKm(obj.autonomieKm), timpIncarcare(obj.timpIncarcare) {}

// OPERATOR =
VehiculElectric& VehiculElectric::operator=(const VehiculElectric& obj)
{
	if (this != &obj)
	{
		Vehicul::operator=(obj); // varianta mai buna decat sa copiezi fiecare atribut din clasa de baza
		this->autonomieKm = obj.autonomieKm;
		this->timpIncarcare = obj.timpIncarcare;
	}
	return *this;
}

// OPERATORII >> SI <<
istream& VehiculElectric::citireVehicul(istream& in)
{
	Vehicul::citireVehicul(in);
	cout << "Autonomie in KM: ";
	in >> autonomieKm;
	cout << "Timp incarcare: ";
	in >> timpIncarcare;
	return in;
}
istream& operator >>(istream& in, VehiculElectric& obj) { return obj.citireVehicul(in); }
ostream& VehiculElectric::afisareVehicul(ostream& out) const
{
	Vehicul::afisareVehicul(out);
	out << "Autonomie in KM: " << autonomieKm << endl;
	out << "Timp incarcare: " << timpIncarcare << endl;
	return out;
}
ostream& operator <<(ostream& out, const VehiculElectric& obj) { return obj.afisareVehicul(out); }



// --------- CLASA VEHICULHIBRID ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculHibrid : public VehiculCarburant, public VehiculElectric {

protected:
	char tipHibrid; // M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculHibrid();

	// CONSTRUCTOR CU PARAMETRI
	VehiculHibrid(string, string, int, bool, double, string, double, double, double, char);

	// COPY CONSTRUCTOR
	VehiculHibrid(const VehiculHibrid&);

	// OPERATOR =
	VehiculHibrid& operator=(const VehiculHibrid&);

	// DESTRUCTOR
	~VehiculHibrid() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculHibrid&);
	friend ostream& operator <<(ostream&, const VehiculHibrid&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override;
};

// CONSTRUCTOR FARA PARAMETRI
VehiculHibrid::VehiculHibrid() : VehiculCarburant(), VehiculElectric(), tipHibrid('0') {}

// CONSTRUCTOR CU PARAMETRI
VehiculHibrid::VehiculHibrid(string marca, string model, int anFabricatie, bool disponibil, double pret, string tipCarburant, double consum, double autonomieKm, double timpIncarcare, char tipHibrid) : VehiculCarburant(marca, model, anFabricatie, disponibil, pret, tipCarburant, consum), VehiculElectric(marca, model, anFabricatie, disponibil, pret, autonomieKm, timpIncarcare), tipHibrid(tipHibrid) {}

//  COPY CONSTRUCTOR
VehiculHibrid::VehiculHibrid(const VehiculHibrid& obj) : VehiculCarburant(obj), VehiculElectric(obj), tipHibrid(obj.tipHibrid) {}

// OPERATOR =
VehiculHibrid& VehiculHibrid::operator=(const VehiculHibrid& obj)
{
	if (this != &obj)
	{
		VehiculCarburant::operator=(obj);
		VehiculElectric::operator=(obj);
		this->tipHibrid = obj.tipHibrid;
	}
	return *this;
}

// OPERATORII >> SI <<
istream& VehiculHibrid::citireVehicul(istream& in)
{
	VehiculCarburant::citireVehicul(in);

	/*VehiculElectric::citireVehicul(in);*/ // altfel se citeste de 2 ori
	cout << "Autonomie in KM: ";
	in >> autonomieKm;
	cout << "Timp incarcare: ";
	in >> timpIncarcare;

	cout << "Tip hibrid: ";
	in >> tipHibrid;
	return in;
}
istream& operator >>(istream& in, VehiculHibrid& obj) { return obj.citireVehicul(in); }
ostream& VehiculHibrid::afisareVehicul(ostream& out) const
{
    VehiculCarburant::afisareVehicul(out);
    
	/*VehiculElectric::afisareVehicul(out);*/ // altfel se citeste de 2 ori
	out << "Autonomie in KM: " << autonomieKm << endl;
	out << "Timp incarcare: " << timpIncarcare << endl;

    out << "Tip hibrid: " << tipHibrid << endl;
    return out;
}
ostream& operator <<(ostream& out, const VehiculHibrid& obj) { return obj.afisareVehicul(out); }




// --------- CLASA CLIENT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Client {
	string nume;
	vector<Vehicul*> vehiculeCumparate;
	/*
	double plataRamasa;
	double creditMaxim;
	*/
};


// --------- CLASA SHOWROOM ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Showroom {
	string adresa;
	vector<Vehicul*> vehiculeDisponibile;
};

int main()
{
	VehiculHibrid v1;
	cin >> v1;
	cout << v1;
	return 0;
}
