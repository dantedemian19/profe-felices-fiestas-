#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <clocale>

using namespace std;

struct productos {
	int cod = 0;
	int stock = 0;
	int precio = 0;
	productos* sig = NULL;
	productos* ant = NULL;
};

typedef productos* node;

node startdepo = NULL;
string namedepo = "deposit.dat";

void wait() {
	Sleep(2000);
};
void pause() {
	system("pause");
};
void cls() {
	system("cls");
};
void read() {// lee un archivo binario y lo ingresa en memoria dinamica
	fstream file;// sirve para abrir el archivo
	node dat = NULL;// datos anteriores
	node p = NULL;// donde voy a guardar lo leido
	node z = NULL;// donde almaceno en memoria lo leido
	file.open(namedepo, ios::binary | ios::in);
	if (file.fail()) {

	}
	else {
		while (file.is_open()) {
			p = new(struct productos);
			while (!file.eof()) {
				file.read(reinterpret_cast<char*>(&p->cod), sizeof(&p->cod));
				file.read(reinterpret_cast<char*>(&p->stock), sizeof(&p->stock));
				file.read(reinterpret_cast<char*>(&p->precio), sizeof(&p->precio));
				cout << p;
				pause();
				if (p->cod != 0) {
					z = p;
					if (startdepo != NULL) {
						dat->sig = z;
						z->ant = dat;
						z->sig = NULL;
					}
					else {
						startdepo = z;
					}
					dat = z;
				}
			}
			file.close();
		}
	}

};
void write(node &p) {// escribe el archivo
	fstream file;// sirve para abrir el archivo
	file.open(namedepo, ios::binary | ios::app | ios::out);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(&p->cod), sizeof(&p->cod));
		file.write(reinterpret_cast<char*>(&p->stock), sizeof(&p->stock));
		file.write(reinterpret_cast<char*>(&p->precio), sizeof(&p->precio));
	}
	file.close();
};
void writefin() {// escribe el archivo
	fstream file;// sirve para abrir el archivo
	node p= startdepo;
	file.open(namedepo, ios::binary | ios::ate | ios::out);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(&p->cod), sizeof(&p->cod));
		file.write(reinterpret_cast<char*>(&p->stock), sizeof(&p->stock));
		file.write(reinterpret_cast<char*>(&p->precio), sizeof(&p->precio));
	}
	file.close();
};
void movim() {
	cout << "1. ingresar codigo de movimiento \n";
	cout << "2. ingresar \n";
	cout << "3. Consultar stock de un articulo \n";
	cout << "4. Salir \n";
};
void menu() {
	read();
	int x = 0;
	while (x != 4) {
		cout << "1. Registrar compra y/o venta \n";
		cout << "2. Consultar precio de un articulo \n";
		cout << "3. Consultar stock de un articulo \n";
		cout << "4. Salir \n";
		cin >> x;
		switch (x) {
		case 1:
			cls();
			movim();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			cout << "Que tenga un buen dia :)";
			break;
		}
		writefin();
	}
};
void crear() {
		int i = 0;
		node dat = new(struct productos);
		fstream file;// sirve para abrir el archivo
		file.open(namedepo, ios::binary | ios::ate | ios::out);
		file.close();
		while (i < 30) {
			cout << i + 1 << "|_____________________ \n";
			dat->cod = i + 1;
			cout << "stock: ";
			cin >> dat->stock;
			cout << "precio por unidad: ";
			cin >> dat->precio;
			file.open(namedepo, ios::binary | ios::app | ios::out);
			if (file.is_open()) {
				file.write(reinterpret_cast<char*>(&dat->cod), sizeof(&dat->cod));
				file.write(reinterpret_cast<char*>(&dat->stock), sizeof(&dat->stock));
				file.write(reinterpret_cast<char*>(&dat->precio), sizeof(&dat->precio));
			}
			file.close();
			i += 1;
		}
};
int main()
{
	setlocale(LC_CTYPE, "Spanish");
	crear();
}

// casi programa creado por Agustin Garone, Dante Alfonso y Lucas Ñore 