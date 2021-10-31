#include"car.h"
#include<stdio.h>
#include"conio2.h"
#include<string.h>

void addAdmin()
{
    FILE *fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        User u[2]={{"admin","test","Ravi"},{"super","demo","Anil"}};
        fwrite(u,sizeof(u),1,fp);
        fclose(fp);
        _getch();
    }
    else
    {
        fclose(fp);
    }

}
User *getInput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(40,1);
    printf("car rental system");
    gotoxy(1,3);
    for(i=1;i<120;i++)
        printf("%c",247);
    gotoxy(40,5);
    printf("*Login Penal*");
    gotoxy(1,7);
    for(i=1;i<120;i++)
        printf("%c",247);
    gotoxy(1,15);
    for(i=1;i<120;i++)
        printf("%c",247);
    gotoxy(90,8);
    textcolor(WHITE);
    printf("press 0 to exit");
    textcolor(YELLOW);
    gotoxy(40,10);
    printf("enter userid");
    textcolor(WHITE);
    static User u;
    fflush(stdin);
    fgets(u.userid,20,stdin);
    char *pos;
    pos=strchr(u.userid,'\n');
    if(pos!=NULL)
    {
        *pos='\0';
    }
    if(strcmp(u.userid,"0")==0)
    {
        textcolor(RED);
        gotoxy(40,17);
        printf("login cancel");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    gotoxy(40,11);
    printf("enter password");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        u.pwd[i]=getch();
        if(u.pwd[i]==13)
        {
            break;
        }
        printf("*");
        i++;
    }
    u.pwd[i]='\0';
    if(strcmp(u.pwd,"0")==0)
    {
        textcolor(RED);
        gotoxy(40,17);
        printf("login cancel");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
        return &u;
}
int checkUserExist(User u,char *usertype)
{
    if(strlen(u.userid)==0||strlen(u.pwd)==0)
    {
        gotoxy(28,40);
        textcolor(LIGHTRED);
        printf("both field are mandatory try again");
        getch();
        gotoxy(28,40);
        printf("\t\t\t\t\t\t\t");
        return 0;
    }
    FILE *fp;
    if(strcmp(usertype,"admin")==0)
    {
        fp=fopen("admin.bin","rb");
    }
    else
    {
        fp=fopen("emp.bin","rb");
    }
    if(fp==NULL)
    {
        gotoxy(15,40);
        textcolor(LIGHTRED);
        printf("cannot open file");
        getch();
        gotoxy(15,40);
        printf("\t\t\t\t\t\t\t");
        return -1;
    }
    int found=0;
    User user;
    while(fread(&user,sizeof(user),1,fp)==1)
    {
        if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
        {
            found=1;
            break;
        }
    }
    if(found==0)
    {
        gotoxy(15,40);
        textcolor(LIGHTRED);
        printf("invalid userid/pwd try again");
        getch();
        gotoxy(15,40);
        printf("\t\t\t\t\t\t\t");
    }
    else
    {
        gotoxy(40,30);
        textcolor(GREEN);
        printf("login successfull");
        getch();
        gotoxy(40,30);
        printf("\t\t\t\t\t\t\t");
    }
    fclose(fp);
    return found;
}
int adminMenu()
{
    int i,choice;
    textcolor(LIGHTRED);
    gotoxy(40,2);
    printf("car rental system");
    textcolor(LIGHTGREEN);
    gotoxy(45,6);
    printf("ADMIN MENU\n");
    for(i=1;i<=120;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(45,8);
    printf("1. Add Employee");
    gotoxy(45,9);
    printf("2.Add Car Details");
    gotoxy(45,10);
    printf("3. Show Employee");
    gotoxy(45,11);
    printf("4. Show car Details");
    gotoxy(45,12);
    printf("5.Delete Employee");
    gotoxy(45,13);
    printf("6. Delete car details");
    gotoxy(45,15);
    printf("7. Exit");
    gotoxy(45,17);
    printf("enter choice");
    scanf("%d",&choice);

    return choice;
}

void addEmployee()
{
    char empid[10]={"EMP-"};
    char temp[10];
    char choice;
    char *pos;
    User u;
    FILE *fp=fopen("emp.bin","ab+");
    fseek(fp,0,SEEK_END);
    int total_rec=ftell(fp)/sizeof(User);
    if(total_rec!=0)
    {
        fseek(fp,-60,SEEK_END);
        fread(temp,sizeof(temp),1,fp);
        printf("temp is %s",temp);
        getch();
        pos=strchr(temp,'-');
        total_rec=atoi(pos+1);
        printf("\ntotal rec is %d",total_rec);
        getch();
    }
    total_rec++;
    sprintf(temp,"%d",total_rec);
    strcat(empid,temp);
    strcpy(u.userid,empid);
    do
    {
        clrscr();
        gotoxy(45,2);
        textcolor(LIGHTRED);
        int i;
        gotoxy(1,3);
        for(i=1;i<=120;i++)
            printf("~");
        textcolor(WHITE);
        gotoxy(40,5);
        printf("*****ADD EMPLOYEE DETAILS*****");
        getch();
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter employee name");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.name,20,stdin);
        pos=strchr(u.name,'\n');
        *pos='\0';
        textcolor(YELLOW);
        printf("Enter Employee pwd:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd,20,stdin);
        pos=strchr(u.pwd,'\n');
        *pos='\0';
        textcolor(YELLOW);
        fseek(fp,0,SEEK_END);
        fwrite(&u,sizeof(User),1,fp);
        gotoxy(40,15);
        textcolor(LIGHTGREEN);
        printf("Employee add successfully");
        printf("\n Employee ID IS:%s",u.userid);
        _getch();
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE EMPLOYEE (Y/N)");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice=='N')
            break;
        total_rec++;
        strcpy(empid,"EMP-");
        sprintf(temp,"%d",total_rec);
        strcat(empid,temp);
        strcpy(u.userid,empid);
    }while(choice=='Y'||choice=='y');
    fclose(fp);
}

void addCarDetails()
{
    char choice;
    int temp;
    Car c;
    int i;
    FILE *fp=fopen("car.bin","ab+");
    fseek(fp,0,SEEK_END);
    int total_rec=ftell(fp)/sizeof(Car);
    if(total_rec!=0)
    {
        fseek(fp,-1*sizeof(Car),SEEK_END);
        fread(&temp,sizeof(temp),1,fp);
        temp=temp+1;
        printf("%d",temp);
        total_rec=temp;
        printf("%d",total_rec);
        getch();
    }
    c.car_id=total_rec;
    do
    {
        clrscr();
        gotoxy(1,2);
        textcolor(LIGHTGREEN);
        for(i=1;i<=120;i++)
        printf("~");
        gotoxy(45,1);
        textcolor(LIGHTRED);
        printf("****CAR RENTAL APP****");
        getch();
        gotoxy(1,5);
        printf("enter car model:");
        fflush(stdin);
        fgets(c.car_name,50,stdin);
        char *pos;
        pos=strchr(c.car_name,'\n');
        *pos='\0';
        printf("\n");
        printf("enter the capacity:");
        fflush(stdin);
        scanf("%d",&c.capacity);
        printf("\n");
        printf("enter the car count:");
        fflush(stdin);
        scanf("%d",&c.car_count);
        printf("\n");
        printf("enter car price for per day:");
        fflush(stdin);
        scanf("%d",&c.price);
        fseek(fp,0,SEEK_END);
        fwrite(&c,sizeof(Car),1,fp);
        textcolor(LIGHTGREEN);
        gotoxy(45,20);
        printf("car added successfully");
        gotoxy(1,15);
        printf("car id is %d",c.car_id);
        getch();
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE EMPLOYEE (Y/N)");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice=='N'||choice=='n')
            break;
        total_rec++;
        c.car_id=total_rec;
    }while(choice=='y'||choice=='Y');
fclose(fp);
}

void viewEmployee()
{
    int i,n=9;
    User u;
    gotoxy(45,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(45,5);
    printf("*  EMPLOYEE DETAILS  *\n");
    textcolor(LIGHTGREEN);
    for(i=0;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,7);
    printf("Employee ID");
    gotoxy(45,7);
    printf("Password");
    gotoxy(85,7);
    printf("Name");
    printf("\n");
    for(i=0;i<=120;i++)
    {
        printf("%c",247);
    }
    FILE *fp;
    fp=fopen("emp.bin","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(45,15);
        printf("no employee found");
        getch();
        return;
    }
    while(fread(&u,sizeof(User),1,fp)==1)
    {
        gotoxy(1,n);
        printf("%s",u.userid);
        gotoxy(45,n);
        printf("%s",u.pwd);
        gotoxy(85,n);
        printf("%s",u.name);
        n++;
    }
    fclose(fp);
    getch();
}

void showCarDetails()
{
    int i,n=9;
    Car c;
    gotoxy(45,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(45,5);
    printf("*  CAR DETAILS  *\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,7);
    printf("Car ID");
    gotoxy(24,7);
    printf("Car Name");
    gotoxy(48,7);
    printf("Capacity");
    printf("\n");
    gotoxy(72,7);
    printf("Car Count");
    printf("\n");
    gotoxy(96,7);
    printf("Price");
    printf("\n");
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    FILE *fp;
    fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(45,15);
        printf("no car found");
        getch();
        return;
    }
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        gotoxy(1,n);
        printf("%d",c.car_id);
        gotoxy(24,n);
        printf("%s",c.car_name);
        gotoxy(48,n);
        printf("%d",c.capacity);
        gotoxy(72,n);
        printf("%d",c.car_count);
        gotoxy(96,n);
        printf("%d",c.price);
        n++;
    }
    fclose(fp);
    getch();
}

int deleteEmp()
{
    FILE *fp1;
    fp1=fopen("emp.bin","rb");
    char empid[10];
    int i,result;
    textcolor(YELLOW);
    gotoxy(45,1);
    printf("car rental system\n");
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* delete employee record *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,12);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n NO employee added yet");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(15,9);
    textcolor(YELLOW);
    printf("enter the employee id");
    textcolor(WHITE);
    scanf("%s",empid);
    User U;
    int found=0;

    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
            else
        {
             found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
    else
    {
        result=remove("emp.bin");
        if(result!=0)
            return 2;
    }
    result=rename("temp.bin","emp.bin");
    if(result!=0)
        return found;
    else//just to remove the warning control reaches end of non-void function
        return -1;
}

int empMenu()
{
    int i,choice;
    clrscr();
    gotoxy(45,1);
    printf("CAR RENTAL SYSTEM");
    gotoxy(48,5);
    textcolor(LIGHTGREEN);
    printf("EMLOYEE MENU");
    gotoxy(1,6);
    for(i=0;i<=120;i++)
        printf("*");
    gotoxy(45,7);
    textcolor(YELLOW);
    printf("1.Rent A Car");
    gotoxy(45,8);
    printf("2.Booking Details");
    gotoxy(45,9);
    printf("3. Available Car Details");
    gotoxy(45,10);
    printf("4.Show All Car Details");
    gotoxy(45,11);
    printf("6.Return car");
    gotoxy(45,12);
    printf("5.Exit");
    gotoxy(45,14);
    printf("Enter choice:");
    scanf("%d",&choice);
    return choice;
}

int rentCar()
{
    Customer_Car_Details CC;
    int c,i;
    textcolor(LIGHTRED);
    gotoxy(45,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(47,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    c=selectCarModel();
    if(c==0||c==-2)
        return c;
    CC.car_id=c;
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    gotoxy(1,17);
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter Pickup Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.pick,30,stdin);
    pos=strchr(CC.pick,'\n');
    *pos='\0';
    gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter Drop Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date (dd/m/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid=isValidDate(CC.sd);
        if(datevalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            _getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(56,12);
            printf("\t\t\t");
            gotoxy(56,12);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date (dd/m/yyyy):");
    textcolor(WHITE);

    do
    {
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        int datevalid=isValidDate(CC.ed);
        if(datevalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            _getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(54,13);
            printf("\t\t\t");
            gotoxy(54,13);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);

    FILE *fp;
    fp=fopen("customer.bin","ab");
if(fp==NULL)
{
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Sorry ! File cannot be opened");
        getch();
        gotoxy(27,18);
        printf("\t\t");
        return -1;
    }
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
    printf("Booking Done:%d",CC.car_id);
    printf("\nPress any key to continue...");
    _getch();

    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;
}


int selectCarModel()
{
    int flag;
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int choice,x=9;
    gotoxy(45,x);
    int carcount=0;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            printf("%d %s",C.car_id,C.car_name);
            gotoxy(45,++x);
            ++carcount;
        }
    }
    if(carcount==0)
    {
        fclose(fp);
        return -2;
    }
    gotoxy(45,x+2);
    printf("enter your choice(0 to quit)");
        while(1)
        {
            flag=0;
            scanf("%d",&choice);
            if(choice==0)
                {
                    fclose(fp);
                    return 0;
                }
            rewind(fp);
            while(fread(&C,sizeof(C),1,fp)==1)
            {
                if(C.car_id==choice&&C.car_count>0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                fclose(fp);
                return choice;
            }
            else
            {
                gotoxy(45,x+4);
                textcolor(LIGHTRED);
                printf("wrong input");
                _getch();
                gotoxy(42,x+4);
                printf("\t\t");
                gotoxy(62,x+2);
                printf("\t");
                gotoxy(52,x+2);
                textcolor(WHITE);
            }
        }
        getch();
}

int isValidDate(struct tm dt)
{
    time_t obj=time(0);
    struct tm *p=localtime(&obj);
    if(dt.tm_year>=2021 && dt.tm_year<=2022)
    {
        if(1900+p->tm_year!=dt.tm_year)
        {
            return 0;
        }
        //check month
        if(dt.tm_mon>=1 && dt.tm_mon<=12)
        {
            if(1+p->tm_mon>dt.tm_mon)
            {
                return 0;
            }
            else{
            //check days
            if((dt.tm_mday>=1 && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
               {
                   if(p->tm_mday>dt.tm_mday)
                        return 0;
                   else
                        return 1;
                }
            else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
               {
                   if(p->tm_mday>dt.tm_mday)
                       return 0;
                   else
                       return 1;
                }
            else if((dt.tm_mday>=1 && dt.tm_mday<=28) && (dt.tm_mon==2))
                {
                   if(p->tm_mday>dt.tm_mday)
                       return 0;
                   else
                       return 1;
                }
            else if(dt.tm_mday==29 && dt.tm_mon==2 && (dt.tm_year%400==0 ||(dt.tm_year%4==0 && dt.tm_year%100!=0)))
               {
                   if(p->tm_mday>dt.tm_mday)
                        return 0;
                   else
                        return 1;
               }
            else
               return 0;}
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

void updateCarCount(int c)
{
    FILE *fp=fopen("car.bin","rb+");
    Car C;
    while(fread(&C,sizeof(Car),1,fp)==1)
    {
        if(C.car_id==c)
        {
            fseek(fp,-8,SEEK_CUR);
            int cc_new;
            cc_new=C.car_count-1;
            fwrite(&cc_new,sizeof(cc_new),1,fp);
            fseek(fp,-4,SEEK_CUR);
            _getch();
        }
        }
    fclose(fp);
}

void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    Customer_Car_Details CC;
    int i;
    gotoxy(45,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,2);
    for(i=0;i<=119;i++)
        printf("%c",247);
    gotoxy(45,5);
    printf("*  BOOKED CAR DETAILS  *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<=119;i++)
        printf("%c",247);
    gotoxy(1,8);
    printf("model\t cust Name\t Pick Up\t Drope\t\t S_Date\t E_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=119;i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,x);
        printf("%s",getCarName(CC.car_id));
        gotoxy(13,x);
        printf("%s",CC.cust_name);
        gotoxy(27,x);
        printf("%s",CC.pick);
        gotoxy(44,x);
        printf("%s",CC.drop);
        gotoxy(58,x);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(70,x);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);
        x++;
    }
    fclose(fp);
    _getch();
}

char *getCarName(int p)
{
    FILE *fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("cannot open file");
        return 0;
    }
    static Car c;
    rewind(fp);
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(p==c.car_id)
        {
            break;
        }
    }
    fclose(fp);
    return c.car_name;
}

void availCarDetails()
{
    clrscr();
    int i,x=7;
    Car c;
    FILE *fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("unable to open file");
        getch();
        return;
    }
    gotoxy(48,1);
    textcolor(LIGHTRED);
    printf("AVAILABLE CAR DETAILS");
    gotoxy(1,4);
    textcolor(LIGHTGREEN);
    for(i=0;i<120;i++)
        printf("*");
    gotoxy(1,6);
    textcolor(LIGHTGREEN);
    for(i=0;i<120;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(1,5);
    printf("car ID");
    gotoxy(35,5);
    printf("car name");
    gotoxy(65,5);
    printf("car count");
    gotoxy(105,5);
    printf("price");
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_count>0)
        {
        textcolor(YELLOW);
        gotoxy(1,x);
        printf("%d",c.car_id);
        gotoxy(35,x);
        printf("%s",c.car_name);
        gotoxy(65,x);
        printf("%d",c.car_count);
        gotoxy(105,x);
        printf("%d",c.price);
        x++;}
    }
    fclose(fp);
    getch();
}
int deleteCarModel()
{
    FILE *fp1;
    fp1=fopen("car.bin","rb");
    int carid;
    int i,result;
    textcolor(YELLOW);
    gotoxy(45,1);
    printf("car rental system\n");
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* delete employee record *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,12);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n NO car added yet");
        return -1;
    }
    FILE *fp2=fopen("temp1.bin","wb+");
    gotoxy(15,9);
    textcolor(YELLOW);
    printf("enter the car id");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car U;
    int found=0;

    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(U.car_id!=carid)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
            else
        {
             found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp1.bin");//remove function return 0 after successful detection
    }
    else
    {
        result=remove("car.bin");
        if(result!=0)
            return 2;
    }
    result=rename("temp1.bin","car.bin");
    if(result!=0)
        return found;
}

int returnCar()
{
    FILE *fp1;
    fp1=fopen("car.bin","rb");
    int carid;
    int i,result;
    textcolor(YELLOW);
    gotoxy(45,1);
    printf("car rental system\n");
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* delete car model *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,12);
    for(i=1;i<=120;i++)
    {
        printf("%c",247);
    }
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n NO car added yet");
        return -1;
    }
    FILE *fp2=fopen("temp1.bin","wb+");
    gotoxy(15,9);
    textcolor(YELLOW);
    printf("enter the car id");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car U;
    int found=0;

    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(U.car_id!=carid)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else if(U.car_id==carid)
        {
             U.car_count=++U.car_count;
             fwrite(&U,sizeof(U),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
        result=remove("car.bin");
        if(result!=0)
            return 2;
    result=rename("temp1.bin","car.bin");
    if(result!=0)
        return found;
}










