#include <bits/stdc++.h>
using namespace std;

// Global variable to store initial power of Abhimanyu
int initialPower;



// Memorization Function to check if Abhimanyu can cross the Chakravyuha
bool canCrossChakravyuha(int index, int &totalCircles, vector<int> enemies, int currentPower,
            int skipsLeft,int rechargesLeft, vector<vector<vector<vector<int>>>> &dp) {
    
    // If Abhimanyu has crossed all circles
    if (index == totalCircles) {
        return (currentPower >= 0);
    }

    // If the state is already computed, return the stored result
    if (dp[index][currentPower][skipsLeft][rechargesLeft] != -1)
        return dp[index][currentPower][skipsLeft][rechargesLeft];

    bool canReach = false;

    // If Abhimanyu has enough power to defeat the enemy in the current circle
    if (currentPower >= enemies[index]) {
        canReach |= canCrossChakravyuha(index + 1, totalCircles, enemies, currentPower - enemies[index], skipsLeft, rechargesLeft, dp);
    }

    // Special case for enemies with regeneration power
    if (index == 2 || index == 6) {
        enemies[index + 1] += enemies[index] / 2;
    }

    // If Abhimanyu can skip this enemy
    if (skipsLeft > 0) {
        canReach |= canCrossChakravyuha(index + 1, totalCircles, enemies, currentPower, skipsLeft - 1, rechargesLeft, dp);
    }

    // If Abhimanyu can recharge his power
    if (rechargesLeft > 0) {
        currentPower = initialPower;
        canReach |= canCrossChakravyuha(index + 1, totalCircles, enemies, currentPower, skipsLeft, rechargesLeft - 1, dp);
    }

    // Store and return the result for the current state
    return dp[index][currentPower][skipsLeft][rechargesLeft] = canReach;
}



// Function to solve each test case
void solve() {
    int totalCircles = 11, power, skips, recharges;
    
    // Read input values : power , skip , reacharge
    cin >> power >> skips >> recharges;
    initialPower = power;
    
    vector<int> enemies(totalCircles,0);
    // Read input values for each enemies power in 11 circles
    for (int i = 0; i < totalCircles; i++) {
        cin >> enemies[i];
    }

    // DP table to store results of subproblems
    vector<vector<vector<vector<int>>>> dp(12, vector<vector<vector<int>>>(205, vector<vector<int>>(20, vector<int>(20, -1))));

    // Check if Abhimanyu can cross the Chakravyuha
    bool canAbhimanyuCross = canCrossChakravyuha(0, totalCircles, enemies, power, skips, recharges, dp);
    
    if (canAbhimanyuCross) {
        cout << "Abhimanyu can cross the Chakravyuh : WIN" << endl;
    } else {
        cout << "Abhimanyu can not cross the Chakravyuh : LOST" << endl;
    }
}


// Main function
int main() {
    int testCases ;
    // Read number of test cases
    cin >> testCases;
    while (testCases--) {
        solve();
    }
    return 0;
}
