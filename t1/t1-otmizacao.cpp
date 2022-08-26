#include <bits/stdc++.h>
using namespace std;


int main () {
    int months;
    cin >> months;
    vector<double> demands(months);
    vector<double> affluence(months);
    for (int i = 0; i < months; i++)
        cin >> demands[i];
    for (int i = 0; i < months; i++)
        cin >> affluence[i];
    double vini,vmax,vmin,k;
    cin >> vini >> vmin >> vmax >> k;
    double tmax,thermcost,ambcost;
    cin >> tmax >> thermcost >> ambcost;

    cout << "min : " << ambcost << " ambcost + " << thermcost << " termprod;\n";
    cout << "term: termprod = ";
    for (int i = 1; i < months; i++)
        cout << "termprod" << i << " + ";
    cout << "termprod" << months << ";\n"; 

    cout << "amb: ambcost = ";
    for (int i = 1; i < months; i++)
        cout << "ambcost" << i << " + ";
    cout << "ambcost" << months << ";\n";

    cout << "c1: termprod1 + " << k << " consumo1 >= " << demands[0] << ";\n";
    cout << "c2: ambcost1 = variacao1;\n";
    cout << "c3: variacao1 >=  " << affluence[0] << " - consumo1;\n"; 
    cout << "c4: variacao1 >= -" << affluence[0] << " + consumo1;\n"; 
    cout << "c5: reservatorio1 = " << vini <<" + " << affluence[0] << " - consumo1;\n";
    cout << "c6: " << vmin << " <= reservatorio1 <= " << vmax << ";\n";
    cout << "c7: " << 0 << " <= termprod1 <= " << tmax << ";\n";
    cout << "c8: variacao1 >= 0;\n\n";

    for (int i = 2; i <= months; i++) {
        cout << "c"  << i << "1: termprod" << i << " + " << k << " consumo" << i << " >= " << demands[i-1] << ";\n";
        cout << "c"  << i << "2: ambcost" << i <<" = variacao" << i << ";\n";
        cout << "c"  << i << "3: variacao"<< i << " >=   " << affluence[i-1] << " - consumo" << i <<";\n"; 
        cout << "c"  << i << "4: variacao"<< i << " >=  -" << affluence[i-1] << " + consumo" << i <<";\n";  
        cout << "c"  << i << "5: reservatorio" << i << " = " << "reservatorio" << i - 1 <<" + " << affluence[i-1] << " - consumo" << i << ";\n";
        cout << "c"  << i << "6: " << vmin << " <= reservatorio" << i << " <= " << vmax << ";\n";
        cout << "c"  << i << "7: "<< 0 << " <= termprod" << i << " <= " << tmax << ";\n";
        cout << "c"  << i << "8: variacao" << i << " >= 0;\n";
        cout << "\n";
    }
}