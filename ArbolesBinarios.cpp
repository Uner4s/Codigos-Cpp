/*
	Archivo de Complejidad.
    Autor: Nicolas Fernando Perez Poblete
*/



#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdio>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
#define lonCad 15

using namespace std;

ofstream Archivo_abb_datos;
ofstream Archivo_abb_freq;
ofstream Archivo_avl_datos;
ofstream Archivo_avl_freq;
ofstream Archivo_23_datos;
ofstream Archivo_23_freq;
ofstream Archivo_b_datos;
ofstream Archivo_b_freq;

int complejidad_ABB=0;
int complejidad_AVL=0;
int complejidad_B=0;

struct timespec tiempo1, tiempo2, latencia;

//*************************************************************************************************************************
void diff_time( timespec *t_fin, timespec *t_ini, timespec *delta )
{
    if( ( (*t_fin).tv_nsec - (*t_ini).tv_nsec ) < 0 )
    {
        if( (*t_fin).tv_sec == (*t_ini).tv_sec )
        {
            (*delta).tv_sec  = 0;
            (*delta).tv_nsec = 1000000000 + (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
        else
        {
            (*delta).tv_sec  = (*t_fin).tv_sec - (*t_ini).tv_sec - 1;
            (*delta).tv_nsec = 1000000000 + (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
    }
    else
    {
        if( (*t_fin).tv_sec == (*t_ini).tv_sec )
        {
            (*delta).tv_sec  = 0;
            (*delta).tv_nsec = (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
        else
        {
            (*delta).tv_sec  = (*t_fin).tv_sec - (*t_ini).tv_sec;
            (*delta).tv_nsec = (*t_fin).tv_nsec - (*t_ini).tv_nsec;
        }
    }
}

//*************************************************************************************************************************

// A BTree node
class BTreeNode
{
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
 
public:
 
    BTreeNode(int _t, bool _leaf);   // Constructor
	void traverse_1();
    void traverse_2();
    void traverse_3();
    void traverse_4();
    BTreeNode *search(int k);  
    int findKey(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    friend class BTree;
};
 
class BTree
{
    int t;
public:

    BTreeNode *root;
    BTree(int _t)
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        root = NULL;
        t = _t;
    }

    void traverse_1()
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        if (root != NULL) root->traverse_1();
    }
    void traverse_2()
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        if (root != NULL) root->traverse_2();
    }
    void traverse_3()
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        if (root != NULL) root->traverse_3();
    }
    void traverse_4()
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        if (root != NULL) root->traverse_4();
    }
  
    BTreeNode* search(int k)
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        return (root == NULL)? NULL : root->search(k);
    }

    void insert(int k);
 	void remove2();
    void remove(int k);
 
};
typedef class BTreeNode * B_23;
 
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];

    n = 0;
}

int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        ++idx;
    }
    return idx;
}
 
// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k)
{
    int idx = findKey(k);
 
    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k)
    {
 		complejidad_B++;// Se va calculando la complejidad de computo.
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            removeFromLeaf(idx);
        }
        else{
        	complejidad_B++;// Se va calculando la complejidad de computo.
            removeFromNonLeaf(idx);
        }
    }
    else
    {
 		complejidad_B++;// Se va calculando la complejidad de computo.
        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {	complejidad_B++;
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==n)? true : false );
 		complejidad_B++;// Se va calculando la complejidad de computo.
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);
 		complejidad_B++;// Se va calculando la complejidad de computo.
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}
 
// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf (int idx)
{
 
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
 
    // Reduce the count of keys
    n--;
 
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{
 
    int k = keys[idx];
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
 
    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }
 
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}
 
// A function to get predecessor of keys[idx]
int BTreeNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=C[idx];
    while (!cur->leaf){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        cur = cur->C[cur->n];
    }
 
    // Return the last key of the leaf
    return cur->keys[cur->n-1];
}
 
int BTreeNode::getSucc(int idx)
{
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        cur = cur->C[0];
    }
 
    // Return the first key of the leaf
    return cur->keys[0];
}
 
// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx)
{
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && C[idx-1]->n>=t){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        borrowFromPrev(idx);
    }
 
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=n && C[idx+1]->n>=t){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        borrowFromNext(idx);
    }
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != n){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            merge(idx);
        }
        else{
        	complejidad_B++;// Se va calculando la complejidad de computo.
            merge(idx-1);
        }
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void BTreeNode::borrowFromPrev(int idx)
{
 	complejidad_B++;// Se va calculando la complejidad de computo.
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];
 
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        child->keys[i+1] = child->keys[i];
    }
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {	
    	complejidad_B++;
        for(int i=child->n; i>=0; --i){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            child->C[i+1] = child->C[i];
        }
    }
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx-1];
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // Moving sibling's last child as C[idx]'s first child
    if (!leaf){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        child->C[0] = sibling->C[sibling->n];
    }
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    complejidad_B++;
    keys[idx-1] = sibling->keys[sibling->n-1];
    child->n += 1;
    sibling->n -= 1;
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void BTreeNode::borrowFromNext(int idx)
{
 
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = keys[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf)){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        child->C[(child->n)+1] = sibling->C[0];
    }
 
    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
 
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        sibling->keys[i-1] = sibling->keys[i];
    }
 
    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            sibling->C[i-1] = sibling->C[i];
        }
    }
 
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;
 	complejidad_B++;// Se va calculando la complejidad de computo.
    return;
}
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
 
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[idx];
 
    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        child->keys[i+t] = sibling->keys[i];
    }
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        for(int i=0; i<=sibling->n; ++i){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            child->C[i+t] = sibling->C[i];
        }
    }
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<n; ++i){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        keys[i-1] = keys[i];
    }
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=n; ++i){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        C[i-1] = C[i];
    }
    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    n--;
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}
 
// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1)
        {
        	complejidad_B++;// Se va calculando la complejidad de computo.
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);
 
            // Make old root as child of new root
            s->C[0] = root;
 
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            complejidad_B++;// Se va calculando la complejidad de computo.
 
            // Change root
            root = s;
        }
        else{  // If root is not full, call insertNonFull for root
        	complejidad_B++;// Se va calculando la complejidad de computo.
            root->insertNonFull(k);
        }
    }
}
 
// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n-1;
    // If this is a leaf node
    if (leaf == true)
    {
    	complejidad_B++;// Se va calculando la complejidad de computo.
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
        	complejidad_B++;// Se va calculando la complejidad de computo.
            keys[i+1] = keys[i];
            i--;
        }
 
        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            i--;
        }
 
        // See if the found child is full
        if (C[i+1]->n == 2*t-1){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        complejidad_B++;// Se va calculando la complejidad de computo.
        C[i+1]->insertNonFull(k);
    }
}
 
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t-1; j++){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        z->keys[j] = y->keys[j+t];
    }
    // Copy the last t children of y to z
    if (y->leaf == false){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        for (int j = 0; j < t; j++){
        	complejidad_B++;// Se va calculando la complejidad de computo.
            z->C[j] = y->C[j+t];
        }
    }
    // Reduce the number of keys in y
    y->n = t - 1;
 	complejidad_B++;// Se va calculando la complejidad de computo.
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        C[j+1] = C[j];
    }
    // Link the new child to this node
    C[i+1] = z;
 
    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--){
    	complejidad_B++;// Se va calculando la complejidad de computo.
        keys[j+1] = keys[j];
    }
    // Copy the middle key of y to this node
    keys[i] = y->keys[t-1];
    // Increment count of keys in this node
    n = n + 1;
}
 
// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse_1()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++){
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse_1();
        //cout << " " << keys[i];
        Archivo_23_datos<<keys[i]<<" ";
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse_1();
}

void BTreeNode::traverse_2()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++){
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse_2();
        //cout << " " << keys[i];
        Archivo_23_freq<<keys[i]<<" ";
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse_2();
}

void BTreeNode::traverse_3()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++){
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse_3();
        //cout << " " << keys[i];
        Archivo_b_datos<<keys[i]<<" ";
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse_3();
}

void BTreeNode::traverse_4()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++){
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse_4();
        //cout << " " << keys[i];
        Archivo_b_freq<<keys[i]<<" ";
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse_4();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    // If the found key is equal to k, return this node
    if (keys[i] == k){
    	//cout<<"si esta"<<endl;
        return this;
    }
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

 
    // Go to the appropriate child
    return C[i]->search(k);
}
 
void BTree::remove(int k)
{
    if (!root){
        cout << "The tree is empty\n";
        return;
    }
 
    // Call the remove function for root
    root->remove(k);
 
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n==0){
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
 
        // Free the old root
        delete tmp;
    }
    return;
}

void BTree::remove2()
{
	root = NULL;
	return;
}


//*************************************************************************************************************************
//*************************************************************************************************************************

int esta(int numero, vector<int> UV, int i2) //Funcion que sirve para crear un vector con los elementos una sola vez.
{
	int cont=0;
	int respuesta=0;
	while(cont<i2){
		if(numero==UV[cont]){
			respuesta++;
			cont++;
		}
		else{
			cont++;
		}
	}
	if(respuesta>0)
		return 1;
	else
		return 0;
}

int frecuencia(int numero, vector<int> elementos, int cantidad)// Esta funcion retorna las frecuencias de un numero especifico
{
	int i=0;
	int freq=0;
	
	while(i<cantidad)
	{
		if(numero==elementos[i]){
			freq++;
			i++;
		}
		else{
			i++;
		}
	}
	return freq;	
}

//*************************************************************************************************************************
//*************************************************************************************************************************

typedef struct puntero{
     int nro;
     struct puntero *izq, *der;
}*ABB; 
 
ABB crearNodo(int x) // Crea un nuevo nodo en el arbol
{
     ABB nuevoNodo = new(struct puntero);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;
     complejidad_ABB++;// Se va calculando la complejidad de computo.
 
     return nuevoNodo;
}
void insertar(ABB &arbol, int x) // Inserta un numero mandado al arbol
{
     if(arbol==NULL) // Si el arbol es nulo
     {
           arbol = crearNodo(x); // crea un nuevo nodo
           complejidad_ABB++; // Se va calculando la complejidad de computo.
     }
     else if(x < arbol->nro){
     	  complejidad_ABB++;// Se va calculando la complejidad de computo.
          insertar(arbol->izq, x);
      }
     else if(x > arbol->nro){
     	  complejidad_ABB++;// Se va calculando la complejidad de computo.	
          insertar(arbol->der, x);
      }
          
}

bool busquedaRec(ABB arbol, int dato) // BUSQUEDA ABB
{
     int r=0;   // 0 indica que lo encontre
 
     if(arbol==NULL)
        return r;
 
     if(dato<arbol->nro)
         r = busquedaRec(arbol->izq, dato);
 
     else if(dato> arbol->nro)
         r = busquedaRec(arbol->der, dato);
 
     else
        r = 1;   // son iguales, lo encontre
 
     return r;
}
//*************************************************************************************************************************
//*************************************************************************************************************************




//*************************************************************************************************************************
//*************************************************************************************************************************

typedef struct avlnode
{
    int clave;
    int bal; /* Factor de balance -1,0,1 */
    struct avlnode *left, *right;
} nodo, *pnodo;

int flag; /* Marca para registrar cambios de altura. En rebalance ascendente */
//flag = 1 indica que debe seguir el ascenso rebalanceando.
int key; /* Variable global, para disminuir argumentos */
int alto_avl = 0; /* Altura árbol avl. Número de nodos desde la raíz a las hojas.*/

static pnodo lrot(pnodo t)
{
    pnodo temp;
    int x,y;
    temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    //Recalcula factores de balance de los dos nodos
    x = temp->bal; // oldbal(A)
    y = t->bal; // oldbal(B)
    temp->bal = x-1-max(y, 0); // nA
    t->bal = min(x-2+min(y, 0), y-1); // nB
    complejidad_AVL++;// Se va calculando la complejidad de computo.
    return t;
}

static pnodo rrot(pnodo t)
{
    pnodo temp = t;
    int x,y;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    x = temp->bal; // oldbal(A)
    y = t->bal;    // oldbal(B)
    temp->bal = x+1-min(y, 0);  // nA
    t->bal = max(x+2+max(y, 0), y+1); //nB
    complejidad_AVL++;// Se va calculando la complejidad de computo.
    return t;
}

static void Error(int tipo)
{
    if (tipo) printf("\nError en inserción\n");
    else printf("\nError en descarte\n");
}

int Altura(void)
{
	complejidad_AVL++;// Se va calculando la complejidad de computo.
    return alto_avl;
}

pnodo CreaNodo(int key)
{
    pnodo t;
    t = (pnodo) malloc(sizeof(nodo));
    t->clave=key;
    t->left=0;
    t->right=0;
    complejidad_AVL++;// Se va calculando la complejidad de computo.
    return t;
}

pnodo insertR(pnodo t)
{
    if (t == NULL)  /* Llegó a un punto de inserción */
    {
        t = CreaNodo(key);
        t->bal = 0; /* Los dos hijos son nulos */
        flag = 1; /* Marca necesidad de revisar balances */
        complejidad_AVL++;// Se va calculando la complejidad de computo.
        return t; /* retorna puntero al insertado */
    }
    else if (t->clave < key)
    {
    	complejidad_AVL++;// Se va calculando la complejidad de computo.
        //desciende por la derecha
        t->right = insertR(t->right);
        //se pasa por la siguiente línea en la revisión ascendente
        t->bal += flag; /* Incrementa factor de balance */
    }
    else if (t->clave > key)
    {
    	complejidad_AVL++;// Se va calculando la complejidad de computo.
        //desciende por la izquierda
        t->left = insertR(t->left);
        //se corrige en el ascenso
        t->bal -= flag; /* Decrementa balance */
    }
    else   /* (t->k == key) Ya estaba en el árbol */
    {
    	complejidad_AVL++;// Se va calculando la complejidad de computo.
        //Error(1);
        flag = 0;
    }

    if (flag == 0) /* No hay que rebalancear. Sigue el ascenso */
        return t;

    /*El código a continuación es el costo adicional para mantener propiedad AVL */
    /* Mantiene árbol balanceado avl. Sólo una o dos rotaciones por inserción */
    if (t->bal < -1)
    {
    	
        /* Quedó desbalanceado por la izquierda. Espejos Casos c y d.*/
        if (t->left->bal > 0){
        	complejidad_AVL++;// Se va calculando la complejidad de computo.
            /* Si hijo izquierdo está cargado a la derecha */
            t->left = lrot(t->left);
        }
        complejidad_AVL++;// Se va calculando la complejidad de computo.
        t = rrot(t);
        flag = 0; /* El subárbol no aumenta su altura */
    }
    else if (t->bal > 1)
    {
        /* Si quedó desbalanceado por la derecha: Casos c y d.*/
        if (t->right->bal < 0){
        	complejidad_AVL++;// Se va calculando la complejidad de computo.
            /* Si hijo derecho está cargado a la izquierda Caso d.*/
            t->right = rrot(t->right);
        }
        t = lrot(t); /* Caso c.*/
        flag = 0; /* El subárbol no aumenta su altura */
        complejidad_AVL++;// Se va calculando la complejidad de computo.
    }
    else if (t->bal == 0){/* La inserción lo balanceo */
    	complejidad_AVL++;// Se va calculando la complejidad de computo.
        flag = 0; /* El subárbol no aumenta su altura. Caso a*/
    }
    else {/* Quedó desbalanceado con -1 ó +1 Caso b */
        complejidad_AVL++;// Se va calculando la complejidad de computo.
		flag = 1; /* Propaga ascendentemente la necesidad de rebalancear */
    }
    complejidad_AVL++;// Se va calculando la complejidad de computo.
    return t;
}

/* Mantiene variable global con el alto del árbol. */
pnodo InsertarAVL(int clave, pnodo t)
{
	complejidad_AVL++;// Se va calculando la complejidad de computo.
    key = clave; //pasa argumento a global.
    t = insertR(t);
    if (flag == 1)
        alto_avl++;
    //si la propagación llega hasta la raíz, aumenta la altura.
    return t;
}


pnodo deleteR(pnodo t)
{
    pnodo p;
    if (t == NULL)  /* No encontró nodo a descartar */
    {
        Error(0);
        flag = 0;
    }
    else if (t->clave < key)
    {
        //Comienza el descenso por la derecha
        t->right = deleteR(t->right);
        //aquí se llega en el retorno ascendente.
        t->bal -= flag; /* Se descartó por la derecha. Disminuye factor */
        //Se retorna después de la revisión de los factores
    }
    else if (t->clave > key)
    {
        //Desciende por la izquierda
        t->left = deleteR(t->left);
        //o se llega por esta vía si se descartó por la izquierda.
        t->bal += flag; /* se descartó por la izq. Aumenta factor de balance */
    }
    else   /* (t->clave == key) */
    {
        /* Encontró el nodo a descartar */
        if (t->left == NULL)   /*Si hay hijo derecho debe ser hoja, por ser AVL */
        {
            p = t;
            t = t->right;
            free(p);
            flag = 1; /* Debe seguir revisando factores de balance */
            return t; /* ascendentemente */
        }
        else if (t->right == NULL)   /*Si hay hijo izquierdo debe ser hoja */
        {
            p = t;
            t = t->left;
            free(p);
            flag = 1; /* Asciende revisando factores de balance */
            return t; /* Corrigiendo */
        }
        else   /* Tiene dos hijos */
        {
            if (t->bal<0)
            {
                /* Si cargado a la izquierda, elimina mayor descendiente hijo izq */
                p = t->left;
                while (p->right != NULL) p = p->right;
                t->clave = p->clave;
                key = p->clave; //busca hoja a eliminar
                t->left = deleteR(t->left);
                t->bal += flag; /* incrementa factor de balance */
            }
            else   /* Si cargado a la derecha, elimina menor descendiente hijo der */
            {
                p = t->right;
                while (p->left != NULL)
                    p = p->left;
                t->clave = p->clave;
                key = p->clave;
                t->right = deleteR(t->right);
                t->bal -= flag; /* decrementa balance */
            }
        }
    }

    /* Mantiene árbol balanceado avl. Sólo una o dos rotaciones por descarte */
    if (flag == 0 ) /* No hay que rebalancear. Sigue el ascenso, sin rebalancear */
        return t;

    /* Hay que revisar factores de balance en el ascenso*/
    if (t->bal < -1)  /* Si quedó desbalanceado por la izquierda y dejó de ser AVL */
    {
        if (t->left->bal > 0)  /*espejos casos c, d y e */
        {
            /* Si el hijo izquierdo está cargado a la derecha */
            t->left = lrot(t->left);
            flag = 1; /*Continuar revisando factores */
        }
        else if (t->left->bal == 0)
            flag = 0; /*No debe seguir el rebalance */
        else
            flag = 1;/* Debe seguir revisando factores de balance */
        t = rrot(t);
    }
    else if (t->bal > 1)  /* Si quedó desbalaceado por la derecha */
    {
        if (t->right->bal < 0)
        {
            /* Si hijo derecho está cargado a la izquierda */
            t->right = rrot(t->right);
            flag = 1; //debe seguir revisando. Caso d.
        }
        else if (t->right->bal == 0)
            flag = 0; /* No debe seguir el rebalance. Caso c. */
        else //positivo
            flag = 1;/* Debe seguir revisando factores de balance. Caso e. */
        t = lrot(t);
    }
    else if (t->bal == 0) /* Si estaba en +1 ó -1 y queda en cero */
        flag = 1; /* Debe seguir corrigiendo. Caso b.*/
    else /* Si estaba en cero y queda en -1 ó +1 */
        flag = 0; /* No debe seguir rebalanceando. Caso a.*/
    return t;
}

pnodo DescartarAVL(int clave, pnodo t)
{
	complejidad_AVL++;// Se va calculando la complejidad de computo.
    key = clave;
    t = deleteR(t);
    if (flag == 1) alto_avl--;
    return t;
}

pnodo deltreeR(pnodo t)
{
    if (t != NULL){
        t->left = deltreeR(t->left);
        t->right = deltreeR(t->right);
        free(t); //borra la raíz subárbol
    }
    return NULL;
}


pnodo deltree(pnodo t)
{
    alto_avl = 0;
    return deltreeR(t);
}


void inorder_datos(pnodo t)
{
    if (t != NULL){
        inorder_datos(t->left);
        Archivo_avl_datos<<t->clave<<" ";
        inorder_datos(t->right);
    }
}

void inorder_frecuencias(pnodo t)
{
    if (t != NULL){
        inorder_frecuencias(t->left);
        Archivo_avl_freq<<t->clave<<" ";
        inorder_frecuencias(t->right);
    }
}

void Buscar(pnodo t, int numero) // BUSQUEDA AVL
{
    if (t != NULL){
        Buscar(t->left, numero);
        if(t->clave==numero){
        	//cout<<"si se encuentra el elemento"<<endl;
        }
        Buscar(t->right, numero);
    }
}


bool busquedaRecAVL(pnodo t, int dato) // BUSQUEDA ABB
{
     int r=0;   // 0 indica que lo encontre
 
     if(t==NULL)
        return r;
 
     if(dato<t->clave)
         r = busquedaRecAVL(t->left, dato);
 
     else if(dato> t->clave)
         r = busquedaRecAVL(t->right, dato);
 
     else
        r = 1;   // son iguales, lo encontre
 
     return r;
}




//*************************************************************************************************************************
//*************************************************************************************************************************


void enOrden_Datos(ABB arbol) //Funcion que guarda en archivo los datos de los arboles abb.
{
     if(arbol!=NULL){
          enOrden_Datos(arbol->izq);
          //cout << arbol->nro << " ";
          Archivo_abb_datos<<arbol->nro << " ";
          enOrden_Datos(arbol->der);
     }
}

void enOrden_Frecuencias(ABB arbol) //Funcion que guarda en archivo las frecuencias de los arboles abb.
{
     if(arbol!=NULL){
          enOrden_Frecuencias(arbol->izq);
          //cout << arbol->nro << " ";
          Archivo_abb_freq<<arbol->nro << " ";
          enOrden_Frecuencias(arbol->der);
     }
}

void Crear_Arboles(map <int , vector<int> > Mapa_Datos, map <int , vector<int> > Mapa_Frecuencias,	vector<int> Busqueda_1, vector<int> Busqueda_2)
{

    cout<<"Comenzando a crear los arboles"<<endl;
	map <int, vector < int> >:: iterator iterador;


    map <int , ABB> Mapa_ABB_Datos; // Mapa de arbol abb de los datos
    map <int , ABB> Mapa_ABB_Frecuencias; // mapa de arbol abb de las frecuencias
    map <int , pnodo> Mapa_AVL_Datos; // Mapa de arbol avl de los datos
    map <int , pnodo> Mapa_AVL_Frecuencias; // Mapa de arbol avl de las frecuencias
    map <int , B_23> Mapa_23_Datos; // Mapa de arbol 2-3 de los datos
    map <int , B_23> Mapa_23_Frecuencias; // Mapa de arbol 2-3 de las frecuencias
    map <int , B_23> Mapa_BTREE_Datos; // Mapa de arbol b de los datos
    map <int , B_23> Mapa_BTREE_Frecuencias; // Mapa de arbol b de las frecuencias

    ABB Prueba;
    pnodo Prueba2; // Variables auxiliares.
    B_23 Prueba3;

	ABB Arbol_ABB_D;
    ABB Arbol_ABB_F;
	Arbol_ABB_D = NULL;
    Arbol_ABB_F = NULL;

    pnodo Arbol_AVL_D;
    pnodo Arbol_AVL_F;
    Arbol_AVL_D = NULL;
    Arbol_AVL_F = NULL;
    
    vector <int> Complejidad_ABB; // vector que contiene la complejidad de la creacion de arboles ABB.
	vector <int> Complejidad_AVL; // vector que contiene la complejidad de la creacion de arboles AVL.
	vector <int> Complejidad_23;  // vector que contiene la complejidad de la creacion de arboles 2-3.
	vector <int> Complejidad_B;   // vector que contiene la complejidad de la creacion de arboles B.
	
	ofstream Archivo_Complejidades; // Se avre un archivo de escritura para guardar las complejidades de computos de creacion de arboles
	Archivo_Complejidades.open("Complejidades.dat");
	Archivo_abb_datos.open("Arbol_ABB_Datos.dat");
	Archivo_abb_freq.open("Arbol_ABB_Frecuencias.dat");
	Archivo_Complejidades<<"Complejidad ABB"<<endl;
	Archivo_Complejidades<<endl;
//------------------------------------------------------------------------------------------------------------
    for(iterador =Mapa_Datos.begin(); iterador != Mapa_Datos.end(); ++iterador){ // Se recorre con un iterador el mapa de datos del archivo.
        for (int i =0;i<iterador->second.size(); i++){ // hasta que llegue al final de la primera linea.
            insertar( Arbol_ABB_D, iterador->second[i]); // Va mandando datos de la fila para crear el arbol abb.
        }
        Complejidad_ABB.push_back(complejidad_ABB); // Se ingresa la complejidad de creacion de la linea a un vector.
        Archivo_Complejidades<<complejidad_ABB<<" "; // Se escribe la complejidad en el archivo.
        complejidad_ABB=0;
        enOrden_Datos(Arbol_ABB_D); // Se llama la funcion para escribir el arbol abb en un archivo.
        Archivo_abb_datos<<endl;
        Mapa_ABB_Datos.insert(pair<int, ABB  >(iterador->first,Arbol_ABB_D)); // Se ingresa el arbol creado a un mapa de arboles abb
        Arbol_ABB_D = NULL;
    }    
    Archivo_abb_datos.close();

    for(iterador =Mapa_Frecuencias.begin(); iterador != Mapa_Frecuencias.end(); ++iterador){// Se recorre con un iterador el mapa de frecuencias de los datos del archivo.
        for (int i =0;i<iterador->second.size(); i++){// hasta que llegue al final de la primera linea.
            insertar( Arbol_ABB_F, iterador->second[i]); // Va insertando los terminos, osea las fecuencias de cada dato en un arbol abb
        }
        enOrden_Frecuencias(Arbol_ABB_F);// Se llama la funcion para escribir el arbol abb frecuencias en un archivo.
        Archivo_abb_freq<<endl;
        Mapa_ABB_Frecuencias.insert(pair<int, ABB  >(iterador->first,Arbol_ABB_F)); // se ingresa el arbol de frecuencias ceado a un mapa de arboles abb.
        Arbol_ABB_F = NULL;// el arbol se hace nulo.
    }   
	Archivo_abb_freq.close(); 
	Archivo_Complejidades<<endl;
//------------------------------------------------------------------------------------------------------------
	Archivo_Complejidades<<endl;
	Archivo_Complejidades<<"Complejidad AVL"<<endl;
	Archivo_Complejidades<<endl;
	Archivo_avl_datos.open("Arbol_AVL_Datos.dat"); // Se abre un archivo para guardar los arboles avl de datos
	Archivo_avl_freq.open("Arbol_AVL_Frecuencias.dat"); // Se abre un archivo para guardar los arboles avl de frecuencias
    for(iterador =Mapa_Datos.begin(); iterador != Mapa_Datos.end(); ++iterador){// Se recorre con un iterador el mapa de datos del archivo.
        for (int i =0;i<iterador->second.size(); i++){// hasta que llegue al final de la primera linea.
            Arbol_AVL_D=InsertarAVL(iterador->second[i], Arbol_AVL_D); // va mandando datos de la fila para crear un arbol AVL.
        }
        Complejidad_AVL.push_back(complejidad_AVL); // Se guarda en un vector la complejidad de creacion de un arbol avl.
        Archivo_Complejidades<<complejidad_AVL<<" ";
        complejidad_AVL=0;
        inorder_datos(Arbol_AVL_D); // Se llama la funcion para guardar en un archivo el arbol avl creado.
        Archivo_avl_datos<<endl;
        Mapa_AVL_Datos.insert(pair<int, pnodo  >(iterador->first,Arbol_AVL_D)); // S van guardando los arboles avl creados en un map.
        Arbol_AVL_D = NULL; // el arbol se hace nulo.
    }  
    
	Archivo_avl_datos.close(); // Se cierrra el archivo donde se guardan los arboles avl de datos.
    for(iterador =Mapa_Frecuencias.begin(); iterador != Mapa_Frecuencias.end(); ++iterador){// Se recorre con un iterador el mapa de frecuencias del archivo.
        for (int i =0;i<iterador->second.size(); i++){// Hasta el final de la primera fila de frecuencias.
            Arbol_AVL_F=InsertarAVL(iterador->second[i], Arbol_AVL_F);// Se van mandando fecuencias para crear un arbol avl de frecuencias.
        }
        Mapa_AVL_Frecuencias.insert(pair<int, pnodo  >(iterador->first,Arbol_AVL_F));// Se inserta en un mapa avl los arboles de frecuecias que se van creando.
        inorder_frecuencias(Arbol_AVL_F); // Funcion que guarda en un archivo los arboles avl de frecuencia.
        Archivo_avl_freq<<endl;
        Arbol_AVL_F = NULL; // Hacemos nulo el puntero del arbol.
    }  
    Archivo_avl_freq.close();// Se cierra el archivo donde se guardan los arboles avl de frecuencia.
//------------------------------------------------------------------------------------------------------------
	Archivo_Complejidades<<endl;
	Archivo_Complejidades<<"Complejidad 2-3"<<endl;
	Archivo_23_datos.open("Arbol_23_datos.dat"); // Se abre un archivo de escritura para guardar arboles 2-3 de datos
	Archivo_23_freq.open("Arbol_23_Frecuencias.dat"); // Se abre un archivo de escritura para guardar arboles 2-3 de frecuencias.
    BTree t(3);// Se hace b = 3 para simular el arbol 2-3.
    for(iterador =Mapa_Datos.begin(); iterador != Mapa_Datos.end(); ++iterador){// Se recorre con un iterador el mapa de datos del archivo.
        for (int i =0;i<iterador->second.size(); i++){ // Se recorre hasta el final de los datos de las key.
            t.insert(iterador->second[i]);// Se van insertando los datos de la fila en el arbol 2-3 de datos.
        }
        t.traverse_1();// Se llama la funcion para guardar en un archivo el arbol 2-3 de datos.
        Archivo_23_datos<<endl;
        Complejidad_23.push_back(complejidad_B);// Se guarda en un vector las complejidades de crear un arbol 2-3
        Archivo_Complejidades<<complejidad_B<<" ";
        Mapa_23_Datos.insert(pair<int, B_23  >(iterador->first,t.root)); // Se van ingresando en un map los arboles 2-3 creados.
        t.remove2(); // Hacemos nulo el puntero del arbol 2-3.
        complejidad_B=0;
    }
	Archivo_23_datos.close();// Se cierra el archivo donde se escriben los arboles 2-3 de datos.
    for(iterador =Mapa_Frecuencias.begin(); iterador != Mapa_Frecuencias.end(); ++iterador){ // Se recorre con un iterador el mapa de frecuencias.
        for (int i =0;i<iterador->second.size(); i++){// Hasta llegar al final dela linea de frecuencias de la key actual.
            t.insert(iterador->second[i]); // Se van insertando las frecuencias en el arbol 2-3.
        }
        t.traverse_2(); // Se llama la funcion para escribir el arbol 2-3 de frecuencias creado.
        Mapa_23_Frecuencias.insert(pair<int, B_23  >(iterador->first,t.root)); // Se ingresan a un mapa de arboles 2-3 de frecuencias.
        t.remove2(); // Se vuelve nulo el puntero.
    }
    Archivo_23_freq.close();// Se cierra el archivo donde guardamos los arboles 2-3 de frecuencias
//------------------------------------------------------------------------------------------------------------
	complejidad_B=0;
	Archivo_Complejidades<<endl;
	Archivo_Complejidades<<"Complejidad B"<<endl;
    BTree BT(6);
	Archivo_b_datos.open("Arbol_B_Datos.dat"); // Se abre un archivo para guardar los arboles de datos B.
	Archivo_b_freq.open("Arbol_B_Frecuencias.dat"); // Se abre un archivo para guardar los arboles B de frecuencias de los datos.
    for(iterador =Mapa_Datos.begin(); iterador != Mapa_Datos.end(); ++iterador){// Se recorre el map de datos por key.
        for (int i =0;i<iterador->second.size(); i++){// Hasta llegar al final de la linea de datos de cada key.
            BT.insert(iterador->second[i]); // Se insertan los datos a un arbol B.
        }
        Complejidad_B.push_back(complejidad_B); // Se va guardando la complejidad de creacion de arbol b en un vector.
        Archivo_Complejidades<<complejidad_B<<" ";
        BT.traverse_3();// Se llama a la funcion que escribe en un archivo los arboles B de datos creados.
        Archivo_b_datos<<endl;
        Mapa_BTREE_Datos.insert(pair<int, B_23  >(iterador->first,BT.root)); // Se van ingresando los arboles B creados a un map con sus key correspondientes.
        BT.remove2(); // Volvemos nulo el puntero del arbol b.
        complejidad_B=0;
    }
	Archivo_Complejidades.close(); // Se cierra el archivo donde se escribieron las complejidades de cada arbol.
	Archivo_b_datos.close();// Se cierra el archivo donde se escribieron los arboles B de datos.
    for(iterador =Mapa_Frecuencias.begin(); iterador != Mapa_Frecuencias.end(); ++iterador){// Se recorre el map de frecuencias por key.
        for (int i =0;i<iterador->second.size(); i++){// Hasta llegar al final de la linea de frecuencias de cada key.
            BT.insert(iterador->second[i]); // Se van insertando las frecuencias en un arbol B.
        }
        BT.traverse_4();
        Archivo_b_freq<<endl;// Se llama la funcion para escribir los arboles B de frecuencias en un archivo.
        Mapa_BTREE_Frecuencias.insert(pair<int, B_23  >(iterador->first,BT.root));// Se van agregando a un map los arboles B de frecuencias creados con su key correspondiente.
        BT.remove2();// volvemos nulo el puntero del arbol b de frecuencias.
    }
    Archivo_b_freq.close(); // Cerramos el archivo de escritura del arbol B de frecuencias.
//------------------------------------------------------------------------------------------------------------

	int totales =0;
    map <int, ABB>:: iterator ti; // Se crea un iterador tipo ABB
    map <int, pnodo>:: iterator ti2; // Se crea un iterador tipo AVL
    map <int , B_23>:: iterator ti3;// Se crea un iterador tipo B y 2-3
    
    int num=0;
    int num2;
    int r;
    long int tiempoComputo;
    
    ofstream tiempos_ABB;
    tiempos_ABB.open("TiemposABB.dat"); // Se abre un archivo para guardar los tiempos de busqueda de los arboles ABB.
	ofstream tiempos_AVL;
    tiempos_AVL.open("TiemposAVL.dat");// Se abre un archivo para guardar los tiempos de busqueda de los arboles AVL.
    ofstream tiempos_23;
    tiempos_23.open("Tiempos23.dat");// Se abre un archivo para guardar los tiempos de busqueda de los arboles 2-3.
    ofstream tiempos_B;
    tiempos_B.open("TiemposB.dat");// Se abre un archivo para guardar los tiempos de busqueda de los arboles B.

    //Comienzo de las busquedas
//-----------------------------------------------------------------------------------------------------------------    
    //cout<<"Tiempo de arbol abb Datos: "<<endl;
    tiempos_ABB<<"Tiempo de arbol abb Datos: "<<endl;
    tiempos_ABB<<endl;
    
    for(ti = Mapa_ABB_Datos.begin(); ti != Mapa_ABB_Datos.end(); ++ti){ // Se recorre el mapa de aroboles abb de datos con un iterador.
        Prueba=ti->second;// Se copia uno de los arboles en Prueba.
        num2=Busqueda_1[num]; // Se obtiene uno de los datos para las busquedas.
        
        clock_gettime(CLOCK_MONOTONIC, &tiempo1); // Se toma el tiempo de inicio.
        r=busquedaRec(Prueba, num2);// Se llama la funcion buscar con el arbol y el dato correspondiente ABB.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Se toma el tiempo termino.
        diff_time(&tiempo2, &tiempo1, &latencia); // Se saca la diferencia de ambos tiempos.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se consigue el tiempo en nanosegundos.
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_ABB<<tiempoComputo<<" "; // Se guarda dentro de un archivo los tiempos ABB.
        //if(r==1)
        //	cout<<"si se encuentra"<<endl;
        totales++;
        Prueba=NULL;
        num++;
    }
    tiempos_ABB<<endl;
    num=0;
    //cout<<"Tiempo de arbol abb Frecuencias: "<<endl;
    tiempos_ABB<<"Tiempo de arbol abb Frecuencias: "<<endl;
    tiempos_ABB<<endl;
    for(ti = Mapa_ABB_Frecuencias.begin(); ti != Mapa_ABB_Frecuencias.end(); ++ti){ // Se recorre el mapa de arboles abb de frecuencias
        Prueba=ti->second; // Se saca un arbol.
        num2=Busqueda_2[num];
        clock_gettime(CLOCK_MONOTONIC, &tiempo1); // Tomamos el tiempo de inicio.
        r=busquedaRec(Prueba, num2);
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Tomamos el tiempo de temino
        diff_time(&tiempo2, &tiempo1, &latencia);// Sacamos la difirencia de ambos tiempos.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // obtenemos el tiempo en nanosegundos
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_ABB<< tiempoComputo<<" "; // se guarda en un archivo los tiempos de  busqueda de frecuencias de los arboles
        //if(r==1)
        //	cout<<"si se encuentra"<<endl;
        totales++;
        Prueba=NULL;
        num++;
    }
//-----------------------------------------------------------------------------------------------------------------
	tiempos_ABB<<endl;
	tiempos_ABB<<"Final";
	tiempos_ABB.close();
	
	num=0;
    //cout<<"Tiempo de arbol AVL Datos: "<<endl;
    tiempos_AVL<<"Tiempo de arbol AVL Datos: "<<endl;
    tiempos_AVL<<endl;
    for(ti2 = Mapa_AVL_Datos.begin(); ti2 != Mapa_AVL_Datos.end(); ++ti2){// Se recorre el map de arboles de datos AVL.
        Prueba2=ti2->second; // Se obtiene un arbol avl de datos
        num2=Busqueda_1[num]; // Se obtiene un dato para iniciar la busqueda.

        clock_gettime(CLOCK_MONOTONIC, &tiempo1);// Se comienzan a tomar el tiempo de incio.
        r=busquedaRecAVL(Prueba2, num2); // Mandamos a la funcion de busqueda el arbol y  el dato.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Se saca el tiempo e termino.
        diff_time(&tiempo2, &tiempo1, &latencia); // Se saca la diferencia de ambos tiempos para obtener el especifico.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se obtiene el tiempo en nanosegundos.
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_AVL<< tiempoComputo<<" "; // Se guardan en un archivo los tiempos de buesquedas de datos avl.
        totales++;
        Prueba=NULL;
        num++;
    }
    tiempos_AVL<<endl;
    num=0;
    //cout<<"Tiempo de arbol AVL Frecuencias: "<<endl;
    tiempos_AVL<<"Tiempo de arbol AVL Frecuencias: "<<endl;
    tiempos_AVL<<endl;
    for(ti2 = Mapa_AVL_Frecuencias.begin(); ti2 != Mapa_AVL_Frecuencias.end(); ++ti2){ // Se recorre el mapa de arboles avl de frecuencias
        Prueba2=ti2->second;// Se obtiene un arbol avl de frecuencias del map.
        num2=Busqueda_2[num];// Obtenemos un termino para iniciar la busqueda.
        
        clock_gettime(CLOCK_MONOTONIC, &tiempo1);// Se toma el tiempo de inicio.
        r=busquedaRecAVL(Prueba2, num2);// Se realiza la busqueda con el arbol y un dato.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Se toma el tiempo de termino,
        diff_time(&tiempo2, &tiempo1, &latencia);// Se realiza una diferencia entre ambos para obetener el tiempo de la busuqeda.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se obtiene el tiempo en nanosegundos.
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_AVL<< tiempoComputo <<" ";
        totales++;
        Prueba=NULL;
        num++;
    }
	tiempos_AVL<<endl;
	tiempos_AVL<<"Final";
	tiempos_AVL.close();


//-----------------------------------------------------------------------------------------------------------------

	num=0;
    //cout<<"Tiempo de arbol 2-3 Datos: "<<endl;
    tiempos_23<<"Tiempo de arbol 2-3 Datos: "<<endl;
    tiempos_23<<endl;
    for(ti3 = Mapa_23_Datos.begin(); ti3 != Mapa_23_Datos.end(); ++ti3){ // Se recorre el mapa de arboles 2-3 de datos
        Prueba3=ti3->second; // Obtenemos un arbol 2-3.
        num2=Busqueda_1[num]; // Sacamos un numero del vector de busquedas.
        t.root=Prueba3;
        clock_gettime(CLOCK_MONOTONIC, &tiempo1); // Sacamos el tiempo de inicio.
        t.search(num2);// Mandamos el numero a la busqueda de arbol 2-3 de datos.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Tiempo de termino
        diff_time(&tiempo2, &tiempo1, &latencia); // Diferencia entre tiempo de inicio y final.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // obtencion de tiempo en nanosegundos
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_23<< tiempoComputo <<" "; // Se escribe en un archivo
        t.remove2();
        Prueba3=NULL;
        num++;
        totales++;
    }
    tiempos_23<<endl;
    
    num=0;
    //cout<<"Tiempo y complejidad de arbol 2-3 Frecuencias: "<<endl;
    tiempos_23<<"Tiempo y complejidad de arbol 2-3 Frecuencias: "<<endl;
    for(ti3 = Mapa_23_Frecuencias.begin(); ti3 != Mapa_23_Frecuencias.end(); ++ti3) { // Se recorre el map de arboles 2-3 de frecuencias
        Prueba3=ti3->second; // Se obtiene un arbol 2-3 de frecuencia.
        num2=Busqueda_2[num];// Se obtiene un dato de frecuencia para la busqueda.
        t.root=Prueba3; // Se agrega el arbol a la clase.
        clock_gettime(CLOCK_MONOTONIC, &tiempo1);// Se toma el tiempo de inicio.
        t.search(num2);// Se inicia la busqueda del arbol 2-3 de frecuencias.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2); // Se saca el tiempo de termino.
        diff_time(&tiempo2, &tiempo1, &latencia); // Se realiza la diferencia entre ambos tiempos para obetener el tiempo especifico.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se obtiene el tiempo en nanosegundos de la busqueda.
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_23<< tiempoComputo << " "; // Se escribe en un archivo el tiempo obtenido.
        t.remove2();       // Se vuelve nulo el puntero del arbol 2-3. 
        Prueba3=NULL;
        num++;
        totales++;
    }
	tiempos_23<<endl;
	tiempos_23<<"Final";
	tiempos_23.close(); // Se cierra el archivo 



//-----------------------------------------------------------------------------------------------------------------	
	num=0;
    //cout<<"Tiempo y complejidad de arbol b Datos: "<<endl;
    tiempos_B<<"Tiempo y complejidad de arbol b Datos: "<<endl;
    for(ti3 = Mapa_BTREE_Datos.begin(); ti3 != Mapa_BTREE_Datos.end(); ++ti3){// Se recorre el mapa de arboles b de datos.
        Prueba3=ti3->second; // Se obtiene un arbol b del map.
        num2=Busqueda_1[num];// Se obtiene un valor del vector de datos de busqueda.
        BT.root=Prueba3;// Se iguala a una variable auxilair
        clock_gettime(CLOCK_MONOTONIC, &tiempo1);// se saca el tiempo de inicio.
        BT.search(num2);
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Se saca el tiempo de termino.
        diff_time(&tiempo2, &tiempo1, &latencia);// Se saca la diferencia de ambos tiempos.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se obtiene el tiempo de busqueda en nanosegundos.
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_B<< tiempoComputo << " "; // Se escriben en un rchivo los tiempos obtenidos.
        BT.remove2();// Volvemos nulo en puntero del arbol B.
        Prueba3=NULL;
        num++;
        totales++;
    }
    tiempos_B<<endl;
    num=0;
    //cout<<"Tiempo y complejidad de arbol b Frecuencias: "<<endl;
    tiempos_B<<"Tiempo y complejidad de arbol b Frecuencias: "<<endl;
    for(ti3 = Mapa_BTREE_Frecuencias.begin(); ti3 != Mapa_BTREE_Frecuencias.end(); ++ti3){ // Se recorre el mapa de arboles B de frecuencia.
        Prueba3=ti3->second; // Se saca un arbol B del mapa.
        num2=Busqueda_2[num];// se obtiene un valor de frecuencia para iniciar la busqueda.
        BT.root=Prueba3; // Se iguala el arbol B a la clase.
        clock_gettime(CLOCK_MONOTONIC, &tiempo1); // Se inicia el tiempo de busuqueda
        BT.search(num2); // Se inicia la busqued del dato en el arbol B de frecuencias.
        clock_gettime(CLOCK_MONOTONIC, &tiempo2);// Se inicia el tiempo de termino.
        diff_time(&tiempo2, &tiempo1, &latencia);// Se saca la diferencia de ambos tiempos para sacar el tiempo especifico.
        
        tiempoComputo = latencia.tv_sec*1000000000 + latencia.tv_nsec; // Se obtiene el tiempo en nanosegundos
        //cout << "Tiempo en nanosegundos:" << tiempoComputo << endl;
        tiempos_B<< tiempoComputo << " "; // Se escribe en un archivo los tiempos obtenidos.
        BT.remove2(); // Volvemos nulo el puntero del arbol B.       
        Prueba3=NULL;
        num++;
        totales++;
    }
    
	tiempos_B<<endl;
	tiempos_B<<"Final";
	tiempos_B.close();// Se cierra el archivo donde se guardan los tiempos de busqueda.
//-----------------------------------------------------------------------------------------------------------------
	cout<<totales<<endl;

}

int abrir_archivo()
{
    cout<<"Ejecutando el programa..."<<endl;
	vector<int> Busqueda_1; // Vector que almacena datos para ralizar las busquedas en los arboles de datos.
	vector<int> Busqueda_2;// Vector que almacena frecuencias para ralizar las busquedas en los arboles de frecuencias.
	vector<int> Datos;
	vector<int> Vector_Principal; // Vector de datos sin datos repetidos
	vector<int> Vector_Frecuencia;// Vector con las frecuencias de los datos del vector de arriba.
	map <int , vector<int> > Mapa_Datos; // Mapa de los datos del archivo.
	map <int , vector<int> > Mapa_Frecuencias;// Mapa de las frecuencias de los datos del archvo.
	ifstream Archivo; // funcion abrir archivo.
	Archivo.open("ubLista3Mb_Factor2_64.dat"); // Se abre el archivo con miles de datos.
	int key; // se declara la key de los maps
	int dato;
	int DATOS_TOTALES; // cantidad de datos en una fila.
	int contador=0;	
	int inservible; // dato inservible dentro de la linea.
	int Numero_Final_Busqueda = 0;
	int numero;
	
	while(!Archivo.eof()) // mientras la lectura del archivo no llegue al final.
	{
		Archivo>>key; // Recibe la key que es el primer elemento de una fila.
		Archivo>>inservible; // recibe el segundo elemento de la fila que no sirve.
		Archivo>>inservible;// recibe el tercer elemento de la fila que tampoco sirve.
		Archivo>>DATOS_TOTALES; // recibe el cuarto elemento de la fila que es igual a la cantidad de datos de la fil.
		contador=0;
		while(DATOS_TOTALES!=contador) // Mietras contador sea distinto a la cantidad de datos de una fila.
		{
			Archivo>>dato; // Se lee un dato de la fila
			Datos.push_back(dato); // se guarda en un vector de datos.
			contador++; // el contador aumenta en 1.
		}
		
		for(int i=0; i<DATOS_TOTALES;i++){ // for encargado de crear un vector de datos no repetidos
			if(i==0)
			{
				Vector_Principal.push_back(Datos[0]); // agrega al vector pincipal el primer elemento de la fila.
				Numero_Final_Busqueda++;
			}
			else{
				numero = Datos[i];
				numero=esta(numero,Vector_Principal,Numero_Final_Busqueda);// Se envia a una fncion que retorna si esta el elemento repetido.
				if(numero==0){
					Vector_Principal.push_back(Datos[i]);// Asi se crea un vector con elementos no repetidos para poder sacar las frecuencias.
					Numero_Final_Busqueda++;					
				}
			}
		}
		for(int i=0; i<Numero_Final_Busqueda; i++) // For para sacar las frecuencias de los datos del vector.
		{
			numero=Vector_Principal[i];
			numero=frecuencia(numero,Datos, DATOS_TOTALES); // Funcion que retorna la frecuencia de un dato de nuestro vector sin repeticiones.
			Vector_Frecuencia.push_back(numero); // Se agrega a la misma posicion de otro vector el dato y su frecuencia.
		}
		Busqueda_1.push_back(Vector_Principal[Numero_Final_Busqueda-1]); // Se crea un vector de datos para busqueda 	
		Busqueda_2.push_back(Vector_Frecuencia[Numero_Final_Busqueda-1]); // se crea un vector de frecuencias para busqueda.
		Mapa_Datos.insert(pair<int,vector<int> >(key,Vector_Principal)); // se agrega al map de datos su key y su vector de datos.
		Mapa_Frecuencias.insert(pair<int,vector<int> >(key,Vector_Frecuencia));// Se crea un map con la key aterior pero con un vector de frecuencias.
		Numero_Final_Busqueda=0;
		Datos.clear();// Se limpan los vectores.
		Vector_Principal.clear();// Se limpan los vectores.
		Vector_Frecuencia.clear();// Se limpan los vectores.
	}
	cout<<endl;
	cout<<endl;
	cout<<"Archivo cargado Completamente"<<endl;	
	Crear_Arboles(Mapa_Datos,Mapa_Frecuencias, Busqueda_1, Busqueda_2 );// Se llama a la funcion para la creacion de arboles.
    cout<<"Arboles creados Exitosamente"<<endl;
	Archivo.close(); // Se cierra el archivo de los miles de datos.
	return 0;
}

int main(){ // Funion main principal.
	abrir_archivo();
	return 0;
}
