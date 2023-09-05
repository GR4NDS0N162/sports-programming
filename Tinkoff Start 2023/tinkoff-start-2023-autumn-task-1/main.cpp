#include <iostream>

using std::cin;
using std::cout;

int main() {
    int n, s;
    cin >> n >> s;

    int a_max = 0;
    for (int a, i = 0; i < n; i++)
    {
        cin >> a;
        if (a > a_max && a <= s)
            a_max = a;
    }

    cout << a_max;
}
