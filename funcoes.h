typedef struct{
	int cod;
	char nome[50];
	float medFinal;
} Student;

typedef struct lista{
	Student aluno;
	struct lista* prox;
} ListStudents;

typedef struct tree{
  Student* aluno;
  struct tree* sad;
  struct tree* sae;
} Tree;

ListStudents* createListStudents();
Tree* createTree();

//Arvore
int treeIsEmpty(Tree* tree);
void showTree(Tree* t);
void insertTree(Tree** t, ListStudents* newStd, int type);
int isInTree(Tree* t, ListStudents* newStd);

//Manter Aluno
ListStudents* insertStd(ListStudents* listStd, Student newStd, Tree** tCod, Tree** tNome, Tree** tMed);
ListStudents* newStdo(ListStudents* listStd, Tree** tCod, Tree** tNome, Tree** tMed);
ListStudents* delStd(ListStudents* listStd);

//Menu
int opMenu();
int opMenuType(int type);
void menuTree(Tree* tCod, Tree* tNome, Tree* tMed, int type);
void menu();

//Mensagens
void msgSuccess(char str[], char cod[]);

