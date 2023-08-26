#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<int> frequency('z' - 'a' + 1, 0);
    for (auto c : s)
        frequency[c - 'a']++;

    std::sort(frequency.begin(), frequency.end());

    int i = 0;
    while (i < frequency.size())
    {
        if (k >= frequency[i])
            k -= frequency[i];
        else
            break;
        i++;
    }

    cout << frequency.size() - i;

    return EXIT_SUCCESS;
}
