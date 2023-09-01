#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class LogMessage {
public:
    enum class Type {
        Fatal,
        Error,
        Warning,
        Unknown,
    };
    ~LogMessage() = default;
    virtual Type type() const = 0;
    virtual const std::string& message() const = 0;

};

class LogHandler {
public:
    explicit LogHandler(std::unique_ptr<LogHandler> next) : next_(std::move(next)) {}
    virtual ~LogHandler() = default;

    void reciveLog(const LogMessage& msg) {
        if (handlePush(msg)) {
            return;
        }
        if (!next_) {
            throw std::runtime_error("Error: Message should be handled!");
        }
        next_->reciveLog(msg);
    }

private:
    virtual bool handlePush(const LogMessage& msg) = 0;
    std::unique_ptr<LogHandler> next_;
};

class WarningHandler : public LogHandler {
public:
    using LogHandler::LogHandler;

private:
    bool handlePush(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Warning) {
            return false;
        }
        std::cout << "Warnig message: " << msg.message() << std::endl;
        return true;
    }
};

class ErrorHandler : public LogHandler {
public:
    using LogHandler::LogHandler;

private:
    bool handlePush(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Error) {
            return false;
        }
        std::ofstream LogFile("CoRLogger.txt", std::ios::app);
        if (!LogFile.is_open()) {
            throw std::runtime_error("Couldn't open file!");
        }
        LogFile << "Error message: " << msg.message() << std::endl;
        LogFile.close();
        return true;
    }
};

class FatalHandler : public LogHandler {
public:
    using LogHandler::LogHandler;

private:
    bool handlePush(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Fatal) {
            return false;
        }
        throw std::runtime_error("Fatal error appeared: " + msg.message());
    }
};

class UnknownHandler : public LogHandler {
public:
    using LogHandler::LogHandler;

private:
    bool handlePush(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::Unknown) {
            return false;
        }
        throw std::runtime_error("Unknown error appeared: " + msg.message());
    }
};

class WarningMessage : public LogMessage {
public:
    WarningMessage(std::string msg) : msg_(msg) {}
    Type type() const override { return Type::Warning; }
    const std::string& message() const override { return msg_; }

private:
    std::string msg_;
};

class ErrorMessage : public LogMessage {
public:
    ErrorMessage(std::string msg) : msg_(msg) {}
    Type type() const override { return Type::Error; }
    const std::string& message() const override { return msg_; }

private:
    std::string msg_;
};

class FatalMessage : public LogMessage {
public:
    FatalMessage(std::string msg) : msg_(msg) {}
    Type type() const override { return Type::Fatal; }
    const std::string& message() const override { return msg_; }

private:
    std::string msg_;
};

class UnknownMessage : public LogMessage {
public:
    UnknownMessage(std::string msg) : msg_(msg) {}
    Type type() const override { return Type::Unknown; }
    const std::string& message() const override { return msg_; }

private:
    std::string msg_;
};

void StartChainOfResponsobilityLogger() {
    auto handler_fatal = std::make_unique<FatalHandler>(nullptr);
    auto handler_error = std::make_unique<ErrorHandler>(std::move(handler_fatal));
    auto handler_warning = std::make_unique<WarningHandler>(std::move(handler_error));
    auto handler = std::make_unique<UnknownHandler>(std::move(handler_warning));

    try
    {
        handler->reciveLog(WarningMessage("code #100"));
        handler->reciveLog(ErrorMessage("code #010"));

        handler->reciveLog(FatalMessage("code #001"));

        handler->reciveLog(WarningMessage("code #200"));

        handler->reciveLog(UnknownMessage("Somthing wrong happened!"));

    }
    catch (const std::exception& e)
    {
        std::cout << "Program crashed!\nReport: " << e.what() << std::endl;
    }
}
