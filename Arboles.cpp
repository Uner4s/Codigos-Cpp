#include <iostream>



using namespace std;


struct arbol
{
    int dato;
    arbol *izq;
    arbol *der;
};

// Declaración de funciones

arbol* eli(arbol* A, int x);      // Elimina un arbol, recibe como parámetro la raíz y el elemento a eliminar
arbol *ing_arbol(arbol* A,int x);    // Crea un arbol, recibe como parámetro la raíz y el elemento a ingresar
void inorden(arbol *A);         // Recorre el árbol en inorden
void preorden(arbol *A);      // Recorre el árbol en preorden
void postorden(arbol *A);    // Recorre el árbol en postorden
int MayorElem(arbol *A);    // Encuentra el mayor elemento de un árbol
int esta(arbol *A, int x);       // Retorna un 1 si el elemento está en el árbol y un 0 si no ésta
void mostrar();		    //Muestra los elementos del arbol
void Hojas (arbol *A, int cont);  // funcion que muestra la cantidad de hojas del arbol y cuales son.
void buscar (arbol *A);
arbol* hojas(arbol* A, int x);
void niveles(arbol *A, int t);
void Niv2(arbol *A,int cont, int niv);


// Una de las pocas funciones que se pueden realizar sin recursividad.
int MayorElem(arbol *A)
{
    while(A->der)
        A=A->der;
    return(A->dato);
}

// Función que elimina un arbol del árbol (tres casos)
arbol* eli(arbol* A, int x)
{
    arbol *p;
    int Mayor;
    if(A->dato == x)
    {
        if(A->izq == NULL && A->der==NULL)   // caso 1: El elemento se encuentra en una hoja
        {
            delete A;
            return NULL;
        }
        else if(A->izq == NULL)		// caso 2: La rama izquierda del dato es nula y en la derecha
        {
            p= A->der;                              //             hay información
            delete A;
            return p;
        }
        else
        {
            Mayor=MayorElem(A->izq);     // Caso 3:  Que sea un arbol interno con rama izq. y rama der.
            A->dato = Mayor;
            A->izq = eli(A->izq,Mayor);
        }
    }
    else if (A->dato > x)				// Parte recursiva para recorrer el arbol hasta encontrar elemento
        A->izq = eli(A->izq,x);
    else
        A->der = eli(A->der,x);
    return A;
}




// Funcion Ingreso
arbol* ing_arbol(arbol *A,int x)
{
    if(A==NULL)
    {
        A= new arbol;
        if(!A)
        {
            cout << "NO HAY SUFICIENTE MEMORIA ";
            return A;
        }
        A->dato=x;
        A->izq=A->der=NULL;
    }
    else    if(A->dato < x)
        A->der=ing_arbol(A->der,x);
    else if (A->dato > x)
        A->izq=ing_arbol(A->izq,x);
    else
    {
        cout << "EL ELEMENTO YA EXISTE, NO PUEDE ESTAR REPETIDO";
        cin.get();
    }
    return A;
}
// Función que determina si el elemento x está en el arbol (retorna 1) o no esta (retorna 0)
int esta(arbol *A, int x)
{
    if (!A)
        return 0;
    if(A->dato==x)
        return 1;
    if(A->dato < x)
        return(esta(A->der,x));
    else
        return(esta(A->izq,x));
}

void niveles(arbol *A, int t)
{
    int cont=0;

    while(t!=A->dato)
    {
        if(t>A->dato)
        {
            A=A->der;
            cont++;
        }
        else
        {
            A=A->izq;
            cont++;
        }


    }

    cout<<" El elemento "<<t<< " se encuentra en el nivel "<<cont<<endl;
    system("pause");
}



void buscar (arbol *A)
{
    int x, t;

    cout<<" Ingrese un elemento para saber si se encuentra en el arbol "<<endl;
    cin>>x;
    t=x;
    if (esta(A,x)==1)
    {
        cout<<"El elemento si se encuentra "<<endl;
        niveles(A,t);
    }
    else
        cout<<" El elemento no se encuentra en el arbol "<<endl;
}


//Función para eliminar un arbol del árbol
arbol *elimina(int x, arbol *R)
{
    if (R  && esta(R,x)==1)
        R=eli(R,x);	// Elimina sólo si el elemento se encuentra en el árbol
    else
    {
        cout << endl <<"EL ELEMENTO NO SE ENCUENTRA, NO PUEDE SER ELIMINADO";
        cin.get();
    }
    return R;
}


void inorden(arbol *A)
{
    if(A)
    {
        inorden(A->izq);

        cout << A->dato <<"\t";

        inorden(A->der);
    }
}

void Niv2(arbol *A,int cont, int niv)
{
    if(A)
    {
        if(cont==niv){
            cout<<endl;
            cout<<"Dato ";
            cout<<A->dato<<endl;

        }
        else
        {
            cont++;
            Niv2(A->izq,cont,niv);
            Niv2(A->der,cont,niv);
        }
    }
}

void Hojas (arbol *A, int cont)
{
    if(A)
    {
        Hojas(A->izq,cont);
        if(A->izq == NULL && A->der==NULL)
        {
            cout << A->dato <<"\t";
            cont++;
        }
        Hojas(A->der,cont);
    }
}


void preorden(arbol *A)
{
    if(A)
    {
        cout << A->dato <<"\t";
        preorden(A->izq);
        preorden(A->der);
    }
}

void postorden(arbol *A)
{
    if(A)
    {
        postorden(A->izq);
        postorden(A->der);
        cout << A->dato <<"\t";
    }
}

// Función que elige la forma de mostrar los datos
void mostrar(arbol *a)
{
    int var,niv, cont=0;
    int op;
    do
    {
        cout <<"\t\tMENU"<<endl;
        cout <<"\t 1. Inorden"<<endl;
        cout <<"\t 2. Preorden"<<endl;
        cout <<"\t 3. Posorden"<<endl;
        cout <<"\t 4. Mostrar las hojas y su cantidad"<<endl;
        cout <<"\t 5. Buscar un elemento X y ver su donde se encuentra "<<endl;
        cout <<"\t 6. Mostrar todos los datos de un nivel"<<endl;
        cout <<"\t 7. Salir"<<endl;
        cout <<"      Opcion:  ";
        cin >> op;
        switch(op)
        {
        case 1 :
            inorden(a);
            cout << endl<<"Presione una tecla para continuar";
            system("pause");
            system("cls");
            break;
        case 2 :
            preorden(a);
            cout << endl<<"Presione una tecla para continuar";
            system("pause");
            system("cls");
            break;
        case 3 :
            postorden(a);
            cout <<endl<< "Presione una tecla para continuar";
            system("pause");
            system("cls");
            break;
        case 4 :
            cout<<" Las hojas del arbol son "<<endl;
            Hojas (a, cont);
            cin.get();
            system("pause");
            system("cls");
            break;
        case 5 :
            buscar (a);
            cout<<" Presione una tecla para continuar "<<endl;
            system("pause");
            system("cls");
            break;
        case 6 :
            cout<<" Ingrese el nivel "<<endl;
            cout<<endl;
            cout<<endl;
            cin>>niv;
            Niv2(a,cont,niv);
            system("pause");
            system("cls");
            break;
        case 7 :
            cin.get();

        }
    }
    while(op!=7);
}


// programa principal
int main()
{
    arbol *a;
    int n,x;
    a= NULL;
    cout <<"Cuantos datos desea ingresar : ";
    cin >> n;

    do
    {
        cout <<"Ingrese dato a arbol :" ;
        cin >> x;
        a=ing_arbol(a,x);
        n--;
    }
    while(n!=0);

    mostrar(a);

    while (a)
        a=eli(a,a->dato);
    return 0;
}
