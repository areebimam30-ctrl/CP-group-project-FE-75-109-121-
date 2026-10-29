#include<stdio.h>
/*............FOOD STRUCTURE.............*/
struct Food{
    int food id ;
    int price;
    char name[20];
    float quantity;

}
/*...........ARRAY OF FOOD ITEMS.............*/
struct Food Menu[max items];
int itemcount=0;
/*..........FUNCTIONS........*/
//apne function yahan par declare karwa dena
void showMenu(void);
void addFood(void);
void displayFood(void);
int main(){
    int choice;
    do{
        showMenu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        //incomplete hai yeh abhi
        switch(choice){
            case 1:
            addFood();
            break;
            case 2:
            displayFood();
            break;


        }while(choice!= );//will decide later
        showMenu(){
            printf(""===================);
            printf("CAFETERIA MANAGE SYSTEM");
            printf("1. Add Food Item\n");
            printf("2. Display Food Items\n");
            printf("3. Search Food Items\n");
            printf("4 Update Food Items\n");
            printf("5. Delete Food Items\n");
            printf("6.");//incomplete
            printf("7. ");//incomplete
            printf("8.");//incomplete
            printf("9. Exit\n");
        }
        void addFood(void){
            if(itemcount<max items){
                printf("Enter Food ID: \n");
                scanf("%d",&Menu[itemcount].food id);
                printf("Enter Food name: \n");
                scanf("%s",Menu[itemcount].name);
                printf("Enter Food price: \n");
                scanf("%d",&Menu[itemcount].price);
                printf("Enter food quantity: \n");
                scanf("%f",&Menu[itemcount].quantity);
                itemcount++;
             }else{
                printf("Menu is full. Can't add more items\n");
             }
             void displayFood(void){
                int i;
                if(itemcount==0){
                printf("No food items present,add some food items first");
                return;}

             }


}