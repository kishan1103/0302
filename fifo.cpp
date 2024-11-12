#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    int frames, n, pageFaults = 0, pageHits = 0;
    cout << "Enter number of frames: ";
    cin >> frames;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference sequence:\n";
    for (int i = 0; i < n; i++) cin >> pages[i];

    unordered_set<int> s;
    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (s.find(pages[i]) != s.end()) {
            pageHits++;
        } else {
            if (s.size() < frames) {
                s.insert(pages[i]);
                q.push(pages[i]);
            } else {
                int val = q.front();
                q.pop();
                s.erase(val);
                s.insert(pages[i]);
                q.push(pages[i]);
            }
            pageFaults++;
        }
    }

    double hitRatio = (double)pageHits / n * 100;

    cout << "Total page faults: " << pageFaults << endl;
    cout << "Total page hits: " << pageHits << endl;
    cout << "Hit ratio: " << hitRatio << "%" << endl;

    return 0;
}
