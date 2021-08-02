#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>


void randpwSeed() {
    srand((unsigned int)(time(NULL)));
}
// Function to randomly generates password
// of length N
void _randpwGen(char *str, size_t size, bool isHaveNum, bool isHaveLower,
     bool isHaveUper, isHaveSpecial)
{
    const char *charset;
  
    // Array of numbers
    const char charsetNum[] = "0123456789";
    // Array of small alphabets
    const char  charsetLowLetter[] = "abcdefghijklmnoqprstuvwyzx";
    // Array of capital alphabets
    const char  charsetUperLetter[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    // Array of all the special symbols
    const char  charsetSymbols[] = "!@#$^&*?";

    // Array of numbers and small alphabets
    const char  charsetNumLowerLetter[] = "0123456789abcdefghijklmnoqprstuvwyzx";
    // Array of numbers and capital alphabets
    const char  charsetNumUperLetter[] = "0123456789ABCDEFGHIJKLMNOQPRSTUYWVZX";
    // Array of numbers and special symbols
    const char  charsetNumSymbols[] = "0123456789!@#$^&*?";
    // Array of alphabets
    const char  charsetLetter[] = "abcdefghijklmnoqprstuvwyzxABCDEFGHIJKLMNOQPRSTUYWVZX";
    // Array of small alphabets and special symbols
    const char  charsetLowerLetterSymbols[] = "abcdefghijklmnoqprstuvwyzx!@#$^&*?";
    // Array of capital alphabets and special symbols
    const char  charsetUperLetterSymbols[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX!@#$^&*?";
            
    // Array of numbers and alphabets
    const char  charsetNumLetter[] = "0123456789abcdefghijklmnoqprstuvwyzxABCDEFGHIJKLMNOQPRSTUYWVZX";
    // Array of numbers and small alphabets and special symbols
    const char  charsetNumLowerLetterSymbols[] = "0123456789abcdefghijklmnoqprstuvwyzx!@#$^&*?";
    // Array of numbers and capital alphabets and special symbols
    const char  charsetNumUperLetterSymbols[] = "0123456789ABCDEFGHIJKLMNOQPRSTUYWVZX!@#$^&*?";
    // Array of alphabets and special symbols
    const char  charsetLetterSymbols[] = "abcdefghijklmnoqprstuvwyzxABCDEFGHIJKLMNOQPRSTUYWVZX!@#$^&*?";

    // Array of numbers and alphabets and special symbols
    const char  charsetNumLetterSymbols[] = "0123456789abcdefghijklmnoqprstuvwyzxABCDEFGHIJKLMNOQPRSTUYWVZX!@#$^&*?";
  
    if(isHaveNum==true && isHaveLower==false && isHaveUper==false && isHaveSpecial==false) charset=charsetNum;
    if(isHaveNum==false && isHaveLower==true && isHaveUper==false && isHaveSpecial==false) charset=charsetLowLetter;
    if(isHaveNum==false && isHaveLower==false && isHaveUper==true && isHaveSpecial==false) charset=charsetUperLetter;
    if(isHaveNum==false && isHaveLower==false && isHaveUper==false && isHaveSpecial==true) charset=charsetSymbols;

    if(isHaveNum==true && isHaveLower==true && isHaveUper==false && isHaveSpecial==false) charset=charsetNumLowerLetter;
    if(isHaveNum==true && isHaveLower==false && isHaveUper==true && isHaveSpecial==false) charset=charsetNumUperLetter;
    if(isHaveNum==true && isHaveLower==false && isHaveUper==false && isHaveSpecial==true) charset=charsetNumSymbols;
    if(isHaveNum==false && isHaveLower==true && isHaveUper==true && isHaveSpecial==false) charset=charsetLetter;
    if(isHaveNum==false && isHaveLower==true && isHaveUper==false && isHaveSpecial==true) charset=charsetLowerLetterSymbols;
    if(isHaveNum==false && isHaveLower==false && isHaveUper==true && isHaveSpecial==true) charset=charsetUperLetterSymbols;

    if(isHaveNum==true && isHaveLower==true && isHaveUper==true && isHaveSpecial==false) charset=charsetNumLetter;
    if(isHaveNum==true && isHaveLower==true && isHaveUper==false && isHaveSpecial==true) charset=charsetNumLowerLetterSymbols;
    if(isHaveNum==true && isHaveLower==false && isHaveUper==true && isHaveSpecial==true) charset=charsetNumUperLetterSymbols;
    if(isHaveNum==false && isHaveLower==true && isHaveUper==true && isHaveSpecial==true) charset=charsetLetterSymbols;

    if(isHaveNum==true && isHaveLower==true && isHaveUper==true && isHaveSpecial==true) charset=charsetNumLetterSymbols;
    if(isHaveNum==true && isHaveLower==false && isHaveUper==false && isHaveSpecial==false) charset=charsetNumLetterSymbols;
    
    int charsetLen = strlen(charset);

    if (size) {
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (charsetLen);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
}

void randpwGen(char *str, size_t size) {
    _randpwGen(str, size, true, true, true, true);
}

void randpwGenUperLetter(char *str, size_t size) {
    _randpwGen(str, size, false, false, true, false);
}

void randpwGenLowerLetter(char *str, size_t size) {
    _randpwGen(str, size, false, true, false, false);
}

void randpwGenLetter(char *str, size_t size) {
    _randpwGen(str, size, false, true, true, false);
}

void randpwGenNumUperLetter(char *str, size_t size) {
    _randpwGen(str, size, true, false, true, false);
}

void randpwGenNumLowerLetter(char *str, size_t size) {
    _randpwGen(str, size, true, true, false, false);
}

void randpwGenNumLetter(char *str, size_t size) {
    _randpwGen(str, size, true, true, true, false);
}

/* Test main */
#ifdef RANDPW_TEST_MAIN

int main(){

    char str[9];
    randpwSeed();
    randpwGenLowerLetter(str, 8);
    printf("genstr:[%s]\n", str);
    randpwGenUperLetter(str, 8);
    printf("genstr:[%s]\n", str);
    randpwGenLetter(str, 8);
    printf("genstr:[%s]\n", str);

    return 0;
}

#endif