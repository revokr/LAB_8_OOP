#include <string>

using std::string;

class valueDTO {
private:
	string type;
	int value;
public:
	
	valueDTO() = default;

	valueDTO(string st, int t) : type{ st }, value{ t } {}

	void operator=(const valueDTO& ot) {
		this->type = ot.type;
		this->value = ot.value;
	}

	string get_type() {
		return this->type;
	}

	int get_value() {
		return this->value;
	}

	void set_type(string t) {
		this->type = t;
	}

	void set_value(int v) {
		this->value = v;
	}

	void inc_value() {
		this->value++;
	}

};