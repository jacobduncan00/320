#include <iomanip>
#include <iostream>
#include <math.h>

// Lab 7 for COSC-320 by Jacob Duncan @ Salisbury University
// Completed 3/24/20 

size_t hash(size_t);
void printHash(size_t);
size_t hashTest1(const std::string&);
size_t hashTest2(const std::string&);

int main(){
  std::cout << "---------------------" << std::endl;
  std::cout << "Testing hashing ints:" << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << "Int: " << 5 << " | ";
  printHash(hash(5));
  std::cout << "Int: " << 100 << " | ";
  printHash(hash(100));
  std::cout << "Int: " << 5000 << " | ";
  printHash(hash(5000));
  std::cout << "Int: " << 100000 << " | ";
  printHash(hash(100000));
  std::cout << "---------------------" << std::endl;
  std::cout << "Int: " << 5 << " | ";
  printHash(hash(5));
  std::cout << "---------------------" << std::endl;

  // Hashing Strings with 1st function
  std::cout << "Testing hashing strings:" << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << "String: I am a COSC major" << std::endl;
  printHash(hashTest1("I am a COSC major"));
  std::cout << "String: Coronavirus" << std::endl;
  printHash(hashTest1("Coronavirus"));
  std::cout << "String: We are using zoom" << std::endl;
  printHash(hashTest1("We are using zoom"));
  std::cout << "------------------------" << std::endl;
  std::cout << "String: I am a COSC major" << std::endl;
  printHash(hashTest1("I am a COSC major"));
  std::cout << "------------------------" << std::endl;

  // Hashing Strings with 2nd function
  std::cout << "Testing hashing strings (2):" << std::endl;
  std::cout << "----------------------------" << std::endl;
  std::cout << "String: Coding in the morning" << std::endl;
  printHash(hashTest2("Coding in the morning"));
  std::cout << "String: I enjoy COSC" << std::endl;
  printHash(hashTest2("I enjoy COSC"));
  std::cout << "String: Arch Linux master distribution" << std::endl;
  printHash(hashTest2("Arch Linux master distribution"));
  std::cout << "----------------------------" << std::endl;
  std::cout << "String: Coding in the morning" << std::endl;
  printHash(hashTest2("Coding in the morning"));
  std::cout << "----------------------------" << std::endl;
  return 0;
}

// Hash function that computes a hash for a given
// integer using the 'multiplication method'

size_t hash(size_t x){
    size_t W = pow(2, 64);
    // Prime number smaller than 64, but
    // not too small
    size_t p = 47;
    // 10 digit prime number
    size_t a = 2971215073;
    size_t rtn = floor(((a * x) % W)/pow(2, 64-p));
    // Using the shift operator we would just
    // floor(((a*w)%W)>>64-p); ?
    return rtn;
}

// Function that takes in a size_t and returns it's
// hex value in order to display to the user

void printHash(size_t num){
  std::cout << "Hash: " << std::hex << num << std::endl;
}

// Function that takes a string and returns a size_t hash 
// way #1

size_t hashTest1(const std::string& str){
  size_t hashVal = 0;
  size_t tableSize = 531;
  for(int i = 0; i < str.length(); i++){
    hashVal += (int)str[i];
  }
  return hashVal % tableSize;
}

// Function that takes a string and returns a size_t hash
// way #2

size_t hashTest2(const std::string& str){
  size_t oddNum = 191;
  size_t tableSize = 531;
  unsigned long long hashVal = 0;
  for(int i = 0; i < str.length(); i++){
    hashVal = hashVal * oddNum + (int)str[i];
  }
  return hashVal % tableSize;
}
