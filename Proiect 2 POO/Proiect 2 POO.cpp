#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Vehicul {

protected:
    string marca;
	string model;
	int anFabricatie;
	bool disponibil;
	double pret;

public:
	
	Vehicul()
	{
		cout << endl << "Constructor Vehicul" << endl;
	}
	~Vehicul()
	{
		cout << endl << "Destructor Vehicul" << endl;
	}
};

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
	VehiculHibrid obj;
    return 0;
}
