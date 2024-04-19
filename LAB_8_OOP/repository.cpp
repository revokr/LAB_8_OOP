#include "repository.h"


vector<Masina> parcare::get_all() {
	return lista;
}

int parcare::cauta(string nr_inm) {
	int i = 0;
	for (auto car : lista) {
		if (car.get_nr() == nr_inm) {
			return i;
		}
		i++;
	}
	return -1;
}

bool parcare::cauta_(string nr_inm) {
	auto f = std::find_if(lista.begin(), lista.end(), [=](Masina& c) {
		return (c.get_nr() == nr_inm);
		});
	if (f != lista.end())
		return true;
	else
		return false;}


void parcare::modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou) {
	try {
		if (cauta_(nr_inm) != false) {
			lista.at(cauta(nr_inm)).set_producator(producator_nou);
			lista.at(cauta(nr_inm)).set_model(model_nou);
			lista.at(cauta(nr_inm)).set_tip(tip_nou);
		}
		else if (cauta_(nr_inm) == false)
			throw parcare_exception("Masina nu exista!!");
	}
	catch (parcare_exception& e) {
		std::cout << e.get_mesaj() << '\n';
		return;}
}

void parcare::sterge(string nr_inm) {
	try {
		if (cauta_(nr_inm) != false)
			lista.erase(lista.begin() + cauta(nr_inm));
		else if (cauta_(nr_inm) == false)
			throw parcare_exception("Masina nu exista!!");
	}
	catch (parcare_exception& e) {
		std::cout << e.get_mesaj() << '\n';
		return;}
}

void parcare::adauga(Masina car) {
	//for (Masina m1 : lista) {
	//	try {
	//		if (car.get_nr() == m1.get_nr())
	//			throw parcare_exception("Nr de inmatriculare existent!!");
	//	}
	//	catch (parcare_exception& e) {
	//		std::cout << e.get_mesaj() << '\n';
	//		return;}
	//}
	lista.push_back(car);
}

void parcare::add(Masina car) {
	lista.push_back(car);
}
