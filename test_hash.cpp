#include <iostream>
#include <functional>
#include <string>
using namespace std;
int main() {
    hash<string> hasher;
    cout << to_string(hasher("password123")) << endl;
}
