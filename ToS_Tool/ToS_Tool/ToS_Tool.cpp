// ToS_Tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\..\..\Libraries\include\opencv2\opencv.hpp"

#include "Town.h"

int main()
{
	Town town(standard, Player(1, "me"), Role::Escort );
	town.confirm(Role::Witch);
	town.print();
    return 0;
}

