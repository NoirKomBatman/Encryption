#include <iostream>

namespace cryptography
{
	static const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

template<typename CipherT>
class Cipher
{
public:
	Cipher();
	virtual ~Cipher() = 0;
	virtual CipherT encrypt() = 0;
};

template<typename CipherT>
class Polyalphabetic_Cipher: public Cipher
{
public:
	Polyalphabetic_Cipher();
	virtual ~Polyalphabetic_cipher() = 0;
};

template<typename CipherT>
class Rotor_Machine: public Polyalphabetic_Cipher
{
public:
	Rotor_Machine();
	virtual ~Rotor_Machine() = 0;

};