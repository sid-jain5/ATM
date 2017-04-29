#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define INF 32500
#define NO 21
struct job
{
    char id[10];
    int wait,withdraw;
};
typedef struct job job;\

int comparator(const void *p, const void *q)
{
    int l = ((struct job *)p)->withdraw;
    int r = ((struct job *)q)->withdraw;
    return (l - r);
}

int min(int a, int b)
{
    if(a>b)
        return b;
    return a;
}

int check(int sector)
{
    if(sector>=1&&sector<=20)
        return 1;
    return 0;
}
unsigned checkAmount(int amount)
{
    if(amount>=1)
        return 1;
    return 0;
}

unsigned checkUN(char s[])
{
    int i;
    printf("\tUsername you entered is %s\n",s);
    if(strlen(s)!=6)
        return 0;
    else {
        for(i=0;i<=3;i++)
        {
            if(!(s[i]>=65&&s[i]<=90||s[i]>=97&&s[i]<=122))
                return 0;
        }
        if(!(s[4]>=48&&s[4]<=57&&s[5]>=48&&s[5]<=57))
            return 0;
        return 1;

    }
}
int* resultArray(int v,int l)
{
    int *p=(int*)malloc(sizeof(int)*(v+1));
    return p;
}
void lpscalc(char *pat, int M, int *lps)
{
    int len = 0;

    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len-1];

            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
int kmp(char pat[], char txt[])
{
    //printf("strings %s %s\n",pat,txt);
    int M = strlen(pat);
    int N = strlen(txt);
    //printf("calling lps array\n");
    int *lps=(int*)malloc(M*sizeof(int));
    lpscalc(pat, M, lps);
    //printf("lps nuilt\n");
    int i = 0;
    int j  = 0;
    int flag=0;
        while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            flag=1;
            break;
            j = lps[j-1];
        }

        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
void coinchange(int amount)
{
    int l,i,j;
    int curr[]={1,3,5,11,13,23,101,151,193,389,587,677,881,947,997};
    //printf("The currency notes available are of 1,3,5,11,13,23,101,151,193,389,587,677,881,947,997\n");
    l=sizeof(curr)/sizeof(curr[0]);

    int *p=resultArray(amount,l);
    int *r;
    r=resultArray(amount,l);

    for(i=0;i<=amount;i++)
    {
        if(i==0)
            p[i]=0;
        else
            p[i]=INF;

        r[i]=-1;

    }

    for(i=0;i<l;i++)
    {
        for(j=0;j<=amount;j++)
        {
            if(j>=curr[i]&&(p[j-curr[i]]+1)<p[j])
            {
                 p[j]=p[j-curr[i]]+1;
                 r[j]=i;
            }
        }
    }
    printf("\tNumber of notes dispensed are %d\n",p[amount]);
    printf("\tNotes dispensed are of denomination: ");
     i=amount;
     int k=36;
    while(i!=0)
    {
        printf("%c%d ",k,curr[r[i]]);
        i=i-curr[r[i]];
    }
    printf("\n");

}
void jobseq(job *a, int n)
{
    int i,j;
    int* slot=(int*)malloc(n*sizeof(int));
    int* result=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        slot[i]=0;
     }
    for(i=0;i<n;i++)
    {
        for(j=min(n,a[i].wait)-1;j>=0;j--)
        {
            if(slot[j]==0)
            {
                slot[j]=1;
                result[j]=i;
                break;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("\n\tjob done are %s \n",a[result[i]].id);
        coinchange(a[result[i]].withdraw);
    }
}
void checkqueue(job* a, int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        printf("\tUser %d\t%s\n",i+1,a[i].id);
    }
}
int dijsktra(int cost[][NO],int source,int target)
{
    int dist[NO],prev[NO],selected[NO]={0},i,m,min,start,d,j;
    char path[NO];
    for(i=1;i< NO;i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = INF;
        m = 0;
        for(i=1;i< NO;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start+64;
        start = prev[start];
    }
    int k;
    path[j]='\0';
    strrev(path);
    printf("\n\tThe path you will have to follow is \n");
    printf("\t");
    for(k=0;k<j;k++)
    printf(" >>sector:%d", path[k]-64);
    printf("\n");
    return dist[target];
}
void findATM()
{
    int source,target,co;
    char name[7];
    int cost[NO][NO] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,INF,2,1,3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,2,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,1,INF,INF,INF,3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,3,INF,INF,INF,4,2,INF,1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,3,4,INF,INF,6,INF,INF,INF,INF,INF,INF,INF,INF,2,INF,INF,INF,INF},
                {0,INF,INF,INF,2,INF,INF,INF,INF,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,6,INF,INF,5,INF,INF,INF,INF,INF,INF,INF,INF,3,INF,INF,INF},
                {0,INF,INF,INF,1,INF,INF,5,INF,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,5,INF,5,INF,4,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,4,INF,2,INF,3,INF,3,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,2,INF,1,INF,6,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1,INF,INF,INF,INF,1,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,3,INF,INF,INF,INF,INF,INF,INF,5,2,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,6,INF,INF,INF,4,INF,INF,INF,INF,6},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,3,INF,INF,INF,4,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,2,INF,INF,INF,INF,INF,INF,1,INF,INF,INF,INF,INF,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,2,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,5,INF,INF,INF,2,INF,INF,INF},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,2,INF,INF,INF,INF,INF,INF,7},
                {0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,6,INF,INF,INF,INF,7,INF}};
    while(1)
    {
    printf("\n\tEnter the current sector you are in: ");
    scanf("%d", &source);
    if(!check(source))
        continue;
    printf("\tBanks Available are\n\tSBI\n\tPNB\n\tHDFC\n\tAXIS\n");
   printf("\tEnter the bank's ATM you want to visit: ");
    fflush(stdin);
    scanf("%s",name);
    if(strcmp(name, "SBI")==0)
        target=12;
    else if(strcmp(name, "PNB")==0)
        target=8;
    else if(strcmp(name, "HDFC")==0)
        target=3;
    else if(strcmp(name, "AXIS")==0)
        target=14;
    else
    {
        printf("\tThis ATM is not available in Noida City\n");
        continue;
    }
    co = dijsktra(cost,source,target);
    printf("\tMinimun distance is: %d kms\n",co);
    break;
    }
    return;

}
int main()
{
    unsigned sector,userChoice;
    int i,amount,choice,wait,qchoice;
    FILE *fp;
    char userName[10];
    char nameString[100];
    printf("\t\t\t\t\tWelcome to the City of Noida\n");
    printf("\t\t\t\t ****There are total 30 Sectors in Noida****\n");
    fp = fopen("file2.txt", "r+");
    if(fp==NULL)
    printf("not opened");
    fscanf(fp,"%s",nameString);
    fclose(fp);
    job* a=(job*)malloc(5*sizeof(job));
    int count=0;

    //printf("new1 is %s\n",nameString);
    while(1)
    {
        //printf("namestring is %s\n",nameString);
        printf("\tpress 1 for existing User and 2 for new User: ");
        printf("\t");
        scanf("%d",&userChoice);
        if(userChoice!=1&&userChoice!=2)
        {
            printf("\tInvalid User choice, Try again\n");
            continue;
        }
        printf("\n\tEnter your UserID of 6 characters which should contain 4 letter followed by 2 number: ");
        printf("\t");
        fflush(stdin);
        scanf("%s",userName);
        if(!checkUN(userName))
        {
            printf("\a\tInvalid, Try Again\n");
           continue;
        }

        int m=kmp(userName,nameString);
        if(m==0&&userChoice==1)
        {
            printf("\a\tRecord not found, Try Again\n");
            continue;
        }
        else if(m==1&&userChoice==1)
            printf("\tUser Name validated, proceed\n");
        else if(m==1&&userChoice==2)
        {
            printf("\aUserName exists, Try Again\n");
            continue;
        }
        else if(m==0&&userChoice==2)
        {
            strcat(nameString,userName);
            printf("\tUserId created Succesfully\n");
            fp = fopen("file2.txt", "w+");
            if(fp==NULL)
             printf("not opened while concat");
            fprintf(fp,"%s",nameString);
            fclose(fp);

        }


        //printf("\tWelcome to Sector xx ATM\n");
        //printf("you've been entered in the queue");
        if(count<3)
        {
            findATM();
        printf("\tEnter the Amount you want to withdraw: ");
        printf("\t");
        scanf("%d",&amount);
        if(!checkAmount(amount))
            continue;
        printf("\tEnter the time you can wait for: ");
        printf("\t");
        scanf("%d",&wait);


            strcpy(a[count].id,userName);
            a[count].withdraw=amount;
            a[count].wait=wait;
            count++;
            printf("\tyou've been successfully added to the queue\n");
            printf("\tpress 1 to check queue and 0 otherwise: ");
            printf("\t");
            scanf("%d",&qchoice);
            printf("\n");
            if(qchoice==1)
                checkqueue(a,count);
            continue;
        }
        qsort((void*)a,count,sizeof(a[0]),comparator);
        //for(i=0;i<count;i++)
            //printf("\t%s %d %d",a[i].id,a[i].withdraw,a[i].wait);

        jobseq(a,count);



        printf("\tEnter 0 to exit the portal or 1 to find another ATM: ");
        printf("\t");
        scanf("%u",&choice);
        if(choice==0)
           break;
        else if(choice==1)
            count=0;

    }
    return 0;
}
