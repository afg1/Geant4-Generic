#ifndef CLP_H
#define CLP_H 1

#include <vector>
#include <string>

class CommandLineParser
{
    public:
        CommandLineParser(int argc, char** argv);
        ~CommandLineParser();
    
        std::vector<std::string> Parse();
    private:
        std::vector<std::string> commands;
};

    

#endif
