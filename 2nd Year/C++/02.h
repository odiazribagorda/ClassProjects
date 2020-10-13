// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>
using namespace std;


class horas{
public:
	int segundo;
	int minuto;
	int lahora;

	horas(){};

	horas(int seg, int min, int hor){
		int a = 0;
		segundo = seg;
		minuto = min;
		lahora = hor;
		if (seg > 59 || min > 59 || hor > 23)throw invalid_argument("ERROR");
	}
	bool operator <(horas const& that) const {
		return lahora < that.lahora || (lahora == that.lahora && minuto<that.minuto) ||
			(lahora == that.lahora && minuto == that.minuto && segundo<that.segundo);
	}
	horas operator+(horas const& h1) {
		horas aux;
		aux.segundo = (segundo + h1.segundo) % 60;
		aux.minuto = (minuto + h1.minuto + (segundo + h1.segundo) / 60) % 60;
		aux.lahora = (lahora + h1.lahora + (minuto + h1.minuto + (segundo + h1.segundo) / 60) / 60);
		if (24 <= aux.lahora) throw domain_error("");
		else return aux;
	}
};


inline ostream & operator<<(ostream & out, horas const& hor) {
	if (hor.lahora < 10)out << '0';
	out << hor.lahora << ':';
	if (hor.minuto < 10)out << '0';
	out << hor.minuto << ':';
	if (hor.segundo < 10)out << '0';
	out << hor.segundo;
	return out;
}


inline istream & operator>>(istream & in, horas & hor) {
	char c; int a, min, hora, seg;
	for (int i = 0; i < 8; ++i){
		in >> c;
		if (i % 3 == 0){
			a = 0;
			a = (int(c) - int('0')) * 10;
		}
		else if (i % 3 == 1){
			a += (int(c) - int('0'));
			if (i < 3)hora = a;
			else if (i < 5)min = a;
			else seg = a;
		}
	}
	try {
		hor = horas(seg, min, hora);
	}
	catch (invalid_argument const & e){
		throw e;
	}
	return in;
}

class pelicula {
public:
	string nombre;
	horas horaIni;
	horas horaFin;
	horas duracion;

	pelicula(){};
	
	pelicula(string n, horas hI, horas dur) {
		nombre = n;
		horaIni = hI;
		duracion = dur;
		horaFin = horaIni + duracion;
	}

	bool operator<(pelicula const& peli) {
		return horaFin < peli.horaFin || (!(horaFin < peli.horaFin || peli.horaFin < horaFin) && nombre < peli.nombre);
	}
};

inline istream & operator>>(istream & archEnt, pelicula & peli) {
	archEnt >> peli.horaIni;
	archEnt >> peli.duracion;
	getline(archEnt, peli.nombre);
	peli.horaFin = peli.horaIni + peli.duracion;

	return archEnt;
}

inline ostream & operator<<(ostream & archSal, pelicula const& peli) {
	archSal << peli.horaFin << ' ' << peli.nombre;
	return archSal;
}