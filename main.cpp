#include <iostream>

/*
INTEGRANTES:
 - Christian Frisancho
 - Isaac Simeón
 */

using namespace std;

//CREACIÓN DE ARBOL BST

class Nodo {
private:
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    friend class ArbolBST;

public:
    Nodo(int dato);
    int getDato();
};

Nodo::Nodo(int _dato) {
    dato = _dato;
    izquierdo = nullptr;
    derecho = nullptr;
}

int Nodo::getDato() {
    return dato;
}

class ArbolBST {
private:
    void insert(int dato, Nodo* &nodo);
    int altura(Nodo* nodo);
    Nodo* buscar(int dato, Nodo* nodo);
    void eliminar(int dato, Nodo* &nodo, Nodo* padre);
    void muestraPreOrden(Nodo* nodo);
    void muestraEnOrden(Nodo* nodo);
    void muestraPostOrden(Nodo* nodo);
    Nodo* minimo(Nodo* nodo);
    Nodo* maximo(Nodo* nodo);
public:
    Nodo* raiz;
    ArbolBST();
    void insert(int dato);
    int altura();
    int buscar(int dato);
    void eliminar(int dato);
    void muestraPreOrden();
    void muestraEnOrden();
    void muestraPostOrden();
    Nodo* minimo();
    Nodo* maximo();
};

ArbolBST::ArbolBST() {
    raiz = nullptr;
}

void ArbolBST::insert(int dato) {
    insert(dato, raiz);
}

void ArbolBST::insert(int dato, Nodo* &nodo) {
    if (nodo == nullptr) {
        nodo = new Nodo(dato);
    } else if (dato < nodo->getDato()) {
        insert(dato, nodo->izquierdo);
    } else if (dato > nodo->getDato()) {
        insert(dato, nodo->derecho);
    }
}

int ArbolBST::altura() {
    return altura(raiz);
}

int ArbolBST::altura(Nodo* nodo) {
    if (nodo == nullptr) {
        return 0;
    } else {
        int alturaIzquierdo = altura(nodo->izquierdo);
        int alturaDerecho = altura(nodo->derecho);
        return 1 + std::max(alturaIzquierdo, alturaDerecho);
    }
}

int ArbolBST::buscar(int dato) {
    Nodo* resultado = buscar(dato, raiz);
    if (resultado != nullptr) {
        return resultado->getDato();
    } else {
        return -1;
    }
}

Nodo* ArbolBST::buscar(int dato, Nodo* nodo) {
    if (nodo == nullptr || dato == nodo->getDato()) {
        return nodo;
    } else if (dato < nodo->getDato()) {
        return buscar(dato, nodo->izquierdo);
    } else {
        return buscar(dato, nodo->derecho);
    }
}

void ArbolBST::eliminar(int dato) {
    eliminar(dato, raiz, nullptr);
}

void ArbolBST::eliminar(int dato, Nodo* &nodo, Nodo* padre) {
    if (nodo == nullptr) {
        return;
    }

    if (dato < nodo->getDato()) {
        eliminar(dato, nodo->izquierdo, nodo);
    } else if (dato > nodo->getDato()) {
        eliminar(dato, nodo->derecho, nodo);
    } else {
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            // Nodo sin hijos
            if (padre == nullptr) {
                raiz = nullptr;
            } else if (padre->izquierdo == nodo) {
                padre->izquierdo = nullptr;
            } else {
                padre->derecho = nullptr;
            }
            delete nodo;
        } else if (nodo->izquierdo == nullptr) {
            // Nodo con un hijo derecho
            Nodo* temp = nodo;
            nodo = nodo->derecho;
            delete temp;
        } else if (nodo->derecho == nullptr) {
            // Nodo con un hijo izquierdo
            Nodo* temp = nodo;
            nodo = nodo->izquierdo;
            delete temp;
        } else {
            // Nodo con dos hijos
            Nodo* sucesor = minimo(nodo->derecho);
            nodo->dato = sucesor->getDato();
            eliminar(sucesor->getDato(), nodo->derecho, nodo);
        }
    }
}

//Crea funciones para encontrar el maximo y minimo valor del arbol
Nodo* ArbolBST::minimo() {
    return minimo(raiz);
}

Nodo* ArbolBST::minimo(Nodo* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->izquierdo == nullptr) {
        return nodo;
    } else {
        return minimo(nodo->izquierdo);
    }
}

Nodo* ArbolBST::maximo() {
    return maximo(raiz);
}

Nodo* ArbolBST::maximo(Nodo* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->derecho == nullptr) {
        return nodo;
    } else {
        return maximo(nodo->derecho);
    }
}

void ArbolBST::muestraPreOrden() {
    muestraPreOrden(raiz);
    cout << endl;
}

void ArbolBST::muestraPreOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        cout << nodo->getDato() << " ";
        muestraPreOrden(nodo->izquierdo);
        muestraPreOrden(nodo->derecho);
    }
}

void ArbolBST::muestraEnOrden() {
    muestraEnOrden(raiz);
    cout << endl;
}

void ArbolBST::muestraEnOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        muestraEnOrden(nodo->izquierdo);
        cout << nodo->getDato() << " ";
        muestraEnOrden(nodo->derecho);
    }
}

void ArbolBST::muestraPostOrden() {
    muestraPostOrden(raiz);
    cout << endl;
}

void ArbolBST::muestraPostOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        muestraPostOrden(nodo->izquierdo);
        muestraPostOrden(nodo->derecho);
        cout << nodo->getDato() << " ";
    }
}


int main() {
    //Estamos creando un arbol para aplicar los distintos metodos que tiene
    ArbolBST arbol;
    arbol.insert(10);
    arbol.insert(5);
    arbol.insert(15);
    arbol.insert(3);
    arbol.insert(7);
    arbol.insert(12);
    arbol.insert(17);

    cout << "Arbol pre-orden:" << endl;
    arbol.muestraPreOrden();

    cout << "Arbol en-orden:" << endl;
    arbol.muestraEnOrden();

    cout << "Arbol post-orden:" << endl;
    arbol.muestraPostOrden();

    cout << "Altura del arbol: " << arbol.altura() << endl;

    int dato = 12;
    int resultado = arbol.buscar(dato);
    if (resultado != -1) {
        cout << "El dato " << dato << " fue encontrado en el arbol." << endl;
    } else {
        cout << "El dato " << dato << " no fue encontrado en el arbol." << endl;
    }

    //eliminando un nodo del arbol
    arbol.eliminar(12);
    int dato2 = 12;
    int resultado2 = arbol.buscar(dato2);
    if (resultado2 != -1) {
        cout << "El dato " << dato << " fue encontrado en el arbol." << endl;
    } else {
        cout << "El dato " << dato << " no fue encontrado en el arbol." << endl;
    }

    //El minimo valor del arbol
    cout << "El minimo valor del arbol es: " << arbol.minimo()->getDato() << endl;

    //El maximo valor del arbol
    cout << "El maximo valor del arbol es: " << arbol.maximo()->getDato() << endl;

    return 0;
}
