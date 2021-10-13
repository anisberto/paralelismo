#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main() {
    int *a, num=25, i, j, potencia=1000;
    clock_t tStart, tStop;
    double cpu_time_used;

    srand(time(NULL));

    a = (int *)malloc(sizeof(int) * num);

    for(i=0; i<num; i++) {
        for(j=1; j<= potencia; j++) {
            a[i] = rand() % 100;
        }

        clock_t t;
        tStart = clock();

        {
            mergesort(a, 0, num-1);
        }
        tStop = clock();

        cpu_time_used = ((double) tStart) / CLOCKS_PER_SEC;
        printf("Vetor ->[%2d] - %10d elements => %0.5f ms\n", i+1, potencia, cpu_time_used);
        potencia*=2;

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

    while(i<=j1)  {
        temp[k++]=a[i++];
    }

    while(j<=j2) {
        temp[k++]=a[j++];
    }

    for(i=i1,j=0; i<=j2; i++,j++) {
        a[i]=temp[j];
    }
}
