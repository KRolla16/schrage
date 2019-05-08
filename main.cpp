#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>


using namespace std;


class Task {
public:
    int r;
    int p;
    int q;
    int nrZad;
    Task() {
        r = 0;
        p = 0;
        q = 0;
        nrZad=0;
    }
};

Task minimum(vector<Task> dane, vector<int> Nn);
Task maximum(vector<Task> dane, vector<int> Ng);
vector<int> Shrage(vector<Task> dane);
int ShrangeP(vector<Task> &dane);

int cmax(vector<int> kolejnosc, vector<Task> dane,  int l_zad);

int ifFound(vector<int> zbior, int szukany) {
	for (int i = 0; i < zbior.size(); i++)
		if (zbior[i] == szukany) return i;
	return -1;
}

vector<int> Shrage(vector<Task> dane) {

    int i=0;
    vector<int> kolejnosc(0);
    Task j;
    vector<int> Ng(0);
    vector<int> Nn(dane.size());
    for (int i = 0; i < Nn.size(); i++)
        Nn[i] = i+1;
    int t = minimum(dane, Nn).r;
    while (Ng.size() != 0 || Nn.size() != 0) {
        while (Nn.size() != 0 && minimum(dane, Nn).r <= t) {
            j = minimum(dane, Nn);
            Ng.push_back(j.nrZad);
            vector<int>::iterator zadanie_gotowe;
            zadanie_gotowe = find(Nn.begin(), Nn.end(), j.nrZad);
            Nn.erase(zadanie_gotowe);
        }
        if (Ng.size() == 0) {
            t = minimum(dane, Nn).r;
        }
            else {
            j = maximum(dane, Ng);
            vector<int>::iterator zadanie_gotowe;
            zadanie_gotowe = find(Ng.begin(), Ng.end(), j.nrZad);
            kolejnosc.resize(kolejnosc.size() + 1);
            kolejnosc[i] = j.nrZad;
            Ng.erase(zadanie_gotowe);
            i++;
            t = t + dane[j.nrZad - 1].p;
        }
    }
    return kolejnosc;
}

int ShrageP(vector<Task> &dane)
{
int cmax = 0;
Task j,l;
l.p = 0;
l.q = 9999999;
 vector<int> Ng(0);
 vector<int> Nn(dane.size());
 for (int i = 0; i < Nn.size(); i++)
    Nn[i] = i+1;
    int t = 0;
  while (Ng.size() != 0 || Nn.size() != 0)
{
      while (Nn.size() != 0 && minimum(dane, Nn).r <= t)
    {
       j = minimum(dane, Nn);
       Ng.push_back(j.nrZad);
        vector<int>::iterator zadanie_gotowe;
            zadanie_gotowe = find(Nn.begin(), Nn.end(), j.nrZad);
            Nn.erase(zadanie_gotowe);
            if(dane[j.nrZad - 1].q > dane[l.nrZad - 1].q)
            {
                dane[l.nrZad - 1].p = t - dane[j.nrZad - 1].r;
                t = dane[j.nrZad - 1].r;

                if(dane[l.nrZad - 1].p>0)
                    Ng.push_back(l.nrZad);
            }
    }
  if (Ng.size() == 0)
    {
        t = minimum(dane, Nn).r;
    }
   else
    {
            j = maximum(dane, Ng);
            vector<int>::iterator zadanie_gotowe;
            zadanie_gotowe = find(Ng.begin(), Ng.end(), j.nrZad);
            Ng.erase(zadanie_gotowe);
            l = j;
            t = t + dane[j.nrZad - 1].p;
            cmax = max(cmax,t+dane[j.nrZad - 1].q);
    }
}
   return cmax;
}

int cmax(vector<int> kolejnosc, vector<Task> dane, int l_zad) {
    vector<int> C(l_zad);
    vector<int> S(C.size()+1);
    S[0] = 0;
    S[1] = max(dane[kolejnosc[0] - 1].r, 0 + 0);
    C[0] = S[1] + dane[kolejnosc[0] - 1].p;
        for (int j = 2; j <= l_zad; j++) {
            S[j] = max(dane[kolejnosc[j-1] - 1].r, S[j - 1] + dane[kolejnosc[j - 2] - 1].p);
            C[j-1] = S[j] + dane[kolejnosc[j - 1]-1].p;
        }
        for(int i=0; i<C.size();i++)
            C[i] = C[i] + dane[kolejnosc[i]-1].q;
        vector<int>::iterator it = max_element(begin(C), end(C));
        int index = distance(C.begin(), it);
    return C[index];
}
Task minimum(vector<Task> dane, vector<int> Nn)
{
    Task mini;
    mini.r = 99999;
    for (int i = 0; i < dane.size(); i++) {
 if (ifFound(Nn, dane[i].nrZad) >= 0){
        if (dane[i].r < mini.r)
        mini = dane[i];
    }
    }
    return mini;
}
Task maximum(vector<Task> dane, vector<int> Ng) {
    Task maxi;
    maxi.q=0;
    for (int i = 0; i < dane.size(); i++) {
        if (ifFound(Ng, dane[i].nrZad) >= 0){
        if (dane[i].q > maxi.q)
        maxi = dane[i];
    }
    }
    return maxi;
}

int main()
{
    int lzad;
    int kolumny;
    ifstream data("in200.txt");
    data >> lzad;
    data >> kolumny;
    vector<Task> dane(lzad);
    for (int j = 0; j < lzad; j++) {
        {
            data >> dane[j].r;
            data >> dane[j].p;
            data >> dane[j].q;
            dane[j].nrZad = j + 1;
        }
    }


    chrono::time_point< std::chrono::system_clock> start = std::chrono::system_clock::now();
    vector<int> kolejnosc = Shrage(dane);
    int Cmax = cmax(kolejnosc, dane, lzad);
    int cmax2 = ShrageP(dane);
    chrono::time_point< std::chrono::system_clock> end = std::chrono::system_clock::now();
    cout << "Cmax = " << Cmax <<" j"<< endl<<endl;
    cout << "CmaxP " << cmax2 <<"j"<< endl<<endl;
    cout << "Kolejnosc zadan: " << endl;
    for (int i = 0; i < kolejnosc.size(); i++) cout << kolejnosc[i] << "  ";
    chrono::duration<double> elapsed_seconds = end - start;
    cout << endl << "czas trwania: " << elapsed_seconds.count() << "s\n";
    return 0;
}
