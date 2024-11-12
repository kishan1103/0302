#include <iostream>
#include <vector>

using namespace std;

void nextFit(vector<int>& blockSize, int m, vector<int>& processSize, int n) {
    vector<int> allocation(n, -1);

    int j = 0; // Start index for the next fit

    for (int i = 0; i < n; i++) {
        int count = 0; // To prevent infinite loop
        while (count < m) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    cout << "Process no\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i];
        if (allocation[i] != -1) {
            cout << "\t\t" << allocation[i] + 1;
        } else {
            cout << "\tNot Allocated";
        }
        cout << endl;
    }
}

int main() {
    int m, n;
    cout << "Enter the size of blockSize array and processSize array respectively: ";
    cin >> m >> n;

    vector<int> processSize(n);
    vector<int> blockSize(m);

    cout << "Enter the values in Process size array:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    cout << "Enter the values in Block size array:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    nextFit(blockSize, m, processSize, n);

    return 0;
}
