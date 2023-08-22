#include "SqlBuilder.h"

std::string SqlSelectBuilder::BuildSelect() {
    std::string select = "SELECT";
    if (s.column.empty()) {
        select += " *";
    }
    else {
        std::for_each(s.column.begin(), s.column.end(), [&](auto str) {
            if (str == *(s.column.end() - 1)) {
                select += " " + str;
            }
            else {
                select += " " + str + ",";
            }
            });
    }

    if (!s.from.empty()) {
        select += " FROM " + s.from;
    }

    if (!s.where.empty()) {
        select += " WHERE";
        std::for_each(s.where.begin(), s.where.end(), [&](auto str) {
            if (str == *(s.where.end() - 1)) {
                select += " " + str;
            }
            else {
                select += " " + str + " AND";
            }
            });
    }

    select += ";";
    return select;
}

SqlSelectBuilder& SqlSelectBuilder::AddColumn(std::string str) noexcept {
    s.column.emplace_back(str);
    return *this;
}

SqlSelectBuilder& SqlSelectBuilder::AddColumn(std::vector<std::string>& v) noexcept {
    std::for_each(v.begin(), v.end(), [&](std::string str) {
        s.column.emplace_back(str);
        });

    return *this;
}

SqlSelectBuilder& SqlSelectBuilder::AddFrom(std::string str) {
    s.from = str;
    return *this;
}

SqlSelectBuilder& SqlSelectBuilder::AddWhere(std::string str1, std::string str2) noexcept {
    s.where.emplace_back(str1 + "=" + str2);
    return *this;
}

SqlSelectBuilder& SqlSelectBuilder::AddWhere(std::map<std::string, std::string>& m) noexcept {
    for (const auto& el : m) {
        s.where.emplace_back(el.second + "=" + el.first);
    }

    return *this;
};

AdvancedSqlSelectBuilder& AdvancedSqlSelectBuilder::AddWhereWithCondition(int id, char act) noexcept {
    std::string actStr(1, act);
    std::string str = "id" + actStr + std::to_string(id);
    s.where.emplace_back(str);
    return *this;
}