// This will allow for input output
#include <stdio.h>
// This will allow for malloc
#include <stdlib.h>

// A Node struct to be used for linked list
struct Node{
    // In this example, data is just an integer; however, you can have as much data as
    // you want. You could have char arrays of a persons name, a int for their age,
    // a floot for their GPA, and etc.
    int data;
    // The * is means that we are going to be creating a pointer.
    // Breaking down the following line we are doing the following :
    // 1. creating a varible of type struct
    // 2. indicating that that struct is Node (can be whatever we name the struct Node is the example name I use)
    // 3. indicating that the varible that we create is going to be a pointer
    // A pointer is a vaule that references another varible
    // int a = 1;
    // int* b = a;
    // b is referenced to the value of a, b holds the address of a, calling &b feteches the value at the address that B holds
    struct Node* head;
    struct Node* tail;
    // Not all linked list require a head and a tail; however, I personally like to make both
    // as it will help when navigating throughout the linked list
};

// CODE FOR EASE OF USE, DON'T WORRY ABOUT THIS
void clearScreen(){ for(int i = 0; i < 20; i++){ printf("\n"); } }
void waitInput(){ int input; printf("Enter Any Number To Continue : "); scanf("%d", &input); }

// A method that returns the head node, takes an arguement of a node pointer, and returns a node pointer
struct Node* fetchHead(struct Node* node){
    // While the head of the node exists, reasign the node to the head of the node
    while (node->head != NULL){ node = node->head; }
    // returning the head of the node
    return node;
}
// Please reference the method 'fetchHead', above, as this is the same logic but just for the tail
struct Node* fetchTail(struct Node* node){
    while (node->tail != NULL){ node = node->tail;}
    return node;
}

// A void method to display the contents of a linked list
void printLinkedList(struct Node* root){
    // Grabbing the head node
    struct Node* node = fetchHead(root);
    // this code is removing a bug
    node = fetchTail(node);node = fetchHead(node);
    // While the node exists, we want to print out the node
    while (node != NULL){
        // printing the node
        printf("%d",node->data);
        // reasinging the node to it's tail
        // because we started with the head node, we only need to worry about going to the tail
        // this logic works both ways as if we set node = fetchTail(root), we would reasing it node->head
        node = node->tail;
        // printing a small visual to show that both parts of the list can be traversed
        if (node != NULL){ printf(" <-> ");}
    } printf("\n");
}

// A void function to push a value to the linked list
void addToTail(struct Node* root, int ID){
    clearScreen();
    // grabbing the current tail node
    struct Node* old_tail_node = fetchTail(root);
    // this code is removing a bug
    old_tail_node = fetchHead(old_tail_node);old_tail_node = fetchTail(old_tail_node);
    
    // visuals for the user, don't worry about this
    printf("\nOld Tail Snapshot : \n");
    if (old_tail_node->head != NULL){printf("-------+    +---+---+------+\n");printf(" %d | o-+----+-o | %d | NULL |\n", old_tail_node->head->data, old_tail_node->data);printf("-------+    +---+---+------+\n");
    }else{printf("+------+---+------+\n");printf("| NULL | %d | NULL |\n", old_tail_node->data);printf("+------+---+------+\n");}
    
    // Creating a new Node pointer which will be our new tail node
    struct Node* new_tail_node = NULL;
    // Assinging the new node to the open space avaible.
    new_tail_node = (struct Node*)malloc(sizeof(struct Node));
    
    // old_tail_node now references the new_tail_node that we created instead of NULL
    old_tail_node->tail = new_tail_node;
    // because want to travel up and down the list, new_tail_node, has a head of the old_tail_node
    new_tail_node->head = old_tail_node;
    // filling out data
    new_tail_node->data = ID;
    // Since this is the last node, it's tail doesn't reference anything, so we set it to NULL
    new_tail_node->tail = NULL;
    
    // visuals for the user, don't worry about this
    printf("\nCurrent Tail Snapshot : \n");
    if (old_tail_node->head != NULL){printf("-------+    +---+---+---+    +---+---+------+\n");printf(" %d | o-+----+-o | %d | o-+----+-o | %d | NULL |\n", old_tail_node->head->data, old_tail_node->data, new_tail_node->data);printf("-------+    +---+---+---+    +---+---+------+\n");
    }else{printf("+------+---+---+    +---+---+------+\n");printf("| NULL | %d | o-+----+-o | %d | NULL |\n", old_tail_node->data, new_tail_node->data);printf("+------+---+---+    +---+---+------+\n");}
    
    // getting a confirmation that the user is ready to continue, than 'clearing' the screen
    waitInput();
    clearScreen();
}
// Please reference the method 'addToTail', above, as this is the same logic but just for the head
void addToHead(struct Node* root, int ID){
    clearScreen();
    // grabbing head
    struct Node* old_head_node = fetchHead(root);
    // this code is removing a bug
    old_head_node = fetchTail(old_head_node);old_head_node = fetchHead(old_head_node);
    // visuals
    printf("\nOld Head Snapshot : \n");
    if (old_head_node->tail != NULL){printf("+------+---+---+    +-------\n");printf("| NULL | %d | o-+----+-o | %d\n", old_head_node->data, old_head_node->tail->data);printf("+------+---+---+    +-------\n");
    }else{printf("+------+---+------+\n");printf("| NULL | %d | NULL |\n", old_head_node->data);printf("+------+---+------+\n");}
    // creating new node
    struct Node* new_head_node = NULL;
    new_head_node = (struct Node*)malloc(sizeof(struct Node));
    // reasinging old_head_node's head
    old_head_node->head = new_head_node;
    // assinging new_head_node's values
    new_head_node->head = NULL;
    new_head_node->data = ID;
    new_head_node->tail = old_head_node;
    // visuals
    printf("\nCurrent Head Snapshot : \n");
    if (old_head_node->tail != NULL){printf("+------+---+---+    +---+---+---+    +-------\n");printf("| NULL | %d | o-+----+-o | %d | o-+----+-o | %d\n", new_head_node->data, old_head_node->data, old_head_node->tail->data);printf("+-----+---+---+    +---+---+---+    +-------\n");
    }else{printf("+------+---+---+    +---+---+------+\n");printf("| NULL | %d | o-+----+-o | %d | NULL |\n", new_head_node->data, old_head_node->data);printf("+------+---+---+    +---+---+------+\n");}
    // confirmation
    waitInput();
    clearScreen();
}

// A void method to remove a node from the linked list
// this is not a true remove, as the node will be removed but still reference the linked this
// I do not completely remove the node because I have 0 be a root node used throughout the code,
// and if the user removes the 0th node, I don't care to have to reasing the root node.
void removeNode(struct Node* root){
    clearScreen();
    printLinkedList(root);
    // collecting an inupt of which node to delete
    int input;
    printf("Enter The ID To Delete : ");
    scanf("%d", &input);
    
    // grabbing the head node
    struct Node* node = fetchHead(root);
    // this code is removing a bug
    node = fetchTail(node);node = fetchHead(node);
    // while the node exists (this should look familiar if you read 'printLinkedList')
    while (node != NULL){
        // if the node has data that is the same as the input exit the loop, if not get the nodes tail
        if (node->data == input){
            break;
        } node = node->tail;
    }
    // if there was no node that had the ID of the user input, than the linked list should have exhausted and our node is NULL
    if (node == NULL){printf("Sorry but %d is not an ID in the link list.\n",input);return;}
    
    // creating two relative values. to remove a node were are
    // going to assing the head of that node, and the tail of
    // the node to reference one another. This means that if
    // for some weird reson we end up at the node we are trying to delete,
    // than we will return to the linked list, hopefully minimizing bugs
    struct Node* relative_head = node->head;
    struct Node* relative_tail = node->tail;
    
    // preventing the user from deleting the last node
    if ((relative_head == NULL)&&(relative_tail == NULL)){printf("Sorry but you can't delete the last node.\n");return;}
    
    // most common case, if the user picks a node that is in the middle of the list
    if ((relative_head != NULL)&&(relative_tail != NULL)){
        // visuals for the user, don't worry about this
        printf("\nOld Index Snapshot : \n");printf("--+---+    +---+---+---+    +-------\n");printf("%d | o-+----+-o | %d | o-+----+-o | %d\n", node->head->data, node->data, node->tail->data);printf("--+---+    +---+---+---+    +-------\n");
        
        // assinging the node's head node tail to the node's tail, and visa versa
        // this can also be done as : node->head->tail = node->tail; node->tail->head = node->head
        // but I felt that this may be a bit harder to understand if you are learning about linked list
        relative_head->tail = relative_tail;
        relative_tail->head = relative_head;
        
        // visuals for the user, don't worry about this
        printf("\nCurrent Index Snapshot : \n");printf("--+---+                     +-------\n");printf("%d | o-+---------------------+-o | %d\n", node->head->data, node->tail->data);printf("--+---+                     +-------\n");printf("     ^     +---+---+---+     ^\n");printf("     +-----+-o | %d | o-+-----+\n",node->data);printf("           +---+---+---+\n");
        
    // less common case of the user wanting to remove the head node
    }else if (relative_head == NULL){
        // visuals for the user, don't worry about this
        printf("\nOld Index Snapshot : \n");printf("+------+---+---+    +-------\n");printf("| NULL | %d | o-+----+-o | %d\n", node->data, node->tail->data);printf("+------+---+---+    +-------\n");
        
        // since there is no head node, as you are trying to remove it, you are tail of the head to NULL
        // this removes the current head from the linked list, but if for some reason we land on the head,
        // we can still return to the linked list
        relative_tail->head = NULL;
        
        // visuals for the user, don't worry about this
        printf("\nCurrent Index Snapshot : \n");printf("+------+---+---+    +----------\n");printf("| NULL | %d | o-+--> | NULL | %d\n", node->data, node->tail->data);printf("+------+---+---+    +----------\n");
        
    // same thing as the if statement above, but instead of for the head it's for the tail
    }else{
        // visuals for the user, don't worry about this
        printf("\nOld Index Snapshot : \n");printf("--+---+    +---+---+------+\n");printf("%d | o-+----+-o | %d | NULL |\n", node->head->data, node->data);printf("--+---+    +---+---+------+\n");
        
        // removing tail
        relative_head->tail = NULL;
        
        // visuals for the user, don't worry about this
        printf("\nCurrent Index Snapshot : \n");printf("--+------+     +---+---+------+\n");printf("%d | NULL | <---+-o | %d | NULL |\n", node->head->data, node->data);printf("--+------+     +---+---+------+\n");
    }
    
    // getting a confirmation that the user is ready to continue, than 'clearing' the screen
    waitInput();
    clearScreen();
}

// A void method to insert a node after an inexed node
void insertNode(struct Node* root, int ID){
    clearScreen();
    printLinkedList(root);
    // this should look familiar if you read 'removeNode'
    int input;
    printf("Enter The ID To Insert After : ");
    scanf("%d", &input);
    
    struct Node* node = fetchHead(root);
    // this code is removing a bug
    node = fetchTail(node);node = fetchHead(node);
    while (node != NULL){
        if (node->data == input){
            break;
        }node = node->tail;
    }if (node == NULL){printf("Sorry but %d is not an ID in the link list.\n",input);return;}
    
    // If the user is inserting after the tail, just run the tail function
    if (node->tail == NULL){addToTail(root, ID);return;}
    
    // since we are inserting after our current node, our tail node is all what extra we need
    struct Node* relative_tail = node->tail;
    // creating a new node
    struct Node* inserted_node = NULL;
    inserted_node = (struct Node*)malloc(sizeof(struct Node));
    // setting our new nodes head to our indexed node
    inserted_node->head = node;
    // setting our new nodes tail to the tail of our indexed node
    inserted_node->tail = relative_tail;
    // setting the new nodes ID
    inserted_node->data = ID;
    
    // By this point, we have a new node that if referenced will bring us into our linked list
    // however, we need to reasing our indexed node, and the tail of our indexed node,
    // to be linked to our new node, or this new node will never be reached
    // setting our indexed node tail to the new node
    node->tail = inserted_node;
    // setting our previous indexed node tail, head to the new node.
    relative_tail->head = inserted_node;
    
    // visuals for the user, don't worry about this
    printf("\nOld Index Snapshot : \n");printf("--+---+                     +---+----\n");printf("%d | o-+---------------------+-o | %d\n",node->data, relative_tail->data);printf("--+---+                     +---+----\n");printf("        +------+---+------+\n");printf("        | NULL | %d | NULL |\n",inserted_node->data);printf("        +------+---+------+\n");printf("\nCurrent Index Snapshot : \n");printf("--+---+                     +---+----\n");printf("%d | o |                     | o | %d\n",node->data, relative_tail->data);printf("--+-+-+                     +-+-+----\n");printf("    |     +---+---+---+       |\n");printf("    +-----+-o | %d | o-+-------+\n",inserted_node->data);printf("          +---+---+---+\n");
    
    // getting a confirmation that the user is ready to continue, than 'clearing' the screen
    waitInput();
    clearScreen();
}

// A print to sum up everything shown here in 20ish lines
void learn(){
    clearScreen();
    printf("BASICS TO LINKED LIST:\n");
    printf("----------------------\n");
    printf("struct Node{\n");
    printf("    int data;\n");
    printf("    struct Node* head;\n");
    printf("    struct Node* tail;\n");
    printf("};\n...\n");
    printf("int main() {\n");
    printf("    struct Node* root = NULL;\n");
    printf("    root = (struct Node*)malloc(sizeof(struct Node));\n\n");
    printf("    struct Node* node = NULL;\n");
    printf("    node = (struct Node*)malloc(sizeof(struct Node));\n\n");
    printf("    root->data = 0;\n");
    printf("    root->tail = node;\n");
    printf("    root->head = NULL;\n\n");
    printf("    node->data = 1;\n");
    printf("    node->tail = NULL;\n");
    printf("    node->head = root;\n...\n}\n");
    waitInput();
    clearScreen();
}

// a print to give the user some extra practice, because this should be a learning tool
void challenges(){
    clearScreen();
    printf("+-----------------------------------------+\n");
    printf("| 0. BUILD YOUR OWN LINKED LIST           |\n");
    printf("| 1. BUILD A LINK LIST THAT LOOPS FOREVER |\n");
    printf("| 2. BINARY TREE LINKED LIST              |\n");
    printf("| 3. SORT A LINK LIST                     |\n");
    printf("| 4. FORK A LINK LIST ( 2 starts one end) |\n");
    printf("+-----------------------------------------+\n");
    waitInput();
    clearScreen();
}

// THE MAIN OF THE CODE
int main() {
    // Inits : input is user inputer, counter is the ID for LL, bc is a break condition in case of emergency since
    // this script is made for novice coders and if they enter an invaild input and don't know how to manually exit the code,
    // I dont want them to freak out
    int input = 1;
    int counter = 1;
    int bc = 0;
    
    // creating a root node
    struct Node* root = NULL;
    // Assinging the root node to the open space avaible.
    root = (struct Node*)malloc(sizeof(struct Node));
    // assinging data to the root node
    root->data = 0;
    root->head = NULL;
    root->tail = NULL;
    
    // main while loop, 0 is the exit condition
    while(input != 0){
        // break conidition as well as visiuals
        if (bc > 99){ printf("FORCE STOP AT 99 ITTERATIONS\n"); return 1; }
        printf("CURRENT LINK LIST :\n");
        printLinkedList(root);
        printf("NEW NODE ID : %d\n",counter);
        printf("+----------------+\n");
        printf("| 0. QUIT        |\n");
        printf("| 1. CLEAR LIST  |\n");
        printf("| 2. ADD TO TAIL |\n");
        printf("| 3. ADD TO HEAD |\n");
        printf("| 4. REMOVE NODE |\n");
        printf("| 5. INSERT NODE |\n");
        printf("| 6. LEARN       |\n");
        printf("| 7. CHALLENGES  |\n");
        printf("+----------------+\n");
        printf("Enter Command : ");
        scanf("%d", &input);
        bc += 1;
        
        // switch case for the user input, the rest should be self explanitory as they call the methods
        switch(input){
            case 0:
                printf("Thank you, goodbye.\n");
                break;
            case 1:
                root->tail = NULL;
                root->head = NULL;
                counter = 1;
                clearScreen();
                break;
            case 2:
                addToTail(root,counter);
                counter++;
                break;
            case 3:
                addToHead(root,counter);
                counter++;
                break;
            case 4:
                removeNode(root);
                break;
            case 5:
                insertNode(root, counter);
                counter++;
                break;
            case 6:
                learn();
                break;
            case 7:
                challenges();
                break;
        }
    }
}
