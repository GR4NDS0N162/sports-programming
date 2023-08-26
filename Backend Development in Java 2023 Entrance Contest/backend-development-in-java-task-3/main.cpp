#include <cstdlib>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Span {
    int start;
    int end;
};

bool doInclude(const Span& container, const Span& other) {
    return container.start < other.start && other.end < container.end;
}

bool isContained(const std::vector<Span>& spans, const Span& span) {
    int left, mid, right;

    left = 0;
    right = spans.size() - 1;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (doInclude(span, spans[mid]))
        { return true; }

        if (spans[mid].end <= span.start)
        { left = mid + 1; }
        else
        { right = mid - 1; }
    }

    return false;
}

vector<Span> findLowerExtremaSpans(const vector<int>& arr) {
    vector<Span> spans;

    bool isUsed = true;
    for (int start, i = 1; i < arr.size() - 1; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            start = i;
            isUsed = false;
        }
        if (!isUsed && arr[i] < arr[i + 1])
        {
            spans.push_back({start + 1, i + 1});
            isUsed = true;
        }
    }

    return spans;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    { cin >> a[i]; }

    auto lowerExtremaSpans = findLowerExtremaSpans(a);

    int m;
    cin >> m;

    vector<bool> ans(m);
    for (int start, end, i = 0; i < m; i++)
    {
        cin >> start >> end;
        ans[i] = isContained(lowerExtremaSpans, {start, end});
    }

    for (auto b : ans)
    { cout << (b ? "NO" : "YES") << endl; }

    return EXIT_SUCCESS;
}
