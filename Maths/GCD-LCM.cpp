#include <iostream>

using namespace std;

// a -> dividend b -> divisor
int gcd(int a, int b) {
    if (a % b == 0) return b;
    // a % b
    return gcd(b, a % b);
}

int gcd2(int a, int b) {
    if (b == 0) return a;
    // a % b
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    int gcdVal = gcd2(a, b);
    return (a * b) / gcdVal;
}

int main() {
    cout << gcd(12, 4) << endl;
    cout << gcd2(18, 12) << endl;

    cout << gcd2(12, 18) << endl;
    cout << lcm(12, 18) << endl;

    return 0;
}