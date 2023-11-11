#pragma once

#include <stdexcept>

class ConfigFileNotFoundException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: Config file not found";
	}
};

