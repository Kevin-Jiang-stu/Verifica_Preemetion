#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Struttura per memorizzare i dati di un singolo processo
struct Processo
{
    int id;
    int arrivo;
    int durata;
    int priorita;
};

void schedulaProcessiES1(vector<Processo> vettProcessi)
{
    int tempo = 0;
    vector<Processo> Coda;

    while (!vettProcessi.empty())
    {
        vector<Processo> Coda;
        for (int i = 0; i < vettProcessi.size(); i++)
        {
            if (tempo >= vettProcessi[i].arrivo)
            {
                Coda.push_back(vettProcessi[i]);
            }
        }
        if (!Coda.empty())
        {

            cout << Coda[0].id << " " << tempo << " " << tempo + Coda[0].durata << endl;
            tempo += Coda[0].durata;
            vettProcessi.erase(vettProcessi.begin());
        }
        else
            tempo++;
    }
}

void schedulaProcessiES2(vector<Processo> vettProcessi)
{
    int tempo = 0;
    vector<Processo> Coda;

    while (!vettProcessi.empty())
    {
        vector<Processo> Coda;
        for (int i = 0; i < vettProcessi.size(); i++)
        {
            if (tempo >= vettProcessi[i].arrivo)
            {
                Coda.push_back(vettProcessi[i]);
            }
        }
        sort(Coda.begin(), Coda.end(), [](const Processo a, const Processo b)
             { return a.durata > b.durata; });

        if (!Coda.empty())
        {
            int D = 0;
            for (int i = 1; i < Coda.size(); i++)
            {
                if (Coda[i].durata < Coda[D].durata)
                {
                    D = i;
                }
            }

            cout << Coda[D].id << " " << tempo << " " << tempo + Coda[0].durata << endl;
            tempo += Coda[D].durata;

            for (int i = 0; i < vettProcessi.size(); i++)
            {
                if (vettProcessi[i].id == Coda[D].id)
                {
                    vettProcessi.erase(vettProcessi.begin()+i);
                    break;
                }
            }
        }
        else
            tempo++;
    }
}

int main()
{
    ifstream file("input.txt");

    // Controllo se il file esiste e si apre correttamente
    if (!file.is_open())
    {
        cout << "Errore nell'apertura del file!" << endl;
        return 1;
    }

    int n;
    file >> n; // Legge il numero totale di processi dalla prima riga

    vector<Processo> vettProcessi(n);

    // Popola il vettore di processi
    for (int i = 0; i < n; i++)
    {
        file >> vettProcessi[i].id >> vettProcessi[i].arrivo >> vettProcessi[i].durata >> vettProcessi[i].priorita;
    }

    file.close();

    // Test esercizio 1
    schedulaProcessiES1(vettProcessi);

    // Test esercizio 2
    schedulaProcessiES2(vettProcessi);
    return 0;
}
