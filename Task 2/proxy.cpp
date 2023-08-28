#include "proxy.h"

std::string VeryHeavyDatabase::GetData(const std::string& key) const noexcept {
    return "Very Big Data String: " + key;
}

CacheProxyDB::CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
std::string CacheProxyDB::GetData(const std::string& key) noexcept {
    if (cache_.find(key) == cache_.end()) {
        std::cout << "Get from real object\n";
        cache_[key] = real_db_->GetData(key);
    }
    else {
        std::cout << "Get from cache\n";
    }
    return cache_.at(key);
}

OneShotDB::OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : real_db_(real_object), shots_(shots) {}
std::string OneShotDB::GetData(const std::string& key) noexcept {
    if (shots_ > 0) {
        shots_--;
        return real_db_->GetData(key);
    }
    else {
        return "the limit has been reached";
    }
}

void DB() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);

    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
}