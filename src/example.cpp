#include "../include/example.h"

Dummy::Dummy() {

}

bool Dummy::doSomething() {
    // Do silly things, using some C++17 features to enforce C++17 builds only.
    
    return true;
}


#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "../tests/doctest/doctest.h"
TEST_CASE("we can have tests written here, to test impl. details")
{
    CHECK(true);
}
#endif
