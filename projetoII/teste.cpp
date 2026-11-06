#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;

// Estruturas de Dados
struct Elemento {
    char Operador[10]; 
    float Numero;
    Elemento *Prox;
};

struct Fila {
    Elemento *Inicio;
    Elemento *Fim;
    int Total;
};

struct Pilha {
    Elemento *Topo;
    int Total;
};

// Funções Auxiliares de Fila e Pilha
void Ini_Fila(Fila *F) {
    F->Inicio = NULL;
    F->Fim = NULL;
    F->Total = 0;
}

void Ini_Pilha(Pilha *P) {
    P->Topo = NULL;
    P->Total = 0;
}

bool Fila_Vazia(Fila *F) {
    return (F->Inicio == NULL);
}

bool Pilha_Vazia(Pilha *P) {
    return (P->Topo == NULL);
}

Elemento* Criar_Elemento(const char* Op, float Num) {
    Elemento *Ret = (Elemento*) malloc(sizeof(Elemento));    
    if (Ret != NULL) {
        strcpy(Ret->Operador, Op);
        Ret->Numero = Num;
        Ret->Prox = NULL;
    }
    return Ret;
}

void Enfileirar(Fila *F, const char* Op, float Num) {
    Elemento *ptE = Criar_Elemento(Op, Num);
    if (ptE != NULL) {
        if (Fila_Vazia(F)) {
            F->Inicio = ptE;            
        } else {
            F->Fim->Prox = ptE;                
        }
        F->Fim = ptE;
        ++F->Total;
    }   
}

Elemento* Desenfileirar(Fila *F) {
    Elemento *Ret = NULL;
    if (!Fila_Vazia(F)) {
        Ret = F->Inicio;
        if (F->Inicio == F->Fim) {
            F->Inicio = NULL;
            F->Fim = NULL;
        } else {
            F->Inicio = F->Inicio->Prox;
        }
        --F->Total;          
    }
    return Ret;
}

void Empilhar(Pilha *P, const char* Op, float Num) {
    Elemento *ptE = Criar_Elemento(Op, Num);
    if (ptE != NULL) {
        if (!Pilha_Vazia(P)) {        
            ptE->Prox = P->Topo;    
        }
        P->Topo = ptE;        
        ++P->Total;
    }   
}

Elemento* Desempilhar(Pilha *P) {
    Elemento *Ret = NULL;
    if (!Pilha_Vazia(P)) {
        Ret = P->Topo;
        P->Topo = P->Topo->Prox;        
        --P->Total;          
    }
    return Ret;
}

void Imprimir(Elemento *E) {
    cout << "IMPRESSAO: ";    
    for (Elemento *Aux = E; Aux != NULL; Aux = Aux->Prox) {
        if (strcmp(Aux->Operador, "#") == 0) {
            cout << Aux->Numero;    
        } else {
            cout << Aux->Operador;    
        }
        if (Aux->Prox != NULL) cout << " ";
    }
    cout << endl;
}

// Processador de texto da expressão
void Processar_Expressao_Texto(Fila *F, const string &expressao) {
    int i = 0;
    int tamanho = expressao.length();

    while (i < tamanho) {
        char c = expressao[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c) || c == '.') {
            string numStr = "";
            while (i < tamanho && (isdigit(expressao[i]) || expressao[i] == '.')) {
                numStr += expressao[i];
                i++;
            }
            float valor = atof(numStr.c_str());
            Enfileirar(F, "#", valor);
        } else {
            char opStr[2] = {c, '\0'};
            Enfileirar(F, opStr, 0);
            i++;
        }
    }
}

// FUNCIONALIDADE 1: Precedência
int Precedencia(const char* op) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if (strcmp(op, "(") == 0) return 0;
    return 0;
}

// FUNCIONALIDADE 2: Cálculo simples
float Calc_Simples(float num1, float num2, const char* op) {
    if (strcmp(op, "+") == 0) return num1 + num2;
    if (strcmp(op, "-") == 0) return num1 - num2;
    if (strcmp(op, "*") == 0) return num1 * num2;
    if (strcmp(op, "/") == 0) {
        if (num2 != 0) return num1 / num2;
        cout << "Erro: Divisao por zero!" << endl;
        return 0;
    }
    return 0;
}

// FUNCIONALIDADE 3: Resolução de pilhas
void Resolver_Pilha(Pilha *PNum, Pilha *POp) {
    if (Pilha_Vazia(POp) || PNum->Total < 2) return;

    Elemento *eOp = Desempilhar(POp);
    Elemento *eNum2 = Desempilhar(PNum);
    Elemento *eNum1 = Desempilhar(PNum);

    float res = Calc_Simples(eNum1->Numero, eNum2->Numero, eOp->Operador);

    Empilhar(PNum, "#", res);

    free(eOp);
    free(eNum1);
    free(eNum2);
}

// OPÇÃO 1 DO MENU: Verificação do balanceamento de parênteses
bool Verificar_Parenteses(Fila F) {
    Pilha pParen;
    Ini_Pilha(&pParen);
    
    Elemento *Aux = F.Inicio;
    bool correto = true;

    while (Aux != NULL) {
        if (strcmp(Aux->Operador, "(") == 0) {
            Empilhar(&pParen, "(", 0);
        } else if (strcmp(Aux->Operador, ")") == 0) {
            if (Pilha_Vazia(&pParen)) {
                correto = false;
                break;
            } else {
                Elemento *des = Desempilhar(&pParen);
                free(des);
            }
        }
        Aux = Aux->Prox;
    }

    if (!Pilha_Vazia(&pParen)) {
        correto = false;
        // Limpa a pilha restante
        while (!Pilha_Vazia(&pParen)) {
            Elemento *des = Desempilhar(&pParen);
            free(des);
        }
    }

    return correto;
}

// FUNCIONALIDADE 4 (OPÇÃO 2 DO MENU): Cálculo da expressão
float Calc_Expressao(Fila F) {
    Pilha PNum, POp;
    Ini_Pilha(&PNum);
    Ini_Pilha(&POp);

    Elemento *Elem = NULL;

    while (!Fila_Vazia(&F) || !Pilha_Vazia(&POp)) {
        if (!Fila_Vazia(&F)) {
            Elem = Desenfileirar(&F);

            if (strcmp(Elem->Operador, "#") == 0) {
                Empilhar(&PNum, Elem->Operador, Elem->Numero);
                free(Elem);
            } 
            else if (strcmp(Elem->Operador, "(") == 0) {
                Empilhar(&POp, Elem->Operador, Elem->Numero);
                free(Elem);
            }
            else if (strcmp(Elem->Operador, ")") == 0) {
                while (!Pilha_Vazia(&POp) && strcmp(POp.Topo->Operador, "(") != 0) {
                    Resolver_Pilha(&PNum, &POp);
                }
                if (!Pilha_Vazia(&POp) && strcmp(POp.Topo->Operador, "(") == 0) {
                    Elemento *abreParen = Desempilhar(&POp);
                    free(abreParen);
                }
                free(Elem);
            }
            else {
                bool empilhou = false;
                while (!empilhou) {
                    if (Pilha_Vazia(&POp)) {
                        Empilhar(&POp, Elem->Operador, Elem->Numero);
                        empilhou = true;
                    } 
                    else {
                        int precAtual = Precedencia(Elem->Operador);
                        int precTopo  = Precedencia(POp.Topo->Operador);

                        if (precAtual > precTopo) {
                            Empilhar(&POp, Elem->Operador, Elem->Numero);
                            empilhou = true;
                        } 
                        else {
                            Resolver_Pilha(&PNum, &POp);
                        }
                    }
                }
                free(Elem);
            }
        } 
        else {
            Resolver_Pilha(&PNum, &POp);
        }
    }

    float resultado = 0.0;
    if (!Pilha_Vazia(&PNum)) {
        Elemento *resElem = Desempilhar(&PNum);
        resultado = resElem->Numero;
        free(resElem);
    }

    return resultado;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
	int opcao = 0;
    Fila f;
    Ini_Fila(&f);

    string linhaTexto;
    cout << "Digite a expressão: ";
    getline(cin, linhaTexto);

    // Preenche a fila a partir da expressão digitada
    Processar_Expressao_Texto(&f, linhaTexto);
	do {
	    // Menu interativo após o preenchimento da fila
	    cout << "\n===============================" << endl;
	    cout << "             MENU              " << endl;
	    cout << "===============================" << endl;
	    cout << "1. Verificação de parênteses" << endl;
	    cout << "2. Cálculo da expressão" << endl;
	    cout << "3. Sair" << endl;
	    cout << "Escolha uma opção: ";
	    cin >> opcao;
	
	    switch (opcao) {
	        case 1:
	            if (Verificar_Parenteses(f)) {
	                cout << "\nResultado: Parênteses estão corretos e balanceados!" << endl;
	            } else {
	                cout << "\nResultado: Erro! Parênteses estão incorretos ou desbalanceados." << endl;
	            }
	            break;
	
	        case 2:
	            // Valida parênteses antes de tentar calcular
	            if (Verificar_Parenteses(f)) {
	                float resultado = Calc_Expressao(f);
	                cout << "\nResultado final da expressão: " << resultado << endl;
	            } else {
	                cout << "\nNão é possível calcular: Os parênteses da expressão estão incorretos!" << endl;
	            }
	            break;
			case 3:
				system("cls");
				cout<<"\n\n\t--- Volte sempre!! ---\n\n\n";
	        	break;
			default:
	            cout << "\nOpção inválida!" << endl;
	            break;
	    }
	} while(opcao!=3);
	system("timeout /t 3");
	system("exit");

    return 0;
}
