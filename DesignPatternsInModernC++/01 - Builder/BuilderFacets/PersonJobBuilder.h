
#pragma once

#include <string>

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder Self;

public:
    explicit PersonJobBuilder( Person& person )
        : PersonBuilderBase{ person }
    {}

    Self& at( std::string company )
    {
        person.companyName = company;
        return *this;
    }

    Self& asA( std::string position )
    {
        person.position = position;
        return *this;
    }

    Self& earning( double income )
    {
        person.income = income;
        return *this;
    }
};
