#include <iostream>
#include <string>
#include <Algorithm>



class Enigma_Machine
{
private:
	int counter1;
	int counter2;
	std::string alpha;
	std::string rotor1; 
	std::string rotor2;
	std::string rotor3;
	std::string reflector;
	char perm[26];

	//Returns appropriate rotor
	std::string get_rotor(int r);

	std::string get_reflector();

	//Checks if every character in rotor is unique
	bool is_all_unique(std::string s);

	//Signal goes through first 3 rotors
	char converse_encryption(char c, int r);

	char reflector_encryption(char c);

	//Signal goes back reverse through rotors
	char inverse_encryption(char c, int r);

	//Checks character's position in alphabet
	int char_alpha_pos(char c);

	//The last stage of signal
	//Goes to assigned value-pair
	char permutation_encryption(char c);
	char permutation_decryption(char c);

	bool permutation_is_unique();

	void rotate_rotor();

	void space_remove(std::string &imp);

public:

	Enigma_Machine();

	void rotors_set_start_pos(char r1, char r2, char r3);

	void start_enigma();

	void rotor_change(int r);
};
Enigma_Machine::Enigma_Machine()
{
	counter1 = 0;
	counter2 = 0;
	alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"; //"EKMFLGDQVZNTOWYHXUSPAIBRCJ"
	rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	rotor3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
	reflector = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
	for (int i : {0, 1, 2, 3, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24})
	{
		perm[i] = NULL;
	}
	perm[4] = 'a';
	perm[5] = 't';
	perm[6] = 'd';
	perm[7] = 'z';
	perm[8] = 'p';
	perm[25] = 'c';
}

std::string Enigma_Machine::get_reflector()
{
	return reflector;
}

std::string Enigma_Machine::get_rotor(int r)
{
	if (r == 1) return rotor1;
	else if (r == 2) return rotor2;
	else return rotor3;
}

void Enigma_Machine::rotor_change(int r)
{
	std::string* rotor_ptr = &get_rotor(r);
	std::string inp;
	do
	{
		std::cout << "Replace rotor with valid one" << std::endl;
		std::cin >> inp;
	} while (inp.length() != 26 && !is_all_unique(inp));
	*rotor_ptr = inp;
}

void Enigma_Machine::rotate_rotor()
{
	rotor1 = rotor1.substr(1, rotor1.length() - 1) + rotor1[0]; counter1++;
	std::cout << rotor1 << std::endl;
	if (counter1 >= 26)
	{
		counter1 = 0;
		rotor2 = rotor2.substr(1, rotor2.length() - 1) + rotor2[0]; counter2++;
		std::cout << rotor2 << std::endl;
		if (counter2 >= 26)
		{
			counter2 = 0;
			rotor3 = rotor3.substr(1, rotor3.length() - 1) + rotor3[0];
			std::cout << rotor3 << std::endl;
		}
	}
}

void Enigma_Machine::start_enigma()
{
	std::cout << "Welcome to Enigma" << std::endl;
	bool ub;
	for (int i = 1; i <= 3; i++)
	{
		try{
			ub = is_all_unique(get_rotor(i));
			if (ub == false)
			{
				throw false;
			}
			std::cout << "Rotor " << i << " is correct" << std::endl;
			std::cout << get_rotor(i) << std::endl;
		}
		catch (bool e)
		{
			std::cout << "Rotor " << i << " is invalid" << std::endl;
			rotor_change(i);
		}
	}
	std::cout << "Set rotors starting positions" << std::endl;
	char r1, r2, r3;
	std::cin >> r1 >> r2 >> r3;
	rotors_set_start_pos(r1, r2, r3);

	std::cout << "Enter your message (no spaces are allowed, meaning becomes obvious with spaces :p): " << std::endl;
	std::string message;
	std::cin >> message;
	transform(message.begin(), message.end(), message.begin(), tolower);
	//space_remove(message);
	std::string encr_message = "";
	//0 - first rotor
	//1 - second rotor
	//2 - third rotor
	//3 - reflector
	//4 - inverse third rotor
	//5 - inverse second rotor
	//6 - inverse first rotor
	//7 - permutations

	for (int i = 0; i < message.length(); i++)	//O(n)
	{
		char curr = message[i];
		for (int j = 0; j < 7; j++)	//O(1)
		{
			if (j < 3)
			{
				curr = converse_encryption(curr, j + 1);
			}
			else if (j == 3)
			{
				curr = reflector_encryption(curr);
			}
			else if (j < 7 && j > 3)
			{
				switch (j)
				{
				case 4: curr = inverse_encryption(curr, 3); break;
				case 5: curr = inverse_encryption(curr, 2); break;
				case 6: curr = inverse_encryption(curr, 1); break;
				}
			}
			else curr = permutation_encryption(curr);
		}
		encr_message += curr;
		rotate_rotor();
	}
	std::cout << "Your encrypted message: " << encr_message << std::endl;;
}


void Enigma_Machine::rotors_set_start_pos(char r1, char r2, char  r3)
{
	//Making characters upper
	r1 = toupper(r1);
	r2 = toupper(r2);
	r3 = toupper(r3);

	//Check if character is the same as starting position of rotor
	if (r1 != rotor1[0])
	{
		for (int i = 0; i < rotor1.length(); i++)
		{
			if (r1 == rotor1[i])
			{
				rotor1 = rotor1.substr(i, rotor1.length() - i) + rotor1.substr(0, i);
			}
		}
	}
	if (r2 != rotor2[0])
	{
		for (int i = 0; i < rotor2.length(); i++)
		{
			if (r2 == rotor2[i])
			{
				rotor2 = rotor2.substr(i, rotor2.length() - i) + rotor2.substr(0, i);
			}
		}
	}
	if (r3 != rotor3[0])
	{
		for (int i = 0; i < rotor3.length(); i++)
		{
			if (r3 == rotor3[i])
			{
				rotor3 = rotor3.substr(i, rotor3.length() - i) + rotor3.substr(0, i);
			}
		}
	}

	//Print new rotor (optional)
	std::cout << rotor1 << std::endl;
	std::cout << rotor2 << std::endl;
	std::cout << rotor3 << std::endl;
}

//Checks whether rotor have unique character in it
bool Enigma_Machine::is_all_unique(std::string s)
{
	//O(n^2) version that doesn't use any additional data structures
	/*
	for (int i = 0; i < s.length(); i++)
	{
		int countdooku = 0;
		for (int j = 0; j < s.length(); j++)
		{
			if (s[i] == s[j])
			{
				countdooku++;
			}
		}
		if (countdooku > 1)
		{
			return false;
		}
	}
	return true;
	*/

	//O(n) version which uses extra array
	int hash_alpha[26] = {};
	for (int i = 0; i < s.length(); i++)
		hash_alpha[s[i]]++;

	for (int i = 0; i < 26; i++)
		if (hash_alpha[i]>1)
			return false;

	return true;
}

//Returns position of character in alphabet
//Starting position is 0
int Enigma_Machine::char_alpha_pos(char c)
{
	c = toupper(c);
	try
	{
		if (isalpha(c) == false)
		{
			throw false;
		}
		for (int i = 0; i < alpha.length(); i++)
		{
			if (alpha[i] == c)
			{
				return i;
			}
		}
	}
	catch (bool b)
	{
		int i;
		std::cout << "Invalid character: ";
		std::cin >> i;
		char_alpha_pos(i);	// Better use loop to avoid stackoverflow
	}
}


char Enigma_Machine::converse_encryption(char c, int r)
{
	int c_pos = char_alpha_pos(c);
	std::string rotor = get_rotor(r);
	return rotor[c_pos];
}

char Enigma_Machine::reflector_encryption(char c)
{
	int c_pos = char_alpha_pos(c);
	return reflector[c_pos];
}

char Enigma_Machine::inverse_encryption(char c, int r)
{
	std::string rotor = get_rotor(r);
	for (int i = 0; i < 26; i++)
	{
		if (rotor[i] == c)
		{
			return alpha[i];
		}
	}
	return '!';
}
bool Enigma_Machine::permutation_is_unique()
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (perm[i] == perm[j] && perm[i] != NULL) return false;
		}
	}
	return true;
}
char Enigma_Machine::permutation_encryption(char c)
{
	if (perm[char_alpha_pos(c)] == NULL)
		return c;
	return perm[char_alpha_pos(c)];
}


void Enigma_Machine::space_remove(std::string &imp)
{
	imp.erase(std::remove(imp.begin(), imp.end(), ' '), imp.end());
}


int main()
{
	Enigma_Machine* h = new Enigma_Machine();

	h->start_enigma();

	return 0;
}
