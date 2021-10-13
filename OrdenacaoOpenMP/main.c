#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define NUM_THREADS 4

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main() {
    clock_t tStart, tStop;
    int *a, num=25, i, id, nt, potencia=1000, j;
    srand(time(NULL));

    a = (int *)malloc(sizeof(int) * num);

    if(a) {
        printf("Sucesso na alocacao de memoria!\n");

        for(i=0; i<num; i++) {
            for(j=1; j<= potencia; j++) {
                a[i] = rand() % 100;

            }
            clock_t t;
            t = clock();

            #pragma omp parallel num_threads(NUM_THREADS)
            {
                id = omp_get_thread_num();
                nt = omp_get_num_threads();
                printf("\n\nProcessado com a thread n: %d com um total de: %d\n", id, nt);
                mergesort(a, 0, num-1);
            }

            t = clock() - t;

            double time_token = (((double)t)/(CLOCKS_PER_SEC/1000));
            printf("Vetor ->[%2d] - %10d elements => %10f ms\n", i+1, potencia, time_token);
            potencia*=2;
        }
    } else {
        printf("Erro ao alocar memoria!\n");
    }

    return 0;

}

void mergesort(int a[],int i,int j) {
    int mid;

    if(i<j) {
        mid=(i+j)/2;
        mergesort(a,i,mid);
        mergesort(a,mid+1,j);
        merge(a,i,mid,mid+1,j);
    }
}

void merge(int a[],int i1,int j1,int i2,int j2) {
    int temp[1000];
    int i,j,k;
    i=i1;
    j=i2;
    k=0;

    while(i<=j1 && j<=j2) {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }

    while(i<=j1) {
        temp[k++]=a[i++];
    }

    while(j<=j2) {
        temp[k++]=a[j++];
    }

    for(i=i1,j=0; i<=j2; i++,j++) {
        a[i]=temp[j];
    }
}
