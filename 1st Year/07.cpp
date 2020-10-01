// Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Struct que permite almacenar todos los datos conocidos sobre la pelicula en el mismo sitio.
struct Peliculas {
	string nombre;
	int hora;
	int minuto;
	int segundo;
};

// Sobrecarga de operador para poder mostrar las peliculas ya ordenadas de manera sencilla.
ostream & operator<<(ostream & archSal, Peliculas pelicula) {
	archSal << setw(2) << setfill('0') << pelicula.hora << ':' << setw(2) << setfill('0') << pelicula.minuto << ':' << setw(2) << setfill('0') << pelicula.segundo << ' ' << pelicula.nombre;
	return archSal;
}

/* Funcion que compara dos nombres por orden alfabetico no teniendo en cuenta mayusculas 
	(No tiene en cuenta el tamaño en palabras coincidentes hasta un punto, en caso de dos 
	nombres de diferente tamaño con uno de ellos siendo una prolongacion del otro, devuelve falso). */
bool comparar(string nombre1, string nombre2) {
	int i = 0;
	while (i < nombre1.size() && i < nombre2.size() && tolower(nombre1[i]) == tolower(nombre2[i]))
		++i;
	return i < nombre1.size() && i < nombre2.size() && tolower(nombre1[i]) > tolower(nombre2[i]);
}

// Sobrecarga para poder comparar dos peliculas (A la vez llama a otra funcion para comparar nombres).
bool operator>(Peliculas pelicula1, Peliculas pelicula2) {
	return (pelicula1.hora > pelicula2.hora ||
		(pelicula1.hora == pelicula2.hora && pelicula1.minuto > pelicula2.minuto) ||
		(pelicula1.hora == pelicula2.hora && pelicula1.minuto == pelicula2.minuto
		&& pelicula1.segundo > pelicula2.segundo) || (pelicula1.hora == pelicula2.hora && pelicula1.minuto == pelicula2.minuto
		&& pelicula1.segundo == pelicula2.segundo && comparar(pelicula1.nombre, pelicula2.nombre)));
}

/* Funcion que lee el comienzo de una pelicula, su duracion y su nombre. Luego calcula la hora de finalizacion comprobando
	que no haya mas de 60 segundos ni minutos (porque la hora no puede ser mas que 23:59:59 segun el enunciado) y lo mete
	en un vector con el resto de peliculas. */
void leer(vector<Peliculas> & cartelera) {
	int durH = 0, durM = 0, durS = 0;
	char aux = ' ';

	for (int i = 0; i < cartelera.size(); ++i) {
		cin >> cartelera[i].hora >> aux >> cartelera[i].minuto
			>> aux >> cartelera[i].segundo;
		cin >> durH >> aux >> durM >> aux >> durS;

		cartelera[i].segundo += durS;
		cartelera[i].minuto += durM;
		cartelera[i].hora += durH;
		if (cartelera[i].segundo >= 60) {
			cartelera[i].segundo -= 60;
			++cartelera[i].minuto;
		}
		if (cartelera[i].minuto >= 60) {
			cartelera[i].minuto -= 60;
			++cartelera[i].hora;
		}

		cin.get(aux);
		getline(cin, cartelera[i].nombre);
	}
}

// Funcion que ordena la cartelera por el metodo de insercion. Comparando peliculas.
void ordenarPeliculas(vector<Peliculas> & cartelera) {
	int puntero = 0;
	Peliculas peliculaAux;

	for (int i = 1; i < cartelera.size(); ++i) {
		peliculaAux = cartelera[i];
		puntero = i;
		while (puntero > 0 && cartelera[puntero - 1] > peliculaAux) {
			cartelera[puntero] = cartelera[puntero - 1];
			--puntero;
		}
		cartelera[puntero] = peliculaAux;
	}
}

int main() {
	int numPeliculas;
	
	cin >> numPeliculas;

	// Va leyendo peliculas y ordenandolas hasta que el numero de peliculas a ordenar sea 0.
	while (numPeliculas != 0) {
		vector<Peliculas> cartelera(numPeliculas);
		leer(cartelera);
		ordenarPeliculas(cartelera);

		for (int i = 0; i < numPeliculas; ++i)
			cout << cartelera[i] << '\n';
		cout << "---\n";

		cin >> numPeliculas;
	}


	return 0;
}