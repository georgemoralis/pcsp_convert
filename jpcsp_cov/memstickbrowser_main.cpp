#pragma once

#include <string>
#include <vector>
#include "MemStickBrowser.h"

int main(int argc, char **argv)
{
	std::vector<std::string> args(argv + 1, argv + argc);
	jpcsp::GUI::MemStickBrowser::main(args);
}

