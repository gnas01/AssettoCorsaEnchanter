#pragma once

#include <stdexcept>
#include <string>

class ConfigAttributeNotFound : public std::exception {
private:
	std::string message;

public:
	ConfigAttributeNotFound(const std::string attributeName)

	{
		message = "Error: attribute '" + attributeName + "' not found in config file";
	}

	const char* what() const noexcept override {
		return message.c_str();
	}
};
