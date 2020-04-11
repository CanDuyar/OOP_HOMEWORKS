#include <iostream> //to use input,output functions
#include <fstream> //for file operations
#include <string> // for string operations

using namespace std;

//CAN DUYAR - 171044075 

class ImageEditor{ // ImageEditor class
public:
	ImageEditor(); // constructor
	void openImage(ifstream & file,string filename); //function to open an image
	void menu(); // menu function
	void saveImageData(ofstream & outfile,string save_file); // function for saving the image data
	void convert_grayscale(const float c_r,const float c_g,const float c_b); //function to convert to grayscale with coefficients
private:
	int max_rgb; //it keeps max value of pixels(in this case,It keeps 250 as max)
	string version; //it keeps the version(in this case,it keeps P3)
	int row,column; // row and column values
	string *keep; // pointer to keep all values
	int numberOfbytes; //it keeps number of bytes(it equals to row*column*3 because each pixel has 3 bytes)
	bool grayscale_control; //value of grayscale_control defines my saveImageData function's algorithm
};

ImageEditor::ImageEditor(): max_rgb(0),row(0),column(0),numberOfbytes(0),grayscale_control(false){ //Constructor
			/*Intentionally empty*/	
}

void ImageEditor::menu(){
	
	ifstream file; 
	ofstream outfile; //for saving file
	int main_menu; //for main menu options
	string fn; // it means file name
	string save_file; 
	bool loop_control = true; 
	float c_r, c_g, c_b; //coefficients

	while(loop_control){ //it works as long as loop_control is not equal to false 
		cout << endl;	
		cout << "MAIN MENU" << endl; //MAIN MENU DESCRIPTION
		cout << "0 - Exit" << endl;
		cout << "1 - Open An Image(D)" << endl;
		cout << "2 - Save Image Data(D)" << endl;
		cout << "3 - Scripts(D)" << endl;

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
				cout << "1 - Enter The Name Of The Image File" << endl;
				if(!(cin >> sub_menu)){ //type of sub_menu is integer so if we enter a type which is different from int
					cin.clear();         // then it exits from the program.
					exit(1);
				}
				// --------------> If sub_menu is an integer then check the following conditions. 							
				if(sub_menu == 0) //UP -> returns to the main menu
					break;

				else if(sub_menu == 1){ //Enter the name of the image file.
					cin >> fn;
					openImage(file,fn);
				}
				else //it means that sub_menu is an integer which is different from 0 and 1.
					exit(1); // exit from the program
					
		  }
			break;

			case 2:
			while(true){
				cout << "SAVE IMAGE DATA MENU" << endl;  //submenu of option 2
				cout << "0 - UP" << endl;
				cout << "1 - Enter A File Name" << endl;
				
				if(!(cin >> sub_menu)){//type of sub_menu is integer so if we enter a type which is different from int
					cin.clear();       // then it exits from the program.
					exit(1);
				}
				// --------------> If sub_menu is an integer then check the following conditions. 							
				if(sub_menu == 0) //UP -> returns to the main menu
					break;

				else if(sub_menu == 1){  //Enter name of the output file.
					cin >> save_file;
					saveImageData(outfile,save_file); 
				}
				else
					exit(1);
			}
				break;

			case 3:
			while(true){
				cout << "CONVERT TO GRAYSCALE MENU" << endl; //submenu of option 3
				cout << "0 - UP" << endl;
				cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels" << endl;
				
				if(!(cin >> sub_menu)){ //type of sub_menu is integer so if we enter a type which is different from int
					cin.clear();       // then it exits from the program.
					exit(1);
				}
			
				if(sub_menu == 0) //UP -> returns to the main menu
					break;

				else if(sub_menu == 1){ //Enter the coefficients. They must be [0,1).Otherwise, exit from the program.
					if(!(cin >> c_r >> c_g >> c_b)){ //types of c_r, c_g, c_b are float so if we enter a type which is different from float
						cin.clear();                 // then it exits from the program.
						exit(1);
					}
					if(c_r >= 0.00 && c_r < 1.00 && c_g >= 0.00 && c_g < 1.00 && c_b >= 0.00 && c_b < 1.00) //it checks the validity of coefficients.
						convert_grayscale(c_r,c_g,c_b); 
					else  // EXIT - INVALID COEFFICIENT
						exit(1);
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

void ImageEditor::openImage(ifstream& file,string filename){

	string str; // I used it to read strings.
	file.open(filename); // to open the file

	if(file.is_open()){
		file >> version; // P3
		file >> row;     // 
		file >> column;  //row column
		file >> max_rgb; // 255

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
int main(int argc, char const *argv[])
{
	ImageEditor img;
	img.menu(); 

	return 0;
}


	