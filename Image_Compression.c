#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include<math.h>

typedef struct qnode qnode; // Instead of struct qnode, simply write qnode

int rows, columns; // rows and columns of array matrix of pixels 
int * p; // 2D array of pixels

// Declaration of QuadTree Node
struct qnode{
    bool isleaf;// Determines whether the complete node is assigned a single value or it is spliited further containg different values in the four nodes
    
    int north_west; // contains the left topmost index of the pixel array (will always be zero)
    int north_east; // contains the right topmost index of the pixel array (will always contain the no. of columns)
    int south_west; // contains the left bottommost index of the pixel array (will always contain the no. of rows)
    int south_east; // contains the right bottommost index of the pixel array (will always be zero)

    int value; // value associated with the complete node after the variance becomes below the threshold value 
    qnode * child[4];// Four Children in the Four Directions
};

qnode q_head;

// Allocation of a new node
qnode * newnode(){
    qnode * node = (qnode *) malloc (sizeof(qnode));
    node->isleaf = false; // Initially the node will not be empty : it will become a leaf only when its further splitting is not required
    
    node->north_west= 0;
    node->north_east = 0;
    node->south_west = 0;
    node->south_east = 0;

    // Four children will be initiated with NULL Value
    for(int j = 0; j<4; j++)
        node->child[j] = NULL;
  
    node->value = 0;
    return node;
}

// Assigning the values in the newly made node as it has not been done in its allocation 
void value_node(qnode * node, int rows, int cols)
{
    node->north_west = 0;
    node->north_east = cols - 1;
    node->south_west = rows - 1;
    node->south_east = 0;
}

float variance(qnode * node)
{
    float variance = 0;

    // four variables made for iterating from left to right and from top to bottom
    int top = node->north_west; // top = starting index with 0
    int bottom = node->south_west; // bottom = no. of rows
    int left = node->south_east; // left = starting index with 0
    int right = node->north_east; // right = no. of columns 
   
    float total_px = (bottom - top + 1) * (right - left + 1); // total pixels = rows*columns

    float total = 0; // will count the sum of all the pixels
    for(int j = top; j<=bottom; j++){
        for(int k = left; k<=right; k++){
            total += p[j*columns + k];
          }
    }

    float average = 0;
    average = total / total_px; // sum of all the pixels of the node divided by total no. of pixels
  
    float total_var; // Total variance = sum of squares of the difference between given value and average value  
    int f = 0;
    for(int j = top; j<bottom+1; j++) // iterating through rows
    { 
        for(int k = left; k<right+1; k++) // iterating through columns
        {
            total_var += (average - p[j*columns + k])*(average - p[j*columns + k]);
            f++;
        }
    }
    
    variance = total_var/total_px; // variance  = sum of variance of individual pixel divided by total no. of pixels
    return variance; // returning the variance of the whole node
} 

void splitnode(qnode * node)
{
  
  int top = node->north_west;
  int bottom = node->south_west;
  int left = node->south_east;
  int right = node->north_east;

  // child[0] being the child in the northwest direction of the node
  node->child[0] = newnode();  
  node->child[0]->north_west = top;
  node->child[0]->south_west = (top+bottom)/2;
  node->child[0]->north_east = (left+right)/2;
  node->child[0]->south_east = left;

    if(left != right)
    {
      // child[1] being the child in the northeast direction of the node
      node->child[1] = newnode();      
      node->child[1]->north_west = top;
      node->child[1]->north_east = right;
      node->child[1]->south_west = (top+bottom)/2;
      node->child[1]->south_east = (left + right)/2 + 1;
    }
 
    if(top != bottom)
    {
      // child[2] being the child in the southwest direction of the node
      node->child[2] = newnode();
      node->child[2]->north_west = (top+bottom)/2 + 1;
      node->child[2]->north_east = (left+right)/2;
      node->child[2]->south_west = bottom;
      node->child[2]->south_east = left;
    }
  
    if((top != bottom) && (left != right))
    {
      // child[3] being the child in the southeast direction of the node
      node->child[3] = newnode();
      node->child[3]->north_west = (top+bottom)/2 + 1;
      node->child[3]->north_east = right;
      node->child[3]->south_west = bottom;
      node->child[3]->south_east = (left+right)/2 + 1;
    }  
}

// making of a Quadtree
void build_quadtree(qnode * node, int threshold)
{  
    if(node == NULL)
      return;

    float variance_ = sqrt(variance(node));
    
    if(variance_ > threshold)
    {
      splitnode(node);

      build_quadtree(node->child[0], threshold);
      build_quadtree(node->child[1], threshold);
      build_quadtree(node->child[2], threshold);
      build_quadtree(node->child[3], threshold);
    }

    else
    {    
      // Variance comes out to be less than threshold value 
      int top = node->north_west;
      int left = node->south_east;
      int right = node->north_east;
      int bottom = node->south_west;

      int total_px = (bottom - top + 1) * (right - left + 1);

      int average = 0;
      
      int total = 0;
      
        for(int j = top; j<=bottom; j++)
        {
          for(int k = left; k<=right; k++)          
          {
              total += p[j*columns + k];
          }
        }
              
      average = total / total_px;
      node->value = average; // making value of every pixel of the node to be equal to the average value 
              
      node->isleaf = true; // making the node to be leaf as no further division is required since the variance comes out to be less than threshold
    
    }
}

int num_nodes(qnode * node) // it will return the no. of nodes that have been made while splitting 
{    
  if(node == NULL) 
  {
    return 0;  
  }    

  else if(node->isleaf == true) // if the node is a leaf,then,it will be counted as a single node 
  {
    return 1;
  }

  else // all the four nodes will be counted
  {
    return num_nodes(node->child[0]) + num_nodes(node->child[1]) + num_nodes(node->child[2]) + num_nodes(node->child[3]);
  } 
}

// Updating the pixels of the node 
void New_pix(qnode * node)
{
  if(node == NULL)
    return;

  else if(node->isleaf == true)
  {
    // when the node becomes a leaf, then, the whole node will be assigned a single value  
    int top = node->north_west;
    int left = node->south_east;
    int right = node->north_east;
    int bottom = node->south_west;

    int value = node->value; 
    for(int j = top; j<=bottom; j++)
    {  
      for(int k = left; k<=right; k++)
      { 
        p[j*columns + k] = value;      // Updating the Pixel array
      }
    }
  }

  else
  {      
    New_pix(node->child[0]);  
    New_pix(node->child[1]);
    New_pix(node->child[2]);
    New_pix(node->child[3]);
  }
}

int main()
{  
  FILE *fptr = fopen("pix.txt", "r"); // 'pix.txt' being the file storing the value of pixels of the image

  if(fptr == NULL) // if can't find such a file
  {
    printf("File cannot be opened");
  }

  fscanf(fptr,"%d",&rows); // first line of 'pix.txt' contains the no. of rows 
  fscanf(fptr,"%d",&columns); // second line of 'pix.txt' contains the no. of columns
  int num_pix = rows*columns; // storing the total no. of pixels

  // making the pixel array
  p = (int *) malloc (sizeof(int)*num_pix);  
  for(int i = 0; i<num_pix; i++)
  {
    fscanf(fptr, "%d \n", &p[i]);
  }

  // User will enter the threshold value according to which compression will be done
  int threshold;
  printf("Please enter the threshold (between 0 and 255): ");
  scanf("%d", &threshold);     

  qnode * node; 
  node = newnode();
  value_node(node, rows, columns);

  fclose(fptr); // Closing the file pointer as the pixel values have been read

  build_quadtree(node,threshold);

  int e = num_nodes(node);

  printf("\nThe split nodes are : %d \n", e); // Gives the total no. of nodes that have been made

    int f = rows * columns;
    printf("The no of pixels are : %d \n", f); 

    float j = f-e; 
    float k = (j/f) * 100;

    printf("\nThe percentage compression is : %f \n", k);

    New_pix(node);
    
    // Using File Handling, to store the new pixel array in a new file 'pix_1.txt'
    fptr = fopen("pix_1.txt", "w"); 
    if(fptr==NULL)
      printf("NULL");

    for(int i = 0; i<num_pix; i++)
    {
        fprintf(fptr, "%d\n", p[i]);
    }


    return 0;
}
