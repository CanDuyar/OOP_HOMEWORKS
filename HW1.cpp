#include <iostream> //header that defines the standart input/output stream objects
#include <string> //I used it for string operations
#include <cstdlib> //I used it to generate random numbers
#include <ctime> // I used it for time operations like srand(time(0))...


//CAN DUYAR - 171044075

using namespace std; // std namespace

//this function checks validity of input. If input is not a digit then it returns false otherwise returns true.
bool valid_input(string input){ //It takes string parameter as input
	for (size_t t = 0; t < input.length(); t++){ 
        if (!isdigit(input[t])) // if input is not a digit then returns false 
            return false;   	
}
  	   return true; // otherwise returns true
}


void generateRandom(int different_digit[10], int digit)
{
    int check[10] = {0};
    int val = (rand() % 9) + 1; // with the help of this part,I can prevent 0.  

    if (check[val] == 0) {
        check[val] = 1;
        different_digit[0] = val;
    }
 
    for (int r = 1; r < digit; r++) {
        while (true) {
            val = rand() % 10; //It generates random numbers between 0 and 9
        
           //main part to generate unique numbers(number which is different from each other)
            if (check[val] == 0) {
                check[val] = 1;
                different_digit[r] = val;
                break;
            }
        }
    }
  //If you want to see the value of secret number then you can use it  
 /* 
    for(int u=0; u < digit; u++)
    	cout << different_digit[u];
  */
    return;
}


//this function returns number of digits of the given number as a parameter
int find_digitNumber(string input_string){
	int input_integer = stoi(input_string); // I used stoi to convert string to integer.
	int digit_numb=1; //It starts from 1 to find total digit number

	while(input_integer >= 10){ // main part to find number of digit
		input_integer/=10;
		digit_numb++;// digit number increases
	}

	return digit_numb; // returns number of digit
}

// if given number is unique(it means all digits are different from each other) then returns true otherwise returns false 
bool is_unique(string guess_number,int digitNumber){
	int ascii;
	int check[10]={0}; // I used it to check that number is unique or not.
	
	for(int i=0; i < digitNumber;i++){
		ascii = guess_number[i];
/*guess_number is a string but check array is integer so I assigned given string to an integer with the help of this way. I
converted character to ascii. I thought that for instance character 2 is equal to 50 as integer. If I substract 48 then
I can get integer 2.
*/
		check[ascii-48]++; //value of check array's specific element increases
		if(check[ascii-48] > 1) // If it has increased before then It can not be an unique number so in this case, it returns false
			return false;
	}
	return true; // Otherwise returns true(It means that it is an unique number)
}

//If secret number has same number which is misplaced with guess number then counter increases 
int misplaced(int different_digit[10],string guess_number,int digitNumber){
	int ascii_numb; 
	int counter = 0; // value of counter starts from 0 to count same number which is misplaced with guess number

for(int u = 0; u < digitNumber; u++){		
	for(int t = 0; t < digitNumber; t++){
		ascii_numb = guess_number[t];
	//I used ascii method like previous function.			
		if(different_digit[u] == (ascii_numb-48) && (different_digit[t]!=ascii_numb-48))
			counter++;

	}
}
	return counter; // It returns counter value

}

// This functions finds value of first_count and prints value of first and second count
void first_second_count(int different_digit[10], string guess_number,int digitNumber){

	int g;
	int ascii_value;
	int first_count = 0; // first count starts from 0
	int second_count;

	second_count = misplaced(different_digit,guess_number,digitNumber);//value of second_count is found by misplaced.

	for(g=0; g < digitNumber;g++){
		ascii_value = guess_number[g];
	//I used ascii method like previous function.			
		if(different_digit[g] == (ascii_value-48)) // If digits' places and values are equal to each other then first_count increases. 
			first_count++;
	}
	if(first_count!=digitNumber)
		cout << first_count << " " << second_count << endl;
	 
}
//If we guess the secret number true then this function returns true, otherwise returns false
bool is_found(string guess_number,int different_digit[10],int digitNumber){
	int convert_ascii;
	int found = 0; //found value starts from 0

	for(int k = 0; k < digitNumber; k++){
		convert_ascii = guess_number[k];
		if(different_digit[k] == (convert_ascii-48)) // if different_digit is equal to gueess number exactly.
			found++; //then value of found increases.
	}

	if(found == digitNumber) //if found value is equal to value of digitNumber then it means that these two numbers are equal(returns true)
		return true;

	else // If these two numbers are not equal(we didn't find secret number) then returns false
		return false;

}

int main(int argc, char const *argv[])
{
	const int max_digit=10; //max digit value is assigned as 10
	int iterations = 0; // it keeps step number of guesses and so starts from 0 
	int different_digit[10] = {0}; // all elements are assigned to 0 to obtain unique number during the following operations 
	int user_mode[10] = {0}; // all elements are assigned to 0 to obtain unique number during the following operations 
	string guess_number;
	string mod_control; //I used it for -r and -u modes
	int digitNum_input;
	string secret_number;
	int digitNumber;
	int ascii_form;
	string user_str;
	int user_digit;

	srand(time(0)); //to generate different numbers for each compile. 

	/**********************************RANDOM MOD****************************/
	if(argc != 3){ // Missing parameter error
		cout << "E0" << endl;
	}
	
	else if(argc == 3 && valid_input(argv[2])){ //If number of parameters is 3 and input is valid then this condition works

		mod_control = argv[1];
		digitNumber = stoi(argv[2]);
		string control = argv[2];		

	if(mod_control == "-r"){ // condition of random mod 
	    if(digitNumber <= 0 || digitNumber >= max_digit){ // we can not try with a digit number which is greater than max digit or negatif value.
			cout << "E0" << endl;
			return 0;
		}
		else if(!valid_input(control)){ //if command line argument is not valid then it prints E0
			cout << "E0" << endl;
			return 0;
		}
		
		else{
			generateRandom(different_digit,digitNumber); // to generate secret number
			while((!is_found(guess_number,different_digit,digitNumber)) && (iterations < 100)){
				cin >> guess_number;

			if(valid_input(guess_number)&& guess_number[0]!='0'){
				digitNum_input = find_digitNumber(guess_number);

			if(is_unique(guess_number,digitNum_input)){
				iterations++;	
				digitNum_input = find_digitNumber(guess_number);

			if(digitNum_input != digitNumber){
				cout << "E1" << endl;
				return 0;
			}
			else if(valid_input(guess_number)){
				first_second_count(different_digit,guess_number,digitNumber);
			}
			else{
				cout << "E2" << endl;
				return 0;
			}
	}
	  else{
		cout << "E1" << endl;
		return 0;
    	}
	}
	   else if(guess_number[0]=='0' || guess_number[0]=='-'){
			cout << "E1" << endl;
			return 0;
		}

		else{
			cout << "E2" << endl;
			return 0;	
		}

	}	
		if(iterations == 100) // if value of iterations is equal to 100 then it prints FAILED
			cout << "FAILED" << endl;

		if(is_found(guess_number,different_digit,digitNumber)) // if we guessed the number correctly then it prints FOUND
			cout << "FOUND " << iterations << endl;
    	}
   }
	/**********************************USER MOD****************************/
	else if(mod_control == "-u"){ // condition of user mod
		user_str = argv[2]; //input of user assigned to user_str
		user_digit = find_digitNumber(user_str);// I found the digit number of user input

		if(is_unique(user_str,user_digit) && user_str[0]!='0'){ // 0. index can not be 0 and user's command line argument should be unique

		for(int z = 0; z < user_digit; z++){
			ascii_form = user_str[z];
			user_mode[z] = ascii_form-48;
		}
		while((!is_found(secret_number,user_mode,user_digit)) && (iterations < 100)){
		  cin >> secret_number;

		if(valid_input(secret_number) && secret_number[0]!='0'){
			digitNum_input = find_digitNumber(secret_number);

		if(is_unique(secret_number,digitNum_input)){
			iterations++; // value of iteration increases	
			digitNum_input = find_digitNumber(secret_number); //it finds the digit number of secret_number

			if((digitNum_input < user_digit && digitNum_input > 0) || digitNum_input > user_digit){
				cout << "E1" << endl;
				return 0;
			}
			else if(valid_input(secret_number)){
				first_second_count(user_mode,secret_number,user_digit);
			}else{
				cout << "E2" << endl;
				return 0;
			}
	}

	 else {
		cout << "E1" << endl;
		return 0;
     } 
  }
   //problem about validity of guess number(that we tried).
 	else if(secret_number[0]== '0' || secret_number[0]== '-'){ 
		cout << "E1" << endl;
		return 0;
	}

	else{
		cout << "E2" << endl;
		return 0;
	}
}	

	if(iterations == 100)// if value of iterations is equal to 100 then it prints FAILED
		cout << "FAILED" << endl;

	if(is_found(secret_number,user_mode,user_digit)) // if we guessed the number correctly then it prints FOUND
		cout << "FOUND " << iterations << endl;
	}
	else{
		cout << "E0" << endl;
		return 0;
	}
  }
	else{
		cout << "E0" << endl;
		return 0;
	}
 }
    else{ // error about command line arguments
		cout << "E0" << endl;
		return 0;
   }
	return 0;
}