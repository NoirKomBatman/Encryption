#ifndef __ENIGMA_HEADER_H__
#define __ENIGMA_HEADER_H__

#include <iostream>
#include <string>
#include <Algorithm>

template <typename T> class Enigma_Machine
{
private:
	const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string reflector = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
	int _counter1;
	int _counter2;
	T _alpha;
	T _rotor1;
	T _rotor2;
	T _rotor3;
	T _refl;
	char _perm[26];

	//Returns appropriate rotor/reflector
	T get_rotor(int r);

	T get_reflector();

	//Checks if every character in rotor is unique
	bool is_all_unique(const T& s);

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

	void space_remove(T &imp);

	void chck_rotors();

	T encrypt(const T& m);

public:

	Enigma_Machine();
	Enigma_Machine(T t);

	~Enigma_Machine();

	void rotors_set_start_pos(char r1, char r2, char r3);

	void start_enigma();

	void rotor_change(int r);
};

#endif //__ENIGMA_HEADER_H__