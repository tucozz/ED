
# Exercícios de Preparação para a Prova

5. Considere uma lista encadeada para armazenar informações de diferentes pessoas (ambas as estruturas são dadas a seguir). Escreva uma função para recuperar os dados de uma pessoa a partir do CPF. 

```
typedef struct 
{
    char *cpf;
    char *nome;
    int idade; 
    float altura; 
} Pessoa; 

typedef struct No
{
    Pessoa p;
    struct No *prox;
} No;

typedef struct 
{
    No *cabeca;
} ListaEncadeada;

// funcao a ser implementada
Pessoa buscar_pessoa(ListaEncadeada *l, char *cpf);

```

9. Escreva uma função para remover a primeira ocorrência de um item em uma lista duplamente encadeada. Assuma que a estrutura da lista é dada a seguir: 

```
typedef struct No
{
    int val;
    No *prox;
    No *ant;
}No;

typedef struct
{
    No *cabeca;
    No *ultimo;
}Lista;

// funcao a ser implementada
void remove(Lista *lista, int x);
```

10. Escreva uma função para inserção ordenada de itens em uma lista encadeada com ponteiro para o último elemento. Assuma que a estrutura da lista é dada a seguir: 

```
typedef struct No
{
    int val;
    No *prox;
}No;

typedef struct
{
    No *cabeca;
    No *ultimo;
}Lista;

// funcao a ser implementada
void insere_ordenado(Lista *lista, int x);
```

11. Usando a função da questão anterior, implemente uma função para ordenação *in-place* de listas encadeadas com ponteiro para o último elemento. A complexidade de espaço adicional da solução não deve ser superior à O(1).

12. Considere uma representação de matrizes esparsas dada por um vetor ordenado de nós em que: 
* Cada nó representa um valor não nulo que contém o número da linha, da coluna e o valor da posição na matriz. 
*  O vetor é ordenado pelo número da linha e, para itens na mesma linha, pelo número da coluna. 

    **Exemplo 1**: A matriz 

    ```
    | 0 7 8 |
    | 0 0 0 |
    | 4 5 6 | 
    ```

    seria representada como: 

    ```
    linha  | 0 0 2 2 2 |
    coluna | 1 2 0 1 2 |
    valor  | 7 8 4 5 6 |
    ```

    **Exemplo 2**: A matriz 

    ```
    | 0 0 0 |
    | 0 0 3 |
    | 5 0 4 | 
    ```

    seria representada como: 

    ```
    linha  | 1 2 2 |
    coluna | 2 0 2 |
    valor  | 3 5 4 |
    ```

Escreva uma função que dada esta representação de matriz, permita recuperar o valor de um elemento a partir dos índices da linha e coluna com complexidade ```O(log2 n)```, onde ```n``` é o número de elementos não nulos. A função deve retornar valores nulos quando for o caso. A estrutura do tipo e a assinatura da função são dadas a seguir: 

```
typedef struct 
{
    int linha;
    int coluna; 
    double valor;
} No;

typedef struct 
{
    No *vals;  // array de valores não nulos
    int tam;   // numero de itens não nulos
} Matriz;

// funcao a ser implementada
double get(Matriz *m, int linha, int coluna);
```

13. Considerando a representação de matriz esparsa da questão anterior, explique como implementar as operações abaixo da forma mais eficiente quanto possível e discuta as complexidades da solução. 

* Verificar se uma linha é nula. 

* Verificar se uma coluna é nula. 

* Recuperar os itens não nulos de uma linha.

* Recuperar os itens não nulos de uma coluna. 

14. Considerando a representação de matriz esparsa da questão 12, implemente uma função que calcule o produto ponto a ponto entre duas matrizes esparsas e retorne a soma dos elementos da matriz resultante. A declaração da função é dada a seguir. Note que não é necessário construir a matriz resultante do produto ponto a ponto explicitamente. 

```
double prod_sum(Matriz *m1, Matriz *m2);
```

15. Considere uma implementação de lista encadeada simples que, para minimizar o uso de memória, não armazena o número de nós da lista. Uma forma de obter o elemento do meio de uma lista neste formato é utilizar dois ponteiros para percorrer a lista, sendo que para cada passo do primeiro ponteiro, o segundo dará dois passos. Quando o segundo ponteiro chegar ao fim da lista, o primeiro estará na metade. Usando esta ideia, implemente uma função para recuperar o elemento do meio de uma lista encadeada.

```
typedef struct No
{
    int val;
    No *prox;
}No;

typedef struct
{
    No *cabeca;
}Lista;

// funcao a ser implementada
int obtem_meio(Lista *lista);
```

16. Considerando a estrutura de lista encadeada da questão anterior, escreva uma função que verifique se a lista define um palíndromo (o conteúdo é igual lendo da direita para a esquerda e da esquerda para a direita). A solução deve armazenar no máximo N/2 itens adicionais, onde N é o número de elementos da lista. Escreva, a seguir, uma solução com complexidade constante de espaço adicional.

```
int eh_palindromo(Lista *lista);
```