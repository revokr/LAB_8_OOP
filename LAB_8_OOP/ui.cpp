#include "ui.h"
#include "valueDTO.h"
#include <chrono>
#include <fstream>
#include <random>
#include <map>
using std::cout;
using std::cin;

void UI::meniu() {
	cout << "\\\\ adauga : adauga o noua masina\n";
	cout << "\\\\ sterge : sterge o masina\n";
	cout << "\\\\ modifica : modifica o masina\n";
	cout << "\\\\ cauta : cauta o masina\n";
	cout << "\\\\ flt_p : filtreaza dupa producator\n";
	cout << "\\\\ flt_t : filtreaza dupa tip\n";
	cout << "\\\\ sort_nr : sorteaza dupa nr_inmatriculare\n";
	cout << "\\\\ sort_prod : sorteaza dupa producator\n";
	cout << "\\\\ sort_tip : sorteaza dupa tip\n";
	cout << "\\\\ report : afiseaza report dupa tip\n";
	cout << "\\\\ print : afiseaza toate masinile\n\n";
	cout << "\\\\    lst : deschide meniul de optiuni pentru lista de lucru\n\n";

}

void UI::print_ui(vector<Masina> vct) {
	for (auto masina : vct) {
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
	}
	cout << '\n';
}

void UI::modifica_ui(string nr) {
	string producator;
	string model;
	string tip;
	cout << "\nproducator: ";
	cin >> producator;
	cout << "\nmodel: ";
	cin >> model;
	cout << "\ntip: ";
	cin >> tip;
	srv.modifica_srv(nr, producator, model, tip);
}

void UI::cauta_ui() {
	string nr_inmatriculare;
	cout << "nr_inmatriculare: ";
	cin >> nr_inmatriculare;
	Masina m = srv.cauta_srv(nr_inmatriculare);
	cout << m.get_nr() << " " << m.get_producator() << " " << m.get_model() << " " << m.get_tip() << "\n";
}

void UI::adauga_ui() {
	string nr_inmatriculare;
	string producator;
	string model;
	string tip;
	cout << "\nnr_inmatriculare: ";
	cin >> nr_inmatriculare;
	cout << "\nproducator: ";
	cin >> producator;
	cout << "\nmodel: ";
	cin >> model;
	cout << "\ntip: ";
	cin >> tip;
	srv.adauga_srv(nr_inmatriculare, producator, model, tip);
}

void UI::filtreaza_p_ui() {
	string producator;
	cout << "producator: ";
	cin >> producator;
	vector<Masina> masini = srv.filtreaza_p(producator);
	for (auto masina : masini) {
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
	}
}

void UI::filtreaza_t_ui() {
	string tip;
	cout << "tip: ";
	cin >> tip;
	vector<Masina> masini = srv.filtreaza_t(tip);
	for (auto masina : masini) {
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
	}
}

void UI::sorteaza_nr_inm_ui() {
	vector<Masina> masini = srv.sorteaza_nr_inm();
	for (auto masina : masini) {
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
	}
}

void UI::sorteaza_prod_ui() {
	vector<Masina> masini = srv.sorteaza_prod();
	for (auto masina : masini) {
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
	}
}

void UI::sorteaza_tip_ui() {
	vector<Masina> masini = srv.sorteaza_tip();
	for (auto masina : masini)
		cout << masina.get_nr() << " " << masina.get_producator() << " " << masina.get_model() << " " << masina.get_tip() << "\n";
}

void UI::report_type() {
	std::map<string, valueDTO> mp;
	vector<Masina> masini = srv.sorteaza_tip();
	for (auto car : masini) {
		if (mp.find(car.get_tip()) == mp.end()) {
			valueDTO v{ car.get_tip(), 1 };
			mp[car.get_tip()] = v;
		}
		else {
			mp[car.get_tip()].inc_value();
		}
	}
	for (auto str : mp) {
		cout << str.second.get_type() << " " << str.second.get_value();
		cout << std::endl;
	}
}

void UI::goleste_lst() {
	for (auto masina : lst.get_all_srv()) {
		lst.sterge_srv(masina.get_nr());
	}
}

void UI::adauga_lst(string nr) {
	Masina car = srv.cauta_srv(nr);
	lst.adauga_ls(car.get_nr(), car.get_producator(), car.get_model(), car.get_tip());
}

void UI::gnr_random(int nr) {
	goleste_lst();
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	vector<Masina> v = srv.get_all_srv();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
	int i = 1;
	if (nr > v.size()) {
		while (lst.get_all_srv().size() < nr){
			for (auto car : v)
				if (lst.get_all_srv().size() < nr) {
					adauga_lst(car.get_nr());
				}
				else
					break;
		}
	}
	else {
		for (auto el : v) {
			lst.adauga_srv(el.get_nr(), el.get_producator(), el.get_model(), el.get_tip());
			if (i == nr)
				break;
			i++;
		}
	}
}

void UI::write_to_file() {
	string nume;
	cout << "Alege numele fisierului :";
	cin >> nume;
	std::ofstream out(nume);
	try {
		if (out.is_open()) {
			for (auto car : lst.get_all_srv()) {
				out << car.get_nr() << " " << car.get_producator() << " " << car.get_model() << " " << car.get_tip();
				out << std::endl;
			}
		}
		else {
			throw parcare_exception("Fisierul nu s-a deschis!!\n");
		}
	}
	catch (parcare_exception& e) {
		cout << e.get_mesaj() << '\n';
	}
}


void UI::lst_run() {
	system("cls");
	cout << "\\\\ adauga : adauga o noua masina\n";
	cout << "\\\\ gol : goleste toate masinile din lista\n";
	cout << "\\\\ print : afiseaza toate masinile din lista\n";
	cout << "\\\\ gnr_rndm : adauga un nr de masini random\n";
	cout << "Nr total masini lista : " << lst.get_all_srv().size() << "\n";
	while (true) {
		string com;
		cout << ">>>";
		cin >> com;
		//cout << "\n";
		if (com == "adauga") {
			print_ui(srv.get_all_srv());
			cout << "Alege un numar de inmatriculare existent\n";
			string nr;
			cin >> nr;
			adauga_lst(nr);
			cout << "Nr total masini lista : " << lst.get_all_srv().size() << "\n";
		}
		if (com == "gol") {
			goleste_lst();
			cout << "Nr total masini lista : " << lst.get_all_srv().size() << "\n";
		}
		if (com == "print")
			print_ui(lst.get_all_srv());
		if (com == "gnr_rndm") {
			int nr;
			cout << "alege nr de masini :";
			cin >> nr;
			gnr_random(nr);
			cout << "Nr total masini lista : " << lst.get_all_srv().size() << "\n";
		}
		if (com == "x") {
			write_to_file();
			goleste_lst();
			break;
		}
	}
}


void UI::run() {
	srv.adauga_srv("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	srv.adauga_srv("CJ90CBV", "BMW", "S1000RR", "SporT");
	srv.adauga_srv("CJ98JHV", "BMW", "A1000R", "Sport");
	srv.adauga_srv("BC12KJF", "Ducati", "AA", "Naked");
	srv.adauga_srv("SV12ASF", "Honda", "FireBlade", "Sport");
	srv.adauga_srv("VS23DAF", "Toyota", "Corola", "Sedan");
	srv.adauga_srv("VS23UYD", "Dacia", "MCV", "Break");
	srv.adauga_srv("CT23AZD", "Dacia", "Logan", "Br");
	system("cls");
	meniu();
	while (true) {
		string com;
		cout << ">>>";
		cin >> com;
		cout << "\n";
		if (com == "x")
			break;
		if (com == "adauga") {
			adauga_ui();
		}
		if (com == "sterge") {
			sterge_ui();
		}
		if (com == "modifica") {
			string nr;
			cout << "Alege nr de inmatriculare : ";
			cin >> nr;
			modifica_ui(nr);
		}
		if (com == "cauta") {
			cauta_ui();
		}
		if (com == "print") {
			print_ui(srv.get_all_srv());
		}
		if (com == "flt_p") {
			filtreaza_p_ui();
		}
		if (com == "flt_t") {
			filtreaza_t_ui();
		}
		if (com == "sort_nr"){
			sorteaza_nr_inm_ui();
		}
		if (com == "sort_prod"){
			sorteaza_prod_ui();
		}
		if (com == "sort_tip"){
			sorteaza_tip_ui();
		}
		if (com == "report"){
			report_type();
		}
		if (com == "lst") {
			lst_run();
			system("cls");
			meniu();
		}
	}
}



void UI::sterge_ui() {
	string nr_inm;
	cout << "Alege nr de inmatriculare : ";
	cin >> nr_inm;
	srv.sterge_srv(nr_inm);
}
