#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

#define COUNT 10 

ListStudents* criaListStudents(){
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

int _print_t(Tree* tree, int is_left, int offset, int depth, char s[20][255], int type){
    char b[50];
    int width;

    if (!tree) return 0;

    switch(type){
    	case 1:
    		width = 5;
    		sprintf(b, "(%03d)", (*tree->aluno).cod);
    		break;
    	case 2:
    		width = strlen((*tree->aluno).nome) + 2;
    		sprintf(b, "(%s)", (*tree->aluno).nome);
    		break;
    	case 3:
    		width = 6;
    		if((*tree->aluno).medFinal > 9.99)
    			width++;
    		sprintf(b, "(%.2f)", (*tree->aluno).medFinal);
    		break;

    }

    int left  = _print_t(tree->sae,  1, offset,                depth + 1, s, type);
    int right = _print_t(tree->sad, 0, offset + left + width, depth + 1, s, type);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(Tree* tree, int type){
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s, type);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

void insertTree(Tree** t, ListStudents* newStd, int type){

	if(*t == NULL){
		*t = (Tree*)malloc(sizeof(Tree));
		(*t)->sae = NULL;
		(*t)->sad = NULL;
		(*t)->aluno = &(newStd->aluno);
	}else{
		if((newStd->aluno.cod < (*(*t)->aluno).cod && type == 1) || (strcmp(newStd->aluno.nome, (*(*t)->aluno).nome) < 0 && type == 2) || (newStd->aluno.medFinal < (*(*t)->aluno).medFinal && type == 3))
			insertTree(&(*t)->sae, newStd, type);
		else		
			insertTree(&(*t)->sad, newStd, type);
	}
}

bool isInTree(Tree* t, Student std){

	if(treeIsEmpty(t)){
		printf("Arvore esta vazia.\n");
		return false;
	}

	if((*t->aluno).cod == std.cod || strcmp((*t->aluno).nome, std.nome) == 0 || (*t->aluno).medFinal == std.medFinal || isInTree(t->sae, std) || isInTree(t->sad, std)){
		printf("Aluno encontrado!\nCodigo:%d\nNome: %s\nMedia Final: %.2f\n---\n", (*t->aluno).cod, (*t->aluno).nome, (*t->aluno).medFinal);
		return true;
	}else{
		printf("Aluno nao encontrado.\n");
		return false;
	}
}

void searchStd(Tree* t, int type){

	Student std;

	switch(type){
		case 1:
			printf("Digite o Codigo do aluno: ");
			scanf("%d", &std.cod);
			fflush(stdin);
			break;
		case 2:
			printf("Digite o Nome do aluno: ");
			gets(std.nome);
			fflush(stdin);
			break;
		case 3:
			printf("Digite a Media Final do aluno: ");
			scanf("%f", &std.medFinal);
			fflush(stdin);
			break;
	}

	isInTree(t, std);
}

Tree* freeTree(Tree* t){

	if(!treeIsEmpty(t)){
		freeTree(t->sae);
		freeTree(t->sad);
		free(t);
	}

	return NULL;
}

//MANTER ALUNO
ListStudents* insertStd(ListStudents* listStd, Student newStd, Tree** tCod, Tree** tNome, Tree** tMed){

	ListStudents* new = (ListStudents*) malloc(sizeof(ListStudents));

	new->aluno = newStd;
	new->prox = listStd;
	insertTree(tCod, new, 1);
	insertTree(tNome, new, 2);
	insertTree(tMed, new, 3);
	return new;
}

ListStudents* newStd(ListStudents* listStd, Tree** tCod, Tree** tNome, Tree** tMed){

	printf("=== CADASTRA ALUNO ===\n");

	Student newStd;

	printf("Digite o codigo do aluno: ");
	scanf("%d", &newStd.cod);
	fflush(stdin);
	printf("Digite o nome do aluno: ");
	gets(newStd.nome);
	fflush(stdin);
	printf("Digite a media final do aluno: ");
	scanf("%f", &newStd.medFinal);
	fflush(stdin);

	listStd = insertStd(listStd, newStd, tCod, tNome, tMed);
	msgSuccess("Aluno", newStd.nome);

	return listStd;
}

ListStudents* delStd(ListStudents* listStd, Tree** tCod, Tree** tNome, Tree** tMed){

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

	*tCod = freeTree(*tCod);
	*tNome = freeTree(*tNome);
	*tMed =freeTree(*tMed);

	printf("Aluno %s removido com sucesso.\n", p->aluno.nome);
	free(p);

	p = listStd;
	while(p != NULL){
		insertTree(tCod, p, 1);
		insertTree(tNome, p, 2);
		insertTree(tMed, p, 3);
		p = p->prox;
	}

	return listStd;
}

//MENU
int opMenu(){

	int op;

	printf("=== MENU ===\n");

	printf("1 - Cadastrar Aluno\n2 - Remover Aluno\n3 - Arvore Alunos por Codigo\n4 - Arvores Aluno por Nome\n5 - Arvores Aluno por Media Final\n6 - Sair\nOp: ");
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

int opMenuType(int type){

	int op;
	char str[50];

	switch(type){
		case 1:
			strcpy(str, "Codigo");
			break;
		case 2:
			strcpy(str, "Nome");
			break;
		case 3:
			strcpy(str, "Media Final");
			break;
	}

	printf("=== Menu Arvore Alunos por %s === \n", str);

	printf("1 - Listar por %s\n2 - Busca por %s\n3 - Voltar ao Menu\nOp: ", str, str);
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

void menuTree(Tree* tCod, Tree* tNome, Tree* tMed, int type){

	int op = opMenuType(type);
	fflush(stdin);

	while(op != 3){
		switch(op){
			case 1:
				if(type == 1) print_t(tCod, 1);
				else if(type == 2) print_t(tNome, 2);
				else print_t(tMed, 3);
				printf("\n");
				break;
			case 2:
				if(type == 1) searchStd(tCod, type);
				else if(type == 2) searchStd(tNome, type);
				else searchStd(tMed, type);
				break;
			case 3:
				printf("Voltando ao menu...\n");
				break;
		}
		op = opMenuType(type);
	}
	system("cls");
}

void menu(){

	ListStudents* listStd = criaListStudents();
	Tree* tCod = createTree();
	Tree* tNome = createTree();
	Tree* tMed = createTree();

	int op = opMenu();
	fflush(stdin);

	while(op != 6){
		switch(op){
			case 1:
				listStd = newStd(listStd, &tCod, &tNome, &tMed);
				break;
			case 2:
				listStd = delStd(listStd, &tCod, &tNome, &tMed);
				break;
			case 3:
				menuTree(tCod, tNome, tMed, 1);
				break;
			case 4:
				menuTree(tCod, tNome, tMed, 2);
				break;
			case 5:
				menuTree(tCod, tNome, tMed, 3);
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
	printf("%s %s cadastrado com sucesso\n", str, cod);
}
