#include <iostream>
#include <list>
#include <unordered_map>
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

    unordered_map<int, list<int>::iterator> pageTable;
    list<int> lruList;

    for (int i = 0; i < n; i++) {
        if (pageTable.find(pages[i]) != pageTable.end()) {
            pageHits++;
            lruList.erase(pageTable[pages[i]]);
        } else {
            pageFaults++;
            if (lruList.size() == frames) {
                int leastUsed = lruList.back();
                lruList.pop_back();
                pageTable.erase(leastUsed);
            }
        }
        lruList.push_front(pages[i]);
        pageTable[pages[i]] = lruList.begin();
    }

    double hitRatio = (double)pageHits / n * 100;

    cout << "Total page faults: " << pageFaults << endl;
    cout << "Total page hits: " << pageHits << endl;
    cout << "Hit ratio: " << hitRatio << "%" << endl;

    return 0;
}
