/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <iostream>

#define CRK_PRINT_TYPE_SIZE(Type) std::cout << #Type << ": " << sizeof(Type) << " bytes." << std::endl;

void printArithmeticTypesSize()
{
	CRK_PRINT_TYPE_SIZE(char);
	CRK_PRINT_TYPE_SIZE(signed char);
	CRK_PRINT_TYPE_SIZE(unsigned char);

	std::cout << std::endl;

	CRK_PRINT_TYPE_SIZE(short);
	CRK_PRINT_TYPE_SIZE(unsigned short);
	CRK_PRINT_TYPE_SIZE(int);
	CRK_PRINT_TYPE_SIZE(unsigned int);
	CRK_PRINT_TYPE_SIZE(long);
	CRK_PRINT_TYPE_SIZE(unsigned long);
	CRK_PRINT_TYPE_SIZE(long long);
	CRK_PRINT_TYPE_SIZE(unsigned long long);

	std::cout << std::endl;

	CRK_PRINT_TYPE_SIZE(float);
	CRK_PRINT_TYPE_SIZE(double);
	CRK_PRINT_TYPE_SIZE(long double);
}