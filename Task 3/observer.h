#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class Logger {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};


class Observed {
public:
    void AddObserver(Logger* observer) {
        observers_.push_back(observer);
    }
    void RemoveObserver(Logger* observer) {
        auto it = std::remove(observers_.begin(), observers_.end(), observer);
        observers_.erase(it, observers_.end());
    }

    void Warning(const std::string& message) {
        std::cout << "Warning appeared!" << std::endl;
        for (const auto& observer : observers_) {
            observer->onWarning(message);
        }
        std::cout << std::endl;
    }
    void Error(const std::string& message) {
        std::cout << "Error appeared!" << std::endl;
        for (const auto& observer : observers_) {
            observer->onError(message);
        }
        std::cout << std::endl;
    }
    void FatalError(const std::string& message) {
        std::cout << "Fatal error appeared!" << std::endl;
        for (const auto& observer : observers_) {
            observer->onFatalError(message);
        }
        std::cout << std::endl;
    }

    ~Observed() {
        for (auto& observer : observers_) {
            RemoveObserver(observer);
        }
    }
private:
    std::vector<Logger*> observers_;
};

class LogWarning : public Logger {
    void onWarning(const std::string& message) override {
        std::cout << "Message: " << message << std::endl;
    }
};

class LogError : public Logger {
    void onError(const std::string& message) override {
        std::ofstream LogFile("ObserverLogger.txt", std::ios::app);
        if (!LogFile.is_open()) {
            throw std::runtime_error("Couldn't open file!");
        }
        LogFile << "Message: " << message << std::endl;
        LogFile.close();
    }
};

class LogFatal : public Logger {
    void onFatalError(const std::string& message) override {
        std::cout << "Message: " << message << std::endl;
        std::ofstream LogFile("ObserverLogger.txt", std::ios::app);
        if (!LogFile.is_open()) {
            throw std::runtime_error("Couldn't open file!");
        }
        LogFile << "Message: " << message << std::endl;
        LogFile.close();
    }
};

void StartObserverLogger() {
    auto obs = Observed();

    auto log_f = LogFatal();
    auto log_w = LogWarning();
    auto log_e = LogError();

    obs.AddObserver(&log_f);
    obs.AddObserver(&log_w);
    obs.AddObserver(&log_e);

    obs.FatalError("fatal error type #f_000");
    obs.Warning("warning type #w_000");
    obs.FatalError("fatal error type #f_001");
    obs.Error("error type #e_000");
    obs.Error("error type #e_001");
}
