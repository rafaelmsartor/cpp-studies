#pragma once

#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase
{
    typedef PersonAddressBuilder Self;

public:
    explicit PersonAddressBuilder( Person& person )
        : PersonBuilderBase{ person }
    {}

    Self& at( std::string streetAddress )
    {
        person.streeAddress = streetAddress;
        return *this;
    }

    Self& withPostCode( std::string postCode )
    {
        person.postCode = postCode;
        return *this;
    }

    Self& in( std::string city )
    {
        person.city = city;
        return *this;
    }
};
