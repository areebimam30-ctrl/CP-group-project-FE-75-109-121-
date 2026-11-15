#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INITIAL_CAPACITY 5
#define MENU_FILE "menu.dat"
/*............FOOD STRUCTURE.............*/
typedef struct Food {
    int foodId;
    float price;
    char name[30];
    int quantity;

}Food;
/*.......DYNAMIC ARRAY OF FOOD ITEMS.......*/
Food *menu = NULL;
int itemcount=0;
int capacity = 0;
/*..........FUNCTIONS........*/

void showMainMenu(void);
void addFood(void);
void displayFood(void);
void searchFood(void);
void updateFood(void);
void deleteFood(void);

int main(){

    int choice;
    loadMenu();
    
    do{
        showMainMenu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        
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
    }
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
        void loadMenu(void){
    FILE *fp=fopen(MENU_FILE,"rb");

    if(fp==NULL){
        /* file does not exist yet (first run): start with an empty menu */
        capacity=INITIAL_CAPACITY;
        menu=malloc(capacity*sizeof(Food));
        if(menu==NULL){
            printf("Memory allocation failed\n");
            exit(1);
        }
        itemcount=0;
        return;
    }

    /* first value in the file is the number of items */
    if(fread(&itemcount,sizeof(int),1,fp)!=1){
        itemcount=0;
    }

    capacity=itemcount+INITIAL_CAPACITY;
    menu=malloc(capacity*sizeof(Food));
    if(menu==NULL){
        printf("Memory allocation failed\n");
        fclose(fp);
        exit(1);
    }

    if(itemcount>0){
        fread(menu,sizeof(Food),itemcount,fp);
    }

    fclose(fp);
    printf("%d food items loaded from file\n",itemcount);
}
        
                void saveMenu(void){
                FILE*fp=fopen(MENU_FILE,"wb");
                if(fp==NULL){
                printf("Could not save data to file\n");
                return;}
                fwrite(&itemcount,sizeof(int),1,fp);
                fwrite(menu,sizeof(Food),itemcount,fp);
                fclose(fp);}
        void addFood(void){
            int i,newid;
            if(itemcount==capacity){
            int newCapacity=capacity*2;
            Food*temp=realloc(menu,newCapacity*sizeof(Food));
            if(temp==NULL){
            printf("Memory allocation failed\n");
            return;}
            menu=temp;
            capacity=newCapacity;}
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
                saveMenu();
                printf("Item added succesfully\n");
             }
    
        
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


    