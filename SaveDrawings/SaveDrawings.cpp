// SaveDrawings.cpp : The program uses a hash function to store drawings entered by the user
// Alexander Ng
// 3/2021

#include <iostream>
#include <string.h>
using namespace std;

const int SIZE = 8;     // stores size of drawing
const int A_SIZE = 8;       // stores size of array of drawings

class Drawings {
private:
    static const int PRIME = 227;
    string names[A_SIZE];
    char drawing[A_SIZE][SIZE][SIZE];
    int create_Hashkey1(string new_Name);
    int create_Hashkey2(string new_Name);
public:
    Drawings();
    void make_Hash(string new_Name);
};

Drawings::Drawings() {      // constructor that resets the name array
    for (int i = 0; i < A_SIZE; i++) {
        names[i] = "0/+=";
    }
}

void Drawings::make_Hash(string new_Name) {       // complete function that makes hash keys
    int sum;
    sum = create_Hashkey1(new_Name);        // creates an independent hash key
    cout << "sum1 is " << sum << endl;
    if (names[sum] != "0/+=") {         // if the space is already occupied, run it through a different hash function
        sum += create_Hashkey2(new_Name);       // adds the new hash key together and mod it to fit array size
        sum = sum % A_SIZE;
        cout << "sum2 is " << sum << endl;
    }
    if (names[sum] != "0/+=") {     // if there is still overlap, recurse through the function again
        make_Hash(new_Name);
    }
    names[sum] = new_Name; // if there are no overlaps, finalize the iD
}

int Drawings::create_Hashkey1(string new_Name) {       // takes (the sum of ASCII values + word length) * prime number % Size of array - If the array position is occupied, + 1 to see if its free slot
    int string_Length = new_Name.length();
    int sum = 0;
    for (int i = 0; i < string_Length; i++) { // loop to add all ASCII values
        sum += static_cast<int>(new_Name[i]);
    }
    sum += string_Length;       // adds string length
    sum *= PRIME;           // adds prime number
    sum = sum % A_SIZE;        // Mods the size of array to get an ID within range of array size

    return sum;
}

int Drawings::create_Hashkey2(string new_Name) {       // takes (the sum of ASCII values * wworld length) * prime number % Size of array - If the array position is occupied, + 1 to see if its free slot
    int string_Length = new_Name.length();
    int sum = 0;
    for (int i = 0; i < string_Length; i++) { // loop to add all ASCII values
        sum += static_cast<int>(new_Name[i]);
    }
    sum *= string_Length;       // adds string length
    sum *= PRIME;           // adds prime number
    sum% A_SIZE;        // Mods the size of array to get an ID within range of array size

    return sum;
}

int main()
{
    Drawings draw;
    draw.make_Hash("Batman");
}
