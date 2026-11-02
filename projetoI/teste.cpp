#include <iostream>
#include <stdlib.h>
#include <string.h>
#define MAX 2
using namespace std;
// Matrizes auxiliar para exibição de texto
char tipo_str[4][12]  = {"Buraco", "Iluminacao", "Violencia", "Vandalismo"}; 
char prio_str[4][12]  = {"Leve", "Medio", "Grave", "Gravissimo"};
char status_str[4][12] = {"Analise", "Andamento", "Execucao", "Solucionado"};

typedef struct {
    char rua[50];
    int num;
} Localizacao;

typedef struct Evento {
    int id, tipo, prioridade, status;
    char descricao[100];
    Localizacao endereco;
    struct Evento *prox; // Nó da Lista Encadeada
} Evento;

typedef struct { // Header da Lista Encadeada
    Evento *Inicio;
    int Total;
} ListaEventos;

typedef struct {
    char Rnorte[50], Rsul[50], Roeste[50], Rleste[50];
    ListaEventos eventos; // Lista dinâmica de eventos da região
} Regiao;

void inicializar_lista(ListaEventos *L) {
    L->Inicio = NULL;
    L->Total = 0;
}

bool lista_vazia(ListaEventos *L) {
    return (L->Inicio == NULL);
}

Evento* criar_evento(int id, int tipo, int prioridade, const char* desc, const char* rua, int num) {
    Evento *novo = (Evento*) malloc(sizeof(Evento));
    if (novo != NULL) {
        novo->id = id;
        novo->tipo = tipo;
        novo->prioridade = prioridade;
        novo->status = 0; // Inicializa em "Analise"
        strcpy(novo->descricao, desc);
        strcpy(novo->endereco.rua, rua);
        novo->endereco.num = num;
        novo->prox = NULL;
    }
    return novo;
}

void inserir_evento(ListaEventos *L, int id, int tipo, int prioridade, const char* desc, const char* rua, int num) {
    Evento *novo = criar_evento(id, tipo, prioridade, desc, rua, num);
    if (novo != NULL) {
        novo->prox = L->Inicio; // Insere no início
        L->Inicio = novo;
        ++L->Total;
        cout << "\n[SUCESSO] Processo " << id << " registrado com sucesso!\n";
    } else {
        cout << "\n[ERRO] Falha ao alocar memoria.\n";
    }
}

Evento* buscar_evento(ListaEventos *L, int id) {
    Evento *ptO, *Pos=NULL;
    for (ptO = L->Inicio; ptO != NULL; ptO = ptO->prox) {
        if (ptO->id == id) {
            Pos = ptO;
        }
    }
    return Pos;
}

void ordenar_por_prioridade(Evento *vetor[], int tam) {
    int i, j;
    Evento *pivo;
    for (i = 1; i < tam; i++) {
        pivo = vetor[i];
        j = i - 1;
        // Ordena por prioridade maior -> menor
        while (j >= 0 && vetor[j]->prioridade < pivo->prioridade) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = pivo;
    }
}

void buscar_eventos_tipo(Regiao c[MAX][MAX]) {
    int tipoDesejado;
    system("cls");
    cout << "--- Buscar Eventos por Tipo ---\nTipo ([0] Buraco, [1] Iluminacao, [2] Violencia, [3] Vandalismo): ";
    cin >> tipoDesejado;
    Evento *aux[100]; // Vetor auxiliar de ponteiros
    int qtd = 0;
    // Percorre todas as regiões buscando os eventos do tipo especificado
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            Evento *ptO = c[i][j].eventos.Inicio;
            while (ptO != NULL) {
                if (ptO->tipo == tipoDesejado && qtd < 100) {
                    aux[qtd] = ptO;
                    qtd++;
                }
                ptO = ptO->prox;
            }
        }
    }
    if (qtd == 0) {
        cout << "\nNenhum evento do tipo selecionado foi encontrado.\n";
	} else {// Ordena os resultados antes da exibição
	    ordenar_por_prioridade(aux, qtd);
	    cout << "\n=== Eventos do Tipo: " << tipo_str[tipoDesejado] << " (Ordenados por Prioridade) ===\n";
	    for (int k = 0; k < qtd; k++) {
	        cout << "\nID: " << aux[k]->id;
	        cout << " | Prioridade: " << prio_str[aux[k]->prioridade];
	        cout << " | Status: " << status_str[aux[k]->status];
	        cout << "\nEndereco: " << aux[k]->endereco.rua << ", N: " << aux[k]->endereco.num;
	        cout << "\nDescricao: " << aux[k]->descricao;
	        cout << "\n----------------------------------------\n";
	    }
    }
    system("pause");
}

void buscar_eventos_status(Regiao c[MAX][MAX]) {
    int statusDesejado;
    system("cls");
    cout << "--- Buscar Eventos por Status ---\nStatus ([0] Analise, [1] Andamento, [2] Execucao, [3] Solucionado): ";
    cin >> statusDesejado;
    Evento *aux[100];
    int qtd = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            Evento *ptO = c[i][j].eventos.Inicio;
            while (ptO != NULL) {
                if (ptO->status == statusDesejado && qtd < 100) {
                    aux[qtd] = ptO;
                    qtd++;
                }
                ptO = ptO->prox;
            }
        }
    }
    if (qtd == 0) {
        cout << "\nNenhum evento com o status selecionado foi encontrado.\n";
    } else {
	    // Ordena os resultados antes da exibição
	    ordenar_por_prioridade(aux, qtd);
	    cout << "\n=== Eventos com Status: " << status_str[statusDesejado] << " (Ordenados por Prioridade) ===\n";
	    for (int k = 0; k < qtd; k++) {
	        cout << "\nID: " << aux[k]->id;
	        cout << " | Tipo: " << tipo_str[aux[k]->tipo];
	        cout << " | Prioridade: " << prio_str[aux[k]->prioridade];
	        cout << "\nEndereco: " << aux[k]->endereco.rua << ", N: " << aux[k]->endereco.num;
	        cout << "\nDescricao: " << aux[k]->descricao;
	        cout << "\n----------------------------------------\n";
	    }
	}
	system("pause");
}

void remover_evento(ListaEventos *L, int id) {
    if (!lista_vazia(L)) {
    	Evento *ptO = L->Inicio;
    	Evento *aux = NULL;
	    // Remoção da cabeça
	    if (L->Inicio->id == id) {
	        L->Inicio = L->Inicio->prox;
	        free(ptO);
	        --L->Total;
	        cout << "\n[SUCESSO] Processo " << id << " removido!\n";
	    } else {
		    // Remoção no meio ou fim
		    while (ptO->prox != NULL && ptO->prox->id != id) {
		        ptO = ptO->prox;
		    }
		    if (ptO->prox != NULL) {
		        aux = ptO->prox;
		        ptO->prox = aux->prox;
		        free(aux);
		        --L->Total;
		        cout << "\n[SUCESSO] Processo " << id << " removido!\n";
		    } else {
		        cout << "\n[ERRO] Processo ID " << id << " nao encontrado nesta regiao.\n";
		    }
		}
    }
}

void imprimir_eventos(ListaEventos *L) {
    if (!lista_vazia(L)) {
	    Evento *ptO;
	    for (ptO = L->Inicio; ptO != NULL; ptO = ptO->prox) {
	        cout << "\n----------------------------------------";
	        cout << "\nID Processo: " << ptO->id;
	        cout << "\nTipo: " << tipo_str[ptO->tipo];
	        cout << "\nPrioridade: " << prio_str[ptO->prioridade];
	        cout << "\nStatus: " << status_str[ptO->status];
	        cout << "\nEndereco: " << ptO->endereco.rua << ", N: " << ptO->endereco.num;
	        cout << "\nDescricao: " << ptO->descricao;
	        cout << "\n----------------------------------------\n";
	    }
    }
}

void abrir_processo(Regiao c[MAX][MAX]) {
    int i, j, id, tipo, prio, num;
    char desc[100], rua[50];
    system("cls");
    cout << "--- Abrir Novo Processo ---\nInforme as coordenadas da regiao (0 a " << MAX-1 << "):\n";
    cout << "Linha (i): "; 
	cin >> i;
    cout << "Coluna (j): "; 
	cin >> j;
    if (i < 0 || i >= MAX || j < 0 || j >= MAX) {
        cout << "\n[ERRO] Regiao invalida!\n";
    } else {
	    cout << "\nID do Processo: "; 
		cin >> id;
	    cout << "Tipo ([0] Buraco, [1] Iluminacao, [2] Violencia, [3] Vandalismo): "; 
		cin >> tipo;
	    cout << "Prioridade ([0] Leve, [1] Medio, [2] Grave, [3] Gravissimo): "; 
		cin >> prio;
	    cin.ignore(); // Limpa o buffer
	    cout << "Rua da ocorrencia: ";
	    gets(rua);
	    cout << "Numero: "; 
		cin >> num;
	    cin.ignore();
	    cout << "Descricao breve: ";
	    gets(desc);
	    inserir_evento(&(c[i][j].eventos), id, tipo, prio, desc, rua, num);
	}
	system("pause");
}

void buscar_processo(Regiao c[MAX][MAX]) {
    int id;
    system("cls");
    cout << "--- Buscar Processo por ID ---\nDigite o ID do processo: "; 
	cin >> id;
    bool achou = false;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            Evento *e = buscar_evento(&(c[i][j].eventos), id);
            if (e != NULL) {
                cout << "\nProcesso encontrado na Regiao [" << i << "][" << j << "]:";
                cout << "\nRua do evento: " << e->endereco.rua << ", " << e->endereco.num;
                cout << "\nTipo: " << tipo_str[e->tipo] << " | Prioridade: " << prio_str[e->prioridade];
                cout << "\nStatus: " << status_str[e->status];
                cout << "\nDescricao: " << e->descricao << "\n";
                achou = true;
            }
        }
    }
    if (!achou) {
        cout << "\nProcesso com ID " << id << " nao foi encontrado em nenhuma regiao.\n";
    }
    system("pause");
}

void remover_processo(Regiao c[MAX][MAX]) {
    int i, j, id;
    system("cls");
    cout << "--- Remover Processo ---\nInforme a Regiao onde o processo se encontra:\n";
    cout << "Linha (i): "; 
	cin >> i;
    cout << "Coluna (j): "; 
	cin >> j;
    cout << "ID do processo a remover: "; 
	cin >> id;
    if (i >= 0 && i < MAX && j >= 0 && j < MAX) {
        remover_evento(&(c[i][j].eventos), id);
    } else {
        cout << "\n[ERRO] Regiao invalida!\n";
    }
    system("pause");
}

void listar_por_regiao(Regiao c[MAX][MAX]) {
    int i, j;
    system("cls");
    cout << "--- Listar Ocorrencias por Regiao ---\n";
    cout << "Linha (i): "; 
	cin >> i;
    cout << "Coluna (j): "; 
	cin >> j;
    if (i >= 0 && i < MAX && j >= 0 && j < MAX) {
        cout << "\n=== Regiao [" << i << "][" << j << "] ===";
        cout << "\nLimites: N: " << c[i][j].Rnorte << " | S: " << c[i][j].Rsul 
             << " | O: " << c[i][j].Roeste << " | L: " << c[i][j].Rleste;
        cout << "\nTotal de Eventos: " << c[i][j].eventos.Total << "\n";
        imprimir_eventos(&(c[i][j].eventos));
    } else {
        cout << "\n[ERRO] Regiao invalida!\n";
    }
    system("pause");
}

void preencher_cidade(Regiao c[MAX][MAX]) {
    cout << "\t--- Preenchimento das Ruas Limite da Cidade ---\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            inicializar_lista(&(c[i][j].eventos));
            cout << "\nRegiao [" << i << "][" << j << "]:\nRua Norte: "; 
			gets(c[i][j].Rnorte);
            cout << "Rua Sul: ";   
			gets(c[i][j].Rsul);
            cout << "Rua Oeste: "; 
			gets(c[i][j].Roeste);
            cout << "Rua Leste: "; 
			gets(c[i][j].Rleste);
        }
    }
}

void menu(Regiao c[MAX][MAX]) {
    int op = -1;
    do {
        system("cls");
        cout << "\t--- Menu de Ocorrências Urbana ---\n[1] Abrir processo\n";
        cout << "[2] Buscar processo por ID\n[3] Buscar eventos por tipo\n[4] Buscar eventos por Status\n";
        cout << "[5] Remover processo\n[6] Listar processos de uma regiao\n[0] Sair\nOpcao: ";
        cin >> op;
        switch (op) {
            case 1: 
				abrir_processo(c); 
				break;
            case 2: 
				buscar_processo(c); 
				break;
            case 3: 
				buscar_eventos_tipo(c); 
				break;
			case 4: 
				buscar_eventos_status(c); 
				break;
			case 5: 
				remover_processo(c); 
				break;
            case 6: 
				listar_por_regiao(c); 
				break;
            case 0: 
				cout << "\nFinalizando sistema...\n"; 
				break;
            default: 
				cout << "\nOpcao invalida!\n"; 
				break;
        }
    } while (op != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Regiao cidade[MAX][MAX];
    preencher_cidade(cidade);
    menu(cidade);
    return 0;
}
