/*  Kaan Yuecel
	C++ Fall 2021
	Due: 9/29/21
    Lab Name: Lab 6 Binary to Decimal Conversion
    Description: Write a C++ program that reads characters representing binary (base 2)
    numbers from a data file called BinaryIn.dat and translates them to decimal (base 10)
    numbers. The binary and decimal numbers should be output in two columns with
    appropriate headings. Here is a sample of the input and output:

    There is only one binary number per input line, but an arbitrary number of blanks can
    precede the number.  The program must read the binary numbers one character at a
    time.  As each character is read, the program multiplies the total decimal value by 2 and
    adds either a 1 or 0, depending on the input character.  The program should check for
    bad data; if it encounters anything except a 1 or 0, it should output the message “Bad
    digit on input.”  The maximum number of spaces that could exist between any two digits
    of a binary number in the input file will be one, in which case, the binary digit would be
    considered bad.  The output for this program should be to the screen and not an output
    file.  In order to read in one character at a time, you will need to use the cin.get
    command.  When you have completed this lab, upload a copy of the .cpp file called
    Lab6.cpp and BinaryIn.dat to GitHub.
*/



#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;



void CheckFile (ifstream& inFile);
//Pre: The function is passed a input stream variable
//Post: Function opens succesfully or terminates because wrong input file


void RemoveLeadingZeros(ifstream& inFile, char& input, int& position);
//Pre: Input cursor encountered 0 in the first position of input file
//Post: The function move the input cursor forward to the first significant digit (i.e. 1) or detect an error in the input stream.


void AddToTotal(int& total, char input, int& position, string& binaryNum);
//Pre: The input stream has read a character from the input file that is either a '1' or a '0'.
//Post: The function updates the location of the decimal total for the conversion from binary to decimal.

void PrintTable(int total, string binaryNum);
//Pre: The main function has successfully read in a series of binary numbers, stored them to a string called binaryNum and converted the binary to a decimal number
//Post: The function will output a table with the binary number that has been read in with its decimal equivalent


int DecimalPlaceValue(int total);
//Pre: The main function has successfully calculated a decimal number called total which is passed to the function by value
//Post: Function returns the number of place values in the decimal number


void ResetCounters(int& total, int& position, string& binaryNum);
//Pre: The while loop has either encountered the end of a line or an error in the input stream
//Post: Function resets the values of counters that are used during program execution.


int main()
{
	ifstream inFile;

	cout << setw(22) << "Binary Number:" << setw(24) << "Decimal Equivalent:" << endl; //Heading for output

	CheckFile(inFile);

	char input; //Reads the characters
	int total = 0; //Stores the decimal equivalent of the input
	int position = 0; //Counter that keeps track of input cursor position (detects spaces in binary numbers)
	string binaryNum = ""; //Empty string to store input chars for binary number as they're read from input file.

	while (inFile.get(input) || (total != 0)) { //While the input stream is valid OR there is a running total for a decimal number

		if (input == '0' && position == 0) { //If a 0 is read on the first space of a line
			RemoveLeadingZeros(inFile, input, position);
		}

		if ((input == '\n' && position > 0) || (!inFile)) { //If file input cursor has read a new line where the position is atleast one OR reached end of file (a complete line of binary)

			//Prints output to table in the console.
			PrintTable(total, binaryNum);

			//Resets counters for the next line of input
			ResetCounters(total, position, binaryNum);
		}
		else if (input == '1' || input == '0') { //If input char is a '1' or a '0'.
			AddToTotal(total, input, position, binaryNum);
		}
		else if (input == '\n' && position == 0) { //If the cursor reads a newline character on the first spot for a character (Finds a blank line)

			continue; //Re-evaluate logic from beginning of the loop with a new character.
		}
		else if ((int(input) < '0' || int(input) > '1') && (input != ' ') || (input == ' ' && position > 0)) { //If the ASCII code for input is less than '0' or greater than '1' AND NOT a space (32 is ASCII code for ' ') OR there is a space in a binary number when position > 0

			//Error Message
			cout << setw(24) << "Bad digit on input\n";

			//Resets counters for the line
			ResetCounters(total, position, binaryNum);

			//Ignores all characters on the input line with bad data
			inFile.ignore(1000, '\n');
		}
	}

	inFile.close(); //Close the input file.
	return 0;
}

void CheckFile(ifstream& inFile) {
	inFile.open("BinaryIn.dat");

	if (!inFile) {
		cout << "This is not the right file ";
	}
}

void RemoveLeadingZeros(ifstream& inFile, char& input, int& position) {

	bool isOne = false;
	bool isBadData = false;

	while (!isOne && !isBadData) { //While input is NOT a one AND is NOT bad data

		position++; //Increment the file cursor (detects spaces in binary numbers)
		inFile.get(input);

		if (input == '1')
			isOne = true; //First one of binary number found - continue to appropriate clause of if-else in the main function

		if ((int(input) < '0' || int(input) > '1') && (input != ' ') || (input == ' ' && position > 0)) { //If anything other than a 1 or a 0 is read AND input is not a space in the middle of a binary number
			isBadData = true; //Bad data found - continue with bad input to error message clause of if-else in the main function
		}
	}
}



void ResetCounters(int& total, int& position, string& binaryNum) {
	//Resets counters for the next line of input
	position = 0;
	total = 0;
	binaryNum = "";
}

void PrintTable(int total, string binaryNum) {


	//Prints binary values according to the number of place values 
	switch (binaryNum.length()) {

	case 1:
		cout << setw(long(binaryNum.length() + 14)) << binaryNum;
		break;

	case 2:
		cout << setw(long(binaryNum.length() + 13)) << binaryNum;
		break;

	case 3:
		cout << setw(long(binaryNum.length() + 13)) << binaryNum;
		break;

	case 4:
		cout << setw(long(binaryNum.length() + 12)) << binaryNum;
		break;

	case 5:
		cout << setw(long(binaryNum.length() + 12)) << binaryNum;
		break;

	case 6:
		cout << setw(long(binaryNum.length() + 11)) << binaryNum;
		break;

	case 7:
		cout << setw(long(binaryNum.length() + 11)) << binaryNum;
		break;

	case 8:
		cout << setw(long(binaryNum.length() + 10)) << binaryNum;
		break;

	case 9:
		cout << setw(long(binaryNum.length() + 10)) << binaryNum;
		break;

	case 10:
		cout << setw(long(binaryNum.length() + 9)) << binaryNum;
		break;

	case 11:
		cout << setw(long(binaryNum.length() + 9)) << binaryNum;
		break;

	case 12:
		cout << setw(long(binaryNum.length() + 8)) << binaryNum;
		break;

	case 13:
		cout << setw(long(binaryNum.length() + 8)) << binaryNum;
		break;

	case 14:
		cout << setw(long(binaryNum.length() + 7)) << binaryNum;
		break;

	case 15:
		cout << setw(long(binaryNum.length() + 7)) << binaryNum;
		break;

	case 16:
		cout << setw(long(binaryNum.length() + 6)) << binaryNum;
		break;

	default:
		cout << setw(22) << "16-bit limit\n";
		break;
	}


	//Prints decimal values
	switch (DecimalPlaceValue(total)) { //Switches off of the decimal place value to determine the spacing in output

	case 1:

		if (total < 4) {
			cout << setw(20) << total << endl;
		}
		else
			cout << setw(19) << total << endl;
		break;

	case 2:
		if (total <= 15) {
			cout << setw(19) << total << endl;
		}
		else if (total <= 32) {
			cout << setw(18) << total << endl;
		}
		else if (total > 32 && total <= 63) {
			cout << setw(18) << total << endl;
		}
		else
			cout << setw(17) << total << endl;
		break;

	case 3:
		if (total < 256) {
			cout << setw(18) << total << endl;
		}
		else
			cout << setw(17) << total << endl;
		break;

	case 4:
		if (total >= 1000 && total < 1024) {
			cout << setw(17) << total << endl;
		}
		else if (total >= 1024 && total < 2048) {
			cout << setw(16) << total << endl;
		}
		else if (total >= 2048 && total <= 4095) {
			cout << setw(16) << total << endl;
		}
		else if (total >= 4096 && total < 10000) {
			cout << setw(15) << total << endl;
		}
		break;

	case 5:
		if (total >= 10000 && total < 16384) {
			cout << setw(16) << total << endl;
		}
		else if (total >= 16384 && total <= 32768) {
			cout << setw(15) << total << endl;
		}
		else if (total > 32768 && total <= 65535) {
			cout << setw(15) << total << endl;
		}
		break;
	}
}

void AddToTotal(int& total, char input, int& position, string& binaryNum) {

	//Adding either 1 or 0
	int k;

	if (input == '1')
		k = 1;
	else
		k = 0;

	binaryNum += input; //Use string concatenation to add the input 1 or 0 to a string 
	total = (total * 2) + k; //Multiply the total by 2 to account for the next highest place value and add 1
	position++; //Increment the file cursor
}

int DecimalPlaceValue(int total) {

	int placeValue = 0;

	while (total != 0) {
		total /= 10;
		placeValue++;
	}

	return placeValue;
}