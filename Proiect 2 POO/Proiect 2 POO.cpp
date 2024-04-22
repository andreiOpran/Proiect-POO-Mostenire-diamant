#include <cstring>
#include <iostream>
#include <string>
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
	virtual ~Vehicul() {} // cand distrug un new VehiculDerivat() sa se distruga complet

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
	// double indiceVechime = pow(0.90, vechime); // in fiecare an scade cu 10%, si ramane in (0,1)
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
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)

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
	// double indiceVechime = pow(0.90, vechime); // in fiecare an scade cu 10%, si ramane in (0,1)
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
	cost += (20000 / 100) * consum * costCarburant;
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
	istream& citireVehicul(istream& in) override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)
	ostream& afisareVehicul(ostream& out) const override; // virtuale ca sa pot apela cu pointeri la clasa de baza (?)

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
	// double indiceVechime = pow(0.90, vechime); // in fiecare an scade cu 10%, si ramane in (0,1)
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

// FUNCTIE VALOAREA REALA VEHICUL
double VehiculHibrid::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	// double indiceVechime = pow(0.90, vechime); // in fiecare an scade cu 10%, si ramane in (0,1)
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
	cost += (20000 / 100) * consum * costCarburant;
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
	double calculCreditScore(); // plataRamasa / creditMaxim

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

	// SETTER CREDIT MAXIM
	void setCreditMaxim(double);
};

// CONSTRUCTOR FARA PARAMETRI
Client::Client() : nume("Anonim"), nrVehiculeCumparate(0), vehiculeCumparate(), plataRamasa(0), creditMaxim(0) {}

// CONSTRUCTOR CU PARAMETRI
Client::Client(string nume, int nrVehiculeCumparate, vector<Vehicul*> vehiculeCumparate, double plataRamasa, double creditMaxim) : nume(nume), nrVehiculeCumparate(nrVehiculeCumparate), vehiculeCumparate(vehiculeCumparate), plataRamasa(plataRamasa), creditMaxim(creditMaxim) {}

// COPY CONSTRUCTOR
Client::Client(const Client& obj) : nume(obj.nume), plataRamasa(obj.plataRamasa), creditMaxim(obj.creditMaxim)
{
	// deep copy

	for (int i = 0; i < this->nrVehiculeCumparate; i++) // eliberare memorie this
	{
		delete this->vehiculeCumparate[i];
	}
	this->vehiculeCumparate.clear();

	this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
	for (int i = 0; i < this->nrVehiculeCumparate; i++)
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
		for (int i = 0; i < this->nrVehiculeCumparate; i++) // eliberare memorie this
		{
			delete this->vehiculeCumparate[i];
		}
		this->vehiculeCumparate.clear();

		this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
		for (int i = 0; i < this->nrVehiculeCumparate; i++)
		{
			this->vehiculeCumparate.push_back(obj.vehiculeCumparate[i]->virtualCopyConstructor());
		}
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
		cout << "\nCe tip de motor are vehiculul " << i + 1 << "?\nIntroduceti litera corespunzatoare: C - Carburant, E - Electric, H - Hibrid." << endl << "> ";
		in >> tipMotor;
		cout << endl;
		if (tipMotor == 'C')
		{
			Vehicul/*Carburant*/* v = new VehiculCarburant();
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
			Vehicul/*Electric*/* v = new VehiculElectric();
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
			Vehicul/*Hibrid*/* v = new VehiculHibrid();
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
	if (obj.nrVehiculeCumparate)
		out << "Vehicule cumparate:\n\n" << endl;
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		out << "Vehiculul " << i + 1 << ":" << endl;
		out << *obj.vehiculeCumparate[i] << endl;
	}
	out << "\nPlata ramasa: " << obj.plataRamasa << endl;
	out << "Credit maxim: " << obj.creditMaxim << endl << endl;
	return out;
}

// FUNCTIE CALCULARE CREDIT SCORE
double Client::calculCreditScore()
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
int Client::getNrVehiculeCumparate() const { return nrVehiculeCumparate; }

// GETTER VEHICULE CUMPARATE
vector<Vehicul*> Client::getVehiculeCumparate() const { return vehiculeCumparate; }

// SETTER PLATA RAMASA
void Client::setPlataRamasa(double plataRamasa) { this->plataRamasa = plataRamasa; }

// SETTER CREDIT MAXIM
void Client::setCreditMaxim(double creditMaxim) { this->creditMaxim = creditMaxim; }


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
};

// CONSTRUCTOR FARA PARAMETRI
Showroom::Showroom() : numeShowroom("Nedefinit"), adresa("Nedefinita"), nrVehiculeDisponibile(0), vehiculeDisponibile() {}

// CONSTRUCTOR CU PARAMETRI
Showroom::Showroom(string numeShowroom, string adresa, int nrVehiculeDisponibile, vector<Vehicul*> vehiculeDisponibile) : numeShowroom(numeShowroom), adresa(adresa), nrVehiculeDisponibile(nrVehiculeDisponibile), vehiculeDisponibile(vehiculeDisponibile) {}

// COPY CONSTRUCTOR
Showroom::Showroom(const Showroom& obj) : numeShowroom(obj.numeShowroom), adresa(obj.adresa)
{
	//deep copy

	for (int i = 0; i < this->nrVehiculeDisponibile; i++) // stergere this
	{
		delete this->vehiculeDisponibile[i];
	}
	this->vehiculeDisponibile.clear();

	this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
	for (int i = 0; i < this->nrVehiculeDisponibile; i++)
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

		for (int i = 0; i < this->nrVehiculeDisponibile; i++) // stergere this
		{
			delete this->vehiculeDisponibile[i];
		}
		this->vehiculeDisponibile.clear();

		this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
		for (int i = 0; i < this->nrVehiculeDisponibile; i++)
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
			Vehicul/*Carburant*/* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'E')
		{
			Vehicul/*Electric*/* v = new VehiculElectric();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else if (tipMotor == 'H')
		{
			Vehicul/*Hibrid*/* v = new VehiculHibrid();
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
	if (obj.nrVehiculeDisponibile)
	{
		out << "Vehicule disponibile:\n" << endl;
		for (int i = 0; i < obj.nrVehiculeDisponibile; i++)
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
};

// CONSTRUCTOR FARA PARAMETRI
Tranzactie::Tranzactie() : idTranzactie(++nrTranzactii + 100000), client(), vehiculCumparat(), pretFinal(0), avans(0), credit(0) {}

// CONSTRUCTOR CU PARAMETRI
Tranzactie::Tranzactie(Client client, Vehicul* vehiculCumparat, double pretFinal, double avans, double credit) : idTranzactie(++nrTranzactii + 100000), client(client), vehiculCumparat(vehiculCumparat), pretFinal(pretFinal), avans(avans), credit(credit) {}

// COPY CONSTRUCTOR
Tranzactie::Tranzactie(const Tranzactie& obj) : idTranzactie(obj.idTranzactie), client(obj.client), pretFinal(obj.pretFinal), avans(obj.avans), credit(obj.credit)
{
	vehiculCumparat = obj.vehiculCumparat->virtualCopyConstructor();
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
	delete vehiculCumparat;
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
		Vehicul/*Carburant*/* v = new VehiculCarburant();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else if (tipMotor == 'E')
	{
		Vehicul/*Electric*/* v = new VehiculElectric();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else if (tipMotor == 'H')
	{
		Vehicul/*Hibrid*/* v = new VehiculHibrid();
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
	out << "\nTranzactia cu id-ul " << obj.idTranzactie << ":\n\n";
	out << "Clientul care face tranzactia:\n" << obj.client;
	out << "Vehiculul cumparat:\n" << *obj.vehiculCumparat;
	out << "Pret final: " << obj.pretFinal << endl;
	out << "Avans: " << obj.avans << endl;
	out << "Credit: " << obj.credit << endl;
	return out;
}

// GETTER ID TRANZACTIE
int Tranzactie::getIdTranzactie() const { return idTranzactie; }

int Tranzactie::nrTranzactii = 0;

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

	Client AndreiPopescu("Andrei Popescu", 2, { daciaLogan, daciaSpring }, 0, 20000);
	Client AlexIonescu("Alex Ionescu", 1, { daciaJogger }, 0, 30000);
	clienti.push_back(AndreiPopescu);
	clienti.push_back(AlexIonescu);


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
			cout << "Dealer auto\n";
			cout << endl;
			okAfisareEndlInceput = false;
		}
		cout << "1. Intrare in submeniul Modele de vehicule\n";
		cout << "2. Intrare in submeniul Clienti\n";
		cout << "3. Intrare in submeniul Showroom\n";
		cout << "4. Intrare in submeniul Tranzactii\n";
		cout << "\n5. Iesire din program\n";
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
								if (typeid(*vehicule[index - 1]) == typeid(VehiculCarburant))
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
										// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
										double consumNou;
										cout << "Introduceti noul consum: ";
										cin >> consumNou;
										VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]); // VERIFICARE
										vehiculCarburant->setConsum(consumNou);
										//vehicule[index - 1]->setConsum(consumNou);
										cout << "\nConsumul a fost modificat cu succes.\n";
										break;
									}
									case 7:
									{
										// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
										string tipCarburantNou;
										cout << "Introduceti noul tip de carburant: ";
										cin >> tipCarburantNou;
										VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]); // VERIFICARE
										vehiculCarburant->setTipCarburant(tipCarburantNou);
										//vehicule[index - 1]->setTipCarburant(tipCarburantNou);
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
											// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
											double autonomieNoua;
											cout << "Introduceti noua autonomie: ";
											cin >> autonomieNoua;
											VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]); // VERIFICARE
											vehiculElectric->setAutonomieKm(autonomieNoua);
											//vehicule[index - 1]->setAutonomieKm(autonomieNoua);
											cout << "\nAutonomia a fost modificata cu succes.\n";
											break;
										}
										case 7:
										{
											// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
											double timpIncarcareNou;
											cout << "Introduceti noul timp de incarcare: ";
											cin >> timpIncarcareNou;
											VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]); // VERIFICARE
											vehiculElectric->setTimpIncarcare(timpIncarcareNou);
											//vehicule[index - 1]->setTimpIncarcare(timpIncarcareNou);
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
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]); // VERIFICARE
												vehiculCarburant->setConsum(consumNou);
												//vehicule[index - 1]->setConsum(consumNou);
												cout << "\nConsumul a fost modificat cu succes.\n";
												break;
											}
											case 7:
											{
												string tipCarburantNou;
												cout << "Introduceti noul tip de carburant: ";
												cin >> tipCarburantNou;
												VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(vehicule[index - 1]); // VERIFICARE
												vehiculCarburant->setTipCarburant(tipCarburantNou);
												//vehicule[index - 1]->setTipCarburant(tipCarburantNou);
												cout << "\nTipul de carburant a fost modificat cu succes.\n";
												break;
											}
											case 8:
											{
												double autonomieNoua;
												cout << "Introduceti noua autonomie: ";
												cin >> autonomieNoua;
												VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]); // VERIFICARE
												vehiculElectric->setAutonomieKm(autonomieNoua);
												//vehicule[index - 1]->setAutonomieKm(autonomieNoua);
												cout << "\nAutonomia a fost modificata cu succes.\n";
												break;
											}
											case 9:
											{
												double timpIncarcareNou;
												cout << "Introduceti noul timp de incarcare: ";
												cin >> timpIncarcareNou;
												VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(vehicule[index - 1]); // VERIFICARE
												vehiculElectric->setTimpIncarcare(timpIncarcareNou);
												//vehicule[index - 1]->setTimpIncarcare(timpIncarcareNou);
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
														VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(vehicule[index - 1]); // VERIFICARE
														vehiculHibrid->setTipHibrid(tipHibridNou);
														//vehicule[index - 1]->setTipHibrid(tipHibridNou);
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
							cout << "Clientul " << i + 1 << ":" << endl;
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
														// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
														double consumNou;
														cout << "Introduceti noul consum: ";
														cin >> consumNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
														vehiculCarburant->setConsum(consumNou);
														//vehicule[index - 1]->setConsum(consumNou);
														cout << "\nConsumul a fost modificat cu succes.\n";
														break;
													}
													case 7:
													{
														// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
														string tipCarburantNou;
														cout << "Introduceti noul tip de carburant: ";
														cin >> tipCarburantNou;
														VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
														vehiculCarburant->setTipCarburant(tipCarburantNou);
														//vehicule[index - 1]->setTipCarburant(tipCarburantNou);
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
															// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
															double autonomieNoua;
															cout << "Introduceti noua autonomie: ";
															cin >> autonomieNoua;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
															vehiculElectric->setAutonomieKm(autonomieNoua);
															//vehicule[index - 1]->setAutonomieKm(autonomieNoua);
															cout << "\nAutonomia a fost modificata cu succes.\n";
															break;
														}
														case 7:
														{
															// FUNCTIA EXISTA DOAR IN CLASA DERIVATA, DECI TREBUIE CAST
															double timpIncarcareNou;
															cout << "Introduceti noul timp de incarcare: ";
															cin >> timpIncarcareNou;
															VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
															vehiculElectric->setTimpIncarcare(timpIncarcareNou);
															//vehicule[index - 1]->setTimpIncarcare(timpIncarcareNou);
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
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
																vehiculCarburant->setConsum(consumNou);
																//vehicule[index - 1]->setConsum(consumNou);
																cout << "\nConsumul a fost modificat cu succes.\n";
																break;
															}
															case 7:
															{
																string tipCarburantNou;
																cout << "Introduceti noul tip de carburant: ";
																cin >> tipCarburantNou;
																VehiculCarburant* vehiculCarburant = dynamic_cast<VehiculCarburant*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
																vehiculCarburant->setTipCarburant(tipCarburantNou);
																//vehicule[index - 1]->setTipCarburant(tipCarburantNou);
																cout << "\nTipul de carburant a fost modificat cu succes.\n";
																break;
															}
															case 8:
															{
																double autonomieNoua;
																cout << "Introduceti noua autonomie: ";
																cin >> autonomieNoua;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
																vehiculElectric->setAutonomieKm(autonomieNoua);
																//vehicule[index - 1]->setAutonomieKm(autonomieNoua);
																cout << "\nAutonomia a fost modificata cu succes.\n";
																break;
															}
															case 9:
															{
																double timpIncarcareNou;
																cout << "Introduceti noul timp de incarcare: ";
																cin >> timpIncarcareNou;
																VehiculElectric* vehiculElectric = dynamic_cast<VehiculElectric*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
																vehiculElectric->setTimpIncarcare(timpIncarcareNou);
																//vehicule[index - 1]->setTimpIncarcare(timpIncarcareNou);
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
																		VehiculHibrid* vehiculHibrid = dynamic_cast<VehiculHibrid*>(clienti[index - 1].getVehiculeCumparate()[indexVehicul - 1]); // VERIFICARE
																		vehiculHibrid->setTipHibrid(tipHibridNou);
																		//vehicule[index - 1]->setTipHibrid(tipHibridNou);
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
						cout << "\nCreditul maxim al clientului " << clienti[index - 1].getNume() << " este de " << clienti[index - 1].calculCreditScore() << " euro.\n";
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
		}
		case 3:
		{

		}

		}
	}
	return 0;
}
