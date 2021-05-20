#include <iostream>
#include <string>
using namespace std;

const int A_SIZE = 8;

class Drawings {
private:
    static const int PRIME = 227;
    string names[A_SIZE];
    string drawing[A_SIZE];
    int create_Hashkey1(string new_Name);
    int create_Hashkey2(string new_Name);
public:
    Drawings();
    void in_Name(int iD, string name) { names[iD] = name; }
    int out_Sizes() { return A_SIZE; }
    string out_Name(int iD) { return names[iD]; }
    void in_Hash(string new_Name);
    int out_Hash(string find_Name);
    void in_Drawing(string line, int iD);
    string out_Drawing(int iD);
    void void_Drawing(int iD);
};

Drawings::Drawings() {      // constructor that resets the name array
    for (int i = 0; i < A_SIZE; i++) {
        names[i] = "0/+=-1";
    }
}

void Drawings::in_Hash(string new_Name) {       // complete function that makes hash keys
    int sum;
    static int count = 0;        // counter to make sure the program does not run too long, if it does, ask the user to make a different name

    sum = create_Hashkey1(new_Name);        // creates an independent hash key

    if ((names[sum] != "0/+=-1") && (names[sum] != new_Name)) {         // if the space is already occupied, run it through a different hash function
        sum += create_Hashkey2(new_Name);       // adds the new hash key together and mod it to fit array size
        sum = sum % A_SIZE;
    }

    if ((names[sum] != "0/+=-1") && (count < 4) && (names[sum] != new_Name)) {     // if there is still overlap, recurse through the function again
        count++;
        in_Hash(new_Name);
    }

    if ((count >= 4) || (names[sum] == new_Name)) {      // checks if it has either been looped too many times or if the name is the same
        cout << "Operation error. Please input a different name.\n";
        cin >> new_Name;
        count = 0;
        in_Hash(new_Name);
    }

    if (names[sum] == "0/+=-1") {       // if there are no overlaps, finalize the iD
        //cout << "The hashkey is " << sum << " and the name is " << new_Name << endl;
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
    sum = sum % A_SIZE;        // Mods the size of array to get an ID within range of array size

    return sum;
}

int Drawings::out_Hash(string find_Name) {        // gets the name of the drawing name and outputs the hashkey for it
    int sum;
    static int count = 0;        // counter to make sure the program does not run too long, if it does, then the name is not right

    sum = create_Hashkey1(find_Name);        // creates an independent hash key

    if (names[sum] != find_Name) {         // if it does not equal to the name we need to find, run it through another create hashkey to maybe the correct one
        sum += create_Hashkey2(find_Name);       // adds the new hash key together and mod it to fit array size
        sum = sum % A_SIZE;
    }

    if ((count < 4) && (names[sum] != find_Name)) {     // if We still cannot find it, run through it again - Similar to making the hashkey 
        count++;
        out_Hash(find_Name);
    }

    if (names[sum] == find_Name) {         // executes if the name is found
        //cout << "The name is " << names[sum] << " and is found at " << sum << endl;
        return sum;
    }

    cout << "The name cannot be found.\n";      // only executes if no name is found
    return -1;
}

void Drawings::in_Drawing(string line, int iD) {         // gets the ASCII drawing of that line and adds it in to the drawing
    //cout << "This is within the in_Drawing class function\n";
    //cout << "Line is " << line << endl;

    if (drawing[iD].empty()) {         // checks if the string is empty

       //cout << "The line is originally empty\n";
        drawing[iD] = line;         // if it is empty, directly add it into the line
        //cout << "The drawing[" << iD << "] is " << drawing[iD] << endl;
        return;         // return to save computational time
    }

    //cout << "The line is not empty\n";
    drawing[iD].append("\n");         // this helps to move to next line

    drawing[iD].append(line);       // adds line to drawing variable
}

string Drawings::out_Drawing(int iD) {        // prints out the drawing
    if (drawing[iD].empty()) {
        return "Error. No drawing found!\n";
    }
    else {
        return drawing[iD];
    }
    
}

void Drawings::void_Drawing(int iD) {       // deletes the drawing
    names[iD] = "0/+=-1";
    drawing[iD].clear();
}
