#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::reverse;
using std::endl;

struct DP {
    int value;
    int j;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> weights;
    weights.reserve(m * 2);
    for (int a, i = 0; i < m; i++)
    {
        cin >> a;
        weights.push_back(a);
        weights.push_back(a);
    }

    int count = m * 2;
    int capacity = n;

    // dp[i][j].value хранит максимальное значение, которое может быть достигнуто с помощью
    // вес меньше или равен `j`, используя элементы до первых `i` элементов
    vector<vector<DP>> dp(count + 1, vector<DP>(capacity + 1));

    for (int i = 0, j = 0; j <= capacity; j++)
        dp[i][j].value = 0;

    for (int i = 1; i <= count; i++) // первые элементы
    {
        for (int j = 0; j <= capacity; j++) // максимальный вес
        {
            if (weights[i - 1] > j)
            { dp[i][j] = dp[i - 1][j]; }
            else
            {
                if (dp[i - 1][j - weights[i - 1]].value + weights[i - 1] > dp[i - 1][j].value)
                {
                    dp[i][j].value = dp[i - 1][j - weights[i - 1]].value + weights[i - 1];
                    dp[i][j].j = j - weights[i - 1];
                }
                else
                { dp[i][j] = dp[i - 1][j]; }
            }
        }
    }

    if (dp[count][capacity].value < capacity)
    {
        cout << -1;
        return 0;
    }

    vector<int> ans;
    for (int i = count, j = capacity; i > 0; i--)
    {
        if (dp[i][j].value != dp[i - 1][j].value)
        {
            ans.push_back(weights[i - 1]);
            j = dp[i][j].j;
        }
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
        cout << " " << ans[i];
}
