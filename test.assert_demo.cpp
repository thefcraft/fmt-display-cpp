#include <iostream>
#include "test.assert.h"
using namespace std;
int main(){
    vector<int> a = {1,2,3,4,5};
    debug(a);
    RUN_TESTS;
    return 0;
}

MAKE_TESTS{
    It(divide by zero){
        vector<int> a = {1,2,3,4,5};
        vector<int> b = {1,2,23,23,23};
        asserteq(a, b);
    }
    It(mul by zero){
        asserteq("test", "test");
    }
    It(randome testcase){
        asserteq("test", "test");
    }
    {
        asserteq("test", "test");   
    }
    {
        assert((bool)72);
    }
    {
        assert(false);
    }
}
