Realizzazione di un software per il calcolo della derivata di una funzione ad una variabile.
Ricevuta una funzione in input (tramite file di testo), il programma restituisce in output (un secondo file di testo) la sua derivata.

Le funzioni in input non si trovano nella forma propria del linguaggio matematico, ma in una notazione prefissa priva di operandi sostituiti da quelli che definiremo “istruzioni”.
Es. input: 	Times ( 3, Plus ( x , 2 ) )		che corrisponde a:		3 ( x + 2 ) 

Esistono quattro categorie di elementi, cioè andando a scomporre in parti minime qualsiasi input valido, ognuna di queste parti rientrerà in una di queste categorie.
Cosa si intende con parti minime:
Es. divisioni in parti minime di Times ( 3, Plus ( x , 2 ) ):
Sono presenti cinque parti minime;
	-Times (che vedremo fare parte delle istruzioni);
	-3 (che vedremo fare parte dei numeri);
	-Plus;
	-x (che vedremo fare parte delle incognite);
	-2;

Elenco delle quattro categorie istituite
ISTRUZIONI:
	-Times;
	-Plus;
	-Pow;
	-Div;
-FUNZIONI:
	-Sen;
	-Cos;
	-Ln;
-NUMERI:
	Nello specifico Interi, i numeri con virgola dovranno essere immessi come frazione utilizzando l’istruzione  “Div”;
-INCOGNITA:
	Gestita una sola variabile, nello specifico definita dal carattere “x”.
