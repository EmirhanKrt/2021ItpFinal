//////////////////////////////////////////
// Emirhan KURT
// 1306190028
// Date: 2021.05.24
// IDE: Visual Studio 2019
///////////////////////////////////////////
//
// Projede dosya işlemlerini kolaylaştırmak için
// C++17 sürümü kullanılmıştır. (<filesystem> kütüphanesi için) 
// Kaynak: canturna.com/cpp-dosya-sistemi-yonetimi-filesystem/
//
//////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem> 
#include <map>

using namespace std;
using namespace std::filesystem;

/* GLOBAL DEĞİŞKENLER - MAPS */
map<int, int> operasyonhiz;

map<int, int> operasyonlargecis;
map< map<int, int>, int> operasyonlargecissure;

/* GLOBAL DEĞİŞKENLER - INT */
int satirsayisi=0, aktifsatirsayisi=0,toplamsure=0, oncekioperasyonkodu=0,donmesayisi=0;

/* GLOBAL DEĞİŞKENLER - OFSTREAM */
ofstream outfile("Schedule.txt");

void operasyonkoduhiztanim(string);
void islemaktarimsureleri(string);
void siparistanimla(string);
void surehesap(int, int, int, int, int);

void operasyonkoduhiztanim(string satir) {
	char satirkarakterler[100];
	string operasyonkodu="", hiz="";
	int intoperasyonkodu=0, inthiz = 0;
	strcpy_s(satirkarakterler, satir.c_str()); 
	for (int i = 0; i < 100; i++) {
		if (satirkarakterler[i] == ';') {
			for (int a = 0; a < i; a++) {
				operasyonkodu += satirkarakterler[a];
			}
			for (int a = i+1; a < satir.size(); a++) {
				if(satirkarakterler[a]!= ' ')
				hiz += satirkarakterler[a];
			}
		}
	}
	intoperasyonkodu = stoi(operasyonkodu);
	inthiz = stoi(hiz);
	operasyonhiz.insert({ intoperasyonkodu ,inthiz }); 
}

void islemaktarimsureleri(string satir) {
	char satirkarakterler[100];
	string sol = "", sag = "", sure = "";
	int operasyonkodusol = 0, intsure = 0, operasyonkodusag = 0, oncekivirgul = 0, ilkdon = 0;
	strcpy_s(satirkarakterler, satir.c_str());
	for (int i = 0; i < 100; i++) {
		if (satirkarakterler[i] == ';') {
			if (ilkdon == 0) {
				ilkdon++;
				oncekivirgul = i;
				for (int j = 0; j < i; j++) {
					if (satirkarakterler[j] != ' ')
						sol += satirkarakterler[j];
				}
			}
			else {
				for (int j = oncekivirgul + 1; j < i; j++) {
					if (satirkarakterler[j] != ' ')
						sag += satirkarakterler[j];
				}
				for (int j = i + 1; j < satir.size(); j++) {
					if (satirkarakterler[j] != ' ')
						sure += satirkarakterler[j];
				}
			}
		}
	}
	operasyonkodusol = stoi(sol); operasyonkodusag = stoi(sag);	intsure = stoi(sure);

	operasyonlargecis.insert({ operasyonkodusol, operasyonkodusag });
	operasyonlargecissure.insert({ operasyonlargecis,intsure });

	operasyonlargecis.clear();

}

void siparistanimla(string satir) {
	char satirkarakterler[100];
	string siparisnumarasi ="",isinuzunlugu = "", operasyonno = "", deadline = "";
	int siparisnumarasiint = 0, operasyonnoint = 0, deadlineint = 0, oncekivirgul = 0, ilkdon = 0, isinuzunluguint = 0;
	strcpy_s(satirkarakterler, satir.c_str());
	for (int i = 0; i < 100; i++) {
		if (satirkarakterler[i] == ';') {
			if (ilkdon == 0) {
				ilkdon++;
				oncekivirgul = i;
				for (int j = 0; j < i; j++) {
					if (satirkarakterler[j] != ' ')
						siparisnumarasi += satirkarakterler[j];
				}
			}
			else {
				if(ilkdon==1){
					ilkdon++;
					for (int j = oncekivirgul + 1; j < i; j++) {
						if (satirkarakterler[j] != ' ')
							isinuzunlugu += satirkarakterler[j];
					}
					oncekivirgul = i;
				}else{
					for (int j = oncekivirgul + 1; j < i; j++) {
						if (satirkarakterler[j] != ' ')
							operasyonno += satirkarakterler[j];
					}
					for (int j = i + 1; j < satir.size(); j++) {
						if (satirkarakterler[j] != ' ')
							deadline += satirkarakterler[j];
					}
				}
			}
		}
	}
	siparisnumarasiint = stoi(siparisnumarasi); isinuzunluguint = stoi(isinuzunlugu); operasyonnoint = stoi(operasyonno); deadlineint = stoi(deadline);

	donmesayisi++;
	surehesap(operasyonnoint, siparisnumarasiint, isinuzunluguint, deadlineint, donmesayisi);
}

void surehesap(int operasyonnoint,int siparisnumarasiint,int isinuzunluguint,int deadlineint,int donmesayisi) {
	double bolum=0;
	int gecissuresi = 0;
	int intbolum = 0,ilkdon=0, tekdon=0;

	if (donmesayisi == 1)
		outfile << toplamsure << "; " << operasyonnoint << "; " << siparisnumarasiint << "; " << isinuzunluguint << "; " << gecissuresi;

	for (auto mapIt = begin(operasyonhiz); mapIt != end(operasyonhiz); ++mapIt) {
		if (mapIt->first == operasyonnoint) {
			//cout <<" operasyonno: " << mapIt->first<<" toplamis: "<<isinuzunluguint<< " hiz: "<<mapIt->second;
			if (isinuzunluguint % mapIt->second == 0) {
				intbolum = isinuzunluguint / mapIt->second;
			}
			else {
				bolum = isinuzunluguint / mapIt->second;
				intbolum = (int)round(bolum)+1;
			}
			if (oncekioperasyonkodu != 0) {
				for (auto mapIt2 = begin(operasyonlargecissure); mapIt2 != end(operasyonlargecissure); ++mapIt2) {
					for (auto mapIt3 = begin(mapIt2->first); mapIt3 != end(mapIt2->first); ++mapIt3) {
						if (mapIt3->first == oncekioperasyonkodu && mapIt3->second == operasyonnoint) {
							gecissuresi = mapIt2->second;
							//cout << " gecissuresi: " << gecissuresi << " ";
						}
						else if (mapIt3->first == operasyonnoint && mapIt3->second == oncekioperasyonkodu) {
							gecissuresi = mapIt2->second;
							//cout << " gecissuresi: " << gecissuresi << " ";
						}
						else if (operasyonnoint == oncekioperasyonkodu) {
							if(tekdon==0){
								tekdon++;
								gecissuresi = 0;
								//cout << " gecissuresi: " << gecissuresi << " ";
							}
						}
					}
				}
			}
		}
	}
	//cout << endl;
	toplamsure += gecissuresi;

	if (donmesayisi != 1)
		outfile << toplamsure << "; " << operasyonnoint << "; " << siparisnumarasiint << "; " << isinuzunluguint << "; "<< gecissuresi;

	toplamsure += intbolum;

	outfile << endl;

	oncekioperasyonkodu = operasyonnoint;
}

int main()
{
	int ilkdonus = 0;
	try {
		path p(".\\");
		for (const directory_entry& dre : directory_iterator(p))
		{
			if (!is_directory(dre))
			{
				if (dre.path().extension() == ".txt")
				{
					if (ilkdonus == 0) {
						ilkdonus++;
						ifstream operations("Operations.txt");
						if (operations.is_open()) {
							string line;
							while (getline(operations, line)) {
								size_t operatortanim = line.find(";");
								if (operatortanim != string::npos)
								operasyonkoduhiztanim(line);
							}
						}
						operations.close();
					}
					if (ilkdonus == 1) {
						ilkdonus++;
						ifstream SetupDurationfirst("SetupDuration.txt");
						if (SetupDurationfirst.is_open()) {
							string line;
							while (getline(SetupDurationfirst, line)) {
								satirsayisi++;
							}
						}
					}
					if (ilkdonus == 2) {
						ilkdonus++;
						ifstream SetupDuration("SetupDuration.txt");
						if (SetupDuration.is_open()) {
							string line;
							while (getline(SetupDuration, line)) {
								aktifsatirsayisi++;
								size_t islemaktarimi = line.find(";");
								if (islemaktarimi != string::npos)
									islemaktarimsureleri(line);
							}
						}
						SetupDuration.close();
					}
					if (ilkdonus == 3) {
						ilkdonus++;
						ifstream Orders("Orders.txt");
						if (Orders.is_open()) {
							string line;
							while (getline(Orders, line)) {
								size_t siparisler = line.find(";");
								if (siparisler != string::npos)
									siparistanimla(line);
							}
						}
						Orders.close();
					}
				}
			}
		}
		ilkdonus = 0;
	}
	catch (const filesystem_error& ex)
	{
		//cout << ex.what() << endl;
	}
}
