/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Arquivos */

/* Aluno: Ricardo Atakiama | nUSP: 10262482 */

#ifndef CAMP_REG_FIXO_H_INCLUDED
#define CAMP_REG_FIXO_H_INCLUDED

#define TAM 16

typedef int tipoChave;

typedef struct {            // Estrutura gravada no arq de dados
	tipoChave numUSP;       //4 bytes
	char nome[TAM];         //16 * 3 = 48 bytes
	char sobrenome[TAM];
	char curso[TAM];
	float nota;             //4 bytes
} tipoAluno;                //=========
                            //TOTAL = 56 bytes

typedef struct {
    tipoChave numUSP;
    int rrn;
} tipoPrimario;

typedef struct {
    char sobrenome[TAM];
    int first;
} tipoSecundario;

typedef struct {
    tipoChave numUSP;
    int next;
} listaInvertida;


void criaArquivos();

void leEntrada(tipoAluno *);

void insereRegistro(tipoAluno *, tipoPrimario **, tipoSecundario **, listaInvertida **);

void imprimeRegistro(tipoAluno);
void imprimePrimario(tipoPrimario);

void listarRegistros();
void listarIndicesPrimarios();
void listarIndicesSecundarios();
void listarListaInvertida();

void pesquisaRegistro(int);
void pesquisaRegistroPorIndice(int);
int pesquisaPrimario(tipoPrimario *,int *,int ,int );

int tam_arq(char *, int);
void ordena_indice(tipoPrimario **);

void carregaIndicePrimario(tipoPrimario **);
void carregaIndiceSecundario(tipoSecundario **, listaInvertida **);

void removeRegistro(int, tipoPrimario **);
void finalizaExecucao();

#endif // CAMP_REG_FIXO_H_INCLUDED
