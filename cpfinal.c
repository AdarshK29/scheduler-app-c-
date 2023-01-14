#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct cls
{
    char sub[20];
    char prof[20];
    char pf[20];
    struct time{
        int date;
        int hour;
        int min;
        }tm;
}cls;

void sort()
{
    cls *c,c1;
    FILE *fp;
    int i,j,td,th,tm;
    fp=fopen("classes.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(cls);
    rewind(fp);
    c= (cls*)calloc(n,sizeof(cls));
    for(i=0;i<n;i++)
    {
        fread(&c[i],sizeof(cls),1,fp);
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(c[i].tm.date>c[j].tm.date)
            {
                c1=c[i];
                c[i]=c[j];
                c[j]=c1;
            }
            else if(c[i].tm.date==c[j].tm.date)
            {
                if(c[i].tm.hour>c[j].tm.hour)
                {
                    c1=c[i];
                    c[i]=c[j];
                    c[j]=c1;
                }
                else if(c[i].tm.hour==c[j].tm.hour)
                {
                    if(c[i].tm.min>c[j].tm.min)
                    {
                        c1=c[i];
                        c[i]=c[j];
                        c[j]=c1;
                    }
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%s CLASS BY %s SIR ON %d AT %d : %0.2d\n",c[i].sub,c[i].prof,c[i].tm.date,c[i].tm.hour,c[i].tm.min);
    }
    fclose(fp);
}

void search()
{
    cls c1;
    FILE *fp;
    int found=0;
    int searchdate;
    printf("SEARCH BY DATE: ");
    scanf("%d",&searchdate);
    printf("\n");
    fp=fopen("classes.txt","r");
    while(fread(&c1,sizeof(cls),1,fp))
    {

        if(c1.tm.date == searchdate)
        {
            found=1;
            printf("YOU HAVE %s CLASS BY %s SIR ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.tm.date,c1.tm.hour,c1.tm.min);
        }
    }
    if(found==0){
    printf("\nRECORD NOT FOUND\n ");
    }

    fclose(fp);
}

void add()
{
    cls *c;
    FILE *fp;
    printf("ENTER THE NUMBER OF ENTRIES: ");
    int n;
    scanf("%i",&n);
    c=(cls*)calloc(n,sizeof(struct cls));
    fp=fopen("classes.txt","w");

    for(int i=0;i<n;i++)
    {
        printf("ENTRIES FOR CLASS %d :\n",i+1);
        fflush(stdin);
        printf("ENTER THE SUBJECT NAME: ");
        scanf("%[^\n]s",&c[i].sub);
        printf("ENTER THE PLATFORM: ");
        scanf("%s",&c[i].pf);
        printf("ENTER THE PROFESSOR: ");
        scanf("%s",&c[i].prof);
        printf("ENTER THE DATE: ");
        scanf("%d",&c[i].tm.date);
        printf("ENTER THE HOURS IN 24-HR FORMAT: ");
        scanf("%d",&c[i].tm.hour);
        printf("ENTER THE MINUTES: ");
        scanf("%d",&c[i].tm.min);
        fwrite(&c[i],sizeof(struct cls),1,fp);
    }
    fclose(fp);
}

void display_rem()
{

    time_t t;
    time( &t );
    struct tm* t2 = localtime( &t );
    int da=t2->tm_mday,hr=t2->tm_hour,mn=t2->tm_min;

    cls c1;
    FILE *fp;
    fp=fopen("classes.txt","r");
    int found=0;
    while(fread(&c1,sizeof(struct cls),1,fp))
        {
            if(c1.tm.date>da){
                     found=1;
            printf("YOU HAVE %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
            }
            else if(c1.tm.date==da)
            {
                if(c1.tm.hour>hr)
                {
                     found=1;
                printf("YOU HAVE %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
                }
                else if(c1.tm.hour==hr)
                {
                    if(c1.tm.min>mn)
                    {
                         found=1;
                    printf("YOU HAVE %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
                    }
                  }
              }
          }

    if(!found){
        printf("\nYOU HAVE NO REMAINING CLASSES\n");
    }

    fclose(fp);
}

void display_mis()
{
    time_t t;
    time( &t );
    struct tm* t2 = localtime( &t );
    int da=t2->tm_mday,hr=t2->tm_hour,mn=t2->tm_min;

    cls c1;
    FILE *fp;
    fp=fopen("classes.txt","r");

    int found=0;
    while(fread(&c1,sizeof(struct cls),1,fp))
        {
            if(c1.tm.date<da){
            found=1;
            printf("YOU HAVE MISSED %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
            }
            else if(c1.tm.date==da)
            {
                if(c1.tm.hour<hr)
                {
                found=1;
                printf("YOU HAVE MISSED %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
                }
                  else if(c1.tm.hour==hr)
                  {
                      if(c1.tm.min<mn)
                      {
                        found=1;
                        printf("YOU HAVE MISSED %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
                      }
                      else if(c1.tm.min=mn)
                      {
                            found=1;
                            printf("YOU HAVE MISSED %s CLASS BY %s SIR, ON %s ON %d AT %d : %0.2d\n",c1.sub,c1.prof,c1.pf,c1.tm.date,c1.tm.hour,c1.tm.min);
                      }
                  }
              }
          }
          if(!found){
            printf("\nHURRAY YOU HAVE NO MISSED CLASSES\n");
          }
    fclose(fp);

}

void append()
{
    cls *c;
    FILE *fp;
    printf("ENTER THE NUMBER OF ENTRIES: ");
    int n;
    scanf("%i",&n);
    c=(cls*)calloc(n,sizeof(struct cls));
    fp=fopen("classes.txt","a");
    for(int i=0;i<n;i++)
    {
        printf("ENTRIES FOR %d CLASS:\n",i+1);
        fflush(stdin);
        printf("ENTER THE SUBJECT NAME: ");
        scanf("%[^\n]s",&c[i].sub);
        printf("ENTER THE PLATFORM: ");
        scanf("%s",&c[i].pf);
        printf("ENTER THE PROFESSOR: ");
        scanf("%s",&c[i].prof);
        printf("ENTER THE DATE: ");
        scanf("%d",&c[i].tm.date);
        printf("ENTER THE HOURS: ");
        scanf("%d",&c[i].tm.hour);
        printf("ENTER THE MINUTES: ");
        scanf("%d",&c[i].tm.min);
        fwrite(&c[i],sizeof(struct cls),1,fp);
    }
    fclose(fp);
}


int main()
{

    time_t t;
    time(&t);
    printf("======================================\n");
    printf("CURRENT DATE AND TIME IS: %s", ctime(&t));
    printf("======================================\n");

    int n;
    do{
    printf("\n=====WELCOME TO MONTHLY SCHEDULER=====");
    printf("\n1.CREATE A NEW SCHEDULE");
    printf("\n2.DISPLAY REMAINING CLASSES");
    printf("\n3.DISPLAY MISSED CLASSES");
    printf("\n4.APPEND");
    printf("\n5.SORT");
    printf("\n6.SEARCH");
    printf("\n0.ENTER 0 TO EXIT");
    printf("\n======================================\n");
    printf("\nENTER AN OPTION: ");

    scanf("%i",&n);
    switch (n)
    {
    case 1:
        add();
        break;
    case 2:
        display_rem();
        break;
    case 3:
        display_mis();
        break;
    case 4:
        append();
        break;
    case 5:
        sort();
        break;
    case 6:
        search();
        break;
    }

    }while(n!=0);
    return 0;

}
