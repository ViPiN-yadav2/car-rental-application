#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include<time.h>
struct User
{
    char userid[20];
    char pwd[20];
    char name[20];
};
struct Car
{
    int car_id;
    char car_name[50];
    int capacity;
    int car_count;
    int price;
};
struct Customer_Car_Details
{
    int car_id;
    char cust_name[30];
    char pick[30];
    char drop[30];
    struct tm ed,sd;
};
typedef struct User User;
typedef struct Car Car;
typedef struct Customer_Car_Details Customer_Car_Details;

void addAdmin();
User*getInput();
int checkUserExist(User,char*);
int adminMenu();
void addEmployee();
void viewEmployee();
void addCarDetails();
void showCarDetails();
int deleteEmp();
int deleteCarModel();
int empMenu();
int rentCar();
int selectCarModel();
int isValidDate(struct tm);
void updateCarCount(int );
void bookedCarDetails();
char *getCarName(int );
void availCarDetails();
int returnCar();
#endif // CAR_H_INCLUDED
