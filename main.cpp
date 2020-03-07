// Trabalho_Final_Angela.cpp
//
//  Created by Renan Augusto Abib Pastore - RA 18031377 and Victor Hugo Bonini Chiossi - RA 18069369 on 01/12/2018.
//
//

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

using namespace std;

typedef struct { //definição da struct pelo typedef, o que faz com que na hora de usar só seja necessário seu nome
	int codigo; //declaração do campo código da struct de tipo inteiro
	char titulo[50]; //declaração do campo título da struct de tipo array de caracteres
	float preco; //declaração do campo preço da struct de tipo decimal
	int idadeMinima; // declaração do campo idadeMinima da struct de tipo inteiro
} jogo;

typedef jogo elemento;

#define nome_arquivo "JOGOSLT.DAT"
#include "ListaLinearArq.h"

void menu(); // Menu - Essa função faz o menu do programa. Seu retorno é de tipo vazio.
void iniciar(Lista& L); // Cadastrar jogo - Essa função cadastra um novo jogo na lista.
void cadastrar(Lista& L); // Cadastrar jogo - Essa função insere um novo jogo. Seu retorno é de tipo vazio.
void consultar_jogo(Lista& L); // Consultar jogo - Essa função consulta um jogo da lista. Seu retorno é de tipo definido pelo elemento.
void modificar(Lista& L); // Alterar dados do jogo - Essa função altera os campos da struct jogo de determinado jogo. Seu retorno é de tipo vazio.
void excluir(Lista& L); // Remover jogo - Essa função elimina um jogo da lista. Seu retorno é de tipo definido pelo elemento.
void imprime_relatorio(Lista L); // Relatórios de todos os jogos - Essa função imprime todas as informações dos jogos cadastrados. Seu retorno é de tipo vazio.
/******************FUNCÕES_IMPRIME_RELATORIO******************/
void dadosUm(Lista &L); // opção que mostra apenas as informações de um único jogo
void dadosTodos(Lista &L); // opção que mostra as informações de todos os jogos
void dadosPrecos(Lista &L); // opção que mostra os jogos de acordo com uma faixa de preço definida pelo usuário
void dadosMaiores(Lista &L); // opção que mostra todos os jogos cadastrados indicados para maiores de 18 anos
void dadosMenores(Lista &L); // opção que mostra todos os jogos cadastrados indicados para menores de 18 anos

int main() {
    setlocale(LC_ALL, "Portuguese");
	Lista L; // lista linear que armazenará os dados dos jogos
	int opcao;// variável do tipo int que será usada para acesar as opções do menu
	char a; // variável do tipo char que será usada para conversão a outra de tipo inteiro (variável opcao)

	do//MENU
	{
		do
		{
			system("cls");
			cout << "=========================================" << endl;
			cout << "\tSistema Cadastro de jogos" << endl;
			cout << "=========================================" << endl;
			cout << " 0. Iniciar Cadastro\n 1. Incluir JOGO\n 2. Consultar JOGO\n 3. Excluir JOGO\n 4. Alterar dado(s) JOGO\n 5. Relatórios JOGO\n 6. Sair" << endl;
			cout << endl;
			a = getch();
			opcao = a - 48;
		} while
		(opcao < 0 || opcao > 6);
		switch (opcao)
		{
		case 0: iniciar(L);
			break;
		case 1: cadastrar(L);
			break;
		case 2: consultar_jogo(L);
			break;
		case 3: excluir(L);
			break;
		case 4: modificar(L);
			break;
		case 5: imprime_relatorio(L);
			break;
		}
	} while (opcao != 6);

}

void iniciar(Lista& L) {
    cout << "=========================================" << endl;
    cout << "              Iniciar Lista              " << endl;
    cout << "=========================================" << endl;

    int tentativa = 1; // variável que controlará em até três o número máximo de chances permitidas para se acertar a senha que iniciará uma nova lista
    int n1, n2, n3; // variáveis do tipo int que armazenarão uma senha para iniciar uma nova lista
    char opc, a, b, c; // variável opc responsável pelas decisões [S/N] do usuário. Demais variáveis responsáveis para conversão de uma variável do tipo char para outra variável do tipo inteiro.

    do{
        cout << "Digite a senha" <<endl;
        a = getch();
        b = getch();
        c = getch();
        n1 = a - 48;
        n2 = b - 48;
        n3 = c - 48;
        tentativa++;
        if ((n1 == 1) && (n2 == 2) && (n3 == 3)){
            init(L);
            cout << "Lista vazia iniciada com sucesso\n" << endl;
            tentativa = 4;
        }else{
            if (tentativa < 4){
                cout << "Deseja tentar novamente (S/N)" << endl;
                opc = getch();
                opc = toupper(opc);
                }
                if (opc == 'N'){
                    tentativa = 4;
                    cout << endl;
                    exit (1);
                }
            if (tentativa == 4){
                cout << "As 3 tentativas foram incorretas" << endl;
                exit (1);
            }
        }
    }while(tentativa <= 3);
    cout << "Aperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void cadastrar(Lista& L){
    cout << "=========================================" << endl;
    cout << "             Iniciar Cadastro            " << endl;
    cout << "=========================================" << endl;

    elemento V;

    cout << "Insira o codigo do elemento: "<< endl;
    cin >> V.codigo;
    cout << "Insira o titulo do elemento: " << endl;
    fflush(stdin);
    gets(V.titulo);
    fflush(stdin);
    cout << "Insira o preco do elemento: " << endl;
    cin >> V.preco;
    cout << "Insira a idade minima para jogar o elemento: " << endl;
    cin >> V.idadeMinima;
    inserir(L, V, compr(L)+1);

    system("cls");

    cout << "Jogo cadastrado com sucesso:" << endl;
    cout << "Código: " << V.codigo << endl;
    cout << "Título: " << V.titulo << endl;
    cout << "Preço: " << V.preco << endl;
    cout << "Idade mínima: " <<  V.idadeMinima << "\n" << endl;
    cout << "Aperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void consultar_jogo(Lista& L){
    cout << "=========================================" << endl;
    cout << "              Consultar Jogo             " << endl;
    cout << "=========================================" << endl;
    cout << "Digite o nome do jogo que deseja consultar" << endl;

    char nome[50]; // string que armazenará um nome do jogo digitado pelo usuário e buscará na lista por comparação
    fflush(stdin);
    gets(nome);
    fflush(stdin);

    for(int i = 1; i <= compr(L); i++){
        elemento V = consultar(L, i);
        if(strcmp(V.titulo, nome) == 0){
            cout <<"Jogo Consultado:\nCódigo "<< V.codigo << "\nNome: " << V.titulo << "\nPreco: " << V.preco << "\nIdade mínima: " << V.idadeMinima << endl;
        }
    }
    cout << "Aperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void modificar(Lista& L){
    cout << "=========================================" << endl;
    cout << "              Modificar Jogo             " << endl;
    cout << "=========================================" << endl;
    cout << "Digite o Título do jogo que deseja alterar" << endl;

    elemento V;
    char nome[50];
    gets(nome);

    for(int i = 1; i <= compr(L); i++){
        elemento V = consultar(L, i);
        if(strcmp(V.titulo, nome) == 0){
            cout <<"Dados atuais do jogo a ser alterado:\nCódigo "<< V.codigo << "\nNome: " << V.titulo << "\nPreco: " << V.preco << "\nIdade mínima: " << V.idadeMinima << "\n" << endl;
            cout << "Insira o novo código:" <<  endl;
            fflush(stdin);
            cin >> V.codigo;
            cout << "Insira o novo título:" << endl;
            fflush(stdin);
            gets(V.titulo);
            fflush(stdin);
            cout << "Insira o novo preço:"<< endl;
            cin >> V.preco;
            fflush(stdin);
            cout << "Insira a nova idade mínima:" << endl;
            cin >> V.idadeMinima;
            fflush(stdin);
            alterar(L, V, i);
            cout <<"Jogo alterado com sucesso" << endl;
        }
    }

    cout << "Aperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void excluir(Lista& L){
    cout << "=========================================" << endl;
    cout << "               Excluir Jogo              " << endl;
    cout << "=========================================" << endl;
    cout << "Digite o título do jogo que deseja excluir" << endl;

    int i;
    char nome[50]; // string que armazenará um nome do jogo digitado pelo usuário e buscará na lista por comparação
    fflush(stdin);
    gets(nome);
    fflush(stdin);
    elemento V;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        if(strcmp(V.titulo, nome)==0){
            cout <<"Jogo excluído:\nCódigo "<< V.codigo << "\nNome: " << V.titulo << "\nPreco: " << V.preco << "\nIdade mínima: " << V.idadeMinima << endl;
            V = eliminar(L, i);
            cout <<"Jogo excluído com sucesso" << endl;
        }
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void imprime_relatorio(Lista L){/************************FAZER ESTILO TABELA*****************************/
	int opcao; // variável do tipo int que será usada para acesar as opções do menu
	char a; // variável do tipo char que será usada para conversão a outra de tipo inteiro (variável opcao)
	do
	{

	    system("cls");
		do
		{
			cout << "=========================================" << endl;
			cout << "                Relatorios               " << endl;
			cout << "=========================================" << endl;
			cout << " 1. Dados de um Jogo\n 2. Todos os Jogos\n 3. Jogos por faixa de preço \n 4. Jogos para maiores de 18 anos JOGO \n 5. Jogos para menores de 18 anos \n 6. Voltar \n 7. Sair" << endl;
			cout << endl;
			a = getch();
			opcao = a - 48;
		} while (opcao < 1 || opcao > 8);
		switch (opcao)
		{
		case 1: dadosUm(L);
			break;
		case 2: dadosTodos(L);
			break;
		case 3: dadosPrecos(L);
			break;
		case 4: dadosMaiores(L);
			break;
		case 5: dadosMenores(L);
			break;
        case 7: exit(1);
			break;
		default:
			;
		}
	} while (opcao != 6);
}

void dadosUm(Lista &L){
    int cod; // string que armazenará um nome do jogo digitado pelo usuário e buscará na lista por comparação

    cout << "Digite o código do jogo que deseja consultar\n";
    cin >> cod;
    elemento V;
    system("cls");
    cout << "-------------------------------------------------------" << endl;
    cout << "|Código|            Nome           |Preco |IdadeMínima|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        if(V.codigo == cod){
            printf("|  %2d  |%27s|%6.2f|%6d     |\n"  ,V.codigo , V.titulo , V.preco ,V.idadeMinima );
            cout << "-------------------------------------------------------" << endl;
        }
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void dadosTodos(Lista &L){
    system("cls");
    elemento V;

    cout << "-------------------------------------------------------" << endl;
    cout << "|Código|            Nome           |Preco |IdadeMínima|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        printf("|  %2d  |%27s|%6.2f|%6d     |\n"  ,V.codigo , V.titulo , V.preco ,V.idadeMinima );
        cout << "-------------------------------------------------------" << endl;
        Sleep(150);
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void dadosPrecos(Lista &L){
    elemento V;
    int p1, p2;

    cout << "Escreva o valor mínimo que deseja consultar" << endl;
    cin >> p1;
    cout << "Escreva o valor máximo que deseja consultar" << endl;
    cin >> p2;
    system("cls");
    cout << "-------------------------------------------------------" << endl;
    cout << "|Código|            Nome           |Preco |IdadeMínima|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        if((V.preco >= p1) && (V.preco <=p2)){
            printf("|  %2d  |%27s|%6.2f|%6d     |\n"  ,V.codigo , V.titulo , V.preco ,V.idadeMinima );
            cout << "-------------------------------------------------------" << endl;
            Sleep(100);
        }
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void dadosMaiores(Lista &L){
    elemento V;
    system("cls");

    cout << "-------------------------------------------------------" << endl;
    cout << "|Código|            Nome           |Preco |IdadeMínima|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        if(V.idadeMinima >= 18){
            printf("|  %2d  |%27s|%6.2f|%6d     |\n"  ,V.codigo , V.titulo , V.preco ,V.idadeMinima );
            cout << "-------------------------------------------------------" << endl;
            Sleep(100);
        }
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}

void dadosMenores(Lista &L){
    elemento V;
    system("cls");

    cout << "-------------------------------------------------------" << endl;
    cout << "|Código|            Nome           |Preco |IdadeMínima|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for(int i = 1; i <= compr(L); i++){
        V = consultar(L, i);
        if(V.idadeMinima < 18){
            printf("|  %2d  |%27s|%6.2f|%6d     |\n"  ,V.codigo , V.titulo , V.preco ,V.idadeMinima );
            cout << "-------------------------------------------------------" << endl;
            Sleep(100);
        }
    }
    cout << "\nAperte qualquer tecla para retornar ao menu:" << endl;
    getch();
}
