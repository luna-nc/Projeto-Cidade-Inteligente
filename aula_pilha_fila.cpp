/*
	1° identificar a expressão (ler);
	2° estrutura (pilha) onde armazena-se, a expressão em um vetor de caracteres, e uma variável do tipo DOUBLE para o resultado anterior;
	3° separar em pequenos pedaços tendo como referência os parênteses
	4° entender as prioridades matemáticas (parênteses, colchetes, chaves, multiplicação e divisão, potenciação e radiciação...);
	5° realizar as operações, já sabendo as prioridades;
	6° retornar o resutado (estar certo).
*/

#include <iostream>
#include <string.h>
using namespace std;
//Inicializar, vazio, inserção, remoção e impressão
struct Elemento{
	char item;
	Elemento *prox;
};
//	FIFO -> First In, First Out
struct Fila{ 
	Elemento *inicio, *fim;
	int total;
};
// LIFO -> Last In, First Out
struct Pilha{ 
	Elemento *topo;
	int total;
};

void ini_fila(Fila *F){
	F->inicio = NULL;
	F->fim = NULL;
	F->total = 0;
}

void ini_pilha(Pilha *P){
	P->topo = NULL;
	P->total = 0;
}

bool vazia_fila(Fila *F){
	return (F->inicio == NULL);
}

bool vazia_pilha(Pilha *P){
	return (P->topo == NULL);
}

void imprimir(Elemento *E){
	Elemento *Aux;
	cout<<"\n\tImpressão\n";
	for(Aux=E;Aux!=NULL;Aux = Aux->prox){
		cout<<Aux->item;
		if(Aux->prox!=NULL){
			cout<<",";
		}
	}
}

Elemento * criar_elemento(char c){
	Elemento *ret;
	ret = (Elemento *) malloc(sizeof(Elemento));
	if(ret != NULL){
		ret->item = c;
		ret->prox = NULL;
	}
	return ret;
}
// Enqueue (En-queue = en-fila) d/dx f = ln(CU^e+[CU-LE]+{LE*(Mal/loc)})
void enfileirar(Fila *F, char c){
	Elemento *ptE;
	ptE = criar_elemento(c);
	if(ptE != NULL){
		if(vazia_fila(F)){
			// Atualiza início e fim
			F->inicio = ptE;
		} else {
			F->fim->prox = ptE;
		}
		F->fim = ptE;
		++F->total;
	}
}
// Dequeue (De-queue = des-fila)
Elemento * desenfileirar(Fila *F){
	Elemento * ret = NULL;
	if(!vazia_fila(F)){
		ret = F->inicio;
		if(F->inicio == F->fim){
			// 1 elemento
			F->inicio = NULL;
			F->fim = F->inicio;
		} else {
			// mais de 1 elemento
			F->inicio = F->inicio->prox;	
		}
		--F->total;
	} 
	return ret;
}

// Push (stack = pilha)
void enpilhar(Pilha *P, char c){
	Elemento *ptE;
	ptE = criar_elemento(c);
	if(ptE != NULL){
		if(!vazia_pilha(P)){
//			Atualiza o fim
			ptE->prox = P->topo;
		}
		P->topo = ptE;
		++P->total;
	}
}
// Pop
Elemento * desenpilhar(Pilha *P){
	Elemento * ret = NULL;
	if(!vazia_pilha(P)){
		ret = P->topo;
		P->topo = P->topo->prox;
		--P->total;
	} 
	return ret;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	Elemento *e; 
//	a,b,c;
	Fila f;
	Pilha p;
	
	/*a.item = '1';
	a.prox = &b;
	b.item = '8';
	b.prox = &c;
	c.item = '-';
	c.prox = NULL;*/
	/*
	ini_fila(&f);
	enfileirar(&f, '1');
	enfileirar(&f, '8');
	enfileirar(&f, '-');
	imprimir(f.inicio);
	cout<<"\nTotal: "<<f.total<<endl<<endl;
	system("pause");
	
	e = desenfileirar(&f);
	imprimir(f.inicio);
	cout<<"\nTotal: "<<f.total<<" e retirou "<<e->item<<endl<<endl;
	system("pause");
	
	e = desenfileirar(&f);
	imprimir(f.inicio);
	cout<<"\nTotal: "<<f.total<<" e retirou "<<e->item<<endl<<endl;
	system("pause");
	*/
	
	ini_pilha(&p);
	enpilhar(&p, '1');
	enpilhar(&p, '8');
	enpilhar(&p, '-');
	imprimir(p.topo);
	cout<<"\nTotal: "<<p.total<<endl<<endl;
	system("pause");
	
	e = desenpilhar(&p);
	imprimir(p.topo);
	cout<<"\nTotal: "<<p.total<<" e retirou "<<e->item<<endl<<endl;
	system("pause");
	
	e = desenpilhar(&p);
	imprimir(p.topo);
	cout<<"\nTotal: "<<p.total<<" e retirou "<<e->item<<endl<<endl;
	system("pause");
	
	return 0;
}
