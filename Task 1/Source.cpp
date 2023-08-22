#include <iostream>

#include "SqlBuilder.h"

int main()
{
    SqlSelectBuilder ssb;
    AdvancedSqlSelectBuilder assb;
    std::string sel;

    std::map<std::string, std::string> m{
        {"22", "id"},
        {"30", "id"},
        {"2", "id"},
        {"jack", "name"},
        {"mike", "name"}
    };

    std::vector<std::string> v{ "name" , "debt" };

    //ssb.AddColumn("name").AddFrom("workers").AddWhere("id", "0");

    //ssb.AddColumn("id").AddColumn("name").AddFrom("hispanic");

    //ssb.AddFrom("apart").AddWhere("id", "0").AddWhere("date", "0").AddWhere("distr", "center");
    //ssb.AddFrom("shop");

    //ssb.AddColumn(v).AddFrom("clients").AddWhere(m);

    sel = ssb.BuildSelect();

    assb.AddColumn(v);
    assb.AddWhereWithCondition(10).AddWhereWithCondition(9, '>').AddWhereWithCondition(0, '<');
    //assb.AddWhereWithCondition(10);
    sel = assb.BuildSelect();

    std::cout << sel << std::endl;

}