// Assignment : Register and Login Program (NCC)

#include<stdio.h>
#define SIZE 500
#include<stdlib.h>

struct Worker{

    int id;
    int age;
    char name[30];
    char email[50];
    char password[50];

};

struct Worker info[SIZE];

char text_file[15] = "assignment.txt";

int globalIndex =0;
void printingAllData();
void login();
void loadingAllDataFromFile();
void UserActionSector();
int charCounting(char toCount[50]);
void passwordChecking(char pass[50],int userIndex);
void myStrCmp(char userInputChar[50]);
void Registeration();
void Lobby();

char email_format[11] = "@gmail.com";
char va = '@';
int same_countt = 0;
int not_same_countt =0;
int go_check = -1;
int glob_var1 = 0;
void Check_Count_function_for_Validate();
void validate_email(char email[SIZE],int var2);

int save_data = -1;
int email_fomat_correct = -1;
int lobby_call = -1;


int efound =-1;
int pfound =-1;

int main()
{
    loadingAllDataFromFile();
    printingAllData();
    Lobby();
    //login();
    return 0;
}

void Lobby()
{
    int lob = 0;
    printf("This is Lobby Sector: \n");
    printf("Press 1 to Register: \n");
    printf("Press 2 to Login: \n");
    printf("Press 3 to Exit: \n");
    scanf(" %d",&lob);
    if(lob==1)
    {
        printf("Register Now: \n");
        Registeration();
    }else if(lob == 2)
    {
        printf("Login Now: \n");
        login();
    }else if(lob ==3 )
    {
        recordingAllDataToFile();
        printingAllData();
        exit(1);
    }else{
        printf("Invalid Option: \n");
        //lobby_call = 1;
        Lobby();
    }

}



void printingAllData()
{
    for(int i=0;i<globalIndex;i++)
    {
        printf("id: %d name: %s - age: %d - email: %s - password: %s \n",info[i].id,info[i].name,info[i].age,info[i].email,info[i].password);
    }
}


void login()
{
    char LEmail[50];
    char LPassword[50];
    int found = -1;

    printf("Login Form: \n");
    printf("Enter email: ");
    scanf(" %[^\n]",&LEmail);

    printf("Enter Password: ");
    scanf(" %[^\n]",&LPassword);

    efound = -1;
    pfound = -1;
    myStrCmp(LEmail);

    passwordChecking(LPassword,efound);

    if(efound != -1 && pfound == 1)
    {
        UserActionSector();
        //printf("You are Login. \nWelcome Sir: %s \n",info[efound].email);
        //efound =-1;
        //login();
    }else{
        printf("You cannot Login:\n Invalid Password or Email:  %s \n",info[efound].email);
        login();
    }
}



void myStrCmp(char userInputChar[50])
{
    int sameCount = 0;
    int sec = charCounting(userInputChar);

    for(int i=0; i<globalIndex; i++)
    {
        int first = charCounting(info[i].email);

        if(first == sec)
        {
            for(int gcc=0; gcc<first; gcc++)
            {
                if(info[i].email[gcc] != userInputChar[gcc])
                {
                    break;
                }else{
                    sameCount++;
                }
            }
        }
        if( sec == sameCount )
        {
            efound = i;
            break;
        }
    }

}


void passwordChecking(char pass[50],int userIndex)
{
    int passCount = charCounting(pass);
    int infoPassCount = charCounting(info[userIndex].password);

    int sameCount = 0;

    if(passCount == infoPassCount)
    {
       for(int i=0;i<passCount;i++)
        {
            if(pass[i] == info[userIndex].password[i])
            {
                sameCount++;
            }else{
                break;
            }
        }
        if(sameCount == passCount)
        {
            pfound = 1;
            //break;
        }
    }
}



int charCounting(char toCount[50])
{
    int charCount = 0;
    for(int gcc=0; gcc<50; gcc++)
    {
        if( toCount[gcc] == '\0' )
        {
            break;
        }else{
            charCount++;
        }
    }
    //printf("char count = %d ;",charCount);

    return charCount;
}

void Registeration()
{
    int a = globalIndex;
    //int a = ++b;
    efound = -1;
    email_fomat_correct = -1;

    //printf("Global index = %d : %d \n",a,globalIndex);

    printf("Enter email: ");
    scanf(" %[^\n]",&info[a].email);

    validate_email(info[a].email,a);
    Check_Count_function_for_Validate();

    if(email_fomat_correct == 1)
    {
        myStrCmp(info[a].email);
        if(efound == -1)
        {
            info[a].id = a;

           // printf("Email Can Register: At efound = %d \n",efound);
            //printf("You can register your email, name, password: \n");

            printf("Enter age: ");
            scanf("%d",&info[a].age);

            printf("Enter name: ");
            scanf(" %[^\n]",&info[a].name);

            printf("Enter password: ");
            scanf(" %[^\n]",&info[a].password);

            save_data = 1;

            recordingAllDataToFile();
            //printingAllData();

            printf("id: %d name: %s - age: %d - email: %s - password: %s \n",info[a].id,info[a].name,info[a].age,info[a].email,info[a].password);


            //Lobby();
        }else{
            //b = globalIndex;
            printingAllData();
            printf("Email is Already Taken: At efound = %d \n",efound);
            Lobby();
        }
    }else{
        Lobby();
    }

    if(save_data == 1)
    {
        recordingAllDataToFile();
        //printingAllData();
        //Lobby();
    }else{
        printf("FAil To Save: \n");
    }

    //recordingAllDataToFile();
}



void recordingAllDataToFile()
{
    FILE *fptr = fopen(text_file,"w");
    if(fptr == NULL)
    {
        printf("Error at recordingAllDataToFind :\n");
    }else{

        for(int i=0;i<globalIndex; i++)
        {
            fprintf(fptr,"%d %d %s %s %s%c",info[i].id,info[i].age,info[i].name,info[i].email,info[i].password,'\n');
            //printf("recording data -->%d\n",globalIndex);
        }
        globalIndex++;
        //printf("recording data --> %d\n",globalIndex);

        printf("Recording data to text file successfully: \n");

    }
    fclose(fptr);
}




void UserActionSector()
{
    int userAction = 0;
    printf("You are Login. \nWelcome Sir: %s \n",info[efound].email);
    printf("Press 1 to User Action Sector: \n");
    printf("Press 2 to Home: \n");
    printf("Press 3 to Exit: \n");
    scanf(" %d",&userAction);

    if(userAction == 1)
    {
        printf("User Action Sector: \n");
    }else if(userAction == 2)
    {
        login();
    }else if(userAction == 3)
    {
        recordingAllDataToFile();
        exit(1);
    }else{
        printf("Invalid Option: \n");
        UserActionSector();
    }

}



void loadingAllDataFromFile()
{
    //printf("Data Reading ... \n");
    FILE *fptr = fopen(text_file,"r");
    if(fptr == NULL)
    {
        printf("Error at Reading Data from text file ... \n");
    }else{

        for(int i=0; i<SIZE; i++)
        {
            fscanf(fptr,"%d%d%s%s%s",&info[i].id,&info[i].age,&info[i].name,&info[i].email,&info[i].password);

            if(info[i].name[0] == '\0')
            {
                break;
            }
            globalIndex++;
        }
    }
    fclose(fptr);
}


void validate_email(char email[SIZE],int var2)
{
    for(int i=0;i<SIZE ;i++){
        if(info[var2].email[i] == '\0')
        {
            break;
        }else{
            if(info[var2].email[i] == va)
            {
                glob_var1 = i;
                go_check = 1;
            }
            //printf("email = %c \n",info[var2].email[i]);
        }
    }

    for(int i=0;i<SIZE ;i++){
        if(email_format[i] == '\0')
        {
            break;
        }else{

            //printf("email_format = %c \n",email_format[i]);
        }

    }

    if(go_check ==1)
    {
        //printf("@@@ Format Checking start Now: %d \n",glob_var1);
        for(int j=0;j<11 ;j++){
            int i = glob_var1;
            if(info[var2].email[i] == email_format[j] && info[var2].email[i] != '\0' && email_format[j] != '\0')
            {
                same_countt++;
                ++glob_var1;
                //printf("Correct: --> %c = %c \n",info[var2].email[i],email_format[j]);
            }else{
                not_same_countt++;
                //printf("Incorrect: --> %c != %c \n",info[var2].email[i],email_format[j]);
                break;
            }

        }

    }
    glob_var1 =0;

}


void Check_Count_function_for_Validate()
{
    if(same_countt == 10)
    {
        email_fomat_correct = 1;
        printf("Mail format is correct. %d\n",email_fomat_correct);
        //same_countt = 0;
        //glob_var1 = 0;
    }else{
        printf("Mail format is incorrect. %d\n",email_fomat_correct);
        //same_countt = 0;
    }

    same_countt = 0;
    //printf("Count = %d \n",same_countt);
    //printf("Not Same Count = %d \n",not_same_countt);
}




