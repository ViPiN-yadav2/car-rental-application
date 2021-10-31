#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"car.h"

int main()
{
    int i,type,k,result,choice;
    User *usr;
    gotoxy(40,10);
    textcolor(YELLOW);
    printf("WELCOM TO CAR RENTAL SYSTEM");
    gotoxy(35,13);
    textcolor(LIGHTGREEN);
    printf("*RENT A CAR AND GO WHEREVER YOU NEED*");
    addAdmin();
    _getch();
    while(1){
    clrscr();
    gotoxy(45,2);
    textcolor(RED);
    printf("car rental system");
        gotoxy(1,3);
        for(i=0;i<=119;i++)
        {
            textcolor(YELLOW);
            printf("*");
        }
        textcolor(YELLOW);
        gotoxy(1,16);
        for(i=0;i<119;i++)
            printf("*");
        textcolor(GREEN);
        gotoxy(45,7);
        printf("1.admin");
        gotoxy(45,8);
        printf("2.Employee");
        gotoxy(45,9);
        printf("3.exit");
        gotoxy(45,10);
        textcolor(WHITE);
        printf("select your role");
        do{
        gotoxy(62,10);
        textcolor(WHITE);
        printf("\t\t\t");
        gotoxy(62,10);
        fflush(stdin);
        scanf("%d",&type);

        if(type==1)
        {
            do
            {
                usr=getInput();
                if(usr==NULL)
                {
                k=2;
                break;
                }
                else
                 {
                     k=checkUserExist(*usr,"admin");
                 }
            }while(k==0);
            if(k==2)
                break;
            if(k==-1)
                break;
            if(k==1)
            {
                gotoxy(1,20);
                textcolor(WHITE);
                printf("press any to continue");
                _getch();
                while(1)
                {
                    clrscr();
                    choice=adminMenu();
                    if(choice==7)
                        break;
                    switch(choice)
                    {
                    case 1:
                        clrscr();
                        addEmployee();
                        break;
                    case 2:
                        clrscr();
                        addCarDetails();
                        break;
                    case 3:
                        clrscr();
                        viewEmployee();
                        break;
                    case 4:
                        clrscr();
                        showCarDetails();
                        break;
                    case 5:
                        clrscr();
                        result=deleteEmp();
                        gotoxy(15,14);
                        if(result==0)
                        {
                            textcolor(LIGHTRED);
                            printf("Sorry no emp found for given emp id");
                        }
                        else if(result==1)
                        {
                            textcolor(LIGHTGREEN);
                            printf("record deleted successfullt");
                        }
                        else if(result==2)
                        {
                            textcolor(LIGHTRED);
                            printf("sorry error in deletion. try again");
                        }
                        textcolor(WHITE);
                        printf("\n\npress any key to go to main screen");
                        getch();
                        break;
                    case 6:
                        clrscr();
                        deleteCarModel();
                        break;
                    default :
                        printf("you have enter wrong input");

                    }
                }
                if(choice==7)
                    break;
            }
        }
        if(type==2)
        {
            do
            {
                usr=getInput();
                if(usr!=NULL)
                {
                    k=checkUserExist(*usr,"emp");
                }
                else if(usr==NULL)
                {
                    k=2;
                    break;
                }
            }while(k==0);
            if(k==2)
                break;
            if(k==-1)
                break;
            if(k==1)
            {
                gotoxy(1,20);
                textcolor(WHITE);
                printf("press any key to continue");

                _getch();
                while(1)
                {
                    clrscr();
                    choice=empMenu();
                    if(choice==5)
                    {
                        break;
                    }
                    switch(choice)
                    {
                    case 1:
                        clrscr();
                        int rentresp;
                       rentresp=rentCar();
                       if(rentresp==-2)
                       {
                           gotoxy(45,10);
                           textcolor(LIGHTRED);
                           printf("all car booked");
                           getch();
                       }
                       else if(rentresp==0)
                       {
                           gotoxy(40,18);
                           textcolor(LIGHTRED);
                           printf("you did not choose any car");
                           getch();
                       }
                        break;
                    case 2:
                        clrscr();
                        bookedCarDetails();
                        break;
                    case 3:
                        clrscr();
                        availCarDetails();
                        break;
                    case 4:
                        clrscr();
                        showCarDetails();
                        break;
                    case 6:
                        clrscr();
                        returnCar();
                        break;
                    default:
                        printf("Incorrect Choice");
                    }
                }
                if(choice==5)
                    break;
            }
        }
        if(type==3)
        {
            clrscr();
            printf("thank you for using our service hope you enjoied");
            getch();
            exit(0);
        }
        else
        {
            textcolor(RED);
            gotoxy(40,15);
            printf("invalid user type");
            _getch();
            gotoxy(40,15);
            printf("\t\t\t\t\t");
        }}while(1);

   _getch();
    }
    return 0;
}
