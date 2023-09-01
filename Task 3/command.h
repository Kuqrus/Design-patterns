#pragma once
#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogIntoConsole : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "Message: " << message << std::endl;
    }
};

class LogIntoFile : public LogCommand {
public:
    void print(const std::string& message) override {
        std::fstream LogFile;
        LogFile.open("CommandLogger.txt", std::ios::app);
        if (!LogFile.is_open()) {
            throw std::runtime_error("Couldn't open file!");
        }
        LogFile << "Message: " << message << std::endl;
        LogFile.close();

    }

private:
};

void print(LogCommand& l, std::string errorMsg) {
    try
    {
        l.print(errorMsg);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


}
void StartCommandLogger() {
    auto console = LogIntoConsole();
    auto file = LogIntoFile();

    print(console, "Console error #01");
    print(file, "File error #01");
    print(file, "File error #02");
}