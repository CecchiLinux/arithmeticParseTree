#include "init.h"

struct nodo* make_tree(std::string input)
{
	int indice_occorrenza;
	struct nodo* vertex;
	vertex=(struct nodo*)malloc(sizeof(struct nodo));
	vertex->left= NULL;
	vertex->right= NULL;

	indice_occorrenza=input.find_first_of('(');
	if(indice_occorrenza == std::string::npos)
	{
		check(vertex, input);
		return vertex;
	}


	int tipo = check(vertex, input.substr(0, indice_occorrenza));
	
	//toglie l'istruzione e le sue parentesi. es. Plus(2,3) -> 2,3
	input=input.substr(indice_occorrenza + 1, input.length() - indice_occorrenza - 2);
	if(tipo == FUNZIONE)
	{
		vertex->left= make_tree(input);
		return vertex;
	}

	int primaParentesi,primaVirgola,i, numParentesi = 0;

	primaParentesi = input.find_first_of('(');
	primaVirgola = input.find_first_of(',');
	if(primaParentesi != std::string::npos)
	{
		if(primaVirgola > primaParentesi)
		{
			i=primaParentesi;
			i++;
			numParentesi++;
			//ricerca posizione parentesi finale (relativa all'istruzione in esame)
			while((input[i] != '\0' ) && (numParentesi))
			{
				if(input[i] == ')')
				{
					numParentesi--;
				}
				if(input[i] == '(')
				{
					numParentesi++;
				}
				i++;
			}
		}
		else
		{
			i = primaVirgola;
		}
		//chiamate ricorsive figli
		vertex->left= make_tree(input.substr(0, i));
		vertex->right= make_tree(input.substr(i + 1, input.length() - i + 1));
	}else{
		indice_occorrenza=input.find_first_of(',');
		//chiamate ricorsive figli
		vertex->left= make_tree(input.substr(0, indice_occorrenza));
		vertex->right= make_tree(input.substr(indice_occorrenza+1, input.length() - indice_occorrenza));
	}
	return vertex;
}

//determina il tipo della sottostringa in questione e lo scrive nel nodo corrente
int check(struct nodo* vertex, std::string s)
{
	if(s.compare(std::string("Plus")) == 0)
	{
			vertex->tipo= ISTRUZIONE;
			vertex->val= PLUS;
			return ISTRUZIONE;
	}else 
		if(s.compare(std::string("Times")) == 0)
		{
			vertex->tipo= ISTRUZIONE;
			vertex->val= TIMES;
			return ISTRUZIONE;

	}else 
		if(s.compare(std::string("Pow")) == 0)
		{
			vertex->tipo= ISTRUZIONE;
			vertex->val= POW;
			return ISTRUZIONE;

	}else 
		if(s.compare(std::string("Div")) == 0)
		{
			vertex->tipo= ISTRUZIONE;
			vertex->val= DIV;
			return ISTRUZIONE;

	}else 
		if(s.compare(std::string("Sen")) == 0)
		{
			vertex->tipo= FUNZIONE;
			vertex->val= SEN;
			return FUNZIONE;
	}else 
		if(s.compare(std::string("Cos")) == 0)
		{
			vertex->tipo= FUNZIONE;
			vertex->val= COS;
			return FUNZIONE;
	}else
		if(s.compare(std::string("Ln")) == 0)
		{
			vertex->tipo= FUNZIONE;
			vertex->val=LN;
			return FUNZIONE;
	}else
		if(s.compare(std::string("x")) == 0)
		{
			vertex->tipo= INCOGNITA;
			vertex->val=-1;
			return INCOGNITA;
	}else{
			//conversione stringa -> intero
			std::istringstream in;
			vertex->tipo= NUMERO;
			in.str(s);
			in >> vertex->val;

			return NUMERO;
		}
}