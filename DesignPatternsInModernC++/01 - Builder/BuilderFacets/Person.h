#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class PersonBuilder;

class Person
{
    //address
    std::string streeAddress, postCode, city;

    //employment
    std::string companyName, position;
    double income;

    Person() {}

public:
    static PersonBuilder create();

    Person( Person const& ) = default;
    Person& operator=( Person const& ) = default;
    Person( Person&& ) = default;
    Person& operator=( Person&& ) = default;

    friend std::ostream& operator<<( std::ostream& os, Person const& person )
    {
        return os 
            << "Street Address: " << person.streeAddress << '\n'
            << "Post Code: " << person.postCode << '\n'
            << "City: " << person.city << '\n'
            << "Company Name: " << person.companyName << '\n'
            << "Position: " << person.position << '\n'
            << "Income: " << std::setprecision(2) << std::fixed << person.income << '\n';
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};