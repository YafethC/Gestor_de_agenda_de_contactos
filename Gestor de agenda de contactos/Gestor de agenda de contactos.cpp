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

// ---------- Utilidades ----------

// toLowerSimple
// Por qué: normalizar cadenas para comparaciones case-insensitive de forma simple.
// Qué hace: devuelve una copia en minúsculas de la cadena de entrada.
string toLowerSimple(const string& s) {

	string r = s;
	for (size_t i = 0; i < r.size(); ++i) {
		if (r[i] >= 'A' && r[i] <= 'Z') r[i] = char(r[i] + ('a' - 'A'));
	}
	return r;

}

// clearScreen
// Por qué: mejorar experiencia de consola limpiando la pantalla entre menús.
// Qué hace: intenta limpiar con secuencia ANSI y luego imprime varias líneas.
void clearScreen() {

	// Secuencia ANSI (funciona en muchas consolas). Luego fallback de nuevas líneas.
	cout << "\x1B[2J\x1B[H";
	for (int i = 0; i < 30; ++i) cout << '\n';

}

// waitEnter
// Por qué: pausa la ejecución hasta que el usuario presione ENTER para ver mensajes.
// Qué hace: imprime un mensaje y lee una línea vacía.
void waitEnter() {

	cout << "\nPresione ENTER para continuar...";
	string tmp;
	getline(cin, tmp);

}

// readLinePrompt
// Por qué: encapsula la lectura de una línea con prompt para evitar repetir código.
// Qué hace: muestra el prompt y devuelve la línea ingresada por el usuario.
string readLinePrompt(const string& prompt) {

	cout << prompt;
	string s;
	getline(cin, s);
	return s;

}

// parseIntNonNeg
// Por qué: validar entradas numéricas simples (índices/opciones) sin excepciones.
// Qué hace: intenta parsear una cadena como entero no negativo; devuelve true si OK
//           y coloca el valor en out.
bool parseIntNonNeg(const string& s, int& out) {

	int n = 0;
	size_t i = 0;
	// omitir espacios iniciales
	while (i < s.size() && (s[i] == ' ' || s[i] == '\t')) ++i;
	if (i == s.size()) return false;
	for (; i < s.size(); ++i) {

		char c = s[i];
		if (c < '0' || c > '9') return false;
		n = n * 10 + (c - '0');
	}

	out = n;
	return true;

}

// ---------- Ordenamientos ----------

// bubbleSortByName
// Por qué: ordenar por nombre de forma estable y simple para demostración/pequeños datos.
// Qué hace: aplica bubble sort sobre el vector usando comparación case-insensitive.
void bubbleSortByName(vector<Contact>& arr) {

	int n = (int)arr.size();
	for (int i = 0; i < n - 1; ++i) {
		bool swapped = false;
		for (int j = 0; j < n - 1 - i; ++j) {

			if (toLowerSimple(arr[j].name) > toLowerSimple(arr[j + 1].name)) {

				Contact tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
				swapped = true;
			}
		}
		if (!swapped) break; // optimización: si no hubo intercambio, ya está ordenado
	}
}

// selectionSortByPhone
// Por qué: ordenar por teléfono usando selección; simple y determinista.
// Qué hace: selection sort usando el campo phone como clave.
void selectionSortByPhone(vector<Contact>& arr) {

	int n = (int)arr.size();
	for (int i = 0; i < n - 1; ++i) {

		int minIdx = i;
		for (int j = i + 1; j < n; ++j)
			if (arr[j].phone < arr[minIdx].phone) minIdx = j;
		if (minIdx != i) {
			Contact tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
		}
	}
}

// ---------- Búsquedas ----------

// linearSearchByName
// Por qué: búsqueda directa útil cuando los datos no están ordenados por nombre.
// Qué hace: recorre secuencialmente y compara nombres (case-insensitive); devuelve índice o -1.
int linearSearchByName(const vector<Contact>& arr, const string& name) {

	string target = toLowerSimple(name);
	for (int i = 0; i < (int)arr.size(); ++i)
		if (toLowerSimple(arr[i].name) == target) return i;
	return -1;
}

// binarySearchByPhone
// Por qué: búsqueda eficiente en un arreglo ordenado por teléfono.
// Qué hace: realiza búsqueda binaria sobre el campo phone; devuelve índice o -1.
int binarySearchByPhone(const vector<Contact>& arr, const string& phone) {

	int left = 0, right = (int)arr.size() - 1;
	while (left <= right) {

		int mid = left + (right - left) / 2;
		if (arr[mid].phone == phone) return mid;
		if (arr[mid].phone < phone) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

// ---------- Lista enlazada (para eliminación) ----------

// buildListFromVector
// Por qué: crear una lista enlazada temporal para eliminar un elemento por índice
//         sin mover muchos elementos del vector manualmente.
// Qué hace: construye y retorna la cabeza de una lista enlazada que contiene los contactos del vector.
ListNode* buildListFromVector(const vector<Contact>& arr) {

	ListNode* head = NULL;
	ListNode* tail = NULL;
	for (int i = 0; i < (int)arr.size(); ++i) {

		ListNode* node = new ListNode(arr[i]);
		if (head == NULL) head = tail = node;
		else { tail->next = node; tail = node; }
	}
	return head;
}

// deleteFromListByIndex
// Por qué: facilita eliminar el nodo en una posición concreta en la lista.
// Qué hace: elimina el nodo en "index"; si se elimina, devuelve true y coloca el contacto eliminado en outDeleted.
bool deleteFromListByIndex(ListNode*& head, int index, Contact& outDeleted) {

	if (head == NULL || index < 0) return false;
	if (index == 0) {
		ListNode* tmp = head;
		head = head->next;
		outDeleted = tmp->data;
		delete tmp;
		return true;
	}

	ListNode* cur = head;
	int i = 0;
	while (cur != NULL && i < index - 1) { cur = cur->next; ++i; }
	if (cur == NULL || cur->next == NULL) return false;
	ListNode* toDel = cur->next;
	cur->next = toDel->next;
	outDeleted = toDel->data;
	delete toDel;
	return true;
}

// listToVectorAndFree
// Por qué: reconstruir un vector a partir de la lista y liberar memoria usada por la lista.
// Qué hace: convierte la lista en vector<Contact>, libera cada nodo y retorna el vector.
vector<Contact> listToVectorAndFree(ListNode* head) {

	vector<Contact> res;
	ListNode* cur = head;
	while (cur != NULL) {
		res.push_back(cur->data);
		ListNode* tmp = cur;
		cur = cur->next;
		delete tmp;
	}
	return res;
}

// ---------- BST ----------

// bstInsert
// Por qué: construir un BST para obtener un ordenamiento por nombre con recorrido inorden.
// Qué hace: inserta recursivamente un Contact en el árbol según comparación por nombre (case-insensitive).
void bstInsert(BSTNode*& root, const Contact& c) {

	if (root == NULL) { root = new BSTNode(c); return; }
	if (toLowerSimple(c.name) < toLowerSimple(root->data.name)) bstInsert(root->left, c);
	else bstInsert(root->right, c);
}

// bstInorder
// Por qué: mostrar contactos en orden alfabético de nombre sin modificar el vector original.
// Qué hace: recorrido inorden que imprime cada contacto.
void bstInorder(BSTNode* root) {

	if (root == NULL) return;
	bstInorder(root->left);
	cout << "-------------------------\n";
	cout << "Nombre  : " << root->data.name << "\n";
	cout << "Telefono: " << root->data.phone << "\n";
	cout << "Email   : " << root->data.email << "\n";
	bstInorder(root->right);
}

// bstPreorder
// Por qué: mostrar contactos siguiendo el recorrido preorden.
// Qué hace: visita nodo actual, luego subárbol izquierdo y derecho.
void bstPreorder(BSTNode* root) {
	if (root == NULL) return;

	cout << "-------------------------\n";
	cout << "Nombre  : " << root->data.name << "\n";
	cout << "Telefono: " << root->data.phone << "\n";
	cout << "Email   : " << root->data.email << "\n";

	bstPreorder(root->left);
	bstPreorder(root->right);
}


// bstFree
// Por qué: liberar la memoria asignada al árbol cuando ya no se necesita.
// Qué hace: recorre y elimina todos los nodos del árbol (postorden).
void bstFree(BSTNode* root) {
	if (root == NULL) return;
	bstFree(root->left);
	bstFree(root->right);
	delete root;
}

// ---------- Operaciones principales (cada función maneja su I/O) ----------

// addContact
// Por qué: interfaz para ingresar un nuevo contacto y registrarlo en el historial.
// Qué hace: pide datos por consola, valida nombre no vacío, agrega al vector principal y al historial.
void addContact(vector<Contact>& mainArray, vector<Operation>& history) {

	Contact c;
	cout << "Agregar contacto\n";
	cout << "Ingrese nombre: "; getline(cin, c.name);
	cout << "Ingrese telefono: "; getline(cin, c.phone);
	cout << "Ingrese email: "; getline(cin, c.email);

	if (c.name.empty()) {

		cout << "Nombre vacio. Operacion cancelada.\n"; return;
	}

	mainArray.push_back(c);
	history.push_back(Operation{ "ADD", c });
	cout << "Contacto agregado: " << c.name << "\n";
}

// listContactsMenu
// Por qué: permitir al usuario ver la lista en distintas ordenaciones sin modificar los datos.
// Qué hace: presenta un submenú; según opción crea copias ordenadas o muestra el vector tal cual.
void listContactsMenu(const vector<Contact>& mainArray) {

	if (mainArray.empty()) {

		cout << "No hay contactos registrados.\n"; return;
	}

	cout << "Listar por:\n1) Nombre (ordenado)\n2) Telefono (ordenado)\n3) Sin ordenar\nElija opcion: ";
	string line;
	getline(cin, line);
	int opt;
	if (!parseIntNonNeg(line, opt)) {

		cout << "Opcion invalida.\n"; return;
	}

	if (opt == 1) {

		vector<Contact> copy = mainArray; // copia para no alterar el original
		bubbleSortByName(copy);
		cout << "Contactos ordenados por nombre:\n";
		for (int i = 0; i < (int)copy.size(); ++i) {
			cout << "[" << i << "]\n";
			cout << "Nombre  : " << copy[i].name << "\n";
			cout << "Telefono: " << copy[i].phone << "\n";
			cout << "Email   : " << copy[i].email << "\n";
		}
	}
	else if (opt == 2) {

		vector<Contact> copy = mainArray; // copia para ordenar por telefono
		selectionSortByPhone(copy);
		cout << "Contactos ordenados por telefono:\n";
		for (int i = 0; i < (int)copy.size(); ++i) {

			cout << "[" << i << "]\n";
			cout << "Nombre  : " << copy[i].name << "\n";
			cout << "Telefono: " << copy[i].phone << "\n";
			cout << "Email   : " << copy[i].email << "\n";
		}
	}
	else if (opt == 3) {

		cout << "Contactos (sin ordenar):\n";
		for (int i = 0; i < (int)mainArray.size(); ++i) {

			cout << "[" << i << "]\n";
			cout << "Nombre  : " << mainArray[i].name << "\n";
			cout << "Telefono: " << mainArray[i].phone << "\n";
			cout << "Email   : " << mainArray[i].email << "\n";
		}
	}
	else {
		cout << "Opcion invalida.\n";
	}
}

// searchContact
// Por qué: permitir búsqueda por nombre o teléfono usando los métodos apropiados.
// Qué hace: según la opción, realiza búsqueda lineal por nombre o binaria por teléfono (en copia ordenada).
void searchContact(vector<Contact>& mainArray) {

	if (mainArray.empty()) {
		cout << "No hay contactos registrados.\n";
		return;
	}
	cout << "Buscar por:\n1) Nombre\n2) Telefono\nElija opcion: ";
	string line; getline(cin, line);
	int opt;

	if (!parseIntNonNeg(line, opt)) {
		cout << "Opcion invalida.\n"; return;
	}

	if (opt == 1) {

		cout << "Ingrese el nombre a buscar: ";
		string name; getline(cin, name);
		int idx = linearSearchByName(mainArray, name);
		if (idx != -1) {

			cout << "Encontrado:\n";
			cout << "Nombre  : " << mainArray[idx].name << "\n";
			cout << "Telefono: " << mainArray[idx].phone << "\n";
			cout << "Email   : " << mainArray[idx].email << "\n";
		}
		else cout << "No encontrado.\n";
	}
	else if (opt == 2) {

		cout << "Ingrese el telefono a buscar: ";
		string phone; getline(cin, phone);
		vector<Contact> copy = mainArray;
		selectionSortByPhone(copy); // ordenar por telefono antes de buscar binariamente
		int idx = binarySearchByPhone(copy, phone);
		if (idx != -1) {

			cout << "Encontrado (en copia ordenada por telefono):\n";
			cout << "Nombre  : " << copy[idx].name << "\n";
			cout << "Telefono: " << copy[idx].phone << "\n";
			cout << "Email   : " << copy[idx].email << "\n";
		}
		else cout << "No encontrado.\n";
	}
	else {
		cout << "Opcion invalida.\n";
	}
}

// deleteContactMenu
// Por qué: interfaz que permite eliminar por índice usando una lista enlazada temporal
//         para simplificar la operación y mantener la semántica de índices mostrados.
// Qué hace: muestra contactos, pide índice, construye lista, intenta eliminar y actualiza el vector e historial.
void deleteContactMenu(vector<Contact>& mainArray, vector<Operation>& history) {

	if (mainArray.empty()) {
		cout << "No hay contactos para eliminar.\n";
		return;
	}

	cout << "Contactos actuales:\n";
	for (int i = 0; i < (int)mainArray.size(); ++i) {
		cout << "[" << i << "] " << mainArray[i].name << " (" << mainArray[i].phone << ")\n";
	}
	cout << "Ingrese indice a eliminar: ";
	string line; getline(cin, line);
	int idx;

	if (!parseIntNonNeg(line, idx)) {
		cout << "Entrada invalida.\n";
		return;
	}

	ListNode* head = buildListFromVector(mainArray);
	Contact deleted;

	if (!deleteFromListByIndex(head, idx, deleted)) {
		// reconstruir vector y liberar
		vector<Contact> tmp = listToVectorAndFree(head);
		(void)tmp;
		cout << "Indice fuera de rango. No se elimino nada.\n";
		return;
	}

	vector<Contact> newVec = listToVectorAndFree(head);
	mainArray = newVec; // actualizar el vector principal con la lista modificada
	history.push_back(Operation{ "DELETE", deleted });
	cout << "Contacto eliminado: " << deleted.name << "\n";
}

// showHistory
// Por qué: permitir al usuario revisar las operaciones realizadas (registro simple).
// Qué hace: imprime el historial en orden inverso (última operación primero).
void showHistory(const vector<Operation>& history) {

	if (history.empty()) {
		cout << "No hay operaciones en el historial.\n";
		return;
	}

	cout << "Historial (ultima operacion primero):\n";
	for (int i = (int)history.size() - 1; i >= 0; --i) {
		cout << history[i].type << " - " << history[i].contact.name << " (" << history[i].contact.phone << ")\n";
	}
}

// pendingQueueMenu
// Por qué: manejar una cola simple de contactos pendientes antes de transferirlos al almacenamiento principal.
// Qué hace: menú interactivo para encolar, listar o transferir todos los pendientes.
void pendingQueueMenu(vector<Contact>& pending, vector<Contact>& mainArray, vector<Operation>& history) {

	while (true) {

		cout << "\nCola de pendientes - opciones:\n";
		cout << "1) Encolar nuevo contacto\n";
		cout << "2) Mostrar pendientes\n";
		cout << "3) Transferir todos los pendientes al almacenamiento principal\n";
		cout << "0) Volver\n";
		cout << "Elija opcion: ";

		string line; getline(cin, line);
		int opt;

		if (!parseIntNonNeg(line, opt)) {
			cout << "Opcion invalida.\n";
			continue;
		}

		if (opt == 0) break;
		else if (opt == 1) {
			Contact c;
			cout << "Ingrese nombre: "; getline(cin, c.name);
			cout << "Ingrese telefono: "; getline(cin, c.phone);
			cout << "Ingrese email: "; getline(cin, c.email);

			if (c.name.empty()) {
				cout << "Nombre vacio. Cancelado.\n";
				continue;
			}
			pending.push_back(c);
			cout << "Contacto encolado: " << c.name << "\n";
		}
		else if (opt == 2) {

			if (pending.empty()) {
				cout << "Cola vacia.\n";
				continue;
			}
			cout << "Pendientes:\n";
			for (int i = 0; i < (int)pending.size(); ++i) {
				cout << "[" << i << "] " << pending[i].name << " (" << pending[i].phone << ")\n";
			}
		}
		else if (opt == 3) {

			if (pending.empty()) {
				cout << "No hay pendientes.\n";
				continue;
			}
			for (int i = 0; i < (int)pending.size(); ++i) {
				mainArray.push_back(pending[i]);
				history.push_back(Operation{ "ADD", pending[i] });
			}
			pending.clear();
			cout << "Pendientes transferidos.\n";
		}
		else {
			cout << "Opcion invalida.\n";
		}
	}
}

// bstMenu
// Por qué: mostrar cómo construir un BST a partir del vector y recorrerlo ordenadamente.
// Qué hace: crea un BST con los contactos actuales, muestra inorden y luego libera memoria.
// bstMenu
// Por qué: mostrar distintas formas de recorrer un BST y darlas como subopciones.
// Qué hace: permite al usuario elegir entre inorden, preorden o ambos recorridos.
void bstMenu(const vector<Contact>& mainArray) {

	if (mainArray.empty()) {
		cout << "No hay contactos para construir el arbol.\n";
		return;
	}

	while (true) {
		cout << "\n--- Arbol BST de Contactos ---\n";
		cout << "1) Mostrar recorrido INORDEN (alfabetico)\n";
		cout << "2) Mostrar recorrido PREORDEN\n";
		cout << "3) Mostrar AMBOS recorridos\n";
		cout << "0) Volver al menu principal\n";
		cout << "Elija opcion: ";

		string line;
		getline(cin, line);
		int opt;
		if (!parseIntNonNeg(line, opt)) {
			cout << "Opcion invalida.\n";
			continue;
		}

		if (opt == 0) break;

		// Construir el BST cada vez para asegurar sincronía
		BSTNode* root = NULL;
		for (int i = 0; i < (int)mainArray.size(); ++i)
			bstInsert(root, mainArray[i]);

		if (opt == 1) {
			cout << "\n--- Recorrido INORDEN ---\n";
			bstInorder(root);
		}
		else if (opt == 2) {
			cout << "\n--- Recorrido PREORDEN ---\n";
			bstPreorder(root);
		}
		else if (opt == 3) {
			cout << "\n--- INORDEN ---\n";
			bstInorder(root);
			cout << "\n--- PREORDEN ---\n";
			bstPreorder(root);
		}
		else {
			cout << "Opcion invalida.\n";
		}

		bstFree(root);
	}
}

int main()
{
    std::cout << "Hello World!\n";
}