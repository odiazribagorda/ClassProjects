// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include "01.h"
using namespace std;

int busqueda(const vector<horas> &horario,int ini,int fin,bool &enc,horas horasalida){
	
	int mitad = (ini + fin) / 2;
	if (horario[mitad]<horasalida){
		if (fin > ini){
			busqueda(horario, mitad + 1, fin, enc,horasalida);
		}
	}
	else{
		enc = true;
		if (fin > ini){
			busqueda(horario, ini, mitad, enc,horasalida);
		}
		else return mitad;
	}
}



int main(){
	int numtrenes, salidas,sol;
	bool encontrado;
	cin >> numtrenes >> salidas;
	while (numtrenes != 0 || salidas != 0){
		vector<horas> horario(numtrenes);
		for (int i = 0; i < horario.size();++i)cin>>horario[i];
		for (int i = 0; i < salidas; ++i){
			try{
				horas horasalida;
				encontrado = false;
				cin >> horasalida;
				sol = busqueda(horario, 0, numtrenes - 1, encontrado, horasalida);
				if (encontrado)cout << horario[sol];
				else cout << "NO";
			}
				catch (invalid_argument const & e){
				cout << e.what();
			}
			cout << '\n';
		}
		cout << "---\n";
		cin >> numtrenes >> salidas;
	}
	return 0;
}