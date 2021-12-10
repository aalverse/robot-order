
#include "automate.h"

/**
 * @brief A typedef of boolean 
 */
typedef enum {false, true} boolean;

typedef struct FoodNode{
    char *data; // Food Item Name
    struct FoodNode * next; // Food next pointer
}FoodNode;

typedef struct OrderList{
    FoodNode *head; // Pointer to first food item for the order (alphabetical)
    int size; // Number of food items in the order
} OrderList;

typedef struct RobotOrder{
    unsigned int robotNum;
    OrderList *data;
    char *deliverTo;
    char *restaurant;
    struct RobotOrder *next;
} RobotOrder;

/**
 * @brief prototypes
 * 
 * @return RobotOrder* 
 */
RobotOrder * newDelivery();
boolean isEmpty(char string[]);
FoodNode * newFoodNode();
FoodNode *  addFoodItem(RobotOrder * robot, FoodNode * food);
void recursivePrint(RobotOrder * robot);
FoodNode * freeOrderList(FoodNode * order);
RobotOrder * freeRobotList(RobotOrder * robot);
void dynamicFree();

/* Head pointer for linked list */
RobotOrder * head;

/**
 * @brief prints '\n' on console
 * 
 */
void ln(){
    printf("\n");
}

/**
 * @brief allocates memory with a check for successful allocation
 * 
 * @param size 
 * @return void* 
 */
void *dmalloc(size_t size){
void *p = malloc(size);
    if(!p){
        printf("memory allocation failed\n");
        exit(1);
    }
    return p;
}

/**
 * @brief This program dmallocs the orderlist
 * 
 * @param order 
 * @return OrderList* 
 */
OrderList * newOrder(){
    return dmalloc(sizeof(OrderList));
}

char * requestInput(char * question){
    char answer[DEFAULT_BUFFER_SIZE];
    char * store = malloc(DEFAULT_BUFFER_SIZE * sizeof(char));
    printf("%s", question);
    fgets(answer,DEFAULT_BUFFER_SIZE,stdin); 
    if( !strcmp(answer, "\n")){
        strcpy(store, "");    
    }else{
        strcpy(store, answer);
    }
    
    return store;
}

int requestInteger(char * question){
    int number;   
    printf("%s", question);
    scanf("%d", &number);
    return number;
}

char requestChar(char * question){
    char input;
    printf("%s", question);
    scanf("%c", &input);
    return input;
}

RobotOrder * initateDelivery(RobotOrder * robot){
    fflush(stdin);
    ln();
    robot->robotNum = requestInteger(CYAN "Robot Number: "MAGENTA);  
    ln();
    fflush(stdin);
    fflush(stdout);
    robot->deliverTo = requestInput(CYAN "Delivery Address for new delivery order: "MAGENTA);
    ln();
    robot->restaurant = requestInput(CYAN "Restaurant from which to pick up food: "MAGENTA); 

    ln();
    char * foodItem = requestInput(CYAN "Food Item: "MAGENTA);

    while(strcmp(foodItem, "") > false){
        FoodNode * food = newFoodNode();
        food->data = foodItem;
        addFoodItem(robot, food);
        foodItem = requestInput(CYAN "Food Item: "MAGENTA);
    }

    ln();
    return robot;
}

boolean isEmpty(char string[]){
    int i;
    for(i = 0; i < strlen(string); i++ ){
        printf(RED "%d - " RESET, string[i]);
        if(string[i] != ' '){
            return false;
        }
        
        if(string[i] == '\n'){
            // printf(RED "%d < STRLEN\n", strlen(string));
            string[i] = ' ';
            return true;
        }
    }
    ln();
    return true;
}

int incrementRobotOrder(RobotOrder * robot){
    return robot->data->size++;
}

FoodNode *  addFoodItem(RobotOrder * robot, FoodNode * food){
    if(robot == NULL) return NULL;

    if(robot->data == NULL){
        robot->data = dmalloc(sizeof(OrderList));
        robot->data->head = food;
        incrementRobotOrder(robot);
        return robot->data->head;
    }

    FoodNode * ptr = robot->data->head;

    while (ptr->next!=NULL){
        ptr = ptr->next;
    }

    if(ptr->next == NULL){
        ptr->next = food;
        incrementRobotOrder(robot);
        return ptr->next;
    }
    
    return NULL;
}

FoodNode * newFoodNode(){
    return dmalloc(sizeof(FoodNode));
}


int askForDelivery(){
top: 
    switch(requestChar(BLUE "New delivery order? (y/n) - " RESET)){
        case 'y':
            initateDelivery(newDelivery());
            goto top;
            break;
        case 'n':
            printf(RED "\n\t\tOrder Summary\n" RESET);
            printf("-------------------------------------------\n");

            recursivePrint(head);
            dynamicFree();
            printf("\nExiting program\n");
            exit(0);
            break;
        default:
            ln();
            printf("Error: Invalid reply");
            ln();
            goto top;
    }

    return 0;
}

RobotOrder * newDelivery(){
    if (!head){
        head = dmalloc(sizeof(RobotOrder));
        return head;
    }

    RobotOrder * neworder = dmalloc(sizeof(RobotOrder));
    neworder->next = head;
    head = neworder;

    return neworder;
}

void printRobotOrder(RobotOrder * order){
    if(order == NULL) return;
    FoodNode * food = order->data->head;
    ln();
    while(food){
        printf(YELLOW "Food Item: %s" RESET, food->data);
        food = food->next;
    }
}

void recursivePrint(RobotOrder * robot){
    if (robot == NULL) {
        printf("\nEmpty Order List\n");
        return;
    }

    ln();ln();
    printf(BLUE "Robot Number: %d Delivery order from '%s' has %d food item(s)", robot->robotNum, robot->restaurant, robot->data->size);
    printRobotOrder(robot);
    printf(CYAN "Deliver To: %s \n", robot->deliverTo);
    if(robot->next!=NULL){recursivePrint(robot->next);}
}

/**
 * @brief prints Welcome message on console
 */
void intro(){
    ln();
    printf("*****************************************************");
    ln();
    ln();
    printf(PURPLE "* Welcome to GMU's Starship Robots Delivery");
    ln();
    printf("* Central Dispatch System" RESET);
    ln();
    ln();
    printf("*****************************************************");
    ln();
    ln();
}

void dynamicFree(){
    freeRobotList(head);
}

RobotOrder * freeRobotList(RobotOrder * robot){
    if(robot == NULL){return NULL;}

    freeOrderList(robot->data->head);
    free(robot->data);
    free(robot->deliverTo);
    free(robot->restaurant);

    if (robot->next!=NULL){
        freeRobotList(robot->next);
    }

    free(robot);
    return robot;
}

/**
 * @brief frees the Linked list dyamically
 * 
 * @param order 
 * @return FoodNode* 
 */
FoodNode * freeOrderList(FoodNode * order){
    if (order == NULL){return NULL;}
    
    free(order->data);
    if(order->next!=NULL){
        freeOrderList(order->next);
    }
    free(order);
    return order;
}

/**
 * @brief prints food item
 * 
 * @param name 
 */
void printFoodItem(char * name){
    printf(YELLOW "\nFood Item: ");
    printf(BLUE "%s\n" RESET, name);
}

// void newDelivery(){
//     ln();
//     printf("New delivery order? (y/n)");
//     ln();
// }

int main(){
    intro();
    ln();
    // printf("\n%d<-------\n", isEmpty(requestInput("input: ")));
    askForDelivery(); 
    // printf(GREEN"\n\n%d: %s %s : %d"RESET, head, head->deliverTo, head->restaurant, head->robotNum);
    // recursivePrint(head);

    // recursivePrint(head);
    ln();
    return 0;   
}
