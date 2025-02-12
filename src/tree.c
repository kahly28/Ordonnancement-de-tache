#include "../include/tree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/list.h"
#include "../include/util.h"
#include "../include/algo.h"


/********************************************************************
 * tree_node_t
 ********************************************************************/

/**
 * @brief
 * Construire et initialiser un nouveau nœud d'un arbre binaire de recherche.
 * Le facteur d'équilibre est initialisé à zero.
 * 
 * @param[in] key Clé du nouveau nœud.
 * @param[in] data Donnée à affecter au nouveau nœud.
 * @return struct tree_node_t* Le nouveau nœud créé.
 */
static struct tree_node_t * new_tree_node(void * key, void * data) {
	
	struct tree_node_t * newNode = calloc(1,sizeof(struct tree_node_t));

	assert(newNode);
	if ( newNode == NULL)
	{
		printf("Unable to alocate memory, Free some space");
	}
	else
	{
		set_bfactor(newNode,0);
		set_tree_node_key(newNode,key);
		set_tree_node_data(newNode,data);
		newNode->left = NULL;
		newNode->right = NULL;
	}

	return newNode;
}

int tree_node_is_empty(struct tree_node_t * node) {

	if(node == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void * get_tree_node_key(const struct tree_node_t * node) {

	return node->key;
}

void * get_tree_node_data(const struct tree_node_t * node) {

	return node->data;
}

struct tree_node_t * get_left(const struct tree_node_t * node) {

	return node->left;
}

struct tree_node_t * get_right(const struct tree_node_t * node) {

	return node->right;
}

int get_bfactor(const struct tree_node_t * node) {

	return node->bfactor;
}

void set_tree_node_key(struct tree_node_t * node, void * newKey) {
	
	node->key = newKey;
}

void set_tree_node_data(struct tree_node_t * node, void * newData) {
	
	node->data = newData;
}

void set_left(struct tree_node_t * node, struct tree_node_t * newLeft) {
	
	node->left = newLeft;
}

void set_right(struct tree_node_t * node, struct tree_node_t * newRight) {
	
	node->right = newRight;
}

void increase_bfactor(struct tree_node_t * node) {

	node->bfactor = node->bfactor + 1;
}

void decrease_bfactor(struct tree_node_t * node) {

	node->bfactor = node->bfactor - 1;
}

void set_bfactor(struct tree_node_t * node, int newBFactor) {

	node->bfactor = newBFactor;
}

/*********************************************************************
 * tree_t
 *********************************************************************/

struct tree_t * new_tree(int balanced, int (*preceed)(const void *, const void *),
							void (*viewKey)(const void *), void (*viewData)(const void *),
							void (*freeKey)(void *), void (*freeData)(void *)) {
	
	struct tree_t * T = malloc(sizeof(struct tree_t));
	set_root(T,NULL);
	T->numelm = 0;
	T->balanced = balanced;
	T->preceed = preceed;
	T->viewKey = viewKey;
	T->viewData = viewData;
	T->freeKey = freeKey;
	T->freeData = freeData;


	return T;

	
}

int tree_is_empty(struct tree_t * T) {
	
	if ( T->numelm == 0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int tree_is_balanced(struct tree_t * T) {
	assert(T);
	return T->balanced;


}

int get_tree_size(const struct tree_t * T) {

	return T->numelm;
}


struct tree_node_t * get_root(const struct tree_t * T) {
	
	return T->root;
}

void increase_tree_size(struct tree_t * T) {
	
	T->numelm = T->numelm + 1;
}

void decrease_tree_size(struct tree_t * T) {
	
	T->numelm = T->numelm - 1;
}

void set_root(struct tree_t * T, struct tree_node_t * newRoot) {
	
	T->root = newRoot;
}

/**
 * @brief
 * Libérer récursivement le sous-arbre raciné au nœud curr.
 * Dans le cas où le pointeur de fonction freeKey (resp. freeData) n'est pas NULL,
 * la mémoire de la clé (resp. de la donnée) du nœud actuel est aussi libérée.
 * NB : procédure récursive.
 * 
 * @param[in] curr 
 * @param[in] freeKey 
 * @param[in] freeData 
 */
//Ajouter static
static void delete_tree_node(struct tree_node_t * curr, void (*freeKey)(void *), void (*freeData)(void *)) 
{
	
	if(tree_node_is_empty(curr) == 1)
	{
		return;
	}
	else {

	
		delete_tree_node(get_left(curr),freeKey,freeData);
		delete_tree_node(get_right(curr),freeKey,freeData);
		if(freeKey)
		{
			freeKey(get_tree_node_key(curr));
		}
		if(freeData)
		{
			freeData(get_tree_node_data(curr));
		}
		//void *temp = &curr;
		free(curr);
		curr = NULL;
	}


}

/**
 * NB : Utiliser la procédure récursive delete_tree_node.
 * Vous devez utiliser les bons paramètres freeKey et freeData
 * par rapport aux valeurs deleteKey et deleteData.
 */
void delete_tree(struct tree_t * T, int deleteKey, int deleteData) {
	assert(deleteKey == 0 || deleteKey == 1);
	assert(deleteData == 0 || deleteData == 1);
	
	struct tree_node_t * Node = get_root(T);
	if(deleteKey == 0 && deleteData == 0)
	{
		delete_tree_node(Node,NULL,NULL);
	}
	else if(deleteKey == 1 && deleteData == 0)
	{
		delete_tree_node(Node,T->freeKey,NULL);
	}
	else if (deleteKey == 0 && deleteData == 1)
	{
		delete_tree_node(Node,NULL,T->freeData);
	}
	else
	{
		delete_tree_node(Node,T->freeKey,T->freeData);
	}
	free(T);
	T = NULL;

	
}

/**
 * @brief
 * Afficher récursivement le sous-arbre raciné au nœud curr
 * en utilisant un ordre infixe.
 * NB : procédure récursive.
 *
 * @param[in] curr 
 * @param[in] viewKey 
 * @param[in] viewData 
 */;

static void view_tree_inorder(struct tree_node_t * curr, void (*viewKey)(const void *), void (*viewData)(const void *)) 
{
	if(tree_node_is_empty(curr) == 0)
	{
		if(tree_node_is_empty(get_left(curr)) == 0)
		{
			view_tree_inorder(get_left(curr),viewKey,viewData);
		}
		printf("key =  \n");
		viewKey(get_tree_node_key(curr));
		printf("data = \n");
		viewData(get_tree_node_data(curr));
		printf("bfactor = %d\n",get_bfactor(curr));
		//printf("bfactor = %d\n",get_bfactor(curr));
		printf("\n");
		if(tree_node_is_empty(get_right(curr)) == 0)
		{
			view_tree_inorder(get_right(curr),viewKey,viewData);
		}
	}
}

/**
 * NB : Utiliser la procédure récursive view_tree_inorder.
 */

void view_tree(const struct tree_t * T) {
	
	//struct tree_node_t * root = get_root(T);
	printf("view_tree\n");
	view_tree_inorder(get_root(T),T->viewKey,T->viewData);

}

/**
 * @brief
 * Effectuer une rotation gauche autour du nœud \p y.
 * N'oubliez pas à mettre à jour les facteurs d'équilibre (bfactor) des nœuds
 * modifiés. Pour ce dernier, il y a 5 cas à considérer :
 * (+) bfactor(y)=-2 et bfactor(y->right)=-1
 * (+) bfactor(y)=-2 et bfactor(y->right)=0
 * (+) bfactor(y)=-1 et bfactor(y->right)=1
 * (+) bfactor(y)=-1 et bfactor(y->right)=-1
 * (+) bfactor(y)=-1 et bfactor(y->right)=0
 * (+) bfactor(y)=-2 et bfactor(y->right)=-2
 * 
 * @param[in] y 
 * @return struct tree_node_t* 
 */
static struct tree_node_t * rotate_left(struct tree_node_t * x) {
	assert(x);
	assert(get_right(x));

	struct tree_node_t * y;
	y = get_right(x);
	set_right(x,get_left(y));
	set_left(y,x);
	if(get_bfactor(x) == -2 && get_bfactor(y) == -1)
	{
		set_bfactor(x,0);
		set_bfactor(y,0);
	}
	else if(get_bfactor(x) == -2 && get_bfactor(y) == 0)
	{
		set_bfactor(x,-1);
		set_bfactor(y,1);
	}
	else if(get_bfactor(x) == -1 && get_bfactor(y) == 1)
	{
		set_bfactor(x,0);
		set_bfactor(y,2);
	}
	else if(get_bfactor(x) == -1 && get_bfactor(y) == -1)
	{
		set_bfactor(x,1);
		set_bfactor(y,1);
	}
	else if(get_bfactor(x) == -1 && get_bfactor(y) == 0)
	{
		set_bfactor(x,0);
		set_bfactor(y,1);
	}
	else if(get_bfactor(x) == -2 && get_bfactor(y) == -2)
	{
		set_bfactor(x,1);
		set_bfactor(y,0);
	}

	return y;


}

/**
 * @brief
 * Effectuer une rotation droite autour du nœud \p x.
 * N'oubliez pas à mettre à jour les facteurs d'équilibre (bfactor) des nœuds
 * modifiés. Pour ce dernier, il y a 5 cas à considérer :
 * (+) bfactor(x)=2 et bfactor(x->left)=1
 * (+) bfactor(x)=2 et bfactor(x->left)=0
 * (+) bfactor(x)=1 et bfactor(x->left)=1
 * (+) bfactor(x)=1 et bfactor(x->left)=-1
 * (+) bfactor(x)=1 et bfactor(x->left)=0
 * (+) bfactor(x)=2 et bfactor(x->left)=2
 * 
 * @param[in] x 
 * @return struct tree_node_t* 
 */
static struct tree_node_t * rotate_right(struct tree_node_t * x) {
	assert(x);
	assert(get_left(x));



	struct tree_node_t * y;
	y = get_left(x);
	set_left(x,get_right(y));
	set_right(y,x);

	//viewInt(get_tree_node_key(get_right(y)));
	if(get_bfactor(x) == 2 && get_bfactor(y) == 1)
	{
		set_bfactor(x,0);
		set_bfactor(y,0);
	}
	else if(get_bfactor(x) == 2 && get_bfactor(y) == 0)
	{
		set_bfactor(x,1);
		set_bfactor(y,-1);
	}
	else if(get_bfactor(x) == 1 && get_bfactor(y) == 1)
	{
		set_bfactor(x,-1);
		set_bfactor(y,-1);
	}
	else if(get_bfactor(x) == 1 && get_bfactor(y) == -1)
	{

		set_bfactor(x,0);
		set_bfactor(y,-2);
	}
	else if(get_bfactor(x) == 1 && get_bfactor(y) == 0)
	{
		set_bfactor(x,0);
		set_bfactor(y,-1);
	}
	else if(get_bfactor(x) == 2 && get_bfactor(y) == 2)
	{
		set_bfactor(x,-1);
		set_bfactor(y,0);
	}

	return y;
	
}

/**
 * @brief
 * Insérer un nouveau nœud de clé \p key et donnée \p data
 * au sous-arbre binaire de recherche raciné au nœud \p curr.
 * Les clés sont comparées en utilisant le pointeur de fonction \p preceed.
 * N'oubliez pas à mettre à jour la facteur d'équilibre du nœud \p curr.
 * N'oubliez pas à faire les rotations nécessaires (4 cas à considérer)
 * si le paramètre \p balanced indique que l'arbre est équilibré.
 * La fonction renvoie le nœud curant éventuellement mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in] curr 
 * @param[in] key 
 * @param[in] data 
 * @param[in] balanced 
 * @param[in] preceed 
 * @return struct tree_node_t* 
 */
static struct tree_node_t * insert_into_tree_node(struct tree_node_t * curr, void * key, void * data,
											int balanced, int (*preceed)(const void *, const void *)) {
	// PARTIE 1 :
	// Mettez ici le code de l'insertion:
	// - exception
	// - recherche récursif de la position à insérer
	// - mise à jour du facteur d'équilibre
	//Si la racine est nulle, creer nv et retourner
//	printf("insert intro \n");
	if(tree_node_is_empty(curr)==1)	
	{
		curr = new_tree_node(key,data);
		set_bfactor(curr,0);
	}

	if(preceed(get_tree_node_key(curr),key) == 1 && preceed(key,get_tree_node_key(curr)) == 0)
	{	 
		if(tree_node_is_empty(get_left(curr)) == 1)
		{
			set_left(curr,insert_into_tree_node(get_left(curr),key,data,balanced,preceed));
			increase_bfactor(curr);

		}
		else
		{
			int oldbfactor = get_bfactor(get_left(curr));
			set_left(curr,insert_into_tree_node(get_left(curr),key,data,balanced,preceed));
			if(oldbfactor==0 && get_bfactor(get_left(curr)) != 0)// || get_bfactor(get_left(curr)) == -1)
			{
				increase_bfactor(curr);

			}

		}



	}


	//Si la racine est inf a la clef donne
	else if( preceed(key,get_tree_node_key(curr)) == 1 && preceed(get_tree_node_key(curr),key)==0)
	{
	//	printf("ici normalement\n");
		if(tree_node_is_empty(get_right(curr)) == 1)
		{
			set_right(curr,insert_into_tree_node(get_right(curr),key,data,balanced,preceed));
			decrease_bfactor(curr);
		}
		else
		{
			int oldbfactor = get_bfactor(get_right(curr));
			set_right(curr,insert_into_tree_node(get_right(curr),key,data,balanced,preceed));
			if(oldbfactor==0 && get_bfactor(get_right(curr)) != 0)// || get_bfactor(get_right(curr)) == -1)
			{
				decrease_bfactor(curr);
			}
		}
	}
	if (balanced) {
		// PARTIE 2 :
		// Gérer ici les rotations
		if(get_bfactor(curr) == 2 && get_bfactor(get_left(curr)) >= 1)
		{
			curr = rotate_right(curr);
		}

		else if(get_bfactor(curr) == 2 && get_bfactor(get_left(curr)) <= -1)
		{
			struct tree_node_t * y;
			y = get_left(curr);
			y = rotate_left(y);
			set_left(curr,y);
			curr = rotate_right(curr);
		}
		else if(get_bfactor(curr) == -2 && get_bfactor(get_right(curr)) <= -1)
		{				
			curr = rotate_left(curr);
		}
		else if(get_bfactor(curr) == -2 && get_bfactor(get_right(curr)) >= 1)
		{
			struct tree_node_t * y;
			y = get_right(curr);
			y = rotate_right(y);
			set_right(curr,y);
			curr = rotate_left(curr);
		}
	
	}
	
	
	return curr;
}

/**
 * NB : Utiliser la fonction récursive insert_into_tree_node.
 */

void tree_insert(struct tree_t * T, void * key, void * data) {
	assert(T);

	if(tree_is_empty(T)==1)
	{
		struct tree_node_t * N = insert_into_tree_node(get_root(T),key,data,T->balanced,T->preceed);
		set_root(T,N);
	}
	else{
		struct tree_node_t * N2 = insert_into_tree_node(get_root(T),key,data,T->balanced,T->preceed);
		set_root(T,N2);
	}
	increase_tree_size(T);

	
}

struct tree_node_t * tree_min(struct tree_node_t * curr) {
	assert(!tree_node_is_empty(curr));
	
	if(tree_node_is_empty(get_left(curr)))
	{
		return curr;
	}
	else
	{
		return tree_min(get_left(curr));
	}


}

struct tree_node_t * tree_max(struct tree_node_t * curr) {
	assert(!tree_node_is_empty(curr));
	
	if(tree_node_is_empty(get_right(curr)))
	{
		return curr;
	}
	else
	{
		return tree_max(get_right(curr));
	}

}

struct tree_node_t * tree_find_node(struct tree_node_t * curr, void * key, int (*preceed)(const void *, const void *)) {
	assert(!tree_node_is_empty(curr));

	//if (get_tree_node_key(curr) ==  key)
	if(preceed(get_tree_node_key(curr),key)  == 0 && preceed(key,get_tree_node_key(curr)) == 0 )
	{
		return curr;
	}
	// Si clé plus petit
	else if(preceed(key,get_tree_node_key(curr)) == 0 )
	{
		return tree_find_node(get_left(curr),key,preceed);
	}
	// SI clé plus grand
	else if (preceed(key,get_tree_node_key(curr)) == 1)
	{
		return tree_find_node(get_right(curr),key,preceed);
	}

}


// Fonction pour trouver le prédécesseur d'une clé dans un arbre binaire de recherche
struct tree_node_t * tree_find_predecessor(struct tree_node_t * curr, void * key, int (*preceed)(const void *, const void *)) 
{
	assert(!tree_node_is_empty(curr));
 
    // Si la clé est supérieure à la clé du noeud courant, le prédécesseur doit être dans le sous-arbre droit
	if(preceed(key,get_tree_node_key(curr)) == 1 && preceed(get_tree_node_key(curr),key) == 0)
	{
        struct tree_node_t * rightPredecessor = tree_find_predecessor(get_left(curr), key,preceed);
	return rightPredecessor;
    }
    // Si la clé est inférieure ou égale à la clé du noeud courant, le prédécesseur doit être dans le sous-arbre gauche
    else {
		if(tree_node_is_empty(get_right(curr))==1)
		{
			return curr;
		}
		else{
			return tree_find_predecessor(get_right(curr), key,preceed);

		}
    }
}








// Fonction pour trouver le successeur d'une clé dans un arbre binaire de recherche
struct tree_node_t * tree_find_successor(struct tree_node_t * curr, void * key, int (*preceed)(const void *, const void *))    // Si l'arbre est vide, il n'y a pas de successeur
{   
	assert(!tree_node_is_empty(curr));

    // Si la clé est inférieure à la clé du noeud courant, le successeur doit être dans le sous-arbre gauche
	if(preceed(key,get_tree_node_key(curr)) == 0 && preceed(get_tree_node_key(curr),key) == 1 )
	{
        struct tree_node_t * leftSuccessor = tree_find_successor(get_right(curr),key,preceed);
        // Si le sous-arbre gauche ne contient pas de successeur, le successeur est le noeud courant
		return leftSuccessor;
    }
    // Si la clé est supérieure ou égale à la clé du noeud courant, le successeur doit être dans le sous-arbre droit
    else {
		if(tree_node_is_empty(get_left(curr)) == 1)
		{
			return curr;
		}
		else
		{
			return tree_find_successor(get_left(curr), key, preceed);

		}
    }
}


/**
 * @brief 
 * Supprimer le nœud de clé \p key du sous-arbre binaire de recherche raciné au nœud \p curr.
 * La donnée du nœud supprimé est restituée en utilisant le pointeur \p data (passage de paramètre par référence).
 * Les clés sont comparées en utilisant le pointeur de fonction \p preceed.
 * N'oubliez pas à mettre à jour la facteur d'équilibre du nœud \p curr.
 * N'oubliez pas à faire les rotations nécessaires (6 cas à considérer)
 * si le paramètre \p balanced indique que l'arbre est équilibré.
 * La fonction renvoie le nœud curant éventuellement mis à jour.
 * NB : fonction récursive.
 * 
 * @param[in] curr 
 * @param[in] key 
 * @param[out] data 
 * @param[in] balanced 
 * @param[in] preceed 
 * @return struct tree_node_t* 
 */
//Il faut ajouter static
static struct tree_node_t * remove_tree_node(struct tree_node_t * curr, void * key, void ** data, int balanced, 
											int (*preceed)(const void *, const void *)) {
	assert(curr);
	// PARTIE 1 :
	// Mettez ici le code de la suppression:
	// - exception
	// - recherche récursif de la clé à supprimer
	// - mise à jour du facteur d'équilibre

	// A FAIRE
//	viewInt(key);
	//Noeud vide
	if(tree_node_is_empty(curr) == 1)
	{
		return NULL;
	}

	//Si la cle est plus petite
	else if(preceed(key,get_tree_node_key(curr)) == 0 && preceed(get_tree_node_key(curr),key) == 1)
	{
		int oldbfactor = get_bfactor(get_left(curr));
		set_left(curr,remove_tree_node(get_left(curr),key,data,balanced,preceed));
		if(tree_node_is_empty(get_left(curr)) == 1)
		{
			decrease_bfactor(curr);
		}
		else
		{
			if(oldbfactor != 0 && get_bfactor(get_left(curr)) == 0)
			{
				decrease_bfactor(curr);

			}
		}
	}

	//Si la cle est plus grande
	//else if(preceed(key,get_tree_node_key(curr)) == 1 && preceed(get_tree_node_key(curr),key) == 0)

	else if(preceed(key,get_tree_node_key(curr)) == 1 && preceed(get_tree_node_key(curr),key) == 0)
	{
		if(tree_node_is_empty(get_right(curr)));
		int oldbfactor = get_bfactor(get_right(curr));
		set_right(curr,remove_tree_node(get_right(curr),key,data,balanced,preceed));
		if(tree_node_is_empty(get_right(curr)) == 1)
		{
			increase_bfactor(curr);

		}
		else
		{
			if(oldbfactor != 0 && get_bfactor(get_right(curr)) == 0)
			{
				increase_bfactor(curr);
			}
		}
	}

	//Si c'est egal
	else
	{
		//Si pas d'enfant
		
		if(tree_node_is_empty(get_left(curr)) == 1 && tree_node_is_empty(get_right(curr)) == 1)
		{
			*data = get_tree_node_data(curr);
			free(curr);
			return NULL;
		}

		
		//Un seul enfant a gauche
		if ( tree_node_is_empty(get_right(curr)) == 1 && tree_node_is_empty(get_left(curr) == 0))
		{
			struct tree_node_t * temp = get_left(curr);
			*data = get_tree_node_data(curr);
			free(curr);
			return temp;
		}
		
		//Un seul enfant a droite
		else if(tree_node_is_empty(get_left(curr))==1 && tree_node_is_empty(get_right(curr) == 0))
		{
			struct tree_node_t * temp = get_right(curr);
			*data = get_tree_node_data(curr);
			free(curr);
			return temp;
		}

		//2 enfant$
		*data = get_tree_node_data(curr);

		struct tree_node_t * temp = tree_find_predecessor(curr,get_tree_node_key(curr),preceed);

		set_tree_node_key(curr,get_tree_node_key(temp));
		set_tree_node_data(curr,get_tree_node_data(temp));
		
	//	curr->data = temp->data;
		set_left(curr,remove_tree_node(get_left(curr),get_tree_node_key(temp),data,balanced,preceed));

	}


	if (balanced && curr) {
		// PARTIE 2 :
		// Gérer ici les rotations	

		if(get_bfactor(curr) == 2 && get_bfactor(get_left(curr)) == 1)
		{
			struct tree_node_t * y = get_left(curr);
			curr = rotate_right(curr);

		}
		else if(get_bfactor(curr) == 2 && get_bfactor(get_left(curr)) == 0)
		{
			curr = rotate_right(curr);
		}
		else if(get_bfactor(curr) == 2 && get_bfactor(get_left(curr)) == -1)
		{
			struct tree_node_t * z = rotate_left(get_left(curr));
			set_left(curr,z);
			curr = rotate_right(curr);
		}
		else if(get_bfactor(curr) == -2 && get_bfactor(get_right(curr)) == -1)
		{
			curr = rotate_left(curr);
		}
		else if(get_bfactor(curr) == -2 && get_bfactor(get_right(curr)) == 0)
		{
			curr = rotate_left(curr);

		}
		else if(get_bfactor(curr) == -2 && get_bfactor(get_right(curr)) == 1)
		{
			struct tree_node_t * z = rotate_right(get_right(curr));
			set_right(curr,z);
			curr = rotate_left(curr);
		}
	

		// A FAIRE
	}
	return curr;
}



/**
 * NB : Utiliser la fonction récursive remove_tree_node.
 */
void * tree_remove(struct tree_t * T, void * key) {
	void * dataDel;
	struct tree_node_t * N = remove_tree_node(get_root(T),key,&dataDel,T->balanced,T->preceed);
	set_root(T,N);
	decrease_tree_size(T);
	return dataDel;
}

