/*
	Necessário fazer um filtro sobre as opções (Qual a região?) - função buscar;
	Fazer a ordenação por data de todos.
*/
#include <iostream>
using namespace std;

char tipo[4][12] = {"Buraco","Iluminacao","Violencia","Vandalismo"}; 
char gravidade[4][12] = {"Leve","Medio","Grave","Gravissimo"};
char status[4][12] = {"Analise","Andamento","Execucao","Solucionado"};

struct Processo {
	char norte[50], sul[50], oeste[50], leste[50], bairro[50]; // Nome das ruas
    struct {
    	int id, tipo, gravidade, status;
	    /*
			Tipo: 1 - Buraco; 2 - Iluminacao; 3 - Violencia; 4 - Vandalismo
			Gravidade: 1 - Leve; 2 - Medio; 3 - Grave; 4 - Gravissimo
			Status: 1 - Analise; 2 - Andamento; 3 - Execucao; 4 - Solucionado
		*/
    	string data;
    	char descricao[];
	}evento[10];
}cidade[50][50];


void ordenar(Processo c[][50], int tam){
	for(int i=1; i<tam;i++){
		int j = i;
		while(j>0 && c[j-1]>c[j]){
			swap(c[j-1],c[j]);
			j--;
		}
	}
}

void buscar(Processo c[][50], int index){
    int resposta;
    do{
    	system("cls");
        cout<<"\t--- Menu ---\n[1] Prioridades\n[2] Regiao\n[3] Data\n[0] Sair\nOpcao: ";
        cin>>resposta;
        switch(resposta){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
        cout<<"Opcao invalida!\nDigite novamente\n\n";
        system("pause");
    }while(resposta!=0 && resposta>4);
}

void alterarStatus(Processo c[][50], int index){
    int id, novoStatus;
    cout<<"Digite o numero do processo: ";
    cin>>id;
    do{
        cout<<"Deseja mudar o status do processo "<<id<<" para: ";
        cin>>novoStatus;
    }while(novoStatus>0 && novoStatus>5);
    c[index][50].evento[id].status=novoStatus;
}

void abrirRequerimento(Processo c[][50], int index, int index2){
	system("cls");
    cout<<"--- Preencha os dados ---\nRua norte: ";
    gets(c[index][50].norte);
    cout<<"\nRua sul: ";
    gets(c[index][50].sul);
    cout<<"\nRua oeste: ";
    gets(c[index][50].oeste);
    cout<<"\nRua leste: ";
    gets(c[index][50].leste);
    system("cls");
    cout<<"\n--- Sobre o evento ---\n*para o preenchimento do 'tipo' coloque os numero referente:\t[1] Buraco;\t[2] Iluminacao;\t[3] Violencia;\t[4] Vandalismo***\nTipo:";
    cin>>c[index][50].evento[index2].tipo;
    cout<<"\nData da solicitacao: ";
    cin>>c[index][50].evento[index2].data;
    cout<<"\nDescricao: ";
    gets(c[index][50].evento[index2].descricao);
    c[index][50].evento[index2].status=1;
    // p.evento[].gravidade= ;
    j++;
}

void subMenu(Processo c[][50], int op, int index){
    int resposta, index2=0;
    do{
    	system("cls");
        cout<<"\t--- Menu ---\n[1] Buscar processos\n[2] ";
		if(op==1){
			cout<<"Alterar status";
		} else {
			cout<<"Abrir requerimento";
		}
		cout<<"\n[0] Sair\nOpcao: ";
        cin>>resposta;
        switch(resposta){
            case 1:
				buscar(c, index);
                break;
            case 2:
                if(op==1){ alterarStatus(c, index); } else { abrirRequerimento(c, index, index2); }
                break;
        }
        cout<<"Opcao invalida!\nDigite novamente\n\n";
        system("pause");
        i++;
    }while(resposta!=0 && resposta>2);
}

void menu(Processo c[][50]){
    int op=0, index=0;
    do{
        cout<<"\t--- Menu ---\n[1] Administrativo\n[2] Cidadao\n[0] Sair\nOpcao: ";
        cin>>op;
        switch(op){
        	case 1:
        		case 2:
        			subMenu(c, op, index);
        		break;
		}
		cout<<"Opcao invalida!\nDigite novamente\n\n";
        system("pause");
    	system("cls");
	}while(op!=0 && op>2);
    system("cls");
    cout<<"\n\t--- Volte sempre!! ---\n\n";
    system("pause");
}

int main(){
	setlocale(LC_ALL,"Portuguese");
    menu(cidade);
    return 0;
}
