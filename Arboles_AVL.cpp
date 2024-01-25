#include <iostream>
using namespace std;

class Nodo
{
    int dato;
    Nodo *izquierdo;
    Nodo *derecho;
    friend class Arbol;

public:
    Nodo(int dato);
    int getdatoizquierdo();
    int getdatoderecho();
    int getdato();
};
Nodo::Nodo(int _dato)
{
    dato = _dato;
    izquierdo = NULL;
    derecho = NULL;
}
int Nodo::getdato()
{
    return dato;
}
int Nodo::getdatoizquierdo()
{
    if (izquierdo == NULL)
    {
        return {};
    }
    else
    {
        return izquierdo->dato;
    }
}
int Nodo::getdatoderecho()
{
    if (derecho == NULL)
    {
        return {};
    }
    else
    {
        return derecho->dato;
    }
}

class Arbol
{
    Nodo *raiz;
    void insert(int dato, Nodo *nodo);
    Nodo *buscar(int dato, Nodo *nodo);
    void eliminar(int dato, Nodo *&nodo, Nodo *padre);
    bool esta_balanceado(Nodo *nodo);
    int factor_balanceo(Nodo *nodo);
    Nodo *minimo(Nodo *nodo);
    Nodo *maximo(Nodo *nodo);

public:
    Arbol();
    bool Estavacio();       // retorna si esta vacio o no
    void insert(int dato);  // inserta un nodo con el dato en el arbol
    Nodo *buscar(int dato); // busca y retorna el nodo que tiene el dato pasado
    Nodo *rotacion_derecha(Nodo *&nodo);
    Nodo *rotacion_izquierda(Nodo *&nodo);
    Nodo *rotacion_doble_derecha(Nodo *&nodo);
    Nodo *rotacion_doble_izquierda(Nodo *&nodo);
    void eliminar(int dato); // elimina el nodo que tiene el dato pasado
    void balancear(Nodo *nodo);
    int pre_altura(Nodo *nodo);
    int altura();
    int factor_balanceo();
    bool esta_balanceado();
    Nodo *minimo();
    Nodo *maximo();
};
Arbol::Arbol()
{
    raiz = NULL;
}
bool Arbol::Estavacio()
{
    return raiz == NULL;
}
void Arbol::insert(int dato)
{
    if (Estavacio())
    {
        raiz = new Nodo(dato);
    }
    else
    {
        insert(dato, raiz);
    }
}
void Arbol::insert(int dato, Nodo *nodo)
{
    if (dato < nodo->dato)
    {
        if (nodo->izquierdo == NULL)
        {
            nodo->izquierdo = new Nodo(dato);
        }
        else
        {
            insert(dato, nodo->izquierdo);
        }
    }
    else if (dato > nodo->dato)
    {
        if (nodo->derecho == NULL)
        {
            nodo->derecho = new Nodo(dato);
        }
        else
        {
            insert(dato, nodo->derecho);
        }
    }
}
Nodo *Arbol::rotacion_derecha(Nodo *&padre)
{
    Nodo *hijo_izquierdo = padre->derecho;
    padre->izquierdo = hijo_izquierdo->derecho;
    hijo_izquierdo->derecho = padre;
    padre = hijo_izquierdo;
}
Nodo *Arbol::rotacion_izquierda(Nodo *&padre)
{
    Nodo *hijo_derecho = padre->derecho;
    padre->derecho = hijo_derecho->izquierdo;
    hijo_derecho->izquierdo = padre;
    padre = hijo_derecho;
}
Nodo *Arbol::rotacion_doble_derecha(Nodo *&padre)
{
    padre->derecho = rotacion_izquierda(padre->derecho);
    return rotacion_derecha(padre);
}
Nodo *Arbol::rotacion_doble_izquierda(Nodo *&padre)
{
    padre->izquierdo = rotacion_derecha(padre->izquierdo);
    return rotacion_izquierda(padre);
}
int Arbol::pre_altura(Nodo *nodo)
{
    if (nodo == NULL)
    {
        return -1; // Retorna -1 para que el cálculo de altura se realice correctamente
    }

    int altura_izquierda = pre_altura(nodo->izquierdo);
    int altura_derecha = pre_altura(nodo->derecho);

    return 1 + max(altura_izquierda, altura_derecha); // 1+ porque se cunta a si mismo
}
void Arbol::balancear(Nodo *x)
{
    if (pre_altura(x) >= 2)
    {
        if (pre_altura(x->izquierdo) <= -1)
        {
            x = rotacion_doble_izquierda(x);
        }
        else
        {
            x = rotacion_derecha(x);
        }
    }
    else if (pre_altura(x) <= -2)
    {
        if (pre_altura(x->derecho) >= 1)
        {
            x = rotacion_doble_derecha(x);
        }
        else
        {
            x = rotacion_izquierda(x);
        }
    }
}

Nodo *Arbol::buscar(int dato)
{
    return buscar(dato, raiz);
}
Nodo *Arbol::buscar(int dato, Nodo *nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    if (dato == nodo->dato)
    {
        return nodo;
    }
    if (dato < nodo->dato)
    {
        return buscar(dato, nodo->izquierdo);
    }
    else
    {
        return buscar(dato, nodo->derecho);
    }
}
Nodo *Arbol::minimo()
{
    return minimo(raiz);
}

Nodo *Arbol::minimo(Nodo *nodo)
{
    if (nodo == nullptr)
    {
        return nullptr;
    }

    if (nodo->izquierdo == nullptr)
    {
        return nodo;
    }
    else
    {
        return minimo(nodo->izquierdo);
    }
}

Nodo *Arbol::maximo()
{
    return maximo(raiz);
}

Nodo *Arbol::maximo(Nodo *nodo)
{
    if (nodo == nullptr)
    {
        return nullptr;
    }

    if (nodo->derecho == nullptr)
    {
        return nodo;
    }
    else
    {
        return maximo(nodo->derecho);
    }
}
void Arbol::eliminar(int dato)
{
    eliminar(dato, raiz, nullptr);
}

void Arbol::eliminar(int dato, Nodo *&nodo, Nodo *padre)
{
    if (nodo == nullptr)
    {
        return;
    }

    if (dato < nodo->getdato())
    {
        eliminar(dato, nodo->izquierdo, nodo);
    }
    else if (dato > nodo->getdato())
    {
        eliminar(dato, nodo->derecho, nodo);
    }
    else
    {
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr)
        {
            // Nodo sin hijos
            if (padre == nullptr)
            {
                raiz = nullptr;
            }
            else if (padre->izquierdo == nodo)
            {
                padre->izquierdo = nullptr;
            }
            else
            {
                padre->derecho = nullptr;
            }
            delete nodo;
        }
        else if (nodo->izquierdo == nullptr)
        {
            // Nodo con un hijo derecho
            Nodo *temp = nodo;
            nodo = nodo->derecho;
            delete temp;
        }
        else if (nodo->derecho == nullptr)
        {
            // Nodo con un hijo izquierdo
            Nodo *temp = nodo;
            nodo = nodo->izquierdo;
            delete temp;
        }
        else
        {
            // Nodo con dos hijos
            Nodo *sucesor = minimo(nodo->derecho);
            nodo->dato = sucesor->getdato();
            eliminar(sucesor->getdato(), nodo->derecho, nodo);
        }
    }
}

int Arbol::altura()
{
    int we = pre_altura(raiz);
    return we;
}

int Arbol::factor_balanceo()
{
    return factor_balanceo(raiz);
}
int Arbol::factor_balanceo(Nodo *nodo)
{
    if (nodo == NULL)
    {
        return 0;
    }

    int altura_izquierda = pre_altura(nodo->izquierdo);
    int altura_derecha = pre_altura(nodo->derecho);

    return altura_izquierda - altura_derecha;
}
bool Arbol::esta_balanceado()
{
    return esta_balanceado(raiz);
}

bool Arbol::esta_balanceado(Nodo *nodo)
{
    if (nodo == NULL)
    {
        return true;
    }

    int nodo_izquierdo = pre_altura(nodo->izquierdo);
    int nodo_derecho = pre_altura(nodo->derecho);

    if (abs(nodo_izquierdo - nodo_derecho) <= 1 && esta_balanceado(nodo->izquierdo) && esta_balanceado(nodo->derecho))
    {
        return true;
    }

    return false;
}

int main()
{
    Arbol arbol;
    arbol.insert(10);
    arbol.insert(5);
    arbol.insert(15);
    arbol.insert(3);
    arbol.insert(7);
    arbol.insert(13);
    arbol.insert(17);

    if (arbol.esta_balanceado() == true)
    {
        cout << "El arbol si esta balanceado ";
    }
    else
    {
        cout << "El arbol no esta balanceado ";
    }
    cout<<endl;
    cout << "el factor de balanceo de la raiz es: " << arbol.factor_balanceo();

    return 0;
}
