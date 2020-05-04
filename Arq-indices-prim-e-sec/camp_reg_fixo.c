/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Arquivos

    Aluno: Ricardo Atakiama | nUSP: 10262482


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camp_reg_fixo.h"

/*  Le os dados de um aluno */
void leEntrada(tipoAluno *aluno){
    printf("N_USP=?");
    scanf("%d", &aluno->numUSP);
    printf("NOME=?");
    scanf(" %[^\n]s", aluno->nome);
    printf("SOBRENOME=?");
    scanf(" %[^\n]s", aluno->sobrenome);
    printf("CURSO=?");
    scanf(" %[^\n]s", aluno->curso);
    printf("NOTA=?");
    scanf("%f", &aluno->nota);
}

/*  Tenta abrir os arquivos, se nao existem, os cria. Se ja existem em branco, seta first_available = -1 no arq. de indices */
void criaArquivos(){
    FILE *arq_dados, *arq_indice_prim, *arq_indice_sec, *arq_lista_invertida;

    arq_dados = fopen("alunos.dad", "rb");
    arq_indice_prim = fopen("index_prim.dad", "rb");
    arq_indice_sec = fopen("index_sec.dad", "rb");
    arq_lista_invertida = fopen("lista_invertida.dad", "rb");

    if(arq_dados == NULL){
        arq_dados = fopen("alunos.dad", "wb");
        if(arq_dados == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }
    }
    if(arq_indice_prim == NULL){
        arq_indice_prim = fopen("index_prim.dad", "wb");
        if(arq_indice_prim == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }else{
            int first_available = -1;                   //Arquivo novo (nao foi criado): nao tem registros removidos = -1
            fwrite(&first_available, sizeof(int), 1, arq_indice_prim);
        }
    }if(arq_indice_sec == NULL){
        arq_indice_sec = fopen("index_sec.dad", "wb");
        if(arq_indice_sec == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }
    }if(arq_lista_invertida == NULL){
        arq_lista_invertida = fopen("lista_invertida.dad", "wb");
        if(arq_lista_invertida == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }

    }else if(arq_dados && arq_indice_prim && arq_indice_sec && arq_lista_invertida){
        fseek(arq_dados, 0, SEEK_END);
        fseek(arq_indice_prim, 0, SEEK_END);

        if(ftell(arq_dados) == 0 && ftell(arq_indice_prim) == 0 &&
           ftell(arq_indice_sec) == 0 && ftell(arq_lista_invertida) == 0
           ){
            fclose(arq_indice_prim);fclose(arq_indice_sec); fclose(arq_lista_invertida);
            arq_indice_prim = fopen("index_prim.dad", "wb");
            if(arq_indice_prim == NULL){
                printf("Erro ao abrir\n");
                exit(-1);
            }else{
                int first_available = -1;                   //Arquivo novo (ja criado) em branco: nao tem registros removidos = -1
                fwrite(&first_available, sizeof(int), 1, arq_indice_prim);
            }
        }
    }
    fclose(arq_dados);
    fclose(arq_indice_prim);
    fclose(arq_indice_sec);
    fclose(arq_lista_invertida);

}

/*  Passa para o vetor de registros os elementos do arquivo de indices */
void carregaIndicePrimario(tipoPrimario **vetor){
    FILE *arq_indice1 = fopen("index_prim.dad", "rb");
    if(arq_indice1 == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        printf("\n Carregando 1\n\n");
        int first_available, tam, i;

        tam = tam_arq("index_prim.dad", sizeof(tipoPrimario));

        *vetor = (tipoPrimario*)malloc(sizeof(tipoPrimario) * tam);

        // Le o primeiro indice disponivel para insercao, -1 se for o ultimo do arquivo
        fread(&first_available, sizeof(int), 1, arq_indice1);

//                                                          printf("leu first available = %d\n",first_available);

        for(i=0; i<tam ;i++){
            fread(&(*vetor)[i], sizeof(tipoPrimario), 1, arq_indice1);
                                                            printf("numUSP = %d \n", (*vetor)[i].numUSP);
                                                            printf("RRN = %d \n", (*vetor)[i].rrn);
                                                            printf("\n");
        }
        fclose(arq_indice1);
    }
}

void carregaIndiceSecundario(tipoSecundario **vetor, listaInvertida **lista){
    FILE *arq_listaInvertida, *arq_indiceSecundario;

    arq_listaInvertida = fopen("lista_invertida.dad", "rb");
    arq_indiceSecundario = fopen("index_sec.dad", "rb");

    if(arq_listaInvertida == NULL || arq_indiceSecundario == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
                                                            printf("\n Carregar 2\n\n");

        int i, tam;

        tam = tam_arq("index_sec.dad", sizeof(tipoSecundario));

        *vetor = (tipoSecundario*)malloc(sizeof(tipoSecundario) * tam);

        for(i=0; i<tam; i++){
            fread(&(*vetor)[i], sizeof(tipoSecundario), 1, arq_indiceSecundario);
                                                            printf("Sobrenome = %s \n", (*vetor)[i].sobrenome);
                                                            printf("FIRST = %d \n",     (*vetor)[i].first);
                                                            printf("\n");
        }
        fclose(arq_indiceSecundario);

                                                                printf("\n");
        tam = tam_arq("lista_invertida.dad", sizeof(listaInvertida));


        *lista = (listaInvertida*)malloc(sizeof(listaInvertida) * tam);

                                                            printf("Carregar lista invertida \n");

        for(i=0; i<tam; i++){
            fread(&(*lista)[i], sizeof(listaInvertida), 1, arq_listaInvertida);
                                                            printf("numUSP = %d \n",    (*lista)[i].numUSP);
                                                            printf("NEXT = %d \n",      (*lista)[i].next);
                                                            printf("\n");
        }

        fclose(arq_listaInvertida);
    }
}

/*  Insere aluno no arq dados E arqs de indices, vetores em MP atualizados */

void insereRegistro(tipoAluno *aluno, tipoPrimario **vetor, tipoSecundario **vetor2, listaInvertida **lista){

    printf("insereRegistro \n");
    int i=0, pos_insercao=0, tam, tam2, tam3, first_available;

    // Abertura dos arquivos de DADOS e de INDICES
    FILE *arq_dados, *arq_indice1, *arq_indice2, *arq_lista_invertida;

    arq_dados = fopen("alunos.dad", "rb+"); // Pode sobreescrever registro marcado como removido
    arq_indice1 = fopen("index_prim.dad", "rb");
    arq_indice2 = fopen("index_sec.dad", "rb");
    arq_lista_invertida = fopen("lista_invertida.dad", "rb");

    if(arq_dados == NULL || arq_indice1 == NULL || arq_indice2 == NULL || arq_lista_invertida == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        fread(&first_available, sizeof(int), 1, arq_indice1);

        int next; //  proximo first_available, depois de usar o first available o novo sera o next

        //(1) arq. DADOS - insercao no fim
        if(first_available == -1){
            fseek(arq_dados, 0, SEEK_END);
            fwrite(aluno, sizeof(tipoAluno), 1, arq_dados);
        }
        else{
            // insercao em cima do ultimo registro removido
                printf("lendo arq dados na posicao %d \n", (int)sizeof(tipoAluno) * first_available + (int)sizeof(int) + (int)sizeof(char));
            fseek(arq_dados, sizeof(tipoAluno) * first_available + sizeof(int) + sizeof(char), SEEK_SET);
            //antes, le quem sera o proximo first available
            fread(&next, sizeof(int), 1, arq_dados);

                printf("next = %d\n", next);
                printf("escrevendo arq dados na posicao %d \n", (int)sizeof(tipoAluno) * first_available);
            fseek(arq_dados, sizeof(tipoAluno) * first_available, SEEK_SET);
            fwrite(aluno, sizeof(tipoAluno), 1, arq_dados);
        }

        fclose(arq_dados);

        //(2) arq. INDICE 1ª -
        tam = tam_arq("index_prim.dad", sizeof(tipoPrimario));
                                                                                printf("pegou tam arq = %d \n", tam);

        *vetor = (tipoPrimario*)realloc(*vetor, sizeof(tipoPrimario) * (tam+1) );

        //atualizando vetor
        for(i=0; i<tam ;i++){
            if(aluno->numUSP > (*vetor)[i].numUSP){
                pos_insercao = i+1;
                printf("POS INSERTION = %d\n\n", pos_insercao);
            }

        }

        // calcular SHIFT

        printf("T1 - copiando vetor[%d] para vetor[%d], bytes: %d \n", pos_insercao, pos_insercao + tam-pos_insercao, (int)sizeof(tipoPrimario) * (tam-pos_insercao));
        memcpy(&(*vetor)[pos_insercao + 1], &(*vetor)[pos_insercao], sizeof(tipoPrimario) * (tam-pos_insercao))  ;   //shift tam registros

        // insercao de fato

        (*vetor)[pos_insercao].numUSP = aluno->numUSP;

        //Rrn do reg no fim do arq ou do ultimo removido
        if(first_available == -1)
            (*vetor)[pos_insercao].rrn =  tam;
        else{
            (*vetor)[pos_insercao].rrn =  first_available;
        }

        fclose(arq_indice1);

        arq_indice1 = fopen("index_prim.dad", "wb");
        if(arq_indice1 == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }

        if(first_available == -1)
            fwrite(&first_available, sizeof(int), 1, arq_indice1);
        else{
            fwrite(&next, sizeof(int), 1, arq_indice1);
        }


        for(i=0; i<tam+1; i++){   // escrever vetor de volta no arq de indice
            fwrite(&(*vetor)[i], sizeof(tipoPrimario), 1, arq_indice1);
                                                      printf("T1 para arq \n %d \n", (*vetor)[i].numUSP);
                                                      printf("%d \n", (*vetor)[i].rrn);
        }

        fclose(arq_indice1);
        //==================================================================================================
        //(3) arq. INDICE 2ª e arq. lista invertida
        int ja_existe = 0;
        pos_insercao = 0;
        listaInvertida *registro; // registro vai percorrer a lista para comparar os numUSP

printf("1\n");
        tam2 = tam_arq("index_sec.dad", sizeof(tipoSecundario));
        printf("pegou tam2 arq = %d \n", tam2);

        int aux;    // apenas para guardar a posicao do sobrenome igual

        // Percorre o vetor2 procurando se ja existe o Sobrenome ou a posicao de insercao
        for(i=0; i<tam2 ;i++){
            printf("[vetor2[i].sobrenome] = %s\n",  (*vetor2)[i].sobrenome);
            printf("[vetor2[i].first] = %d\n",  (*vetor2)[i].first);

            if(strcmp (aluno->sobrenome, (*vetor2)[i].sobrenome) == 0){
                printf("Achou == \n");
                ja_existe = 1;
                aux = i;
                break;
            }
            if(strcmp (aluno->sobrenome, (*vetor2)[i].sobrenome) > 0){

                pos_insercao = i+1;
                printf("POS INSERTION = %d\n", pos_insercao);
            }
        }
printf("2\n");

        tam3 = tam_arq("lista_invertida.dad", sizeof(listaInvertida));
                                                                        printf("pegou tam3 arq = %d \n", tam3);
        *lista = (listaInvertida*)realloc(*lista, sizeof(listaInvertida)* (tam3+1));

printf("3\n");

        if(ja_existe){
                // registro eh o primeiro indice, que o t2 aponta
                registro = &(*lista)[(*vetor2)[aux].first];
                                    printf("NUSP %d | FIRST %d\n", (*lista)[(*vetor2)[aux].first].numUSP, (*vetor2)[aux].first );

                (*lista)[tam3].numUSP = aluno->numUSP;


                // Caso 1: EXISTE + Se o numUSP eh o menor de todos = COMPLETO!
                /* Works!!! */
                if(aluno->numUSP < (*registro).numUSP){
printf("4\n");

                    // alterar o next do item da lista invertida a ser inserido: e' o rrn apontado anteriormente pelo tipo secundario
                    (*lista)[tam3].next = (*vetor2)[aux].first;
                    // o novo rrn sera o da ultima posicao inserida ( = tam )
                    (*vetor2)[aux].first = tam3;


                // Caso 2: EXISTE + Se o numUSP nao eh o menor de todos
                }else{
                    int aux2;
printf("5\n");

                    while((*registro).next != -1 &&  aluno->numUSP > (*registro).numUSP ){
                        registro = &(*lista)[(*registro).next];
                        printf("reg->NUSP %d", (*registro).numUSP);

                        if((*lista)[(*registro).next].numUSP > aluno->numUSP)
                            break;
                    }

                    aux2 = (*registro).next;
                    printf("aux2=%d\n", aux2);

                    memcpy( &(*registro).next, &tam3, sizeof(int));
                    printf("*registro.next=%d\n", (*registro).next);

                    (*lista)[tam3].next = aux2;
                    printf("(*lista)[tam3].next=%d\n", (*lista)[tam3].next);
                }
        }

        /* Works!!! */
        // Caso 3: Nao existe o sobrenome = COMPLETO!

        else{
            *vetor2 = (tipoSecundario*)realloc(*vetor2, sizeof(tipoSecundario) * (tam2+1));

            // Ordena o vetor 2
            printf("T2 - copiando vetor[%d] para vetor[%d], bytes: %d \n", pos_insercao, pos_insercao + tam2-pos_insercao, (int)sizeof(tipoSecundario) * (tam2-pos_insercao));
            memcpy(&(*vetor2)[pos_insercao + 1], &(*vetor2)[pos_insercao], sizeof(tipoSecundario) * (tam2-pos_insercao))  ;   //shift tam2 *registros

            // Passa o sobrenome
            strcpy((*vetor2)[pos_insercao].sobrenome, aluno->sobrenome);
            // Passa o first
            (*vetor2)[pos_insercao].first = tam2;
            // Insere *registro no fim da lista
            (*lista)[tam3].numUSP = aluno->numUSP;
            // Nao ha next
            (*lista)[tam3].next = -1;

            tam2++; // so aumenta o arquivo secundario se cair neste caso (sobrenome diferente)
        }
        fclose(arq_indice2);
        fclose(arq_lista_invertida);

        arq_indice2 = fopen("index_sec.dad", "wb");
        arq_lista_invertida = fopen("lista_invertida.dad", "wb");
        if(arq_indice2 == NULL || arq_lista_invertida == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }

        // escreve indice secundario

printf("FWRITING - vetor2 \n\n");

        for(i=0; i<tam2; i++){
            fwrite(&(*vetor2)[i], sizeof(tipoSecundario), 1, arq_indice2);
                                                      printf("T2 para arq \n %s \n", (*vetor2)[i].sobrenome);
                                                      printf("%d \n",                (*vetor2)[i].first);
        }
        fclose(arq_indice2);
printf("FWRITING - lista \n\n");
        //escreve lista invertida


        for(i=0; i<tam3+1; i++){
            fwrite(&(*lista)[i], sizeof(listaInvertida), 1, arq_lista_invertida);
                                                      printf("LI para arq \n %d \n", (*lista)[i].numUSP);
                                                      printf("%d \n",                (*lista)[i].next);
        }
printf("FWRITING - end\n\n");


        fclose(arq_lista_invertida);

        }

}

/*  Remover registro logicamente, vetor em MP atualizado */
void removeRegistro(int num, tipoPrimario **vetor){
    printf("removeRegistro \n");
    int i=0, tam, pos, first_available, marcador = '*';


    FILE *arq_dados, *arq_indice1;

    arq_dados = fopen("alunos.dad", "r+");
    arq_indice1 = fopen("index_prim.dad", "rb");

    if(arq_dados == NULL || arq_indice1 == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{

        tam = tam_arq("index_prim.dad", sizeof(tipoPrimario));
        printf("tam=%d\n", tam);

        fread(&first_available, sizeof(int), 1, arq_indice1);

        fclose(arq_indice1);

        pos = pesquisaPrimario(*vetor, &num, 0, tam-1); //  encontra o "i" no vetor
        printf("Pos do indice a remover: %d\n", pos);

        int aux = first_available;

        first_available = (*vetor)[pos].rrn;
        printf("FA=%d, *vetor[pos].rrn = %d\n", first_available, (*vetor)[pos].rrn);

        fseek(arq_dados, (*vetor)[pos].rrn  * sizeof(tipoAluno) + (int)sizeof(int), SEEK_SET);

        fwrite(&marcador, sizeof(char), 1, arq_dados);

        fwrite(&aux, sizeof(int), 1, arq_dados);


        printf("Num do RRN no arq dados: %d\n", (*vetor)[pos].rrn  * (int)sizeof(tipoAluno) + (int)sizeof(int));

        printf("vetor[%d] vetor[%d] bytes %d", pos+1, pos, (int)sizeof(tipoPrimario) * (tam-pos-1));

        if(pos != tam-1)
            memcpy(&(*vetor)[pos], &(*vetor)[pos+1], sizeof(tipoPrimario) * (tam-pos-1));


        arq_indice1 = fopen("index_prim.dad", "wb");
        if(arq_indice1 == NULL){
            printf("Erro ao abrir\n");
            exit(-1);
        }

        fwrite(&first_available, sizeof(int), 1, arq_indice1);

        for(i=0; i<tam-1; i++)
            fwrite(&(*vetor)[i], sizeof(tipoPrimario), 1, arq_indice1);



        fclose(arq_dados);
        fclose(arq_indice1);


    }
}

/*  Impressao de um aluno */
void imprimeRegistro(tipoAluno aluno){
    printf(" \n N_USP: %d ", aluno.numUSP);
    printf(" \n Nome: %s ", aluno.nome);
    printf(" \n Sobrenome: %s ", aluno.sobrenome);
    printf(" \n Curso: %s ", aluno.curso);
    printf(" \n Nota: %.2f \n", aluno.nota);
}

void imprimePrimario(tipoPrimario aluno){
    printf(" \n N_USP: %d ", aluno.numUSP);
    printf(" \n rrn: %d \n", aluno.rrn);
}

void imprimeSecundario(tipoSecundario aluno){
    printf(" \n SOBRENOME: %s ", aluno.sobrenome);
    printf(" \n Rrn: %d \n", aluno.first);
}

void imprimeListaInvertida(listaInvertida lista){
    printf(" \n numUSP: %d ", lista.numUSP);
    printf(" \n NEXT: %d \n", lista.next);
}

/*  Abrindo arq. de dados em leitura (bin) para buscar e imprimir cada aluno */
void listarRegistros(){
    FILE *file;
    file = fopen("alunos.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        printf("\nlistar registros\n");
        tipoAluno aluno;
        while(fread(&aluno, sizeof(tipoAluno), 1, file)){
            imprimeRegistro(aluno);
        }
        fclose(file);
    }
}

/*  Abrindo arq. de indices em leitura (bin) para buscar e imprimir cada indice primario */
void listarIndicesPrimarios(){
    FILE *file;
    file = fopen("index_prim.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        printf("\nlistar indices 1 \n");
        tipoPrimario aluno;
        int first_available;

        fread(&first_available, sizeof(int), 1, file);
        printf("FA=%d\n", first_available);
        while(fread(&aluno, sizeof(tipoPrimario), 1, file)){
            imprimePrimario(aluno);
        }
        fclose(file);
    }
}

void listarIndicesSecundarios(){
    FILE *file;
    file = fopen("index_sec.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        printf("\nlistar indices 2\n");
        tipoSecundario aluno;

        while(fread(&aluno, sizeof(tipoSecundario), 1, file)){
            imprimeSecundario(aluno);
        }
        fclose(file);
    }
}

void listarListaInvertida(){
    FILE *file;
    file = fopen("lista_invertida.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        printf("\nlistar lista invertida\n");
        listaInvertida lista;

        while(fread(&lista, sizeof(listaInvertida), 1, file)){
            imprimeListaInvertida(lista);
        }
        fclose(file);
    }
}


/*  Abrindo arq. em leitura (bin) para buscar um aluno em especifico */
void pesquisaRegistro(int num){
    FILE *file;
    file = fopen("alunos.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        tipoAluno aluno;
        fseek(file, num * sizeof(tipoAluno), SEEK_SET);
        fread(&aluno, sizeof(tipoAluno), 1, file);
        imprimeRegistro(aluno);

        fclose(file);
    }
}

/*  Entra com o RRN do registro para pesquisar direto um indice primario */
void pesquisaRegistroPorIndice(int qtd){
    FILE *file;
    file = fopen("index_prim.dad", "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        if(qtd == -1){
            printf("Numero nao encontrado!\n");
        }else{
            tipoPrimario aluno;
            fseek(file, qtd * sizeof(tipoPrimario) + sizeof(int), SEEK_SET); // o sizeof(int) para pular o first_available
            fread(&aluno, sizeof(tipoPrimario), 1, file);

            pesquisaRegistro(aluno.rrn);
            fclose(file);
        }
    }
}

/*  Busca binaria em vetor de indices */
int pesquisaPrimario(tipoPrimario *aluno, int *key, int start, int end){

    int middle;

    if (start > end) {
        return -1;
    }
    middle = (start + end) / 2;

    if (*key == aluno[middle].numUSP) {
        return middle;
    } else if (*key < aluno[middle].numUSP) {
        return pesquisaPrimario(aluno, key, start, middle-1);
    } else {
        return pesquisaPrimario(aluno, key, middle+1, end);
    }
}

/*  Calcula o tamanho do arquivo */
int tam_arq(char *filename, int tam_reg){
    FILE *file;
    file = fopen(filename, "rb");
    if(file == NULL){
        printf("Erro ao abrir\n");
        exit(-1);
    }else{
        fseek (file, 0, SEEK_END);
        int tam = ftell(file)/tam_reg;
        fclose(file);
        return tam;
    }
}

/* Arquivo de dados ja sao fechados a cada operacao realizada */
void finalizaExecucao() {
    exit(0);
}

