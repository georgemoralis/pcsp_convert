using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Syscallv15.h"

namespace jpcsp
{

int **Syscallv15::syscalls = new int*[676]
{
	new int[2] {0x2000, 0xca04a2b9},
	new int[2] {0x2001, 0xd61e6961},
	new int[2] {0x2002, 0xfb8e22ec},
	new int[2] {0x2003, 0x8a389411},
	new int[2] {0x2004, 0x5cb5a78b},
	new int[2] {0x2005, 0x7860e0dc},
	new int[2] {0x2006, 0xfc4374b8},
	new int[2] {0x2007, 0xd2e8363f},
	new int[2] {0x2008, 0xeee43f47},
	new int[2] {0x2009, 0x6e9ea350},
	new int[2] {0x200a, 0x0c106e53},
	new int[2] {0x200b, 0x72f3c145},
	new int[2] {0x200c, 0x369eeb6b},
	new int[2] {0x200d, 0xe81caf8f},
	new int[2] {0x200e, 0xedba5844},
	new int[2] {0x200f, 0xc11ba8c4},
	new int[2] {0x2010, 0xba4051d6},
	new int[2] {0x2011, 0x2a3d44ff},
	new int[2] {0x2012, 0x349d6d6c},
	new int[2] {0x2013, 0x730ed8bc},
	new int[2] {0x2014, 0x9ace131e},
	new int[2] {0x2015, 0x82826f70},
	new int[2] {0x2016, 0xd59ead2f},
	new int[2] {0x2017, 0xfccfad26},
	new int[2] {0x2018, 0x9944f31f},
	new int[2] {0x2019, 0x75156e8f},
	new int[2] {0x201a, 0x278c0df5},
	new int[2] {0x201b, 0x840e8133},
	new int[2] {0x201c, 0xceadeb47},
	new int[2] {0x201d, 0x68da9e36},
	new int[2] {0x201e, 0xbd123d9e},
	new int[2] {0x201f, 0x1181e963},
	new int[2] {0x2020, 0xd6da4ba1},
	new int[2] {0x2021, 0x28b6489c},
	new int[2] {0x2022, 0x3f53e640},
	new int[2] {0x2023, 0x4e3a1105},
	new int[2] {0x2024, 0x6d212bac},
	new int[2] {0x2025, 0x58b1f937},
	new int[2] {0x2026, 0x8ffdf9a2},
	new int[2] {0x2027, 0xbc6febc5},
	new int[2] {0x2028, 0x55c20a00},
	new int[2] {0x2029, 0xef9e4c70},
	new int[2] {0x202a, 0x1fb15a32},
	new int[2] {0x202b, 0x812346e4},
	new int[2] {0x202c, 0x402fcf22},
	new int[2] {0x202d, 0x328c546a},
	new int[2] {0x202e, 0x30fd48f0},
	new int[2] {0x202f, 0xcd203292},
	new int[2] {0x2030, 0xa66b0120},
	new int[2] {0x2031, 0x8125221d},
	new int[2] {0x2032, 0x86255ada},
	new int[2] {0x2033, 0xe9b3061e},
	new int[2] {0x2034, 0x18260574},
	new int[2] {0x2035, 0xf3986382},
	new int[2] {0x2036, 0x0d81716a},
	new int[2] {0x2037, 0x87d4dd36},
	new int[2] {0x2038, 0xa8e8c846},
	new int[2] {0x2039, 0x7c0dc2a0},
	new int[2] {0x203a, 0xf0b7da1c},
	new int[2] {0x203b, 0x876dbfad},
	new int[2] {0x203c, 0x7c41f2c2},
	new int[2] {0x203d, 0x884c9f90},
	new int[2] {0x203e, 0x74829b76},
	new int[2] {0x203f, 0xfbfa697d},
	new int[2] {0x2040, 0xdf52098f},
	new int[2] {0x2041, 0x349b864d},
	new int[2] {0x2042, 0x33be4024},
	new int[2] {0x2043, 0x56c039b5},
	new int[2] {0x2044, 0x89b3d48c},
	new int[2] {0x2045, 0xbed27435},
	new int[2] {0x2046, 0xec0a693f},
	new int[2] {0x2047, 0xaf36d708},
	new int[2] {0x2048, 0xb736e9ff},
	new int[2] {0x2049, 0x1d371b8a},
	new int[2] {0x204a, 0x39810265},
	new int[2] {0x204b, 0xc07bb470},
	new int[2] {0x204c, 0xed1410e0},
	new int[2] {0x204d, 0xd979e9bf},
	new int[2] {0x204e, 0xe7282cb6},
	new int[2] {0x204f, 0x623ae665},
	new int[2] {0x2050, 0xf6414a71},
	new int[2] {0x2051, 0xa8aa591f},
	new int[2] {0x2052, 0xd8199e4c},
	new int[2] {0x2053, 0x0e927aed},
	new int[2] {0x2054, 0x110dec9a},
	new int[2] {0x2055, 0xc8cd158c},
	new int[2] {0x2056, 0xba6b92e2},
	new int[2] {0x2057, 0xe1619d7c},
	new int[2] {0x2058, 0xdb738f35},
	new int[2] {0x2059, 0x82bc5777},
	new int[2] {0x205a, 0x369ed59d},
	new int[2] {0x205b, 0x6652b8ca},
	new int[2] {0x205c, 0xb2c25152},
	new int[2] {0x205d, 0x7e65b999},
	new int[2] {0x205e, 0xdaa3f564},
	new int[2] {0x205f, 0x20fff560},
	new int[2] {0x2060, 0x328f9e52},

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
