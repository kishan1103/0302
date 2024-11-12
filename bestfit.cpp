#include <iostream>
using namespace std;

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];
    for (int i = 0; i < 10; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "Process No\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main() {
    int m, n;

    cout << "Enter the number of blocks and processes respectively: ";
    cin >> m >> n;

    int processSize[n];
    int blockSize[m];

    cout << "Enter the values in the Process Size array:\n";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    cout << "Enter the values in the Block Size array:\n";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}
