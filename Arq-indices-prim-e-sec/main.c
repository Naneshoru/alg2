/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Arquivos */

/* Aluno: Ricardo Atakiama | nUSP: 10262482 */

#include <stdio.h>
#include <stdlib.h>
#include "camp_reg_fixo.h"

int main(void) {

	int comando;
	int tam, num, pos;

	tipoPrimario *vetorPrimario;
	tipoSecundario *vetorSecundario;
	listaInvertida *listaInvertida;

    tipoAluno aluno;
    criaArquivos();

	do {
        carregaIndicePrimario(&vetorPrimario);
        carregaIndiceSecundario(&vetorSecundario, &listaInvertida);

		printf("Operacoes:\n- Gravar(1)\n- Pesquisar(2)\n- Remover(3)\n- Finalizar(4)\n\n");

		scanf("%d", &comando);
		printf("COMANDO = %d \n", comando);

        switch(comando){
            case 1:
                leEntrada(&aluno);

                insereRegistro(&aluno, &vetorPrimario, &vetorSecundario, &listaInvertida);     //insere aluno no arq dados + arq indices, atualiza vetor

                listarRegistros();
                listarIndicesPrimarios();
                listarIndicesSecundarios();
                listarListaInvertida();
                break;

            case 2:

                listarRegistros();
                listarIndicesPrimarios();
                listarIndicesSecundarios();
                listarListaInvertida();

                printf("Digite o numero usp para procurar um aluno\n");
                scanf("%d", &num);

                tam = tam_arq("alunos.dad", sizeof(tipoAluno));

                pos = pesquisaPrimario(vetorPrimario, &num, 0, tam-1);  // Encontra o indice do aluno por busca binaria
    //                                      printf("num da pesq %d\n", num);
    //                                      printf("pos da pesq %d\n", pos);
    //                                      printf("tam-1 da pesq %d\n", tam-1);

                pesquisaRegistroPorIndice(pos); // Encontra registro por indice no arq de indices, para depois pesquisar no arq de dados

                break;

            case 3:
                printf("Digite o numero usp para remover um aluno\n");
                scanf("%d", &num);

                removeRegistro(num, &vetorPrimario);

                listarRegistros();

                listarIndicesPrimarios();
                break;

            case 4:
                free(vetorPrimario);
                free(vetorSecundario);
                free(listaInvertida);

                finalizaExecucao();

                break;

            default:
                printf("Opcao invalida\n");

        }

	} while(1);

    return 0;

}


