#pragma once

#include <stdexcept>

class DuplicateAliasException: public std::exception
{
public:
	const char* what() const noexcept override 
	{
		return "Error: Duplicate alias found";
	}
};

