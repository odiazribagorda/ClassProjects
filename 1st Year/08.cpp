// Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <vector>

using namespace std;

// Tipo definido para guardar los usuarios dados.
struct tUsuarios {
	int identificador;
	int periodo;
	int suma;
};

// Sobrecarga del operador mayor(>) para poder comparar usuarios teniendo en cuenta la suma de periodos y el identificador.
bool operator>(tUsuarios usuario1, tUsuarios usuario2) {
	return (usuario1.suma > usuario2.suma) || (usuario1.suma == usuario2.suma 
		&& usuario1.identificador > usuario2.identificador);
}

// Funcion que lee un numero determinado de usuarios en un vector de usuarios. (Asigna el periodo a la suma inicial).
void leer(vector<tUsuarios> & listaPeriodos, int numUsuarios) {
	tUsuarios usuario;

	for (int i = 0; i < numUsuarios; ++i) {
		cin >> usuario.identificador >> usuario.periodo;
		usuario.suma = usuario.periodo;
		listaPeriodos.push_back(usuario);
	}
}

/* Funcion que ordena todos los datos de un vector de usuarios de menor periodo a mayor
	y en caso de ser iguales de menor a mayor identificador. */
void ordenarLista(vector<tUsuarios> & listaPeriodos) {
	int puntero = 0;
	tUsuarios usuarioAux;

	for (int i = 1; i < listaPeriodos.size(); ++i) {
		usuarioAux = listaPeriodos[i];
		puntero = i;
		while (puntero > 0 && listaPeriodos[puntero - 1] > usuarioAux) {
			listaPeriodos[puntero] = listaPeriodos[puntero - 1];
			--puntero;
		}
		listaPeriodos[puntero] = usuarioAux;
	}
}

// Funcion que ordena tan solo el ultimo elemento añadido al vector de la misma manera que ordenarLista pero solo con el ultimo.
void ordenarUltimo(vector<tUsuarios> & listaPeriodos) {
	int puntero = 0;
	tUsuarios usuarioAux;

		usuarioAux = listaPeriodos[listaPeriodos.size() - 1];
		puntero = listaPeriodos.size() - 1;
		while (puntero > 0 && listaPeriodos[puntero - 1] > usuarioAux) {
			listaPeriodos[puntero] = listaPeriodos[puntero - 1];
			--puntero;
		}
		listaPeriodos[puntero] = usuarioAux;
}

int main() {
	int numUsuarios = 0, numEnvios = 0;
	tUsuarios usuario;
	
	cin >> numUsuarios;

	while (numUsuarios != 0) {
		vector<tUsuarios> listaPeriodos;
		leer(listaPeriodos, numUsuarios);
		ordenarLista(listaPeriodos);
		cin >> numEnvios;

		/* Se escribe el primer elemento de la lista ordenada que sera el menor de todos. Despues añade el siguiente envio
			de ese usuario al vector porque es el unico que puede ser menor que el segundo usuario. Por ultimo, en un bucle,
			se ordena el ultimo elemento de la lista y se saca el siguiente usuario de la lista. Se vuelve a añadir el siguiente
			envio de este usuario que es de nuevo el unico que puede ser menor que el siguiente que toca sacar, y asi hasta que
			se completen el numero de envios. */
		cout << listaPeriodos[0].identificador << '\n';
		usuario = listaPeriodos[0];
		usuario.suma += usuario.periodo;
		listaPeriodos.push_back(usuario);
		for (int i = 1; i < numEnvios; ++i) {
			ordenarUltimo(listaPeriodos);
			cout << listaPeriodos[i].identificador << '\n';
			usuario = listaPeriodos[i];
			usuario.suma += usuario.periodo;
			listaPeriodos.push_back(usuario);
		}

		cout << "----\n";

		cin >> numUsuarios;
	}

	return 0;
}