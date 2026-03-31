#include <iostream>
#include <string>
#include <cstdint>

#include "hashPassword.h"

using namespace std;

string hashPassword(const string& password)
{
    const uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
    const uint64_t FNV_PRIME = 1099511628211ULL;

    uint64_t hashValue = FNV_OFFSET_BASIS;

    for (unsigned char byte : password)
    {
        hashValue ^= byte;           //Take each character from the password and mix it into the hash value using XOR
        hashValue *= FNV_PRIME;      //Mix the hash bits more by multiplying with the FNV prime
    }

    return to_string(hashValue);     // Converts the hash to a string
}