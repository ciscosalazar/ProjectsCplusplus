#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string.h>
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
ptnodo cola[5];
// funciones
int ultimo_num(string n);
void popcola_todo(ptnodo &cola, T1 &elem);
void pushcola(ptnodo &cola,T1 &elem);
void cima_cola(ptnodo &frente,string &elem);
void popcola(ptnodo &cola, T1 &elem);
void mostrar_cola(ptnodo &cola, T1 registro);
void borrar_cola(ptnodo &cola);
int main() {
		string elem, num;
		int opc = 0, i = 0, opc2 = 0, res;
		ifstream A1;
        T1 registro, *ptregistro = NULL;
		while(opc != 5){
			cout << "Menu de opciones\n";
			cout << "1.- Cargar datos\n";
			cout << "2.- Mostrar una cola especifica\n";
			cout << "3.- Vaciar arreglo, mostrando datos que salen\n";
			cout << "4.- Opcion adicional\n";
			cout << "5.- Salir\n";
			cin >> opc;
			system("cls");
			switch(opc){
				case 1:
					if(ptregistro != NULL)// liberar memoria
						delete[] ptregistro;
					for(i = 0; i < 5; i++)
						borrar_cola(cola[i]);
					ptregistro = new T1[27];
					A1.open("lista3.txt");
					if(!A1){
					cout << "Error al abrir archivo\n";
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
					for(i = 0; i < 27; i++){
                            num = ptregistro[i].exp[10];
					   res = ultimo_num(num);
						switch(res){
							case 0: case 1:
							pushcola(cola[0], ptregistro[i]);
							break;
							case 2: case 3:
							pushcola(cola[1], ptregistro[i]);
							break;
							case 4: case 5:
							pushcola(cola[2], ptregistro[i]);
							break;
							case 6: case 7:
							pushcola(cola[3], ptregistro[i]);
							break;
							case 8: case 9:
							pushcola(cola[4], ptregistro[i]);
							break;
						}
					}
					break;
                case 2:
                    opc2 = 0;
					while (opc2 != 6){
						cout << "\nmenu de opciones mostrar\n" << endl;
						cout << "1.- cola del dia lunes\n";
						cout << "2.- cola del dia martes\n";
						cout << "3.- cola del dia miercoles\n";
						cout << "4.- cola del dia jueves\n";
						cout << "5.- cola del dia viernes\n";
						cout << "6.- salir del modo mostrar\n";
						cin >> opc2;
						system("cls");
						switch(opc2){
							case 1:
								mostrar_cola(cola[0], registro);
								break;
							case 2:
								mostrar_cola(cola[1], registro);
								break;
							case 3:
								mostrar_cola(cola[2], registro);
								break;
							case 4:
								mostrar_cola(cola[3], registro);
								break;
							case 5:
								mostrar_cola(cola[4], registro);
								break;
                            case 6:
                                cout << "salio de la modalidad mostrar\n" << endl;
                                break;
							default:
								cout << "ingrese una opcion valida\n\n";
						}
					}
					break;
				case 3:
				    i = 0;
				    while(i < 5){
						mostrar_cola(cola[i], registro);
						popcola_todo(cola[i], registro);
						i++;
					}
					break;
				case 4:
					break;
				case 5:
					// liberar memoria
					delete[] ptregistro;
					for(i = 0; i < 5; i++)
						borrar_cola(cola[i]);
					break;
				default:
					cout << "Ingrese una opcion valida \n\n";
				break;
			}
		}
        return 0;
	}
void pushcola(ptnodo &cola,T1 &elem){
	ptnodo nuevo, Aux = cola;
	nuevo = new(nodo);
	nuevo -> info = elem;
	nuevo -> sig = NULL;
	if(cola == NULL)
		cola = nuevo;
	else{
		while(Aux -> sig != NULL)
			Aux = Aux -> sig;
		Aux -> sig = nuevo;
	}
}
void cima_cola(ptnodo &frente,string &elem){
	if(cola != NULL)
		elem = frente -> info.exp;
}
void popcola(ptnodo &cola, T1 &elem){
	ptnodo Aux = cola;
	if(cola != NULL){
		cola = cola -> sig;
		elem = Aux -> info;
		delete(Aux);
	}else{
		cout << "error popc_t\n" << endl;}
}
void popcola_todo(ptnodo &cola, T1 &elem){
	ptnodo Aux = cola;
	if(cola != NULL){
            while (cola != NULL){
		cola = cola -> sig;
		elem = Aux -> info;
            }
		delete(Aux);
	}else{
		cout << "error popc\n" << endl;}
}
void mostrar_cola(ptnodo &cola, T1 registro){
	ptnodo Aux1 = cola;
	if(Aux1 != NULL){
            registro = Aux1 -> info;
        while(Aux1 != NULL){
            registro = Aux1 -> info;
        cout << setw(3) << left <<registro.N;
        cout << setw(13) << registro.exp;
        cout << setw(4) << registro.grupo;
        cout << setw(24) << registro.nombre <<endl;
        Aux1 = Aux1 -> sig;
		}
		delete Aux1;
	}else
		cout << "cola vacia\n\n";
}
void borrar_cola(ptnodo &cola){
    T1 elem;
    while(cola != NULL)
        popcola_todo(cola, elem);
}
int ultimo_num(string n){
    if(n == "0")
        return 0;
    if(n == "1")
        return 1;
    if(n == "2")
        return 2;
    if(n == "3")
        return 3;
    if(n == "4")
        return 4;
    if(n == "5")
        return 5;
    if(n == "6")
        return 6;
    if(n == "7")
        return 7;
    if(n == "8")
        return 8;
    if(n == "9")
        return 9;
    }
