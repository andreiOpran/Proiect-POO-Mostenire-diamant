#include <iostream>
#include<cstring>
#include<vector>
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

	virtual float calculeazaPret() = 0; // metoda virtuala pura, =0 inseamna ca nu ii definesti body ul
	virtual ~Produs() {};

	// o interfata contine doar metode virtuale pure
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


	//L8
	ProdusPerisabil operator=(const ProdusPerisabil& obj)
	{
		if (this != &obj)
		{
			/*this->numeProdus = obj.numeProdus;     //varianta proasta
			this->pretBrut = obj.pretBrut;*/ 

			Produs::operator=(obj); // upcasting -- varianta buna, se cheama this automat, apelatul este this
			this->dataExp = obj.dataExp;
		}
		return *this;
	}

	friend istream& operator>>(istream& in, ProdusPerisabil& obj)
	{
		// nu dam copypaste
		// in >> obj // loop infinit de upcasting
		cout << "Produs: ";
		in >> (Produs&)obj;
		cout << "Data expirare: ";
		in >> obj.dataExp;
		return in;
	}
	friend ostream& operator<<(ostream& out, const ProdusPerisabil& obj)
	{
		out << (Produs&)obj;
		out << obj.dataExp;
		return out;
	}
	
	float calculeazaPret()
	{
		return /*Produs::calculeazaPret()*/pretBrut; // am facut o p aia virtuala
	}
};

class ProdusNeperisabil :public Produs
{
private:
	string aniGarantie;

public:
	void f()
	{
		cout << this->numeProdus;
	}

	//ProdusNeperisabil()/*:id(contor)*/ // corect dpdv strctural, dar gresit dpdv al poo-ului, pt ca avem constrctor si la Produs - prima data se cheama constructorul pt Produs si dupa se adauga ce are ProdusNeperisabil
	//{
	//	// daca nu chem un constructor in mostenire, copilul cheama automat un constrcutor fara parametri din parinte IMPORTANT
	//	this->numeProdus = "Anonim";
	//	this->pretBrut = 20;
	//	this->aniGarantie = "dd/mm/yyyy";
	//}

	ProdusNeperisabil() :Produs()
	{
		this->aniGarantie = "dd/mm/yyyy";
	}

	ProdusNeperisabil(string numeProdus, float pretBrut, string aniGarantie) : Produs(numeProdus, pretBrut)
	{
		this->aniGarantie = aniGarantie;
	}

	ProdusNeperisabil(const ProdusNeperisabil& obj) :Produs(obj) // daca nu se pune :... se apeleaza constructorul fara parametri din Produs si se dau valori default, se va face un upcasting
	{
		this->aniGarantie = obj.aniGarantie;
	}


	//L8
	ProdusNeperisabil operator=(const ProdusNeperisabil& obj)
	{
		if (this != &obj)
		{
			/*this->numeProdus = obj.numeProdus;     //varianta proasta
			this->pretBrut = obj.pretBrut;*/

			Produs::operator=(obj); // upcasting -- varianta buna, se cheama this automat, apelatul este this
			this->aniGarantie = obj.aniGarantie;
		}
		return *this;
	}

	friend istream& operator>>(istream& in, ProdusNeperisabil& obj)
	{
		// nu dam copypaste
		// in >> obj // loop infinit de upcasting
		cout << "Produs: ";
		in >> (Produs&)obj;
		cout << "Data expirare: ";
		in >> obj.aniGarantie;
		return in;
	}
	friend ostream& operator<<(ostream& out, const ProdusNeperisabil& obj)
	{
		out << (Produs&)obj;
		out << obj.aniGarantie;
		return out;
	}

	float calculeazaPret()
	{
		//if (aniGarantie < 6)
		//	pretBrut *= 1.5;
		return /*Produs::calculeazaPret()*/ pretBrut; // am facut o virtuala pe aia
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


	// in loc de liniile de sus
	// return obj.citire(in);
	
	return in;
}
int Produs::nrProduse = 0;
int main()
{
	vector<Produs*> produse;// * -> nu creez obiecte, creez adrese
	int k = 1;
	while (k)
	{
		cout << "1. Produs perisabil" << endl;
		cout << "2. Produs neperisabil" << endl;
		cout << "3. Afisare produse" << endl;
		cout << "4. Afisare suma totala a preturilor" << endl;
		cout << "5. Exit";
		int val;
		cin >> val;
		switch (val)
		{
		case 1:
		{
			//ProdusPerisabil  p;
			//cin >> p;
			////produse.push_back(&p); // nu merge ca o sa se stearga dupa ce iese din case
			
			
			Produs*  p = new ProdusPerisabil;

			cin >>static_cast<ProdusPerisabil&>(*p); // downcasting
			produse.push_back(p); // p este pointer
			break;
		}
		case 2:
		{
			Produs* p = new ProdusNeperisabil;
			cin >> *p;
			produse.push_back(p); // p este pointer
			break;
		}
		case 3:
		{
			for (int i = 0; i < produse.size(); i++)
				if (typeid(ProdusPerisabil) == typeid(*produse[i])) // ca sa afiseze corect tipul de produs
					cout << static_cast<ProdusPerisabil&>(*produse[i]) << endl; 
				else
					cout << static_cast<ProdusNeperisabil&>(*produse[i]) << endl;
			break;
		}
		case 4:
		{
			float s = 0;
			for (int i = 0; i < produse.size(); i++)
				s = s + produse[i]->calculeazaPret();
			cout << s;
			break;
		}
		case 5:
		{
			k = 0;
			break;
		}
		break;
		}
	}
	return 0;
}


// mostenire diamant in proiect doar daca o stapanesti 100% altfel pierzi puncte