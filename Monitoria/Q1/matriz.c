#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

//Tipo matriz (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
struct matriz{
    size_t linhas;
    size_t colunas;
    int **matriz;
};

/*Inicializa uma matriz de nlinhas e ncolunas
 * inputs: nlinhas (no de linhas) e ncolunas (no de colunas)
 * output: ponteiro para a matriz inicializada
 * pre-condicao: nlinhas e ncolunas diferentes de 0
 * pos-condicao: matriz de retorno existe e contem nlinhas e ncolunas
 */
Matriz* inicializaMatriz (int nlinhas, int ncolunas){
    Matriz *matriz = malloc(sizeof(Matriz));
    matriz->matriz = calloc(nlinhas, sizeof(int*));
    for(int i = 0; i < nlinhas; i++){
        matriz->matriz[i] = calloc(ncolunas, sizeof(int));
    }
    matriz->linhas = nlinhas;
    matriz->colunas = ncolunas;

    return matriz;
}

/*Modifica o elemento [linha][coluna] da matriz mat
 * inputs: a matriz, a linha, a coluna, e o novo elemento
 * output: nenhum
 * pre-condicao: matriz mat existe, linha e coluna são válidos na matriz
 * pos-condicao: elemento [linha][coluna] da matriz modificado
 */
void modificaElemento (Matriz* mat, int linha, int coluna, int elem){
    mat->matriz[linha][coluna] = elem;
}

/*Retorna o elemento mat[linha][coluna]
 * inputs: a matriz, a linha e a coluna
 * output: elemento mat[linha][coluna]
 * pre-condicao: matriz mat existe, linha e coluna são válidos na matriz
 * pos-condicao: mat não é modificada
 */
int recuperaElemento(Matriz* mat, int linha, int coluna){
    return mat->matriz[linha][coluna];
}

/*Retorna o número de colunas da matriz mat
 * inputs: a matriz
 * output: o número de colunas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada
 */
int recuperaNColunas (Matriz* mat){
    return mat->colunas;
}

/*Retorna o número de linhas da matriz mat
 * inputs: a matriz
 * output: o número de linhas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada
 */
int recuperaNLinhas (Matriz* mat){
    return mat->linhas;
}

/*Retorna a matriz transposta de mat
 * inputs: a matriz
 * output: a matriz transposta
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada e matriz transposta existe
 */
Matriz* transposta (Matriz* mat){
    Matriz *transposta = inicializaMatriz(mat->colunas, mat->linhas);
    for(int i = 0; i < mat->linhas; i++){
        for(int j = 0; j < mat->colunas; j++){
            transposta->matriz[j][i] = mat->matriz[i][j];
        }
    }
    return transposta;
}

/*Retorna a matriz multiplicacao entre mat1 e mat2
 * inputs: as matrizes mat1 e mat2
 * output: a matriz multiplicação
 * pre-condicao: matrizes mat1 e mat2 existem, e o numero de colunas de mat1
 * correponde ao numero de linhas de mat2
 * pos-condicao: mat1 e mat2 não são modificadas e a matriz multiplicacao existe
 */
Matriz* multiplicacao (Matriz* mat1, Matriz* mat2){
    Matriz *resultado = inicializaMatriz(mat1->linhas, mat2->colunas);
    for(int i = 0; i < resultado->linhas; i++){
        for(int j = 0; j < resultado->colunas; j++){
            int parcial = 0;
            for(int k = 0; k < mat1->colunas; k++){
                parcial += mat1->matriz[i][k] * mat2->matriz[k][j];
                //printf("parcial: %d\n", parcial);
            }
            //printf("valor[%d][%d] = %d\n", i, j, parcial);
            resultado->matriz[i][j] = parcial;
        }
    }
    return resultado;
}

/*Imprime a matriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: nenhuma
 */
void imprimeMatriz(Matriz* mat){
    for(int i = 0; i < mat->linhas; i++){
        for(int j = 0; j < mat->colunas; j++){
            printf("%d ", mat->matriz[i][j]);
        }
        printf("\n");
    }
}


/*Libera memória alocada para a matriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: toda a memória alocada para matriz foi liberada
 */
void destroiMatriz(Matriz* mat){
    for(int i = 0; i < mat->linhas; i++)
        free(mat->matriz[i]);
    free(mat->matriz);
    free(mat);
}