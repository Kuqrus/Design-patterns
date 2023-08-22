#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

class SqlSelect {
public:
    std::vector<std::string> column;
    std::string from;
    std::vector<std::string> where;
};

class SqlSelectBuilder {
public:
    SqlSelectBuilder() {};

    std::string BuildSelect();

    SqlSelectBuilder& AddColumn(std::string str) noexcept;

    SqlSelectBuilder& AddColumn(std::vector<std::string>& v) noexcept;

    SqlSelectBuilder& AddFrom(std::string str);

    SqlSelectBuilder& AddWhere(std::string str1, std::string str2) noexcept;

    SqlSelectBuilder& AddWhere(std::map<std::string, std::string>& m) noexcept;

protected:
    SqlSelect s;
};

class AdvancedSqlSelectBuilder : public SqlSelectBuilder {
public:
    explicit AdvancedSqlSelectBuilder() {};

    AdvancedSqlSelectBuilder& AddWhereWithCondition(int id, char act = '=') noexcept;

private:
    SqlSelectBuilder::s;
};
