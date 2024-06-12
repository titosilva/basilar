#include "src/simple.hpp"
#include "src/subfolder/sub.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << sum(1, 2) << endl;
    cout << sub(1, 2) << endl;
    return 0;
}