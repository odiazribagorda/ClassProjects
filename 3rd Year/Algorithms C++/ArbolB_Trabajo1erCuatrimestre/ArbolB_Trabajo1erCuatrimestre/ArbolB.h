// Oscar Diaz Ribagorda (DG04)
// Clase de Arbol-B que tiene Nodos-B y las operaciones necesarias para operar con el.

#ifndef ArbolB_
#define ArbolB_

#include <iostream>
#include <fstream>
#include <iomanip>
#include "NodoB.h"
using namespace std;

template<class T>
class ArbolB {

public:
	// Constructor
	ArbolB(int t) {
		numClaves = 2 * t - 1;
		minClaves = t - 1;
		root = nullptr;
		listaAux = new T[numClaves + 1];
		listaPuntAux = new NodoB<T>*[numClaves + 2];
	}
	// Destructor
	~ArbolB() {
		delete[] listaAux;
		delete[] listaPuntAux;
		eliminar(root);
	}

	// Funcion que inserta la clave pedida en el arbol-B.
	void insertar(T & clave) {
		// Si no hay raiz, se crea.
		if (root == nullptr) 
			root = new NodoB<T>(numClaves);
		// Si la raiz esta llena, se separa en dos y cambia la raiz al nodo unidad que contiene unicamente la mediana.
		else if (root->numLlavesUsadas == numClaves) {
			NodoB<T> *aux = new NodoB<T>(numClaves);
			aux = root;
			root = new NodoB<T>(numClaves);
			root->numLlavesUsadas = 0;
			root->hijos[0] = aux;
			separarHijo(root, 0);
		}
		inserta(root, clave);
	}

	// Funcion que borra una clave del arbol-B (solo si esta, si no no hace nada).
	void borrar(T & clave) {
		borra(root, clave);
	}

	// Devuelve verdadero si la clave esta dentro del arbol.
	bool contiene(T & clave) {
		if (buscar(clave) == nullptr) return false;
		else return true;
	}

	// Funcion que te devuelve el valor que estas buscando si lo encuentra.
	T *buscar(T & clave) {
		return buscar(root, clave);
	}

	// Guarda en el archivo dado el arbolB (en preorden)
	bool guardar(char *file) {
		ofstream out(file);

		if (!out.fail()) {
			guardarPreorden(out, true, nullptr);
			out << endl;
		}
		else
			return false;
		out.close();
		return true;
	}

	// Guarda en el archivo dado el arbolB (en preorden), añadiendo a lo que ya hay en el archivo.
	bool guardarAñadiendo(char *file) {
		ofstream out(file, ios::app);

		if (!out.fail()) {
			guardarPreorden(out, true, nullptr);
			out << endl;
		}
		else
			return false;
		out.close();
		return true;
	}

	// Funcion que guarda en el archivo dado los nodos en preorden.
	void guardarPreorden(ostream &out, bool r, NodoB<T>* nodo) {
		if (r)
			nodo = root;
		if (!nodo)
			return;

		for (int i = 0; i<nodo->numLlavesUsadas; i++)
			out << nodo->claves[i] << "\t";

		for (int i = 0; i <= nodo->numLlavesUsadas; i++)
			guardarPreorden(out, false, nodo->hijos[i]);
	}

	// Muestra los nodos por consola en preorden.
	void preorden(bool r, NodoB<T>* nodo) {
		int i;
		if (r)
			nodo = root;
		if (!nodo)
			return;
		mostrar(nodo);
		for (i = 0; i <= nodo->numLlavesUsadas; i++)
			preorden(false, nodo->hijos[i]);
	}

	// Muestra un nodo por consola.
	void mostrar(NodoB<T>* nodo)
	{
		for (int i = 0; i < nodo->numLlavesUsadas; i++)
			cout << nodo->claves[i] << endl;
	}

private:
	int numClaves, minClaves;	// Indican el numero maximos y minimo de claves en cada nodo.
	NodoB<T> *root;
	T *listaAux;				// Estas dos listas se utilizan como auxiliares para la funcion de insercion.
	NodoB<T> **listaPuntAux;	//

	// Funcion que destruye recursivamente todos los nodos del arbol que tiene como raiz el nodo que le pasan.
	void eliminar(NodoB<T>* nodo) {
		if (nodo != NULL) {
			for (int i = 0; i < nodo->numLlavesUsadas; ++i) eliminar(nodo->hijos[i]);
			delete nodo;
		}
	}

	// Funcion que separa un hijo con numClaves numero de claves en dos hijos poniendo como clave en el padre
	// la mediana del hijo.
	void separarHijo(NodoB<T> * padre, int pos) {
		NodoB<T> *hijoIz = padre->hijos[pos];
		NodoB<T> *hijoDer = new NodoB<T>(numClaves);
		// Se desplazan las claves del padre para hacer hueco.
		for (int i = padre->numLlavesUsadas; i > pos; --i) {
			padre->claves[i] = padre->claves[i - 1];
			padre->hijos[i + 1] = padre->hijos[i];
		}
		// Se rellena el hijo derecho.
		hijoDer->numLlavesUsadas = (hijoIz->numLlavesUsadas - 1) / 2;
		for (int i = 0; i < hijoDer->numLlavesUsadas; ++i) {
			hijoDer->claves[i] = hijoIz->claves[(hijoIz->numLlavesUsadas / 2) + 1 + i];
			hijoDer->hijos[i] = hijoIz->hijos[(hijoIz->numLlavesUsadas / 2) + 1 + i];
		}
		hijoDer->hijos[hijoDer->numLlavesUsadas] = hijoIz->hijos[hijoIz->numLlavesUsadas];

		// Se establece la mediana como clave, se reduce el hijo izquierdo y se enlazan al padre los dos hijos.
		padre->claves[pos] = hijoIz->claves[hijoIz->numLlavesUsadas / 2];
		++padre->numLlavesUsadas;
		hijoIz->numLlavesUsadas = hijoIz->numLlavesUsadas / 2;
		padre->hijos[pos] = hijoIz;
		padre->hijos[pos + 1] = hijoDer;
		hijoDer->padre = padre;
	}

	// Inserta recursivamente asegurandose de que el nodo donde vaya a insertar no tenga el maximo de claves posibles.
	void inserta(NodoB<T> *padre, T & clave) {
		int i = padre->numLlavesUsadas;
		// Si el padre es un nodo hoja. Lo inserta en la posicion adecuada.
		if (padre->hijos[0] == nullptr) {
			while (i > 0 && padre->claves[i - 1] > clave) {
				padre->claves[i] = padre->claves[i - 1];
				--i;
			}
			padre->claves[i] = clave;
			++padre->numLlavesUsadas;
		}
		// Si el padre es un nodo intermedio, busca en que hijo lo tiene que insertar y se asegura que este hijo
		// tenga menos de numClaves nodos.
		else {
			while (i > 0 && padre->claves[i - 1] > clave) --i;
			if (padre->hijos[i]->numLlavesUsadas == numClaves) {
				separarHijo(padre, i);
				if (clave > padre->claves[i]) ++i;
			}
			inserta(padre->hijos[i], clave);
		}
	}

	// Elimina recursivamente la clave a partir de la raiz dada asegurandose siempre de no dejar menos claves de las minimas en cada nodo.
	void borra(NodoB<T> *raiz, T & clave) {
		int i = 0;
		while (i < raiz->numLlavesUsadas && raiz->claves[i] < clave) ++i;
		// Si esta en una hoja, se borra.
		if (i < raiz->numLlavesUsadas && raiz->claves[i] == clave && raiz->hijos[0] == nullptr) {
			for (int j = i; j < raiz->numLlavesUsadas - 1; ++j) {
				raiz->claves[j] = raiz->claves[j + 1];
				raiz->hijos[j] = raiz->hijos[j + 1];
			}
			raiz->hijos[raiz->numLlavesUsadas - 1] = raiz->hijos[raiz->numLlavesUsadas];
			--raiz->numLlavesUsadas;
		}
		// Si esta en un nodo intermedio, hay tres opciones.
		else if (i < raiz->numLlavesUsadas && raiz->claves[i] == clave && raiz->hijos[0] != nullptr) {
			NodoB<T> *hijoIz = raiz->hijos[i];
			NodoB<T> *hijoDer = raiz->hijos[i + 1];
			// Si el hijo izquierdo del elemento que queremos borrar tiene suficientes elementos, subimos el ultimo.
			if (hijoIz->numLlavesUsadas > minClaves) {
				raiz->claves[i] = hijoIz->claves[hijoIz->numLlavesUsadas - 1];
				borra(hijoIz, hijoIz->claves[hijoIz->numLlavesUsadas - 1]);
			}
			// Si el hijo derecho del elemento tiene suficientes elementos, subimos el primero.
			else if (hijoDer->numLlavesUsadas > minClaves) {
				raiz->claves[i] = hijoDer->claves[0];
				borra(hijoDer, hijoDer->claves[0]);
			}
			// Si ninguno de los hijos tiene suficientes elementos, estos se unen quitando asi la clave entre ellos dos.
			else {
				merge(raiz, i);
				// Se elimina la clave, ahora del hijo izquierdo que es donde la hemos movido.
				borra(hijoIz, clave);
			}
		}
		// Si no esta en este nodo, se coje el hijo del nodo donde este y se asegura que este hijo tenga minClaves + 1.
		else if (raiz->hijos[i] != nullptr) {
			NodoB<T> *hijo = raiz->hijos[i];
			// Se opera si el hijo tiene minClaves para mantener que tenga al menos minClaves + 1.
			if (hijo->numLlavesUsadas < minClaves + 1) {
				// Si tiene un hijo a la izquierda con al menos minClaves + 1, se mueve una clave de este al que estamos trabajando.
				if (i - 1 >= 0 && raiz->hijos[i - 1]->numLlavesUsadas > minClaves) {
					NodoB<T> *hijoAdj = raiz->hijos[i - 1];
					++hijo->numLlavesUsadas;
					for (int j = hijo->numLlavesUsadas - 1; j > 0; --j) {
						hijo->claves[j] = hijo->claves[j - 1];
						hijo->hijos[j + 1] = hijo->hijos[j];
					}
					hijo->hijos[1] = hijo->hijos[0];
					hijo->hijos[0] = hijoAdj->hijos[hijoAdj->numLlavesUsadas];
					hijo->claves[0] = raiz->claves[i - 1];
					raiz->claves[i - 1] = hijoAdj->claves[hijoAdj->numLlavesUsadas - 1];
					--hijoAdj->numLlavesUsadas;
				}
				// Si tiene un hijo a la derecha con al menos minClaves + 1, se mueve una clave de este al que estamos trabajando.
				else if (i + 1 <= raiz->numLlavesUsadas && raiz->hijos[i + 1]->numLlavesUsadas > minClaves) {
					NodoB<T> *hijoAdj = raiz->hijos[i + 1];
					++hijo->numLlavesUsadas;
					hijo->hijos[hijo->numLlavesUsadas] = hijoAdj->hijos[0];
					hijo->claves[hijo->numLlavesUsadas - 1] = raiz->claves[i + 1];
					raiz->claves[i + 1] = hijoAdj->claves[0];
					--hijoAdj->numLlavesUsadas;
					for (int j = 0; j < hijoAdj->numLlavesUsadas; ++j) {
						hijoAdj->claves[j] = hijoAdj->claves[j + 1];
						hijoAdj->hijos[j] = hijoAdj->hijos[j + 1];
					}
					hijoAdj->hijos[hijoAdj->numLlavesUsadas] = hijoAdj->hijos[hijoAdj->numLlavesUsadas + 1];
				}
				// Si no, ambos lados tienen minClaves.
				else {
					// Si hay un hijo a la izquierda, se une con este.
					if (i - 1 >= 0) {
						merge(raiz, i - 1);
					}
					// Si hay un hijo a la derecha (y no a la izquierda), se une con este.
					else if (i + 1 <= raiz->numLlavesUsadas) {
						merge(raiz, i);
					}
				}
			}
			borra(hijo, clave);
		}

	}

	// Funcion que une los el hijo izquierdo y derecho del nodo padre en la posicion i en un unico nodo (en el izquierdo)
	// y elimina la clave i del padre y el hijo derecho de i.
	void merge(NodoB<T> *raiz, int i) {
		NodoB<T> *hijoIz = raiz->hijos[i];
		NodoB<T> *hijoDer = raiz->hijos[i + 1];

		// Se unen el hijo izquierdo + la clave + el hijo derecho, todo en un nodo.
		hijoIz->numLlavesUsadas = 2 * minClaves + 1;
		hijoIz->claves[minClaves] = raiz->claves[i];
		for (int j = 0; j < minClaves; ++j) {
			hijoIz->claves[minClaves + 1 + j] = hijoDer->claves[j];
			hijoIz->hijos[minClaves + 1 + j] = hijoDer->hijos[j];
			if (hijoIz->hijos[minClaves + 1 + j] != nullptr) (hijoIz->hijos[minClaves + 1 + j])->padre = hijoIz;
		}
		hijoIz->hijos[hijoIz->numLlavesUsadas] = hijoDer->hijos[minClaves];
		if (hijoIz->hijos[hijoIz->numLlavesUsadas] != nullptr) (hijoIz->hijos[hijoIz->numLlavesUsadas])->padre = hijoIz;

		for (int j = i; j < raiz->numLlavesUsadas - 1; ++j) {
			raiz->claves[j] = raiz->claves[j + 1];
			raiz->hijos[j + 1] = raiz->hijos[j + 2];
		}
		--raiz->numLlavesUsadas;
		if (raiz == root && raiz->numLlavesUsadas == 0) {
			root = hijoIz;
			root->padre = nullptr;
			raiz = nullptr;
		}
	}

	// Funcion que busca recursivamente el valor pedido, recorre las claves de cada nodo para ver entre que valores esta,
	// si lo encuentra lo devuelve, si no, devuelve nullptr.
	T *buscar(NodoB<T> *raiz, T & clave) {
		if (raiz == nullptr)
			return nullptr;
		else {
			int i = 0;
			while (i < raiz->numLlavesUsadas && raiz->claves[i] < clave) ++i;
			if (i < raiz->numLlavesUsadas && raiz->claves[i] == clave)
				return &raiz->claves[i];
			else {
				return buscar(raiz->hijos[i], clave);
			}
		}
	}

};


#endif // ArbolB