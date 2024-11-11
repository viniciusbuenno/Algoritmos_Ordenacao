#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Move elementos maiores que "key" para uma posição à frente
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) // Se maior, troca posições
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    // Mescla L e R de volta em arr
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); // Coloca o pivot na posição correta
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) { // Se maior não é a raiz, ajusta o heap
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void medirTempo(void (*algoritmo)(int[], int), int arr[], int n) {
    clock_t inicio = clock();
    algoritmo(arr, n);
    clock_t fim = clock();
    double tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", tempo_cpu);
}

void gerarArrayAleatorio(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {100, 1000, 10000, 50000, 100000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        int *arr = (int *)malloc(n * sizeof(int));

        printf("Tamanho do array: %d\n", n);

        gerarArrayAleatorio(arr, n);
        printf("Selection Sort: ");
        medirTempo(selectionSort, arr, n);

        gerarArrayAleatorio(arr, n);
        printf("Insertion Sort: ");
        medirTempo(insertionSort, arr, n);

        gerarArrayAleatorio(arr, n);
        printf("Bubble Sort: ");
        medirTempo(bubbleSort, arr, n);

        gerarArrayAleatorio(arr, n);
        printf("Merge Sort: ");
        medirTempo(mergeSortWrapper, arr, n);

        gerarArrayAleatorio(arr, n);
        printf("Quick Sort: ");
        medirTempo(quickSortWrapper, arr, n);

        gerarArrayAleatorio(arr, n);
        printf("Heap Sort: ");
        medirTempo(heapSort, arr, n);

        free(arr);
    }

    return 0;
}



// Complexidade dos casos : 

// Selection
// Complexidade de Tempo:
// - Melhor caso: O(n) - Ocorre quando o array já está ordenado. Cada elemento é comparado com o anterior uma vez.
// - Pior caso: O(n^2) - Acontece quando o array está em ordem inversa; todos os elementos precisam ser comparados e movidos.
// - Caso médio: O(n^2) - Em média, o algoritmo precisa inserir cada elemento em uma posição média, realizando cerca de n*(n-1)/4 comparações.
// Complexidade de Espaço:
// - Espaço adicional: O(1) - Apenas variáveis auxiliares são utilizadas, sem necessidade de armazenamento extra.


// Insertion
// Complexidade de Tempo:
// - Melhor caso: O(n) - Ocorre quando o array já está ordenado. Cada elemento é comparado com o anterior uma vez.
// - Pior caso: O(n^2) - Acontece quando o array está em ordem inversa; todos os elementos precisam ser comparados e movidos.
// - Caso médio: O(n^2) - Em média, o algoritmo precisa inserir cada elemento em uma posição média, realizando cerca de n*(n-1)/4 comparações.
// Complexidade de Espaço:
// - Espaço adicional: O(1) - Apenas variáveis auxiliares são utilizadas, sem necessidade de armazenamento extra.


// Bubble
// Complexidade de Tempo:
// - Melhor caso: O(n) - Ocorre quando o array já está ordenado; uma passagem é suficiente para verificar a ordenação.
// - Pior caso: O(n^2) - Acontece quando o array está em ordem inversa; cada elemento é comparado repetidamente até que todos estejam ordenados.
// - Caso médio: O(n^2) - Em média, há comparações e trocas suficientes para gerar complexidade quadrática.
// Complexidade de Espaço:
// - Espaço adicional: O(1) - Utiliza apenas variáveis auxiliares para trocas.

// Merge
// Complexidade de Tempo:
// - Melhor caso: O(n log n) - Divisões e combinações são necessárias para todas as ordens de entrada.
// - Pior caso: O(n log n) - Mesmo processo de divisão e combinação é aplicado em qualquer caso.
// - Caso médio: O(n log n) - A quantidade de comparações e combinações permanece estável, resultando em complexidade log-linear.
// Complexidade de Espaço:
// - Espaço adicional: O(n) - Requer armazenamento temporário para os subarrays L e R durante as combinações.

// Quick
// Complexidade de Tempo:
// - Melhor caso: O(n log n) - Quando o pivot divide os elementos em duas metades quase iguais a cada partição.
// - Pior caso: O(n^2) - Quando o pivot é o menor ou maior elemento em cada divisão, como em um array já ordenado ou invertido.
// - Caso médio: O(n log n) - Em média, o algoritmo atinge logarítmico, assumindo partições balanceadas.
// Complexidade de Espaço:
// - Espaço adicional: O(log n) - Em um Quick Sort otimizado com partições balanceadas, a profundidade da recursão é log n.

// Heap
// Complexidade de Tempo:
// - Melhor caso: O(n log n) - A construção e a remoção do heap têm complexidade logarítmica em todas as situações.
// - Pior caso: O(n log n) - Mesmo processo de reorganização do heap em todas as entradas.
// - Caso médio: O(n log n) - Em média, o algoritmo realiza uma série de operações logarítmicas ao construir e reorganizar o heap.
// Complexidade de Espaço:
// - Espaço adicional: O(1) - Heap Sort realiza operações no próprio array sem armazenamento extra além de variáveis auxiliares.



