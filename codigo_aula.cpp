#include <iostream>
#include <string.h>
#define N 2
using namespace std;

struct Regiao{
	char Norte[50], Sul[50], Leste[50], Oeste[50];
};

void imprimir(Regiao M[][N]){
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(!(strcmp(M[0][0].Norte, "Luciana"))){
				cout<<"\t"<<M[i][j].Norte<<" - "<<M[i][j].Sul<<" - "<<M[i][j].Leste<<" - "<<M[i][j].Oeste<<"\t";
			}
		}
		cout<<"\n";
	}
}

void registrar(Regiao M[][N]){
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			cout<<"Rua norte: ";
			cin>>M[i][j].Norte;
			cout<<"Rua sul: ";
			cin>>M[i][j].Sul;
			cout<<"Rua leste: ";
			cin>>M[i][j].Leste;
			cout<<"Rua oeste: ";
			cin>>M[i][j].Oeste;
		}
		cout<<"\n";
	}
}

void menu(Regiao C[][N]){
	int op;
    do{
        cout<<"\t--- Menu ---\n[1] Registrar\n[2] Imprimir\n[0] Sair\nOpção: ";
        cin>>op;
        switch(op){
        	case 0:
        		system("exit");
        		break;
            case 1:
                registrar(C);
                break;
            case 2:
                imprimir(C);
                break;
            default:
                cout<<"Opção inválida!\n";
        }
    }while((op>-1 || op<3) && op!=0);
}

int Tamanho(char T[]){
	int Tam=0;
	while(T[Tam]!='\0'){
		++Tam;
	}
	return Tam;
}

int main(){
	Regiao cidade[N][N]={{{"A","B","C","D"}, {"E","F","G","H"}},
						 {{"I","J","K","L"},	{"M","N","O","P"}}};
						 
	strcpy(cidade[0][0].Norte, "Luciana");
	menu(cidade);
}
