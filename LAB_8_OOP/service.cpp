#include "service.h"
#include <iostream>
#include <algorithm>


using std::cout;


void service::adauga_srv(string nr, string prod, string model, string tip) {
	Masina car{ nr, prod, model, tip };

	if (car.valideaza() == 1) {
		for (Masina m1 : p.get_all()) {
			try {
				if (car.get_nr() == m1.get_nr())
					throw parcare_exception("Nr de inmatriculare existent!!");
			}
			catch (parcare_exception& e) {
				std::cout << e.get_mesaj() << '\n';
				return;		}
		}
		p.adauga(car);
	}

}

void service::adauga_ls(string nr, string prod, string model, string tip) {
	Masina car{ nr, prod, model, tip };
	p.add(car);
}

void service::sterge_srv(string nr_inm) {
	p.sterge(nr_inm);
}

void service::modifica_srv(string nr_inm, string prod_nou, string model_nou, string tip_nou) {
	Masina c(nr_inm, prod_nou, model_nou, tip_nou);
	if (c.valideaza() == 1)
	p.modifica(nr_inm, prod_nou, model_nou, tip_nou);
}

Masina service::cauta_srv(string nr_inm) {
	int pos = p.cauta(nr_inm);
	try {
		if (pos != -1) {
			return p.curent(pos);}
		else {
			throw parcare_exception("Masina nu exista!");
		}
	}
	catch (parcare_exception& e) {
		cout << e.get_mesaj();
		Masina m2{ "", "" , "", "" };
		return m2;}}

vector<Masina> service::filtreaza_p(string prod) {
	vector<Masina> masini = p.get_all();
	vector<Masina> masini_filtrate;
	for (auto car : masini) {
		if (car.get_producator() == prod) {
			masini_filtrate.push_back(car);
		}
	}
	return masini_filtrate;
}

vector<Masina> service::filtreaza_t(string tip) {
	vector<Masina> masini = p.get_all();
	vector<Masina> masini_filtrate;
	for (auto car : masini) {
		if (car.get_tip() == tip) {
			masini_filtrate.push_back(car);
		}
	}
	return masini_filtrate;
}

vector<Masina> service::sorteaza_nr_inm() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b) {return a.get_nr() < b.get_nr(); });
	return masini;
}

vector<Masina> service::sorteaza_prod() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b)
		{return (a.get_producator() < b.get_producator() ||
			(a.get_producator() == b.get_producator() && a.get_model() < b.get_model())); });
	return masini;
}

vector<Masina> service::sorteaza_tip() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b) {return a.get_tip() < b.get_tip(); });
	return masini;
}

vector<Masina> service::get_all_srv() {
	return p.get_all();
}

