//////////////////////////////////////////
//  Emirhan KURT
//  1306190028
//  Date: 2021.05.12
//  IDE: Visual Studio 2019
///////////////////////////////////////////
//
//  Projede dosya işlemlerini kolaylaştırmak için C++17 sürümü kullanılmıştır. (<filesystem> kütüphanesi için) 
//  Kaynak: canturna.com/cpp-dosya-sistemi-yonetimi-filesystem/
//
//	Projede ilk olarak dosyanın kaç satırlı olduğunu hesaplamak için dosya açık kaldığı sürece while loop ile satirsayisi değişkenini arttırıyorum. (Bu aşamada verileri işlemeye almıyorum.)
//  Bu satirsayisi değişkenini input dosyasındaki verileri işlerken son satıra geldiğimi ve çıktı vermem gerektiğini if döngüsü ile kontrol etmek için kullanıyorum.
//	
//	Bir dahaki while döngüsü içerisinde ise verileri işlemeye başlıyorum ve aktifsatirsayisi değişkeni ile kaçıncı satırda olduğumu hesaplıyorum. Sırasıyla yaptığım adımlar:
//
//  1-Satırın içerisinde virgül olup olmadığını kontrol ediyorum. Eğer varsa virgüller arasını parselleyen fonksiyonumu çağırıyorum ve parsellediğim string ifadeleri nodeler mapına atıyorum.
//
//	2-Node tanımlama işlemim bittiği zaman nodenin gidebileceği yerleri kontrol ediyorum. Eğer satır içerisinde "->" ifadesi varsa linktanımla(string) fonksiyonumu çağırıyorum ve "->" ifadesinin
//  sağ ve sol kısmını parselleyerek multimap<string, string> sagsolnodeler multimapıma gönderiyorum.
//
//	3-Yolları tanımlama işlemim bittiği zaman "Paths:" satırını bulup yololusturkontrol fonksiyonum ile yolları oluşturmaya başlıyorum. Bu fonksiyon içerisinde for(auto&p:solsagnodeler) döngüsü ile
//	soldakiler vectörümün içerisindeki sol düğümleri ve o string ifadeye karşılık gelen sağdaki düğümleri multimap <string, vector<string>> yolhafiza içerisine atıyorum. Ve "Paths:" ifadesinin kaçıncı
//	satır olduğunu kontrol2 değişkenine aktarıyorum. Bir sornaki adımda kontrol2 değişkenimi kullanacağım.
//
//	4-Yolhafiza multimapimi oluşturduktan sonra eğer satır içerisinde "Paths:", ",", "->", "Links:" string ifadelerini bulmazsa (mesela AAB satırına geldiği zaman) yolkontrol(line, satirsayisi - kontrol2) 
//  fonksiyonumu çağırıyorum. Bu fonksiyon çağırılan fonksiyonu parsellemekle görevli ve bu parsellediği karakterleri paths vektörümün içerisine char olarak atıyorum. Eğer (fonksiyonun dönme sayısı)==(satirsayisi - kontrol2)
//  ise en son aşama olan kontrol yapısı olan yol fonksiyonunu çağırıyorum. 
//
//	5-yol() fonksiyonum ile gelen paths dizimin içerisinde önce soldaki düğümün soldakiler içerisinde olup olmadığını kontrol ediyorum eğer yoksa o paths için cevap [NO] oluyor. Eğer varsa bu sefer sağdaki düğümümü yolhafiza içerisinde
//  soldaki düğüm ve sağdaki düğüm uyuşuyorsa işlem devam ediyor eğer uyuşmuyorsa işlem bitiyor ve o satır için cevap gene [NO] çıkıyor. Bu sürekli tekrarlanıyor ve eğer bu işlemin tekrarlanma sayısı o satırın boyutundan 1 eksik ise [YES]
//	çıktısı alıyorum. Bu işlemin sonucuna göre bool vectörüm olan ft nin içerisine 1 veya 0 girdileri veriyorum.
//
//	6- Aktifsatirsayisi==satirsayisi olduğu zaman output.txt dosyasını yazmaya başlıyorum ve paths[i][j] ile o satırın tam halini yazıyorum. ft vektörüm ile paths vektörümün i indexi aynı satırdan bahsettiği için ft[i] == true ise yazıkont
//  adlı değişkenimi true yapıyorum değilse else yapıyorum. Eğer yazıkont true ise [YES] yazılıyor değilse [NO] yazılıyor.
//
//
//
//  Global değişken kullanmanın diğer yazılım dillerinde pek sağlıklı olmadığını öğrendim fakat global değişken kullanmadan yaptığım zaman işin içinden çıkamadım. Kendimi bu konuda geliştireceğim.
//
//
//
//	
//	Okuduğunuz için teşekkür ederim. Sağlıklı günler dilerim.
//	
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
#include <regex>

using namespace std;
using namespace std::filesystem;

/* GLOBAL DEĞİŞKENLER - MAPS */
map<string, int> nodeler;
multimap <string, string> solsagnodeler;
multimap <string, vector<string>> yolhafiza;

/* GLOBAL DEĞİŞKENLER - VECTORLER */
vector <vector<string>> gidebildigiyer;
vector <string> soldakiler;
vector <vector<char>> paths;
vector <bool>ft(10);

/* GLOBAL DEĞİŞKENLER - INT */
int donmesayisi = 0;
int satirsayisi = 0;
int enazbiryol = 0;

void yololusturkontrol() {
	vector <string> sagdakiler;
	int ilkkez{ 0 };
	for (auto& p : solsagnodeler) {
		vector<string>::iterator it;
		it = find(soldakiler.begin(), soldakiler.end(), p.first);
		if (it == soldakiler.end()) {
			if (ilkkez != 0) {
				gidebildigiyer.push_back(sagdakiler);
			}
			ilkkez++;
			sagdakiler.clear();
			soldakiler.push_back(p.first);
			sagdakiler.push_back(p.second);
			if (ilkkez == solsagnodeler.size()) {
				gidebildigiyer.push_back(sagdakiler);
			}
		}
		else {
			ilkkez++;
			sagdakiler.push_back(p.second);
		}
	}
	for (int i = 0; i < gidebildigiyer.size(); i++)
	{
		for (int j = 0; j < 1; j++)
		{
			yolhafiza.insert({ soldakiler[i],gidebildigiyer[i] });
		}
	}
}

void nodetanimla(string line) {
	int ilkkezdonus = 0, ilkvirgulkonum = 0, nodesayisi = 0;
	char satirkarakterler[100];
	string solkisim = "", sagkisim = "";
	size_t sonvirgul = line.find_last_of(",");
	strcpy_s(satirkarakterler, line.c_str());
	for (int i = 0; i < 100; i++) {
		if (satirkarakterler[i] == ',') {
			for (int a = ilkvirgulkonum; a < i; a++) {
				solkisim += satirkarakterler[a];
			}
			ilkvirgulkonum = i + 1;
			//cout << solkisim << " ";
			nodeler.insert({ solkisim,nodesayisi });
			nodesayisi++;
		}
		solkisim = "";
	}
	for (int i = 0; i < 100; i++) {
		if (ilkkezdonus == 0) {
			ilkkezdonus++;
			for (int a = sonvirgul + 1; a < line.size(); a++) {
				sagkisim += satirkarakterler[a];
			}
			//cout << sagkisim << " ";
			nodeler.insert({ sagkisim,nodesayisi });
		}
		sagkisim = "";
	}
}

void linktanimlat(string line) {
	char satirkarakterler[100];
	strcpy_s(satirkarakterler, line.c_str());
	string solkisim = "", sagkisim = "";
	for (int i = 0; i < 100; i++) {
		if (satirkarakterler[i] == '-' && satirkarakterler[i + 1] == '>') {
			for (int c = 0; c < i; c++) {
				solkisim += satirkarakterler[c];
			}
			for (int c = i + 2; c < line.size(); c++) {
				sagkisim += satirkarakterler[c];
			}
			//cout << solkisim << "->" << sagkisim << endl;
			solsagnodeler.insert({ solkisim, sagkisim });
		}
	}
}

void yol() {
	string kon = "",kon2="",kon3="",kon4="", sag = "", sol = "", oncekisol="";
	bool kontrolet{ false };
	int ilkkez = 0, donme = 0, donme1 = 0,index=0;
	vector<int>kontrol;
	vector<vector<int>>kontroller;
	for (int i = 0; i < paths.size(); i++) {
		kontrol.push_back(1);
		for (int j = 0; j < paths[i].size(); j++) {
			for (int h = 0; h < 1; h++) {
				if (j != paths[i].size() - 1 && paths[i][j] != NULL) {
					if (j == paths[i].size() - 2) {
						sag = paths[i][j];
					}
					if (j == 0) {
						oncekisol = paths[i][j];
						kon4+= paths[i][j];
					}
					else
					{
						donme1++;
						sol = paths[i][j];
						kon4 += paths[i][j];
						if (donme1 < paths[i].size() - 1) {
							for (auto mapIt = begin(yolhafiza); mapIt != end(yolhafiza); ++mapIt)
							{
								size_t solda;
								if (ilkkez == 0)
									solda = mapIt->first.find(oncekisol);
								else
									solda = mapIt->first.find(kon);

								//cout << ilkkez <<" " <<paths[i].size()<<" " ;
								if (solda != string::npos && ilkkez <= paths[i].size()) {
									ilkkez++;
									//soldakini degiskenler icinde bulursa
									for (auto c : mapIt->second)
									{
										size_t sagda = c.find(sol);
										if (sagda != string::npos) {
											for (auto& p : soldakiler) {
												vector<string>::iterator it;
												it = find(soldakiler.begin(), soldakiler.end(), c);
												if (it != soldakiler.end()) {
													kon2 = c;
												}
											}
											if (kon2 == "") {
												kon = c;
											}
											else {
												kon = kon2;
											}
											kon2 = "";
											//cout << mapIt->first << " -> " << kon << " ";
										}
										if (c == mapIt->second.back()) {
											for(int k=0;k<1;k++){
												if (mapIt->first != kon) {
													enazbiryol++;
													//cout << " " << mapIt->first << " -> " << kon;
													kontrol.push_back(enazbiryol); 
													kon3 += mapIt->first[0];
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			donme = 0;
		}
		kon3 += sag;
		if (kon3 != kon4) {
			if (kon3.size() == kon4.size()) {
				ft[i] = 0;
				//cout << i <<" "<<ft[i]<<" " ;
				index = i;
			}
		}
		
		kon4 = "";
		kon3 = "";
		kontroller.push_back(kontrol);
		kontrol.clear();
		enazbiryol = 0;
		ilkkez = 0;
		donme1 = 0;
		//cout << endl;
	}

	for (int i = 0; i < kontroller.size(); i++) {
		for (int j = 0; j < kontroller[i].size(); j++) {
			if (j == kontroller[i].size() - 1) {
				if (kontroller[i][j] >= paths[i].size() - 2) {
					ft[i] = 1;
				}
				else {
					ft[i] = 0;
				}
				ft[index] = 0;
				//cout << i << " " << ft[i] << " ";
			}
		}
		//cout << endl;
	}

} //Sol kısımdakini degisken olarak algıla gidebileceği yolları tara eğer yoksa false döndür. Eğer varsa yeni değişkene geç onu tara.

void yolkontrol(string line, int size) {
	vector <char> path;
	char satirkarakterler[100];
	int tekdonus = 0;
	char solnode, sagnode;
	strcpy_s(satirkarakterler, line.c_str());
	for (int i = 0; i < line.size(); i++) {
		if (satirkarakterler[i] != ' ' && satirkarakterler[i + 1] != NULL) {
			if (tekdonus == 0) {
				tekdonus++;
				solnode = satirkarakterler[i];
				path.push_back(solnode);
			}
			sagnode = satirkarakterler[i + 1];
			path.push_back(sagnode);
			solnode = NULL;
			sagnode = NULL;
		}
	}
	path.push_back(NULL);
	donmesayisi++;
	paths.push_back(path);
	if (donmesayisi == size) {
		yol();
	}
}

int main()
{
	try {
		path p(".\\");
		for (const directory_entry& dre : directory_iterator(p))
		{
			if (!is_directory(dre))
			{
				if (dre.path().extension() == ".txt")
				{
					ifstream file(dre.path().filename());
					ifstream satirsayisiicin(dre.path().filename());
					if (satirsayisiicin.is_open()) {
						string line;
						while (getline(satirsayisiicin, line)) {
							satirsayisi++;
						}
					}
					if (file.is_open()) {
						string line;
						int kontrol1 = 0, kontrol2 = 0;
						int aktifsatirsayisi = 0;
						while (getline(file, line)) {
							aktifsatirsayisi++;
							size_t nodesatiri = line.find(",");
							size_t yol = line.find("->");
							size_t links = line.find("Links:");
							size_t paths1 = line.find("Paths:");
							if (nodesatiri != string::npos)
								nodetanimla(line);
							if (yol != string::npos)
								linktanimlat(line);
							if (paths1 != string::npos) {
								yololusturkontrol();
								kontrol2 = aktifsatirsayisi;
							}
							if (nodesatiri == string::npos and yol == string::npos and links == string::npos and paths1 == string::npos)
								yolkontrol(line, satirsayisi - kontrol2);
							if (aktifsatirsayisi == satirsayisi) {
								ofstream outfile("output.txt");
								bool yazikont = false;
								for (int i = 0; i < paths.size(); i++) {
									for (int j = 0; j < paths[i].size(); j++) {
										outfile << paths[i][j];
									}
									for (int j = 0; j < ft.size(); j++) {
										if (ft[i] == 1)
											yazikont = true;
										else
											yazikont = false;
									}
									if (yazikont) {
										outfile << " [YES]";
									}
									else {
										outfile << " [NO]";
									}
									outfile << endl;
								}
							}
						}
					}
				}
			}
		}
	}
	catch (const filesystem_error& ex)
	{
		//cout << ex.what() << endl;
	}
}
