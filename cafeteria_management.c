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
// STRUCTURE OF ORDER ITEMS

typedef struct {
    int orderid;
    Food item;
    float subtotal;
} orderitem;

/*.......DYNAMIC ARRAY OF FOOD ITEMS.......*/
Food *menu = NULL;
int itemcount=0;
int capacity = 0;
orderitem *orders = NULL;
int ordercount = 0;
int ordercapacity = 0;

int nextorderid = 1;

/*..........FUNCTIONS........*/
int increaseOrderCapacity(int needed);
void showMainMenu(void);
void addFood(void);
void displayFood(void);
void searchFood(void);
void updateFood(void);
void deleteFood(void);
void loadMenu(void);
void loadOrders(void);
void saveMenu(void);
void takeOrder(void);
void displayOrders(void);


int main(){

    int choice;
    loadMenu();
    loadOrders();
    
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
            case 6:
            takeOrder();
            break;
            case 7:
            displayOrders();
            break;
            case 9:
                
            saveMenu();
            free(menu);
           
            menu=NULL;
          

            printf("Thank you for using this system\n");
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
            printf("6. Place your order\n");
            printf("7. Display previous orders\n");
            printf("8.\n");
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
        printf("%-5d %-20s %-10.2f %-8d\n",menu[i].foodId,
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
// INCREASE ORDER MEMORY

int increaseOrderCapacity(int needed)
{
    if (needed <= ordercapacity)
        return 1;

    int newcapacity = (ordercapacity == 0) ? 2 : ordercapacity;

    while (newcapacity < needed)
        newcapacity *= 2;

    orderitem *temp = realloc(
        orders, newcapacity * sizeof(orderitem));

    if (temp == NULL)
    {
        printf("Order memory allocation failed!\n");
        return 0;
    }

    orders = temp;
    ordercapacity = newcapacity;

    return 1;
}


// LOAD PREVIOUS ORDERS

void loadOrders(void)
{
    FILE *fp = fopen("orders.txt", "r");

    if (fp == NULL)
    {
        printf("No previous orders found.\n");
        return;
    }

    orderitem temp;
    int largestid = 0;

    while (fscanf(fp, "%d|%d|%29[^|]|%d|%d|%f",
                  &temp.orderid,
                  &temp.item.foodId,
                  temp.item.name,
                  &temp.item.price,
                  &temp.item.quantity,
                  &temp.subtotal) == 6)
    {
        if (!increaseOrderCapacity(ordercount + 1))
            break;

        orders[ordercount] = temp;
        ordercount++;

        if (temp.orderid > largestid)
            largestid = temp.orderid;
    }

    nextorderid = largestid + 1;

    fclose(fp);
}


// SAVE ORDERS TO FILE

int saveOrders(orderitem cart[], int cartcount)
{
    FILE *fp = fopen("orders.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening order file!\n");
        return 0;
    }

    for (int i = 0; i < cartcount; i++)
    {
        if (fprintf(fp, "%d|%d|%s|%d|%d|%.2f\n",
                    cart[i].orderid,
                    cart[i].item.foodId,
                    cart[i].item.name,
                    cart[i].item.price,
                    cart[i].item.quantity,
                    cart[i].subtotal) < 0)
        {
            fclose(fp);
            return 0;
        }
    }

    if (fclose(fp) != 0)
        return 0;

    return 1;
}


// TAKE CUSTOMER ORDER

void takeOrder(void)
{
    int cartcapacity = 2;
    int cartcount = 0;

    // DYNAMICALLY ALLOCATE CART MEMORY

    orderitem *cart = malloc(cartcapacity * sizeof(orderitem));

    if (cart == NULL)
    {
        printf("Cart memory allocation failed!\n");
        return;
    }

    int foodid, quantity, found;
    int orderid = nextorderid;

    float total = 0.0;

    if (itemcount == 0)
    {
        printf("No food items available!\n");
        free(cart);
        return;
    }

    // DISPLAY AVAILABLE MENU

    displayFood();

    printf("\nOrder ID: %d\n", orderid);

    while (1)
    {
        printf("\nEnter Food ID to order (0 to finish): ");

        if (scanf("%d", &foodid) != 1)
        {
            printf("Invalid input!\n");
            free(cart);
            return;
        }

        if (foodid == 0)
            break;

        // SEARCH FOOD ITEM

        found = -1;

        for (int i = 0; i < itemcount; i++)
        {
            if (menu[i].foodId == foodid)
            {
                found = i;
                break;
            }
        }

        if (found == -1)
        {
            printf("Food item not found!\n");
            continue;
        }

        printf("Enter quantity: ");

        if (scanf("%d", &quantity) != 1)
        {
            printf("Invalid input!\n");
            free(cart);
            return;
        }

        if (quantity <= 0)
        {
            printf("Invalid quantity!\n");
            continue;
        }

        // CHECK ALREADY ORDERED QUANTITY

        int alreadyOrderedQuantity = 0;

        for (int j = 0; j < cartcount; j++)
        {
            if (cart[j].item.foodId == foodid)
            {
                alreadyOrderedQuantity += cart[j].item.quantity;
            }
        }

        // CHECK AVAILABLE STOCK

        if (quantity + alreadyOrderedQuantity > menu[found].quantity)
        {
            printf("Not enough stock available!\n");
            continue;
        }

        // INCREASE CART CAPACITY IF FULL

        if (cartcount == cartcapacity)
        {
            int newcapacity = cartcapacity * 2;

            orderitem *temp = realloc(
                cart, newcapacity * sizeof(orderitem));

            if (temp == NULL)
            {
                printf("Cart memory allocation failed!\n");
                free(cart);
                return;
            }

            cart = temp;
            cartcapacity = newcapacity;
        }

        // STORE ORDER DETAILS

        cart[cartcount].orderid = orderid;
        cart[cartcount].item = menu[found];

        cart[cartcount].item.quantity = quantity;

        cart[cartcount].subtotal =
            quantity * menu[found].price;

        total += cart[cartcount].subtotal;

        cartcount++;

        printf("Item added to cart!\n");
    }


    // CHECK EMPTY CART

    if (cartcount == 0)
    {
        printf("No items ordered!\n");
        free(cart);
        return;
    }


    // EXPAND ORDER RECORD MEMORY

    if (!increaseOrderCapacity(ordercount + cartcount))
    {
        free(cart);
        return;
    }


    // SAVE ORDER RECORDS

    if (!saveOrders(cart, cartcount))
    {
        printf("Order could not be saved!\n");
        free(cart);
        return;
    }


    // COPY CART INTO ORDER ARRAY

    for (int i = 0; i < cartcount; i++)
    {
        orders[ordercount] = cart[i];
        ordercount++;
    }


    // REDUCE MENU STOCK

    for (int i = 0; i < itemcount; i++)
    {
        int sold = 0;

        for (int j = 0; j < cartcount; j++)
        {
            if (cart[j].item.foodId == menu[i].foodId)
            {
                sold += cart[j].item.quantity;
            }
        }

        menu[i].quantity -= sold;
    }

    // SAVE UPDATED STOCK

    saveMenu();

    nextorderid++;


    // DISPLAY BILL

    printf("\n========== CUSTOMER BILL ==========\n");

    printf("Order ID: %d\n", orderid);

    for (int i = 0; i < cartcount; i++)
    {
        printf("%s x %d = Rs. %.2f\n",
               cart[i].item.name,
               cart[i].item.quantity,
               cart[i].subtotal);
    }

    printf("-----------------------------------\n");
    printf("Total Bill: Rs. %.2f\n", total);
    printf("Order saved successfully!\n");

    // RELEASE CART MEMORY

    free(cart);
}


// DISPLAY PREVIOUS ORDERS

void displayOrders(void)
{
    if (ordercount == 0)
    {
        printf("No previous orders available!\n");
        return;
    }

    printf("\n----------- ORDER RECORDS -----------\n");

    for (int i = 0; i < ordercount; i++)
    {
        printf("Order ID: %d | Food: %s | Quantity: %d | Bill: Rs. %.2f\n",
               orders[i].orderid,
               orders[i].item.name,
               orders[i].item.quantity,
               orders[i].subtotal);
    }
}


    
