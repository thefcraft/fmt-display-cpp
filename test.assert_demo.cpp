#include <iostream>
#include "test.assert.h"
using namespace std;
void solver(){
    int a, b;
    cin>>a>>b;
    cout<<a+b<<endl; // endl or \n
}
int main(){
    vector<int> a = {1,2,3,4,5};
    debug(a);
    RUN_TESTS;
    return 0;
}

MAKE_TESTS{
    It(add small numbers){
        tin.set("3 4");
        solver();
        asserttout("7\n");
    }
    It(add larger numbers){
        tin.set("99", "99");
        solver();
        asserttout("198\n");
    }
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
    // {
    //     tout.clear(); // have to call if you don't want to use It(){}
    //     tin.set("6", "8");
    //     solver();
    //     asserttout("14\n");
    // } // UNSUPPORTED FROM NOW or call mannual ~tin.clear(), please use empty It(){} insted
}
