#include "enigma_machine.h"
#include "helper.cpp"




template <typename T> 
Enigma_Machine<T>::Enigma_Machine() :_counter1(10), _counter2(0), _alpha(alphabet), _refl(reflector)
{
	_rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"; //"EKMFLGDQVZNTOWYHXUSPAIBRCJ"
	_rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	_rotor3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

	for (int i : {0, 1, 2, 3, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24})
	{
		_perm[i] = NULL;
	}
	_perm[4] = 'a';
	_perm[5] = 't';
	_perm[6] = 'd';
	_perm[7] = 'z';
	_perm[8] = 'p';
	_perm[25] = 'c';
}

template <typename T>
Enigma_Machine<T>::Enigma_Machine(T t)
{
	Enigma_Machine();
}

template <typename T> 
Enigma_Machine<T>::~Enigma_Machine()
{
}

template <typename T> 
T Enigma_Machine<T>::get_reflector()
{
	return _refl;
}

template <typename T> T
Enigma_Machine<T>::get_rotor(int r)
{
	if (r == 1) return _rotor1;
	else if (r == 2) return _rotor2;
	else return _rotor3;
}

template <typename T> 
void Enigma_Machine<T>::rotor_change(int r)
{
	T* rotor_ptr = &get_rotor(r);
	T inp;
	do
	{
		std::cout << "Replace rotor with valid one" << std::endl;
		std::cin >> inp;
	} while (inp.length() != 26 && !is_all_unique(inp));
	*rotor_ptr = inp;
}

template <typename T> 
void Enigma_Machine<T>::rotate_rotor()
{
	//Screw clock arithmetic huehuehue :3
	_rotor1 = _rotor1.substr(1, _rotor1.length() - 1) + _rotor1[0]; _counter1++;
	if (_counter1 >= 26)
	{
		_counter1 = 0;
		_rotor2 = _rotor2.substr(1, _rotor2.length() - 1) + _rotor2[0]; _counter2++;
		std::cout << _rotor2 << std::endl;
		if (_counter2 >= 26)
		{
			_counter2 = 0;
			_rotor3 = _rotor3.substr(1, _rotor3.length() - 1) + _rotor3[0];
			std::cout << _rotor3 << std::endl;
		}
	}
}

template <typename T> 
T Enigma_Machine<T>::encrypt(const T& message)
{
	T encr_message = T();

	//0 - first rotor
	//1 - second rotor
	//2 - third rotor
	//3 - reflector
	//4 - inverse third rotor
	//5 - inverse second rotor
	//6 - inverse first rotor
	//7 - permutations

	
	for (int i = 0; i < len_of<T>(message); i++)	//O(n)
	{
		char curr = char_at<T>(message, i);
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
	return encr_message;
}


template <typename T> 
void Enigma_Machine<T>::rotors_set_start_pos(char r1, char r2, char  r3)
{
	//Making characters upper
	char t1 = r1;
	char t2 = r2;
	char t3 = r3;
	t1 = toupper(r1);
	t2 = toupper(r2);
	t3 = toupper(r3);

	//Check if character is the same as starting position of rotor
	if (t1 != char_at<T>(_rotor1, 0))
	{
		for (int i = 0; i < len_of<T>(_rotor1); i++)
		{
			if (t1 == char_at<T>(_rotor1, i))
			{
				_rotor1 = _rotor1.substr(i, _rotor1.length() - i) + _rotor1.substr(0, i);
			}
		}
	}
	if (t2 != char_at(_rotor2, 0))
	{
		for (int i = 0; i <  len_of<T>(_rotor2); i++)
		{
			if (t2 == char_at<T>(_rotor2, i))
			{
				_rotor2 = _rotor2.substr(i, _rotor2.length() - i) + _rotor2.substr(0, i);
			}
		}
	}
	if (t3 != char_at(_rotor3, 0))
	{
		for (int i = 0; i < len_of(_rotor3); i++)
		{
			if (t3 == char_at(_rotor3,i))
			{
				_rotor3 = _rotor3.substr(i, _rotor3.length() - i) + _rotor3.substr(0, i);
			}
		}
	}
}

template <typename T> 
void Enigma_Machine<T>::chck_rotors()
{
	bool ub;
	for (int i : {1, 2, 3})
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
}

//Checks whether rotor have unique character in it
template <typename T> 
bool Enigma_Machine<T>::is_all_unique(const T& s)
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
	int hash_alpha[26];
	for (int i = 0; i < len_of(s); i++) {
		int c = char_at(s, i);
		hash_alpha[c]++;
	}

	for (int i = 0; i < 26; i++)
		if (hash_alpha[i]>1)
			return false;

	return true;
}

//Returns position of character in alphabet
//Starting position is 0
template <typename T> 
int Enigma_Machine<T>::char_alpha_pos(char c)
{
	c = toupper(c);
	try
	{
		if (isalpha(c) == false)
		{
			throw false;
		}
		for (int i = 0; i < 26; i++)
		{
			if (char_at(_alpha, i) == c)
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
		char_alpha_pos(i);	//Better use loop to avoid stackoverflow
	}
}


template <typename T> 
char Enigma_Machine<T>::converse_encryption(char c, int r)
{
	int c_pos = char_alpha_pos(c);
	T rotor = get_rotor(r);
	return char_at(rotor, c_pos);
}

template <typename T> 
char Enigma_Machine<T>::reflector_encryption(char c)
{
	int c_pos = char_alpha_pos(c);
	return char_at(_refl, c_pos);
}

template <typename T> 
char Enigma_Machine<T>::inverse_encryption(char c, int r)
{
	T rotor = get_rotor(r);
	for (int i = 0; i < 26; i++)
	{
		if (char_at(rotor, i) == c)
		{
			return _alpha[i];
		}
	}
	return '!';
}
template <typename T> 
bool Enigma_Machine<T>::permutation_is_unique()
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (char_at<T>(_perm, i) == char_at<T>(_perm, j) && char_at<T>(_perm, i) != NULL) return false;
		}
	}
	return true;
}
template <typename T> 
char Enigma_Machine<T>::permutation_encryption(char c)
{
	if (_perm[char_alpha_pos(c)] == NULL)
		return c;
	return _perm[char_alpha_pos(c)];
}


template <typename T> 
void Enigma_Machine<T>::space_remove(T &imp)
{
	imp.erase(std::remove(imp.begin(), imp.end(), ' '), imp.end());
}

template <typename T>
void Enigma_Machine<T>::start_enigma()
{
	std::cout << "Welcome to Enigma Machine!" << std::endl;
	chck_rotors();
	std::cout << "Please adjust rotors starting positions" << std::endl;
	char r1, r2, r3;
	std::cin >> r1 >> r2 >> r3;

	rotors_set_start_pos(r1, r2, r3);
	T message = T();
	std::cout << "For security reasons spaces are not allowed. Makes everything more obvious" << std::endl;
	std::cout << "Enter message for ecnryption: ";
	std::cin >> message;
	transform(message.begin(), message.end(), message.begin(), tolower);
	std::cout << "Encrypted message: " << encrypt(message) << std::endl;
}