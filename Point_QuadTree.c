#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct quad_tree_node q_t; // Instead of struct quadtree, simply write q_t  
typedef struct point pt; // Instead of struct point, simply write pt;

// Declaration of a point 
struct point{
    // X and Y coordinates will be associated with every point
    float x;
    float y;
};

// Declaration of QuadTree Node
struct quad_tree_node{
    // One point will be associated with every quadtree node and each node will further have four children/nodes 
    struct point p;
    struct quad_tree_node * n_e;
    struct quad_tree_node * n_w;
    struct quad_tree_node * s_e;
    struct quad_tree_node * s_w;
};

// Allocation of a new node
q_t * make_node(float x_c, float y_c){
    q_t * new = (q_t *)malloc(sizeof(q_t));
    new->p.x = x_c;
    new->p.y = y_c;
    new->n_e = NULL; // n_e : North East(NE)
    new->n_w = NULL; // n_w : North West(NW)
    new->s_e = NULL; // s_e : South East(SE)
    new->s_w = NULL; // s_w : South West(SW)
    return new;
}

// Insertion of a point in a quadtree
q_t * insert(q_t * root, float key_x, float key_y){
    if(root == NULL){ // check if the node is empty 

        return (make_node(key_x,key_y)); // Make a new node by inserting the point in the node and assigning its four children 
    }

    else
    {
        // Check whether the x & y coordinates of the point(we want to insert) have values less than those of the point of given node
        if(root->p.x >= key_x && root->p.y >= key_y)
            root->s_w = insert(root->s_w, key_x, key_y);// In such case,the new point will be located in SW direction of the node

        // Checking if x and y coordinates of the given point is greater than the point of the node
        else if(root->p.x <= key_x && root->p.y <= key_y)
            root->n_e = insert(root->n_e, key_x, key_y);// the new point will be located in NE direction of the node

        // Checking if x coordinate is greater and y coordinate is smaller than the point of the node
        else if(root->p.x <= key_x && root->p.y >= key_y)
            root->s_e = insert(root->s_e, key_x, key_y);// the new point will be located in SE direction of the node

        // Checking if x coordinate is smaller and y coordinate is greater than the point of the node
        else if(root->p.x >= key_x && root->p.y <= key_y)
            root->n_w = insert(root->n_w, key_x, key_y);// the new point will be located in NW direction of the node
    }
}

// Searching for the given point in the node
void search(q_t * root, float key_x, float key_y){
    if(root == NULL){ // If the node is empty
        printf("\nElement not found \n");
        return;
    }

    if(root->p.x == key_x && root->p.y == key_y){ // if the point of the node is equal to the given point
        printf("\nElement has been found \n");
        return;
    }

    else{ // Searching for the point in the children of the node
        if(root->p.x >= key_x && root->p.y >= key_y)
            search(root->s_w, key_x, key_y); // Searching in SW node

        else if(root->p.x <= key_x && root->p.y <= key_y)
            search(root->n_e, key_x, key_y); // Searching in NE node

        else if(root->p.x <= key_x && root->p.y >= key_y)
            search(root->s_e, key_x, key_y); // Searching in SE node

        else if(root->p.x >= key_x && root->p.y <= key_y)
            search(root->n_w, key_x, key_y); // Searching in NW node
    }
}

// Printing all the points present in the QuadTree
void display(q_t * root){
    if(root == NULL){
        return;
    }

    // If the root is containing a point, then print it, and check for its children
    printf("(%f, %f), ", root->p.x, root->p.y);

    display(root->n_w);
    display(root->s_e);
    display(root->n_e);
    display(root->s_w);
}

// Checking whether the given point lies in the region(formed by four points p1,p2,p3,p4) 
bool in_range(pt p1, pt p2, pt p3, pt p4, float key_x, float key_y){
    if(p1.x <= key_x && p1.y >= key_y && p2.x >= key_x && p2.y >= key_y && p3.x >= key_x && p3.y <= key_y && p4.x <= key_x && p4.y <= key_y)
        return true;

    else 
        return false;
}

// Printing the points present in the given region 
void display_range(pt p1, pt p2, pt p3, pt p4, q_t * root){
    if(root == NULL){
        return;
    }

    if(in_range(p1, p2, p3, p4, root->p.x, root->p.y))
        printf("(%f, %f), ", root->p.x, root->p.y);


    display_range(p1, p2, p3, p4,root->n_w);
    display_range(p1, p2, p3, p4, root->s_e);
    display_range(p1, p2, p3, p4, root->n_e);
    display_range(p1, p2, p3, p4, root->s_w);
}

int main(){
    q_t * root = NULL;

    while(1)
    {
        int choice;

        int quit = 0;

        printf(" \nOperations: \n1. Insert \n2. Search \n3. To display all the points of QuadTree \n4. To display points in a region \n5. Quit\n Enter the operation: ");

        scanf("%d", &choice);

        switch(choice){
            case 1 : {
                float key_x, key_y;
                printf("\nPlease enter the element you want to insert : \nx_coordinate : ");
                scanf("%f", &key_x);
                printf("y_coordinate : ");
                scanf("%f", &key_y);
                //printf("%f, %f \n", key_x, key_y);
                root = insert(root, key_x, key_y);
                //printf("The x pue is : %f %f \n", root->p.x, root->p.y);
                break;
            }

            case 2 : {
                float key_x, key_y;
                printf("Please enter the element you want to search : \nx_coordinate : ");
                scanf("%f", &key_x);
                printf("y_coordinate : ");
                scanf("%f", &key_y);
                search(root, key_x, key_y);
                break;
            }

            case 3 : {
                printf("\nPoints in the Quadtree are: ");
                display(root);
                printf("\n");
                break;
            }

            case 4 : {
                struct point p1, p2, p3, p4;
                printf("Please enter the points (rectangle) in clockwise order \n");
                printf("Enter the top-left most point \n ");
                printf("x_coordinate : ");
                scanf("%f", &p1.x);
                printf("y_coordinate : ");
                scanf("%f", &p1.y);
                printf("Enter the top-right most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p2.x);
                printf("y_coordinate : ");
                scanf("%f", &p2.y);
                printf("Enter the bottom-right most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p3.x);
                printf("y_coordinate : ");
                scanf("%f", &p3.y);
                printf("Enter the bottom-left most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p4.x);
                printf("y_coordinate : ");
                scanf("%f", &p4.y);

                printf("\nPoints in the range are: ");
                display_range(p1, p2, p3, p4, root);
                printf("\n");
                break;
            }

            case 5 : {
                printf("\nThank you for using the program\n");
                quit = 1;
            }
        }

        if(quit == 1){
            break;
        }
    }
}