#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct qnode qnode;

int rows, columns;

int * p;

struct qnode{
    bool isleaf;
    int north_east;
    int north_west;
    int south_east;
    int south_west;

    int value;
    struct qnode * child[4];
};

struct qnode q_head;

struct qnode * newnode(){
    qnode * node = (qnode * ) malloc (sizeof(qnode));
    node->isleaf = false;
    node->north_east = 0;
    node->south_east = 0;
    node->north_west = 0;
    node->south_west = 0;

    for(int j = 0; j<4; j++){
        node->child[j] = NULL;
    }

    node->value = 0;

    return node;
}

void value_node(qnode * node, int rows, int cols){
    node->north_east = 0;
    node->north_west = cols - 1;
    node->south_east = rows - 1;
    node->south_west = 0;
}


float variance(qnode * node){
    float variance = 0;

    int top = node->north_east;
  
    int left = node->south_west;
  
    int right = node->north_west;
   
    int bottom = node->south_east;
   
    float total_px = (bottom - top + 1) * (right - left + 1);
   
    float average = 0;
   
  float total = 0;

    for(int j = top; j<bottom+1; j++){
        for(int k = left; k<right+1; k++){
            total += p[j*columns + k];
          }
    }

    average = total / total_px;
  
    float total_var;
  
  int f = 0;

    for(int j = top; j<bottom+1; j++){
        for(int k = left; k<right+1; k++){
  
            total_var += (average - p[j*columns + k])*(average - p[j*columns + k]);
  
            f++;
  
        }
    }

    variance = total_var/total_px;
  

    return variance;
}

void splitnode(qnode * node){
  
  int top = node->north_east;
  
  int bottom = node->south_east;
  
  int left = node->south_west;
  
  int right = node->north_west;

  
  node->child[0] = newnode();
  
  node->child[0]->north_east = top;
  
  node->child[0]->south_east = (top+bottom)/2;
  
  node->child[0]->north_west = (left+right)/2;
  
  node->child[0]->south_west = left;

  
    if(left != right){
  
      node->child[1] = newnode();
      
      node->child[1]->north_east = top;
      
      node->child[1]->north_west = right;
      
      node->child[1]->south_east = (top+bottom)/2;
      
      node->child[1]->south_west = (left + right)/2 + 1;
    
    }

    if(top != bottom){

      node->child[2] = newnode();
      
      node->child[2]->north_east = (top+bottom)/2 + 1;
      
      node->child[2]->north_west = (left+right)/2;
      
      node->child[2]->south_east = bottom;
      
      node->child[2]->south_west = left;
    }
  

    if((top != bottom) && (left != right)){
  
      node->child[3] = newnode();
      
      node->child[3]->north_east = (top+bottom)/2 + 1;
      
      node->child[3]->north_west = right;
      
      node->child[3]->south_east = bottom;
      
      node->child[3]->south_west = (left+right)/2 + 1;
    }
  
}



void build_quadtree(qnode * node, int threshold){
  
    if(node == NULL){
  
      return;
    
    }

    float variance_ = sqrt(variance(node));
    
      if(variance_ > threshold){
  
        splitnode(node);

        build_quadtree(node->child[0], threshold);

        build_quadtree(node->child[1], threshold);

        build_quadtree(node->child[2], threshold);

        build_quadtree(node->child[3], threshold);
    }

    else{
        
      int top = node->north_east;
      
      int left = node->south_west;
      
      int right = node->north_west;
      
      int bottom = node->south_east;

        int total_px = (bottom - top + 1) * (right - left + 1);

      int average = 0;
      
      int total = 0;
      
        for(int j = top; j<=bottom; j++){
      
          for(int k = left; k<=right; k++){
            
            total += p[j*columns + k];
          
            
            }
        }
       
       
      average = total / total_px;

      
      node->value = average;
              
        node->isleaf = true;
    
    }
}

int num_nodes(qnode * node){
    
  if(node == NULL){
  
    return 0;
    
  }    

    
    else if(node->isleaf == true){
    
      return 1;
    
    }

    else{
    
      return num_nodes(node->child[0]) + num_nodes(node->child[1]) + num_nodes(node->child[2]) + num_nodes(node->child[3]);
     }
  
}


void New_pix(qnode * node){
    

    if(node == NULL){

      return;
    }

    else if(node->isleaf == true){
      
      int top = node->north_east;
      
      int left = node->south_west;
      
      int right = node->north_west;
      
      int bottom = node->south_east;

        int value = node->value;
      
       for(int j = top; j<=bottom; j++){
      
         for(int k = left; k<=right; k++){
         
           p[j*columns + k] = value;
           
         }
        }
    }

    else{
        
      New_pix(node->child[0]);
      
      New_pix(node->child[1]);
      
      New_pix(node->child[2]);
      
      New_pix(node->child[3]);
    }
  
}

int main(){
  
  FILE * fptr = fopen("to_compress.txt", "r");

    if(fptr == NULL){
  
      printf("File cannot be opened");
    }
  

    int num_pix = 241402;

    columns = 602;
    rows = 401;
    p = (int *) malloc (sizeof(int)*num_pix);

    for(int i = 0; i<num_pix; i++){
        fscanf(fptr, "%d \n", &p[i]);
    }

   /* for(int i = 0; i<num_pix; i++){
        printf("%d , ", p[i]);
    }*/

    int threshold;

    printf("Please enter the threshold (between 0 and 255): ");
    scanf("%d", &threshold);    

    qnode * node; 
    
    node = newnode();

    value_node(node, rows, columns);

    //printf("The total variance is %f : ", variance(node));

    fclose(fptr);

    build_quadtree(node,threshold);

    int e = num_nodes(node);

    printf("\nThe split nodes are : %d \n", e);

    int f = rows * columns;

    printf("The no of pixels are : %d \n", f);

    float j = f-e;
    float k = (j/f) * 100;

    printf("\nThe percentage compression is : %f \n", k);

    New_pix(node);

    fptr = fopen("final_compress.txt", "w");
    if(fptr==NULL){
        printf("NULL");
    }

    for(int i = 0; i<num_pix; i++){
        fprintf(fptr, "%d\n", p[i]);
    }


    return 0;
}
