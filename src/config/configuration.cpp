#include "configuration.h"
#include <fstream>
#include <sstream>
#include "exceptions/config_file_not_found_exception.h"
#include "exceptions/config_attribute_not_found.h"

Configuration* Configuration::instance = nullptr;

Configuration* Configuration::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Configuration();
    }

    return instance;
}

void Configuration::ParseFile(std::string path)
{
    std::ifstream file(path);

    if (!file.good())
    {
        throw ConfigFileNotFoundException();
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;

        if (std::getline(is_line, key, ':'))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                configData[key] = value;
            }
        }
    }
}

bool Configuration::GetShouldStall()
{
    std::string shouldStall = GetAttribute("should_stall");

    return shouldStall == "true" ? true : false;
}

bool Configuration::GetShouldRoll()
{
    std::string shouldRoll = GetAttribute("should_roll");

    return shouldRoll == "true" ? true : false;
}

int Configuration::GetStallThreshold()
{
    try
    {
        std::string stallThreshold = GetAttribute("stall_threshold");
        return std::stoi(stallThreshold);
    }
    catch (const std::invalid_argument)
    {
        return 0;
    }

    return stallThreshold;
}

bool Configuration::GetShouldUseEasyStall()
{
    std::string shouldStall = GetAttribute("should_use_easy_stall");

    return shouldStall == "true" ? true : false;
}

std::string Configuration::GetAttribute(const std::string key)
{
    auto it = configData.find(key);
    if (it != configData.end())
    {
        return it->second;
    }

    throw ConfigAttributeNotFound(key);
}
