#include "CommandLineParser.hh"

CommandLineParser::CommandLineParser(int argc, char** argv)
{
    int n(0);
    while (n < argc)
    {
        commands.push_back((std::string)argv[n]);
        n++;
    }
    
}

CommandLineParser::~CommandLineParser()
{}

std::vector<std::string> CommandLineParser::Parse()
{
    return commands;
}