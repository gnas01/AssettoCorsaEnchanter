#pragma once
#include <iostream>
#include <string>
#include <map>

class Configuration
{
public:
    static Configuration* GetInstance();

    void ParseFile(std::string path);

    bool GetShouldStall();
    bool GetShouldRoll();
    int GetStallThreshold();


private:
    static Configuration* instance;

    std::string path;
    std::map<std::string, std::string> configData;

    bool shouldStall;
    bool shouldRoll;
    int stallThreshold;

    std::string GetAttribute(const std::string key);
};

