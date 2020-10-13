//
//  conjunto.h
//

#ifndef conjunto_h
#define conjunto_h

#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move

template <class T>
class set {
public:
	set(size_t tam = TAM_INICIAL); // constructor
	set(set<T> const& other); // constructor por copia
	set<T> & operator=(set<T> const& other); // operador de asignación
	~set(); // destructor
	void insert(T e, int k);
	bool contains(T e) const;
	void erase(T e);
	bool empty() const;
	size_t size() const;
	T getMinor() const;
	void eraseMinor();
private:
	const static size_t TAM_INICIAL = 8;
	size_t contador;
	size_t capacidad;
	T * datos;
	void amplia();
	void libera();
	void copia(set<T> const& other);
	void buscar(T const& cosa, int & pos, int ini, int fin);
};

template <class T>
set<T>::set(size_t tam) : contador(0), capacidad(tam), datos(new T[capacidad]) {}

template <class T>
set<T>::~set() { libera(); }

template <class T>
void set<T>::libera() { delete[] datos; datos = nullptr; }

/** Constructor por copia */
template <class T>
set<T>::set(set<T> const& other) {
	copia(other);
}

/** Operador de asignación */
template <class T>
set<T> & set<T>::operator=(set<T> const& other) {
	if (this != &other) {
		libera();
		copia(other);
	}
	return *this;
}

template <class T>
void set<T>::copia(set<T> const& other) {
	capacidad = other.capacidad;
	contador = other.contador;
	datos = new T[capacidad];
	for (size_t i = 0; i < contador; ++i)
		datos[i] = other.datos[i];
}

template <class T>
void set<T>::buscar(T const& cosa, int & pos, int ini, int fin) {
	if (ini == fin) {
		pos = ini;
	}
	else {
		int mitad = (ini + fin) / 2;
		if (cosa > datos[mitad]) buscar(cosa, pos, mitad + 1, fin);
		else if (cosa < datos[mitad]) buscar(cosa, pos, ini, mitad);
		else pos = mitad;
	}
}

template <class T>
void set<T>::insert(T e, int k) {
	if (!contains(e)) {
		if (contador == 0) {
			datos[0] = e;
			++contador;
		}
		else if (contador < k || e > getMinor()) {
			if (contador == capacidad)
				amplia();

			int pos = 0;
			buscar(e, pos, 0, contador - 1);
			if (datos[pos] < e) ++pos;

			if (contador < k) {
				for (int i = contador - 1; i >= pos; --i) {
					datos[i + 1] = datos[i];
				}
				datos[pos] = e;
				++contador;
			}
			else {
				--pos;
				for (int i = 0; i < pos; ++i) {
					datos[i] = datos[i + 1];
				}
				datos[pos] = e;
			}
		}
	}
}

template <class T>
bool set<T>::contains(T e) const {
	size_t i = 0;
	while (i < contador && datos[i] != e)
		++i;
	return i < contador;
}

template <class T>
void set<T>::amplia() {
	T * nuevos = new T[2 * capacidad];
	for (size_t i = 0; i < capacidad; ++i)
		nuevos[i] = std::move(datos[i]);
	delete[] datos;
	datos = nuevos;
	capacidad *= 2;
}

template <class T>
void set<T>::erase(T e) {
	size_t i = 0;
	while (i < contador && datos[i] != e)
		++i;
	if (i < contador) {
		for (int j = i; j < contador - 1; ++j)
			datos[j] = datos[j + 1];
		--contador;
	}
	else
		throw std::domain_error("El elemento no esta");
}


template <class T>
bool set<T>::empty() const {
	return contador == 0;
}

template <class T>
size_t set<T>::size() const {
	return contador;
}

template <class T>
T set<T>::getMinor() const {
	if (contador > 0) return datos[0];
	else throw std::domain_error("No hay elementos");
}

template <class T>
void set<T>::eraseMinor() {
	if (contador > 0) {
		for (int i = 0; i < contador - 1; ++i)
			datos[i] = datos[i + 1];
		--contador;
	}
	else throw std::domain_error("No hay elementos");
}

#endif // conjunto_h