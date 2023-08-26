#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::abs;

void printAnswer(const vector<int>& a) {
    for (auto ai : a)
    { cout << ai << " "; }
}

int main() {
    int n, c, d;
    cin >> n >> c >> d;

    vector<int> a(n);

    auto compare = [&a](auto lhs, auto rhs) { return abs(a[lhs]) > abs(a[rhs]); };
    priority_queue<int, vector<int>, decltype(compare)> index(compare);

    int countPositive = 0;
    int countNegative = 0;
    int countZero = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        index.push(i);

        if (a[i] < 0)
        { countNegative++; }
        else if (a[i] > 0)
        { countPositive++; }
        else // a[i] == 0
        { countZero++; }
    }

    if (c < countZero) // Изменений не хватит, чтобы изменить все нулевые элементы
    {
        printAnswer(a);
        return EXIT_SUCCESS;
    }
    // Изменений хватит, чтобы избавиться от нулевых элементов

    if (countZero > 0)
    {
        if (countNegative % 2 == 0)
        {
            int idx = index.top();
            index.pop();

            a[idx] -= d;
            c--;
            countZero--;
            countNegative++;

            index.push(idx);
        }

        for (int idx; countZero > 0;)
        {
            idx = index.top();
            index.pop();

            a[idx] += d;
            c--;
            countZero--;
            countPositive++;

            index.push(idx);
        }
    }
    // Нули отсутствуют

    if (c <= 0) // Изменений не осталось
    {
        printAnswer(a);
        return EXIT_SUCCESS;
    }
    // Изменения остались

    if (countNegative % 2 == 0)
    {
        if ((a[index.top()] > 0 && a[index.top()] - d * c < 0) ||
            (a[index.top()] < 0 && a[index.top()] + d * c > 0)) // Изменений хватает, чтобы изменить знак произведения
        {
            int idx = index.top();
            index.pop();

            int count = abs(a[idx]) / d + 1;
            if (a[idx] > 0)
            {
                a[idx] -= d * count;
                countPositive--;
                countNegative++;
            }
            else
            {
                a[idx] += d * count;
                countNegative--;
                countPositive++;
            }
            c -= count;

            index.push(idx);
        }
        else if ((a[index.top()] > 0 && a[index.top()] - d * c == 0) ||
                 (a[index.top()] < 0 && a[index.top()] + d * c == 0)) // Изменений хватит, только на произведение = 0
        {
            int idx = index.top();
            index.pop();

            a[idx] = 0;

            printAnswer(a);
            return EXIT_SUCCESS;
        }
        else // Изменений не хватает, чтобы изменить знак произведения
        {
            for (int idx; c > 0;)
            {
                idx = index.top();
                index.pop();

                if (a[idx] > 0)
                { a[idx] -= d; }
                else
                { a[idx] += d; }
                c--;

                index.push(idx);
            }

            printAnswer(a);
            return EXIT_SUCCESS;
        }
    }
    // Произведение будет отрицательным

    for (int idx; c > 0;)
    {
        idx = index.top();
        index.pop();

        if (a[idx] > 0)
        { a[idx] += d; }
        else
        { a[idx] -= d; }
        c--;

        index.push(idx);
    }
    // Произведение минимизировано

    printAnswer(a);
    return EXIT_SUCCESS;
}
