//DG05 (Oscar Diaz Ribagorda : 70066751B)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct tAsignatura {
	string nombre;
	float creditos;
	int plazas;
};

const int NUM_ASIG = 6, MAX_RES = 4;

bool cargar(vector<tAsignatura> & catalogo) {
	bool error = false;
	int cont = 0;
	tAsignatura asignatura;
	
	ifstream archEnt;
	archEnt.open("asignaturas.txt");
	if (!archEnt.is_open()) error = true;
	else {
		archEnt >> asignatura.nombre;
		while (asignatura.nombre != "XXX" && cont < NUM_ASIG) {
			archEnt >> asignatura.creditos >> asignatura.plazas;
			catalogo.push_back(asignatura);
			archEnt >> asignatura.nombre;
			++cont;
		}
		if (cont < NUM_ASIG) error == true;
	}

	archEnt.close();

	return error;
}

void mostrarDisponibles(const vector<tAsignatura> & catalogo) {
	
	cout << "Asignaturas disponibles...\n";
	cout << "Asignatura  Creditos  Grupos\n";
	for (int i = 0; i < NUM_ASIG; ++i) {
		if (catalogo[i].plazas != 0) {
			cout << setw(3 + catalogo[i].nombre.size()) << catalogo[i].nombre;
			cout << setw(15 - catalogo[i].nombre.size()) << fixed << setprecision(2) << catalogo[i].creditos;
			cout << setw(7) << catalogo[i].plazas << '\n';
		}
	}
	cout << '\n';
}

void leerReservas(vector<tAsignatura> & reserva) {
	tAsignatura asignatura;
	int cont = 0;

	cout << "Realize su reserva:\n";

	cout << "Nombre de la asignatura (XXX para terminar): ";
	cin >> asignatura.nombre;
	while (cont < MAX_RES - 1 && asignatura.nombre != "XXX") {
		cout << "Grupos a reservar: ";
		cin >> asignatura.plazas;
		reserva.push_back(asignatura);

		cout << "Nombre de la asignatura (XXX para terminar): ";
		cin >> asignatura.nombre;
		++cont;
	}
	if (asignatura.nombre != "XXX") {
		cout << "Grupos a reservar: ";
		cin >> asignatura.plazas;
		reserva.push_back(asignatura);
	}
	else if (cont == MAX_RES - 1) cout << "¡Maximo numero de reservas!\n\n";
}

bool buscarAsignatura(const vector<tAsignatura> & catalogo, tAsignatura reserva, int & pos) {
	int cont = 0;
	bool existe = false;

	while (cont < NUM_ASIG && !existe) {
		if (reserva.nombre == catalogo[cont].nombre) {
			pos = cont;
			existe = true;
		}
		++cont;
	}

	return existe;
}

void realizarReserva(vector<tAsignatura> & catalogo, const vector<tAsignatura> & reserva) {
	int pos = 0;
	float creditos = 0.0;
	
	for (int i = 0; i < MAX_RES; ++i) {
		if (buscarAsignatura(catalogo, reserva[i], pos) && reserva[i].plazas <= catalogo[pos].plazas) {
			catalogo[pos].plazas -= reserva[i].plazas;
			creditos += (catalogo[pos].creditos * reserva[i].plazas);
		}
		else if (!buscarAsignatura(catalogo, reserva[i], pos))
			cout << "Asignatura desconocida: " << reserva[i].nombre << '\n';
		else
			cout << "Asignatura " << reserva[i].nombre << ": ¡No hay suficientes grupos!\n";
	}
	cout << '\n';
	cout << ">>> Numero de creditos reservados = " << fixed << setprecision(2) << creditos << " <<<\n\n";

}

void guardar(const vector<tAsignatura> & catalogo) {
	ofstream archSal;
	archSal.open("asignaturas.txt");
	for (int i = 0; i < NUM_ASIG; ++i) {
		archSal << catalogo[i].nombre << ' ' << fixed << setprecision(2) << catalogo[i].creditos << ' ' << catalogo[i].plazas << '\n';
	}
	archSal << "XXX\n";

	archSal.close();
}

int main() {
	vector<tAsignatura> catalogo;
	vector<tAsignatura> reserva;
	
	if (cargar(catalogo)) cout << "No se pudo cargar el archivo\n";
	else {
		mostrarDisponibles(catalogo);
		leerReservas(reserva);
		realizarReserva(catalogo, reserva);
		mostrarDisponibles(catalogo);
		guardar(catalogo);
	}

	return 0;
}