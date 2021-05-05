// SaveDrawings.cpp : The program uses a hash function to store drawings entered by the user
// Alexander Ng
// 3/2021

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "HashClass.h"
using namespace std;

Drawings draw;      // declare as global variable since it will be the only variable used, so no reason to pass for local variable - reducing complications

void menu();
void get_Draw();
void out_Draw();
void display();
void file_Save();

int main()
{
    const int SIZE = draw.out_Sizes();
    menu();
    file_Save();
}

void menu() {
    string input;

    cout << "<<====================MENU====================>>\n"
        << "1. Enter a new drawing\n"
        << "2. Find a drawing\n"
        << "3. Display all drawings\n"
        << "4. Done\n"
        << "<<=============================================>>\n"
        << "Enter an option\n\n";

    cin >> input;

    // if's that goes to different modules based on user input
    if ((input == "1") || (input == "Enter a new drawing")) {
        cin.ignore(256, '\n');
        get_Draw();
    }
    else if ((input == "2") || (input == "Find a drawing")) {
        cin.ignore(256, '\n');
        out_Draw();
    }
    else if ((input == "3") || (input == "Display all drawings")) {
        cin.ignore(256, '\n');
        display();
    }
    else if ((input == "4") || (input == "Done")) {
        return;
    }

    menu();
}

void get_Draw() {         // function that gets the drawing and a new name for the drawing from the user
    string input;

    cout << "\nPlease enter the name of the drawing.\n";
    getline(cin, input);
    draw.in_Hash(input);

    int iD = draw.out_Hash(input);

    cout << "\nYou can now start drawing! Enter the ASCII characters into any shape you prefer\n"
        << "Enter 'Done' to finish the drawing!\n";

    do {        // loops that allow user to enter drawing until they enter Done then Y so to make sure that is what they want to enter
        cout << "\n<<====================CANVAS====================>>\n";
        cout << draw.out_Drawing(iD) << endl;       // prints the drawing of that iD
        getline(cin, input);        // gets the user input of ASCII

        if (input == "Done") {
            cout << "\n<<====================CANVAS====================>>\n";
            cout << "Are you sure to quit? Enter 'Y' for yes and anything else to add 'Done' onto the canvas.\n";
            cin >> input;

            if ((input != "Y") && (input != "y")) {
                input = "Done";
            }
            else {
                cin.ignore(256, '\n');
                return;
            }
        }

        draw.in_Drawing(input, iD);         // stores the ASCII to drawing
    } while (input != "Y");
}

// function that asks the user to choose which drawing to display
void out_Draw() {
    cout << "\nDrawings stored:\n"
        << "<<====================STORED====================>>\n";

    int SIZE = draw.out_Sizes();        // gets the total size of arrays

    for (int i = 0; i < SIZE; i++) {        // loop to output all the names
        if (draw.out_Name(i) != "0/+=-1") {
            cout << "ID #" << i << " Name: " << draw.out_Name(i) << endl;
        }
    }

    cout << "\n<<==============================================>>\n"
        << "Which drawings would you like to see?\n";

    string input;
    getline(cin, input);

    int iD = draw.out_Hash(input);      // gets the hashkey for the name

    if (iD == -1) {     // Gets -1 if it is an invalid key, aka it is not found
        cout << "The drawing cannot be found.\n";
        return;
    }

    cout << draw.out_Drawing(iD) << endl;       // outputs drawing based on the hashkey

}

// function that displays all saved ASCII drawings
void display() {
    int SIZE = draw.out_Sizes();

    for (int i = 0; i < SIZE; i++) {        // loop to output all the names
        if (draw.out_Name(i) != "0/+=-1") {     // checks if the name is empty
            cout << "ID #" << i << " Name: " << draw.out_Name(i) << endl;       // outputs hashkey of drawing & name
            cout << "<<====================CANVAS====================>>\n"
                << draw.out_Drawing(i) // outputs drawings
                << "<<\n\n====================CANVAS====================>>\n\n";
        }
    }
}

//saves all current drawings onto a savefile
void file_Save() {
    ofstream ASCII_Images("ASCII_Images.txt");     // creates save file "ASCII_Images.txt" to save drawings to

    int SIZE = draw.out_Sizes();

    ASCII_Images << SIZE << endl;

    for (int i = 0; i < SIZE; i++) {        // loops through the total number of drawings
        ASCII_Images << draw.out_Name(i) << endl;           // gets the name first
        if (draw.out_Name(i) != "0/+=-1") {     // if there is a user set name
            ASCII_Images << "pInKlEaF3&." << endl;         // set up boundaries to know when the drawing begins and ends
            ASCII_Images << draw.out_Drawing(i) << endl;           // store the drawing as well
            ASCII_Images << "pInKlEaF3&." << endl;
        }
    }

    ASCII_Images.close();       // close the file
}