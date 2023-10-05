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
    std::string Get(const std::initializer_list<std::string> &keys) const;
    void Set(const std::initializer_list<std::string> &keys, const std::any &value);

private:
    std::string file_;
};