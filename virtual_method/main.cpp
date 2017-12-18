#include <iostream>
using namespace std;

class Mammalia {
public:
    void name() {
        cout << "семейство млекопитающих" << endl;
    }

    virtual void full_name() {
        cout << "млекопитающее";
    }
};

class Carnivora : public Mammalia {
public:
    void name() {
        cout << "отряд хищники" << endl;
    }

    virtual void full_name() {
        Mammalia::full_name();
        cout << " => хищники";
    }
};

class Caniformia : public Carnivora {
public:
    void name() {
        cout << "псообразные" << endl;
    }

    virtual void full_name() {
        Carnivora::full_name();
        cout << " => псообразные";
    }
};

class Feliformia : public Carnivora {
public:
    void name() {
        cout << "кошкообразные" << endl;
    }

    virtual void full_name() {
        Carnivora::full_name();
        cout << " => кошкообразные";
    }
};

class Canidae : public Caniformia {
public:
    void name() {
        cout << "псовые" << endl;
    }

    virtual void full_name() {
        Caniformia::full_name();
        cout << " => псовые";
    }
};

class Procyonidae : public  Caniformia {
public:
    void name() {
        cout << "енотовидные" << endl;
    }

    virtual void full_name() {
        Caniformia::full_name();
        cout << " => енотовидные";
    }
};

class Procyon : public  Procyonidae {
public:
    void name() {
        cout << "еноты" << endl;
    }

    virtual void full_name() {
        Procyonidae::full_name();
        cout << " => еноты";
    }
};

class Procyon_lotor : public  Procyon {
public:
    void name() {
        cout << "енот-полоскун" << endl;
    }

    virtual void full_name() {
        Procyon::full_name();
        cout << " => енот-полоскун";
    }
};
int main(void) {
    Mammalia* animals[] = {
            new Carnivora(),
            new Caniformia(),
            new Feliformia(),
            new Canidae(),
            new Procyonidae(),
            new Procyon(),
            new Procyon_lotor()
    };
    for(int i = 0; i < 7; ++i) {
        cout << i+1 << " animal:" << endl;
        cout << "name is: " << endl;
        animals[i]->name();
        cout << "full name is: " << endl;
        animals[i]->full_name(), cout << endl;
        delete animals[i];
    }
    return 0;
}