#include "Config.h"

Config::Config(const std::string &file) : file_(file)
{
    Trace(Level::DEBUG, __func__);

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
    Trace(Level::DEBUG, __func__);
}

nlohmann::json Config::Read() const
{
    Trace(Level::DEBUG, __func__);

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

    Trace(Level::INFORMATION, result.dump());

    return result;
}

void Config::Write(const nlohmann::json &data)
{
    Trace(Level::DEBUG, __func__);

    std::ofstream file(file_);

    if (!file.is_open())
    {
        throw std::runtime_error(Trace(Level::ERROR, "Failed to open config file"));        
    }
    
    file << data.dump(4);

    Trace(Level::INFORMATION, data.dump());

    file.close();
}