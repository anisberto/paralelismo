#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main()
{
    int *a, num, i;
    clock_t t;

    printf("Defina o tamanho do vetor: ");
    scanf("%d",&num);

    srand(time(NULL));

    a = (int *)malloc(sizeof(int) * num);
    printf("\n\nVetor nao-ordenado:\n");
    for(i=0; i<num; i++)
    {
        a[i] = rand() % 100;
        printf("%d | ",a[i]);
    }


    printf("\n\nTempos Gastos:\n");
    t = clock();
    mergesort(a, 0, num-1);
    t = clock() - t;
    double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000); // in seconds
    printf("%d elements => %f\n", i,time_taken );

    printf("\n\nVetor ordenado:\n");
    for(i=0; i<num; i++)
    {
        printf("%d | ",a[i]);
    }
    return 0;
}

void mergesort(int a[],int i,int j)
{

    int mid;


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
