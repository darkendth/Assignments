#include <stdio.h>
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

void main()
{
    Transaction t;
    FILE *fp;
    fp = fopen("testinput.txt","wb");
    if(fp == NULL)
    {
        printf("File not found!\n");
        exit(1);
    }
    int tc;
    scanf("%d",&tc);
    while(tc>0)
    {
        scanf("%d%d",&t.id,&t.amount);
        scanf("%s",t.name);
        scanf("%d",&t.category);
        // printf("%d %d %s %d\n",t.id,t.amount,t.name,t.category);
        fwrite(&t,sizeof(t),1,fp);
        tc--;
    }
    fclose(fp);
    
    fp = fopen("testinput.txt","rb");
    if(fp == NULL)
    {
        printf("File not found!\n");
        exit(1);
    }

    printf("content of file\n");
    while(fread(&t,sizeof(t),1,fp)==1)
    {
        printf("%d %d %s %d\n",t.id,t.amount,t.name,t.category);
    }
    fclose(fp);
}