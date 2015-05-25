#ifndef __CIPHERS_HEADER_H__
#define __CIPHERS_HEADER_H__
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
	// fix this one, can't instantiate Enigma due to Cipher being abstract class and inability to override pure virtual function encrypt()
	// virtual CipherT encrypt() = 0;
};

template<typename CipherT>
class Polyalphabetic_Cipher: public Cipher<CipherT>
{
public:
	Polyalphabetic_Cipher();
	virtual ~Polyalphabetic_Cipher() = 0;
};

template<typename CipherT>
class Rotor_Machine: public Polyalphabetic_Cipher<CipherT>
{
public:
	Rotor_Machine();
	virtual ~Rotor_Machine() = 0;

};
#endif