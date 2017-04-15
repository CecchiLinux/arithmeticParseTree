#include "init.h"
#include "letturaScrittura.h"
#include<stdio.h>
#include<stdlib.h>
using namespace std;


void liberaMemoria(struct nodo* a);
string Derivata(struct nodo* albero);
void SistemaDerivata(struct nodo** albero);

int main(){
	string input,risultato;
	struct nodo* albero;
	albero= NULL;
	ifstream File("funzione_input.txt");
	if(!File)
	{
		printf("errore apertura file\n");
		return -1;
	}
	getline(File,input);
	File.close();
	
	albero=make_tree(input);	// crazione albero con input
	risultato=Derivata(albero);
	liberaMemoria(albero);
	albero= NULL; //resetto variabile locale	
	
	albero = make_tree(risultato);    //  creazione albero con il risultato per semplificarlo
	//StampaAlbero(albero);
	SistemaDerivata(&albero);
	//StampaAlbero(albero);
	//printf("\n");
	risultato=Leggi_Albero(albero);
	//std::cout << ris << "\n";
	liberaMemoria(albero);
	albero= NULL;
	
	ofstream f("Derivata.txt");
	f<<risultato<<endl;

	return 0;
}

string Derivata(struct nodo* albero)
{
	string ris;
	if(albero == NULL)
	{
		return NULL;
	}
	switch(albero->tipo)	//selezione del contenuto del nodo corrente
	{
		case INCOGNITA:
			ris="1";	//derivata di un' incognita
			break;
		case FUNZIONE:
			switch(albero->val)		//selezione tipologia funzione (seno,coseno,logaritmo)
			{
			case SEN:
				ris="Times(Cos("+Leggi_Albero(albero->left)+"),"+Derivata(albero->left)+")";	//derivata(sen(a)) = derivata(a)*cos(a)
				break;
			case COS:
				ris="Times(Times(Sen("+Leggi_Albero(albero->left)+"),-1),"+Derivata(albero->left)+")";    //derivata(cos(a)) = derivata(a)*(-1*sen(a))
				break;
			case LN:
				ris="Div("+Derivata(albero->left)+","+Leggi_Albero(albero->left)+")";		//derivata(ln(a)) = derivata(a)/a
				break;
			}
			break;
		case ISTRUZIONE:
			switch(albero->val)
			{
			case TIMES:
				//derivata a*b = derivata(a) * b + a * derivata(b)
				ris="Plus(Times("+Derivata(albero->left)+","+Leggi_Albero(albero->right)+"),Times("+Leggi_Albero(albero->left)+","+Derivata(albero->right)+"))";
				break;
			case PLUS:
				//derivata a+b = derivata(a) + derivata(b)
				ris="Plus("+Derivata(albero->left)+","+Derivata(albero->right)+")";
				break;
			case POW:
				if(albero->right->tipo == NUMERO) // a^b con a=f(x) o numero e b numero
				{
					//derivata(a^b) =  b * a^(b-1) * derivata(a)
					ris="Times(Times("+Leggi_Albero(albero->right)+",Pow("+Leggi_Albero(albero->left)+",Plus("+Leggi_Albero(albero->right)+",-1))),"+Derivata(albero->left)+")"; //f(x)^a
				}
				else if(albero->left->tipo == NUMERO)  //a^b con a numero (esponenziale)
				{
					//derivata(a^b) = a^b * (derivata(b) * ln(a))
					ris="Times(Pow("+Leggi_Albero(albero->left)+","+Leggi_Albero(albero->right)+"),Times("+Derivata(albero->right)+",Ln("+Leggi_Albero(albero->left)+")))"; //a^f(x)
				}
				else		//derivata(f(x)^g(x)) = f(x)^g(x) * ((derivata(g(x)) * ln(f(x)) + (g(x) / f(x)) * derivata(f(x))
				{
					ris="Times(Pow("+Leggi_Albero(albero->left)+","+Leggi_Albero(albero->right)+"),Plus(Times("+Derivata(albero->right)+",Ln("+Leggi_Albero(albero->left)+")),Times(Div("+Leggi_Albero(albero->right)+","+Leggi_Albero(albero->left)+"),"+Derivata(albero->left)+")))"; 
				}
				break;
			case DIV:
				//derivata(a/b) = (derivata(a) * b) + (-1 * (a + derivata(b))) / (b ^ 2) 
				ris="Div(Plus(Times("+Derivata(albero->left)+","+Leggi_Albero(albero->right)+"),Times(-1,Plus("+Leggi_Albero(albero->left)+","+Derivata(albero->right)+"))),Pow("+Leggi_Albero(albero->right)+",2))";
				break;
			}
			break;
		case NUMERO:
			ris="0";   //derivata di un numero
			break;
	}
	return ris;
}

//funzione ricorsiva che semplifica il risultato eliminando scritture inutili
//come moltiplicazioni per 1 o 0, somme di due numeri, ...
void SistemaDerivata(struct nodo** albero)
{
	int val;

	if(*albero == NULL)
	{
		return;
	}
	SistemaDerivata(&(*albero)->left);
	SistemaDerivata(&(*albero)->right);
	if((*albero)->tipo ==  ISTRUZIONE)
	{
		switch((*albero)->val)
		{
		case TIMES:				
			if((*albero)->left->tipo == NUMERO && (*albero)->right->tipo == NUMERO) //numero*numero
			{					
				val = (*albero)->left->val * (*albero)->right->val; //a*b = c
				(*albero)->tipo = NUMERO;
				(*albero)->val = val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				liberaMemoria((*albero)->right);
				(*albero)->left = NULL;
				(*albero)->right = NULL;
			}
			else if((*albero)->left->tipo == NUMERO) 
			{ 
				if((*albero)->left->val == 0) //0*f(x)
				{
					(*albero)->tipo = NUMERO;
					(*albero)->val = 0;			
					//rimozione nodi superflui
					liberaMemoria((*albero)->left);
					liberaMemoria((*albero)->right);
					(*albero)->left = NULL;
					(*albero)->right = NULL;
				}
				else if((*albero)->left->val == 1) //1*f(x) 
				{
					(*albero)->tipo = (*albero)->right->tipo;
					(*albero)->val = (*albero)->right->val;
					liberaMemoria((*albero)->left);				//libera memoria
					(*albero)->left=(*albero)->right->left;       
					(*albero)->right=(*albero)->right->right;   
				}
			}
			else if((*albero)->right->tipo == NUMERO) //f(x)*0
			{ 
				if((*albero)->right->val == 0)
				{
					(*albero)->tipo = NUMERO;
					(*albero)->val = 0;
					//rimozione nodi superflui
					liberaMemoria((*albero)->left);
					liberaMemoria((*albero)->right);
					(*albero)->left = NULL;
					(*albero)->right = NULL;
				}
				else if((*albero)->right->val == 1) //f(x)*1  
				{
					(*albero)->tipo = (*albero)->left->tipo;
					(*albero)->val = (*albero)->left->val;
					liberaMemoria((*albero)->right);				//libera memoria
					(*albero)->right = (*albero)->left->right;
					(*albero)->left = (*albero)->left->left;
				}
			}
			break;
		case PLUS:
			if((*albero)->left->tipo == NUMERO && (*albero)->right->tipo == NUMERO) // a+b
			{					
				val = (*albero)->left->val + (*albero)->right->val; // a+b = c
				(*albero)->tipo = NUMERO;
				(*albero)->val = val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				liberaMemoria((*albero)->right);
				(*albero)->left = NULL;
				(*albero)->right = NULL;
			}
			else if(((*albero)->left->val == 0) && ((*albero)->left->tipo == NUMERO)) // 0+f(x) = f(x)
			{
				//*albero = (*albero)->right; 
				(*albero)->tipo = (*albero)->right->tipo;
				(*albero)->val = (*albero)->right->val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				(*albero)->left = NULL;
				(*albero)->left=(*albero)->right->left;
				(*albero)->right=(*albero)->right->right;
				

			}
			else if(((*albero)->right->val == 0)&&((*albero)->right->tipo==NUMERO)) // f(x)+0 = f(x)
			{
				//*albero = (*albero)->left; 
				(*albero)->tipo = (*albero)->left->tipo;
				(*albero)->val = (*albero)->left->val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->right);
				(*albero)->right = NULL;
				(*albero)->right=(*albero)->left->right;
				(*albero)->left=(*albero)->left->left;
				
				
			}
			break;
		case POW:
			int val,i;
			if((*albero)->left->tipo == NUMERO)
			{
				if((*albero)->right->tipo == NUMERO) //a^b   con a e b numeri
				{	
					if((*albero)->right->val == 0) // a^0 = 1
					{
						(*albero)->tipo = NUMERO;
						(*albero)->val = 1;
						//rimozione nodi superflui
						liberaMemoria((*albero)->left);
						liberaMemoria((*albero)->right);
						(*albero)->left = NULL;
						(*albero)->right = NULL;
					}
					else if((*albero)->right->val == 1) // a^1 = a
					{
						(*albero)->tipo = (*albero)->left->tipo;;
						(*albero)->val = (*albero)->left->val;
						//rimozione nodi superflui
						liberaMemoria((*albero)->right);
						(*albero)->right = NULL;
					}
					else{                              //a^b = c
						val = (*albero)->left->val;
						for(i = 1 ; i < (*albero)->right->val; i++){
							val *= (*albero)->left->val;
						}
						(*albero)->tipo = NUMERO;
						(*albero)->val = val;
						//rimozione nodi superflui
						liberaMemoria((*albero)->left);
						liberaMemoria((*albero)->right);
						(*albero)->left = NULL;
						(*albero)->right = NULL;
					}
				}
			}
			break;
		case DIV:
			string cmp;
			cmp=Leggi_Albero((*albero)->left);
			if(cmp.compare(Leggi_Albero((*albero)->right)) == 0) //  a/a     f(x)/f(x)
			{
				(*albero)->tipo=NUMERO;
				(*albero)->val=1;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				liberaMemoria((*albero)->right);
				(*albero)->left=NULL;
				(*albero)->right=NULL;
			}
			//lasciamo versione frazionaria
			/*else if((*albero)->left->tipo == NUMERO && (*albero)->right->tipo == NUMERO) // a/b
			{					
				val = (*albero)->left->val / (*albero)->right->val; // a/b = c
				(*albero)->tipo = NUMERO;
				(*albero)->val = val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				liberaMemoria((*albero)->right);
				(*albero)->left = NULL;
				(*albero)->right = NULL;
			}*/
			else if((*albero)->right->tipo == NUMERO && (*albero)->right->val == 1) // f(x)/1
			{
				(*albero)->tipo=(*albero)->left->tipo;
				(*albero)->val=(*albero)->left->val;
				//rimozione nodi superflui
				liberaMemoria((*albero)->left);
				liberaMemoria((*albero)->right);
				(*albero)->left = NULL;
				(*albero)->right = NULL;
			}
			break;
		}
	}
	return;
}


void liberaMemoria(struct nodo* a){
	if(a == NULL)
		return;
	if(a->left != NULL)
	{
		liberaMemoria(a->left);
	}
	if(a->right != NULL)
	{
		liberaMemoria(a->right);
	}
	free(a);
	return;
	
	
}

