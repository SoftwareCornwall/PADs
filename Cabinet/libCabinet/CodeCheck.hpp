#ifndef CODECHECK_H
#define CODECHECK_H
#include <string>
#include <map>
#include <iostream>

class CodeCheck
{
    public:
        CodeCheck();
        bool inputCheck(std::string inputCode);
        void keyPressed(int keyID);
        std::string getCodeEntered();
    protected:
    private:
        std::string codeEntered = "";
        const int maxLength = 20;
        std::map<int,char> inputConversion;
};

#endif
