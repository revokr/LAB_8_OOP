#include "domain.h"
#include <vector>
#include <iostream>
#include "exceptie.h"

using std::vector;




class parcare {
private:
	vector<Masina> lista;

public:
	/*
		Constructor implicit
	*/
	parcare() = default;

	Masina curent(int i) {
		Masina m1 = lista.at(i);
		return m1;
	}

	/*
		Adauga o masina in lista
		Parametru : car - obiect masina
	*/
	void adauga(Masina car);

	void add(Masina car);
	/*
		Sterge o masina din lista dupa pozitia in lista
		Parametru : pos - int
	*/
	void sterge(string nr_inm);

	/*
		modifica o masina din lista
	*/
	void modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou);

	/*
		Returneaza dimensiunea listei
	*/

	int cauta(string nr_inm);

	bool cauta_(string nr_inm);

	/*
		Creeaza o lista cu toate masinile din parcare
	*/
	vector<Masina> get_all();

	/*
		Destructor
	*/
	~parcare() = default;


};