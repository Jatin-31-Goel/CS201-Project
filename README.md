# Quad Trees

Our project shows the implementation of two types of quadtrees(Point quadtree and region quadtree) which is an adaptation of a binary tree but has four children.

a. Point Quad Tree: 

Operations performed on quadtrees in our project are as follows:

1. Insert Node: This function is used to insert a new point in our quad tree
2. Search node: This function is used to search for a particular point
3. Display : This function is used to display all points that are inserted in the quadtree.
4. Range Query: This function is used to display the points present in the range given by the user.

To support these operations, we have made various supporting functions.

b. Region Quad Tree:

We have implemented image compression using region quadtree.

To download our program, please copy and paste this line to your terminal:
```
git clone https://github.com/Jatin-31-Goel/CS201-Project.git
```
Then type
```
cd CS201-Project
```
### First you will need to decide if you want to simulate 2D Point Quad Tree or Image Compression Quad Tree:
To simulate 2D Points quad tree, type 
``` 
gcc Point_QuadTree.c -o point_quadtree
```
and then type in your terminal :
``` 
./point_quadtree
```


To simulate image compression, refer below.

---

### Steps to run Image Compression
It is expected that your system has OpenCV library installed. If not steps for the same are given below.

***Steps to install OpenCV in python***

Build and install OpenCV in your machine if you already haven't. Here are guides to do the same:
* [For Windows](https://www.geeksforgeeks.org/how-to-install-opencv-for-python-in-windows/)
  
* [For Linux](https://www.geeksforgeeks.org/how-to-install-opencv-for-python-in-linux/)
  
* [For MacOS](https://www.geeksforgeeks.org/how-to-install-opencv-4-on-macos/)
  

After installing OpenCV, to simulate image compression, type in your terminal:
```
python Reading_Actual_Image.py 
```

It will show the actual image which is being saved as ``` to.jpeg ``` and read the image to store pixels in a file as ``` pix.txt ```. 
If the actual image name is not ``` to.jpeg ``` , then, you can change the name in the source code i.e. in the file ``` python Reading_Actual_Image.py ```.


Now, to read the stored pixels  type 
``` 
gcc Image_Compression.c -o image_compression
```
This will generate an output file ***test.exe***. To run this file type in your terminal:
``` 
./image_compression
```
or 
``` 
./image_compression.exe
```
It will store the new pixels in a new file as ``` pix_1.txt```.

 
The updated pixels can now be read usning File Handling in python . Type in your terminal:
``` 
python Creating_Compressed_Image.py
```
This will generate a new compressed image.

---
**Mentor**
Ms. Manpreet Kaur 

**Group Members**
| Name            | Entry Number |
| --------------- | ------------ |
| Jatin Goel | 2022MCB1266  |
| Pranav Menon | 2022CSB1329  |
| Piyush Kumar | 2022MCB1275  |

