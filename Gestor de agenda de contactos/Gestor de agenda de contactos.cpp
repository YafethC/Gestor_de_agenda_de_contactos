#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------- Estructuras ----------

// Contact
// Por qué: representa la unidad de información en la agenda (modelo de datos).
// Qué hace: almacena nombre, teléfono y email de un contacto.
struct Contact {

	string name;
	string phone;
	string email;

};

// Operation
// Por qué: llevar un historial simple de acciones realizadas (registro de cambios).
// Qué hace: guarda el tipo de operación ("ADD" o "DELETE") y el contacto afectado.
struct Operation {

	string type; // "ADD" o "DELETE"
	Contact contact;

};

// ListNode
// Por qué: implementar una lista enlazada simple usada para eliminar por índice
//         sin depender exclusivamente de operaciones costosas en vector.
// Qué hace: nodo de lista que encapsula un Contact y un puntero al siguiente nodo.
struct ListNode {

	Contact data;
	ListNode* next;
	ListNode(const Contact& c) : data(c), next(NULL) {}

};

// BSTNode
// Por qué: facilitar un recorrido ordenado (inorden) por nombre sin alterar el vector
// Qué hace: nodo de árbol binario de búsqueda que contiene un Contact y punteros a hijos.
struct BSTNode {

	Contact data;
	BSTNode* left;
	BSTNode* right;
	BSTNode(const Contact& c) : data(c), left(NULL), right(NULL) {}

};

int main()
{
    std::cout << "Hello World!\n";
}