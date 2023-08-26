#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;

int main() {
    int s, n;
    cin >> s >> n;

    n %= (s + 1) * s / 2;

    for (int si = s; n >= si; si = si > 1 ? si - 1 : s)
        n -= si;

    cout << n;

    return EXIT_SUCCESS;
}
