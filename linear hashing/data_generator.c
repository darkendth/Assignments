#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Transaction
{
    /* data */
    int id;
    int amount;
    char name[3];
    int category;
};
typedef struct Transaction Transaction;

int main(){
    srand(time(NULL));
    Transaction t;
    FILE *fp;
    int n;
    int counter = 1;
    printf("Enter the number of records you want to enter : ");
    scanf("%d",&n);
    fp = fopen("transaction_data.txt","wb");
    if(fp == NULL)
    {
        printf("File not found!\n");
        exit(1);
    }
    while(n>0)
    {
        t.id = counter;
        t.amount = rand()%80000;
        for(int i=0;i<3;i++)
        {
            t.name[i] = 65+rand()%26;
        }
        t.category = rand()%1500;

        //write a record in the file.
        fwrite(&t,sizeof(t),1,fp);
        counter++;
        n--;
    }
    fclose(fp);
    return 0;
}