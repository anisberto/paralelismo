#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <omp.h>

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int dateRand()
{
    int i, R, BASE;
    for(i =0; i < 12; i++)
    {
        R = (2^i)* 1000;
        printf("Array Interno: %d", R);
        return R;
    }
}

int main()
{
    int *a, num = dateRand(), i;
/*
    printf("Defina o tamanho do vetor: ");
    scanf("%d",&num);
*/
    srand(time(NULL));

    a = (int *)malloc(sizeof(int) * num);
    printf("\nArray %d ", num);
    printf("\n\nVetor nao-ordenado:\n");


    for(i=0; i<num; i++)
    {

        a[i] = rand() % 100;
        printf("%d | ",a[i]);
    }

    clock_t t;
    t = clock();
    mergesort(a, 0, num-1);
    t = clock() - t;

    printf("\n\nVetor ordenado:\n");

    #pragma omp parallel
    for(i=0; i<num; i++)
        printf("%d | ",a[i]);
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    int ID = omp_get_thread_num();
    printf("( main ) numero da Thread: %d \n", ID);

    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}

void mergesort(int a[],int i,int j)
{
    int mid;

    #pragma omp parallel
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,i,mid);        //left recursion
        mergesort(a,mid+1,j);    //right recursion
        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}

void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;

    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }

    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];

    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];

    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0; i<=j2; i++,j++)
        a[i]=temp[j];
}
