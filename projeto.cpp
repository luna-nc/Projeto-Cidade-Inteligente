/*
    Desafios:
        1 - Relacionamento das struct:
            - Como colocar ids para a melhor associação de uma Pessoa a muitos Eventos?
        2 - Vetor:
            - Será que estão nos lugares certos?
            - Deveriam estar em algum outro lugar?
        3 - Variáveis:
            - Como localização vai armazenar o conteúdo?
            - Deve-se fazer uma análise sobre o tipo e a localização do evento para gravar algo na gravidade. Mas como?
        4 - Categorias:
            - Como apresentar para o usúario o significado de cada número armazenado na struct Eventos?
            - Será que há algo que equivale aos objetos chave-valor que possa ser usado?
*/
#include <iostream>
using namespace std;

struct Pessoa {
    string nome, cpf;
    struct {
        string bairro, residencia, rua, numero;
    }endereco;
};

struct Eventos {
    int tipo; // 1 - Buraco; 2 - Iluminação; 3 - Violência; 4 - Vandalismo
    int gravidade; // 1 - Leve; 2 - Médio; 3 - Grave; 4 - Gravíssimo
    int status; // 1 - Análise; 2 - Andamento; 3 - Execução; 4 - Solucionado
    String localizacao // O tipo da variável deve ser discutido
    string data, descricao;
};

struct Requerimento { // Estrutura de relação entre Pessoa e Eventos
    Eventos evento[];
    Pessoa requerente;
};

void imprimir(Requerimento p, int pos, int tipo){
    cout<<"--- Sobre o requerente ---\nNome: ";
    cin>>p.requerente.nome;
    cout<<"\nCPF: ";
    cin>>p.requerente.cpf;
    cout<<"\nBairro: ";
    cin>>p.requerente.endereco.bairro;
    cout<<"\nCasa ou Apartamento(C/A): ";
    cin>>p.requerente.endereco.recidencia;
    cout<<"\nRua: ";
    cin>>p.requerente.endereco.rua;
    cout<<"\nnNúmero da residencia: ";
    cin>>p.requerente.endereco.numero;
    
    cout<<"\n--- Sobre o evento ---\nTipo: ";
    cin>>p.evento[].tipo;
    cout<<"\nData da solicitação: ";
    cin>>p.evento[].data;
    cout<<"\nLocalização: ";
    cin>>p.evento[].localizacao;
    cout<<"\nDescrição: ";
    cin>>p.evento[].descricao;
}

void buscar(Requerimento p){
    int resposta;
    do{
        cout<<"\t--- Menu ---\n[1] Prioridades\n[2] Região\n[3] Data\n[0] Sair\nOpção: ";
        cin>>resposta;
        switch(resposta){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                cout<<"Opção inválida!";
        }
    }while(op!=0 && op<4);
}

void alterarStatus(Requerimento p){
    int id;
    cout<<"Digite o número do processo: ";
    cin>>id;
    do{
        cout<<"Deseja mudar o status do processo "<<id<<" para: "
        cin>>novoStatus;
    }while(novoStatus>0 && novoStatus<5);
    p.evento[id].status=novoStatus;
}

void abrirRequerimento(Requerimento p){
    cout<<"--- Sobre o requerente ---\nNome: ";
    cin>>p.requerente.nome;
    cout<<"\nCPF: ";
    cin>>p.requerente.cpf;
    cout<<"\nBairro: ";
    cin>>p.requerente.endereco.bairro;
    cout<<"\nCasa ou Apartamento(C/A): ";
    cin>>p.requerente.endereco.recidencia;
    cout<<"\nRua: ";
    cin>>p.requerente.endereco.rua;
    cout<<"\nnNúmero da residencia: ";
    cin>>p.requerente.endereco.numero;
    cout<<"\n--- Sobre o evento ---\nTipo: ";
    cin>>p.evento[].tipo;
    cout<<"\nData da solicitação: ";
    cin>>p.evento[].data;
    cout<<"\nLocalização: ";
    cin>>p.evento[].localizacao;
    cout<<"\nDescrição: ";
    cin>>p.evento[].descricao;
    //Inicia-se em 1 (Análise)
    p.evento[].status=1;
    // p.evento[].gravidade= ;
}


void subMenu(Requerimento p, int op){
    int resposta;
    do{
        cout<<"\t--- Menu ---\n[1] Buscar processos\n[2] "<<(op==1)? "Alterar status": "Abrir requerimento"<<"\n[0] Sair\nOpção: ";
        cin>>resposta;
        switch(resposta){
            case 1:
                buscar(p);
                break;
            case 2:
                (op==1)? alterarStatus(p) : abrirRequerimento(p);
                break;
            default:
                cout<<"Opção inválida!";
        }
    }while(op!=0 && op<3);
}

void menu(Requerimento p){
    int op;
    do{
        cout<<"\t--- Menu ---\n[1] Administrativo\n[2] Cidadão\n[0] Sair\nOpção: ";
        cin>>op;
        subMenu(p, op);
    }while(op!=0 && op<3);
    cout<<"\n\t--- Volte sempre!! ---\n\n";
    system("pause");
}


int main(){
    setlocale(LC_ALL,"Portuguese");
    Requerimento processos[];
    menu(processo);
    return 0;
}