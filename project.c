#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int A[],int ar_size);
void selection_sort(int A[],int ar_size);
void insertion_sort(int A[],int ar_size);
void merge_sort(int A[],int i,int j);
void merge(int A[],int i,int p,int j,int q);
void quick_sort(int A[],int i,int j);
int partition(int A[],int p,int q);

void swap(int *p1,int *p2){
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void display(int A[], int ar_size){
    for(int i = 0; i<ar_size; i++){
        printf("%d\t",A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    
    int ar_size;
    if(argc == 1)
    {
        printf("Enter array size as command line argument. ");
        return 0;
    }
    
    sscanf(argv[1], "%d", &ar_size);
    int B[ar_size],A[ar_size];
    int CASE;
    clock_t start_time, end_time;
    double funcn_time;

    revaluate:
        printf("1.Random Array \n2.Sorted Array \n3.Reverse Sorted Array \n4.Almost Sorted Array\n");
        printf("Enter the case(1,2,3,4) : ");
        scanf("%d", &CASE);
        switch (CASE)
        {
        case 1:
            /* Random Array */
            for(int i=0; i<ar_size; i++)
            {
                B[i] = rand()%100;
            }
            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            printf("\nSize of Array \t: %d \n",ar_size);
            start_time = clock();
            bubble_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Bubble Sort\t  : %f\n",funcn_time);
            // display(A,ar_size);
            
            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            // display(A,ar_size);
            start_time = clock();
            selection_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Selection Sort\t  : %f\n",funcn_time);
            // display(A,ar_size);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            // display(A,ar_size);
            start_time = clock();
            insertion_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Insertion Sort\t : %f\n",funcn_time);
            // display(A,ar_size);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            // display(A,ar_size);
            start_time = clock();
            merge_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Merge Sort\t : %f\n",funcn_time);
            // display(A,ar_size);


            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            // display(A,ar_size);
            start_time = clock();
            quick_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Quick Sort\t : %f\n",funcn_time);
            // display(A,ar_size);
            
            // display(A,ar_size);
            break;
        
        case 2:
            /* Sorted Array */
            for(int i=0; i<ar_size; i++)
            {
                B[i] = rand()%100;
            }
            quick_sort(B,0,ar_size-1);
            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];  // copy array B to A
            }
            printf("\nSize of Array \t: %d \n",ar_size);

            start_time = clock();
            bubble_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Bubble Sort\t\t  : %f\n",funcn_time);

            start_time = clock();
            selection_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Selection Sort\t\t  : %f\n",funcn_time);

            start_time = clock();
            insertion_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Insertion Sort\t\t  : %f\n",funcn_time);

            start_time = clock();
            merge_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Merge Sort\t\t  : %f\n",funcn_time);

            start_time = clock();
            quick_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Quick Sort\t\t  : %f\n",funcn_time);

            break;

        case 3:
            /* Reverse Sorted Array */
            for(int i=0; i<ar_size; i++)
            {
                B[i] = rand()%100;
            }
            quick_sort(B,0,ar_size-1);
            printf("\nSize of Array \t: %d \n",ar_size);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[ar_size-i-1];  // copy array B to A
            }
            start_time = clock();
            bubble_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Bubble Sort\t\t  : %f\n",funcn_time);
            

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[ar_size-i-1];  // copy array B to A
            }
            start_time = clock();
            selection_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Selection Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[ar_size-i-1];  // copy array B to A
            }
            start_time = clock();
            insertion_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Insertion Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[ar_size-i-1];  // copy array B to A
            }
            start_time = clock();
            merge_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Merge Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[ar_size-i-1];  // copy array B to A
            }
            start_time = clock();
            quick_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Quick Sort\t\t  : %f\n",funcn_time);
            break;
        
        case 4:
            /* Almost Sorted Array */
            for(int i=0; i<ar_size; i++)
            {
                B[i] = rand()%100;
            }
            quick_sort(B,0,ar_size-1);
            for(int i=0; i<(ar_size*0.2); i++)
            {
                swap((B+(rand()%ar_size)),(B+(rand()%ar_size)));
            }
            printf("\nSize of Array \t: %d \n",ar_size);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];
            } 
            start_time = clock();
            bubble_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Bubble Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];
            } 
            start_time = clock();
            selection_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Selection Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];
            } 
            start_time = clock();
            insertion_sort(A,ar_size);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Insertion Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];
            } 
            start_time = clock();
            merge_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Merge Sort\t\t  : %f\n",funcn_time);

            for(int i=0; i<ar_size; i++)
            {
                A[i] = B[i];
            } 
            start_time = clock();
            quick_sort(A,0,ar_size-1);
            end_time = clock();
            funcn_time = ((double)(end_time - start_time ) )/ CLOCKS_PER_SEC;
            printf("Quick Sort\t\t  : %f\n",funcn_time);

            break;

        default:
            printf("Invalid Entry\n");
            goto revaluate;
        }
        
    return 0;
}

void bubble_sort(int A[], int ar_size)
{
    int temp, flag;
    for(int i = 0; i<ar_size; i++)
    {
        flag = 0;
        for(int j = 0; j < (ar_size-i-1); j++)
        {   
            if(A[j] > A[j+1])
            {
                
                swap((A+j) ,(A+j+1));
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
}

void selection_sort(int A[],int ar_size)
{
    int min;
    for(int i=0; i<ar_size; i++)
    {
        min = i;
        for(int j=i+1; j<ar_size; j++)
        {
            if(A[min]>A[j])
                min = j;
        }
        swap((A+min),(A+i));
    }
}

void insertion_sort(int A[],int ar_size)
{
    int p,j;
    for(int i=1; i<ar_size; i++)
    {
        p = A[i];
        j = i;
        while(A[j-1]>p && j>=1)
        {
            A[j] = A[j-1];
            j--;
        }
        A[j] = p;
    }
}

void merge(int A[],int i,int p,int j,int q)
{
    int n = q-i+1;
    int B[n];
    int k=0;
    while((i<=p) && (j<=q))
    {
        if(A[i]<=A[j])
        {
            B[k] = A[i];
            i++;
            k++;
        }
        else
        {
            B[k] = A[j];
            j++;
            k++;
        }
    }
    while(i<=p)
    {
        B[k] = A[i];
        i++;
        k++;
    }
    while(j<=q)
    {
        B[k] = A[j];
        j++;
        k++;
    }
    for(k=n-1;k>=0;k--)
    {
        A[q] = B[k];
        q--;
    }
}

void merge_sort(int A[],int i,int j)
{
    int mid;
    if(i<j)
    {
        mid = (i+j)/2;
        merge_sort(A,i,mid);
        merge_sort(A,mid+1,j);
        merge(A,i,mid,mid+1,j);
    }
}

int partition(int A[],int p,int q)
{
    int x,i;
    x = A[q];
    i = p-1;
    for(int j=p;j<q;j++)
    {
        if(A[j]<=x)
        {
            i++;
            swap((A+j),(A+i));
        }
    }
    i++;
    swap((A+i),(A+q));
    return i;
}

void quick_sort(int A[],int i,int j)
{
    if(i<=j)
    {
        int p = partition(A,i,j);
        quick_sort(A,i,p-1);
        quick_sort(A,p+1,j);
    }
}