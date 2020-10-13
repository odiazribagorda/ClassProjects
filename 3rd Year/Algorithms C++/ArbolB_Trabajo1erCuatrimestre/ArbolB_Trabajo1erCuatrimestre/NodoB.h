// Oscar Diaz Ribagorda (DG04)
// Clase Nodo de un arbol-B que tiene n claves con n+1 hijos.

#ifndef NodoB_
#define NodoB_

template <class T> class ArbolB;

template<class T>
class NodoB {
private:
	int numLlavesUsadas;	// Numero que indica el tamaño del nodo actual (en numero de claves).
	T *claves;				// Vector con las claves de este nodo.
	NodoB<T> *padre;		// Puntero al padre de este nodo.
	NodoB<T> **hijos;		// Puntero a un vector con los hijos de  este nodo.

	friend class ArbolB<T>;

public:
	// Constructor
	NodoB(int numClaves) {
		numLlavesUsadas = 0;
		claves = new T[numClaves];
		padre = NULL;
		hijos = new NodoB<T>* [numClaves + 1];
		for (int i = 0; i < numClaves + 1; ++i) hijos[i] = nullptr;
	}

	// Destructor
	~NodoB() {
		delete[] claves;
		delete[] hijos;
	}
};

#endif //NodoB_