#include "dotenv.h"
#include <iostream>

using namespace std;
using namespace dotenv;

int main() {
    if (!env.load_dotenv()) {
        cerr << "Failed to load .env file" << endl;
        return 1;
    }
    if (env.has("DB_NAME")) {
        cout<<"DB_NAME exists"<<endl;
    }
    cout<<"================================================================"<<endl;
    // Get all variables
    for (const auto& [key, value] : env.all()) {
        cout << key << "=" << value << endl;
    }
    cout<<"================================================================"<<endl;

    cout << "DB_NAME: " << env["DB_NAME"] << endl;
    cout << "eval \"" << env["COMMAND"] << " " << env["HOST"] << "\"" << endl;
    
    // You can also use the safer get() method that returns an optional
    if (auto db_name = env.get("DB_NAME")) {
        cout << "Database name: " << *db_name << endl;
    }
    
    return 0;
}