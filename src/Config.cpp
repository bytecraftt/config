#include "Config.h"

Config::Config(const std::string &file) : file_(file)
{
    Trace trace(Level::DEBUG, __func__);

    if (file_.empty())
    {
        throw std::runtime_error(Trace(Level::ERROR, "Config file name should not be empty"));
    }

    std::ifstream ifile(file_);

    if (!ifile.good())
    {
        Trace(Level::WARRNING, "Config file should be created");
        std::ofstream ofile(file_);
        ofile << nlohmann::json::object();
        ofile.close();
        ifile.open(file_);
    }

    ifile.close();
}

Config::~Config()
{
    Trace trace(Level::DEBUG, __func__);
}

nlohmann::json Config::Read() const
{
    Trace trace(Level::DEBUG, __func__);

    nlohmann::json result;
    std::ifstream file(file_);

    if (!file.is_open())
    {
        throw std::runtime_error(Trace(Level::ERROR, "Failed to open config file"));
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    try
    {
        result = nlohmann::json::parse(content);
    }
    catch (const std::exception& exception)
    {
        Trace(Level::ERROR, exception.what());
    }

    return result;
}

void Config::Write(const nlohmann::json &data)
{
    Trace trace(Level::DEBUG, __func__);

    std::ofstream file(file_);

    if (!file.is_open())
    {
        throw std::runtime_error(Trace(Level::ERROR, "Failed to open config file"));        
    }
    
    file << data.dump(4);

    file.close();
}

std::string Config::Get(const std::initializer_list<std::string> &keys) const
{
    Trace trace(Level::DEBUG, __func__);

    nlohmann::json data = Read();

    for (const auto key : keys)
    {
        if (data.contains(key))
        {
            data = data[key];
        }
        else
        {
            throw std::runtime_error(Trace(Level::ERROR, "Wrong key: " + key));
        }
    }

    return data.dump();
}

void Config::Set(const std::initializer_list<std::string> &keys, const std::any &value)
{
    Trace trace(Level::DEBUG, __func__);

    nlohmann::json data = Read();
    nlohmann::json *part = &data;
    size_t size = keys.size();
    size_t count = 0;

    for (const auto &key : keys)
    {
        count++;

        if (part->contains(key))
        {
            if (count == size)
            {
                if (value.type() == typeid(int))
                {
                    (*part)[key] = std::any_cast<int>(value);
                }
                else if (value.type() == typeid(double))
                {
                    (*part)[key] = std::any_cast<double>(value);        
                }
                else if (value.type() == typeid(std::string))
                {
                    (*part)[key] = std::any_cast<std::string>(value);
                }
                else
                {
                    throw std::runtime_error(Trace(Level::ERROR, "Unsupported type"));
                }
            }
            else
            {
                part = &(*part)[key];
            }
        }
        else
        {
            throw std::runtime_error(Trace(Level::ERROR, "Wrong key: " + key));
        }
    }

    Write(data);
}