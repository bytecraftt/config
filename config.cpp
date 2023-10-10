#include "Config.h"

int main(int argc, char **argv)
{
    Trace::SetFileName("config.txt");
    Trace::SetTraceLevelFlag(Level::ALL);

    Config config("config.json");

    nlohmann::json data = {
        {"user", {
            {"firstname", "Serhii"},
            {"lastname", "Budianskyi"},
            {"age", 25},
            {"account", 3900452.49},
            {"dob", {14, 1, 1998}},
            {"sex", true}
        }}
    };

    config.Write(data);
    config.Read();

    std::cout << config.Get({"user", "age"}) << std::endl;
    config.Set({"user", "age"}, 5);
    std::cout << config.Get({"user", "age"}) << std::endl;
    config.Add<std::vector<int>>({"user", "count"}, {5,6,3});

    return 0;
}