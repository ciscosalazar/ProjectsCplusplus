#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct T_hijos{
    string  nombre;
	int ced, ced_padre, edad;
};
struct T_padres{
	string nombre;
	int ced, telf;
	string direccion;
};
typedef T_padres _padres;
typedef T_hijos _hijos;
struct nodo_h{
	_hijos info;
	nodo_h* sig;
};
struct nodo_p{
	_padres info;
	nodo_p* sig;
};
typedef nodo_h* ptnodo_h;
typedef nodo_p* ptnodo_p;
ptnodo_h lista_h = NULL, Aux = NULL;
ptnodo_p lista_p = NULL;
// funciones
void INSERTAR_FIN(ptnodo_p &Lista, _padres Elem);
void INSERTAR_FIN(ptnodo_h &Lista, _hijos Elem);
void MOSTRAR_LISTA (ptnodo_p Lista);
void MOSTRAR_LISTA (ptnodo_h Lista);
void BORRAR(ptnodo_h &Lista);
void BORRAR(ptnodo_p &Lista);
int BUSCAR_ced(ptnodo_h Lista, int ced_h);
int BUSCAR_telf(ptnodo_p Lista, int ced_p);
ptnodo_h hijos_porced(ptnodo_h Lista, int ced_p);
int main() {
		string elem, num;
		int opc = 0, opc2 = 0, ced_h, ced_p, telf, ban = 0;
		ifstream A1;
        _padres registro_padre;
		_hijos registro_hijo;
		while(opc != 6){
			cout << "Menu de opciones\n";
			cout << "1.- Cargar datos\n";
			cout << "2.- Mostrar datos cargados\n";
			cout << "3.- Buscar el telefono de un padre conociendo la cedula de su hijo\n";
			cout << "4.- Buscar y mostrar los hijos de un padre usando su numero de cedula\n";
			cout << "5.- Opcion extra\n";
			cout << "6.- Salir\n";
			cin >> opc;
			system("cls");
			switch(opc){
				case 1:
				    // liberar memoria
                    if(lista_p != NULL)
                        BORRAR(lista_p);
                    if(lista_h != NULL)
                        BORRAR(lista_h);
					/*cargando los datos de los padres e hijos por separado,no combinar,
					ya que los registros son distintos, igual que los nodos*/
					A1.open("padres.txt");
					if(!A1){
						cout << "Error al abrir archivo padres\n";
						break;
					}
					getline(A1,registro_padre.nombre,'\t');
					A1>> registro_padre.ced;
					A1.ignore(1);
					A1>> registro_padre.telf;
					A1.ignore(1);
					getline(A1,registro_padre.direccion);
					INSERTAR_FIN(lista_p, registro_padre);
					while(A1.eof() == 0){
						getline(A1,registro_padre.nombre,'\t');
						A1>> registro_padre.ced;
						A1.ignore(1);
						A1>> registro_padre.telf;
						A1.ignore(1);
						getline(A1,registro_padre.direccion);
						INSERTAR_FIN(lista_p, registro_padre);
					}
					A1.close();
					// ahora se cargan los hijos
					A1.open("hijos.txt");
					if(!A1){
						cout << "Error al abrir archivo hijos\n";
						break;
					}
					getline(A1,registro_hijo.nombre,'\t');
					A1>> registro_hijo.ced;
					A1.ignore(1);
					A1>> registro_hijo.ced_padre;
					A1.ignore(1);
					A1>> registro_hijo.edad;
					A1.ignore(1);
					INSERTAR_FIN(lista_h, registro_hijo);
					while(A1.eof() == 0){
						getline(A1,registro_hijo.nombre,'\t');
						A1>> registro_hijo.ced;
						A1.ignore(1);
						A1>> registro_hijo.ced_padre;
						A1.ignore(1);
						A1>> registro_hijo.edad;
						A1.ignore(1);
						INSERTAR_FIN(lista_h, registro_hijo);
					}
					A1.close();
					ban = 1;
					break;
                case 2:
                    opc2 = 0;
					while (opc2 != 3){
                        system("color 70");
						cout << "menu de opciones mostrar\n";
						cout << "1.- Lista de hijos\n";
						cout << "2.- Lisa de padres\n";
						cout << "3.- Salir del modo mostrar\n";
						cin >> opc2;
						system("cls");
						switch(opc2){
							case 1:
								MOSTRAR_LISTA (lista_h);
								break;
							case 2:
								MOSTRAR_LISTA (lista_p);
								break;
                            case 3:
                                cout << "Salio de la modalidad mostrar\n";
                                system("color 0F");
                                break;
							default:
								cout << "Ingrese una opcion valida\n";
								break;
						}
					}
					break;
				case 3:
				    if (ban){
                        cout << "Ingrese la cedula del ni" << (char) 164 <<"o\n";
                        cin >> ced_h;
                        ced_p = BUSCAR_ced(lista_h, ced_h);
                            if(ced_p){
                                telf = BUSCAR_telf(lista_p, ced_p);
                                if(telf)
                                    cout << "el numero de telefono del padre es: " << telf << endl;
                            }else
                                cout << "no existe coincidencia\n";
                    }else
                        cout << "Se deben cargar los datos primero" << endl;
					break;
				case 4:
				    if (ban){
                        cout << "Ingrese la cedula del representante\n";
                        cin >> ced_p;
                        Aux = hijos_porced(lista_h, ced_p);
                        if(Aux != NULL){
                            MOSTRAR_LISTA(Aux);
                        }else
                            cout << "No hay coincidencia\n";
                    }else
                        cout << "Se deben cargar los datos primero" << endl;
					break;
				case 5:
					break;
				case 6:
					// liberar memoria
					BORRAR(Aux);
					BORRAR(lista_p);
					BORRAR(lista_h);
					break;
				default:
					cout << "Ingrese una opcion valida\n";
				break;
			}
		}
        return 0;
	}
void INSERTAR_FIN(ptnodo_p &Lista, _padres Elem){
    ptnodo_p A = Lista, NUEVO;
	NUEVO = new nodo_p;
	NUEVO -> info = Elem;
	NUEVO -> sig = NULL;
	if(Lista == NULL)
		Lista = NUEVO;
	else
	{	while (A -> sig != NULL)
			A = A -> sig;
		A -> sig = NUEVO;
	}
}
void INSERTAR_FIN(ptnodo_h &Lista, _hijos Elem){
    ptnodo_h A = Lista, NUEVO;
	NUEVO = new nodo_h;
	NUEVO -> info = Elem;
	NUEVO -> sig = NULL;
	if(Lista == NULL)
		Lista = NUEVO;
	else
	{	while (A -> sig != NULL)
			A = A->sig;
		A -> sig = NUEVO;
	}
}
void MOSTRAR_LISTA (ptnodo_p Lista){
	ptnodo_p A = Lista;
  	if (A != NULL){
		while( A != NULL){
			cout << setw(15) << left << A -> info.nombre;
			cout << setw(9) << A -> info.ced;
			cout << setw(12) << A -> info.telf;
			cout << setw(20) << A -> info.direccion <<endl;
   			A = A -> sig;
		}
	}
	else cout << "Lista Vacia\n";
}
void MOSTRAR_LISTA (ptnodo_h Lista){
	ptnodo_h A = Lista;
  	if (A != NULL){
		while( A != NULL){
			cout << setw(15) << left << A -> info.nombre;
			cout << setw(9) << A -> info.ced;
			cout << setw(9) << A -> info.ced_padre;
			cout << setw(4) << A -> info.edad <<endl;
   			A = A -> sig;
		}
	}
	else cout << "Lista Vacia\n";
}
void BORRAR(ptnodo_p &Lista){
	ptnodo_p Aux = Lista;
	if(Aux != NULL){
			Lista = Lista -> sig;
		delete Aux;
		BORRAR(Lista);
	}
}
void BORRAR(ptnodo_h &Lista){
	ptnodo_h Aux = Lista;
	if(Aux != NULL){
			Lista = Lista -> sig;
		delete Aux;
		BORRAR(Lista);
	}
}
int BUSCAR_ced(ptnodo_h Lista, int ced_h){
    ptnodo_h A = Lista;
	if(A != NULL)
	{	while(A -> info.ced != ced_h && A -> sig != NULL)
            A = A -> sig;
		if(A -> info.ced == ced_h)
            return A -> info.ced_padre;
		else
		return 0;
	}
	else
	{	cout<<"Lista de hijos vacia\n" << endl;
		return 0;
	}
}
ptnodo_h hijos_porced(ptnodo_h Lista, int ced_p){
    ptnodo_h A = Lista, B = NULL;
    _hijos registro;
	if(A != NULL){
            while(A != NULL){
                if(A -> info.ced_padre == ced_p){
                    registro = A -> info;
                    INSERTAR_FIN(B, registro);
                }
                A = A -> sig;
            }
            return B;
	}else{
	    cout<<"Lista de hijos vacia\n" << endl;
		return NULL;
	}
}
int BUSCAR_telf(ptnodo_p Lista, int ced_p){
    ptnodo_p A = Lista;
	if(A != NULL)
	{	while(A -> info.ced != ced_p && A -> sig != NULL)
            A = A -> sig;
		if(A -> info.ced == ced_p)
            return A -> info.telf;
		else
            return 0;
	}
	else
	{	cout<<"Lista de padres vacia\n";
		return 0;
	}
}
