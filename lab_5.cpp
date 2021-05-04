#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;
struct T1{
    int N;
    string exp, grupo, nombre;
};
typedef T1 _T1;
struct nodo{
	_T1 info;
	nodo* sig;
};
typedef nodo* ptnodo;
ptnodo pila1, pila2;
// funciones
void push(ptnodo &pila, T1 &elem);
void cima(ptnodo &pila,string &elem);
void pop(ptnodo &pila, T1 &elem);
void mostrar(T1 *ptregistro);
void borrar_pila(ptnodo &pila);
int main() {
		string elem, cim;
		int opc, i = 0;
		ifstream A1;
        T1 registro, *ptregistro = NULL;
		while(opc != 6){
			cout << "Menu de opciones\n";
			cout << "1.- Cargar datos\n";
			cout << "2.- Mostrar los datos cargados\n";
			cout << "3.- Ordenar datos por expedientes\n";
			cout << "4.- Cargar datos en una pila\n";
			cout << "5.- Opcion adicional\n";
			cout << "6.- Salir\n";
			cin >> opc;
			system("cls");
			switch(opc){
				case 1:
				if(ptregistro != NULL){// liberar memoria
                                 delete[] ptregistro;
                                borrar_pila(pila1);
				borrar_pila(pila2);
                }
				ptregistro = new T1[27];
				A1.open("lista3.txt");
				if(!A1){
                cout << "Error al abrir archivo";
				}
				A1>> ptregistro -> N;
				A1.ignore(1);
				getline(A1,ptregistro -> exp,'\t');
				getline(A1,ptregistro -> grupo,'\t');
				getline(A1,ptregistro -> nombre);
				i = 1;
				while(A1.eof() == 0){
					A1>>ptregistro[i].N;
					A1.ignore(1);
					getline(A1,ptregistro[i].exp,'\t');
					getline(A1,ptregistro[i].grupo,'\t');
					getline(A1,ptregistro[i].nombre);
					i++;
				}
				A1.close();
				break;
                case 2:
				mostrar(ptregistro);
				break;
				case 3:
				    if(pila1 != NULL)
                                        borrar_pila(pila1);
				push(pila1, ptregistro[0]);
				i = 1;
				while (i < 27){
					elem = ptregistro[i].exp;
					cima(pila1, cim);
					while(pila1 !=NULL && cim < elem){
						pop(pila1, registro);
						push(pila2, registro);
						cima(pila1, cim);
					}
					push(pila1, ptregistro[i]);
					while(pila2 != NULL){
						pop(pila2, registro);
						push(pila1, registro);
					}
					i++;
				}
				i = 0;
				while(pila1 != NULL){
					pop(pila1, ptregistro[i]);
					i++;
				}
				mostrar(ptregistro);
				break;
				case 4:
				    if(pila1 != NULL)
                        borrar_pila(pila1);
                    for(i = 26; i >= 0; i--)
                        push(pila1, ptregistro[i]);
                    cout << "se muestran los datos almacenados en la pila\n\n";
                    mostrar(ptregistro);
				break;

				case 5:
                                if(pila1 != NULL)
                                        borrar_pila(pila1);
                                if(pila2 != NULL)
                                borrar_pila(pila2);
				i = 26;
				while (i >= 0){
					elem = ptregistro[i].grupo;
                                        if(elem == "G2")
                                        push(pila1, ptregistro[i]);
                                        cima(pila1, cim);
                                        i--;
                                }
                                i = 0;
                                while (i < 27) {
                                elem = ptregistro[i].grupo;
                                        if(elem == "G1")
                                        push(pila2, ptregistro[i]);
                                        cima(pila2, cim);
                                        i++;
                                }
                                while(pila2 != NULL){
						pop(pila2, registro);
						push(pila1, registro);
                                }


				i = 0;
				while(pila1 != NULL){
					pop(pila1, ptregistro[i]);
					i++;
				}
				mostrar(ptregistro);
				break;
				case 6:
				// liberar memoria
				delete[] ptregistro;
				borrar_pila(pila1);
				borrar_pila(pila2);
				break;
				default:
				cout << "Ingrese una opcion valida \n\n";
				break;
			}
		}
        return 0;
	}
void push(ptnodo &pila,T1 &elem){
	ptnodo nuevo;
	nuevo = new(nodo);
	nuevo -> info = elem;
	nuevo -> sig = NULL;
	if(pila == NULL)
		pila = nuevo;
	else{
		nuevo -> sig = pila;
		pila = nuevo;
	}
}
void cima(ptnodo &pila,string &elem){
	if(pila != NULL)
		elem = pila -> info.exp;
}
void pop(ptnodo &pila, T1 &elem){
	ptnodo Aux = pila;
	if(Aux != NULL){
		pila = pila -> sig;
		elem = Aux -> info;
		delete(Aux);
	}else{
		cout << "error popa" << endl;}
}
void mostrar(T1 *ptregistro){
	for(int i = 0; i < 27; i++){
		cout << setw(3) << left <<ptregistro[i].N;
		cout << setw(13) << ptregistro[i].exp;
		cout << setw(4) << ptregistro[i].grupo;
		cout << setw(24) << ptregistro[i].nombre <<endl;
				}
}
void borrar_pila(ptnodo &pila){
    T1 elem;
    while(pila != NULL)
        pop(pila, elem);
    }
