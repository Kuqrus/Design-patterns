#pragma once
#include <iostream>
#include <map>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept;
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object);
    std::string GetData(const std::string& key) noexcept;

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots);
    std::string GetData(const std::string& key) noexcept;

private:
    VeryHeavyDatabase* real_db_;
    size_t shots_;
};

void DB();
