#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include <stdlib.h>

#ifndef INIT_H
#define INIT_H

#define TIMES 0
#define PLUS 1
#define DIV 2
#define POW 3

#define ISTRUZIONE 0
#define NUMERO 1
#define FUNZIONE 2
#define INCOGNITA 3

#define SEN 0
#define COS 1
#define LN 2

struct nodo* make_tree(std::string input);
int check(struct nodo* vertex,std::string s);

struct nodo{
	int val;  //0 = times, 1 = plus, 2 = div, 3 = pow,
	short int tipo;  //0 istruzione, 1 numero,variabile;2 funzione
	struct nodo* left;
	struct nodo* right;
};
#endif
