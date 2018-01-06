#pragma once
#include <vector>
#include "Film.h"
using namespace std;
class Disk
{
public:
	Disk();
	~Disk();
	int add_Film(Film flm);
	void del_Film();
	int get_FVolume();
	int test_Empty();
	int clear();
	void set_Vol(int vol);
private:
	int volume;
	vector <Film> lst;
};

