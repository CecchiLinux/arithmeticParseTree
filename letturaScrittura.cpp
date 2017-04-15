#include"letturaScrittura.h"

void StampaAlbero(struct nodo* a)
{
  if(a == NULL)
  {
    printf("");
    return;
  }
  printf("( ");
  StampaAlbero(a->left);
  printf(" ");
  switch(a->tipo)
  {
	case ISTRUZIONE:
		switch(a->val)
		{
			case DIV:
				printf("%s","Div");
			break;
			case TIMES:
				printf("%s","Times");
			break;
			case PLUS:
				printf("%s","Plus");
			break;
			case POW:
				printf("%s","Pow");
			break;
		}
	 	break;
	case INCOGNITA:
			printf("%s","x");
		break;
	case NUMERO:
			printf("%d",a->val);
		break;
	case FUNZIONE:
			switch(a->val)
			{
				case SEN:
					printf("%s","Sen");
				break;
				case COS:
					printf("%s","Cos");
				break;
				case LN:
					printf("%s","Ln");
			}
		break;
  }
  printf(" ");
  StampaAlbero(a->right);
  printf(" ) ");
}

//"legge" un albero facendo ritornare la stringa corrispondente in notazione (Plus(),Times(),...)
std::string Leggi_Albero(struct nodo* a)
{
	std::string str;
	std::stringstream out;
	if(a == NULL)
	{
	    return NULL;
	 }
	switch(a->tipo)
	{
		case ISTRUZIONE:
			switch(a->val)
			{
				case TIMES:
					str="Times("+Leggi_Albero(a->left)+","+Leggi_Albero(a->right)+")";
				break;
				case PLUS:
					str="Plus("+Leggi_Albero(a->left)+","+Leggi_Albero(a->right)+")";
				break;
				case POW:
					str="Pow("+Leggi_Albero(a->left)+","+Leggi_Albero(a->right)+")";
				break;
				case DIV:
					str="Div("+Leggi_Albero(a->left)+","+Leggi_Albero(a->right)+")";
				break;
			}
	 		break;
		case INCOGNITA:
				str="x";
			break;
		case NUMERO:
				out << a->val;
				str = out.str();
			break;
		case FUNZIONE:
				switch(a->val)
				{
					case SEN:
						str="Sen("+Leggi_Albero(a->left)+")";
					break;
					case COS:
						str="Cos("+Leggi_Albero(a->left)+")";
					break;
					case LN:
						str="Ln("+Leggi_Albero(a->left)+")";
					break;
				}
			break;
		}
	return str;

}
