#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;


class InterfataVehicul {

public:
	
};


// --------- CLASA IOINTERFACEVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class IOInterfaceVehicul {

public:
	virtual ostream& afisareVehicul(ostream&) const = 0;
	virtual istream& citireVehicul(istream&) = 0;
};


// --------- CLASA VEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Vehicul : public IOInterfaceVehicul, public InterfataVehicul{

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
	virtual ~Vehicul() {}

	// OPERATORIi >> SI <<
	friend istream& operator >>(istream&, Vehicul&);
	friend ostream& operator <<(ostream&, const Vehicul&);
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out) // virtuale ca sa pot apela cu pointeri la clasa de baza (?)

	// SETTER DISPONIBIL
	void setDisponibil(bool);

	// GETTER DISPONIBIL
	bool getDisponibil();
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
	
// SETTER DISPONIBIL
void Vehicul::setDisponibil(bool disponibil) { this->disponibil = disponibil; }

// GETTER DISPONIBIL
bool Vehicul::getDisponibil() { return disponibil; }


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
	virtual ~VehiculCarburant() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculCarburant&);
	friend ostream& operator <<(ostream&, const VehiculCarburant&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
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
	virtual ~VehiculElectric() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculElectric&);
	friend ostream& operator <<(ostream&, const VehiculElectric&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
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

	cout << "Introduceti una dintre cele 3 litere pentru tipul de hibrid (M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid): ";
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
	int nrVehiculeCumparate;
	vector<Vehicul*> vehiculeCumparate;
	double plataRamasa;
	double creditMaxim;

public:
	
	// CONSTRUCTOR FARA PARAMETRI
	Client();

	// CONSTRUCTOR CU PARAMETRI
	Client(string, int, vector<Vehicul*>, double, double);

	// COPY CONSTRUCTOR
	Client(const Client&);

	// OPERATOR =
	Client& operator=(const Client&);

	// DESTRUCTOR
	~Client();

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, Client&);
	friend ostream& operator <<(ostream&, const Client&);

};

// CONSTRUCTOR FARA PARAMETRI
Client::Client() : nume("Anonim"), nrVehiculeCumparate(0), vehiculeCumparate(), plataRamasa(0), creditMaxim(0) {}

// CONSTRUCTOR CU PARAMETRI
Client::Client(string nume, int nrVehiculeCumparate, vector<Vehicul*> vehiculeCumparate, double plataRamasa, double creditMaxim) : nume(nume), nrVehiculeCumparate(nrVehiculeCumparate), vehiculeCumparate(vehiculeCumparate), plataRamasa(plataRamasa), creditMaxim(creditMaxim) {}

// COPY CONSTRUCTOR
Client::Client(const Client& obj) : nume(obj.nume), nrVehiculeCumparate(obj.nrVehiculeCumparate), vehiculeCumparate(obj.vehiculeCumparate), plataRamasa(obj.plataRamasa), creditMaxim(obj.creditMaxim) {}

// OPERATOR =
Client& Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
		this->vehiculeCumparate = obj.vehiculeCumparate;
		this->plataRamasa = obj.plataRamasa;
		this->creditMaxim = obj.creditMaxim;
	}
	return *this;
}

// DESTRUCTOR
Client::~Client()
{
	for (int i = 0; i < nrVehiculeCumparate; i++)
	{
		delete vehiculeCumparate[i];
	}
}

// OPERATORII >> SI <<
istream& operator >>(istream& in, Client& obj)
{
	cout << "Nume: ";
    getline(in, obj.nume);
	cout << "Numar vehicule cumparate: ";
	in >> obj.nrVehiculeCumparate;
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		char tipMotor;
		cout << "\nCe tip de motor are vehiculul " << i + 1 <<"?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
		in >> tipMotor;
		cout << endl;
		if (tipMotor == 'C')
		{
			VehiculCarburant* v = new VehiculCarburant();
			in >> *v;
			if (v->getDisponibil() == true)
			{
				cout << "\nAti setat disponibilitatea vehiculului " << i + 1 << " la TRUE, dar vehiculul este deja vandut. Acesta va fi memorat ca indisponibil in mod implicit.\n";
				v->setDisponibil(false);
			}
			obj.vehiculeCumparate.push_back(v);
		}
		else if (tipMotor == 'E')
		{
			VehiculElectric* v = new VehiculElectric();
			in >> *v;
			if (v->getDisponibil() == true)
			{
				cout << "\nAti setat disponibilitatea vehiculului " << i + 1 << " la TRUE, dar vehiculul este deja vandut. Acesta va fi memorat ca indisponibil in mod implicit.\n";
				v->setDisponibil(false);
			}
			obj.vehiculeCumparate.push_back(v);
		}
		else if (tipMotor == 'H')
		{
			VehiculHibrid* v = new VehiculHibrid();
			in >> *v;
			if (v->getDisponibil() == true)
			{
				cout << "\nAti setat disponibilitatea vehiculului " << i + 1 << " la TRUE, dar vehiculul este deja vandut. Acesta va fi memorat ca indisponibil in mod implicit.\n";
				v->setDisponibil(false);
			}
			obj.vehiculeCumparate.push_back(v);
		}
		else
		{
			cout << "Introduceti una dintre literele C, E sau H." << endl;
			i--;
		}
	}
	cout << "\nPlata ramasa: ";
	in >> obj.plataRamasa;
	cout << "Credit maxim: ";
	in >> obj.creditMaxim;
	return in;
}
ostream& operator <<(ostream& out, const Client& obj)
{
	out << "\nNume: " << obj.nume << endl;
	cout << endl;
	out << "Vehicule cumparate:\n" << endl;
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		out << "Vehiculul " << i + 1 << ":" << endl;
		out << *obj.vehiculeCumparate[i] << endl;
	}
	out << "\nPlata ramasa: " << obj.plataRamasa << endl;
	out << "Credit maxim: " << obj.creditMaxim << endl;
	return out;
}

// --------- CLASA SHOWROOM ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Showroom {
	string numeShowroom;
	string adresa;
	int nrVehiculeDisponibile;
	vector<Vehicul*> vehiculeDisponibile;
public:
	// CONSTRUCTOR FARA PARAMETRI
	Showroom();

	// CONSTRUCTOR CU PARAMETRI
	Showroom(string, string, int, vector<Vehicul*>);

	// COPY CONSTRUCTOR
	Showroom(const Showroom&);

	// OPERATOR =
	Showroom& operator=(const Showroom&);

	// DESTRUCTOR
	~Showroom();

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, Showroom&);
	friend ostream& operator <<(ostream&, const Showroom&);
};

// CONSTRUCTOR FARA PARAMETRI
Showroom::Showroom() : numeShowroom("Nedefinit"), adresa("Nedefinita"), nrVehiculeDisponibile(0), vehiculeDisponibile() {}

// CONSTRUCTOR CU PARAMETRI
Showroom::Showroom(string numeShowroom, string adresa, int nrVehiculeDisponibile, vector<Vehicul*> vehiculeDisponibile) : numeShowroom(numeShowroom), adresa(adresa), nrVehiculeDisponibile(nrVehiculeDisponibile), vehiculeDisponibile(vehiculeDisponibile) {}

// COPY CONSTRUCTOR
Showroom::Showroom(const Showroom& obj) : numeShowroom(obj.numeShowroom), adresa(obj.adresa), nrVehiculeDisponibile(obj.nrVehiculeDisponibile), vehiculeDisponibile(obj.vehiculeDisponibile) {}

// OPERATOR =
Showroom& Showroom::operator=(const Showroom& obj)
{
	if (this != &obj)
	{
		this->numeShowroom = obj.numeShowroom;
		this->adresa = obj.adresa;
		this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
		this->vehiculeDisponibile = obj.vehiculeDisponibile;
	}
	return *this;
}

// DESTRUCTOR
Showroom::~Showroom()
{
	for (int i = 0; i < nrVehiculeDisponibile; i++)
	{
		delete vehiculeDisponibile[i];
	}
}

// OPERATORII >> SI <<
istream& operator >>(istream& in, Showroom& obj)
{
	cout << "Nume showroom: ";
	getline(in, obj.numeShowroom);
	cout << "Adresa showroom: ";
	getline(in, obj.adresa);
	cout << "Numar vehicule disponibile: ";
	in >> obj.nrVehiculeDisponibile;
	for (int i = 0; i < obj.nrVehiculeDisponibile; i++)
	{
		char tipMotor;
		cout << "\nCe tip de motor are vehiculul " << i + 1 << "?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
		in >> tipMotor;
		cout << endl;
		if (tipMotor == 'C')
		{
			VehiculCarburant* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'E')
		{
			VehiculElectric* v = new VehiculElectric();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'H')
		{
			VehiculHibrid* v = new VehiculHibrid();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else
		{
			cout << "Introduceti una dintre literele C, E sau H." << endl;
			i--;
		}
	}
	return in;
}
ostream& operator <<(ostream& out, const Showroom& obj)
{
	out << "\nNume showroom: " << obj.numeShowroom << endl;
	out << "Adresa showroom: " << obj.adresa << endl;
	cout << endl;
	out << "Vehicule disponibile:\n" << endl;
	for (int i = 0; i < obj.nrVehiculeDisponibile; i++)
	{
		out << "Vehiculul " << i + 1 << ":" << endl;
		out << *obj.vehiculeDisponibile[i] << endl;
	}
	return out;
}

int main()
{
	Vehicul v1;
	/*cin >> v1;*/
	/*cout << v1 << endl;*/

	//VehiculCarburant v2;
	///*cin >> v2;*/
	//cout << v2 << endl;

	//VehiculElectric v3;
	///*cin >> v3;*/
	//cout << v3 << endl;

	//VehiculHibrid v4;
	///*cin >> v4;*/
	//cout << v4 << endl;

	/*Vehicul* p = new VehiculHibrid();
	p->afisareVehicul(cout);*/

	/*Client c1;
	cin >> c1;
	cout << c1;*/

	Showroom s1;
	cin >> s1;
	cout << s1;


	return 0;
}
