// AssetoCorsaEnchanter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "process.h"
#include "dynamic_address.h"

int main()
{
    Process assetoCorsa(L"acs.exe");
    DynamicAddress idleRpm(&assetoCorsa, 0x01559AF0, { 0x58, 0x60, 0x38, 0x70, 0x8, 0x508 });
    DynamicAddress currentRpm(&assetoCorsa, 0x01559AF0, { 0x38, 0xC0, 0x10, 0xF8, 0x48, 0x20, 0x5D8 });

    std::cout << idleRpm.Read<int>();
    idleRpm.Write(3000);
    std::cout << idleRpm.Read<int>();

    getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
