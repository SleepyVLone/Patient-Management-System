#include <iostream>
#include <functional>
#include <string>
using namespace std;
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}
int main() {
    cout << hashPassword("password123") << endl;
}
