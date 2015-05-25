#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <array>

using namespace std;

class VigenereCipher {
private:
	//Alphabet of charecters
	std::array<char, 52> alphabet{ { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' } };
	//List of numerals and punctuation allowed in the cipher
	std::array<char, 42> punctuation{ { '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '\\', '_', '^', '{', '|', '}', '~', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' } }; // punctuation common white space charecters, and numbers
	//Helper function to encrypt punctuation and numerical digits
	char encryptPunctNum(char plainPunct, char currentKey);
	//Helper function to decrypt punctuation and numerical digits
	char decryptPunctNum(char encryptedPunct, char currentKey);


public:

	//Function to encrypt an entire string 
	std::string encrypt(std::string plainText, std::string key);
	//Function to decrypt an entire string
	std::string decrypt(std::string encryptedText, std::string key);

};

//Encrypt charecters that are non alphabetical (ie. punctuation and numbers), helper function
char  VigenereCipher::encryptPunctNum(char plainPunct, char currentKey){         //Takes a plain punctuation/number charecter and the index of a key string
	int plainPunctIndex;                                                         //The index of the plain punctuation/number in the punctuation[] array
	int key1st;
	for (int j = 0; j < 42; j++) {
		if (punctuation[j] == plainPunct){
			plainPunctIndex = j;                                                 //Loop through the punctuation array to find the correct index of the given plain punctuation/number
		}
	}
	for (int i = 0; i < 52; i++) {                                               //Loop through the alphabet to determine the index of the current key char. 
		if (alphabet[i] == currentKey){
			key1st = i;
		}
	}

	int encryptedPunctuationIndex = (plainPunctIndex + key1st) % 42;            //Create a new, encrypted index by adding the index got previously and the index of the key, then calling MOD on the length of the array

	return punctuation[encryptedPunctuationIndex];                              //Return the charecter at the encrypted index
}

//Decrypt charecters that are non-alphabetical (ie. punctuation and numbers), helper function
char VigenereCipher::decryptPunctNum(char encryptedPunct, char currentKey){
	int encryptedPunctIndex;
	int key1st;

	for (int j = 0; j < 42; j++) {
		if (punctuation[j] == encryptedPunct){
			encryptedPunct = j;
		}
	}
	for (int i = 0; i < 52; i++) {                                           //If the current plaintext charecter is not punctuation or numerical, loop through the alphabet and see if it is an upper or lower-case letter.
		if (alphabet[i] == currentKey){
			key1st = i;
		}
	}
	int decryptedPunctuationIndex = (encryptedPunct - key1st + 42) % 42;    //Similar to encrypt, except here i'm suptracting the index of the encrypted punctuation/number from the index of the key, I add 42 incase the result is a negitive number

	return punctuation[decryptedPunctuationIndex];                          //Return the original charecter at the decrypted index
}

//Encrypt the charectes of a string using a Veginere Cipher
std::string VigenereCipher::encrypt(std::string plainText, std::string key){
	std::string encryptedString;                                             //The encrypted string to be returned
	int length = plainText.length();                                         //The length of the plain string that is to be encrypted
	int r = 0;                                                               //The index of the key starting at 0
	int keylen = key.length() - 1;                                           //The length of the key - 1

	for (int i = 0; i < length; i++){                                        //Plaintext string
		char currentPlainText = (plainText.at(i));                           //Current charecter of the plaintext string
		char currentKey = key.at(r);                                         //Current charecter of the key
		int plaintext1st;                                                    //Index position of current plaintext char
		int key1st;                                                          //Index position of current key char

		if (!isalpha(plainText.at(i))){                                      // If the current plaintext charecter is not alphabetic, then check if it is punctuation or number
			encryptedString.push_back(encryptPunctNum(plainText.at(i), currentKey));
			r = ((r >= keylen) ? 0 : r + 1);                                 //Ternary Opperator to save space, Increment key index if it has not reached the end of it's length, else set the index to the beginning at 0
		}

		else
		{
			for (int j = 0; j < 52; j++) {                                   //If the current plaintext charecter is not punctuation or numerical, loop through the alphabet and see if it is an upper or lower-case letter.
				if (alphabet[j] == currentPlainText){
					plaintext1st = j;                                        //Get the index numbers of the current plaintext charecter and current key charecter in the alphabet[] array
				}
				if (alphabet[j] == currentKey){
					key1st = j;
				}
			}

			r = ((r >= keylen) ? 0 : r + 1);
			int encryptedLetterIndex = (plaintext1st + key1st) % 52;          //Add the index numbers of the plaintext and key to create an encrypted letter index --- forumla from wikipedia adapted
			encryptedString.push_back(alphabet[encryptedLetterIndex]);        //Push to the back of the encrypted string the letter at the encrypted index.
		}
	}

	return encryptedString;                                                   //After going through each charecter of the plaintext string, encrypting it, and pushing it to the tail of the encryptedString, return the encryptedString
}


//Decrypt the charectes of a string using a Veginere Cipher
std::string VigenereCipher::decrypt(std::string encryptedText, std::string key){
	std::string decryptedString;                                              //The decrypted String to be returned
	int length = encryptedText.length();                                      //The length of the encrypted string to be decrypted
	int r = 0;                                                                //The index of the key starting at 0
	int keylen = key.length() - 1;                                            //The length of the key - 1

	for (int i = 0; i < length; i++){                                         //EncryptedText string
		char currentEncryptedText = (encryptedText.at(i));                    //Current charecter of the encrypted text
		char currentKey = key.at(r);                                          //current key charecter
		int encryptedText1st;                                                 //index position of current encryptedText char
		int key1st;                                                           //index position of current key char


		if (!isalpha(encryptedText.at(i))){                                   // If the current plaintext char is not alphabetic, then check if it is punctuation or numeric
			decryptedString.push_back(decryptPunctNum(encryptedText.at(i), currentKey));
			r = ((r >= keylen) ? 0 : r + 1);
		}

		else {
			for (int j = 0; j < 52; j++) {                                     //Alphabet
				if (alphabet[j] == currentEncryptedText){                      // If current letter of the alphabet is equal to the current encrypted text, then encryptedText1st becomes it's alphabetical index number
					encryptedText1st = j;
				}
				if (alphabet[j] == currentKey){                                // If current letter of alphabet is equal to the current key letter, then set key1st to it's alphabetical index number
					key1st = j;
				}
			}

			r = ((r >= keylen) ? 0 : r + 1);
			int dencryptedLetterIndex = (encryptedText1st - key1st + 52) % 52; //Subtract the index numbers of the plaintext and key to create an encrypted letter index, add 52 incase the result is negitive
			decryptedString.push_back(alphabet[dencryptedLetterIndex]);        //Add the decrypted letter to the end of the decrypted string.
		}
	}

	return decryptedString;                                                    //Return decrypted text
}

//Future implementations:
//Throw an error exception when a non-alphabetical/numerical/punctuation char is input and print instructions to use english alphabetical/numerical/punctuation chars only.
//Develop UI for encrypt and decrypt.

int main(int argc, const char* argv[]) {
	VigenereCipher Vigenere;

	//Encryption
	cout << "TESTING ENCRYPTION:" << endl << endl;
	std::string plainText("Yooo baby, what's goin on? I wanna take u shoppin' at Value Village at 9? :D, call me maybe at 104 512 6969, Ohh if you one of em hipsta new-age gurlz, I also gots an email :) frugal_ladykiller@hotmail.com");
	std::string key("deadly");
	std::string cipherifiedText = Vigenere.encrypt(plainText, key);
\
	cout << "The plaintext is: " << plainText << endl;
	cout << "The key is: " << key << endl;
	cout << "The Encrypted text is: " << cipherifiedText << endl << endl << endl;


	//Decryption
	cout << "TESTING DECRYPTION:" << endl << endl;
	std::string encryptedText = cipherifiedText;
	std::string decryptedText = Vigenere.decrypt(encryptedText, key);
	cout << "The Encrypted text is: " << encryptedText << endl;
	cout << "The key is: " << key << endl;
	cout << "The Decrypted text is: " << decryptedText << endl;
	cin.get();

	return 0;

}

