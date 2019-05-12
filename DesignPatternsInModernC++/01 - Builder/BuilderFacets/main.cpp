
#include <iostream>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

using namespace std;

int main()
{
    Person p = Person::create()
        .lives()
            .at( "Does Not Exist St., 404" )
            .withPostCode( "88000-00" )
            .in( "Florianopolis" )
        .works()
            .at( "My Fake Company" )
            .asA( "Software Developer" )
            .earning( 6666.66 );
    
    cout << p << endl;
    return 0;
}