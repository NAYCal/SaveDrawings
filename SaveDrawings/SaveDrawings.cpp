// SaveDrawings.cpp : The program uses a hash function to store drawings entered by the user
// Alexander Ng
// 3/2021

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "HashClass.h"
using namespace std;

void get_Draw(Drawings& draw);

int main()
{
    Drawings draw;      // declare variable
    const int SIZE = draw.out_Sizes();

    get_Draw(draw);
}

void get_Draw(Drawings &draw) {         // function that gets the drawing and a new name for the drawing from the user
    string input;

    cout << "Please enter the name of the drawing.\n";
    getline(cin, input);
    draw.in_Hash(input);

    int iD = draw.out_Hash(input);

    cout << "\nYou can now start drawing! Enter the ASCII characters into any shape you prefer\n"
         << "Enter 'Done' to finish the drawing!\n";

    do {
        cout << "\n<<====================CANVAS====================>>\n";
        draw.out_Drawing(iD);
        getline(cin, input);
        draw.in_Drawing(input, iD);
        if (input == "Done") {
            cout << "\n<<====================CANVAS====================>>\n";
            cout << "Are you sure to quit? Enter 'Y' for yes and anything else to add 'Done' onto the canvas.\n";
            cin >> input;

            if (input != "Y") {
                input = "Done";
            }
        }
    } while(input != "Y");

    
}
