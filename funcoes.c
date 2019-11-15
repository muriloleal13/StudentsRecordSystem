#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

ListStudents* criaListAlunos(){
	return NULL;
}

Tree* createTree(){
	return NULL;
}

//ARVORE
int treeIsEmpty(Tree* t){
	return t == NULL;
}

void showTree(Tree* t){  
	printf("<");
	if(!treeIsEmpty(t)){
		printf("%s ", (*t->aluno).nome);
		showTree(t->sae);
		showTree(t->sad);
	}
	printf(">");
}

void insertTree(Tree** t, Student* newStd, int type){
	if(*t == NULL){
		*t = (Tree*)malloc(sizeof(Tree));
		(*t)->sae = NULL;
		(*t)->sad = NULL;
		(*t)->aluno = newStd;
	}else{
		Student std = (*(*t)->aluno);
		if(((*newStd).cod < std.cod && type == 1) || (strcmp((*newStd).nome, std.nome) < 0 && type == 2) || ((*newStd).medFinal < std.medFinal && type == 3))
			insertTree(&(*t)->sae, newStd, type);
		else		
			insertTree(&(*t)->sad, newStd, type);
	}
}

int isInTree(Tree* t, Student std){
	if(treeIsEmpty(t))
		return 0;
	return t->std == std || isInTree(t->sae, std) || isInTree(t->sad, std);
}

//MANTER ALUNO
ListStudents* insertStd(ListStudents* listStd, Student newStd){

	ListStudents* new = (ListStudents*) malloc(sizeof(ListStudents));

	new->aluno = newStd;
	new->prox = listStd;
	return new;
}

ListStudents* newStd(ListStudents* listStd){

	printf("=== CADASTRA ALUNO ===\n");

	Student newStd;

	printf("Digite o codigo do aluno: ");
	scanf("%d", &newStd.cod);
	fflush(stdin);
	printf("Digite o nome do aluno: ");
	gets(newStd.nome);
	fflush(stdin);
	printf("Digite a media final do aluno: ");
	scanf("%f", newStd.medFinal);
	fflush(stdin);
	listStd = insertStd(listStd, newStd);
	msgSuccess("Aluno", newStd.nome);

	return listStd;
}

ListStudents* delStd(ListStudents* listStd){

	printf("=== REMOVE ALUNO ===\n");

	int cod;

	printf("Digite o Codigo do aluno a remover: ");
	scanf("%d", &cod);

	ListStudents* ant = NULL;
	ListStudents* p = listStd;

	while (p != NULL && p->aluno.cod != cod){
		ant = p;
		p = p->prox;
	}

	if (p == NULL){
		printf("Nenhum aluno com o codigo %d encontrado.\n", cod);
		return listStd; 
	}else if(ant == NULL){
		listStd = p->prox; 
	}else{
		ant->prox = p->prox;
	}

	printf("Aluno %s removido com sucesso.\n", p->aluno.nome);

	free(p);

	return listStd;
}

//MENU
int opMenu(){

	int op;

	printf("=== MENU ===\n");

	printf("1 - Cadastrar Aluno\n2 - Remover Aluno\n3 - Arvore Aluno Codigo\n4 - Arvore Aluno Nome\n5 - Arvore Aluno Media FInal\n6 - Sair\nOp: ");
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

int opMenuType(char str[]){

	int op;

	printf("=== Menu %s === \n", str);

	printf("1 - Lisatr %s\n2 - Busca %s\n3 - Voltar ao Menu\nOp: ", str, str);
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

void menu(){

	ListStudents* listStd = criaListStudents();

	int op = opMenu();
	fflush(stdin);

	while(op != 6){
		switch(op){
			case 1:
				listStd = insertStd();
				break;
			case 2:
				listStd = delStd();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				printf("Sessao finalizada.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		op = opMenu();
	}
	printf("Finalizando sessao...\n");
}

//MENSAGENS PADRÕES
void msgSuccess(char str[], char cod[]){
	printf("%s %s cadastrada com sucesso\n", str, cod);
}
