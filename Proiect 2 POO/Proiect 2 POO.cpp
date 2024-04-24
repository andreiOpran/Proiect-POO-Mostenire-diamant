/*

IDE: Visual Studio
Platform toolset: Visual Studio 2022 (v143)

*/

#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

class Vehicul; // ca sa mearga functia din InterfataVehicul care returneaza Vehicul*

class InterfataVehicul {

public:
	virtual double valoareaRealaVehicul() const = 0;
	virtual double costFolosireSiIntretinere() const = 0; // calcul pentru 1 an, presupunem ca intretinerea este X * valoarea reala a vehiculului, unde X = 0.03 la VehiculCarburant, X = 0.01 la VehiculElectric, X = 0.02 la VehiculHibrid
	virtual Vehicul* virtualCopyConstructor() const = 0; // PT CC SI OP= DIN SHOWROOM, CLIENT SI TRANZACTIE	

};


// --------- CLASA IOINTERFACEVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class IOInterfaceVehicul {

public:
	virtual ostream& afisareVehicul(ostream&) const = 0;
	virtual istream& citireVehicul(istream&) = 0;
};


// --------- CLASA VEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Vehicul : public IOInterfaceVehicul, public InterfataVehicul {

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
	virtual ~Vehicul() {} // virtual - cand distrug un new VehiculDerivat() sa se distruga complet

	// OPERATORIi >> SI <<
	friend istream& operator >>(istream&, Vehicul&);
	friend ostream& operator <<(ostream&, const Vehicul&);
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out) // virtuale ca sa pot apela cu pointeri la clasa de baza (?)

	// FUNCTIE VALOAREA REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;

	// VCC
	Vehicul* virtualCopyConstructor() const override;

	// SETTER MARCA
	void setMarca(string);

	// SETTER MODEL
	void setModel(string);

	// SETTER AN FABRICATIE
	void setAnFabricatie(int);

	// SETTER DISPONIBIL
	void setDisponibil(bool);

	// GETTER DISPONIBIL
	bool getDisponibil() const;

	// SETTER PRET
	void setPret(double);

	// GETTER MARCA
	string getMarca() const;

	// GETTER MODEL
	string getModel() const;

};

// CONSTRUCTOR FARA PARAMETRI
Vehicul::Vehicul() : marca("Anonim"), model("Anonim"), anFabricatie(0), disponibil(false), pret(0) {}

// CONSTRUCTOR CU PARAMETRI
Vehicul::Vehicul(string marca, string model, int anFabricatie, bool disponibil, double pret) :marca(marca), model(model), anFabricatie(anFabricatie), disponibil(disponibil), pret(pret) {}

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

// FUNCTIE VALOAREA REALA VEHICUL
double Vehicul::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	double indiceVechime = 1 - (0.1 * vechime);
	double indiceMarca = marca == "Audi" || marca == "Mercedes-Benz" || marca == "BMW" ? 1.2 : 1.0;
	if (pret * indiceVechime * indiceMarca > pret)
		return pret;
	else
		return pret * indiceVechime * indiceMarca;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double Vehicul::costFolosireSiIntretinere() const { return 0.03 * valoareaRealaVehicul(); }

// VCC
Vehicul* Vehicul::virtualCopyConstructor() const { return new Vehicul(*this); }

// SETTER MARCA
void Vehicul::setMarca(string marca) { this->marca = marca; }

// SETTER MODEL
void Vehicul::setModel(string model) { this->model = model; }

// SETTER AN FABRICATIE
void Vehicul::setAnFabricatie(int anFabricatie) { this->anFabricatie = anFabricatie; }

// SETTER DISPONIBIL
void Vehicul::setDisponibil(bool disponibil) { this->disponibil = disponibil; }

// GETTER DISPONIBIL
bool Vehicul::getDisponibil() const { return disponibil; }

// SETTER PRET
void Vehicul::setPret(double pret) { this->pret = pret; }

// GETTER MARCA
string Vehicul::getMarca() const { return marca; }

// GETTER MODEL
string Vehicul::getModel() const { return model; }


// --------- CLASA VEHICULCARBURANT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculCarburant : virtual public Vehicul {

protected:
	string tipCarburant;
	double consum; // litri/100km

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculCarburant();

	// CONSTRUCTOR CU PARAMETRI
	VehiculCarburant(string, string, int, bool, double, string, double);

	// COPY CONSTRUCTOR
	VehiculCarburant(const VehiculCarburant&);

	// OPERATOR =
	VehiculCarburant& operator=(const VehiculCarburant&);

	// DESTRUCTOR
	virtual ~VehiculCarburant() {}

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, VehiculCarburant&);
	friend ostream& operator <<(ostream&, const VehiculCarburant&); // trebuie const pt ca out este const in functia cealalta cu return obj.afisare(out)
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override;

	// FUNCTIE VALOAREA REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;

	// VCC
	virtual Vehicul* virtualCopyConstructor() const override;

	// SETTER TIP CARBURANT
	void setTipCarburant(string);

	// SETTER CONSUM
	void setConsum(double);
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

// FUNCTIE VALOAREA REALA VEHICUL
double VehiculCarburant::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	double indiceVechime = 1 - (0.1 * vechime);
	double indiceMarca = marca == "Audi" || marca == "Mercedes-Benz" || marca == "BMW" ? 1.2 : 1.0;
	double indiceConsum = consum < 5 ? 1.1 : 1.0;
	if (pret * indiceVechime * indiceMarca * indiceConsum > pret)
		return pret;
	else
		return pret * indiceVechime * indiceMarca * indiceConsum;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double VehiculCarburant::costFolosireSiIntretinere() const
{
	double cost = 0.03 * valoareaRealaVehicul(); // intretinerea pe an
	double costCarburant = 0; // voi calcula conmform https://www.capital.ro/preturile-la-pompa-9-aprilie-benzina-motorina-pretul-petrolului.html#:~:text=Conform%20Peco%20Online%2C%20un%20litru%20de%20benzin%C4%83%20standard,premium%20cost%C4%83%20%C3%AEntre%207%2C83%20lei%20%C8%99i%208%2C01%20lei.
	if (tipCarburant == "Benzina")
		costCarburant = 7.24;
	else
		if (tipCarburant == "Motorina")
			costCarburant = 7.47;
		else
			costCarburant = 0;
	// presupunem ca se fac 20000 km/an
	cost += (double)(20000 / 100) * consum * costCarburant;
	return cost;
}

// VCC
Vehicul* VehiculCarburant::virtualCopyConstructor() const { return new VehiculCarburant(*this); }

// SETTER TIP CARBURANT
void VehiculCarburant::setTipCarburant(string tipCarburant) { this->tipCarburant = tipCarburant; }

// SETTER CONSUM
void VehiculCarburant::setConsum(double consum) { this->consum = consum; }


// --------- CLASA VEHICULELECTRIC ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculElectric : virtual public Vehicul {

protected:
	double autonomieKm;
	double timpIncarcare; // pana la 100%, in ore

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
	istream& citireVehicul(istream& in) override;
	ostream& afisareVehicul(ostream& out) const override;

	// FUNCTIE VALOAREA REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;

	// VCC
	virtual Vehicul* virtualCopyConstructor() const override;

	// SETTER AUTONOMIE KM
	void setAutonomieKm(double);

	// SETTER TIMP INCARCARE
	void setTimpIncarcare(double);
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

// FUNCTIE VALOAREA REALA VEHICUL
double VehiculElectric::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	double indiceVechime = 1 - (0.1 * vechime);
	double indiceMarca = marca == "Audi" || marca == "Mercedes-Benz" || marca == "BMW" ? 1.2 : 1.0;
	double indiceAutonomie = autonomieKm > 500 ? 1.1 : 1.0;
	double indiceTimpIncarcare = timpIncarcare < 6 ? 1.1 : 1.0; // 6 ore
	if (pret * indiceVechime * indiceMarca * indiceAutonomie * indiceTimpIncarcare > pret)
		return pret;
	else
		return pret * indiceVechime * indiceMarca * indiceAutonomie * indiceTimpIncarcare;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double VehiculElectric::costFolosireSiIntretinere() const
{
	double cost = 0.01 * valoareaRealaVehicul(); // intretinerea pe an, 0.01 in loc de 0.03, masinile electrice sunt mai fiabile
	double costElectricitateOIncarcare = 80; // 80 lei/incarcare
	// presupunem ca se fac 20000 km/an
	cost += (20000 / autonomieKm) * costElectricitateOIncarcare;
	return cost;
}

// VCC
Vehicul* VehiculElectric::virtualCopyConstructor() const { return new VehiculElectric(*this); }

// SETTER AUTONOMIE KM
void VehiculElectric::setAutonomieKm(double autonomieKm) { this->autonomieKm = autonomieKm; }

// SETTER TIMP INCARCARE
void VehiculElectric::setTimpIncarcare(double timpIncarcare) { this->timpIncarcare = timpIncarcare; }

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

	// FUNCTIE VALOAREA REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;

	// VCC
	Vehicul* virtualCopyConstructor() const override;

	// SETTER TIP HIBRID
	void setTipHibrid(char);
};

// CONSTRUCTOR FARA PARAMETRI
VehiculHibrid::VehiculHibrid() : VehiculCarburant(), VehiculElectric(), tipHibrid('0') {}

// CONSTRUCTOR CU PARAMETRI
VehiculHibrid::VehiculHibrid(string marca, string model, int anFabricatie, bool disponibil, double pret, string tipCarburant, double consum, double autonomieKm, double timpIncarcare, char tipHibrid) : Vehicul(marca, model, anFabricatie, disponibil, pret), VehiculCarburant(marca, model, anFabricatie, disponibil, pret, tipCarburant, consum), VehiculElectric(marca, model, anFabricatie, disponibil, pret, autonomieKm, timpIncarcare), tipHibrid(tipHibrid) {}

//  COPY CONSTRUCTOR
VehiculHibrid::VehiculHibrid(const VehiculHibrid& obj) : Vehicul(obj), VehiculCarburant(obj), VehiculElectric(obj), tipHibrid(obj.tipHibrid) {}

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
	out << "Autonomie in KM: " << autonomieKm << endl;
	out << "Timp incarcare: " << timpIncarcare << endl;

	out << "Tip hibrid: " << tipHibrid << endl;
	return out;
}
ostream& operator <<(ostream& out, const VehiculHibrid& obj) { return obj.afisareVehicul(out); }

// FUNCTIE VALOAREA REALA VEHICUL
double VehiculHibrid::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	double indiceVechime = 1 - (0.1 * vechime);
	double indiceMarca = marca == "Audi" || marca == "Mercedes-Benz" || marca == "BMW" ? 1.2 : 1.0;
	double indiceConsum = consum < 5 ? 1.1 : 1.0;
	double indiceAutonomie = autonomieKm > 500 ? 1.1 : 1.0;
	double indiceTimpIncarcare = timpIncarcare < 6 ? 1.1 : 1.0; // 6 ore
	if (pret * indiceVechime * indiceMarca * indiceConsum * indiceAutonomie * indiceTimpIncarcare > pret)
		return pret;
	else
		return pret * indiceVechime * indiceMarca * indiceConsum * indiceAutonomie * indiceTimpIncarcare;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double VehiculHibrid::costFolosireSiIntretinere() const
{
	double cost = 0.02 * valoareaRealaVehicul(); // intretinerea pe an, 0.02 in loc de 0.03, masinile hibride sunt mai fiabile, dar nu la fel de fiabile ca cele electrice care eu indicele 0.01
	double costCarburant = 0; // voi calcula conmform https://www.capital.ro/preturile-la-pompa-9-aprilie-benzina-motorina-pretul-petrolului.html#:~:text=Conform%20Peco%20Online%2C%20un%20litru%20de%20benzin%C4%83%20standard,premium%20cost%C4%83%20%C3%AEntre%207%2C83%20lei%20%C8%99i%208%2C01%20lei.
	if (tipCarburant == "Benzina")
		costCarburant = 7.24;
	else
		if (tipCarburant == "Motorina")
			costCarburant = 7.47;
		else
			costCarburant = 0;
	// presupunem ca se fac 20000 km/an
	cost += (double)(20000 / 100) * consum * costCarburant;
	cost /= 2; // este vehicul hibrid, pp ca se foloseste jumatate din timp motorul electric
	double costElectricitateOIncarcare = 80; // 80 lei/incarcare

	cost += (20000 / autonomieKm) * costElectricitateOIncarcare;
	cost /= 2; // este vehicul hibrid, pp ca se foloseste jumatate din timp motorul electric
	return cost;
}

// VCC
Vehicul* VehiculHibrid::virtualCopyConstructor() const { return new VehiculHibrid(*this); }

// SETTER TIP HIBRID
void VehiculHibrid::setTipHibrid(char tipHibrid) { this->tipHibrid = tipHibrid; }


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

	// FUNCTIE CALCULARE CERDIT SCORE
	double calculCreditScore() const; // plataRamasa / creditMaxim

	// SETTER NUME
	void setNume(string);

	// GETTER NUME
	string getNume() const;

	// GETTER NR VEHICULE CUMPARATE
	int getNrVehiculeCumparate() const;

	// GETTER VEHICULE CUMPARATE
	vector<Vehicul*> getVehiculeCumparate() const;

	// SETTER PLATA RAMASA
	void setPlataRamasa(double);

	// GETTER PLATA RAMASA
	double getPlataRamasa() const;

	// SETTER CREDIT MAXIM
	void setCreditMaxim(double);

	//GETTER CREDIT MAXIM
	double getCreditMaxim() const;

	// OPERATIA CLIENT + VEHICUL*
	Client operator+(Vehicul*);
};

// CONSTRUCTOR FARA PARAMETRI
Client::Client() : nume("Anonim"), nrVehiculeCumparate(0), vehiculeCumparate(), plataRamasa(0), creditMaxim(0) {}

// CONSTRUCTOR CU PARAMETRI
Client::Client(string nume, int nrVehiculeCumparate, vector<Vehicul*> vehiculeCumparate, double plataRamasa, double creditMaxim) : nume(nume), nrVehiculeCumparate(nrVehiculeCumparate), vehiculeCumparate(vehiculeCumparate), plataRamasa(plataRamasa), creditMaxim(creditMaxim) {}

// COPY CONSTRUCTOR
Client::Client(const Client& obj) : nume(obj.nume), plataRamasa(obj.plataRamasa), creditMaxim(obj.creditMaxim)
{
	// deep copy

	for (int i = 0; i < this->vehiculeCumparate.size(); i++) // eliberare memorie this
	{
		delete this->vehiculeCumparate[i];
	}
	this->vehiculeCumparate.clear();

	this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
	for (int i = 0; i < obj.vehiculeCumparate.size(); i++)
	{
		this->vehiculeCumparate.push_back(obj.vehiculeCumparate[i]->virtualCopyConstructor());
	}
}

// OPERATOR =
Client& Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->plataRamasa = obj.plataRamasa;
		this->creditMaxim = obj.creditMaxim;

		//deep copy

		for (int i = 0; i < this->vehiculeCumparate.size(); i++) // eliberare memorie this
		{
			delete this->vehiculeCumparate[i];
		}
		this->vehiculeCumparate.clear();

		this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
		for (int i = 0; i < obj.vehiculeCumparate.size(); i++)
		{
			this->vehiculeCumparate.push_back(obj.vehiculeCumparate[i]->virtualCopyConstructor());
		}
	}
	return *this;
}

// DESTRUCTOR
Client::~Client()
{
	for (int i = 0; i < vehiculeCumparate.size(); i++)
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
		cout << "\nCe tip de motor are vehiculul " << i + 1 << "?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
		in >> tipMotor;
		cout << endl;
		if (tipMotor == 'C')
		{
			Vehicul* v = new VehiculCarburant();
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
			Vehicul* v = new VehiculElectric();
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
			Vehicul* v = new VehiculHibrid();
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
	if (obj.vehiculeCumparate.size())
		out << "Vehicule cumparate:\n\n" << endl;
	else
		out << "Clientul nu are vehicule cumparate.\n";
	for (int i = 0; i < obj.vehiculeCumparate.size(); i++)
	{
		out << "Vehiculul " << i + 1 << ":" << endl;
		out << *obj.vehiculeCumparate[i] << endl;
	}
	out << "\nPlata ramasa: " << obj.plataRamasa << endl;
	out << "Credit maxim: " << obj.creditMaxim << endl << endl;
	return out;
}

// FUNCTIE CALCULARE CREDIT SCORE
double Client::calculCreditScore() const
{
	double creditScore = 0;
	if (creditMaxim != 0)
		creditScore = plataRamasa / creditMaxim;
	else
		creditScore = 0;
	return creditScore;
}

// SETTER NUME
void Client::setNume(string nume) { this->nume = nume; }

// GETTER NUME
string Client::getNume() const { return nume; }

// GETTER NR VEHICULE CUMPARATE
int Client::getNrVehiculeCumparate() const { /*return nrVehiculeCumparate;*/return vehiculeCumparate.size(); }

// GETTER VEHICULE CUMPARATE
vector<Vehicul*> Client::getVehiculeCumparate() const { return vehiculeCumparate; }

// SETTER PLATA RAMASA
void Client::setPlataRamasa(double plataRamasa) { this->plataRamasa = plataRamasa; }

// GETTER PLATA RAMASA
double Client::getPlataRamasa() const { return plataRamasa; }

// SETTER CREDIT MAXIM
void Client::setCreditMaxim(double creditMaxim) { this->creditMaxim = creditMaxim; }

// GETTER CREDIT MAXIM
double Client::getCreditMaxim() const { return creditMaxim; }


// OPERATIA CLIENT + VEHICUL*
Client Client::operator+(Vehicul* obj)
{
	Client copie = *this;
	copie.vehiculeCumparate.push_back(obj);
	copie.nrVehiculeCumparate++;
	return copie;
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

	// FUNCTIE CALCULARE PRET VEHICUL PT CLIENT (PRET CUMPRARE + PROFIT)
	double calculPretVehiculCuProfit(Vehicul*);

	// GETTER VEHICULE DISPONIBILE
	vector<Vehicul*> getVehiculeDisponibile() const;

	// SETTER NUME
	void setNumeShowroom(string);

	// SETTER ADRESA
	void setAdresa(string);

	// GETTER NR VEHICULE DISPONIBILE
	int getNrVehiculeDisponibile() const;

	// GETTER NUME SHOWROOM
	string getNumeShowroom() const;

	// SETTER NR VEHICULE DISPONIBILE
	void setNrVehiculeDisponibile(int);

	// OPERATUL SHOWROOM + VEHICUL*
	Showroom operator+(Vehicul*);

	// OPERATUL SHOWROOM - VEHICUL* (SE VA TRANSMITE CA PARAMETRU INDEX-UL VEHICULULUI DIN VECTORUL DE VEHICULE DISPONIBILE)
	Showroom operator-(int);

};

// CONSTRUCTOR FARA PARAMETRI
Showroom::Showroom() : numeShowroom("Nedefinit"), adresa("Nedefinita"), nrVehiculeDisponibile(0), vehiculeDisponibile() {}

// CONSTRUCTOR CU PARAMETRI
Showroom::Showroom(string numeShowroom, string adresa, int nrVehiculeDisponibile, vector<Vehicul*> vehiculeDisponibile) : numeShowroom(numeShowroom), adresa(adresa), nrVehiculeDisponibile(nrVehiculeDisponibile), vehiculeDisponibile(vehiculeDisponibile) {}

// COPY CONSTRUCTOR
Showroom::Showroom(const Showroom& obj) : numeShowroom(obj.numeShowroom), adresa(obj.adresa)
{
	//deep copy

	for (int i = 0; i < this->vehiculeDisponibile.size(); i++) // stergere this
	{
		delete this->vehiculeDisponibile[i];
	}
	this->vehiculeDisponibile.clear();

	this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
	for (int i = 0; i < obj.vehiculeDisponibile.size(); i++)
	{
		this->vehiculeDisponibile.push_back(obj.vehiculeDisponibile[i]->virtualCopyConstructor());
	}
}

// OPERATOR =
Showroom& Showroom::operator=(const Showroom& obj)
{
	if (this != &obj)
	{
		this->numeShowroom = obj.numeShowroom;
		this->adresa = obj.adresa;

		//deep copy

		for (int i = 0; i < this->vehiculeDisponibile.size(); i++) // stergere this
		{
			delete this->vehiculeDisponibile[i];
		}
		this->vehiculeDisponibile.clear();

		this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
		for (int i = 0; i < obj.vehiculeDisponibile.size(); i++)
		{
			this->vehiculeDisponibile.push_back(obj.vehiculeDisponibile[i]->virtualCopyConstructor());
		}
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
			Vehicul* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'E')
		{
			Vehicul* v = new VehiculElectric();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'H')
		{
			Vehicul* v = new VehiculHibrid();
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
	if (obj.vehiculeDisponibile.size() > 0)
	{
		out << "Vehicule disponibile:\n" << endl;
		for (int i = 0; i < obj.vehiculeDisponibile.size(); i++)
		{
			out << "Vehiculul " << i + 1 << ":" << endl;
			out << *obj.vehiculeDisponibile[i] << endl;
		}
	}
	else
		out << "Showroom-ul nu are vehicule in stoc.\n";
	return out;
}

// FUNCTIE CALCULARE PRET VEHICUL PT CLIENT (PRET CUMPRARE + PROFIT)
double Showroom::calculPretVehiculCuProfit(Vehicul* v)
{
	return v->valoareaRealaVehicul() + 0.05 * v->valoareaRealaVehicul();
}

// GETTER VEHICULE DISPONIBILE
vector<Vehicul*> Showroom::getVehiculeDisponibile() const { return vehiculeDisponibile; }

// SETTER NUME
void Showroom::setNumeShowroom(string numeShowroom) { this->numeShowroom = numeShowroom; }

// SETTER ADRESA
void Showroom::setAdresa(string adresa) { this->adresa = adresa; }

// GETTER NR VEHICULE DISPONIBILE
int Showroom::getNrVehiculeDisponibile() const { /*return nrVehiculeDisponibile;*/return vehiculeDisponibile.size(); }

// GETTER NUME SHOWROOM
string Showroom::getNumeShowroom() const { return numeShowroom; }

// SETTER NR VEHICULE DISPONIBILE
void Showroom::setNrVehiculeDisponibile(int nrVehiculeDisponibile) { this->nrVehiculeDisponibile = nrVehiculeDisponibile; }

// OPERATUL SHOWROOM + VEHICUL*
Showroom Showroom::operator+(Vehicul* obj)
{
	Showroom copie = *this;
	copie.vehiculeDisponibile.push_back(obj);
	copie.nrVehiculeDisponibile++;
	return copie;
}

// OPERATUL SHOWROOM - VEHICUL* (SE VA TRANSMITE CA PARAMETRU INDEX-UL VEHICULULUI DIN VECTORUL DE VEHICULE DISPONIBILE)
Showroom Showroom::operator-(int index)
{
	try {
		if (index > nrVehiculeDisponibile)
		{
			throw 1;
		}
		if (index < 0)
		{
			throw 2;
		}
		Showroom copie = *this;
		delete copie.vehiculeDisponibile[index];
		copie.vehiculeDisponibile.erase(copie.vehiculeDisponibile.begin() + index);
		copie.nrVehiculeDisponibile--;
		return copie;
	}
	catch (int var)
	{
		if (var == 1)
		{
			cout << "\n****************************************************************EROARE****************************************************************\n";
			cout << "\nEroare!\nIn operatia de stergere al unui vehicul din showroom, index-ul introdus este mai mare decat numarul de vehicule disponibile.\nVectorul de vehicule din " << this->getNumeShowroom() << " a ramas nemodificat.\n";
			cout << "\n****************************************************************EROARE****************************************************************\n";
			return *this;
		}
		else
			if (var == 2)
			{
				cout << "\n*********************************************EROARE*********************************************\n";
				cout << "\nEroare!\nIn operatia de stergere al unui vehicul din showroom index-ul introdus este negativ.\nVectorul de vehicule din " << this->getNumeShowroom() << " a ramas nemodificat.\n";
				cout << "\n*********************************************EROARE*********************************************\n";
				return *this;
			}
	}
}


// --------- CLASA TRANZACTIE ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Tranzactie {
	const int idTranzactie;
	static int nrTranzactii;
	Client client;
	Vehicul* vehiculCumparat;
	double pretFinal; // pret final = avans + credit
	double avans;
	double credit;

public:

	// CONSTRUCTOR FARA PARAMETRI
	Tranzactie();

	// CONSTRUCTOR CU PARAMETRI
	Tranzactie(Client, Vehicul*, double, double, double);

	// COPY CONSTRUCTOR
	Tranzactie(const Tranzactie&);

	// OPERATOR =
	Tranzactie& operator=(const Tranzactie&);

	// DESTRUCTOR
	~Tranzactie();

	// OPERATORII >> SI <<
	friend istream& operator >>(istream&, Tranzactie&);
	friend ostream& operator <<(ostream&, const Tranzactie&);

	// GETTER ID TRANZACTIE
	int getIdTranzactie() const;

	// GETTER NR TRANZACTII
	static int getNrTranzactii();

	// SETTER NR TRANZACTII
	static void setNrTranzactii(int nrTranzactii);

	// SETTER PRET FINAL
	void setPretFinal(double);

	// GETTER PRET FINAL
	double getPretFinal() const;

	// SETTER AVANS
	void setAvans(double);

	// GETTER AVANS
	double getAvans() const;

	// SETTER CREDIT
	void setCredit(double);

	// GETTER CREDIT
	double getCredit() const;

	// GETTER VEHICUL CUMPARAT
	Vehicul* getVehiculCumparat() const;

	// SETTER CLIENT
	void setClient(Client);

	// SETTER VEHICUL*
	void setVehiculCumparat(Vehicul*);
};

// CONSTRUCTOR FARA PARAMETRI
Tranzactie::Tranzactie() : idTranzactie(++nrTranzactii + 100000), client(), vehiculCumparat(), pretFinal(0), avans(0), credit(0) {}

// CONSTRUCTOR CU PARAMETRI
Tranzactie::Tranzactie(Client client, Vehicul* vehiculCumparat, double pretFinal, double avans, double credit) : idTranzactie(++nrTranzactii + 100000), client(client), vehiculCumparat(vehiculCumparat), pretFinal(pretFinal), avans(avans), credit(credit) {}

// COPY CONSTRUCTOR
Tranzactie::Tranzactie(const Tranzactie& obj) : idTranzactie(obj.idTranzactie), client(obj.client), pretFinal(obj.pretFinal), avans(obj.avans), credit(obj.credit)
{
	this->vehiculCumparat = obj.vehiculCumparat->virtualCopyConstructor();
}

// OPERATOR =
Tranzactie& Tranzactie::operator=(const Tranzactie& obj)
{
	if (this != &obj)
	{
		this->client = obj.client;
		this->pretFinal = obj.pretFinal;
		this->avans = obj.avans;
		this->credit = obj.credit;
		this->vehiculCumparat = obj.vehiculCumparat->virtualCopyConstructor();
	}
	return *this;
}

// DESTRUCTOR
Tranzactie::~Tranzactie()
{
	if (vehiculCumparat != nullptr) // uneori incearca sa il stearga de doua ori 
	{
		vehiculCumparat = nullptr;
		delete vehiculCumparat;
	}
}

// OPERATORII >> SI <<
istream& operator >>(istream& in, Tranzactie& obj)
{
	cout << "Clientul care face tranzactia:\n";
	in >> obj.client;
	cout << "\nVehiculul cumparat:\n";
	char tipMotor;
	cout << "\nCe tip de motor are vehiculul?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
	in >> tipMotor;
	cout << endl;
	if (tipMotor == 'C')
	{
		Vehicul* v = new VehiculCarburant();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else if (tipMotor == 'E')
	{
		Vehicul* v = new VehiculElectric();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else if (tipMotor == 'H')
	{
		Vehicul* v = new VehiculHibrid();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else
	{
		cout << "Introduceti una dintre literele C, E sau H." << endl;
	}
	cout << "Atentie! Pretul final trebuie sa fie egal cu suma dintre avans si credit.\nUrmatoarele date care se cer sunt: pretul final, avansul si creditul.\n";
	cout << "Pret final: ";
	in >> obj.pretFinal;
	cout << "Avans: ";
	in >> obj.avans;
	cout << "Credit: ";
	in >> obj.credit;
	return in;
}
ostream& operator <<(ostream& out, const Tranzactie& obj)
{
	out << "\nID Tranzactie: " << obj.idTranzactie << "\n\n";
	out << "Numele clientului: " << obj.client.getNume() << "\n\n";
	out << "Vehiculul cumparat:\n" << *obj.vehiculCumparat;
	out << "\nPret final: " << obj.pretFinal << endl;
	out << "Avans: " << obj.avans << endl;
	out << "Credit: " << obj.credit << endl;
	return out;
}

// GETTER ID TRANZACTIE
int Tranzactie::getIdTranzactie() const { return idTranzactie; }

// GETTER NR TRANZACTII
int Tranzactie::getNrTranzactii() { return nrTranzactii; }

// SETTER NR TRANZACTII
void Tranzactie::setNrTranzactii(int nrTranzactii) { Tranzactie::nrTranzactii = nrTranzactii; }

// SETTER PRET FINAL
void Tranzactie::setPretFinal(double pretFinal) { this->pretFinal = pretFinal; }

// GETTER PRET FINAL
double Tranzactie::getPretFinal() const { return pretFinal; }

// SETTER AVANS
void Tranzactie::setAvans(double avans) { this->avans = avans; }

// GETTER AVANS
double Tranzactie::getAvans() const { return avans; }

// SETTER CREDIT
void Tranzactie::setCredit(double credit) { this->credit = credit; }

// GETTER CREDIT
double Tranzactie::getCredit() const { return credit; }

// GETTER VEHICUL CUMPARAT
Vehicul* Tranzactie::getVehiculCumparat() const { return vehiculCumparat; }

// SETTER CLIENT
void Tranzactie::setClient(Client client) { this->client = client; }

// SETTER VEHICUL*
void Tranzactie::setVehiculCumparat(Vehicul* vehiculCumparat) { this->vehiculCumparat = vehiculCumparat; }

int Tranzactie::nrTranzactii = 0;

Vehicul* vehiculCumparat = nullptr; // UN POINTER PT GENERARE TRANZACTIE

int main()
{
	// MENIU INTERACTIV

	vector<Vehicul*> vehicule;
	vector<Client> clienti;
	vector<Showroom> showroomuri;
	vector<Tranzactie> tranzactii;

	Vehicul* daciaLogan = new VehiculCarburant("Dacia", "Logan", 2015, true, 10000, "Motorina", 5.5);
	Vehicul* daciaSpring = new VehiculElectric("Dacia", "Spring", 2020, true, 15000, 200, 6);
	Vehicul* daciaJogger = new VehiculHibrid("Dacia", "Jogger", 2025, true, 20000, "Benzina", 6, 500, 3, 'F');
	vehicule.push_back(daciaLogan);
	vehicule.push_back(daciaSpring);
	vehicule.push_back(daciaJogger);

	Vehicul* daciaLoganAndrei = daciaLogan->virtualCopyConstructor();
	Vehicul* daciaSpringAndrei = daciaSpring->virtualCopyConstructor();
	Vehicul* daciaJoggerAlex = daciaJogger->virtualCopyConstructor();
	daciaLoganAndrei->setDisponibil(false);
	daciaSpringAndrei->setDisponibil(false);
	daciaJoggerAlex->setDisponibil(false);

	Client AndreiPopescu("Andrei Popescu", 2, { /*daciaLoganAndrei, daciaSpringAndrei*/ }, 0, 20000);
	Client AlexIonescu("Alex Ionescu", 1, { /*daciaJoggerAlex*/ }, 0, 30000);
	clienti.push_back(AndreiPopescu);
	clienti.push_back(AlexIonescu);

	Vehicul* daciaLoganShowroomBucuresti = daciaLogan->virtualCopyConstructor();
	Vehicul* daciaSpringShowroomBucuresti = daciaSpring->virtualCopyConstructor();
	Vehicul* daciaJoggerShowroomBucuresti = daciaJogger->virtualCopyConstructor();
	Vehicul* daciaLoganShowroomCluj = daciaLogan->virtualCopyConstructor();
	Vehicul* daciaJoggerShowroomCluj = daciaJogger->virtualCopyConstructor();

	Showroom showroomDaciaBucuresti("Showroom Dacia Bucuresti", "Bucuresti", 3, { daciaLoganShowroomBucuresti, daciaSpringShowroomBucuresti, daciaJoggerShowroomBucuresti });
	Showroom showroomDaciaCluj("Showroom Dacia Cluj", "Cluj", 2, { daciaLoganShowroomCluj, daciaJoggerShowroomCluj });
	showroomuri.push_back(showroomDaciaBucuresti);
	showroomuri.push_back(showroomDaciaCluj);
	showroomDaciaBucuresti.setNrVehiculeDisponibile(3);
	showroomDaciaCluj.setNrVehiculeDisponibile(2);

	//Vehicul* daciaLoganTranzactie1 = daciaLogan->virtualCopyConstructor();
	//Vehicul* daciaSpringTranzactie2 = daciaSpring->virtualCopyConstructor();
	//Vehicul* daciaJoggerTranzactie3 = daciaJogger->virtualCopyConstructor();
	//daciaLoganTranzactie1->setDisponibil(false);
	//daciaSpringTranzactie2->setDisponibil(false);
	//daciaJoggerTranzactie3->setDisponibil(false);

	//Tranzactie tranzactie1(AndreiPopescu, daciaLoganTranzactie1, 10000, 5000, 5000);
	//Tranzactie tranzactie2(AndreiPopescu, daciaSpringTranzactie2, 15000, 10000, 5000);
	//Tranzactie tranzactie3(AlexIonescu, daciaJoggerTranzactie3, 20000, 10000, 10000);
	//tranzactii.push_back(tranzactie1);
	//tranzactii.push_back(tranzactie2);
	//tranzactii.push_back(tranzactie3);

	bool okAfisareEndlInceput = true;
	int k = 1, comanda;
	while (k == 1)
	{
		if (okAfisareEndlInceput == false)
		{
			cout << endl;
			cout << "// ------------------------------------------------------------------------------------------------------------------ //" << endl << endl;
		}
		if (okAfisareEndlInceput == true)
		{
			cout << "\n// --------------- DEALER AUTO --------------- // \n\n";
			cout << endl;
			okAfisareEndlInceput = false;
		}
		cout << "1. Intrare in submeniul Modele de vehicule\n";
		cout << "2. Intrare in submeniul Clienti\n";
		cout << "3. Intrare in submeniul Showroom\n";
		cout << "4. Intrare in submeniul Tranzactii\n";
		cout << "5. Generare tranzactie noua, folosind datele din submeniurile Clienti si Showroom\n";
		cout << "\n6. Iesire din program\n";
		cout << endl << "> ";
		cin >> comanda;
		switch (comanda)
		{

		case 1:
		{
			int ramaiInVehicul = 1;
			while (ramaiInVehicul == 1)
			{
				int comandaVehicul;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare model de vehicul\n";
				cout << "2. Afisare modele vehicule\n";
				cout << "3. Stergere vehicul\n";
				cout << "4. Modificare model vehicul\n";
				cout << "5. Afisare valoarea reala al unui model de vehicul\n";
				cout << "6. Afisare cost folosire si intretinere al unui model de vehicul\n";
				cout << "\n7. Iesire din submeniul Modele de vehicule\n";
				cout << endl << "> ";
				cin >> comandaVehicul;
				switch (comandaVehicul)
				{
				case 1:
				{
					int okIntroducereTipMotor = 0;
					char tipMotor;
					cout << "\nCe tip de motor are vehiculul?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
					while (okIntroducereTipMotor == 0)
					{
						cin >> tipMotor;
						if (tipMotor == 'C')
						{
							Vehicul* p = new VehiculCarburant();
							cin >> *p;
							vehicule.push_back(p);
							okIntroducereTipMotor = 1;
						}
						else if (tipMotor == 'E')
						{
							Vehicul* p = new VehiculElectric();
							cin >> *p;
							vehicule.push_back(p);
							okIntroducereTipMotor = 1;
						}
						else if (tipMotor == 'H')
						{
							Vehicul* p = new VehiculHibrid();
							cin >> *p;
							vehicule.push_back(p);
							okIntroducereTipMotor = 1;
						}
						else
							cout << "\nIntroduceti una dintre literele C, E sau H.\n\n" << "> ";
					}
					break;
				}
				case 2:
				{
					if (vehicule.size() == 0)
						cout << "\nNu exista vehicule inregistrate, deci nu se pot afisa vehiculele.\n";
					else
					{
						for (int i = 0; i < vehicule.size(); i++)
						{
							cout << "Vehiculul " << i + 1 << ":" << endl;
							cout << *vehicule[i] << endl;
						}
					}
					break;
				}
				case 3:
				{
					if (vehicule.size() == 0)
						cout << "\nNu exista vehicule inregistrate, deci nu se poate efectua stergerea unui vehicul.\n";
					else
					{
						cout << "\nLista vehicule:\n\n";
						for (int i = 0; i < vehicule.size(); i++)
						{
							cout << "\nVehiculul " << i + 1 << ":" << endl;
							cout << *vehicule[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul vehiculului pe care doriti sa il stergeti.\nPentru anularea operatiei de stergere introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > vehicule.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << vehicule.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							delete vehicule[index - 1];
							vehicule.erase(vehicule.begin() + index - 1);
							cout << "\nVehiculul a fost sters cu succes.\n";
						}
					}
					break;
				}
				case 4:
				{
					if (vehicule.size() == 0)
						cout << "\nNu exista vehicule inregistrate, deci nu se poate efectua modificarea unui vehicul.\n";
					else
					{
						cout << "\nLista vehicule:\n\n";
						for (int i = 0; i < vehicule.size(); i++)
						{
							cout << "\nVehiculul " << i + 1 << ":" << endl;
							cout << *vehicule[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul vehiculului pe care doriti sa il modificati.\nPentru anularea operatiei de modificare introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > vehicule.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << vehicule.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							int okModificare = 0;
							while (okModificare == 0)
							{
								int comandaModificare;
								cout << "\nCe doriti sa modificati la vehiculul " << index << "?\n";
								// if (typeid(*vehicule[static_cast<std::vector<Vehicul*, std::allocator<Vehicul*>>::size_type>(index) - 1]) == typeid(VehiculCarburant)) // Visual Studio sugereaza sa schimb cu acest if()
								if (typeid(*vehicule[index - 1]) == typeid(VehiculCarburant)) // primesc mesajul lnt-arithmetic-overflow, 
								{
									cout << "1. Modificare marca\n";
									cout << "2. Modificare model\n";
									cout << "3. Modificare an fabricatie\n";
									cout << "4. Modificare disponibilitate\n";
									cout << "5. Modificare pret\n";
									cout << "6. Modificare consum\n";
									cout << "7. Modificare tip carburant\n";
									cout << "\n8. Finalizare modificare\n";
									cout << endl << "> ";
									cin >> comandaModificare;
									switch (comandaModificare)
									{
									case 1:
									{
										string marcaNoua;
										cout << "Introduceti noua marca: ";
										cin >> marcaNoua;
										vehicule[index - 1]->setMarca(marcaNoua);
										cout << "\nMarca a fost modificata cu succes.\n";
										break;
									}
									case 2:
									{
										string modelNou;
										cout << "Introduceti noul model: ";
										cin >> modelNou;
										vehicule[index - 1]->setModel(modelNou);
										cout << "\nModelul a fost modificat cu succes.\n";
										break;
									}
									case 3:
									{
										int anFabricatieNou;
										cout << "Introduceti noul an de fabricatie: ";
										cin >> anFabricatieNou;
										vehicule[index - 1]->setAnFabricatie(anFabricatieNou);
										cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
										break;
									}
									case 4:
									{
										bool disponibilNou;
										cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
										cin >> disponibilNou;
										vehicule[index - 1]->setDisponibil(disponibilNou);
										cout << "\nDisponibilitatea a fost modificata cu succes.\n";
										break;
									}
									case 5:
									{
										double pretNou;
										cout << "Introduceti noul pret: ";
										cin >> pretNou;
										vehicule[index - 1]->setPret(pretNou);
										cout << "\nPretul a fost modificat cu succes.\n";
										break;
									}
									case 6:
									{
										double consumNou;
										cout << "Introduceti noul consum: ";
										cin >> consumNou;
										VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]);
										vehiculCarburant->setConsum(consumNou);
										cout << "\nConsumul a fost modificat cu succes.\n";
										break;
									}
									case 7:
									{
										string tipCarburantNou;
										cout << "Introduceti noul tip de carburant: ";
										cin >> tipCarburantNou;
										VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]);
										vehiculCarburant->setTipCarburant(tipCarburantNou);
										cout << "\nTipul de carburant a fost modificat cu succes.\n";
										break;
									}
									case 8:
									{
										okModificare = 1;
										break;
									}
									}
								}
								else
									if (typeid(*vehicule[index - 1]) == typeid(VehiculElectric))
									{
										cout << "1. Modificare marca\n";
										cout << "2. Modificare model\n";
										cout << "3. Modificare an fabricatie\n";
										cout << "4. Modificare disponibilitate\n";
										cout << "5. Modificare pret\n";
										cout << "6. Modificare autonomie\n";
										cout << "7. Modificare timp incarcare\n";
										cout << "\n8. Finalizare modificare\n";
										cout << endl << "> ";
										cin >> comandaModificare;
										switch (comandaModificare)
										{
										case 1:
										{
											string marcaNoua;
											cout << "Introduceti noua marca: ";
											cin >> marcaNoua;
											vehicule[index - 1]->setMarca(marcaNoua);
											cout << "\nMarca a fost modificata cu succes.\n";
											break;
										}
										case 2:
										{
											string modelNou;
											cout << "Introduceti noul model: ";
											cin >> modelNou;
											vehicule[index - 1]->setModel(modelNou);
											cout << "\nModelul a fost modificat cu succes.\n";
											break;
										}
										case 3:
										{
											int anFabricatieNou;
											cout << "Introduceti noul an de fabricatie: ";
											cin >> anFabricatieNou;
											vehicule[index - 1]->setAnFabricatie(anFabricatieNou);
											cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
											break;
										}
										case 4:
										{
											bool disponibilNou;
											cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
											cin >> disponibilNou;
											vehicule[index - 1]->setDisponibil(disponibilNou);
											cout << "\nDisponibilitatea a fost modificata cu succes.\n";
											break;
										}
										case 5:
										{
											double pretNou;
											cout << "Introduceti noul pret: ";
											cin >> pretNou;
											vehicule[index - 1]->setPret(pretNou);
											cout << "\nPretul a fost modificat cu succes.\n";
											break;
										}
										case 6:
										{
											double autonomieNoua;
											cout << "Introduceti noua autonomie: ";
											cin >> autonomieNoua;
											VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]);
											vehiculElectric->setAutonomieKm(autonomieNoua);
											cout << "\nAutonomia a fost modificata cu succes.\n";
											break;
										}
										case 7:
										{
											double timpIncarcareNou;
											cout << "Introduceti noul timp de incarcare: ";
											cin >> timpIncarcareNou;
											VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]);
											vehiculElectric->setTimpIncarcare(timpIncarcareNou);
											cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
											break;
										}
										case 8:
										{
											okModificare = 1;
											break;
										}
										}
									}

									else
										if (typeid(*vehicule[index - 1]) == typeid(VehiculHibrid))
										{
											cout << "1. Modificare marca\n";
											cout << "2. Modificare model\n";
											cout << "3. Modificare an fabricatie\n";
											cout << "4. Modificare disponibilitate\n";
											cout << "5. Modificare pret\n";
											cout << "6. Modificare consum\n";
											cout << "7. Modificare tip carburant\n";
											cout << "8. Modificare autonomie\n";
											cout << "9. Modificare timp incarcare\n";
											cout << "10. Modificare tip hibrid\n";
											cout << "\n11. Finalizare modificare\n";
											cout << endl << "> ";
											cin >> comandaModificare;
											switch (comandaModificare)
											{
											case 1:
											{
												string marcaNoua;
												cout << "Introduceti noua marca: ";
												cin >> marcaNoua;
												vehicule[index - 1]->setMarca(marcaNoua);
												cout << "\nMarca a fost modificata cu succes.\n";
												break;
											}
											case 2:
											{
												string modelNou;
												cout << "Introduceti noul model: ";
												cin >> modelNou;
												vehicule[index - 1]->setModel(modelNou);
												cout << "\nModelul a fost modificat cu succes.\n";
												break;
											}
											case 3:
											{
												int anFabricatieNou;
												cout << "Introduceti noul an de fabricatie: ";
												cin >> anFabricatieNou;
												vehicule[index - 1]->setAnFabricatie(anFabricatieNou);
												cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
												break;
											}
											case 4:
											{
												bool disponibilNou;
												cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
												cin >> disponibilNou;
												vehicule[index - 1]->setDisponibil(disponibilNou);
												cout << "\nDisponibilitatea a fost modificata cu succes.\n";
												break;
											}
											case 5:
											{
												double pretNou;
												cout << "Introduceti noul pret: ";
												cin >> pretNou;
												vehicule[index - 1]->setPret(pretNou);
												cout << "\nPretul a fost modificat cu succes.\n";
												break;
											}
											case 6:
											{
												double consumNou;
												cout << "Introduceti noul consum: ";
												cin >> consumNou;
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]);
												vehiculCarburant->setConsum(consumNou);
												cout << "\nConsumul a fost modificat cu succes.\n";
												break;
											}
											case 7:
											{
												string tipCarburantNou;
												cout << "Introduceti noul tip de carburant: ";
												cin >> tipCarburantNou;
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]);
												vehiculCarburant->setTipCarburant(tipCarburantNou);
												cout << "\nTipul de carburant a fost modificat cu succes.\n";
												break;
											}
											case 8:
											{
												double autonomieNoua;
												cout << "Introduceti noua autonomie: ";
												cin >> autonomieNoua;
												VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]);
												vehiculElectric->setAutonomieKm(autonomieNoua);
												cout << "\nAutonomia a fost modificata cu succes.\n";
												break;
											}
											case 9:
											{
												double timpIncarcareNou;
												cout << "Introduceti noul timp de incarcare: ";
												cin >> timpIncarcareNou;
												VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]);
												vehiculElectric->setTimpIncarcare(timpIncarcareNou);
												cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
												break;
											}
											case 10:
											{
												int introducereCorecta = 0;
												char tipHibridNou;
												cout << "Introduceti noul tip de hibrid (M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid): ";
												while (introducereCorecta == 0)
												{
													cin >> tipHibridNou;
													if (tipHibridNou == 'M' || tipHibridNou == 'F' || tipHibridNou == 'P')
													{
														VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(vehicule[index - 1]);
														vehiculHibrid->setTipHibrid(tipHibridNou);
														cout << "\nTipul de hibrid a fost modificat cu succes.\n";
														introducereCorecta = 1;
													}
													else
														cout << "Introduceti una dintre literele M, F sau P.\n" << "> ";
												}
												break;
											}
											case 11:
											{
												okModificare = 1;
												break;
											}
											}
										}
							}
						}
					}
				}
				case 5:
				{
					if (vehicule.size() == 0)
						cout << "\nNu exista vehicule inregistrate, deci nu se poate calcula valoarea reala a vreunui vehicul.\n";
					else
					{
						cout << "\nLista vehicule:\n\n";
						for (int i = 0; i < vehicule.size(); i++)
						{
							cout << "\nVehiculul " << i + 1 << ":" << endl;
							cout << *vehicule[i] << endl;
						}

						int okIntroducereIndex = 0;
						int index;
						cout << "Introduceti index-ul vehiculului pentru care doriti sa calculati valoarea reala.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> index;
							if (index < 1 || index > vehicule.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << vehicule.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						cout << "\nValoarea reala a vehiculului " << vehicule[index - 1]->getMarca() << ' ' << vehicule[index - 1]->getModel() << ", cu index-ul egal cu " << index << ", este de " << vehicule[index - 1]->valoareaRealaVehicul() << " euro.\n";
					}
					break;
				}
				case 6:
				{
					if (vehicule.size() == 0)
						cout << "\nNu exista vehicule inregistrate, deci nu se poate calcula costul folosirii si intretinerii vreunui vehicul.\n";
					else
					{
						cout << "\nLista vehicule:\n\n";
						for (int i = 0; i < vehicule.size(); i++)
						{
							cout << "\nVehiculul " << i + 1 << ":" << endl;
							cout << *vehicule[i] << endl;
						}

						int okIntroducereIndex = 0;
						int index;
						cout << "Introduceti index-ul vehiculului pentru care doriti sa calculati costul folosirii si intretinerii.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> index;
							if (index < 1 || index > vehicule.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << vehicule.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						cout << "\nCostul folosirii si intretinerii vehiculului " << vehicule[index - 1]->getMarca() << ' ' << vehicule[index - 1]->getModel() << ", cu index-ul egal cu " << index << ", este de " << vehicule[index - 1]->costFolosireSiIntretinere() << " euro/an, pentru un rulaj de 20.000 km/an.\n";
					}
					break;
				}
				case 7:
				{
					ramaiInVehicul = 0;
					break;
				}

				}

			}
			break;
		}
		case 2:
		{
			int iesiDinModificareVehicul = 0;
			int nuIntraIn5 = 0;
			int ramaiInClient = 1;
			while (ramaiInClient == 1)
			{
				int comandaClient;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare client\n";
				cout << "2. Afisare clienti\n";
				cout << "3. Stergere client\n";
				cout << "4. Modificare client\n";
				cout << "5. Afisare credit score pentru un anumit client\n";
				cout << "\n6. Iesire din submeniul Clienti\n";
				cout << endl << "> ";
				cin >> comandaClient;
				switch (comandaClient)
				{
				case 1:
				{
					Client c;
					cin.get(); // pt consumare \n dupa ce introduci 1 de la tastatura ca sa intri in meniul "Adaugare client"
					cin >> c;
					clienti.push_back(c);
					break;
				}
				case 2:
				{
					if (clienti.size() == 0)
						cout << "\nNu exista clienti inregistrati, deci nu se pot afisa clientii.\n";
					else
					{
						for (int i = 0; i < clienti.size(); i++)
						{
							cout << "\nClientul " << i + 1 << ":" << endl;
							cout << clienti[i] << endl;
						}
					}
					break;
				}
				case 3:
				{
					if (clienti.size() == 0)
						cout << "\nNu exista clienti inregistrati, deci nu se poate efectua stergerea unui client.\n";
					else
					{
						cout << "\nLista clienti:\n\n";
						for (int i = 0; i < clienti.size(); i++)
						{
							cout << "\nClientul " << i + 1 << ":" << endl;
							cout << clienti[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul clientului pe care doriti sa il stergeti.\nPentru anularea operatiei de stergere introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > clienti.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << clienti.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							clienti.erase(clienti.begin() + index - 1);
							cout << "\nClientul a fost sters cu succes.\n";
						}
					}
					break;
				}
				case 4:
				{
					nuIntraIn5 = 0;
					if (clienti.size() == 0)
						cout << "\nNu exista clienti inregistrati, deci nu se poate efectua modificarea unui client.\n";
					else
					{
						cout << "\nLista clienti:\n\n";
						for (int i = 0; i < clienti.size(); i++)
						{
							cout << "\nClientul " << i + 1 << ":" << endl;
							cout << clienti[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul clientului pe care doriti sa il modificati.\nPentru anularea operatiei de modificare introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								nuIntraIn5 = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > clienti.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << clienti.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							int okModificare = 0;
							while (okModificare == 0)
							{
								int comandaModificare;
								cout << "\nCe doriti sa modificati la clientul " << index << "?\n";
								cout << "1. Modificare nume\n";
								cout << "2. Modificare vehicule cumparate\n";
								cout << "3. Modificare plata ramasa\n";
								cout << "4. Modificare credit maxim\n";
								cout << "\n5. Finalizare modificare\n";
								cout << endl << "> ";
								cin >> comandaModificare;
								switch (comandaModificare)
								{
								case 1:
								{
									string numeNou;
									cout << "Introduceti noul nume: ";
									cin.get();
									getline(cin, numeNou);
									clienti[index - 1].setNume(numeNou);
									cout << "\nNumele a fost modificat cu succes.\n";
									break;
								}
								case 2:
								{
									introducereAnulare = 0;
									iesiDinModificareVehicul = 0;
									int okIntroducereIndexVehicul = 0;
									int indexVehicul;
									if (clienti[index - 1].getNrVehiculeCumparate() == 0)
										cout << "\nClientul nu a cumparat niciun vehicul, deci nu se poate efectua modificarea vehiculelor cumparate.\n";
									else
									{
										cout << "\nLista vehicule cumparate de clientul " << clienti[index - 1].getNume() << ":\n\n";
										for (int i = 0; i < clienti[index - 1].getNrVehiculeCumparate(); i++)
										{
											cout << "\nVehiculul " << i + 1 << ":" << endl;
											cout << *clienti[index - 1].getVehiculeCumparate()[i] << endl;
										}
										cout << "Introduceti index-ul vehiculului pe care doriti sa il modificati. Pentru anularea operatiei de modificare introduceti litera A\n\n" << "> ";
										while (okIntroducereIndexVehicul == 0)
										{
											cin >> verificareAnulare;
											if (verificareAnulare == 'A')
											{
												iesiDinModificareVehicul = 1;
												introducereAnulare = 1;
												okIntroducereIndexVehicul = 1;
												break;
											}
											else
												indexVehicul = verificareAnulare - '0';
											if (indexVehicul < 1 || indexVehicul > clienti[index - 1].getNrVehiculeCumparate())
												cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << clienti[index - 1].getNrVehiculeCumparate() << "].\n\n" << "> ";
											else
												okIntroducereIndexVehicul = 1;
										}
										if (introducereAnulare == 0)
										{
											int okModificare = 0;
											while (okModificare == 0)
											{
												int comandaModificare;
												cout << "\nCe doriti sa modificati la vehiculul " << indexVehicul << "?\n";
												if (typeid(*clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]) == typeid(VehiculCarburant))
												{
													cout << "1. Modificare marca\n";
													cout << "2. Modificare model\n";
													cout << "3. Modificare an fabricatie\n";
													cout << "4. Modificare disponibilitate\n";
													cout << "5. Modificare pret\n";
													cout << "6. Modificare consum\n";
													cout << "7. Modificare tip carburant\n";
													cout << "\n8. Finalizare modificare\n";
													cout << endl << "> ";
													cin >> comandaModificare;
													switch (comandaModificare)
													{
													case 1:
													{
														string marcaNoua;
														cout << "Introduceti noua marca: ";
														cin >> marcaNoua;
														clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setMarca(marcaNoua);
														cout << "\nMarca a fost modificata cu succes.\n";
														break;
													}
													case 2:
													{
														string modelNou;
														cout << "Introduceti noul model: ";
														cin >> modelNou;
														clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setModel(modelNou);
														cout << "\nModelul a fost modificat cu succes.\n";
														break;
													}
													case 3:
													{
														int anFabricatieNou;
														cout << "Introduceti noul an de fabricatie: ";
														cin >> anFabricatieNou;
														clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
														cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
														break;
													}
													case 4:
													{
														bool disponibilNou;
														cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
														cin >> disponibilNou;
														clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setDisponibil(disponibilNou);
														cout << "\nDisponibilitatea a fost modificata cu succes.\n";
														break;
													}
													case 5:
													{
														double pretNou;
														cout << "Introduceti noul pret: ";
														cin >> pretNou;
														clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setPret(pretNou);
														cout << "\nPretul a fost modificat cu succes.\n";
														break;
													}
													case 6:
													{
														double consumNou;
														cout << "Introduceti noul consum: ";
														cin >> consumNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
														vehiculCarburant->setConsum(consumNou);
														cout << "\nConsumul a fost modificat cu succes.\n";
														break;
													}
													case 7:
													{
														string tipCarburantNou;
														cout << "Introduceti noul tip de carburant: ";
														cin >> tipCarburantNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
														vehiculCarburant->setTipCarburant(tipCarburantNou);
														cout << "\nTipul de carburant a fost modificat cu succes.\n";
														break;
													}
													case 8:
													{
														iesiDinModificareVehicul = 1;
														okModificare = 1;
														break;
													}
													}
												}
												else
													if (typeid(*clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]) == typeid(VehiculElectric))
													{
														cout << "1. Modificare marca\n";
														cout << "2. Modificare model\n";
														cout << "3. Modificare an fabricatie\n";
														cout << "4. Modificare disponibilitate\n";
														cout << "5. Modificare pret\n";
														cout << "6. Modificare autonomie\n";
														cout << "7. Modificare timp incarcare\n";
														cout << "\n8. Finalizare modificare\n";
														cout << endl << "> ";
														cin >> comandaModificare;
														switch (comandaModificare)
														{
														case 1:
														{
															string marcaNoua;
															cout << "Introduceti noua marca: ";
															cin >> marcaNoua;
															clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setMarca(marcaNoua);
															cout << "\nMarca a fost modificata cu succes.\n";
															break;
														}
														case 2:
														{
															string modelNou;
															cout << "Introduceti noul model: ";
															cin >> modelNou;
															clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setModel(modelNou);
															cout << "\nModelul a fost modificat cu succes.\n";
															break;
														}
														case 3:
														{
															int anFabricatieNou;
															cout << "Introduceti noul an de fabricatie: ";
															cin >> anFabricatieNou;
															clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
															cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
															break;
														}
														case 4:
														{
															bool disponibilNou;
															cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
															cin >> disponibilNou;
															clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setDisponibil(disponibilNou);
															cout << "\nDisponibilitatea a fost modificata cu succes.\n";
															break;
														}
														case 5:
														{
															double pretNou;
															cout << "Introduceti noul pret: ";
															cin >> pretNou;
															clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setPret(pretNou);
															cout << "\nPretul a fost modificat cu succes.\n";
															break;
														}
														case 6:
														{
															double autonomieNoua;
															cout << "Introduceti noua autonomie: ";
															cin >> autonomieNoua;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
															vehiculElectric->setAutonomieKm(autonomieNoua);
															cout << "\nAutonomia a fost modificata cu succes.\n";
															break;
														}
														case 7:
														{
															double timpIncarcareNou;
															cout << "Introduceti noul timp de incarcare: ";
															cin >> timpIncarcareNou;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
															vehiculElectric->setTimpIncarcare(timpIncarcareNou);
															cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
															break;
														}
														case 8:
														{
															iesiDinModificareVehicul = 1;
															okModificare = 1;
															break;
														}
														}
													}

													else
														if (typeid(*clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]) == typeid(VehiculHibrid))
														{
															cout << "1. Modificare marca\n";
															cout << "2. Modificare model\n";
															cout << "3. Modificare an fabricatie\n";
															cout << "4. Modificare disponibilitate\n";
															cout << "5. Modificare pret\n";
															cout << "6. Modificare consum\n";
															cout << "7. Modificare tip carburant\n";
															cout << "8. Modificare autonomie\n";
															cout << "9. Modificare timp incarcare\n";
															cout << "10. Modificare tip hibrid\n";
															cout << "\n11. Finalizare modificare\n";
															cout << endl << "> ";
															cin >> comandaModificare;
															switch (comandaModificare)
															{
															case 1:
															{
																string marcaNoua;
																cout << "Introduceti noua marca: ";
																cin >> marcaNoua;
																clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setMarca(marcaNoua);
																cout << "\nMarca a fost modificata cu succes.\n";
																break;
															}
															case 2:
															{
																string modelNou;
																cout << "Introduceti noul model: ";
																cin >> modelNou;
																clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setModel(modelNou);
																cout << "\nModelul a fost modificat cu succes.\n";
																break;
															}
															case 3:
															{
																int anFabricatieNou;
																cout << "Introduceti noul an de fabricatie: ";
																cin >> anFabricatieNou;
																clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
																cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
																break;
															}
															case 4:
															{
																bool disponibilNou;
																cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
																cin >> disponibilNou;
																clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setDisponibil(disponibilNou);
																cout << "\nDisponibilitatea a fost modificata cu succes.\n";
																break;
															}
															case 5:
															{
																double pretNou;
																cout << "Introduceti noul pret: ";
																cin >> pretNou;
																clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]->setPret(pretNou);
																cout << "\nPretul a fost modificat cu succes.\n";
																break;
															}
															case 6:
															{
																double consumNou;
																cout << "Introduceti noul consum: ";
																cin >> consumNou;
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
																vehiculCarburant->setConsum(consumNou);
																cout << "\nConsumul a fost modificat cu succes.\n";
																break;
															}
															case 7:
															{
																string tipCarburantNou;
																cout << "Introduceti noul tip de carburant: ";
																cin >> tipCarburantNou;
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
																vehiculCarburant->setTipCarburant(tipCarburantNou);
																cout << "\nTipul de carburant a fost modificat cu succes.\n";
																break;
															}
															case 8:
															{
																double autonomieNoua;
																cout << "Introduceti noua autonomie: ";
																cin >> autonomieNoua;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
																vehiculElectric->setAutonomieKm(autonomieNoua);
																cout << "\nAutonomia a fost modificata cu succes.\n";
																break;
															}
															case 9:
															{
																double timpIncarcareNou;
																cout << "Introduceti noul timp de incarcare: ";
																cin >> timpIncarcareNou;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
																vehiculElectric->setTimpIncarcare(timpIncarcareNou);
																cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
																break;
															}
															case 10:
															{
																int introducereCorecta = 0;
																char tipHibridNou;
																cout << "Introduceti noul tip de hibrid (M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid): ";
																while (introducereCorecta == 0)
																{
																	cin >> tipHibridNou;
																	if (tipHibridNou == 'M' || tipHibridNou == 'F' || tipHibridNou == 'P')
																	{
																		VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]);
																		vehiculHibrid->setTipHibrid(tipHibridNou);
																		cout << "\nTipul de hibrid a fost modificat cu succes.\n";
																		introducereCorecta = 1;
																	}
																	else
																		cout << "Introduceti una dintre literele M, F sau P.\n" << "> ";
																}
																break;
															}
															case 11:
															{
																iesiDinModificareVehicul = 1;
																okModificare = 1;
																break;
															}
															}
														}
											}
										}
									}
								}
								case 3:
								{
									if (iesiDinModificareVehicul == 1)
									{
										iesiDinModificareVehicul = 0;
										break;
									}
									double plataRamasaNoua;
									cout << "Introduceti noua plata ramasa: ";
									cin >> plataRamasaNoua;
									clienti[index - 1].setPlataRamasa(plataRamasaNoua);
									cout << "\nPlata ramasa a fost modificata cu succes.\n";
									break;
								}
								case 4:
								{
									double creditMaximNou;
									cout << "Introduceti noul credit maxim: ";
									cin >> creditMaximNou;
									clienti[index - 1].setCreditMaxim(creditMaximNou);
									cout << "\nCreditul maxim a fost modificat cu succes.\n";
									break;
								}
								case 5:
								{
									nuIntraIn5 = 1;
									okModificare = 1;
									break;
								}
								}

							}
						}
					}
				}
				case 5:
				{
					if (nuIntraIn5 == 1)
					{
						nuIntraIn5 = 0;
						break;
					}
					if (clienti.size() == 0)
						cout << "\nNu exista clienti inregistrati, deci nu se poate calcula credit score-ul pentru niciun client.\n";
					else
					{
						cout << "\nLista clienti:\n\n";
						for (int i = 0; i < clienti.size(); i++)
						{
							cout << "\nClientul " << i + 1 << ":" << endl;
							cout << clienti[i] << endl;
						}

						int okIntroducereIndex = 0;
						int index;
						cout << "Introduceti index-ul clientului pentru care doriti sa calculati credit score-ul.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> index;
							if (index < 1 || index > clienti.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << clienti.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						cout << "\nCredit score-ul clientului " << clienti[index - 1].getNume() << " este " << clienti[index - 1].calculCreditScore() << ".\n";
					}
					break;
				}
				case 6:
				{
					ramaiInClient = 0;
					break;
				}

				}
			}
			break;
		}
		case 3:
		{
			int iesiDinModificareVehicul = 0;
			int nuIntraIn5 = 0;
			int ramaiInShowroom = 1;
			while (ramaiInShowroom)
			{
				int comandaShowroom;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare showroom\n";
				cout << "2. Afisare showroom-uri\n";
				cout << "3. Stergere showroom\n";
				cout << "4. Modificare showroom\n";
				cout << "5. Calcularea pretului unui vehicul, adaugand automat profitul\n";
				cout << "\n6. Iesire din submeniul Showroom-uri\n";
				cout << endl << "> ";
				cin >> comandaShowroom;
				switch (comandaShowroom)
				{
				case 1:
				{
					Showroom s;
					cin.get(); // pt consumare \n dupa ce introduci 1 de la tastatura ca sa intri in meniul "Adaugare showroom"
					cin >> s;
					showroomuri.push_back(s);
					break;
				}
				case 2:
				{
					if (showroomuri.size() == 0)
						cout << "\nNu exista showroom-uri inregistrate, deci nu se pot afisa showroom-urile.\n";
					else
					{
						cout << endl;
						for (int i = 0; i < showroomuri.size(); i++)
						{
							cout << "Showroom-ul " << i + 1 << ":" << endl;
							cout << showroomuri[i] << endl;
						}
					}
					break;
				}
				case 3:
				{
					if (showroomuri.size() == 0)
						cout << "\nNu exista showroom-uri inregistrate, deci nu se poate efectua stergerea unui showroom.\n";
					else
					{
						cout << "\nLista showroom-uri:\n\n";
						for (int i = 0; i < showroomuri.size(); i++)
						{
							cout << "\nShowroom-ul " << i + 1 << ":" << endl;
							cout << showroomuri[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul showroom-ului pe care doriti sa il stergeti.\nPentru anularea operatiei de stergere introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > showroomuri.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							showroomuri.erase(showroomuri.begin() + index - 1);
							cout << "\nShowroom-ul a fost sters cu succes.\n";
						}
					}
					break;
				}
				case 4:
				{
					nuIntraIn5 = 0;
					if (showroomuri.size() == 0)
						cout << "\nNu exista showroom-uri inregistrate, deci nu se poate efectua modificarea unui showroom.\n";
					else
					{
						cout << "\nLista showroom-uri:\n\n";
						for (int i = 0; i < showroomuri.size(); i++)
						{
							cout << "\nShowroom-ul " << i + 1 << ":" << endl;
							cout << showroomuri[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul showroom-ului pe care doriti sa il modificati.\nPentru anularea operatiei de modificare introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								nuIntraIn5 = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > showroomuri.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							int okModificare = 0;
							while (okModificare == 0)
							{
								int comandaModificare;
								cout << "\nCe doriti sa modificati la showroom-ul " << index << "?\n";
								cout << "1. Modificare nume\n";
								cout << "2. Modificare adresa\n";
								cout << "3. Modificare vehicule\n";
								cout << "4. Finalizare modificare\n";
								cout << endl << "> ";
								cin >> comandaModificare;
								switch (comandaModificare)
								{
								case 1:
								{
									string numeNou;
									cout << "Introduceti noul nume: ";
									cin.get();
									getline(cin, numeNou);
									showroomuri[index - 1].setNumeShowroom(numeNou);
									cout << "\nNumele a fost modificat cu succes.\n";
									break;
								}
								case 2:
								{
									string adresaNoua;
									cout << "Introduceti noua adresa: ";
									cin.get();
									getline(cin, adresaNoua);
									showroomuri[index - 1].setAdresa(adresaNoua);
									cout << "\nAdresa a fost modificata cu succes.\n";
									break;
								}
								case 3:
								{
									introducereAnulare = 0;
									iesiDinModificareVehicul = 0;
									int okIntroducereIndexVehicul = 0;
									int indexVehicul;
									if (showroomuri[index - 1].getNrVehiculeDisponibile() == 0)
										cout << "\nShowroom-ul nu are niciun vehicul, deci nu se poate efectua modificarea vehiculelor.\n";
									else
									{
										cout << "\nLista vehicule din showroom-ul " << showroomuri[index - 1].getNumeShowroom() << ":\n\n";
										for (int i = 0; i < showroomuri[index - 1].getNrVehiculeDisponibile(); i++)
										{
											cout << "\nVehiculul " << i + 1 << ":" << endl;
											cout << *showroomuri[index - 1].getVehiculeDisponibile()[i] << endl;
										}
										cout << "Introduceti index-ul vehiculului pe care doriti sa il modificati. Pentru anularea operatiei de modificare introduceti litera A\n\n" << "> ";
										while (okIntroducereIndexVehicul == 0)
										{
											cin >> verificareAnulare;
											if (verificareAnulare == 'A')
											{
												iesiDinModificareVehicul = 1;
												introducereAnulare = 1;
												okIntroducereIndexVehicul = 1;
												break;
											}
											else
												indexVehicul = verificareAnulare - '0';
											if (indexVehicul < 1 || indexVehicul > showroomuri[index - 1].getNrVehiculeDisponibile())
												cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri[index - 1].getNrVehiculeDisponibile() << "].\n\n" << "> ";
											else
												okIntroducereIndexVehicul = 1;
										}
										if (introducereAnulare == 0)
										{
											int okModificare = 0;
											while (okModificare == 0)
											{
												int comandaModificare;
												cout << "\nCe doriti sa modificati la vehiculul " << indexVehicul << "?\n";
												if (typeid(*showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]) == typeid(VehiculCarburant))
												{
													cout << "1. Modificare marca\n";
													cout << "2. Modificare model\n";
													cout << "3. Modificare an fabricatie\n";
													cout << "4. Modificare disponibilitate\n";
													cout << "5. Modificare pret\n";
													cout << "6. Modificare consum\n";
													cout << "7. Modificare tip carburant\n";
													cout << "\n8. Finalizare modificare\n";
													cout << endl << "> ";
													cin >> comandaModificare;
													switch (comandaModificare)
													{
													case 1:
													{
														string marcaNoua;
														cout << "Introduceti noua marca: ";
														cin >> marcaNoua;
														showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setMarca(marcaNoua);
														cout << "\nMarca a fost modificata cu succes.\n";
														break;
													}
													case 2:
													{
														string modelNou;
														cout << "Introduceti noul model: ";
														cin >> modelNou;
														showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setModel(modelNou);
														cout << "\nModelul a fost modificat cu succes.\n";
														break;
													}
													case 3:
													{
														int anFabricatieNou;
														cout << "Introduceti noul an de fabricatie: ";
														cin >> anFabricatieNou;
														showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
														cout << "\nAnul de fabricatie a fost modificat";
													}
													case 4:
													{
														bool disponibilNou;
														cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
														cin >> disponibilNou;
														showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setDisponibil(disponibilNou);
														cout << "\nDisponibilitatea a fost modificata cu succes.\n";
														break;
													}
													case 5:
													{
														double pretNou;
														cout << "Introduceti noul pret: ";
														cin >> pretNou;
														showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setPret(pretNou);
														cout << "\nPretul a fost modificat cu succes.\n";
														break;
													}
													case 6:
													{
														double consumNou;
														cout << "Introduceti noul consum: ";
														cin >> consumNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
														vehiculCarburant->setConsum(consumNou);
														cout << "\nConsumul a fost modificat cu succes.\n";
														break;
													}
													case 7:
													{
														string tipCarburantNou;
														cout << "Introduceti noul tip de carburant: ";
														cin >> tipCarburantNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
														vehiculCarburant->setTipCarburant(tipCarburantNou);
														cout << "\nTipul de carburant a fost modificat cu succes.\n";
														break;
													}
													case 8:
													{
														iesiDinModificareVehicul = 1;
														okModificare = 1;
														break;
													}

													}
												}
												else
													if (typeid(*showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]) == typeid(VehiculElectric))
													{
														cout << "1. Modificare marca\n";
														cout << "2. Modificare model\n";
														cout << "3. Modificare an fabricatie\n";
														cout << "4. Modificare disponibilitate\n";
														cout << "5. Modificare pret\n";
														cout << "6. Modificare autonomie\n";
														cout << "7. Modificare timp incarcare\n";
														cout << "\n8. Finalizare modificare\n";
														cout << endl << "> ";
														cin >> comandaModificare;
														switch (comandaModificare)
														{
														case 1:
														{
															string marcaNoua;
															cout << "Introduceti noua marca: ";
															cin >> marcaNoua;
															showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setMarca(marcaNoua);
															cout << "\nMarca a fost modificata cu succes.\n";
															break;
														}
														case 2:
														{
															string modelNou;
															cout << "Introduceti noul model: ";
															cin >> modelNou;
															showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setModel(modelNou);
															cout << "\nModelul a fost modificat cu succes.\n";
															break;
														}
														case 3:
														{
															int anFabricatieNou;
															cout << "Introduceti noul an de fabricatie: ";
															cin >> anFabricatieNou;
															showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
															cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
															break;
														}
														case 4:
														{
															bool disponibilNou;
															cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
															cin >> disponibilNou;
														}
														case 5:
														{
															double pretNou;
															cout << "Introduceti noul pret: ";
															cin >> pretNou;
															showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setPret(pretNou);
															cout << "\nPretul a fost modificat cu succes.\n";
															break;
														}
														case 6:
														{
															double autonomieNoua;
															cout << "Introduceti noua autonomie: ";
															cin >> autonomieNoua;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
															vehiculElectric->setAutonomieKm(autonomieNoua);
															cout << "\nAutonomia a fost modificata cu succes.\n";
															break;
														}
														case 7:
														{
															double timpIncarcareNou;
															cout << "Introduceti noul timp de incarcare: ";
															cin >> timpIncarcareNou;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
															vehiculElectric->setTimpIncarcare(timpIncarcareNou);
															cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
															break;
														}
														case 8:
														{
															iesiDinModificareVehicul = 1;
															okModificare = 1;
															break;
														}

														}
													}
													else
														if (typeid(*showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]) == typeid(VehiculHibrid))
														{
															cout << "1. Modificare marca\n";
															cout << "2. Modificare model\n";
															cout << "3. Modificare an fabricatie\n";
															cout << "4. Modificare disponibilitate\n";
															cout << "5. Modificare pret\n";
															cout << "6. Modificare consum\n";
															cout << "7. Modificare tip carburant\n";
															cout << "8. Modificare autonomie\n";
															cout << "9. Modificare timp incarcare\n";
															cout << "10. Modificare tip hibrid\n";
															cout << "\n11. Finalizare modificare\n";
															cout << endl << "> ";
															cin >> comandaModificare;
															switch (comandaModificare)
															{
															case 1:
															{
																string marcaNoua;
																cout << "Introduceti noua marca: ";
																cin >> marcaNoua;
																showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setMarca(marcaNoua);
																cout << "\nMarca a fost modificata cu succes.\n";
																break;
															}
															case 2:
															{
																string modelNou;
																cout << "Introduceti noul model: ";
																cin >> modelNou;
																showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setModel(modelNou);
																cout << "\nModelul a fost modificat cu succes.\n";
																break;
															}
															case 3:
															{
																int anFabricatieNou;
																cout << "Introduceti noul an de fabricatie: ";
																cin >> anFabricatieNou;
																showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setAnFabricatie(anFabricatieNou);
																cout << "\nAnul de fabricatie a fost modificat cu succes.\n";
																break;
															}
															case 4:
															{
																bool disponibilNou;
																cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
																cin >> disponibilNou;
																showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setDisponibil(disponibilNou);
																cout << "\nDisponibilitatea a fost modificata cu succes.\n";
																break;
															}
															case 5:
															{
																double pretNou;
																cout << "Introduceti noul pret: ";
																cin >> pretNou;
																showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]->setPret(pretNou);
																cout << "\nPretul a fost modificat cu succes.\n";
																break;
															}
															case 6:
															{
																double consumNou;
																cout << "Introduceti noul consum: ";
																cin >> consumNou;
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
																vehiculCarburant->setConsum(consumNou);
																cout << "\nConsumul a fost modificat cu succes.\n";
																break;
															}
															case 7:
															{
																string tipCarburantNou;
																cout << "Introduceti noul tip de carburant: ";
																cin >> tipCarburantNou;
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
																vehiculCarburant->setTipCarburant(tipCarburantNou);
																cout << "\nTipul de carburant a fost modificat cu succes.\n";
																break;
															}
															case 8:
															{
																double autonomieNoua;
																cout << "Introduceti noua autonomie: ";
																cin >> autonomieNoua;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
																vehiculElectric->setAutonomieKm(autonomieNoua);
																cout << "\nAutonomia a fost modificata cu succes.\n";
																break;
															}
															case 9:
															{
																double timpIncarcareNou;
																cout << "Introduceti noul timp de incarcare: ";
																cin >> timpIncarcareNou;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
																vehiculElectric->setTimpIncarcare(timpIncarcareNou);
																cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
																break;
															}
															case 10:
															{
																int introducereCorecta = 0;
																char tipHibridNou;
																cout << "Introduceti noul tip de hibrid (M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid): ";
																while (introducereCorecta == 0)
																{
																	cin >> tipHibridNou;
																	if (tipHibridNou == 'M' || tipHibridNou == 'F' || tipHibridNou == 'P')
																	{
																		VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]);
																		vehiculHibrid->setTipHibrid(tipHibridNou);
																		cout << "\nTipul de hibrid a fost modificat cu succes.\n";
																		introducereCorecta = 1;
																	}
																	else
																		cout << "Introduceti una dintre literele M, F sau P.\n" << "> ";
																}
																break;
															}
															case 11:
															{
																iesiDinModificareVehicul = 1;
																okModificare = 1;
																break;
															}

															}
														}
											}
										}
									}
								}
								case 4:
								{
									if (iesiDinModificareVehicul == 1)
									{
										iesiDinModificareVehicul = 0;
										break;
									}
									nuIntraIn5 = 1;
									okModificare = 1;
									break;
								}
								}
							}
						}
					}
				}
				case 5:
				{
					if (nuIntraIn5 == 1)
					{
						nuIntraIn5 = 0;
						break;
					}
					if (showroomuri.size() == 0)
						cout << "\nNu exista showroom-uri inregistrate, deci nu se poate calcula pretul plus profitul vreunui vehicul.\n";
					else
					{
						cout << "\nLista showroom-uri:\n\n";
						for (int i = 0; i < showroomuri.size(); i++)
						{
							cout << "\nShowroom-ul " << i + 1 << ":" << endl;
							cout << showroomuri[i] << endl;
						}

						int okIntroducereIndex = 0;
						int index;
						cout << "Introduceti index-ul showroom-ului pentru care doriti sa calculati pretul, plus profitul adaugat automat, al unui vehicul.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> index;
							if (index < 1 || index > showroomuri.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}

						int okIntroducereIndexVehicul = 0;
						int indexVehicul;
						cout << "\nLista vehicule din showroom-ul " << showroomuri[index - 1].getNumeShowroom() << ":\n\n";
						for (int i = 0; i < showroomuri[index - 1].getNrVehiculeDisponibile(); i++)
						{
							cout << "\nVehiculul " << i + 1 << ":" << endl;
							cout << *showroomuri[index - 1].getVehiculeDisponibile()[i] << endl;
						}
						cout << "Introduceti index-ul vehiculului pentru care doriti sa calculati pretul, plus profitul adaugat automat.\n\n" << "> ";
						while (okIntroducereIndexVehicul == 0)
						{
							cin >> indexVehicul;
							if (indexVehicul < 1 || indexVehicul > showroomuri[index - 1].getNrVehiculeDisponibile())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri[index - 1].getNrVehiculeDisponibile() << "].\n\n" << "> ";
							else
								okIntroducereIndexVehicul = 1;
						}
						cout << "\nPretul vehiculului " << indexVehicul << ", la care se adauga profitul, este de " << showroomuri[index - 1].calculPretVehiculCuProfit(showroomuri[index - 1].getVehiculeDisponibile()[indexVehicul - 1]) << " euro.\n";
					}

					break;
				}
				case 6:
				{
					ramaiInShowroom = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}
				}
			}

			break;
		}

		case 4:
		{
			int ramaiInTranzactie = 1;
			while (ramaiInTranzactie)
			{
				int comandaTranzactie;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare tranzactie\n";
				cout << "2. Afisare tranzactii\n";
				cout << "3. Stergere tranzactie\n";
				cout << "4. Modificare tranzactie\n";
				cout << "\n5. Iesire din submeniul Tranzactii\n";
				cout << endl << "> ";
				cin >> comandaTranzactie;
				switch (comandaTranzactie)
				{
				case 1:
				{
					Tranzactie t;
					cin.get(); // pt consumare \n dupa ce introduci 1 de la tastatura ca sa intri in meniul "Adaugare tranzactie"
					cin >> t;
					tranzactii.push_back(t);
					break;
				}
				case 2:
				{
					if (tranzactii.size() == 0)
						cout << "\nNu exista tranzactii inregistrate, deci nu se pot afisa tranzactiile.\n";
					else
					{
						cout << endl;
						for (int i = 0; i < tranzactii.size(); i++)
						{
							cout << "\nTranzactia " << i + 1 << ":" << endl;
							cout << tranzactii[i] << endl;
						}
					}
					break;
				}
				case 3:
				{
					if (tranzactii.size() == 0)
						cout << "\nNu exista tranzactii inregistrate, deci nu se poate efectua stergerea unei tranzactii.\n";
					else
					{
						cout << "\nLista tranzactii:\n\n";
						for (int i = 0; i < tranzactii.size(); i++)
						{
							cout << "\nTranzactia " << i + 1 << ":" << endl;
							cout << tranzactii[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul tranzactiei pe care doriti sa o stergeti.\nPentru anularea operatiei de stergere introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > tranzactii.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << tranzactii.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0 && tranzactii.size() != 0)
						{
							tranzactii.erase(tranzactii.begin() + index - 1);
							if (tranzactii.size() != 0)
							{
								tranzactii[0].setNrTranzactii(tranzactii[0].getNrTranzactii() - 1);
							}
							if (tranzactii.size() == 0)
							{
								cout << "\nTranzactia a fost stearsa cu succes.\nNu mai exista tranzactii inregistrate.\n";
								break;
							}
							else
								cout << "\nTranzactia a fost stearsa cu succes.\n";
						}
					}
					break;
				}
				case 4:
				{
					if (tranzactii.size() == 0)
						cout << "\nNu exista tranzactii inregistrate, deci nu se poate efectua modificarea unei tranzactii.\n";
					else
					{
						cout << "\nLista tranzactii:\n\n";
						for (int i = 0; i < tranzactii.size(); i++)
						{
							cout << "\nTranzactia " << i + 1 << ":" << endl;
							cout << tranzactii[i] << endl;
						}

						int okIntroducereIndex = 0, introducereAnulare = 0;
						int index;
						char verificareAnulare;
						cout << "Introduceti index-ul tranzactiei pe care doriti sa o modificati.\nPentru anularea operatiei de modificare introduceti litera A.\n\n" << "> ";
						while (okIntroducereIndex == 0)
						{
							cin >> verificareAnulare;
							if (verificareAnulare == 'A')
							{
								introducereAnulare = 1;
								okIntroducereIndex = 1;
								break;
							}
							else
								index = verificareAnulare - '0';
							if (index < 1 || index > tranzactii.size())
								cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << tranzactii.size() << "].\n\n" << "> ";
							else
								okIntroducereIndex = 1;
						}
						if (introducereAnulare == 0)
						{
							int okModificare = 0;
							while (okModificare == 0)
							{
								int comandaModificare;
								cout << "\nCe doriti sa modificati la tranzactia " << index << "?\n";
								cout << "1. Modificare vehicul\n";
								cout << "2. Modificare pret final, avans si credit\n";
								cout << "3. Finalizare modificare\n";
								cout << endl << "> ";
								cin >> comandaModificare;
								switch (comandaModificare)
								{
								case 1:
								{
									int iesiDinModificareVehicul = 0;
									int okModificare = 0;
									int introducereAnulare = 0;
									Vehicul* vehiculNou = tranzactii[index - 1].getVehiculCumparat();

									while (okModificare == 0)
									{
										int comandaModificare;
										cout << "\nCe doriti sa modificati la vehiculul cumparat in tranzactia " << index << "?\n";
										if (typeid(*vehiculNou) == typeid(VehiculCarburant))
										{
											cout << "1. Modificare marca\n";
											cout << "2. Modificare model\n";
											cout << "3. Modificare an fabricatie\n";
											cout << "4. Modificare disponibilitate\n";
											cout << "5. Modificare pret\n";
											cout << "6. Modificare consum\n";
											cout << "7. Modificare tip carburant\n";
											cout << "\n8. Finalizare modificare\n";
											cout << endl << "> ";
											cin >> comandaModificare;
											switch (comandaModificare)
											{
											case 1:
											{
												string marcaNoua;
												cout << "Introduceti noua marca: ";
												cin >> marcaNoua;
												vehiculNou->setMarca(marcaNoua);
												cout << "\nMarca a fost modificata cu succes.\n";
												break;
											}
											case 2:
											{
												string modelNou;
												cout << "Introduceti noul model: ";
												cin >> modelNou;
												vehiculNou->setModel(modelNou);
												cout << "\nModelul a fost modificat cu succes.\n";
												break;
											}
											case 3:
											{
												int anFabricatieNou;
												cout << "Introduceti noul an de fabricatie: ";
												cin >> anFabricatieNou;
												vehiculNou->setAnFabricatie(anFabricatieNou);
												cout << "\nAnul de fabricatie a fost modificat";
											}
											case 4:
											{
												bool disponibilNou;
												cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
												cin >> disponibilNou;
												vehiculNou->setDisponibil(disponibilNou);
												cout << "\nDisponibilitatea a fost modificata cu succes.\n";
												break;
											}
											case 5:
											{
												double pretNou;
												cout << "Introduceti noul pret: ";
												cin >> pretNou;
												vehiculNou->setPret(pretNou);
												cout << "\nPretul a fost modificat cu succes.\n";
												break;
											}
											case 6:
											{
												double consumNou;
												cout << "Introduceti noul consum: ";
												cin >> consumNou;
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehiculNou);
												vehiculCarburant->setConsum(consumNou);
												cout << "\nConsumul a fost modificat cu succes.\n";
												break;
											}
											case 7:
											{
												string tipCarburantNou;
												cout << "Introduceti noul tip de carburant: ";
												cin >> tipCarburantNou;
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehiculNou);
												vehiculCarburant->setTipCarburant(tipCarburantNou);
												cout << "\nTipul de carburant a fost modificat cu succes.\n";
												break;
											}
											case 8:
											{
												iesiDinModificareVehicul = 1;
												okModificare = 1;
												break;
											}
											}
										}
										else
											if (typeid(*vehiculNou) == typeid(VehiculElectric))
											{
												cout << "1. Modificare marca\n";
												cout << "2. Modificare model\n";
												cout << "3. Modificare an fabricatie\n";
												cout << "4. Modificare disponibilitate\n";
												cout << "5. Modificare pret\n";
												cout << "6. Modificare autonomie\n";
												cout << "7. Modificare timp incarcare\n";
												cout << "\n8. Finalizare modificare\n";
												cout << endl << "> ";
												cin >> comandaModificare;
												switch (comandaModificare)
												{
												case 1:
												{
													string marcaNoua;
													cout << "Introduceti noua marca: ";
													cin >> marcaNoua;
													vehiculNou->setMarca(marcaNoua);
													cout << "\nMarca a fost modificata cu succes.\n";
													break;
												}
												case 2:
												{
													string modelNou;
													cout << "Introduceti noul model: ";
													cin >> modelNou;
													vehiculNou->setModel(modelNou);
													cout << "\nModelul a fost modificat cu succes.\n";
													break;
												}
												case 3:
												{
													int anFabricatieNou;
													cout << "Introduceti noul an de fabricatie: ";
													cin >> anFabricatieNou;
													vehiculNou->setAnFabricatie(anFabricatieNou);
													cout << "\nAnul de fabricatie a fost modificat";
												}
												case 4:
												{
													bool disponibilNou;
													cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
													cin >> disponibilNou;
													vehiculNou->setDisponibil(disponibilNou);
													cout << "\nDisponibilitatea a fost modificata cu succes.\n";
													break;
												}
												case 5:
												{
													double pretNou;
													cout << "Introduceti noul pret: ";
													cin >> pretNou;
													vehiculNou->setPret(pretNou);
													cout << "\nPretul a fost modificat cu succes.\n";
													break;
												}
												case 6:
												{
													double autonomieNoua;
													cout << "Introduceti noua autonomie: ";
													cin >> autonomieNoua;
													VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehiculNou);
													vehiculElectric->setAutonomieKm(autonomieNoua);
													cout << "\nAutonomia a fost modificata cu succes.\n";
													break;
												}
												case 7:
												{
													double timpIncarcareNou;
													cout << "Introduceti noul timp de incarcare: ";
													cin >> timpIncarcareNou;
													VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehiculNou);
													vehiculElectric->setTimpIncarcare(timpIncarcareNou);
													cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
													break;
												}
												case 8:
												{
													iesiDinModificareVehicul = 1;
													okModificare = 1;
													break;
												}
												}
											}
											else
												if (typeid(*vehiculNou) == typeid(VehiculHibrid))
												{
													cout << "1. Modificare marca\n";
													cout << "2. Modificare model\n";
													cout << "3. Modificare an fabricatie\n";
													cout << "4. Modificare disponibilitate\n";
													cout << "5. Modificare pret\n";
													cout << "6. Modificare consum\n";
													cout << "7. Modificare tip carburant\n";
													cout << "8. Modificare autonomie\n";
													cout << "9. Modificare timp incarcare\n";
													cout << "10. Modificare tip hibrid\n";
													cout << "\n11. Finalizare modificare\n";
													cout << endl << "> ";
													cin >> comandaModificare;
													switch (comandaModificare)
													{
													case 1:
													{
														string marcaNoua;
														cout << "Introduceti noua marca: ";
														cin >> marcaNoua;
														vehiculNou->setMarca(marcaNoua);
														cout << "\nMarca a fost modificata cu succes.\n";
														break;
													}
													case 2:
													{
														string modelNou;
														cout << "Introduceti noul model: ";
														cin >> modelNou;
														vehiculNou->setModel(modelNou);
														cout << "\nModelul a fost modificat cu succes.\n";
														break;
													}
													case 3:
													{
														int anFabricatieNou;
														cout << "Introduceti noul an de fabricatie: ";
														cin >> anFabricatieNou;
														vehiculNou->setAnFabricatie(anFabricatieNou);
														cout << "\nAnul de fabricatie a fost modificat";
													}
													case 4:
													{
														bool disponibilNou;
														cout << "Introduceti noua disponibilitate (0 - indisponibil, 1 - disponibil): ";
														cin >> disponibilNou;
														vehiculNou->setDisponibil(disponibilNou);
														cout << "\nDisponibilitatea";
													}
													case 5:
													{
														double pretNou;
														cout << "Introduceti noul pret: ";
														cin >> pretNou;
														vehiculNou->setPret(pretNou);
														cout << "\nPretul a fost modificat cu succes.\n";
														break;
													}
													case 6:
													{
														double consumNou;
														cout << "Introduceti noul consum: ";
														cin >> consumNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehiculNou);
														vehiculCarburant->setConsum(consumNou);
														cout << "\nConsumul a fost modificat cu succes.\n";
														break;
													}
													case 7:
													{
														string tipCarburantNou;
														cout << "Introduceti noul tip de carburant: ";
														cin >> tipCarburantNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehiculNou);
														vehiculCarburant->setTipCarburant(tipCarburantNou);
														cout << "\nTipul de carburant a fost modificat cu succes.\n";
														break;
													}
													case 8:
													{
														double autonomieNoua;
														cout << "Introduceti noua autonomie: ";
														cin >> autonomieNoua;
														VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehiculNou);
														vehiculElectric->setAutonomieKm(autonomieNoua);
														cout << "\nAutonomia a fost modificata cu succes.\n";
														break;
													}
													case 9:
													{
														double timpIncarcareNou;
														cout << "Introduceti noul timp de incarcare: ";
														cin >> timpIncarcareNou;
														VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehiculNou);
														vehiculElectric->setTimpIncarcare(timpIncarcareNou);
														cout << "\nTimpul de incarcare a fost modificat cu succes.\n";
														break;
													}
													case 10:
													{
														int introducereCorecta = 0;
														char tipHibridNou;
														cout << "Introduceti noul tip de hibrid (M - Mild Hybrid, F - Full Hybrid, P - Plug-in Hybrid): ";
														while (introducereCorecta == 0)
														{
															cin >> tipHibridNou;
															if (tipHibridNou == 'M' || tipHibridNou == 'F' || tipHibridNou == 'P')
															{
																VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(vehiculNou);
																vehiculHibrid->setTipHibrid(tipHibridNou);
																cout << "\nTipul de hibrid a fost modificat cu succes.\n";
																introducereCorecta = 1;
															}
															else
																cout << "Introduceti una dintre literele M, F sau P.\n" << "> ";
														}
														break;
													}
													case 11:
													{
														iesiDinModificareVehicul = 1;
														okModificare = 1;
														break;
													}

													}
												}
									}
									break;
								}
								case 2: // modificare pret final, avans si credit, cu conditia ca pret final == avans + credit
								{
									cout << "\n Avansul = " << tranzactii[index - 1].getAvans() << " euro\n";
									cout << "\n Creditul = " << tranzactii[index - 1].getCredit() << " euro\n";
									cout << "\n Pretul final = " << tranzactii[index - 1].getPretFinal() << " euro\n";

									int pretFinalCorect = 0;
									while (pretFinalCorect == 0)
									{
										cout << "\n Introduceti noul pret final: ";
										double pretFinalNou;
										cin >> pretFinalNou;
										cout << "\n Introduceti noul avans: ";
										double avansNou;
										cin >> avansNou;
										cout << "\n Introduceti noul credit: ";
										double creditNou;
										cin >> creditNou;
										if (pretFinalNou == avansNou + creditNou)
										{
											tranzactii[index - 1].setPretFinal(pretFinalNou);
											tranzactii[index - 1].setAvans(avansNou);
											tranzactii[index - 1].setCredit(creditNou);
											cout << "\n Pretul final, avansul si creditul au fost modificate cu succes.\n";
											pretFinalCorect = 1;
										}
										else
											cout << "\n Pretul final trebuie sa fie egal cu suma dintre avans si credit.\n";
									}
									break;
								}
								case 3:
								{
									okModificare = 1;
									break;
								}

								}
							}
						}
					}
				}
				case 5:
				{
					ramaiInTranzactie = 0;
					break;
				}

				}
			}
			break;
		}
		case 5:
		{

			int ramaiInProgram = 1;
			while (ramaiInProgram)
			{


				if (clienti.size() == 0)
				{
					cout << "\nNu exista clienti inregistrati, deci nu se poate genera o tranzactie.\n";
					ramaiInProgram = 0;
					break;
				}
				if (showroomuri.size() == 0)
				{
					cout << "\nNu exista showroom-uri inregistrate, deci nu se poate genera o tranzactie.\n";
					ramaiInProgram = 0;
					break;
				}
				int afisatClienti = 0;
				if (afisatClienti == 0)
				{
					afisatClienti = 1;
					cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n\n";
					for (int i = 0; i < clienti.size(); i++)
					{
						cout << "Clientul " << i + 1 << ":" << endl;
						cout << clienti[i];
						cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n\n";
					}
				}
				cout << "Introduceti index-ul clientului pentru care doriti sa generati o tranzactie.\nAveti lista cu clientii mai sus.\n\n" << "> ";
				int indexClient;
				int okCitireIndex = 0;
				while (okCitireIndex == 0)
				{
					cin >> indexClient;
					if (indexClient < 1 || indexClient > clienti.size())
					{
						cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << clienti.size() << "].\n" << "\n> ";
					}
					else
					{
						cout << "\nAti ales clientul " << indexClient << ".\n";
						okCitireIndex = 1;
					}
				}
				cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n";
				int afisatShowroom = 0;
				if (afisatShowroom == 0)
				{
					afisatShowroom = 1;
					for (int i = 0; i < showroomuri.size(); i++)
					{
						cout << "Showroom-ul " << i + 1 << ":" << endl;
						cout << showroomuri[i];
						cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n\n";
					}
				}
				cout << "Ati ales clientul " << indexClient << ".\n\n";
				cout << "Introduceti index-ul showroom-ului din care doriti sa cumparati un vehicul.\nAveti lista cu showroom-uri mai sus.\n\n";
				int indexShowroom;
				int okShowroomGol = 0;
				int okCitireIndexShowroom = 0;
				while (okCitireIndexShowroom == 0)
				{
					cout << "> ";
					cin >> indexShowroom;

					if (indexShowroom < 1 || indexShowroom > showroomuri.size())
					{
						cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri.size() << "].\n" << "\n> ";
					}
					else
						if (showroomuri[indexShowroom - 1].getNrVehiculeDisponibile() == 0)
						{
							cout << "\nShowroom-ul ales nu are vehicule disponibile.\n";
							cout << "\n1. Anulare tranzactie.\n";
							cout << "2. Reintroducere index showroom.\n\n";
							int comandaDisponibilitate;
							cout << "\n> ";
							cin >> comandaDisponibilitate;
							if (comandaDisponibilitate == 1)
							{
								cout << "\nTranzactia a fost anulata.\n";
								ramaiInProgram = 0;
								okShowroomGol = 1;
								break;
							}
						}

						else
						{
							cout << "\nAti ales showroom-ul " << indexShowroom << ".\n";
							okCitireIndexShowroom = 1;
						}
				}
				if (okShowroomGol == 1)
				{
					okShowroomGol = 0;
					break;
				}
				cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n";
				int afisatVehicule = 0;
				if (afisatVehicule == 0)
				{
					afisatVehicule = 1;
					for (int i = 0; i < showroomuri[indexShowroom - 1].getNrVehiculeDisponibile(); i++)
					{
						cout << "Vehiculul " << i + 1 << ":" << endl;
						cout << *showroomuri[indexShowroom - 1].getVehiculeDisponibile()[i];
						cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n\n";
					}
				}
				cout << "Ati ales showroom-ul " << indexShowroom << ".\n\n";
				cout << "Introduceti index-ul vehiculului pe care doriti sa il cumparati.\nAveti lista cu vehiculele din showroom-ul selectat mai sus.\n\n";

				int anulareDinCitireIndexVehicul = 0;
				int indexVehicul;
				int okCitireIndexVehicul = 0;
				while (okCitireIndexVehicul == 0)
				{
					cout << "> ";
					cin >> indexVehicul;
					if (indexVehicul < 1 || indexVehicul > showroomuri[indexShowroom - 1].getNrVehiculeDisponibile())
					{
						cout << "\nIndex invalid.\nTrebuie sa introduceti un index din intervalul [1," << showroomuri[indexShowroom - 1].getNrVehiculeDisponibile() << "].\n" << "\n> ";
					}
					else
						if (showroomuri[indexShowroom - 1].getVehiculeDisponibile()[indexVehicul - 1]->getDisponibil() == 0)
						{
							cout << "\nVehiculul ales nu este disponibil.\n";
							cout << "\n1. Anulare tranzactie.\n";
							cout << "2. Reintroducere index vehicul.\n\n";
							int comandaDisponibilitate;
							cout << "\n> ";
							cin >> comandaDisponibilitate;
							if (comandaDisponibilitate == 1)
							{
								cout << "\nTranzactia a fost anulata.\n";
								anulareDinCitireIndexVehicul = 1;
								break;
							}
						}
						else
						{
							cout << "\nAti ales vehiculul " << indexVehicul << ".\n";
							okCitireIndexVehicul = 1;
						}
				}
				if (anulareDinCitireIndexVehicul == 0)
				{
					cout << "\n\n// ------------------------------------------------------------------------------------------------------------------ //\n\n";
					cout << "Atentie! Pretul final trebuie sa fie egal cu suma dintre avans si credit.\n";
					cout << "Atentie! Suma dintre credit si plata ramasa a clientului nu trebuie sa depaseasca creditul maxim al clientului.\n\n";
					cout << "Pentru referinta, pretul vehiculului la care se adauga automat profitul este de " << showroomuri[indexShowroom - 1].calculPretVehiculCuProfit(showroomuri[indexShowroom - 1].getVehiculeDisponibile()[indexVehicul - 1]) << " euro.\n";
					cout << "Pentru referinta, creditul maxim al clientului este de " << clienti[indexClient - 1].getCreditMaxim() << " euro.\n";
					cout << "Pentru referinta, plata ramasa a clientului este de " << clienti[indexClient - 1].getPlataRamasa() << " euro.\n\n";
					int okPretFinal = 0;
					while (okPretFinal == 0)
					{
						cout << "\nIntroduceti pretul final al vehiculului ales: ";
						double pretFinal;
						cin >> pretFinal;
						cout << "\nIntroduceti avansul: ";
						double avans;
						cin >> avans;
						cout << "\nIntroduceti creditul: ";
						double credit;
						cin >> credit;
						if (credit + clienti[indexClient - 1].getPlataRamasa() > clienti[indexClient - 1].getCreditMaxim())
						{
							cout << "\n\nSuma dintre credit si plata ramasa a clientului depasesc creditul maxim al clientului.";
							cout << "\n\n1. Anulare tranzactie.\n";
							cout << "2. Reintroducere date pentru pret final, avans si credit.\n\n";
							int comandaCredit;
							cout << "\n> ";
							cin >> comandaCredit;
							if (comandaCredit == 1)
							{
								cout << "\nTranzactia a fost anulata.\n";
								break;
							}
						}
						else
							if (credit > clienti[indexClient - 1].getCreditMaxim())
							{
								cout << "\n\nCreditul depaseste creditul maxim al clientului.";
								cout << "\n\n1. Anulare tranzactie.\n";
								cout << "2. Reintroducere date pentru pret final, avans si credit.\n\n";
								int comandaCredit;
								cout << "\n> ";
								cin >> comandaCredit;
								if (comandaCredit == 1)
								{
									cout << "\nTranzactia a fost anulata.\n";
									break;
								}
							}
							else
								if (pretFinal == avans + credit)
								{

									vehiculCumparat = showroomuri[indexShowroom - 1].getVehiculeDisponibile()[indexVehicul - 1]->virtualCopyConstructor(); // copie cu new
									vehiculCumparat->setDisponibil(0); // vehiculul cumparat devine indisponibil

									// mut declararea lui t in afara 

									//Tranzactie t(clienti[indexClient - 1], vehiculCumparat, pretFinal, avans, credit);
									Tranzactie t;
									t.setClient(clienti[indexClient - 1]);
									t.setVehiculCumparat(vehiculCumparat);
									t.setPretFinal(pretFinal);
									t.setAvans(avans);
									t.setCredit(credit);

									tranzactii.push_back(t);

									clienti[indexClient - 1].setPlataRamasa(clienti[indexClient - 1].getPlataRamasa() + credit); // se adauga creditul la plata ramasa a clientului
									clienti[indexClient - 1] = clienti[indexClient - 1] + vehiculCumparat; // atribuire vehiculului clientului in baza de date

									showroomuri[indexShowroom - 1] = showroomuri[indexShowroom - 1] - (indexVehicul - 1); // stergere vehicul din showroom, in plus, operator - face si -- la nrVehiculeDisponibile

									cout << "\nTranzactia a fost generata cu succes.\n";
									cout << "ID Tranzactie: " << tranzactii.back().getIdTranzactie() << ".\n";
									okPretFinal = 1;
									ramaiInProgram = 0;
								}
								else
									cout << "\n\nPretul final trebuie sa fie egal cu suma dintre avans si credit.\n\n";
					}
				}

			}
			break;
		}
		case 6:
		{
			cout << "\nIesirea din program a fost finalizata cu succes. La revedere!\n";
			k = 0;
			break;
		}
		default:
		{
			cout << "\nComanda invalida.\n";
			break;
		}

		break;
		}

	}
	return 0;
}

