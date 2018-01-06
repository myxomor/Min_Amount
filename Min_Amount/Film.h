#pragma once
class Film
{
public:
	Film(int volume);
	~Film();
	int get_Volume();
	void set_Volume(int vol);
	bool get_RStat();
	void set_RStat(bool stat);
private:
	int vol;
	bool rec;

};

