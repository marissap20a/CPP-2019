#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
  // Add code to validate input (Do in part 1)  
  cout << "Input filename: ";
  cin >> filename;
  cout << "Input width and height: ";
  cin >> width >> height;
   
   
   if(cin.fail() >> width) {
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<< "Error: width is a non-integer value" << endl;
	return 1;
    }
  if (width <= 0) {
	cout << "Error: width must be greater than 0. You entered " << width << endl;
	return 1;
    }
	
	
	
  if(cin.fail() >> height) {
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<< "Error: height is a non-integer value" << endl;
	return 1;
    }
  
  if (height <= 0){
	cout << "Error: height must be greater than 0. You entered " << height << endl;
	return 1;
    }
	
	
  cout << "Input target width and target height: ";
  cin >> targetWidth >> targetHeight;
 



  if(cin.fail() >> targetWidth) {
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<< "Error: target width is a non-integer value" << endl;
	return 1;
    }
  if (targetWidth <= 0){
	cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl;
	return 1;
	}
  
  if(targetWidth > width) {
	cout << "Error: target width must be less than width, "<< targetWidth << " is greater than "<< width << endl;
	return 1;
    }
	
	
  if(cin.fail()>> targetHeight) {
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout<< "Error: target height is a non-integer valuez" << endl;
	return 1;
    
	}
  if (targetHeight <= 0) {
	cout << "Error: target height must be greater than 0. You entered " << targetHeight<< endl;
	return 1;
	}
  
  if(targetHeight > height) {
	cout << "Error: target height must be less than height, "<< targetHeight << " is greater than "<< height << endl;
	return 1;
    }
  
  int originalWidth = width; // need to delete image array at end of program
  int start_col = 0;
  int start_row = 0;
  cout << "enter start col: ";
  cin >> start_col;
  cout << "enter start row: ";
  cin >> start_row;
  //int* seam_v = NULL;
  //seam_v = new int[height];
  //int* seam_h = NULL;
  //seam_h = new int[width];
  
  int* min_v_en = NULL;
  int* min_h_en = NULL;
  
  Pixel** image = createImage(width, height); // create array of size that we need
  if (image != nullptr) {
    if (loadImage(filename, image, width, height)) {
      cout << "Start carving..." << endl;
      
      // Add code to remove seams from image (Do in part 2)
	  while(width - targetWidth > 0 || height - targetHeight > 0) {
		if(width > targetWidth) {
			cout << width << endl;
			int* seam_v = NULL;
			seam_v = new int[height];
			loadVerticalSeam(image, start_col, width, height, seam_v);
			min_v_en = findMinVerticalSeam(image, width, height);
			removeVerticalSeam(image,width, height, min_v_en);
			delete [] seam_v;
			width -= 1;
		}
		if(height > targetHeight) {
			 int* seam_h = NULL;
			seam_h = new int[width];
			loadHorizontalSeam(image, start_row, width, height, seam_h);
			min_h_en = findMinHorizontalSeam(image,width,height);
			removeHorizontalSeam(image, width, height, min_h_en);
			delete [] seam_h;
			height -= 1;
		}
	  }
	  // set up output filename
      
	  stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
	
  
    // call last to remove the memory from the heap
    deleteImage(image, originalWidth);
	}
  // else 
  
}
}