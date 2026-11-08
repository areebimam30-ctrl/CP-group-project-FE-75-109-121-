#include<stdio.h>
#include<string.h>
#define maxItems 100
/*............FOOD STRUCTURE.............*/
struct Food {
    int foodId;
    float price;
    char name[30];
    int quantity;

};
/*...........ARRAY OF FOOD ITEMS.............*/
struct Food menu[maxItems];
int itemcount=0;
/*..........FUNCTIONS........*/
//apne apne functions yahan par declare krwa dena
void showMainMenu(void);
void addFood(void);
void displayFood(void);
void searchFood(void);
void updateFood(void);
void deleteFood(void);

int main(){
    int choice;
    do{
        showMainMenu();
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
            case 3:
            //searchFood();
            case 4:
            //updateFood();
            case 5:
            //deleteFood();
            case 9:
            printf("Thank you for using this system\n");
            break;

            default:
            printf("invalid choice\n");}
        }


        while(choice!=9 );
        return 0;
    }//will decide later
        void showMainMenu(){
            printf("===================\n");
            printf("CAFETERIA MANAGEMENT SYSTEM\n");
            printf("1. Add Food Item\n");
            printf("2. Display Food Items\n");
            printf("3. Search Food Items\n");
            printf("4 Update Food Items\n");
            printf("5. Delete Food Items\n");
            printf("6.\n");//incomplete
            printf("7. \n");//incomplete
            printf("8.\n");//incomplete
            printf("9. Exit\n");
        }
        void addFood(void){
            int i,newid;
            if(itemcount<maxItems){
                printf("Enter Food ID: \n");
                scanf("%d",&newid);
                for(i=0;i<itemcount;i++){
                if(menu[i].foodId==newid){
            printf("this id already exists\n");
            return;
        }}
        menu[itemcount].foodId=newid;
                printf("Enter Food name: \n");
                scanf(" %29[^\n]",menu[itemcount].name);
                printf("Enter Food price: \n");
                scanf("%f",&menu[itemcount].price);
                printf("Enter food quantity: \n");
                scanf("%d",&menu[itemcount].quantity);
                itemcount++;
                printf("Item added succesfully\n");
             }else{
                printf("Menu is full. Can't add more items\n");
             }}
             void displayFood(void){
                int i;
                if(itemcount==0){
                printf("No food items present,add some food items first\n");
                return;
            }
            printf("\n----Menu----\n");
              printf("%-5s %-20s %-10s %-8s\n", "ID", "Name", "Price", "Qty");
    printf("---------------------------------------------\n");

    for (i = 0; i < itemcount; i++) {
        printf("%-5d %-20s %-10.2f %-8d\n",
            menu[i].foodId,
            menu[i].name,
            menu[i].price,
            menu[i].quantity);
    }
}
            

             


