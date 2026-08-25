#include <iostream>
using namespace std;

char *tipo[] = {"Buraco","Iluminação","Violencia", "Vandalismo"}, 
	 *gravidade[] = {"Leve","Médio","Grave","Gravéssimo"}, 
	 *status[] = {"Análise","Andamento","Execução","Solucionado"};

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
    	char descricao[100];
	}evento[10];
}cidade[50][50];

void buscar(Processo c[][50], int i){
    int resposta;
    do{
    	system("cls");
        cout<<"\t--- Menu ---\n[1] Prioridades\n[2] Região\n[3] Data\n[0] Sair\nOpção: ";
        cin>>resposta;
        switch(resposta){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
        cout<<"Opção inválida!\nDigite novamente\n\n";
        system("pause");
    }while(resposta!=0 && resposta>4);
}

void alterarStatus(Processo c[][50], int i){
    int id, novoStatus;
    cout<<"Digite o numero do processo: ";
    cin>>id;
    do{
        cout<<"Deseja mudar o status do processo "<<id<<" para: ";
        cin>>novoStatus;
    }while(novoStatus>0 && novoStatus>5);
    c[i][50].evento[id].status=novoStatus;
}

void abrirRequerimento(Processo c[][50], int i, int j){
	system("cls");
    cout<<"--- Preencha os dados ---\nRua norte: ";
    gets(c[i][50].norte);
    cout<<"\nRua sul: ";
    gets(c[i][50].sul);
    cout<<"\nRua oeste: ";
    gets(c[i][50].oeste);
    cout<<"\nRua leste: ";
    gets(c[i][50].leste);
    system("cls");
    cout<<"\n--- Sobre o evento ---\n*para o preenchimento do 'tipo' coloque os numero referente:\t[1] Buraco;\t[2] Iluminacao;\t[3] Violencia;\t[4] Vandalismo***\nTipo:";
    cin>>c[i][50].evento[j].tipo;
    cout<<"\nData da solicitacao: ";
    cin>>c[i][50].evento[j].data;
    cout<<"\nDescricao: ";
    gets(c[i][50].evento[j].descricao);
    c[i][50].evento[j].status=1;
    // p.evento[].gravidade= ;
    j++;
}

void subMenu(Processo c[][50], int op, int i){
    int resposta, j=0;
    do{
    	system("cls");
        cout<<"\t--- Menu ---\n[1] Buscar processos\n[2] ";
		if(op==1){
			cout<<"Alterar status";
		} else {
			cout<<"Abrir requerimento";
		}
		cout<<"\n[0] Sair\nOpção: ";
        cin>>resposta;
        switch(resposta){
            case 1:
				buscar(c, i);
                break;
            case 2:
                if(op==1){ alterarStatus(c, i); } else { abrirRequerimento(c, i, j); }
                break;
        }
        cout<<"Opção inválida!\nDigite novamente\n\n";
        system("pause");
        i++;
    }while(resposta!=0 && resposta>2);
}

void menu(Processo c[][50]){
    int op=0, i=0;
    do{
        cout<<"\t--- Menu ---\n[1] Administrativo\n[2] Cidadão\n[0] Sair\nOpção: ";
        cin>>op;
        switch(op){
        	case 1:
        		case 2:
        			subMenu(c, op, i);
        		break;
		}
		cout<<"Opção inválida!\nDigite novamente\n\n";
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
