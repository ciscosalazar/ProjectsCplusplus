#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
//declaracion------------------------------------
struct _dato{
	int n;
	char palabra[25];
};
typedef _dato dato;
struct nodo{
	dato info;
	nodo *ant, *sig;
};
typedef nodo *ptnodo;
ptnodo lista_d = NULL;
//funiones----------------------------------------
void INSERTAR_FIN(ptnodo &Ld, dato X);
ptnodo ULTIMO(ptnodo &Ld);
void MOSTRAR_LISTA (ptnodo &Lista);
void BORRAR_LISTA(ptnodo &Ld);
void buscar_pal(ptnodo Ld, char pal[]);
using namespace std;
int main(){
	ifstream A1;
	char aux[25], let, pal[25];
	int i, flag = 0, cont = 0,opc = 0, ban = 0;
	dato regis;
	while(opc != 6){
			cout << "Menu de opciones\n";
			cout << "1.- Cargar un archivo de texto\n";
			cout << "2.- Mostrar la lista de palabras\n";
			cout << "3.- Agregar datos\n";
			cout << "4.- Buscar palabra\n";
			cout << "5.- Opcion extra\n";
			cout << "6.- Salir\n";
			cin >> opc;
			system("cls");
			switch(opc){
				case 1:
				    cont = 0;
				    if(lista_d != NULL)
                        BORRAR_LISTA(lista_d);
					A1.open("texto.txt");
					if (!A1){
						cout << "Problemas con archivo\n";
						break;
					}
					A1.get(let);
					while(! A1.eof()){
						i = 0;
						flag = 0;
						while(isalpha(let)){
							aux[i] = let;
							A1.get(let);
							i ++;
							flag = 1;
						}
						if(flag == 1){
							aux [i] = '\0';
							cont ++;
							regis.n = cont; strcpy(regis.palabra,aux);
							INSERTAR_FIN(lista_d, regis);
						}
						A1.get(let);
					}
					ban = 1;
					A1.close();
					break;
				case 2:
				    if (ban){
                        MOSTRAR_LISTA (lista_d);
                    }else
                                cout << "Se deben cargar los datos primero\n";
					break;
				case 3:
					break;
				case 4:
                    cout << "ingrese la palabra a buscar\n";
                    cin.ignore(1);
                    cin.getline(pal, 25);
                    buscar_pal(lista_d, pal);
					break;
				case 5:
					break;
				case 6:
					if(lista_d != NULL)
                        BORRAR_LISTA(lista_d);
					break;
				default:
					cout << "Ingrese una opcion valida\n";
				break;
			}
	}
    return 0;
}
void INSERTAR_FIN(ptnodo &Ld, dato X){
	ptnodo NUEVO, U;
	NUEVO = new(nodo);
	NUEVO -> info = X;
	NUEVO -> sig = NULL; NUEVO -> ant = NULL;
	if(Ld == NULL) Ld = NUEVO;
	else
	{	U = ULTIMO(Ld);
		U -> sig = NUEVO;
		NUEVO -> ant = U;
	}
}
ptnodo ULTIMO(ptnodo &Ld){
	ptnodo A = Ld;
	if(A != NULL){
		while (A -> sig != NULL)
			A = A -> sig;
		return  A;
}else {
		cout << "Lista vacia\n";
		return NULL;	}
}
void MOSTRAR_LISTA (ptnodo &Lista){
	ptnodo A = Lista;
  	if (A != NULL){
   		while(A != NULL){
			cout << setw(3) << A -> info.n << setw(20) << A -> info.palabra << endl;
   			A = A -> sig;
		}
	}
	else cout << "Lista vacia\n";
}
void BORRAR_LISTA(ptnodo &Ld){
    ptnodo P = Ld;
	if(Ld != NULL){
        if(P == Ld && P -> sig == NULL)
			Ld = NULL;
		else{
            Ld = Ld -> sig;
            Ld -> ant = NULL;
        }
        delete(P);
        BORRAR_LISTA(Ld);
        }
}
void buscar_pal(ptnodo Ld, char pal[]){
    ptnodo A = Ld, P[15];
    int b = 0, a = 4, i = 0;
    for(i = 0; i < b; i++)
        P[i] = NULL;
    if(A != NULL){
        while(A != NULL){
                a = strcmp(pal, A -> info.palabra);
            if(!a){
                b ++;
                P[i] = A;
            i++;
            }
            A = A -> sig;
        }
    }else{
        cout << "La lista esta vacia\n";
        }
    if (b){
            cout << "Palabra encontrada\n";
            for(i = 0; i < b; i++){
                cout << setw(3) << P[i] -> info.n << setw(20) << P[i] -> info.palabra << endl;
                P[i] = NULL;
            }
    }else
        cout << "No hay coincidencia\n";
}
