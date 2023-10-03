#pragma once

#include <nlohmann/json.hpp>

#include "Trace.h"

class Config
{
public:
    Config(const std::string &file);
    ~Config();

    nlohmann::json Read() const;
    void Write(const nlohmann::json &data);

private:
    std::string file_;
};