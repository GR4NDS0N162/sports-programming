#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::numeric_limits;
using std::min;

int main() {
    string s;
    cin >> s;

    unordered_map<char, int> letters;
    for (auto c : s)
        letters[c]++;

    string sheriff = "sheriff";
    unordered_map<char, int> target_letters;
    for (auto c : sheriff)
        target_letters[c]++;

    int count = numeric_limits<int>::max();
    for (const auto& [k, x] : target_letters)
        count = min(count, letters[k] / x);

    cout << count;
}
