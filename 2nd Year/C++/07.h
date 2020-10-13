
#include "deque_eda.h"
#include <iostream>
using namespace std;

template <class T>
class Extension : public deque<T> {
	using Nodo = typename deque<T>::Nodo;

public:

	void invierte() {
		// Tan solo invertimos el orden de siguiente y anterior.
		Nodo* act = this->fantasma->sig;
		while (act != this->fantasma) {
			Nodo* aux = act->sig;
			act->sig = act->ant;
			act->ant = aux;
			act = aux;
		}
		//Para cambiar el fantasma.
		Nodo* aux = act->sig;
		act->sig = act->ant;
		act->ant = aux;
	}

	void mostrar() {
		// Se muestra primero el primero tras el fantasma y luego los siguientes hasta que se encuentre otra vez el fantasma.
		if (this->nelems > 0) {
			cout << this->fantasma->sig->elem;
			Nodo* aux = this->fantasma->sig->sig;
			while (aux != this->fantasma) {
				cout << ' ' << aux->elem;
				aux = aux->sig;
			}
		}
		cout << '\n';
	}
};