#include "stdafx.h"
#include "Film.h"



Film::Film(int volume)
{
	vol = volume;
	rec = false;
}

Film::~Film()
{
	vol = 0;
}

int Film::get_Volume()
{
	return vol;
}

void Film::set_Volume(int volume)
{
	vol = volume;
}

bool Film::get_RStat()
{
	return rec;
}

void Film::set_RStat(bool stat)
{
	rec = stat;
}
