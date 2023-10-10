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
    template <typename T>
    void Add(const std::initializer_list<std::string> &keys, const T &value)
    {
        Trace trace(Level::DEBUG, __func__);

        nlohmann::json data = Read();
        nlohmann::json *part = &data;

        for (const auto &key : keys)
        {
            (*part)[key];
            part = &(*part)[key];
        }
        
        *part = value;

        Write(data);
    }

private:
    std::string file_;
};