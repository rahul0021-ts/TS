#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a Job structure
struct Job {
    string id;
    int profit;
    int deadline;
};

// Comparison function to sort jobs by profit in descending order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    // Sample input
    vector<Job> jobs = {
        {"j1", 15, 2},
        {"j2", 27, 3},
        {"j3", 10, 3},
        {"j4", 100, 3},
        {"j5", 150, 4}
    };

    // Sort jobs by profit
    sort(jobs.begin(), jobs.end(), compare);

    int n = jobs.size();
    vector<int> slot(n + 1, 0);          // Slots to mark filled time slots (1-based index)
    vector<string> ans(n + 1, "null");   // Job assignment to slots
    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        // Try to fit job in latest available slot before deadline
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                ans[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Output
    cout << "Jobs scheduled: ";
    for (int i = 1; i <= n; i++) {
        if (ans[i] != "null")
            cout << ans[i] << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;

    return 0;
}
/*
📦 Job Sequencing with Deadlines (Greedy Approach)
🎯 Objective:
Schedule jobs to maximize total profit while meeting deadlines.
Each job takes 1 unit time, and only one job can be scheduled at a time.

🧾 Given Jobs
cpp
Copy
Edit
vector<Job> jobs = {
    {"j1", 15, 2},
    {"j2", 27, 3},
    {"j3", 10, 3},
    {"j4", 100, 3},
    {"j5", 150, 4}
};
Job ID	Profit	Deadline
j1	15	2
j2	27	3
j3	10	3
j4	100	3
j5	150	4

🧠 Greedy Logic
Sort jobs by profit in descending order.

Try placing each job in the latest available slot before or on its deadline.

Use arrays:

slot[] to track filled time slots

ans[] to store job scheduled at each time

🔢 Sorted Jobs by Profit
Job ID	Profit	Deadline
j5	150	4
j4	100	3
j2	27	3
j1	15	2
j3	10	3

📌 Slot Assignment (1-based index)
Step 1: Try to schedule j5 (deadline 4)
Slot 4 is free → assign j5 → ✅

Step 2: Try to schedule j4 (deadline 3)
Slot 3 is free → assign j4 → ✅

Step 3: Try to schedule j2 (deadline 3)
Slot 3 is full → check slot 2 → free → assign j2 → ✅

Step 4: Try to schedule j1 (deadline 2)
Slot 2 is full → check slot 1 → free → assign j1 → ✅

Step 5: Try to schedule j3 (deadline 3)
Slot 3, 2, 1 all full → ❌ cannot assign

📊 Final Job Assignments
Slot	Job
1	j1
2	j2
3	j4
4	j5

📈 Total Profit = 15 (j1) + 27 (j2) + 100 (j4) + 150 (j5) = 292

✅ Output
yaml
Copy
Edit
Jobs scheduled: j1 j2 j4 j5 
Total Profit: 292

*/