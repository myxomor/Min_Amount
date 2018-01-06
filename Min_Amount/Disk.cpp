#include "stdafx.h"
#include "Disk.h"
#include "Film.h"
#include <iostream>


Disk::Disk()
{
	vector <Film> lst;
	volume = 700;
}


Disk::~Disk()
{
	volume = 700;
	lst.clear();
}

int Disk::add_Film(Film flm)
{
	int flm_vol = flm.get_Volume();
	if (volume > flm_vol)
	{
		lst.push_back(flm);
		volume = volume - flm_vol;
		//cout << "yes" << volume << endl;
		return 0;
	}
	else
	{
		//cout << "no" << endl;
		return -1;
	}
}

void Disk::del_Film()
{
	int s = lst.size();
	int fVol;
	fVol = lst[s - 1].get_Volume();
	volume = volume + fVol;
	lst.pop_back();
}

int Disk::get_FVolume()
{
	return volume;
}

int Disk::test_Empty()
{
	int count = 0;
	if (lst.size()>0)
	{
		count = 1;
	}
	return count;
}

int Disk::clear()
{
	volume = 700;
	lst.clear();
	return 0;
}

void Disk::set_Vol(int vol)
{
	volume = vol;
}
