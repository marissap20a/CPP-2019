#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;


Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  //This function will return a pointer to an array of ints allocated on the heap. The array must be initialized so that all elements have a value of zero in them.
  //The parameter indicates how many elements must be in the returned array. You can also think of this as the size of the array
 // makeZeroedArray(n) returns an array with
  // n items, all set to 0.

    int* seam = new int[length];
    for(int i = 0; i < length; i++)
    {
       seam[i] = 0;
    }
    return seam;
  
  
  
  return nullptr;
}

void deleteSeam(int* seam) {
/*
This function will deallocate the memory for the indicated array, returning its memory to the heap.
The parameter is a pointer to an array of ints on the heap.
*/
 delete [] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream fin;
  fin.open(filename);
  string type_element;
  int width_element = 0;
  int height_element = 0;
  int max_value = 0;
  int final_val = 0;
 
  
  if (!fin) { // error in opening the file
		cout<< "Error: failed to open input file - " << filename << endl;
		return false;
    }
  getline(fin,type_element);
  
  if (type_element != "P3") {
		cout << "Error: type is " << type_element << " instead of P3" << endl;
		return false;
    }
  
  fin >> width_element >> height_element;
  if (width_element != width) {
		cout << "Error: input width (" << width << ") does not match value in file (" << width_element <<")" <<endl;
		return false;
    }
  if (height_element != height) {
		cout << "Error: input height (" << height << ") does not match value in file (" << height_element <<")" <<endl;
		return false;
    }
  fin >> max_value;
 
 for(int j = 0; j < height ; ++j) {
	for (int i = 0; i < width ; ++i) {
		fin >> image[i][j].r;
		fin >> image[i][j].g;
		fin >> image[i][j].b;
		if(!fin.eof() && fin.fail()){
			cout << "Error: read non-integer value" << endl;
			return false;
		}
		if(fin.eof() && fin.fail()){
			cout << "Error: not enough color values" << endl;
			return false;
		}
		if(image[i][j].r < 0 || image[i][j].r > max_value) {
			cout << "Error: invalid color value "<< image[i][j].r << endl;
			return false;
		}
		if(image[i][j].g < 0 || image[i][j].g > max_value) {
			cout << "Error: invalid color value "<< image[i][j].g << endl;
			return false;
		}
		if(image[i][j].b < 0 || image[i][j].b > max_value) {
			cout << "Error: invalid color value "<< image[i][j].b << endl;
			return false;
		}
	}
  }
  fin >> final_val;
  if(!fin.fail()) {
		cout << "Error: too many color values" << endl;
		return false;
	}
return true;	

}



bool outputImage(string filename, Pixel** image, int width, int height) {

  cout << "Outputting image..." << endl;
  // declare/define and open output file stream
  ofstream outFS;
  outFS.open(filename);
  
  // check if output stream opened successfully
  if(!outFS.is_open()) {
	cout << "Error: failed to open output file " << filename;
	return false;
  }
  // output preamble
  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << "255" << endl;
  // output pixels
  for(int j = 0; j < height ; ++j) {
    for (int i = 0; i < width ; ++i) {
		outFS << image[i][j].r << " " << image[i][j].g << " " << image[i][j].b << " ";
		outFS << endl;
	}
  }

  return true;
}
  
  
  
  


int energy(Pixel** image, int x, int y, int width, int height) { 
	/*
	int energy(Pixel** image, int x, int y, int width, int height);
	This function will return the dual-gradient energy of the pixel. How to calculate this is below in the 
	“Computing the energy of a pixel” section below.
	The first parameter is a pointer to a pointer to a Pixel. With this structure we can access our array with the
	[][] notation. Since we are using dynamic arrays, 
	the width is not standard, so we cannot use [][] in the function signature since we would have to specify 
	the array dimensions at compile time, but we get the dimensions (e.g. width) a run time.
	
	The second parameter x is the column which is the first value in the 
	coordinate (x, y).
	
	The third parameter y is the row which is the second value in the 
	coordinate (x, y).
	
	Note you can write a function that prints out a table of the energy for each pixel coordinate. This is a great debugging tool for seeing if your energies are correct.
	Implement
	*/
	int xr = 0;
	int xg = 0;
	int xb = 0;
	int x_tot = 0;
	
	int yr = 0;
	int yg = 0;
	int yb = 0;
	int y_tot = 0;
	
	int energy = 0;
	
	// x y is a corner
	if(x == 0 && y == 0){
		xr = image[x+1][y].r - image[width-1][y].r;
		xg = image[x+1][y].g - image[width-1][y].g; 
		xb = image[x+1][y].b - image[width-1][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		yr = image[x][y+1].r - image[x][height-1].r;
		yg = image[x][y+1].g - image[x][height-1].g; 
		yb = image[x][y+1].b - image[x][height-1].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	if(x == 0 && y == height-1) {
		xr = image[x+1][y].r - image[width-1][y].r;
		xg = image[x+1][y].g - image[width-1][y].g; 
		xb = image[x+1][y].b - image[width-1][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		yr = image[x][y-1].r - image[x][0].r;
		yg = image[x][y-1].g - image[x][0].g; 
		yb = image[x][y-1].b - image[x][0].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		energy = x_tot + y_tot;
		return energy;
	}
		
	if(x == width-1 &&  y == 0) {
		xr = image[x-1][y].r - image[0][y].r;
		xg = image[x-1][y].g - image[0][y].g; 
		xb = image[x-1][y].b - image[0][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		yr = image[x][y+1].r - image[x][height-1].r;
		yg = image[x][y+1].g - image[x][height-1].g; 
		yb = image[x][y+1].b - image[x][height-1].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	if(x == width - 1 && y == height-1) {
		xr = image[x-1][y].r - image[0][y].r;
		xg = image[x-1][y].g - image[0][y].g; 
		xb = image[x-1][y].b - image[0][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		yr = image[x][y-1].r - image[x][0].r;
		yg = image[x][y-1].g - image[x][0].g; 
		yb = image[x][y-1].b - image[x][0].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	// x y is top border
	if(y == 0) {
		
		xr = image[x+1][y].r - image[x-1][y].r;
		xg = image[x+1][y].g - image[x-1][y].g; 
		xb = image[x+1][y].b - image[x-1][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		//cout << x_tot << endl;
		
		yr = image[x][y+1].r - image[x][height-1].r;
		yg = image[x][y+1].g - image[x][height-1].g; 
		yb = image[x][y+1].b - image[x][height-1].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		//cout << y_tot << endl;
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	
	// x y is left border
	if (x == 0) {
		xr = image[x+1][y].r - image[width-1][y].r;
		xg = image[x+1][y].g - image[width-1][y].g; 
		xb = image[x+1][y].b - image[width-1][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		//cout << x_tot << endl;
		
		yr = image[x][y+1].r - image[x][y-1].r;
		yg = image[x][y+1].g - image[x][y-1].g; 
		yb = image[x][y+1].b - image[x][y-1].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		//cout << y_tot << endl;
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	// x y is right border
	if(x == width-1) {
		xr = image[x-1][y].r - image[0][y].r;
		xg = image[x-1][y].g - image[0][y].g; 
		xb = image[x-1][y].b - image[0][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		//cout << x_tot << endl;
		
		yr = image[x][y+1].r - image[x][y-1].r;
		yg = image[x][y+1].g - image[x][y-1].g; 
		yb = image[x][y+1].b - image[x][y-1].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		//cout << y_tot << endl;
		
		energy = x_tot + y_tot;
		return energy;
	}
	
	//x y is bottom border
	if(y == height - 1) {
		xr = image[x+1][y].r - image[x-1][y].r;
		xg = image[x+1][y].g - image[x-1][y].g; 
		xb = image[x+1][y].b - image[x-1][y].b; 
		
		x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
		
		//cout << x_tot << endl;
		
		yr = image[x][y-1].r - image[x][0].r;
		yg = image[x][y-1].g - image[x][0].g; 
		yb = image[x][y-1].b - image[x][0].b; 
		
		y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
		
		//cout << y_tot << endl;
		
		energy = x_tot + y_tot;
		return energy;
	}

	//x y is not an edge case
	xr = image[x+1][y].r - image[x-1][y].r;
	xg = image[x+1][y].g - image[x-1][y].g; 
	xb = image[x+1][y].b - image[x-1][y].b; 
	
	x_tot = pow(xr,2)+pow(xg,2)+pow(xb,2);
	
	//cout << x_tot << endl;
	
	yr = image[x][y-1].r - image[x][y+1].r;
	yg = image[x][y-1].g - image[x][y+1].g; 
	yb = image[x][y-1].b - image[x][y+1].b; 
	
	y_tot = pow(yr,2)+pow(yg,2)+pow(yb,2);
	
	//cout << y_tot << endl;
	
	energy = x_tot + y_tot;		
	return energy;
	
	
	
  return 0;
}




int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  
  int min_energy = 0;
  int tot_energy = 0;
  int curr_col = 0;
  
  min_energy = energy(image, start_col, 0, width, height);
  tot_energy += min_energy;
  seam[0] = start_col;  
  curr_col = start_col;
  
  int left = curr_col + 1;
  int right = curr_col - 1;
  int middle = curr_col;
  int me = 0;
  int le = 0;
  int re = 0;
  
  
  // start left
  for(int row = 1 ; row < height ; ++row) {
	left = curr_col + 1;
    right = curr_col - 1;
    middle = curr_col;
	
	if(curr_col == 0) {
		me = energy(image, middle, row, width, height);
		le = energy(image, left, row, width, height);
		if(me == le) {
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if(me < le) {
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if(le < me) {
			min_energy = le;
			seam[row] = left;
			curr_col = left;
		}
    }
  // start right
    else if(curr_col == width-1) {
		me = energy(image, middle, row, width, height);
		re = energy(image, right, row, width, height);
		if(me == re) {
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if(me < re) {
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if(re < me) {
			min_energy = re;
			seam[row] = right;
			curr_col = right;
		}
		
	}
	else{
	//start at middle
		me = energy(image, middle, row, width, height);
		le = energy(image, left, row, width, height);
		re = energy(image, right, row, width, height);
		if(me == re && le == re) { // all mins are equivalent	
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if((me == le) && me < re) { //middle and left are equal
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		} 
		else if((me == re) && me < le) { //middle and left are equal
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}  
		else if((le == re) && le < me) {
			min_energy = le;
			seam[row] = left;
			curr_col = left;
		}
		else if(me < le && me < re) {
			min_energy = me;
			seam[row] = middle;
			curr_col = middle;
		}
		else if(le < me && le < re) {
			min_energy = le;
			seam[row] = left;
			curr_col = left;
		}
		else if(re < me && re < le) {
			min_energy = re;
			seam[row] = right;
			curr_col = right;
		}
	}
	tot_energy += min_energy;
}
return tot_energy;
}






int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int min_energy = 0;
  int tot_energy = 0;
  int curr_row = 0;
  
  min_energy = energy(image, 0, start_row, width, height);
  tot_energy += min_energy;
  seam[0] = start_row;  
  curr_row = start_row;
  
  int left = curr_row + 1;
  int right = curr_row - 1;
  int middle = curr_row;
  int me = 0;
  int le = 0;
  int re = 0;
  
  
  // start left
  for(int col = 1 ; col < width ; ++col) {
	left = curr_row + 1;
    right = curr_row - 1;
    middle = curr_row;
	
	if(curr_row == 0) {
		me = energy(image, col, middle, width, height);
		le = energy(image, col, left, width, height);
		if(me == le) {
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if(me < le) {
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if(le < me) {
			min_energy = le;
			seam[col] = left;
			curr_row = left;
		}
    }
  // start right
    else if(curr_row == height-1) {
		me = energy(image, col, middle, width, height);
		re = energy(image, col, right, width, height);
		if(me == re) {
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if(me < re) {
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if(re < me) {
			min_energy = re;
			seam[col] = right;
			curr_row = right;
		}	
	}
	else{
	//start at middle
		me = energy(image, col, middle, width, height);
		le = energy(image, col, left, width, height);
		re = energy(image, col, right, width, height);
		if(me == re && le == re) { // all mins are equivalent	
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if((me == le) && me < re) { //middle and left are equal
			min_energy = me;
			seam[col] = middle;
			curr_row= middle;
		} 
		else if((me == re) && me < le) { //middle and left are equal
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}  
		else if((le == re) && le < me) { //***** problem statatement
			min_energy = re;
			seam[col] = right;
			curr_row = right;
		}
		else if(me < le && me < re) {
			min_energy = me;
			seam[col] = middle;
			curr_row = middle;
		}
		else if(le < me && le < re) {
			min_energy = le;
			seam[col] = left;
			curr_row = left;
		}
		else if(re < me && re < le) {
			min_energy = re;
			seam[col] = right;
			curr_row = right;
		}
	}
	tot_energy += min_energy;
}
return tot_energy;
 
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  //set minimall energy to the result of loading the seam for the first column
  int energy;
  int min_energy;
  int* seam = NULL;
  int* min_seam = NULL;
  seam = new int[height];
  min_seam = new int[height];
  energy = loadVerticalSeam(image, 0, width, height, seam);
  
  for(int i = 0; i < height ; ++i) {
	min_seam[i] = seam[i];  
	}
  min_energy = energy;
    
  for (int start_col = 1 ; start_col < width ; ++start_col) {
		energy = loadVerticalSeam(image, start_col, width, height, seam);
		if(energy < min_energy) {
			min_energy = energy;
			for(int i = 0; i < height; ++i) {
				min_seam[i] = seam[i];
			}
		}		
	}
	delete [] seam;
  return min_seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  //set minimall energy to the result of loading the seam for the first column
  int energy;
  int min_energy;
  int* seam = NULL;
  int* min_seam = NULL;
  seam = new int[width];
  min_seam = new int[width];
  energy = loadHorizontalSeam(image, 0, width, height, seam);
  
  for(int i = 0; i < width ; ++i) {
	min_seam[i] = seam[i];  
	}
  min_energy = energy;
    
  for (int start_row = 1 ; start_row < height ; ++start_row) {
		energy = loadHorizontalSeam(image, start_row, width, height, seam);
		if(energy < min_energy) {
			min_energy = energy;
			for(int i = 0; i < width; ++i) {
				min_seam[i] = seam[i];
			}
		}		
		
	}
	delete [] seam;
  return min_seam;
}



void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	//go through each row in the image
	//remove the column designated
	//somehow must deallocate later
	//Pixel**ary = new Pixel[width+1][height];
	//Pixel **ary = new Pixel*[width-1];
		
	int remove_col ;
		
	for(int row = 0; row < height ; ++row) { 
		if(verticalSeam == NULL){
			break;
		}
		remove_col = verticalSeam[row];
		for(int col = 0; col < width; ++ col) {
			if(col < remove_col) {
				image[col][row].r = image[col][row].r;
				image[col][row].g = image[col][row].g;
				image[col][row].b = image[col][row].b;
			}
			else if(col > remove_col) {
				image[col-1][row].r = image[col][row].r;
				image[col-1][row].g = image[col][row].g;
				image[col-1][row].b = image[col][row].b;
				
			}
		}
	}
}
	

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	//go through each row in the image
	//remove the column designated
	//somehow must deallocate later
	//Pixel**ary = new Pixel[width+1][height];
	//Pixel **ary = new Pixel*[width-1];
		
	int remove_row;
		
	for(int col = 0; col < width ; ++col) { 
		remove_row = horizontalSeam[col];
		if(horizontalSeam == NULL){
			break;
		}
		for(int row = 0; row < height; ++row) {
			if(row < remove_row) {
				image[col][row].r = image[col][row].r;
				image[col][row].g = image[col][row].g;
				image[col][row].b = image[col][row].b;
			}
			else if(row > remove_row) {
				image[col][row-1].r = image[col][row].r;
				image[col][row-1].g = image[col][row].g;
				image[col][row-1].b = image[col][row].b;
				
			}
		}
	}
	
}

