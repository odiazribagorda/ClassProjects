// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "PriorityQueue.h"

using namespace std;

struct Usuario {
	int id;
	int p;
	int periodoOriginal;
};
bool operator<(Usuario const& u1, Usuario const& u2) {
	return (u1.p < u2.p) || (u1.p == u2.p && u1.id < u2.id);
}

int main() {
	int numUsuarios = 0;
	cin >> numUsuarios;
	while (numUsuarios != 0) {
		PriorityQueue<Usuario> pq;
		Usuario u;
		for (int i = 0; i < numUsuarios; ++i) {
			cin >> u.id >> u.periodoOriginal;
			u.p = u.periodoOriginal;
			pq.push(u);
		}
		int numConsultas = 0;
		cin >> numConsultas;
		for (int i = 0; i < numConsultas; ++i) {
			pq.pop(u);
			cout << u.id << '\n';
			u.p += u.periodoOriginal;
			pq.push(u);
		}
		cout << "----\n";
		cin >> numUsuarios;
	}

}