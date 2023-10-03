#include "Config.h"

int main(int argc, char **argv)
{
    Trace::SetFileName("config.txt");
    Trace::SetTraceLevelFlag(Level::ALL);

    Config config("config.json");

    return 0;
}