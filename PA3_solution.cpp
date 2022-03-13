#include <iostream> //to use input,output functions
#include <fstream> //for file operations
#include <string> // for string operations
#include <cstdlib>

using namespace std;

//CAN DUYAR - 171044075 

class ImageEditor{ // ImageEditor class
public:
	ImageEditor(); // constructor
	ImageEditor(const ImageEditor &copy); // copy constructor
	~ImageEditor(){/*Body is intentionally empty*/} //destructor
	//GETTERS
	int getRow()const{return row;}
	string getVersion()const{return version;}
	int getMaxRGB()const{return max_rgb;}
	string *getKeep()const{return this->keep;}
	string *getKeep2()const{return this->keep2;}
	string *getMerge()const{return this->keepMerge;}
	//SETTERS
	void setRow(const int row_set){this->row = row_set;this->row2 = row_set;}
	void setVersion(const string version_set){this->version = version_set;this->version2 = version_set;}
	void setMaxRGB(const int rgb){this->max_rgb = rgb;this->max_rgb2 = rgb;}
	void setColumn(const int col){this->column = col; this->column2 = col;}
	//FUNCTIONS
	void openImage(ifstream & file,string filename); //function to open the image-1
	void openImage2(ifstream& file2,string filename2); // function to open the image-2
	void menu(); // menu function
	void saveImageData(ofstream & outfile,string save_file); // function for saving the image-1 data
	void saveImageData2(ofstream & outfile2,string save_file2); // function for saving the image-2 data
	void saveMerge(ofstream & outfile3,string save_file3,ImageEditor &Merge); //function for saving the merged image data
	void convert_grayscale(const float c_r,const float c_g,const float c_b); //function to convert grayscale with coefficients for Image-1
	void convert_grayscale2(const float c_r2,const float c_g2,const float c_b2); //function to convert grayscale with coefficients for Image-2
 	ImageEditor operator+(ImageEditor &img1); // + operator overloading
 	ImageEditor& operator=(const ImageEditor &assign); // assignment operator overloading
	bool Image_control(); // to compare properties of images
private:
	int max_rgb,max_rgb2; //it keeps max value of pixels for image-1 and image-2(in this case,It keeps 250 as max)
	string version,version2; //it keeps the version for image-1 and image-2(in this case,it keeps P3)
	int row,column,row2,column2; // row and column values for image-1 and image-2
	string *keep,*keep2,*keepMerge; // pointers to keep all values for image-1,image-2 and merged imaged
	int numberOfbytes,numberOfbytes2; //it keeps number of bytes(it equals to row*column*3 because each pixel has 3 bytes)
	bool grayscale_control,grayscale_control2; //value of grayscale_control.It defines my saveImageData function's algorithm for image-1 and image-2
};

ImageEditor::ImageEditor(): max_rgb(0),row(0),column(0),numberOfbytes(0),grayscale_control(false){ //Constructor
		/*Body is Intentionally empty*/	
}

ImageEditor::ImageEditor(const ImageEditor &copy){ //copy constructor
	keepMerge = copy.keepMerge;
	keep = copy.keep;
	keep2 = copy.keep2;
	row2 = copy.row2;
	row = copy.row;
	column = copy.column;
	column2 = copy.column2;
	numberOfbytes = copy.numberOfbytes;
	numberOfbytes2 = copy.numberOfbytes2;
	version = copy.version;
	version2 = copy.version2;
	max_rgb = copy.max_rgb;
	max_rgb2 = copy.max_rgb2;
}
																									
/* if two images have same properties(numbers of rows and columns ,image version and max rgb value)
      then returns true otherwise returns false*/
bool ImageEditor::Image_control(){
	if((row == row2) && (column == column2) && (max_rgb == max_rgb2) && (version == version2))
		return true;
	else
		return false;
}

//+ operator overlaoading(to sum two images)
ImageEditor ImageEditor::operator+(ImageEditor &img1){ 
	float temp;
	ImageEditor mergeImag;
	mergeImag.keepMerge = new string[img1.numberOfbytes2+1];
	for(int f = 0;f < img1.numberOfbytes2;f++){
		temp = stof(keep[f]) + stof(img1.keep2[f]);   //converting string to float
		if(temp > 255.00)
			temp = 255.00; // max rgb value
		mergeImag.keepMerge[f] = to_string(temp); // converting float to string
	}
	return mergeImag; 
}

//assignment operator overloading
ImageEditor& ImageEditor::operator=(const ImageEditor &assign){   // Assignment operator overloading
	if(this == &assign)
		return *this;
	keepMerge = assign.keepMerge;
	keep = assign.keep;
	keep2 = assign.keep2;
	row2 = assign.row2;
	row = assign.row;
	column = assign.column;
	column2 = assign.column2;
	numberOfbytes = assign.numberOfbytes;
	numberOfbytes2 = assign.numberOfbytes2;
	version = assign.version;
	version2 = assign.version2;
	max_rgb = assign.max_rgb;
	max_rgb2 = assign.max_rgb2;

	return *this;
}
//MENU FUNCTION
void ImageEditor::menu(){
	
	ifstream file,file2; 
	ofstream outfile,outfile2,outfile3; //for saving file
	ImageEditor merge;
	int main_menu; //for main menu options
	string fn,fn2; // it means filename1 and filename2
	string save_file,save_file2,merge_save;
	string name1,name2; 
	bool loop_control = true; 
	float c_r, c_g, c_b; //coefficients for image-1
	float c_r2, c_g2, c_b2; //coefficients for image-2
	ImageEditor img1,img2; // image-1 and image-2 object

	while(loop_control){ //it works as long as loop_control is not equal to false 
		cout << endl;	
		cout << "MAIN MENU" << endl; //MAIN MENU DESCRIPTION
		cout << "0 - Exit" << endl;
		cout << "1 - Open An Image(D)" << endl;
		cout << "2 - Save Image Data(D)" << endl;
		cout << "3 - Tools(D)" << endl;

		cin >> main_menu;
		cout << endl;

		switch(main_menu){ //It takes main menu option to open submenu. 
			int sub_menu;

			case 0:
				loop_control = false; //to exit from the program.
			break;

			case 1:
			while(true){
				cout << "OPEN AN IMAGE MENU" << endl; //submenu of option 1
				cout << "0 - UP" << endl; //
				cout << "1 - Enter The Name Of The Image-1" << endl;
				cout << "2 - Enter The Name Of The Image-2" << endl;
				if(!(cin >> sub_menu)){ //type of sub_menu is integer so if we enter a type which is different from int
					cin.clear();         // then it exits from the program.
					exit(1);
				}
				// --------------> If sub_menu is an integer then check the following conditions. 							
				if(sub_menu == 0) //UP -> returns to the main menu
					break;

				else if(sub_menu == 1){ //Enter the name of the image file 1.
					cin >> fn;
					openImage(file,fn);
				}
				else if(sub_menu == 2){ //Enter the name of the image file 2.
					cin >> fn2;
					openImage2(file2,fn2);	
				}
				else //it means that sub_menu is an integer which is different from 0,1 and 2.
					exit(1); // exit from the program
    		  }
			break;

			case 2:
			while(true){
				cout << "SAVE IMAGE DATA MENU" << endl;  //submenu of option 2
				cout << "0 - UP" << endl;
				cout << "1 - Enter a File Name To Save First Image" << endl;
				cout << "2 - Enter a File Name To Save Second Image" << endl;
				
				if(!(cin >> sub_menu)){//type of sub_menu is integer so if we enter a type which is different from int
					cin.clear();       // then it exits from the program.
					exit(1);
				}
				// --------------> If sub_menu is an integer then check the following conditions. 							
				if(sub_menu == 0) //UP -> returns to the main menu
					break;
				else if(sub_menu == 1){  //Enter name of the output file 1.
					cin >> save_file;
					saveImageData(outfile,save_file); 
				}
				else if(sub_menu == 2){
					cin >> save_file2; //Enter name of the output file 2.
					saveImageData2(outfile2,save_file2);
				}
				else
					exit(1);
			}
				break;

			case 3:
			int grayscale_menu;
			while(true){
				cout << "TOOLS MENU" << endl; //submenu of option 3
				cout << "0 - UP" << endl; //returns to the main menu.
				cout << "1 - Convert To Grayscale(D)" << endl; // go to convert to grayscale menu
				cout << "2 - Sum Of Two Images" << endl; //go to sum of two images

				if(!(cin >> grayscale_menu)){ //type of grayscale_menu is integer so if we enter a type which is different from int
					cin.clear();       // then it exits from the program.
					exit(1);
				}
				
				if(grayscale_menu == 0) //UP -> returns to the main menu
					break;
			
				else if(grayscale_menu == 1){ //condition for convert to grayscale menu 
					while (true){
					cout << "CONVERT TO GRAYSCALE MENU" << endl; //submenu of option 1 of option 3 
					cout << "0 - UP" << endl;
					cout << "1 - Enter Coefficients of Image-1 For RED GREEN And BLUE Channels" << endl;
					cout << "2 - Enter Coefficients of Image-2 For RED GREEN And BLUE Channels" << endl;
					
					if(!(cin >> sub_menu)){ //type of sub_menu is integer so if we enter a type which is different from int
						cin.clear();       // then it exits from the program.
						exit(1);
					}
					if(sub_menu == 0) //UP -> returns to the script menu 
						break;
					else if(sub_menu == 1){ //Enter the coefficients for image-1. They must be [0,1).Otherwise, exit from the program.
						if(!(cin >> c_r >> c_g >> c_b)){ //types of c_r, c_g, c_b are float so if we enter a type which is different from float
							cin.clear();                 // then it exits from the program.
							exit(1);
						}
						if(c_r >= 0.00 && c_r < 1.00 && c_g >= 0.00 && c_g < 1.00 && c_b >= 0.00 && c_b < 1.00) //it checks the validity of coefficients.
							convert_grayscale(c_r,c_g,c_b); 
						else  // EXIT - INVALID COEFFICIENT for image-1
							exit(1);
					}
					else if(sub_menu == 2){ //Enter the coefficients for image-2. They must be [0,1).Otherwise, exit from the program.
						if(!(cin >> c_r2 >> c_g2 >> c_b2)){ //types of c_r2, c_g2, c_b2 are float so if we enter a type which is different from float
							cin.clear();                 // then it exits from the program.
							exit(1);
						}
						if(c_r2 >= 0.00 && c_r2 < 1.00 && c_g2 >= 0.00 && c_g2 < 1.00 && c_b2 >= 0.00 && c_b2 < 1.00) //it checks the validity of coefficients.
							convert_grayscale2(c_r2,c_g2,c_b2); 
						else  // EXIT - INVALID COEFFICIENT for image-2
							exit(1);
					}				
					else
						exit(1);
				}
			}
			else if(grayscale_menu == 2){   //SUM OF TWO IMAGES
				ifstream image_file1,image_file2;
				cout <<"Enter the name of Image-1 file" << endl;
				cin >> name1; //name of image-1
				cout <<"Enter the name of Image-2 file" << endl;
				cin >> name2; //name of image-2

				
				openImage(image_file1,name1); // to open image-1
				openImage2(image_file2,name2); // to open image-2
				img1.keep = new string[numberOfbytes+1]; //dynamic memory allocation for image-1
				img2.keep2 = new string[numberOfbytes2+1]; // dynamic memory allocation for image-2

				for(int t = 0; t < numberOfbytes; ++t){ //assignment operation
					img1.keep[t] = keep[t];
					img2.keep2[t] = keep2[t];
				}

				img2.numberOfbytes2 = numberOfbytes;
				merge.keepMerge = new string[numberOfbytes2+1];
				img1 = *this;
				merge = img1 + img2;
				cout << "Please, enter a file name to save merged Image: " << endl;
				cin >> merge_save;
				saveMerge(outfile3,merge_save,merge); //to save merged file
			
			}
			else
				exit(1);

			}
				break;	
			default:  //if options of the menu are different from 0-1-2-3 then it exits from the program.
				exit(1);	
			}
	  }
}
//function to convert grayscale for image-1
void ImageEditor::convert_grayscale(const float Cred,const float Cgreen,const float Cblue){
	float temp;
	grayscale_control = true; /* it changes the value of grayscale_control from false to true.It defines 
	my saveImageData function's algorithm */ 
 	for(int t = 0; t < numberOfbytes;t++){
		if(t%3 == 0){ //beginning of a pixel.It means red.
			temp = stof(keep[t])*Cred + stof(keep[t+1])*Cgreen + stof(keep[t+2])*Cblue; //It finds the pixel value according to formula.
			if(temp > 255.00){ //saturated color                                   //I have a string array so I used stof to convert to float.
				temp = 255.00;
			}
			keep[t] = to_string(temp); //RED
			keep[t+1] = to_string(temp); //GREEN
			keep[t+2] = to_string(temp); //BLUE
	    	}
	}
}
//function to convert grayscale for image-2
void ImageEditor::convert_grayscale2(const float Cred,const float Cgreen,const float Cblue){
	float temp;
	grayscale_control2 = true; /* it changes the value of grayscale_control from false to true.It defines 
	my saveImageData function's algorithm */ 

	for(int t = 0; t < numberOfbytes;t++){
		if(t%3 == 0){ //beginning of a pixel.It means red.
			temp = stof(keep2[t])*Cred + stof(keep2[t+1])*Cgreen + stof(keep2[t+2])*Cblue; //It finds the pixel value according to formula.
			if(temp > 255.00){ //saturated color                                   //I have a string array so I used stof to convert to float.
				temp = 255.00;
			}
			keep2[t] = to_string(temp); //RED
			keep2[t+1] = to_string(temp); //GREEN
			keep2[t+2] = to_string(temp); //BLUE
	    	}
		}
}
//to save image data for image-1
void ImageEditor::saveImageData(ofstream & outfile,string save_file){

	outfile.open(save_file);
	outfile << version << endl;                   //  P3
	outfile << row << " " << column << endl;      // row column
	outfile << max_rgb << endl;                   // 255 

	if(grayscale_control == false){ //without convert_grayscale function.  -----> probability - 1
	for(int z = 0; z < numberOfbytes; z++){
		outfile << keep[z].substr(0,5) << " ";
		
		if(keep[z].length() < 3 ){
			if(keep[z+1].length()==1)
				outfile << "  ";  
			else
				outfile << " ";
		}
		if(keep[z].length() == 3 && z%3!=2)
			outfile << " ";
		
		 if(z%3 == 2){ //It means, end of a pixel.
			if(keep[z+1].length() == 3 && keep[z].length() == 3)
				outfile << "  ";
			else
				outfile << "   ";
		}
		if(z%(column*3) == (column*3)-1)
			outfile << endl;

	    }
	}
	  //Probabability 1 and 2 are related with printing shapely
	if(grayscale_control == true){  ////with convert_grayscale function.  -----> probability - 2
		for(int z = 0; z < numberOfbytes; z++){
			if(keep[z][1] == '.'){ // 0.0 ....
				if(z%3!=2)
					outfile << keep[z].substr(0,4) << "   ";
				else if(z%3==2) //It means, end of a pixel.
					outfile << keep[z].substr(0,4) << "     ";
			}
			if(keep[z][2] == '.'){  //10.00 ....
				if(z%3!=2)
					outfile << keep[z].substr(0,5) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile << keep[z].substr(0,5) << "     ";
			}
			if(keep[z][3] == '.'){ // 100.00 ...
				if(z%3 != 2)
					outfile << keep[z].substr(0,6) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile << keep[z].substr(0,6) << "   ";
		}
			if(z%(column*3) == (column*3)-1)
				outfile << endl;
	   }
 	}
 	outfile.close();
 }

// to save image data for image-2
void ImageEditor::saveImageData2(ofstream & outfile2,string save_file2){

	outfile2.open(save_file2);
	outfile2 << version2 << endl;                   //  P3
	outfile2 << row2 << " " << column2 << endl;      // row column
	outfile2 << max_rgb2 << endl;                   // 255 

	if(grayscale_control2 == false){ //without convert_grayscale function.  -----> probability - 1
	for(int z = 0; z < numberOfbytes2; z++){
		outfile2 << keep2[z].substr(0,5) << " ";
		
		if(keep2[z].length() < 3 ){
			if(keep2[z+1].length()==1)
				outfile2 << "  ";  
			else
				outfile2 << " ";
		}
		if(keep2[z].length() == 3 && z%3!=2)
			outfile2 << " ";
		
		 if(z%3 == 2){ //It means, end of a pixel.
			if(keep2[z+1].length() == 3 && keep2[z].length() == 3)
				outfile2 << "  ";
			else
				outfile2 << "   ";
		}
		if(z%(column2*3) == (column2*3)-1)
			outfile2 << endl;

	    }
	}
	                      //Probabability 1 and 2 are related with printing shapely
	if(grayscale_control2 == true){  ////with convert_grayscale function.  -----> probability - 2
		for(int z = 0; z < numberOfbytes2; z++){
			if(keep2[z][1] == '.'){ // 0.0 ....
				if(z%3!=2)
					outfile2 << keep2[z].substr(0,4) << "   ";
				else if(z%3==2) //It means, end of a pixel.
					outfile2 << keep2[z].substr(0,4) << "     ";
			}
			if(keep2[z][2] == '.'){  //10.00 ....
				if(z%3!=2)
					outfile2 << keep2[z].substr(0,5) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile2 << keep2[z].substr(0,5) << "     ";
			}
			if(keep2[z][3] == '.'){ // 100.00 ...
				if(z%3 != 2)
					outfile2 << keep2[z].substr(0,6) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile2 << keep2[z].substr(0,6) << "   ";
		}
			if(z%(column2*3) == (column2*3)-1)
				outfile2 << endl;
	   }
 	}
 	outfile2.close();
 }
 //to save image data for merged image
void ImageEditor::saveMerge(ofstream & outfile3,string save_file3,ImageEditor &Merge){

	if(Image_control()){ //image control condition->if two images have same properties then it works!
		outfile3.open(save_file3);
		outfile3 << version2 << endl;                   //  P3
		outfile3 << row2 << " " << column2 << endl;      // row column
		outfile3 << max_rgb2 << endl;                   // 255 

		for(int z = 0; z < numberOfbytes2; z++){
			if(Merge.keepMerge[z][1] == '.'){ // 0.0 ....
				if(z%3!=2)
					outfile3 << Merge.keepMerge[z].substr(0,4) << "   ";
				else if(z%3==2) //It means, end of a pixel.
					outfile3 << Merge.keepMerge[z].substr(0,4) << "     ";
			}
			if(Merge.keepMerge[z][2] == '.'){  //10.00 ....
				if(z%3!=2)
					outfile3 << Merge.keepMerge[z].substr(0,5) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile3 << Merge.keepMerge[z].substr(0,5) << "     ";
			}
			if(Merge.keepMerge[z][3] == '.'){ // 100.00 ...
				if(z%3 != 2)
					outfile3 << Merge.keepMerge[z].substr(0,6) << " ";
				else if(z%3==2) //It means, end of a pixel.
					outfile3 << Merge.keepMerge[z].substr(0,6) << "   ";
		}
			if(z%(column2*3) == (column2*3)-1)
				outfile3 << endl;
	   }
 	outfile3.close();
 	}

 	else
 		cout << "File could not be saved because file properties don't match!!!" << endl;
 }

void ImageEditor::openImage(ifstream& file,string filename){

	string str; // I used it to read strings.
	ifstream file_comment;
	string comment_control; // to check header comments
	string cc3,cc4; // to check header comments
	string copy_version;
	string comment_temp;
	file.open(filename); // to open the file
	file_comment.open(filename); //to keep header comment line

	if(file.is_open()){
		file_comment >> cc3;
		if(cc3[0] == '#'){
			file >> cc3; // to solve the problem about getline
			getline(file,comment_temp); // it reads whole comment line
		}
		file >> version; // P3

		file_comment >> comment_control >> cc4;
		if(comment_control[0] == '#'){ //it means that file has a header comment line
			file >> comment_control >> cc4; // to solve the problem about getline
			getline(file,comment_temp); // it reads whole comment line
		}

		file >> row;     //row
		file >> column;  //column

		file_comment >> cc4;
			if(cc4[0] == '#'){ //it means that file has a header comment line
				file >> cc4; // to solve the problem about getline
				getline(file,comment_temp); // it reads whole comment line
		}
		file >> max_rgb; // 255
		file_comment.close(); // my file_comment was closed.

		if(row <=0 || column <=0) //row and column values must be greater than 0.Otherwise exit from the program.
			exit(1);
			
		if(version != "P3") //version must be P3.Otherwise,exit from the program.
			exit(1);

		if(max_rgb!=255) //max_rgb must be 255.Otherwise,exit from the program.
			exit(1);

		numberOfbytes = row*column*3; //total bytes number. 
		keep = new string[numberOfbytes+1]; //dynamic memory allocation.

		int i = 0;
		while(!file.eof()){ //reads to the end of the file.
			file >> str;
			keep[i] = str; // I filled keep array with strings
			i++;
		}
	file.close();
	}
	else{ //If there is no file with this name. It can not be opened and exits from the program.
		exit(1);
	}
}

void ImageEditor::openImage2(ifstream& file2,string filename2){
	string str; // I used it to read strings.
	ifstream file_comment2;
	string comment_control2; // to check header comments
	string cc3,cc4; // to check header comments
	string copy_version;
	string comment_temp;
	
	file2.open(filename2); // to open the file
	file_comment2.open(filename2); //to keep header comment line

	if(file2.is_open()){
		file_comment2 >> cc3;
		if(cc3[0] == '#'){
			file2 >> cc3; // to solve the problem about getline
			getline(file2,comment_temp); // it reads whole comment line
		}
		file2 >> version2; // P3
		file_comment2 >> comment_control2 >> cc4;
		if(comment_control2[0] == '#'){ //it means that file has a header comment line
			file2 >> comment_control2 >> cc4; // to solve the problem about getline
			getline(file2,comment_temp); // it reads whole comment line
		}

		file2 >> row2;     // row2 
		file2 >> column2;  // column2
		file_comment2 >> cc4;
			if(cc4[0] == '#'){ //it means that file has a header comment line
				file2 >> cc4; // to solve the problem about getline
				getline(file2,comment_temp); // it reads whole comment line
		}
		file2 >> max_rgb2; // 255
		file_comment2.close(); // my file_comment was closed.

		if(row2 <=0 || column2 <=0) //row and column values must be greater than 0.Otherwise exit from the program.
			exit(1);
	
		if(version2 != "P3") //version must be P3.Otherwise,exit from the program.
			exit(1);

		if(max_rgb2!=255) //max_rgb must be 255.Otherwise,exit from the program.
			exit(1);

		numberOfbytes2 = row2*column2*3; //total bytes number. 
		keep2 = new string[numberOfbytes2+1]; //dynamic memory allocation.
		int t = 0;
		while(!file2.eof()){ //reads to the end of the file.
			file2 >> str;
			keep2[t] = str; // I filled keep array with strings
			t++;
		}
	file2.close();
    }
	else
		exit(1);
}
int main(int argc, char const *argv[])
{
	ImageEditor img;
	img.menu(); 
	return 0;
}


	