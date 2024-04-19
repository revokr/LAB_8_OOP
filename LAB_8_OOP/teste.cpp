#include "service.h"
#include <assert.h>


void teste_repo() {
	parcare p1;
	Masina m1("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	p1.adauga(m1);
	assert(p1.get_all().size() == 1);
	assert(p1.curent(0).get_nr() == m1.get_nr());
	assert(p1.cauta("BC06DSK") == 0);
	assert(p1.cauta("BC06asDSK") == -1);
	//p1.adauga(m1);
	assert(p1.get_all().size() == 1);
	p1.modifica("BC06DSKas", "Ducati", "Panigale_V2", "Sport");
	p1.sterge("BC06asDSK");
	p1.sterge("BC06DSK");
	assert(p1.get_all().size() == 0);

	Masina car("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	p1.adauga(car);
	assert(p1.cauta_(car.get_nr()) == true);
}


void teste_service() {
	parcare repo;
	service srv(repo);
	Masina m1("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	srv.adauga_srv("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	assert(srv.get_all_srv().size() == 1);
	srv.sterge_srv("BC06DSK");
	assert(srv.get_all_srv().size() == 0);
	srv.adauga_srv("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	assert(srv.get_all_srv().size() == 1);


	srv.modifica_srv("BC06DSK", "Ducati", "Panigale_V2", "Sport");
	assert(srv.get_all_srv().size() == 1);
	assert(srv.cauta_srv("BC06DSK").get_nr() == "BC06DSK");
	srv.cauta_srv("asd");

	vector<Masina> flt = srv.filtreaza_p("Ducati");
	assert(flt.size() == 1);

	vector<Masina> flt2 = srv.filtreaza_t("Sport");
	assert(flt2.size() == 1);

	srv.adauga_srv("BC21GHH", "BMW", "S1000RR", "Sport");
	srv.adauga_srv("BC21GHH", "BMW", "S1000RR", "Sport");
	srv.adauga_srv("CJ98JHV", "BMW", "A1000R", "Sport");
	assert(srv.get_all_srv().size() == 3);

	vector<Masina> sort = srv.sorteaza_nr_inm();
	assert(sort.at(0).get_nr() == "BC06DSK");

	vector<Masina> sort2 = srv.sorteaza_prod();
	assert(sort2.at(0).get_producator() == "BMW");

	vector<Masina> sort3 = srv.sorteaza_tip();
	assert(sort3.at(0).get_tip() == "Sport");
	srv.adauga_ls("CJ9das8JHV", "BMW", "A1000R", "Sport");
}


void teste_masina() {
	Masina m1("BC06DSK", "Ducati", "Panigale_V4", "Sport");
	assert(m1.get_nr() == "BC06DSK");
	assert(m1.get_producator() == "Ducati");
	assert(m1.get_model() == "Panigale_V4");
	assert(m1.get_tip() == "Sport");
	assert(m1.valideaza() == 1);
	m1.set_nr("asd");
	assert(m1.get_nr() == "asd");
	m1.set_producator("das");
	assert(m1.get_producator() == "das");
	m1.set_model("aasd");
	assert(m1.get_model() == "aasd");
	m1.set_tip("assd");
	assert(m1.get_tip() == "assd");

	Masina m21("BC06DSK", "Ducati", "Panigale_V4", "");
	assert(m21.valideaza() == 0);

	Masina dacia(m1);

	assert(dacia.get_nr() == "asd");
}


void test_all() {
	teste_masina();
	teste_repo();
	teste_service();
}