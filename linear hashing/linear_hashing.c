#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Transaction
{
    /* data */
    int id;
    int amount;
    char name[3];
    int category;
};
typedef struct Transaction Transaction;

struct Meta_data 
{
    char name[20];
    int num_of_record; //Total number of record present in a bucket;
    int num_overflow;  //number of overflow bucket linket to main bucket;
    char last_of_bucket[20]; //Name of last overflow bucket;
};
typedef struct Meta_data Bucket_meta_data;


int split_pointer=0,k=1;                
int B,over_flow=0;                      //# of records in a bucket
int v; //visualization variable.

char* get_bucket_name(int);                         //return the name of bucket.
char *get_name_of_overflow_bucket(int,char*);       //return the name of overflow bucket.
int record_in_bucket(char* );                       //return the number of records in a bucket.
void store_record(Transaction,char*);               //store record in file.
char* get_overflow_bucket(Transaction,char*);       //return the overflowed bucket to store data.
void rehash(Transaction,char *);                    //rehashing the record.
void copy_file(char *,char *);                      //copied content of file1 to file2
void split_bucket();                                //split the bucket when overflow is set to 1;
void content_of_file(char*);                        //display the content of file.
void display_record_in_every_bucket();               //gives status of every bucket.
int search_in_bucket(char *,int);
void search_record(int);

int main(){
    Transaction t;
    FILE *fp = fopen("testinput.txt","rb");
    if(fp == NULL)
    {
        printf("Data file not found!");
        exit(1);
    }
    int p,sr;                  //destine bucket for a record           
    char *bucket_name;
    printf("Enter the value for number of record in bucket : ");
    scanf("%d",&B);
    printf("Enter '1' to go for visualization of what's happening in linear hashing. :(for small data set)\n");
    printf("Enter '2' to go for without visualization (for large data set) : ");
    scanf("%d",&v);

    while(fread(&t,sizeof(t),1,fp)==1)
    {
        p = t.id%((int)pow(2,k));   //compute hash value
        if(p<split_pointer)
        {
            p = t.id%((int)pow(2,(k+1)));
        }
        if(v==1)
        {
            printf("\nsplit bucket pointer : %d\t",split_pointer);
            printf("mod value : %d\n",((int )pow(2,k)));
        }
        printf("record to be stored %d\n",t.id);
        bucket_name = get_bucket_name(p);
        if(record_in_bucket(bucket_name)>=B)
        {
            bucket_name = get_overflow_bucket(t,bucket_name);
            store_record(t,bucket_name);
            if(over_flow==1)
            {
                split_bucket();
                over_flow = 0;
            }
        }
        else
        {
            store_record(t,bucket_name);
        }
        free(bucket_name);
    }
    fclose(fp);
    display_record_in_every_bucket();

    do
    {
        printf("\nEnter the record id to search : ");
        scanf("%d",&sr);
        search_record(sr);
        printf("To continue searching press '1' otherwise press '0' : ");
        scanf("%d",&sr);
    } while (sr==1);
    

    return 0;
}

char* get_bucket_name(int p)
{
    char *bk;
    bk = (char *)malloc(sizeof(char)*20);
    sprintf(bk,"%d",p);
    strcat(bk,".txt");
    return bk;
}

char *get_name_of_overflow_bucket(int p,char* ck)
{
    char *bk = (char *)malloc(sizeof(char)*20);
    sprintf(bk,"%d",p);
    strcat(bk,"_OV_");
    strcat(bk,ck);
    return bk;
}

int record_in_bucket(char* bucket_name)
{
    FILE *bucket;
    Bucket_meta_data md;
    bucket = fopen(bucket_name,"rb");
    if(bucket==NULL)
        return 0;
    
    fread(&md,sizeof(md),1,bucket);
    fclose(bucket);
    return md.num_of_record;
}

void store_record(Transaction t,char* bucket_name)
{
    FILE *bucket;
    Bucket_meta_data md;
    bucket = fopen(bucket_name,"rb+");
    if(bucket == NULL)
    {
        //first time create bucket store meta data and data in a bucket.
        bucket = fopen(bucket_name,"wb+");
        if(bucket==NULL)
        {
            printf("unable to create bucket\n");
            exit(2);
        }
        strcpy(md.name,bucket_name);
        md.num_of_record = 1;
        md.num_overflow = 0;
        fwrite(&md,sizeof(md),1,bucket);
        fwrite(&t,sizeof(t),1,bucket);    
    }
    else
    {   
        //store record and update meta data(number of record in a bucket field).
        fread(&md,sizeof(md),1,bucket);
        md.num_of_record += 1;
        fseek(bucket,-sizeof(md),SEEK_CUR);
        fwrite(&md,sizeof(md),1,bucket);
        fseek(bucket,0,SEEK_END);
        fwrite(&t,sizeof(t),1,bucket);
    }
    fclose(bucket);
    if(v==1)
    {
        printf("content of bucket after insert : \n");
        content_of_file(bucket_name);
    }
}

char* get_overflow_bucket(Transaction t,char *bucket_name)
{
    char *overflow_bucket=(char *)malloc(sizeof(char)*20);
    FILE *bucket,*of_bucket;
    Bucket_meta_data md1,md2;
    bucket = fopen(bucket_name,"rb+");
    if(bucket == NULL)
    {
        printf("file not found\n");
        exit(3);
    }
    fread(&md1,sizeof(md1),1,bucket);
    if(md1.num_overflow==0)
    {
        //for first overflow case.
        md1.num_overflow = 1;
        sprintf(overflow_bucket,"%d",md1.num_overflow);
        strcat(overflow_bucket,"_OV_");
        strcat(overflow_bucket,bucket_name);
        strcpy(md1.last_of_bucket,overflow_bucket);
        fseek(bucket,-sizeof(md1),SEEK_CUR);
        fwrite(&md1,sizeof(md1),1,bucket);
        fclose(bucket);
        over_flow = 1;
    }
    else
    {
        //find previously overflow bucket and return it.
        of_bucket = fopen(md1.last_of_bucket,"rb");
        if(of_bucket == NULL)
        {
            printf("overflow bucket not found\n");
            exit(4);
        }
        fread(&md2,sizeof(md2),1,of_bucket);
        if(md2.num_of_record==B)
        {
            //if previously overflow bucket is full then create new overflow bucket.
            md1.num_overflow += 1;
            sprintf(overflow_bucket,"%d",md1.num_overflow);
            strcat(overflow_bucket,"_OV_");
            strcat(overflow_bucket,bucket_name);
            strcpy(md1.last_of_bucket,overflow_bucket);
            fseek(bucket,-sizeof(md1),SEEK_CUR);
            fwrite(&md1,sizeof(md1),1,bucket);
            over_flow = 1;
        }
        else
        {
            strcpy(overflow_bucket,md1.last_of_bucket);
        }
        fclose(of_bucket);
        fclose(bucket);
    }
    free(bucket_name);
    if(v==1)
        printf("overflow bucket name : %s\n",overflow_bucket);
    return overflow_bucket;
}

void rehash(Transaction t,char *bucket_name)
{
    if(record_in_bucket(bucket_name)>=B){
        bucket_name = get_overflow_bucket(t,bucket_name);
        store_record(t,bucket_name);
        over_flow = 0;
    }
    else
    {
        store_record(t,bucket_name);
    }
}

void copy_file(char *bucket1,char *bucket2)
{
    FILE *bk1,*bk2;
    Bucket_meta_data md;
    Transaction t;
    bk1 = fopen(bucket1,"rb");
    if(bk1==NULL)
    {
        printf("file content can't copy\n");
        exit(6);
    }
    bk2 = fopen(bucket2,"wb");
    if(bk2==NULL)
    {
        printf("file content can't copy\n");
        exit(6);
    }
    fread(&md,sizeof(md),1,bk1);
    fwrite(&md,sizeof(md),1,bk2);
    while (fread(&t,sizeof(t),1,bk1)==1)
    {
        fwrite(&t,sizeof(t),1,bk2);
    }
    fclose(bk1);
    fclose(bk2);
    if(v==1)
    {
        printf("list of record to rehash : \n");
        content_of_file(bucket2);
    }

    // remove the bucket (ex : 1.txt ) for storing rehashing record.
    if(remove(bucket1)==0)
    {
        // printf("file deleted successfully\n");
    }
    else
    {
        printf("unable to delete a file.\n");
        exit(7);
    }
}

void split_bucket()
{
    char *split_bucket_name = get_bucket_name(split_pointer);
    char *temp_bucket = "temp.txt";
    char *bucket_name;
    FILE *split_bucket;
    Bucket_meta_data md; 
    Transaction t;
    int p;
    if(v==1)
    {
        printf("splitting bucket %s\n",split_bucket_name);
    }

    copy_file(split_bucket_name,temp_bucket);
    split_bucket = fopen(temp_bucket,"rb");
    if(split_bucket == NULL)
    {
        printf("Bucket needed to split does not exist\n");
        exit(5);
    }
    fread(&md,sizeof(md),1,split_bucket);
    while(fread(&t,sizeof(t),1,split_bucket)==1)
    {   
        //rehash content of main bucket.
        p = t.id%((int)pow(2,(k+1)));
        bucket_name = get_bucket_name(p);
        rehash(t,bucket_name);
        free(bucket_name);
    }
    fclose(split_bucket);
    if(v==1)
        printf("1 split complete \n");
    for(int i=1;i<=md.num_overflow;i++)
    {
        //rehash content of overflow bucket linked to main bucket.
        bucket_name = get_name_of_overflow_bucket(i,split_bucket_name);
        copy_file(bucket_name,temp_bucket);
        free(bucket_name);
        split_bucket = fopen(temp_bucket,"rb");
        if(split_bucket==NULL)
            exit(8);
        fseek(split_bucket,sizeof(md),SEEK_CUR);
        while(fread(&t,sizeof(t),1,split_bucket)==1)
        {   
            p = t.id%((int) pow(2,(k+1)));
            bucket_name = get_bucket_name(p);
            rehash(t,bucket_name);
            free(bucket_name);
        }
        fclose(split_bucket);
        if(v==1)
            printf("%d split complete\n",(i+1));
    }
    free(split_bucket_name);
    split_pointer++;
    if(split_pointer==((int) pow(2,k)))
    {
        k = k+1;
        split_pointer = 0;
    }
}


void content_of_file(char *bucket_name)
{
    FILE *bucket;
    Transaction t;
    Bucket_meta_data md;
    bucket = fopen(bucket_name,"rb");
    if(bucket == NULL)
    {
        printf("Bucket is empty\n");
    }
    else
    {
        fread(&md,sizeof(md),1,bucket);
        printf("Meta data :\n Name : %s, number of record : %d, overflow bucket : %d, last overflow bucket : %s\n",md.name,md.num_of_record,md.num_overflow,md.last_of_bucket);
        while(fread(&t,sizeof(t),1,bucket)==1)
        {
            printf("id = %d, name = %s, amount = %d, category = %d\n",t.id,t.name,t.amount,t.category);
        }
        printf("\n");
        fclose(bucket);
    }
}

void display_record_in_every_bucket()
{
    int l = pow(2,k);
    char *bucket_name,*overflow_bucket;
    FILE *bucket;
    Bucket_meta_data md;
    printf("mod value : %d\n",l);
    for(int i=0;i<((int )pow(2,(k+1)));i++)
    {
        bucket_name = get_bucket_name(i);
        printf("\nContent of file %s\n",bucket_name);
        content_of_file(bucket_name);
        bucket = fopen(bucket_name,"rb");
        if(bucket != NULL)
        {
        fread(&md,sizeof(md),1,bucket);
        fclose(bucket);
        for(int j=1;j<=md.num_overflow;j++)
        {
            overflow_bucket = get_name_of_overflow_bucket(j,bucket_name);
            printf("\nContent of file %s\n",overflow_bucket);
            content_of_file(overflow_bucket);
            free(overflow_bucket);
        }
        }
        free(bucket_name);
    }
}

int search_in_bucket(char *bucket_name,int sr)
{
    Bucket_meta_data md;
    Transaction t;
    char *overflow_bucket;
    FILE *bucket;
    bucket = fopen(bucket_name,"rb");
    fread(&md,sizeof(md),1,bucket);
    while(fread(&t,sizeof(t),1,bucket)==1)
    {
        if(t.id==sr)
        {
            fclose(bucket);
            printf("id = %d, name = %s, amount = %d, category = %d\n",t.id,t.name,t.amount,t.category);
            return 1;
        }
    }
    fclose(bucket);
    for(int i=1;i<=md.num_overflow;i++)
    {   
        overflow_bucket = get_name_of_overflow_bucket(i,bucket_name);
        bucket = fopen(overflow_bucket,"rb");
        fseek(bucket,sizeof(md),SEEK_CUR);
        while(fread(&t,sizeof(t),1,bucket)==1)
        {   
            if(t.id==sr)
            {
                fclose(bucket);
                free(overflow_bucket);
                printf("id = %d, name = %s, amount = %d, category = %d\n",t.id,t.name,t.amount,t.category);
                return 1;
            }
        }
        free(overflow_bucket);
        fclose(bucket);
    }
    return 0;
}


void search_record(int sr)
{
    int p ;
    char *bucket_name;
    if(split_pointer == 0)
    {
        p = sr%((int)pow(2,k));
        bucket_name = get_bucket_name(p);
        p = search_in_bucket(bucket_name,sr);
        if(p==0)
            printf("record not found!\n");
        free(bucket_name);
    }
    else
    {
        p = sr%((int)pow(2,k));
        if(p<split_pointer)
        {
            p = sr%((int)pow(2,(k+1)));
            bucket_name = get_bucket_name(p);
            p = search_in_bucket(bucket_name,sr);
            if(p==0)
                printf("Record does not exist!\n");
            free(bucket_name);
        }
        else
        {
            bucket_name = get_bucket_name(p);
            p = search_in_bucket(bucket_name,sr);
            if(p==0)
                printf("Record does not exist!\n");
            free(bucket_name);
        }
    }
}