// SaveDrawings.cpp : The program uses a hash function to store drawings entered by the user
// Alexander Ng
// 3/2021

#include <iostream>
#include <string.h>
#include "HashClass.h"
using namespace std;

int main()
{
    Drawings draw;
    draw.make_Hash("Batman");
    draw.make_Hash("Dingus");
    int x = draw.get_Hash("Batman");
}
