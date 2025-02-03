#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char month[50];
    char year[50];
} Pdate;
typedef struct
{
    char ISBN[14];
    char Title[100];
    char Author_name[100];
    int quantity;
    float price;
    Pdate Pubdate;
} Books;
Books B[100];
int i=0;
char Mnth[12][50]= {"January","february","March","April","May","June","July","August","September","October","November","December"};
void welcome()
{
    printf("\t\t\t\t\t\t ________________________\n");
    printf("\t\t\t\t\t\t|                        |\n");
    printf("\t\t\t\t\t\t| WELCOME TO OUR PROGRAM |\n");
    printf("\t\t\t\t\t\t|________________________|\n");

}
void printline()
{
    printf("\n_________________________________________________________\n");
}
void ReadFile()
{
    FILE *f=fopen("books.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%[^,],%d,%f,%[^-]-%[^\n]\n",B[i].ISBN,B[i].Title,B[i].Author_name,&B[i].quantity,&B[i].price,B[i].Pubdate.month,B[i].Pubdate.year);
        i++;
    }

    fclose(f);
}
void Save()
{
    int j;
    FILE *f=fopen("books.txt","w");
    for(j=0; j<i; j++)
    {
        if(j==i-1)
            fprintf(f,"%s,%s,%s,%d,%.2f,%s-%s",B[j].ISBN,B[j].Title,B[j].Author_name,B[j].quantity,B[j].price,B[j].Pubdate.month,B[j].Pubdate.year);
        else
            fprintf(f,"%s,%s,%s,%d,%.2f,%s-%s\n",B[j].ISBN,B[j].Title,B[j].Author_name,B[j].quantity,B[j].price,B[j].Pubdate.month,B[j].Pubdate.year);

    }
    fclose(f);
    printline();
    printf("\nCHANGES SAVED SUCCESSFULLY!!");
    Menu();
}
void printfile(int j)
{
    {
        printf("\nISBN: %s\nTitle: %s\nAuthor: %s\nQuantity: %d\nPrice: %.2f\nPublished: %s %s\n",B[j].ISBN,B[j].Title,B[j].Author_name,B[j].quantity,B[j].price,Mnth[atoi(B[j].Pubdate.month)-1],B[j].Pubdate.year);
    }
}
void printallfile()
{
    int j;
    for(j=0; j<i; j++)
    {
        printf("\nISBN: %s\nTitle: %s\nAuthor: %s\nQuantity: %d\nPrice: %.2f\nPublished: %s %s\n\n",B[j].ISBN,B[j].Title,B[j].Author_name,B[j].quantity,B[j].price,Mnth[atoi(B[j].Pubdate.month)-1],B[j].Pubdate.year);
    }
}
int Check_ISBN(char sISBN[])
{
    int j;
    if(strlen(sISBN)!=13)
    {
        printf("Invalid ISBN!!\n");
        return 0;
    }
    for(j=0; j<13; j++)
        if(!(sISBN[j]>='0'&&sISBN[j]<='9'))
        {
            printf("Invalid ISBN!!\n");
            return 0;
        }
    return 1;

}
int CheckDuplicate(char sISBN[])
{
    int j;
    for(j=0; j<i; j++)
        if(!strcmp(sISBN,B[j].ISBN))
        {
            printf("Duplicate ISBN!!\n");
            return 0;
        }
    return 1;
}
int Check_Month(char CheckMnth[])
{
    int j;
    for(j=0; j<strlen(CheckMnth); j++)

    {
        if(!isdigit(CheckMnth[j]))
        {
            printf("Invalid Month Choice\n");
            return 0;
        }
    }
    int x=atoi(CheckMnth);
    if(x>=1 && x<=12)
        return 1;
    else
    {
        printf("Invalid Month Choice\n");
        return 0;
    }

}
int Check_Year(char CheckYear[])
{
    int j;
    for(j=0; j<strlen(CheckYear); j++)

        if(!isdigit(CheckYear[j]))
        {
            printf("Invalid Year choice\n");
            return 0;
        }
    int x=atoi(CheckYear);
    if(x>=1000&&x<=2022)
        return 1;
    else
    {
        printf("Invalid Year choice\n");
        return 0;
    }
}

void Add()
{
    int flag,j;
    int point_cnt=0;
    char Quantity_str[50],Price_str[50];
    printf("ADD Book (%d):\n",i+1);

    do
    {
        flag=1;
        printf("Enter ISBN:");
        gets(B[i].ISBN);
        if(Check_ISBN(B[i].ISBN)&&CheckDuplicate(B[i].ISBN))
            flag=0;


    }
    while(flag);
    printf("Enter Title:");
    gets(B[i].Title);
    printf("Enter Author:");
    gets(B[i].Author_name);
    do
    {
        flag=0;
        printf("Enter Quantity:");
        gets(Quantity_str);
        for(int j=0; j<strlen(Quantity_str); j++)
        {
            if(!isdigit(Quantity_str[j]))
            {
                flag=1;

            }
        }
        if(flag)
            printf("invalid Quantity\n");
    }
    while(flag);
    B[i].quantity=atoi(Quantity_str);

    do
    {
        flag=0;
        point_cnt=0;

        printf("Enter Price:");
        gets(Price_str);
        for( j=0; j<strlen(Price_str); j++)
        {

            if(!(isdigit(Price_str[j])||Price_str[j]=='.'))
            {
                flag=1;
            }
            if(Price_str[j]=='.')
                point_cnt++;
        }
        if(point_cnt>1)
            flag=1;
        if(flag)
            printf("invalid Price\n");


    }
    while(flag);
    Price_str[j]='\0';
    B[i].price=atof(Price_str);



    do
    {
        printf("Enter month:");
        gets(B[i].Pubdate.month);
    }
    while(!Check_Month(B[i].Pubdate.month));
    do
    {
        printf("Enter Year:");
        gets(B[i].Pubdate.year);
    }
    while(!Check_Year(B[i].Pubdate.year));
    i++;
//printallfile();
   printline();
    printf("\nBOOK ADDED SUCCESSFULLY!!");
    Menu();

}
void Delete()
{
    int j,k;
    int flag=0;
    char sISBN[14];
    printf("Enter Book ISBN: ");
    gets(sISBN);
    if(!Check_ISBN(sISBN))
    {
        Menu();
        return;
    }
    for(j=0; j<i; j++)
    {
        if(strcmp(sISBN,B[j].ISBN)==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
        printf("Book not Found!!\n");

    for(k=j; k<i-1; k++)
        B[k]=B[k+1];
    if(flag)
        i--;
    // printallfile();
    printline();
    printf("\nBOOK DELETED SUCCESSFULLY!!");
    Menu();
}
void Modify()
{
    char sISBN[14];
    int j,k,flag,point_cnt=0;
    char choice[100],change[100],Quantity_str[50],Price_str[50];

    do
    {
        printf("Enter ISBN:");
        gets(sISBN);
    }
    while(!Check_ISBN(sISBN));
    for(j=0; j<i; j++)
    {
        if(strcmp(sISBN,B[j].ISBN)==0)
            break;
    }
    if(j==i)
    {
        printf("Book not found!!!\n");
        Menu();
        return;
    }
    printf("\nWhat do you want to modify: \n");
    printf("1.ISBN\n2.Title\n3.Author Name\n4.Quantity\n5.Price\n6.Month\n7.Year\n");
    printf("Enter choice:");
    gets(choice);

    if(!strcmp("1",choice))
    {
        do
        {
            flag=1;
            printf("Enter ISBN:");
            gets(change);
            if(Check_ISBN(change)&&CheckDuplicate(change))
                flag=0;


        }
        while(flag);
        strcpy(B[j].ISBN,change);

    }
    else if(!strcmp("2",choice))
    {
        printf("Enter Title:");
        gets(B[j].Title);

    }

    else if(!strcmp("3",choice))
    {
        printf("Enter Author Name:");
        gets(B[j].Author_name);

    }
    else if(!strcmp("4",choice))
    {

        do
        {
            flag=0;
            printf("Enter Quantity:");
            gets(Quantity_str);
            for(int k=0; k<strlen(Quantity_str); k++)
            {
                if(!isdigit(Quantity_str[k]))
                {
                    flag=1;

                }
            }
            if(flag)
                printf("invalid Quantity\n");
        }
        while(flag);
        B[j].quantity=atoi(Quantity_str);
    }
    else if(!strcmp("5",choice))
    {
        do
        {
            flag=0;
            point_cnt=0;

            printf("Enter Price:");
            gets(Price_str);
            for( k=0; k<strlen(Price_str); k++)
            {

                if(!(isdigit(Price_str[k])||Price_str[k]=='.'))
                {
                    flag=1;
                }
                if(Price_str[k]=='.')
                    point_cnt++;
            }
            if(point_cnt>1)
                flag=1;
            if(flag)
                printf("invalid Price\n");


        }
        while(flag);
        Price_str[k]='\0';
        B[j].price=atof(Price_str);
    }
    else if(!strcmp("6",choice))
    {

        do
        {
            printf("Enter Month:");
            gets(change);
        }
        while(!Check_Month(change));
        strcpy(B[j].Pubdate.month,change);

    }
    else if(!strcmp("7",choice))
    {
        do
        {
            printf("Enter Year:");
            gets(change);
        }
        while(!Check_Year(change));
        strcpy(B[j].Pubdate.year,change);


    }
    else
    {
        printf("Invalid input\n");
        Modify();
    }
    // printallfile();
    printline();
    printf("\nBOOK MODIFIED SUCCESSFULLY!!");
    Menu();

}
void Query()
{
    int j=0;
    int flag=0;
    char sISBN[14];
    printf("(SEARCH)Enter Book ISBN: ");
    gets(sISBN);

    if(!Check_ISBN(sISBN))
    {
        Menu();
        return;
    }

    for(j=0; j<i; j++)

        if(!strcmp(sISBN,B[j].ISBN))
        {
            printfile(j);
            flag=1;
            break;
        }

    if (!flag)
    {
        printf("Book Not Found!!\n");
    }
    Menu();
}
void AdvancedSearch()
{
    int j,flag=0;
    char *p;
    char Asearch[50];
    printf("Enter Category Book Search: ");
    gets(Asearch);
    //printf("%s",Asearch);
    for(j=0; j<i; j++)
    {
        p=strstr(B[j].Title,Asearch);
        if(p!=NULL)
        {
            flag=1;
            printfile(j);
        }

    }
    if(flag==0)
        printline();
        printf("Category not found!!\n");
    Menu();

}
void SortbyTitle()
{
    int j,k;
    Books temp;
    for(j=0; j<i-1; j++)
    {
        for(k=j+1; k<i; k++)
            if(strcasecmp(B[j].Title,B[k].Title)>0)
            {
                temp=B[j];
                B[j]=B[k];
                B[k]=temp;
            }
    }
    printallfile();
}
void SortByPrice()
{
    int j,k;
    Books temp;
    for(j=0; j<i; j++)
    {
        for(k=j+1; k<i; k++)
        {
            if(B[j].price>B[k].price)
            {
                temp=B[k];
                B[k]=B[j];
                B[j]=temp;
            }
        }
    }
    printallfile();
}
void  SortByDate()
{
    int j,k;
    Books temp;

    for(j=0; j<i; j++)
    {
        for(k=j+1; k<i; k++)
        {
            if(strcmp(B[j].Pubdate.year,B[k].Pubdate.year)<0)
            {
                temp=B[k];
                B[k]=B[j];
                B[j]=temp;
            }
            else if(!strcmp(B[j].Pubdate.year,B[k].Pubdate.year))
                if(strcmp(B[j].Pubdate.month,B[k].Pubdate.month)<0)/*atoi(B[j].Pubdate.month)<atoi(B[k].Pubdate.month)*/
                {
                    temp=B[k];
                    B[k]=B[j];
                    B[j]=temp;
                }
        }
    }
    printallfile();
}
void Print()
{
    char choice[50];
    printf("\nSort by?\n");
    printf("1.Title\n2.Price\n3.Date\n");
    printf("Enter choice: ");
    gets(choice);
    if(!strcmp(choice,"1"))
    {   printline();
        SortbyTitle();
        Menu();
    }
    else if(!strcmp(choice,"2"))
    {printline();
        SortByPrice();
        Menu();
    }
    else if(!strcmp(choice,"3"))
    {printline();
        SortByDate();
        Menu();
    }
    else
    {printline();
        printf("Invalid choice\n");
        Print();
    }

}
void Menu()
{
    int x[100],flag;
    printline();
    printf("\nHow can we assist you?\n");
    printf("1.Add\n2.Delete\n3.Modify\n4.Query Search\n5.Advanced Search\n6.Print\n7.Save\n8.Quit\n");
    printf("Enter your choice: ");
    gets(x);

    if(!strcmp("1",x))
    {
        printline();
        Add();
    }
    else if(!strcmp("2",x))
    {
        printline();
        Delete();
    }

    else if(!strcmp("3",x))
    {
        printline();
        Modify();
    }
    else if(!strcmp("4",x))
    {
        printline();
        Query();
    }
    else if(!strcmp("5",x))
    {
        printline();
        AdvancedSearch();
    }
    else if(!strcmp("6",x))
    {
        printline();
        Print();
    }
    else if(!strcmp("7",x))
    {
        Save();
    }
    else if(!strcmp("8",x))
    {
        printline();
        printf("Quit without saving? ~WARNING!!ALL CHANGES WILL BE DISCARDED~\n");
        printf("1.Save\n2.Return to menu\n3.Quit\n");
        do
        {
            flag=0;
            printf("Enter your choice: ");
            gets(x);
            if(!strcmp("1",x))
            {
                Save();
                printf("\nGOODBYE!!!!!");
                exit(0);
            }
            else if(!strcmp("2",x))
                Menu();
            else if(!strcmp("3",x))
            {
                printf("\nGOODBYE!!!!!");
                exit(0);

            }
            else
            {
                printf("Invalid Input\n");
                flag=1;

            }
        }
        while(flag);

    }
    else
    {
        printf("Invalid Input\n");
        Menu();
    }



}

void Login()
{
    int j;
    char creds[2][50],login[2][50];
    FILE *fc=fopen("credentials.txt","r");
    if(fc==NULL)
    {
        printf("File Not Found!!!");
        exit(0);
    }
    while(!feof(fc))
    {
        fscanf(fc,"%[^\n]\n",creds[j]);

        j++;
    }
    fclose(fc);
    do
    {
        printline();
        printf("Enter Username:");
        gets(login[0]);
        printf("Enter password:");
        gets(login[1]);
        if(strcmp(login[0],creds[0])==0&&strcmp(login[1],creds[1])==0)
        {
            Menu();
        }
        else printf("Invalid Username or password!!\n");
    }
    while(strcmp(login[0],creds[0])!=0||strcmp(login[1],creds[1])!=0);
}


void login_Menu()
{
    char x[50];
    welcome();
    printf("1.Login\n2.Exit");
    printf("\nEnter choice: ");
    gets(x);

    if(!strcmp("1",x))
        Login();
    else if(!strcmp("2",x))
    {
        printf("\nGOODBYE!!!!!");
        exit(0);
    }
    else
    {
        printf("Invalid option!!\n");
        login_Menu();
    }

}

int main()
{


    ReadFile();
    login_Menu();


    return 0;

}
