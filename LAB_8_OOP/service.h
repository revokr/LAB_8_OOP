#pragma once
#include "repository.h"



class service {

	//friend class parcare;
	//friend class Masina;

private:
	parcare p;
public:
	//explicit service(parcare& repo) :p{ repo }{};
	service(parcare& p) : p{ p } {

	}

	/*
		adauga o masina in lista
		nr : string
		prod : string
		model : string
		tip : string
	*/
	void adauga_srv(string nr, string prod, string model, string tip);

	void adauga_ls(string nr, string prod, string model, string tip);

	/*
	* returneaza toate masinile din lista
	*/
	vector<Masina> get_all_srv();

	/*
	* sterge o masina din lista
	* nr_inm : string
	*/
	void sterge_srv(string nr_inm);

	/*
	* modifica o masina din lista
	* nr_inm : string
	* prod_nou : string
	* model_nou : string
	* tip_nou : string
	*/
	void modifica_srv(string nr_inm, string prod_nou, string model_nou, string tip_nou);

	/*
	* cauta o masina in lista
	* nr_inm : string
	* returneaza masina
	*/
	Masina cauta_srv(string nr_inm);

	/*
	* filtreaza masinile dupa un producator dat
	* prod : string
	* returneaza masinile filtrate
	*/
	vector<Masina> filtreaza_p(string prod);

	/*
	  filtreaza masinile dupa un tip dat
	* prod : string
	* returneaza masinile filtrate
	*/
	vector<Masina> filtreaza_t(string tip);

	/*
		sorteaza dupa numarul de inmatriculare
	*/
	vector<Masina> sorteaza_nr_inm();

	/*
		sorteaza dupa producator si model
	*/
	vector<Masina> sorteaza_prod();

	/*
		sorteaza dupa tip
	*/
	vector<Masina> sorteaza_tip();

	/*
		teste
	*/
	vector<Masina> teste_service();
};