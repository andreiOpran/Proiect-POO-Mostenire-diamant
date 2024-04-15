#include <iostream>
using namespace std;
class obj {

public:
    static void met() { cout << "met"; }
};
class interfata {

public:
    virtual void f1() = 0;
    virtual void f1(int) = 0;
    virtual /*int*/ void f2() = 0;
};

class parinte {
protected:
    int a;
public:
    parinte() {
        cout << "\nCD-Parinte\n";
        a = 0;
    }
    parinte(int a) {
        cout << "\nCP-Parinte\n";
        this->a = a;
    }
    parinte(const parinte& p)
    {
        this->a = p.a;
    }
    parinte& operator=(const parinte& p) {

        if (this != &p) {
            cout << this << endl << &this->a;
            this->a = p.a;
        }
        return *this;
    }
    friend void g(parinte&);
    void f() { cout << "ceva"; }
    void f(int a) { cout << "ceva " << a; }
    virtual void fun() { cout << "\nfun parite;\n"; }
    virtual void virt() = 0;
    virtual  ~parinte() {
        cout << "\nDes parinte\n";
    }
};

class copil :public parinte {
public:
    int b;
public:
    //copil():parinte() e.g. copil()
    copil() {
        cout << "\nCD-Copil\n";
        b = 1;
    }
    copil(const copil& c) :parinte(c) {
        this->b = c.b;
    }
    copil& operator=(const copil& c) {
        if (this != &c) {
            cout << this << endl << &this->a << endl << &this->b << endl;
            this->parinte::operator=(c);
            this->b = c.b;
        }
        return *this;
    }
    void f() {
        this->parinte::f(10);
        obj::met();
        cout << "copil ";
    }
    friend void g(copil);

    void fun2() { cout << "\nfun2 copil;\n"; }

    void fun() { cout << "\nfun copil;\n"; }
    virtual ~copil() {
        cout << "\nDes copil\n";
    }

    void metC()const {

        cout << this->b;
    }
    int getA()const { return a; }

    virtual void virt() { cout << "virt;"; };
};

void g(parinte& p) {
    cout << &p << endl;
    cout << p.a;
}
void g(copil p) {
    cout << "\ncopil" << endl;
    cout << p.b;
}

void myf(const copil& p) {
    cout << "\nAna are mere\n";
    p.metC();
}
int main()
{

    //parinte a;
   // a.virt();
    copil b;
    cout << "\n\n----------\n\n";
    b.f();
    cout << endl;
    //a.f(30);
    cout << endl;
    //cout<<&a<<endl;
    //g(a);
    g(b);

    cout << "\n**********\n";
    parinte* p = new copil();//up cast
    cout << "\n********\n";
    //(static_cast<copil*>(p))->fun2();
    p->fun();


    cout << "\n\n----------\n\n";

    myf(b);
    return 0;
}


/*
class base {
public:
    virtual void print() {
        cout << "print base class\n";
    }
    void show() {
        cout << "show base class\n";
    }
};

class derived : public base {
public:
    void print() {
        cout << "print derived class\n";
    }
    void show() {
        cout << "show derived class\n";
    }
};

int main() {
    base* bptr;
    derived d;
    bptr = &d;

    // Apelul funcției virtuale se face la versiunea clasei derivate
    bptr->print(); // Output: print derived class

    // Apelul funcției non-virtuale se face la versiunea clasei de bază
    bptr->show(); // Output: show base class

    return 0;
}
*/