#include<stdio.h>
//orders and billing
//......STRUCTURE OF FOOD ITEM AND ORDER ITEM.....//
typedef struct {
    int id,quantity;
    char name[50],category[50];
    float price;
} fooditem;
typedef struct {
    int orderid;
    fooditem item;
    float subtotal;
} orderitem;
//......FUNCTION FOR ORDER.....//
void takeorder(fooditem items[],int count,orderitem orders[],int *ordercount,int *nextorderid){
orderitem cart[100];
int cartcount=0;
int orderid, foodid, quantity,found;
char foodname[50];
float total=0.0;
//generate order id
orderid = *nextorderid;
printf("Order ID: %d\n", orderid);
//take order inputs
printf("Enter food item ID to order (0 to finish): ");
while(1){
    scanf("%d",&foodid);

    if(foodid==0){
        break;
    }
//search for food item in the menu
found=-1;
for(int i=0;i<count;i++){
    if(items[i].id==foodid){
        found=i;
        break;
    }
}
if(found==-1){
    printf("Food item not found!\n");
    printf("enter foodid again\n");
    continue;
}
//ask for quantity
printf("Enter quantity: ");
scanf("%d",&quantity);

if(quantity<=0){
    printf("Invalid quantity!\n");
    continue;
  }
}
//check previously ordered quantity for the same food item
int alreadyOrderedQuantity = 0;
for(int j=0;j<cartcount;j++){
    if(cart[j].item.id == foodid){
        alreadyOrderedQuantity += cart[j].item.quantity;
    }
//check stock availability
if(quantity+alreadyOrderedQuantity > items[found].quantity){
    printf("Not enough stock available!\n");
    continue;
   }
if(cartcount>=100){
    printf("Cart is full!\n");
    break;
  }
}
//store order details in cart
cart[cartcount].orderid = orderid;
cart[cartcount].item = items[found];

//store quantity and calculate subtotal
cart[cartcount].item.quantity = quantity;
cart[cartcount].subtotal=quantity * items[found].price;
total += cart[cartcount].subtotal;
cartcount++;
printf("item added to cart!\n");

//check if customer ordered any items
if(cartcount==0){ 
    printf("No items ordered!\n");
    return;
}
// check order limit
if(*ordercount + cartcount > 100){
    printf("Order limit exceeded!\n");
    return;
 }
}

int main(){
    fooditem items[100];
orderitem orders[100];

int count = 0;
int orderCount = 0;
int nextOrderId = 1;


  takeorder(items, count, orders,
              &orderCount, &nextOrderId);

}

