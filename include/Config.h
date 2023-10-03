#pragma once

#include <nlohmann/json.hpp>

#include "Trace.h"

class Config
{
public:
    Config(const std::string &file);
    ~Config();



private:
    std::string file_;
};