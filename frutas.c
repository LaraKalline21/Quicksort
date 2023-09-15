#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Comparacoes{ 
    int NumTrocas;
    int NumComparacoes;
} Comparacoes;
// função que realiza a troca entre duas strings
void troca_string(char *fruta[], int i, int j)
{
    char *aux = "";
    aux = strdup(fruta[i]);
    fruta[i] = strdup(fruta[j]);
    fruta[j] = strdup(aux);

}

// particiona e retorna o índice do pivô
int particiona(char *fruta[], int inicio, int fim, struct Comparacoes comparacao)
{
	char *pivo, pivoIndice, i;
	
	pivo = fruta[fim]; // ultimo elemento = pivo
	pivoIndice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
        comparacao.NumComparacoes=comparacao.NumComparacoes +1;
		if(strcmp(fruta[i], pivo) <= 0)
		{
			comparacao.NumTrocas=comparacao.NumTrocas+1;
			// realiza a troca_string
			troca_string(fruta, i, pivoIndice);
			// incrementa o pivoIndice
			pivoIndice++;
		}
	}
	
	// troca_string o pivô
	troca_string(fruta, pivoIndice, fim);
	comparacao.NumTrocas=comparacao.NumTrocas+1;
	// retorna o índice do pivô
	return pivoIndice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(char *fruta[], int inicio, int fim, struct Comparacoes comparacao)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca_string(fruta, pivo_indice, fim);
	comparacao.NumTrocas=comparacao.NumTrocas+1;
	// chama a particiona
	return particiona(fruta, inicio, fim, comparacao);
}

void quick_sort(char *fruta[], int inicio, int fim, struct Comparacoes comparacao)
{
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(fruta, inicio, fim, comparacao);
		
		// chamadas recursivas quick_sort
		quick_sort(fruta, inicio, pivo_indice - 1, comparacao);
		quick_sort(fruta, pivo_indice + 1, fim, comparacao);
	}

}

int main()
{
	struct Comparacoes comparacao; 
    //Definição do Array
    char *arr[20] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limao", "manga",
        "abacate", "kiwi", "cereja", "morango", "pessego", "goiaba", "melancia",
        "framboesa", "amora", "caqui", "figo", "papaya"
    };
    //Tamanho do Array
    int tam_array = sizeof(arr) / sizeof(char*);
	

     comparacao.NumComparacoes = 0;
	 comparacao.NumTrocas = 0;

	// chamada do quicksort
	quick_sort(arr, 0, tam_array - 1, comparacao);
	
    //Criação de Arquivo
    FILE *stream = fopen("FrutasOrdenadas.txt", "w");
	fprintf(stream, "Número de trocas: %d\n", comparacao.NumTrocas);
	fprintf(stream, "Número de comparacoes: %d\n", comparacao.NumComparacoes);
	fprintf(stream, "Vetor ordenado:\n");


    //Escrevendo o nome das frutas em ordem crescente
    for(int i = 0; i < tam_array; i++){
        if(i != tam_array - 1)
        {
            fprintf(stream, "%s\n", arr[i]);
        }
        else
        {
            fprintf(stream, "%s", arr[i]);
        }
    }
	int mediana = tam_array / 2;
    fprintf(stream, "\nMediana: %s - %s", arr[mediana], arr[mediana + 1]);
    fclose(stream); //fecha o arquivo
	// Imprime no console as frutas ordenadas
	for(int i = 0; i < tam_array; i++)
    {
        if(i != tam_array - 1)
        {
		    printf("%s - ", arr[i]);
        }
        else
        {
		    printf("%s", arr[i]);
        }
    } 
	
	return 0; 
}
