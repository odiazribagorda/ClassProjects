// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <fstream>
#include "ArbolB.h"

using namespace std;

const int NUM_PRUEBAS = 4;

int main() {
	ifstream archEnt("prueba.txt");
	ofstream archSal("salida.txt");
	archSal.close();
	for (int i = 0; i < NUM_PRUEBAS; ++i) {
		int numNodos = 0;
		int nodo = 0;
		int minHijos = 0;
		// Se crea un arbol 3-4-5-6 de 100 nodos y se borra un elemento de uno que no es hoja (de hecho es la raiz).
		if (i == 0) {
			minHijos = 3;
			ArbolB<int> arbol(minHijos);
			archEnt >> numNodos;
			for (int j = 0; j < numNodos; ++j) {
				archEnt >> nodo;
				arbol.insertar(nodo);
			}
			archSal.open("salida.txt", ios::app);
			archSal << "Ejemplo " << i + 1 << ":\nEn este ejemplo se muestra un arbol(numero minimo de hijos = "
				<< minHijos << ") de " << numNodos << " nodos."
				<< " Que tras la insercion queda (en preorden):\n\t";
			archSal.close();

			arbol.guardarAñadiendo("salida.txt");
			nodo = 27;

			archSal.open("salida.txt", ios::app);
			archSal << "Ahora se borra el nodo " << nodo << " del arbol y queda (en preorden):\n\t";
			archSal.close();
			arbol.borrar(nodo);
			arbol.guardarAñadiendo("salida.txt");
		}
		// Se crea un arbol 2-3-4 de 10 elementos y borramos el ultimo (en una hoja)
		else if (i == 1) {
			minHijos = 2;
			ArbolB<int> arbol(minHijos);
			archEnt >> numNodos;
			for (int j = 0; j < numNodos; ++j) {
				archEnt >> nodo;
				arbol.insertar(nodo);
			}
			archSal.open("salida.txt", ios::app);
			archSal << "Ejemplo " << i + 1 << ":\nEn este ejemplo se muestra un arbol(numero minimo de hijos = "
				<< minHijos << ") de " << numNodos << " nodos."
				<< " Que tras la insercion queda (en preorden):\n\t";
			archSal.close();

			arbol.guardarAñadiendo("salida.txt");
			nodo = 10;

			archSal.open("salida.txt", ios::app);
			archSal << "Ahora se borra el nodo " << nodo << " del arbol y queda (en preorden):\n\t";
			archSal.close();
			arbol.borrar(nodo);
			arbol.guardarAñadiendo("salida.txt");
		}
		// Se crea un arbol 20-21-21-...-39-40. Que tendra todos los nodos en la raiz (porque tiene 33 nodos)
		// y se borra un elemento cualquiera.
		else if (i == 2) {
			minHijos = 20;
			ArbolB<int> arbol(minHijos);
			archEnt >> numNodos;
			for (int j = 0; j < numNodos; ++j) {
				archEnt >> nodo;
				arbol.insertar(nodo);
			}
			archSal.open("salida.txt", ios::app);
			archSal << "Ejemplo " << i + 1 << ":\nEn este ejemplo se muestra un arbol(numero minimo de hijos = "
				<< minHijos << ") de " << numNodos << " nodos."
				<< " Que tras la insercion queda (en preorden):\n\t";
			archSal.close();

			arbol.guardarAñadiendo("salida.txt");
			nodo = 13;

			archSal.open("salida.txt", ios::app);
			archSal << "Ahora se borra el nodo " << nodo << " del arbol y queda (en preorden):\n\t";
			archSal.close();
			arbol.borrar(nodo);
			arbol.guardarAñadiendo("salida.txt");
		}
		// Se crea un arbol 2-3-4 y se mira si un elemento esta en el arbol.
		else {
			minHijos = 2;
			ArbolB<int> arbol(minHijos);
			archEnt >> numNodos;
			for (int j = 0; j < numNodos; ++j) {
				archEnt >> nodo;
				arbol.insertar(nodo);
			}
			archSal.open("salida.txt", ios::app);
			archSal << "Ejemplo " << i + 1 << ":\nEn este ejemplo se muestra un arbol(numero minimo de hijos = "
				<< minHijos << ") de " << numNodos << " nodos."
				<< " Que tras la insercion queda (en preorden):\n\t";
			archSal.close();

			arbol.guardarAñadiendo("salida.txt");
			nodo = 10;

			archSal.open("salida.txt", ios::app);
			archSal << "Se realiza la busqueda de la clave " << nodo << " y el resultado es:\n";
			if(arbol.contiene(nodo)) archSal << "\tLa clave " << nodo << " SI que pertenece al arbol\n";
			else archSal << "\tLa clave " << nodo << " NO se pudo encontrar en el arbol.\n\t";
			archSal.close();
		}
	}
	archEnt.close();
	return 0;
}