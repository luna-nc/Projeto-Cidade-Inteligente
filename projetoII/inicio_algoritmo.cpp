#include <iostream>
#include <stdlib.h>
#define tam 10
using namespace std;
// Variável de identificação de erro de parenteses
int error=0;
// Inicializar, vazio, inser??o, remo??o e impress?o
struct Elemento{
	char expressao;
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
	cout<<"\n\tImpress?o\n";
	for(Aux=E;Aux!=NULL;Aux = Aux->prox){
		cout<<Aux->expressao;
		if(Aux->prox!=NULL){
			cout<<",";
		}
	}
}

Elemento* criar_elemento(char c){
	Elemento *ret;
	ret = (Elemento *) malloc(sizeof(Elemento));
	if(ret != NULL){
		ret->expressao = c;
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
			// Atualiza inicio e fim
			F->inicio = ptE;
		} else {
			F->fim->prox = ptE;
		}
		F->fim = ptE;
		if(F->fim->expressao == '(' || F->fim->expressao == ')'){
			++F->total;
		}
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
void empilhar(Pilha *P, char c){
	Elemento *ptE;
	ptE = criar_elemento(c);
	if(ptE != NULL){
		if(!vazia_pilha(P)){
			// Atualiza o fim
			ptE->prox = P->topo;
		}
		P->topo = ptE;
		++P->total;
	}
}
// Pop
void desempilhar(Pilha *P){
	if(!vazia_pilha(P)){
		P->topo = P->topo->prox;
		--P->total;
	} else {
		++error;
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	char exp;
	Fila f;
	Pilha p;
	
	ini_fila(&f);
	ini_pilha(&p);
	
	cout<<"Digite a expressão: ";
	while(cin.get(exp) && exp != '\n'){
		enfileirar(&f, exp);
	}
	
	/*
	enfileirar(&f, '5');
	enfileirar(&f, '/');
	enfileirar(&f, '(');
	enfileirar(&f, '5');
	enfileirar(&f, '*');
	enfileirar(&f, '5');
	enfileirar(&f, ')');
	*/
	
	while(!vazia_fila(&f)){
		if(f.inicio->expressao == '('){
			empilhar(&p, 1);
		}
		if(f.inicio->expressao == ')'){
			desempilhar(&p);
		}
		f.inicio = f.inicio->prox;
	}
	if(p.total!=0 || error!=0){
		cout<<"\nExpressão inválida!";
	} else {
		cout<<"\n\n- Total de parênteses: "<<f.total;
	}
	return 0;
}
