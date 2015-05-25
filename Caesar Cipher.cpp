#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <array>
#include <ctime>

using namespace std;

class Caesar_Cipher {
private:
	//The charecters that are allowed to be encrypted
	std::array<char, 94> alphabet{ { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
		't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 
		'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', 
		'<', '=', '>', '?', '@', '[', ']', '\\', '_', '^', '{', '|', '}', '~', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' } };
	
public:
	//Function to encrypt an entire string using a Caesar Cipher
	std::string encrypt(string plaintext, int shiftValue);
	//Function to decrypt an entire string 
	std::string decrypt(string encryptedText, int shiftValue);
};

// Encrypt a string, takes a string plaintext and a value by which to shift each letter/charecter. Returns encrypted string.
std::string Caesar_Cipher::encrypt(std::string plaintext, int shiftValue){
	std::string encryptedString; 
		
	for (int a = 0; a < plaintext.length(); a++){                                     //iterate through each charecter of the string 
		int indexValue;
		char currentchar = plaintext.at(a);

		for (int i = 0; i < 94; i++){                                                 //check list of allowed charecters to determine index value
			if (alphabet[i] == currentchar){
				indexValue = i;                                                       //set indexValue to the index value of the charecter list
			}
		}

		int encryptedIndex = (indexValue + shiftValue) % 94;                          //get the encrypted index by shifting the current plaintext's index right by the shiftValue
		encryptedString.push_back(alphabet[encryptedIndex]);                          //push a charecter at the encrypted index into the encrypted string.
	}
	return encryptedString;
	}
// decrypt an entire string, takes an encrypted string and the value that it was originally shifted by. Returns decrypted string.
std::string Caesar_Cipher::decrypt(std::string encryptedText, int shiftValue){
	std::string decryptedString;
	

	for (int a = 0; a < encryptedText.length(); a++){                                 //iterate through each charecter of the encrypted string 
		int indexValue;
		char currentchar = encryptedText.at(a);

		for (int i = 0; i < 94; i++){                                                 //check list of allowed charecters to determine index value
			if (alphabet[i] == currentchar){
				indexValue = i;                                                       //set indexValue of the encrypted charecter to the coressponding index value of the charecter list
			}
		}
		int decryptedIndex = (indexValue - shiftValue + 94) % 94;                     //get the original index by shifting the current encrypted charecter's index left by the original shiftValue
		decryptedString.push_back(alphabet[decryptedIndex]);                          //push a charecter at the decrypted index into the decrypted string.
	}
	return decryptedString;
}

// Future implementations:
// Allow users to choose between using a randomizer or choosing a number.
int main(){
	Caesar_Cipher Cc;                                                              

	int x;
	std::string yesOrNo;
	cout << "Would you like to choose the shift value? if you type no the shift value will be randomly generated. " << endl;
	cin >> yesOrNo;

	if (yesOrNo == "no") {
		srand(time(NULL)); //seed
	    x = rand() % 27; //get a random alphabetical index number to shift by
	}
	else if (yesOrNo == "yes"){
		cout << "What value would you like to shift by? " << endl;
		cin >> x;
	}


	cout << "Encryption Testing: " << endl << endl;
	int shiftValue = x;
	std::string message = "Lolz, this incription scheisse iz too easy to crack!!! u want lurn real encrypt??? call me at 1234567890";
	std::string encryptedText = Cc.encrypt(message, shiftValue);
	std::string decryptedText = Cc.decrypt(encryptedText, shiftValue);

	cout << "Top secret message: " << message << endl << endl;
	cout << "Message encrypted: " << encryptedText << endl << endl;
	cout << "Decrypted mesage: " << decryptedText << endl << endl;
	

	system("pause");

	return 0;
}


