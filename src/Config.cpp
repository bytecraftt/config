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