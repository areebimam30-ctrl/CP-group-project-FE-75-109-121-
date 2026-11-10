
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTURE OF ORDER ITEMS

typedef struct {
    int orderid;
    Food item;
    float subtotal;
} orderitem;


// GLOBAL VARIABLES FOR ORDERS

orderitem *orders = NULL;
int ordercount = 0;
int ordercapacity = 0;

int nextorderid = 1;


// FUNCTION PROTOTYPES

int increaseOrderCapacity(int needed);

void loadOrders(void);
int saveOrders(orderitem cart[], int cartcount);

void takeOrder(void);
void displayOrders(void);


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


