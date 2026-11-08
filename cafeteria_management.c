#include<stdio.h>
#include<string.h>
#define maxItems 100
/*............FOOD STRUCTURE.............*/
struct Food {
    int foodId;
    int price;
    char name[30];
    float quantity;

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
            searchFood();
            break;
            case 4:
            updateFood();
            break;
            case 5:
            deleteFood();
            break;
            case 9:
            printf("\nThank you for using CAFETERIA MANAGEMENT SYSTEM!\n");
            printf("Program Exited Successfuly");
            break; 
            default:
            printf("invalid choice\n");
            break;
         }
        }


        while(choice!=9);
        return 0;
    }//will decide later
        void showMainMenu(){
            printf("\n===================\n");
            printf("CAFETERIA MANAGEMENT SYSTEM");
            printf("\n===================\n");
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
                scanf("%d",&menu[itemcount].foodId);
                for(i=0;i<itemcount;i++){
                if(menu[i].foodId==newid){
            printf("this id already exists");
            return;
        }}
                printf("Enter Food name: \n");
                scanf("%s",menu[itemcount].name);
                printf("Enter Food price: \n");
                scanf("%d",&menu[itemcount].price);
                printf("Enter food quantity: \n");
                scanf("%f",&menu[itemcount].quantity);
                itemcount++;
                printf("Item added succesfully");
             }else{
                printf("Menu is full. Can't add more items\n");
             }}
             void displayFood(void){
                int i;
                if(itemcount==0){   
                printf("No food items present,add some food items first");
                return;
            }
            printf("\n----Menu----\n");
              printf("%-5s %-20s %-10s %-8s \n", "ID",
                 "Name",
                 "Price",
                 "Qty");
    printf("---------------------------------------------\n");

    for (i = 0; i < itemcount; i++) {
        printf("%-5d %-20s %-10d %-8.2f\n",menu[i].foodId,
            menu[i].name,
            menu[i].price,
            menu[i].quantity);
    }
}
            
// search food function 

void searchFood(void)
{
    int searchID;

    printf("Enter food id to search: ");
    scanf("%d",&searchID);

    int i;
    for(i=0;i<itemcount;i++)
    {
        if(menu[i].foodId==searchID)
        {
            printf("Food Found : %s\n",menu[i].name);
            return; 
        }
    }

    printf("Food item not found \n");
}
             
// update food function

void updateFood(void)
{
    int id, i;

    printf("Enter Food ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < itemcount; i++)
    {
        if (menu[i].foodId == id)
        {
            printf("Enter new name: ");
            scanf("%29s", menu[i].name);

            printf("Enter new price: ");
            scanf("%d", &menu[i].price);

            printf("Enter new quantity: ");
            scanf("%f", &menu[i].quantity);

            printf("Food updated successfully!\n");
            return;
        }
    }

    printf("Food item not found!\n");
}

// delete food function

void deleteFood(void)
{
    int id, i, j;

    printf("Enter Food ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < itemcount; i++)
    {
        if (menu[i].foodId == id)
        {
            for (j = i; j < itemcount - 1; j++)
            {
                menu[j] = menu[j + 1];
            }

            itemcount--;

            printf("Food deleted successfully!\n");
            return;
        }
    }

    printf("Food item not found!\n");
}


    