#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "vector.h"

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

int main()
{

    printf("N menor maior medio\n");

    for(int N = 1; N <= 2001; N+=200){

        double menortempo = 9999, maiortempo = 0, tempomedio = 0;
        for(int M = 0; M < 1000; M++){
            Vector *V = vector_construct();

            srand(time(NULL));
            
            //preenche o vetor com valores de 0 a N
            for(int i=0; i < N; i++){
                vector_push_back(V, rand());
            }

            // Gera um índice aleatório
            int idx = rand() % N;
            
            // Seleciona o item daquela posição 
            int valor = vector_get(V, idx);

            // Meça o tempo para encontrar o índice do item usando a busca linear 
            double inicio = get_timestamp();
            vector_sort(V);
            vector_binary_search(V, valor);
            //vector_find(V, valor);
            double fim = get_timestamp();
            double duracao = fim - inicio; 
        
            // Atualize as estatísticas de menor tempo, maior tempo e tempo médio.
            if(duracao < menortempo)
                menortempo = duracao;
            if(duracao > maiortempo)
                maiortempo = duracao;
            tempomedio += duracao;

            //printf("%d, %d\n", N, M);

            free(V);

        }

        tempomedio = tempomedio / 1000;

        printf("%d %.10lf %.10lf %.10lf\n", N, menortempo, maiortempo, tempomedio);
    
    }

    return 0;
}