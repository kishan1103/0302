#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

class RW {
private:
    mutex readlock, writelock;
    int readcount = 0;

public:
    void read(int thread_num) {
        try {
            unique_lock<mutex> rl(readlock);
            readcount++;
            if (readcount == 1) {
                writelock.lock();
            }
            rl.unlock();

            cout << "Thread " << thread_num << " is reading." << endl;
            this_thread::sleep_for(chrono::milliseconds(2500));
            cout << "Thread " << thread_num << " has finished reading." << endl;

            rl.lock();
            readcount--;
            if (readcount == 0) {
                writelock.unlock();
            }
            rl.unlock();
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

    void write(int thread_num) {
        try {
            unique_lock<mutex> wl(writelock);
            cout << "Thread " << thread_num << " is writing." << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout << "Thread " << thread_num << " has finished writing." << endl;
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

    void fun() {
        int n;
        cout << "Enter the number of read & write processes: ";
        cin >> n;
        
        vector<int> seq(n);
        cout << "Enter the sequence: 1 for reading & 0 for writing." << endl;
        for (int i = 0; i < n; i++) {
            cin >> seq[i];
        }

        vector<thread> processes;
        for (int i = 0; i < n; i++) {
            if (seq[i] == 1) {
                processes.emplace_back(&RW::read, this, i + 1);
            } else if (seq[i] == 0) {
                processes.emplace_back(&RW::write, this, i + 1);
            }
        }

        for (auto& process : processes) {
            process.join();
        }
    }
};

int main() {
    RW rw;
    rw.fun();
    return 0;
}
