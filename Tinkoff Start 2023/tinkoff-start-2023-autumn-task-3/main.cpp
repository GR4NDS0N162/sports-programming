#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using std::cin;
using std::cout;
using std::vector;
using std::unordered_map;
using std::numeric_limits;
using std::min;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    int left = 0;
    int right = n - 1;
    while (left <= right && a[left] == b[left])
        left++;
    while (left <= right && a[right] == b[right])
        right--;
    if (left > right)
    {
        cout << "YES";
        return 0;
    }

    unordered_map<int, int> balance;
    for (int i = left; i <= right; ++i)
    {
        balance[a[i]]++;
        balance[b[i]]--;
    }
    for (const auto [_, val] : balance)
    {
        if (val != 0)
        {
            cout << "NO";
            return 0;
        }
    }

    for (int i = left; i < right; ++i)
    {
        if (b[i] > b[i + 1])
        {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
}
