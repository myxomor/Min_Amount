// Min_Amount.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>


using namespace std;
vector <Film> films;
vector <Disk> dsk;
vector <Disk> dsk_opt;
vector <Film> workF;
int lvl = 0;
int test;
int o_disk = 10;
int disk;
const int16_t c_films = 12;	//количество фильмов в выборке
//const double D = 1.2;

void Percentage(vector <Disk> search, int cnt) 
{
	string out="";
	std::stringstream str;
	for (int i = 0; i < cnt; i++)
	{
	/*	str << ((dsk[i].get_FVolume())/700);
		out = out + str.str() + '%';
		*/
		cout << ((search[i].get_FVolume())*100/700) << '%' << endl;
	}

	//cout << out;
}

int PercentageT(vector <Disk> search, int cnt)
{
	int p;
	int t=0;
	for (int i = 0; i < cnt; i++)
	{
		p = ((search[i].get_FVolume()) * 100 / 700);
		cout << p << '%' << endl;
		if (p<=20)
		{
			t++;
		}
	}
	return t;
}

void CreateRandBD()
{
	ofstream BD("db.txt");
	for	(int g = 0; g < 10; g++)
	{
		for (int i = 0; i < c_films; i++)
		{
			films.push_back(Film(rand() % 700));
			BD << films[i].get_Volume() << endl;
			cout << "#" << i << " " << films[i].get_Volume() << endl;
		}
		films.clear();
	}
	BD.close();
}

void OpenBD()
{
	ifstream BD("db.txt");
	int vol;
	for	(int g = 0; g < 10; g++)
	{
		for (int i = 0; i < c_films; i++)
		{
			BD >> vol;
			films.push_back(Film(vol));
			cout << "#" << i << " " << films[i].get_Volume() << endl;
		}
		films.clear();
	}
	BD.close();
	//return 0;

}

/*void BF(vector <Film> flms)
{
	int opt_disk = 10;
	int disks = 0;
	int t = 10;
//	int repeat = 0;
	for (int i = 0; i < 10; i++)							//для одного набора фильмов в workBF g=1
	{
		for (int e = 0; e < 10; e++)
		{
			workF[e].set_Volume(flms[e].get_Volume());
		}
		for (int q = 0; q < t; q++)
		{
			if (i > q)
			{
				int temp = workF[i].get_Volume();
				workF[i].set_Volume(workF[q].get_Volume());
				workF[q].set_Volume(temp);
				//cout << "change film #" << i << endl;
			}
			for (int n = 0; n < 10; n++)
			{
				int test;
				for (int d = 0; d < 10; d++)
				{
					test = dsk[d].add_Film(workF[n]);
					if (test == 0) break;

				}
				//cout << "film #"<< n << " write on disk#" << d << endl;
			}
			for (int n = 0; n < 10; n++)
			{
				if (dsk[n].test_Empty() != 0) {
					disks++;
					//cout << "Count data #" << n << endl;
				}
			}
			//cout << "Needed disks: " << disks << endl;
			//repeat++;
			if (disks <= opt_disk)
			{
				opt_disk = disks;
			}
			disks = 0;
			//dsk.clear();
			for (int j = 0; j < 10; j++)
			{
				dsk[j].clear();
				//cout << "create disk #" << j << endl;
			}

		}
		t--;
	}
	cout << "min amount of disks: " << opt_disk << endl;
	for (int j = 0; j < 10; j++)
	{
		dsk[j].clear();
		//cout << "create disk #" << j << endl;
	}
}*/

void BF(int lvl)
{
	if (lvl == c_films)
	{
		disk = 0;
		for (int n = 0; n < c_films; n++)
		{
			if (dsk[n].test_Empty() != 0) {
				disk++;
			}
		}
		//cout << "needed disks: " << disk << endl;
		if (o_disk>disk)
		{
			//dsk_opt = dsk;
			o_disk = disk;
			for (int i = 0; i < c_films; i++)
			{
				dsk_opt[i] = Disk();
				dsk_opt[i] = dsk[i];

			}
		}
		return;
	}
/*	if (lvl==0)
	{
		dsk[0].add_Film(films[lvl]);
		lvl++;
		BF(lvl);
		lvl--;
	}*/
	for (int i = 0; i < c_films; i++)
	{
		test = dsk[i].add_Film(films[lvl]);
		if (test==0)
		{
			lvl++;
			BF(lvl);
			lvl--;
			dsk[i].del_Film();
		}
	}
	//cout << "lvl" << lvl << endl;
}
	
void WorkBF()
{
	for (int j = 0; j < c_films; j++)
	{
		dsk.push_back(Disk());
		films.push_back(Film(0));
		workF.push_back(Film(0));
		//cout << "create disk #" << j << endl;
	}
	films.push_back(Film(0));
	ifstream BD("db.txt");
	int vol;
	for (int g = 0; g < 10; g++)	//количество выборок
	{
		for (int h = 0; h < c_films; h++)
		{
			BD >> vol;
			//films.push_back(Film(vol));
			films[h].set_Volume(vol);
		}
		for (int q = 0; q < c_films; q++)
		{
			cout << "viborka: " << q << endl;
			BF(lvl);
			for (int i = 0; i < c_films; i++)
			{
				if (i == 0)
				{
					films[c_films].set_Volume(films[0].get_Volume());
					films[i].set_Volume(films[i + 1].get_Volume());
				}
				else
				{
					films[i].set_Volume(films[i + 1].get_Volume());
				}
				dsk[i].clear();
			}
		}
		Percentage(dsk_opt,o_disk);
		cout << "optimal disks: " << o_disk << endl;
		ofstream OUT("BF.txt");
		OUT << o_disk << endl;
		OUT.close();
		//films.clear();
		for (int j = 0; j < c_films; j++)
		{
			dsk[j].clear();
		}
		o_disk = 10;
		disk = 0;
		lvl = 0;
	}
	BD.close();
}

void RS(vector <Film> flms)
{
	int opt_disksR = c_films;
	for (int c = 0; c < 1000; c++)
	{
		int t = 0;
		int disksR = 0;
		do
		{
			int i = rand() % c_films;
			//cout << "number" << i << endl;
			if (flms[i].get_RStat() == false)
			{
				int test;
				for (int d = 0; d < c_films; d++)
				{
					test = dsk[d].add_Film(flms[i]);
					//cout << test << endl;
					if (test == 0)
					{
						flms[i].set_RStat(true);
						t++;
						//cout << "yes" << endl;
						break;
					}
				}
			}
		} while (t != c_films);
		//cout << "cirle# " << c << endl;
		for (int n = 0; n < c_films; n++)
		{
			if (dsk[n].test_Empty() != 0) {
				disksR++;
				//cout << "Count data #" << n << endl;
			}
		}
		if (opt_disksR>disksR)
		{
			opt_disksR = disksR;
			dsk_opt = dsk;
		}
		//cout << "needed disks: " << disksR << endl;
		for (int j = 0; j < c_films; j++)
		{
			dsk[j].clear();
			flms[j].set_RStat(false);
		}
	}
	Percentage(dsk_opt, opt_disksR);
	cout << "optimal count: " << opt_disksR << endl;
	ofstream OUTRS("RS.txt");
	OUTRS << opt_disksR << endl;
	OUTRS.close();
	for (int j = 0; j < c_films; j++)
	{
		dsk[j].clear();
	}
}

void WorkRS() 
{
	for (int j = 0; j < c_films; j++)
	{
		dsk.push_back(Disk());
		//dsk_opt.push_back(Disk());
		films.push_back(Film(0));
		workF.push_back(Film(0));
		//cout << "create disk #" << j << endl;
	}
	ifstream BD("db.txt");
	int vol;
	for (int g = 0; g < 10; g++)  //колтчество выборок
	{
		for (int h = 0; h < c_films; h++)
		{
			BD >> vol;
			films[h].set_Volume(vol);
		}
		RS(films);
	}
	BD.close();
}

void GM(vector <Film> flms) 
{
	int disksR = 0;
	int t = 0;
	int test;
	int buf;
	bool recT;
	for (int i = 0; i < c_films; i++)
	{
		flms[i].set_RStat(false);
		int min = i;
		for (int q = i+1; q < c_films; q++)
		{
			if (flms[q].get_Volume()<flms[min].get_Volume())
			{
				buf = flms[min].get_Volume();
				flms[min].set_Volume(flms[q].get_Volume());
				flms[q].set_Volume(buf);
			}
		}
	}
	int d = 0;
	do
	{
		for (int f = c_films-1; f >= 0; f--)
		{
			recT = flms[f].get_RStat();
			if (recT == false)
			{
				test = dsk[d].add_Film(flms[f]);
				if (test == 0)
				{
					flms[f].set_RStat(true);
					t++;
				}
			}
		}
		d++;
		//cout << d << endl;
	} while (t!= c_films);
	for (int n = 0; n < c_films; n++)
	{
		if (dsk[n].test_Empty() != 0) {
			disksR++;
			//cout << "Count data #" << n << endl;
		}
	}
	Percentage(dsk, disksR);
	cout << "Needed disks: " << disksR << endl;
	ofstream OUTGM("GM.txt");
	OUTGM << disksR << endl;
	OUTGM.close();
	for (int j = 0; j < c_films; j++)
	{
		dsk[j].clear();
	}
}

void WorkGM() 
{
	for (int j = 0; j < c_films; j++)
	{
		dsk.push_back(Disk());
		films.push_back(Film(0));
	}
	ifstream BD("db.txt");
	int vol;
	for (int g = 0; g < 10; g++)
	{
		for (int h = 0; h < c_films; h++)
		{
			BD >> vol;
			films[h].set_Volume(vol);
		}
		GM(films);
	}
	BD.close();
}

int WR(vector <Film> flms, double t) 
{
	double D;
	vector <long double> F;
	double minF;
	double R;
	int cnt;
	int disksR;
	int opt_disksR = 10;
	D = t;
	int result;
	for (int w = 0; w < 10; w++)
	{
		F.push_back(0);
		//cout << "w " << w << endl;
	}
	for (int c = 0; c < 1000; c++)
	{
		disksR = 0;
		int FV = 0;
		int DV = 0;
		int temp;
		for (int i = 0; i < 10; i++)
		{
			FV = flms[i].get_Volume();
			//minF = 701 * (1 + 2 * D*0.5);
			minF = 0;
			cnt = 0;
			for (int q = 0; q < 10; q++)
			{
				DV = dsk[q].get_FVolume();
				if (DV > FV)
				{
					R = rand() % 100;
					F[q] = DV*(1 + 2 *D*(R / 100 - 0.5));
					if (minF<F[q])
					{
						minF = F[q];
						cnt = q;
					}
				}
				else
				{
					continue;
				}
			}
		//	cout << "F=" << F[cnt] << endl;
			temp = dsk[cnt].add_Film(flms[i]);
		}
		for (int n = 0; n < 10; n++)
		{
			if (dsk[n].test_Empty() != 0) {
				disksR++;
			}
		}
		if (opt_disksR>disksR)
		{
			opt_disksR = disksR;
			dsk_opt = dsk;
			/*for (int pp = 0; pp < 10; pp++)
			{
				dsk_opt[pp] = Disk();
				dsk_opt[pp] = dsk[pp];
			}*/
		}
		for (int j = 0; j < 10; j++)
		{
			dsk[j].clear();
			flms[j].set_RStat(false);
		}
		//cout << "new it" << endl;
	}
	//result = PercentageT(dsk_opt, opt_disksR);
	cout << "optimal count: " << opt_disksR << endl;
	for (int j = 0; j < 10; j++)
	{
		dsk[j].clear();
		dsk_opt[j].clear();
	}
	result = opt_disksR;
	return result;
};

void WorkWR() 
{
	for (int j = 0; j < 10; j++)
	{
		dsk.push_back(Disk());
		films.push_back(Film(0));
	//	workF.push_back(Film(0));
		//cout << "create disk #" << j << endl;
	}
	ifstream BD("test.txt");
	int vol;
	for (int g = 0; g < 1; g++)
	{
		for (int h = 0; h < 10; h++)
		{
			BD >> vol;
			films[h].set_Volume(vol);
			cout << vol << endl;
		}
		//WR(films);		
	}
	BD.close();

};

void test_intel()
{
	int answ;
	int c = 0;
	for (int j = 0; j < 10; j++)
	{
		dsk.push_back(Disk());
		films.push_back(Film(0));
		//	workF.push_back(Film(0));
		//cout << "create disk #" << j << endl;
	}
	ifstream BD("test.txt");
	int vol;
		for (int h = 0; h < 10; h++)
		{
			BD >> vol;
			films[h].set_Volume(vol);
			cout << vol << endl;
		}
		BD.close();
		ofstream OUT("stat.txt");
		double iter = 0.000;
		do
		{
			answ = WR(films, iter);
			iter += 0.01;
			OUT << answ << endl;
			c++;
			cout << "done " << iter << endl;
		} while (c!=200);
		OUT.close();
}

int main()
{
	int i;
	for (int wi = 0; wi < 10; wi++)
	{
		dsk_opt.push_back(Disk());
	}
	do
	{
		cout << "Your action" << endl;
		cout << "1 - create BD" << endl;
		cout << "2 - view BD" << endl;
		cout << "3 - work BF" << endl;
		cout << "4 - work RS" << endl;
		cout << "5 - work GM" << endl;
		cout << "6 - work WR" << endl;
		cout << "10 - intel_test" << endl;
		cout << "7 - exit" << endl;
		cin >> i;

		if (i == 1) {
			CreateRandBD();
		}
		if (i == 2) {
			OpenBD();
		}
		if (i == 3) {
			WorkBF();
		}
		if (i == 4) {
			WorkRS();
		}
		if (i == 5) {
			WorkGM();
		}
		if (i == 6) {
			WorkWR();
		}
		if (i == 10) {
			test_intel();
		}
	}
	while (i!=7);
		
	return 0;

}




