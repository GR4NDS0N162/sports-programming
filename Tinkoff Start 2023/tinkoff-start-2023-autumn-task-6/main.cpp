#include <iostream>
#include <vector>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;

struct Spirit {
    int count;
    int group;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Spirit> spirits(n);
    for (int i = 0; i < n; i++)
        spirits[i] = {1, i};

    vector<unordered_set<int>> groups;
    groups.reserve(n);
    for (int i = 0; i < n; i++)
        groups.emplace_back(unordered_set<int>{i});

    for (int i = 0, query, x, y; i < m; i++)
    {
        cin >> query;
        if (query == 1)
        {
            cin >> x >> y;
            x--, y--;

            int fromGroup, toGroup;
            if (groups[spirits[x].group].size() < groups[spirits[x].group].size())
            {
                fromGroup = spirits[x].group;
                toGroup = spirits[y].group;
            }
            else
            {
                fromGroup = spirits[y].group;
                toGroup = spirits[x].group;
            }

            for (auto spirit : groups[fromGroup])
            {
                groups[toGroup].insert(spirit);
                spirits[spirit].group = toGroup;
            }
            for (auto spirit : groups[toGroup])
                spirits[spirit].count++;
        }
        else if (query == 2)
        {
            cin >> x >> y;
            cout << (spirits[x - 1].group == spirits[y - 1].group ? "YES" : "NO") << endl;
        }
        else
        {
            cin >> x;
            cout << spirits[x - 1].count << endl;
        }
    }
}
