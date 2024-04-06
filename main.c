#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
float formula(int i)
{
    return i*pow(cos(i+1),i+1);
}
float sum_formula(float sum, int i,float res)
{
    if(i%2==0)
        sum+=res;
    return sum;
}
void exercise_1()
{
    float block,sum=0;
    int n;
    while(n)
    {
        printf("Input n from 7 to 40:");
        scanf("%d",&n);
        if( n>=7 && n<=40)
        {
            break;
        }
        else
        {
            printf("ERORR,check conditional.\n");
            fflush (stdin);
        }
    }
    FILE *f=fopen("f.dat","wb");
    for(int i=1; i<=n; i++)
    {
        block = formula(i);//1
        fwrite(&block,sizeof(block),1,f);
        sum=sum_formula(sum,i,block);
    }
    fclose(f);

    printf("File f:\t");
    f=fopen("f.dat","rb");
    while(fread(&block,sizeof(float),1,f))
        printf("%.3f\t",block);
    printf("\n");
    fclose(f);

    printf("Summ = %f\n",sum);
}
#define  S sizeof(int)
void exercise_2()
{
    const int count_number =10;
    srand(time(NULL));
    FILE *g;
    int block,i;
    //fill in
    if((g = fopen("g.dat","wb"))==NULL)
    {
        perror("Error.");
        exit(1);
    }
    for ( i = 1; i <= count_number; i++)
    {
        block = rand()%20-10;//1
        fwrite(&block,sizeof(block),1,g);
    }
    fclose(g);
    //printf in
    printf("File g:\t");
    if((g = fopen("g.dat","rb"))==NULL)
    {
        perror("Error.");
        exit(3);
    }
    while(fread(&block,sizeof(float),1,g))
        printf("%d\t",block);
    printf("\n");
    fclose(g);


    if((g = fopen("g.dat","rb+"))==NULL)
    {
        perror("Error.");
        exit(2);
    }
    //exercise
    int n;
    fseek(g, 0, SEEK_END);
    n = ftell(g) / sizeof(int);
    int x, y;
    for (int r = 1; r <= n - 1; r++)
    {
        for (int i = 0; i <= n - 2; i++)
        {
            fseek(g, i * sizeof(int), SEEK_SET);
            fread(&x, sizeof(int), 1, g);
            fread(&y, sizeof(int), 1, g);

            if ((x < 0 && y >= 0) || (x == 0 && y > 0))
            {
                fseek(g, i * sizeof(int), SEEK_SET);
                fwrite(&y, sizeof(int), 1, g);
                fwrite(&x, sizeof(int), 1, g);
            }
        }
    }
    fclose(g);
    //printf out
    printf("File g:\t");
    if((g = fopen("g.dat","rb"))==NULL)
    {
        perror("Error.");
        exit(3);
    }
    while(fread(&block,sizeof(float),1,g))
        printf("%d\t",block);
    printf("\n");
    fclose(g);
}
void exercise_3()
{
    FILE *file1 = fopen("file1.txt", "r");
    FILE *file2 = fopen("file2.txt", "r");

    if (file1 == NULL || file2 == NULL)
    {
        perror("error open");
        return 1;
    }

    char ch1, ch2;
    int line_number = 1, position = 0;
    int f = 1;

    while ((ch1 = fgetc(file1)) != EOF && (ch2 = fgetc(file2)) != EOF)
    {
        if (ch1 != ch2)
        {
            f = 0;
            break;
        }
        if (ch1 == '\n')
        {
            line_number++;
            position = 0;
        }
        else
        {
            position++;
        }
    }

    if (!f)
    {
        printf("The files are different on row %d, position %d\n", line_number, position);
    }
    else
    {
        printf("files match\n");
    }

    fclose(file1);
    fclose(file2);
}

void GotoXY(int X, int Y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleTextAttribute(hStdOut,2);
    SetConsoleCursorPosition(hStdOut, coord);
}

void colour(int i)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut,i);
}

void ConsoleCursorVisible(int show, short size)//the visibility of the cursor
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void option()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    ConsoleCursorVisible(0, 100);

    const char* menuOptions[] = {"Block 1","Block 2","Block 3","Exit"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int active_menu = 0;
    char key;

    while (1)
    {
        GotoXY(0, 0);
        printf("To switch left and right arrows\n");
        int x = 25, y = 0;
        GotoXY(x, y);

        for (int i = 0; i < numOptions; i++)
        {
            GotoXY(x+=18, y);
            if (i == active_menu)
            {
                colour(10);
                printf("/ %s / ",  menuOptions[i]);
            }
            else
                printf("  %s   ", menuOptions[i]);
        }
        key = _getch();
        if (key == 32)
            key = _getch();
        switch (key)
        {
        case 27:
            exit(0);
        case 75:
            if (active_menu > 0)
                active_menu--;
            break;
        case 77:
            if (active_menu < numOptions - 1)
                active_menu++;
            break;

        case 13:
            switch (active_menu)
            {
            case 0:
                SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN);
                system("CLS");
                exercise_1();
                _getch();
                system("CLS");
                break;
            case 1:
                SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN);
                system("CLS");
                exercise_2();
                _getch();
                system("CLS");
                break;
            case 2:
                SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN);
                system("CLS");
                exercise_3();
                _getch();
                system("CLS");
                break;
            case 3:
                SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN);
                exit(0);
                break;
            }
            break;
        }
    }
}
int main()
{
    option();
    return 0;
}
