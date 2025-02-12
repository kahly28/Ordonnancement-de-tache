#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/util.h"
#include "../include/list.h"
#include "../include/tree.h"
#include "../include/instance.h"
#include "../include/schedule.h"
#include "../include/algo.h"

static int compare_lists(struct list_t *l1, int* l2[], int size) {
	if (get_list_size(l1) != size)
	{
		printf("1\n");
		return 0;

	}
	if (get_list_head(l1) == NULL)
	{
		return 1;
	}
	struct list_node_t * curr = get_list_head(l1);
	int i = 0;
	while (curr != NULL) {
		/*
		printf("ddd  = %d\n",l2[i]);
		printf("get list node data  = %d\n",get_list_node_data(curr));
		*/
		if (get_list_node_data(curr) != l2[i])
		{
			printf("2\n");
			return 0;
		}
		curr = get_successor(curr);
		i++;
	}

	printf("\n");
	curr = get_list_tail(l1);
	//printf("size = %d\n",size);
	i = size - 1;
	//printf("i = %d\n",i);
	while (curr != NULL) {

		if (get_list_node_data(curr) != l2[i])
		{
			printf("3\n");

			return 0;
		}
		curr = get_predecessor(curr);
		i--;
	}
	free(curr);
	return 1;
}

static int compare_lists_2(struct list_t *l1, int* l2[], int size) {
	if (get_list_size(l1) != size)
	{
		printf("1\n");
		return 0;

	}
	if (get_list_head(l1) == NULL)
	{
		return 1;
	}
	struct list_node_t * curr = get_list_tail(l1);
	int i = 0;
	while (curr != NULL) {
	
		if (get_list_node_data(curr) != l2[i])
		{
			printf("2\n");
			return 0;
		}
		curr = get_predecessor(curr);
		i++;
	}

	printf("\n");
	curr = get_list_head(l1);
	//printf("size = %d\n",size);
	i = size - 1;
	//printf("i = %d\n",i);
	while (curr != NULL) {

		if (get_list_node_data(curr) != l2[i])
		{
			printf("3\n");

			return 0;
		}
		curr = get_successor(curr);
		i--;
	}
	free(curr);
	return 1;
}

void test_list_insert_last() {
	int *i1 = malloc(sizeof(int));
	int *i2 = malloc(sizeof(int));
	int *i3 = malloc(sizeof(int));
	*i1 = 1;
	*i2 = 2;
	*i3 = 3;

	struct list_t * L = new_list(viewInt, freeInt);
	int* tab[3];
	tab[0] = i1; tab[1] = i2; tab[2] = i3;

	printf("1 ===================\n");
	list_insert_last(L, i1);
	if (compare_lists(L, tab, 1) == 0) printf("problème 1\n");
	printf("2 ===================\n");
	list_insert_last(L, i2);
	if (compare_lists(L, tab, 2) == 0) printf("problème 2\n");
	
	printf("3 ===================\n");
	list_insert_last(L, i3);
	if (compare_lists(L, tab, 3) == 0) printf("problème 3\n");
	// Il manque la libération de la mémoire. C'est à vous !
	free(i1);
	free(i2);
	free(i3);
	delete_list(L,0);
}

void test_list_insert_first()
{
	int *i1 = malloc(sizeof(int));
	int *i2 = malloc(sizeof(int));
	int *i3 = malloc(sizeof(int));
	*i1 = 1;
	*i2 = 2;
	*i3 = 3;

	struct list_t * L = new_list(viewInt, freeInt);
	int* tab[3];
	tab[0] = i1; tab[1] = i2; tab[2] = i3;

	printf("1 ===================\n");
	list_insert_first(L, i1);
	if (compare_lists_2(L, tab, 1) == 0) printf("problème 1\n");

	printf("2 ===================\n");
	list_insert_first(L, i2);
	if (compare_lists_2(L, tab, 2) == 0) printf("problème 2\n");
	
	printf("3 ===================\n");
	list_insert_first(L, i3);
	if (compare_lists_2(L, tab, 3) == 0) printf("problème 3\n");
	// Il manque la libération de la mémoire. C'est à vous !

	delete_list(L,1);
}

int check_list(struct list_t * M, void * tab[], int size, struct list_node_t * Node)
{
	if(get_list_size(M) != size)
	{
		printf("1\n");
		return 0;

	}
	if (get_list_head(M) == NULL)
	{
		return 1;
	}
	struct list_node_t * curr = get_list_head(M);

	int i = 0;
	while(curr != NULL)
	{
		if(get_list_node_data(curr) != tab[i])
		{
			printf("2\n");
			return 0;
		}
		curr = get_successor(curr);
		i = i+1;
	}

	i = size -1;
	curr = get_list_tail(M);
	while(curr != NULL)
	{
		if(get_list_node_data(curr) != tab[i])
		{
			printf("3\n");
			return 0;
		}
		curr = get_predecessor(curr);
		i = i-1;
	}
	return 1;
}

void test_insert_after()
{
	int a1 = 4;
	int b2 = 5;
	int c3 = 6;

	void * data1 = &a1;
	void * data2 = &b2;
	void * data3 = &c3;

	struct list_t * M = new_list(viewInt, freeInt);
	void * tab[3];
	tab[0] = data1;
	tab[1] = data2;
	tab[2] = data3;

	list_insert_first(M,data1);
	list_insert_last(M,data3);
	struct list_node_t * AfterThisNode = get_list_head(M);
	list_insert_after(M,data2,AfterThisNode);
	if(check_list(M,tab,3,AfterThisNode) == 0)
	{
		printf("Probleme\n");
	}
	else{
		printf("Test ok\n");
	}

	delete_list(M,1);

}


test_list_remove_last()
{
	int * i = malloc(sizeof(int));
	*i = 5;

	int *i2 = malloc(sizeof(int));
	*i2 = 10;

	int *i3 = malloc(sizeof(int));
	*i3 = 15;

	printf("%d\n", i);

	printf("ici ? \n");
	struct list_t * L = new_list(viewInt,freeInt);
	list_insert_first(L,i);
	printf("laaa ? \n");
	list_insert_first(L,i2);
	list_insert_first(L,i3);
	
	view_list(L);
	printf("after \n");
	list_remove_last(L);
	view_list(L);
	delete_list(L,1);

}

test_delete_tree_node()
{
	int * intA = malloc(sizeof(int));
	*intA = 20;
	int * aDataa = malloc(sizeof(int));
	*aDataa = 50;

	int * intB = malloc(sizeof(int));
	*intB = 18;
	int * bDataa = malloc(sizeof(int));
	*bDataa = 51;

	int * intC = malloc(sizeof(int));
	*intC = 23;
	int * cDataa = malloc(sizeof(int));
	*cDataa = 52;

	int * intD = malloc(sizeof(int));
	*intD = 16;
	int * dDataa = malloc(sizeof(int));
	*dDataa = 53;

	int * intE = malloc(sizeof(int));
	*intE = 19;
	int * eDataa = malloc(sizeof(int));
	*eDataa = 54;

	int * intF = malloc(sizeof(int));
	*intF = 21;
	int * fDataa = malloc(sizeof(int));
	*fDataa = 56;


	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T,intA,aDataa);
	tree_insert(T,intB,bDataa);
	tree_insert(T,intC,cDataa);
	tree_insert(T,intD,dDataa);
	//tree_insert(T,intE,eDataa);
	tree_insert(T,intF,fDataa);
	view_tree(T);

	/*
	int m = 6;
	void * dataa = &m;
	remove_tree_node(get_root(T),intE,&dataa,0,T->preceed);
	view_tree(T);
	viewInt(dataa);

	int n = 7;
	void * dataa2 = &n;
	remove_tree_node(get_root(T),intD,&dataa2,0,T->preceed);
	view_tree(T);
	viewInt(dataa2);
	*/

	
	int * KeyDel = malloc(sizeof(int));
	*KeyDel = 20;
	//int DelData = 60;
	void * DataDel;
	printf("???\n");
	//remove_tree_node(get_root(T),KeyDel,&DataDel,0,T->preceed);
	DataDel = tree_remove(T,KeyDel);
	printf("view list\n");
	view_tree(T);
	/*
	viewInt(DataDel);
	printf("INT\n");
	viewInt(get_tree_node_key(get_root(T)));
	*/


	printf("TEST delete TREE\n");
	delete_tree(T,1,1);
	

}

void test_tree_insert()
{
	int * data = malloc(sizeof(int));
	*data = 39;
	int * datakey = malloc(sizeof(int));
	*datakey = 5;

	int * data2 = malloc(sizeof(int));
	*data2 = 40;
	int * datakey2 = malloc(sizeof(int));
	*datakey2 = 3;

	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int * data3 = malloc(sizeof(int));
	*data3 = 41;
	int * datakey3 = malloc(sizeof(int));
	*datakey3 = 8;

	int * data4 = malloc(sizeof(int));
	*data4 = 42;
	int * datakey4 = malloc(sizeof(int));
	*datakey4 = 1;

	int * data5 = malloc(sizeof(int));
	*data5 = 43;
	int * datakey5 = malloc(sizeof(int));
	*datakey5 = 4;

	int * data6 = malloc(sizeof(int));
	*data6 = 44;
	int * datakey6 = malloc(sizeof(int));
	*datakey6 = 6;

	int * data7 = malloc(sizeof(int));
	*data7 = 43;
	int * datakey7 = malloc(sizeof(int));
	*datakey7 = 9;

	printf("Test insert liste vide\n");
	tree_insert(T,datakey,data);
	printf("-K\n");
	view_tree(T);

	printf("Test insert valeur plus petite 1\n");
	tree_insert(T,datakey2,data2);
	printf("Nb elment %d\n", T->numelm);
	//viewInt(get_tree_node_key(get_left(get_root(T))));
	view_tree(T);

	printf("Test insert valeur plus grande 1\n");
	tree_insert(T,datakey3,data3);
	printf("Nb elment %d\n", T->numelm);
	view_tree(T);

	tree_insert(T,datakey4,data4);
	tree_insert(T,datakey5,data5);
	tree_insert(T,datakey6,data6);
	tree_insert(T,datakey7,data7);
	view_tree(T);
	delete_tree(T,1,1);
}

void test_tree_min()
{
	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int * data = malloc(sizeof(int));
	*data = 39;
	int * datakey = malloc(sizeof(int));
	*datakey = 5;

	int * data2 = malloc(sizeof(int));
	*data2 = 40;
	int * datakey2 = malloc(sizeof(int));
	*datakey2 = 3;

	int * data3 = malloc(sizeof(int));
	*data3 = 41;
	int * datakey3 = malloc(sizeof(int));
	*datakey3 = 8;

	int * data4 = malloc(sizeof(int));
	*data4 = 42;
	int * datakey4 = malloc(sizeof(int));
	*datakey4 = 1;

	int * data5 = malloc(sizeof(int));
	*data5 = 43;
	int * datakey5 = malloc(sizeof(int));
	*datakey5 = 4;

	int * data6 = malloc(sizeof(int));
	*data6 = 44;
	int * datakey6 = malloc(sizeof(int));
	*datakey6 = 6;

	int * data7 = malloc(sizeof(int));
	*data7 = 43;
	int * datakey7 = malloc(sizeof(int));
	*datakey7 = 9;

	tree_insert(T,datakey,data);
	tree_insert(T,datakey2,data2);
	tree_insert(T,datakey3,data3);
	tree_insert(T,datakey4,data4);
	tree_insert(T,datakey5,data5);
	tree_insert(T,datakey6,data6);
	tree_insert(T,datakey7,data7);
	view_tree(T);

	struct tree_node_t * min = tree_min(get_root(T));
	printf("???\n");
	viewInt(get_tree_node_key(min));
	delete_tree(T,1,1);
}

test_tree_max()
{
	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int * data = malloc(sizeof(int));
	*data = 39;
	int * datakey = malloc(sizeof(int));
	*datakey = 5;


	int * data2 = malloc(sizeof(int));
	*data2 = 40;
	int * datakey2 = malloc(sizeof(int));
	*datakey2 = 3;

	int * data3 = malloc(sizeof(int));
	*data3 = 41;
	int * datakey3 = malloc(sizeof(int));
	*datakey3 = 8;

	int * data4 = malloc(sizeof(int));
	*data4 = 42;
	int * datakey4 = malloc(sizeof(int));
	*datakey4 = 1;

	int * data5 = malloc(sizeof(int));
	*data5 = 43;
	int * datakey5 = malloc(sizeof(int));
	*datakey5 = 4;

	int * data6 = malloc(sizeof(int));
	*data6 = 44;
	int * datakey6 = malloc(sizeof(int));
	*datakey6 = 6;

	int * data7 = malloc(sizeof(int));
	*data7 = 43;
	int * datakey7 = malloc(sizeof(int));
	*datakey7 = 9;

	tree_insert(T,datakey,data);
	tree_insert(T,datakey2,data2);
	tree_insert(T,datakey3,data3);
	tree_insert(T,datakey4,data4);
	tree_insert(T,datakey5,data5);
	tree_insert(T,datakey6,data6);
	tree_insert(T,datakey7,data7);
	view_tree(T);

	struct tree_node_t * max = tree_max(get_root(T));
	printf("???\n");
	viewInt(get_tree_node_key(max));
	delete_tree(T,1,1);
}

test_tree_find_node()
{
	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int * data = malloc(sizeof(int));
	*data = 39;
	int * datakey = malloc(sizeof(int));
	*datakey = 5;

	int * data2 = malloc(sizeof(int));
	*data2 = 40;
	int * datakey2 = malloc(sizeof(int));
	*datakey2 = 3;

	int * data3 = malloc(sizeof(int));
	*data3 = 41;
	int * datakey3 = malloc(sizeof(int));
	*datakey3 = 8;

	int * data4 = malloc(sizeof(int));
	*data4 = 42;
	int * datakey4 = malloc(sizeof(int));
	*datakey4 =  1;

	int * data5 = malloc(sizeof(int));
	*data5 = 43;
	int * datakey5 = malloc(sizeof(int));
	*datakey5 = 4;

	int * data6 = malloc(sizeof(int));
	*data6 = 44;
	int * datakey6 = malloc(sizeof(int));
	*datakey6 = 6;

	int * data7 = malloc(sizeof(int));
	*data7 = 43;
	int * datakey7 = malloc(sizeof(int));
	*datakey7 = 9;

	tree_insert(T,datakey,data);
	tree_insert(T,datakey2,data2);
	tree_insert(T,datakey3,data3);
	tree_insert(T,datakey4,data4);
	tree_insert(T,datakey5,data5);
	tree_insert(T,datakey6,data6);
	tree_insert(T,datakey7,data7);
	view_tree(T);

	int Find = 4;
	void * keyToFind = &Find;
	struct tree_node_t * NodeFind = tree_find_node(get_root(T),keyToFind,T->preceed);
	viewInt(get_tree_node_key(NodeFind));
	delete_tree(T,1,1);
}


test_tree_find_successor()
{
/*
	struct tree_t * T = new_tree(0,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int z = 39;
	void * data = &z;
	int key1 = 10;
	void * datakey = &key1;

	int z2 = 40;
	void * data2 = &z2;
	int key2 = 15;
	void * datakey2 = &key2;

	int z3 = 41;
	void * data3 = &z3;
	int key3 = 13;
	void * datakey3 = &key3;

	int z4 = 42;
	void * data4 = &z4;
	int key4 = 8;
	void * datakey4 = &key4;

	int z5 = 43;
	void * data5 = &z5;
	int key5 = 4;
	void * datakey5 = &key5;

	int z6 = 44;
	void * data6 = &z6;
	int key6 = 6;
	void * datakey6 = &key6;

	int z7 = 43;
	void * data7 = &z7;
	int key7 = 9;
	void * datakey7 = &key7;


	tree_insert(T,datakey,data);
	tree_insert(T,datakey2,data2);
	tree_insert(T,datakey3,data3);
	
	tree_insert(T,datakey4,data4);
	
	tree_insert(T,datakey5,data5);
	tree_insert(T,datakey6,data6);
	tree_insert(T,datakey7,data7);
	view_tree(T);
*/
	/*
	int * keytofind = malloc(sizeof(int));
	*keytofind = 10;
	*/
	//struct tree_node_t * KeyFind = tree_find_successor(get_root(T),keytofind,T->preceed);
	//printf("keeey find = ");
	//viewInt(get_tree_node_key(KeyFind));
	//delete_tree(T,1,1);

}




void test_insert_balanced()
{
	int *key1 = malloc(sizeof(int));
	*key1 = 10;
	int * data1 = malloc(sizeof(int));
	*data1 = 50;

	struct tree_t * T = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T,key1,data1);
	int *key2 = malloc(sizeof(int));
	*key2 = 7;
	int * data2 = malloc(sizeof(int));
	*data2 = 150;

	int * key3 = malloc(sizeof(int));
	*key3 = 15;
	int * data3 = malloc(sizeof(int));
	*data3 = 234;

	int * key4 = malloc(sizeof(int));
	*key4 = 5;
	int *data4 = malloc(sizeof(int));
	*data4 = 345;

	int * key5 = malloc(sizeof(int));
	*key5 = 3;
	int *data5 = malloc(sizeof(int));
	*data5 = 563;

	int * key6 = malloc(sizeof(int));
	*key6 = 8;
	int *data6 = malloc(sizeof(int));
	*data6 = 345;

	tree_insert(T,key3,data3);
	tree_insert(T,key2,data2);
	tree_insert(T,key4,data4);
	//tree_insert(T,key6,data6);
	//tree_insert(T,key3,data3);
	tree_insert(T,key5,data5);

	//printf("bfactor %d\n",get_bfactor(get_root(T)));
	printf("laaa\n");
	//viewInt(get_tree_node_key(get_left(get_root(T))));
	printf("\n\n");
	view_tree(T);
	printf("\n\n\n");
	int * keytodel = malloc(sizeof(int));
	*keytodel = 10;
	int * datatodel = malloc(sizeof(int));
	struct tree_node_t * curr = get_root(T);

	int * keytodel2 = malloc(sizeof(int));
	*keytodel2 = 5;
	int * datatodel2 = malloc(sizeof(int));

	int * keytodel3 = malloc(sizeof(int));
	*keytodel3 = 3;
	int * datatodel3 = malloc(sizeof(int));

	//remove_tree_node(curr,keytodel,datatodel,1,T->preceed);
	//remove_tree_node(curr,keytodel2,datatodel2,1,T->preceed);
	//remove_tree_node(curr,keytodel3,datatodel3,1,T->preceed);

	view_tree(T);
	viewInt(get_tree_node_key(get_root(T)));
	delete_tree(T,1,1);
}

test_remove_tree_node()
{
	struct tree_t * T = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);

	int *key1 = malloc(sizeof(int));
	*key1 = 15;
	int *data1 = malloc(sizeof(int));
	*data1 = 100;

	int *key2 = malloc(sizeof(int));
	*key2 = 8;
	int * data2 = malloc(sizeof(int));
	*data2 = 105;

	int *key3 = malloc(sizeof(int));
	*key3 = 18;
	int *data3 = malloc(sizeof(int));
	*data3 = 106;

	int *key4 = malloc(sizeof(int));
	*key4 = 16;
	int *data4 = malloc(sizeof(int));
	*data4 = 107;

	int *key5 = malloc(sizeof(int));
	*key5 = 10;
	int *data5 = malloc(sizeof(int));
	*data5 = 108;

	int *key6 = malloc(sizeof(int));
	*key6 = 7;
	int *data6 = malloc(sizeof(int));
	*data6 = 109;

	int *key7 = malloc(sizeof(int));
	*key7 = 5;
	int *data7 = malloc(sizeof(int));
	*data7 = 110;

	int *key8 = malloc(sizeof(int));
	*key8 = 13;
	int *data8 = malloc(sizeof(int));
	*data8 = 256;

	int *key9 = malloc(sizeof(int));
	*key9 = 20;
	int *data9 = malloc(sizeof(int));
	*data8 = 258;

	delete_tree(T,1,1);

//1er cas
/* 1er cas
	tree_insert(T,key1,data1);
	
	tree_insert(T,key2,data2);
	tree_insert(T,key3,data3);
	tree_insert(T,key4,data4);
	tree_insert(T,key5,data5);
	tree_insert(T,key6,data6);
	tree_insert(T,key7,data7);
	view_tree(T);

	int *keytodeel = malloc(sizeof(int));
	*keytodeel = 16;
	int * datatorecup = malloc(sizeof(int));
 
	datatorecup = tree_remove(T,keytodeel);
	view_tree(T);

	printf("data = ");
	viewInt(datatorecup);
*/

/* 2eme test
	struct tree_t * T2 = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T2,key1,data1);
	tree_insert(T2,key3,data3);
	tree_insert(T2,key6,data6);
	tree_insert(T2,key2,data2);
	tree_insert(T2,key7,data7);

	int * cleASupp = malloc(sizeof(int));
	*cleASupp = 18;
	//viewInt(cleASupp);
	view_tree(T2);

	int * dataToRecup = malloc(sizeof(int));
	dataToRecup = tree_remove(T2,cleASupp);
	view_tree(T2);
*/

//3eme cas
/*
	struct tree_t * T3 = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T3,key4,data4);
	tree_insert(T3,key3,data3);
	tree_insert(T3,key5,data5);
	tree_insert(T3,key9,data9);
	tree_insert(T3,key1,data1);
	tree_insert(T3,key2,data2);
	tree_insert(T3,key8,data8);
	view_tree(T);

	int * cleASupp = malloc(sizeof(int));
	*cleASupp = 20;
	int * dataToRecup = malloc(sizeof(int));
	dataToRecup = tree_remove(T3,cleASupp);
	view_tree(T3);
*/

//4eme cas
/*
	struct tree_t * T4 = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T4,key1,data1);
	tree_insert(T4,key4,data4);
	tree_insert(T4,key2,data2);
	tree_insert(T4,key3,data3);
	view_tree(T);

	int * cleASupp = malloc(sizeof(int));
	*cleASupp = 8;
	int * dataToRecup = malloc(sizeof(int));
	dataToRecup = tree_remove(T4,cleASupp);
	view_tree(T4);
*/

//5eme cas
/*
	struct tree_t * T5 = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T5,key5,data5);
	tree_insert(T5,key2,data2);
	tree_insert(T5,key4,data4);
	tree_insert(T5,key1,data1);
	tree_insert(T5,key3,data3);
	view_tree(T5);

	int * cleASupp = malloc(sizeof(int));
	*cleASupp = 8;
	int * dataToRecup = malloc(sizeof(int));
	dataToRecup = tree_remove(T5,cleASupp);
	view_tree(T5);
*/

	struct tree_t * T6 = new_tree(1,intGreaterThan,viewInt,viewInt,freeInt,freeInt);
	tree_insert(T6,key5,data5);
	tree_insert(T6,key2,data2);
	tree_insert(T6,key4,data4);
	tree_insert(T6,key1,data1);
	view_tree(T6);

	int * cleASupp = malloc(sizeof(int));
	*cleASupp = 8;
	int * dataToRecup = malloc(sizeof(int));
	dataToRecup = tree_remove(T6,cleASupp);
	view_tree(T6);
	delete_tree(T6,1,1);
}

void test_task()
{
	char * id = "Ye";
	struct task_t * T = new_task(id,3,6);
	printf("%s\n",T->id);
	view_task(T);
	delete_task(T);
	view_task(T);
	delete_task(T);
}

void test_instance()
{
	Instance * I = read_instance("fichier.txt");
	view_instance(I);
	delete_instance(I,1);
}


void test_schedule()
{
	struct schedule_t * S = new_schedule(3);
	Instance * I = read_instance("fichier.txt");
	delete_instance(I,1);

}

void test_schedule2()
{
	/*
	struct task_t * T = new_task("Yooo",1,2);
	struct task_t * T2 = new_task("Yee",2,4);
	struct schedule_t * S = new_schedule(3);
	view_task(T);
	printf("%d\n",get_num_machines(S));
	add_task_to_schedule(S,T,1,1,2);
	add_task_to_schedule(S,T2,1,2,4);
	printf("bzz\n\n");
	view_schedule(S);
	delete_task(T);
	delete_task(T2);
	delete_schedule(S);
	*/
}

void test_create_schedule()
{
	printf("Non preemptif\n");
	Instance * I = read_instance("fichier.txt");
	view_instance(I);
	printf("Non balance ?\n");
	struct schedule_t * schedule = new_schedule(2);
	schedule = create_schedule(I,4,0,0);
	view_schedule(schedule);
	save_schedule(schedule,"fichier1.txt");
	delete_schedule(schedule);

	printf("Balance \n");
	schedule = create_schedule(I,4,0,1),
	view_schedule(schedule);
	save_schedule(schedule,"fichier2.txt");
	delete_schedule(schedule);


	printf("preemptif\n");
	printf("Non balance ?\n");
	schedule = create_schedule(I,4,1,0);
	view_schedule(schedule);
	save_schedule(schedule,"fichier3.txt");
	delete_schedule(schedule);

	printf("Balance \n");
	schedule = create_schedule(I,4,1,1),
	printf("\n");
	view_schedule(schedule);
	save_schedule(schedule,"fichier4.txt");
	delete_schedule(schedule);

/*
	struct list_t * L = get_schedule_of_machine(schedule,1);
	struct list_node_t * LN = get_list_tail(L);
	struct schedule_node_t * SN = get_list_node_data(LN);
	printf("EEEe = %lu\n",get_schedule_node_end_time(SN));
*/



	//printf("Preemptif\n");
	//Instance * I2 = read_instance("fichier.txt");



	//delete_instance(I,1);
	//delete_schedule(schedule);
}



int main() {

	printf("====== LIST ====== \n");
	printf("Test insert last\n");
	//test_list_insert_last();
	printf("-----------------------\n\n");

	printf("Test insert first\n");
	//test_list_insert_first();
	printf("-----------------------\n\n");

	printf("Test insert_after\n");
	//test_insert_after();
	printf("\n\n");
	printf("---------------------\n\n");

	printf("Test remove last\n");
	//test_list_remove_last();
	printf("\n\n");

	printf("====== TREE ======\n");
	printf("Test delete\n");
	//test_delete_tree_node();


	printf("Test tree_insert\n");
	//test_tree_insert();
	printf("-----------------------\n\n");

	printf("Test tree_min \n");
	//test_tree_min();
	printf("-----------------------\n\n");

	printf("Test tree_max\n");
	//test_tree_max();
	printf("-----------------------\n\n");

	printf("Test tree_find_node\n");
	//test_tree_find_node();
	printf("-----------------------\n\n");

	printf("Test successor\n");
	test_tree_find_successor();
	printf("-----------------------\n\n");

	printf("Test arbre balance\n");
	printf("Test insert node\n");
//	test_insert_balanced();

	printf("Test remove tree_node\n");
//	test_remove_tree_node();

	printf("-----------------------\n\n");
	printf("Test task\n");
//	test_task();

	printf("------------------------\n\n");
	printf("Test instance\n");
	test_instance();

	printf("========================\n\n");
	printf("Test schedule\n");
	test_schedule();
	printf("\n");

	printf("Test schedule2\n");
	test_schedule2();

	printf("--------------------\n");
	printf("Test create_schedule\n");
	test_create_schedule();


	return EXIT_SUCCESS;
}