#include <iostream>
using namespace std;

const int A_SIZE = 8;
const int SIZE = 8;

class Drawings {
private:
    static const int PRIME = 227;
    string names[A_SIZE];
    char drawing[A_SIZE][SIZE];
    int create_Hashkey1(string new_Name);
    int create_Hashkey2(string new_Name);
public:
    Drawings();
    void make_Hash(string new_Name);
    int get_Hash(string find_Name);
};

Drawings::Drawings() {      // constructor that resets the name array
    for (int i = 0; i < A_SIZE; i++) {
        names[i] = "0/+=";
    }
}

void Drawings::make_Hash(string new_Name) {       // complete function that makes hash keys
    int sum;
    static int count = 0;        // counter to make sure the program does not run too long, if it does, ask the user to make a different name

    sum = create_Hashkey1(new_Name);        // creates an independent hash key

    if ((names[sum] != "0/+=") && (names[sum] != new_Name)) {         // if the space is already occupied, run it through a different hash function
        sum += create_Hashkey2(new_Name);       // adds the new hash key together and mod it to fit array size
        sum = sum % A_SIZE;
    }

    if ((names[sum] != "0/+=") && (count < 4) && (names[sum] != new_Name)) {     // if there is still overlap, recurse through the function again
        count++;
        make_Hash(new_Name);
    }

    if ((count >= 4) || (names[sum] == new_Name)) {      // checks if it has either been looped too many times or if the name is the same
        cout << "Operation error. Please input a different name.\n";
        cin >> new_Name;
        count = 0;
        make_Hash(new_Name);
    }

    if (names[sum] == "0/+=") {       // if there are no overlaps, finalize the iD
        cout << "The sum is " << sum << " and the name is " << new_Name << endl;
        names[sum] = new_Name;
    }
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

int Drawings::get_Hash(string find_Name) {        // gets the name of the drawing name and outputs the hashkey for it
    int sum;
    static int count = 0;        // counter to make sure the program does not run too long, if it does, then the name is not right

    sum = create_Hashkey1(find_Name);        // creates an independent hash key

    if (names[sum] != find_Name) {         // if it does not equal to the name we need to find, run it through another create hashkey to maybe the correct one
        sum += create_Hashkey2(find_Name);       // adds the new hash key together and mod it to fit array size
        sum = sum % A_SIZE;
    }

    if ((count < 4) && (names[sum] != find_Name)) {     // if We still cannot find it, run through it again - Similar to making the hashkey 
        count++;
        make_Hash(find_Name);
    }

    if (names[sum] == find_Name) {         // executes if the name is found
        cout << "The name is " << names[sum] << " and is found at " << sum << endl;
        return sum;
    }

    cout << "The name cannot be found.\n";      // only executes if no name is found
    return -1;
}