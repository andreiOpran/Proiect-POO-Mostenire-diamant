#include <iostream>
#include<cstring>
using namespace std;
class Produs
{
protected: // ca sa mearga fct din public din ProdusPerisabil
	string numeProdus;
	float pretBrut;
	const int id;
	static int nrProduse;
public:
	//constructor
	Produs(string, float);
	//constructor fara parametri
	Produs();
	//copy constructor
	Produs(const Produs&);
	//supraincarcare =
	Produs& operator=(const Produs&);
	//citire
	friend ostream& operator<<(ostream&, const Produs&);
	// afisare
	friend istream& operator>>(istream&, Produs&);
};

class ProdusPerisabil :public Produs
{
private:
	string dataExp;

public:
	void f()
	{
		cout << this->numeProdus;
	}

	//ProdusPerisabil()/*:id(contor)*/ // corect dpdv strctural, dar gresit dpdv al poo-ului, pt ca avem constrctor si la Produs - prima data se cheama constructorul pt Produs si dupa se adauga ce are ProdusPerisabil
	//{
	//	// daca nu chem un constructor in mostenire, copilul cheama automat un constrcutor fara parametri din parinte IMPORTANT
	//	this->numeProdus = "Anonim";
	//	this->pretBrut = 20;
	//	this->dataExp = "dd/mm/yyyy";
	//}

	ProdusPerisabil() :Produs()
	{
		this->dataExp = "dd/mm/yyyy";
	}

	ProdusPerisabil(string numeProdus, float pretBrut, string dataExp) : Produs(numeProdus, pretBrut)
	{
		this->dataExp = dataExp;
	}

	ProdusPerisabil(const ProdusPerisabil& obj) :Produs(obj) // daca nu se pune :... se apeleaza constructorul fara parametri din Produs si se dau valori default, se va face un upcasting
	{
		this->dataExp = obj.dataExp;
	}
};

//cosntructor
Produs::Produs(string, float) : id(++nrProduse), pretBrut(pretBrut) {}
// constrctor fara parametri
Produs::Produs() : id(++nrProduse)
{
	numeProdus = "Nedefinit";
	pretBrut = 0;
}
// copy constrcuctor
Produs::Produs(const Produs& obj) : id(++nrProduse), numeProdus(obj.numeProdus), pretBrut(obj.pretBrut) {}
// supraincarcare =
Produs& Produs::operator=(const Produs& obj)
{
	if (this != &obj)
	{
		this->numeProdus = obj.numeProdus;
		this->pretBrut = obj.pretBrut;
	}
	return *this;
}
// afisare
ostream& operator<<(ostream& out, const Produs& obj)
{
	out << "Nume produs: " << obj.numeProdus << endl;
	out << "Pret brut: " << obj.pretBrut << endl;
	out << "ID: " << obj.id << endl;
	out << "Nr. produse: " << obj.nrProduse << endl;
	return out;
}
// citire
istream& operator>>(istream& in, Produs& obj)
{
	cout << "Nume produs: ";
	in >> obj.numeProdus;
	cout << "Pret brut: ";
	in >> obj.pretBrut;
	/*cout << "ID: ";
	cout << "Nr. produse: ";*/
	return in;
}
int Produs::nrProduse = 0;
int main()
{
	Produs p1;

	ProdusPerisabil pp;
	//pp.setNume("paine");
	cout << pp;
	return 0;
}
// pt data viitoare class ProdusNeperisabil cu "int aniGarantie"

// colocviu -> mostenire diamant == 90% sanse