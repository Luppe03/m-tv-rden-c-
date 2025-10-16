#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <limits>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Matning {
    double varde;
    string tid;
};

void visaMeny();
void laggTillVarden(vector<Matning>&);
void visaStatistik(const vector<Matning>&);
void sokVarde(const vector<Matning>&);
void sorteraLista(vector<Matning>&);
void genereraSlumpvarden(vector<Matning>&);

double lasInDouble();
double beraknaMedel(const vector<double>&);
double beraknaVarians(const vector<double>&);
double beraknaStdAvvikelse(const vector<double>&);
string nuvarandeTid();

int main() {
    vector<Matning> matvarden;
    int val;

    do {
        visaMeny();
        cout << "Välj ett alternativ: ";
        cin >> val;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Felaktig inmatning! Ange ett nummer mellan 1 och 6.\n";
            continue;
        }

        switch (val) {
            case 1: laggTillVarden(matvarden); break;
            case 2: visaStatistik(matvarden); break;
            case 3: sokVarde(matvarden); break;
            case 4: sorteraLista(matvarden); break;
            case 5: genereraSlumpvarden(matvarden); break;
            case 6: cout << "Avslutar programmet...\n"; break;
            default: cout << "Ogiltigt val, försök igen.\n"; break;
        }

    } while (val != 6);

    return 0;
}

void visaMeny() {
    cout << "\n===== MENY =====\n";
    cout << "1. Lägg till nya mätvärden\n";
    cout << "2. Visa statistik\n";
    cout << "3. Söka efter ett värde\n";
    cout << "4. Sortera listan\n";
    cout << "5. Generera slumpmässiga mätvärden\n";
    cout << "6. Avsluta\n";
    cout << "================\n";
}

string nuvarandeTid() {
    time_t nu = time(0);
    tm* lokalTid = localtime(&nu);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", lokalTid);
    return string(buffer);
}

void laggTillVarden(vector<Matning>& lista) {
    cout << "Ange mätvärden (skriv 'q' för att avsluta inmatning):\n";
    while (true) {
        cout << "Värde: ";
        string input;
        cin >> input;

        if (input == "q" || input == "Q") break;

        try {
            double varde = stod(input);
            lista.push_back({varde, nuvarandeTid()});
        } catch (...) {
            cout << "Ogiltigt värde, försök igen.\n";
        }
    }
}

void genereraSlumpvarden(vector<Matning>& lista) {
    int antal;
    cout << "Hur många värden ska simuleras? ";
    cin >> antal;

    if (cin.fail() || antal <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ogiltigt antal!\n";
        return;
    }

    srand(time(0));
    for (int i = 0; i < antal; ++i) {
        double varde = 20.0 + static_cast<double>(rand()) / RAND_MAX * 10.0;
        lista.push_back({varde, nuvarandeTid()});
    }

    cout << antal << " slumpmässiga värden (20–30 °C) har genererats.\n";
}

void visaStatistik(const vector<Matning>& lista) {
    if (lista.empty()) {
        cout << "Listan är tom. Lägg till värden först!\n";
        return;
    }

    vector<double> vardesLista;
    for (auto& m : lista) vardesLista.push_back(m.varde);

    double summa = accumulate(vardesLista.begin(), vardesLista.end(), 0.0);
    double medel = beraknaMedel(vardesLista);
    double varians = beraknaVarians(vardesLista);
    double stdavvikelse = beraknaStdAvvikelse(vardesLista);

    auto min_it = min_element(lista.begin(), lista.end(),
        [](const Matning& a, const Matning& b) { return a.varde < b.varde; });
    auto max_it = max_element(lista.begin(), lista.end(),
        [](const Matning& a, const Matning& b) { return a.varde < b.varde; });

    cout << "\n--- Statistik ---\n";
    cout << "Antal värden: " << lista.size() << "\n";
    cout << "Summa: " << summa << "\n";
    cout << "Medelvärde: " << medel << "\n";
    cout << "Minvärde: " << min_it->varde << " (kl. " << min_it->tid << ")\n";
    cout << "Maxvärde: " << max_it->varde << " (kl. " << max_it->tid << ")\n";
    cout << "Varians: " << varians << "\n";
    cout << "Standardavvikelse: " << stdavvikelse << "\n";
}

void sokVarde(const vector<Matning>& lista) {
    if (lista.empty()) {
        cout << "Listan är tom.\n";
        return;
    }

    cout << "Ange värde att söka efter: ";
    double sokeVarde = lasInDouble();

    bool hittad = false;
    for (size_t i = 0; i < lista.size(); ++i) {
        if (fabs(lista[i].varde - sokeVarde) < 1e-9) {
            cout << "Värdet " << sokeVarde << " hittades på position "
                 << (i + 1) << " (kl. " << lista[i].tid << ").\n";
            hittad = true;
        }
    }

    if (!hittad)
        cout << "Värdet " << sokeVarde << " finns inte i listan.\n";
}

void sorteraLista(vector<Matning>& lista) {
    if (lista.empty()) {
        cout << "Listan är tom.\n";
        return;
    }

    cout << "Sortera stigande (1) eller fallande (2)? ";
    int val;
    cin >> val;

    if (val == 1)
        sort(lista.begin(), lista.end(),
             [](const Matning& a, const Matning& b) { return a.varde < b.varde; });
    else if (val == 2)
        sort(lista.begin(), lista.end(),
             [](const Matning& a, const Matning& b) { return a.varde > b.varde; });
    else {
        cout << "Ogiltigt val!\n";
        return;
    }

    cout << "Sorterad lista:\n";
    for (const auto& m : lista)
        cout << m.varde << " (" << m.tid << ")\n";
}

double lasInDouble() {
    double varde;
    while (true) {
        cin >> varde;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ogiltig inmatning, försök igen: ";
        } else return varde;
    }
}

double beraknaMedel(const vector<double>& lista) {
    double summa = accumulate(lista.begin(), lista.end(), 0.0);
    return summa / lista.size();
}

double beraknaVarians(const vector<double>& lista) {
    double medel = beraknaMedel(lista);
    double sum = 0.0;
    for (double v : lista) sum += pow(v - medel, 2);
    return sum / lista.size();
}

double beraknaStdAvvikelse(const vector<double>& lista) {
    return sqrt(beraknaVarians(lista));
}
