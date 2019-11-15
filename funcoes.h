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
void insertTree(Tree** t, Student* newStd, int type);
int isInTree(Tree* t, Student* newStd);

//Manter Aluno
ListStudents* insertStd(ListStudents* listStd, Student newStd);
ListStudents* newStdo(ListStudents* listStd);
ListStudents* delStd(ListStudents* listStd);

//Menu
int opMenu();
int opMenuType(char str[]);
void menu();

//Mensagens
void msgSuccess(char str[], char cod[]);

