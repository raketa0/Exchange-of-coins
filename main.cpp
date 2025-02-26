/*4.6. ������ ����� (6)
��������� ��������� �������� ����� ����� ����������� ����������� �����.
����. ������ ������ ����� INPUT.TXT �������� ����� ����� L (1 ? L ? 20000) � ���������� ����� ����� N (1 ? N ? 30). ������ ������ �������� N �������� Ci ����� ������: ��������� ����� ����� (1 ? Ci ? L).
�����. � ������ ������ ��������� ���������� ����� ����� K, ����������� ��� �������, � ����� ����������� ���������� ����� M. � ��������� K ������� ��������� ����� ������ �� 2 �����: ��������� ������ � ���������� ����������� ������ ������. ��� K ����� ������ ��������� � ������� �������� ��������� �����. ���� ������� ��������� ��������� �������, ���������� ������� ����� �� ���. ���� ��������� ����� ��������� ����������, �� �������� ���� ������ ��������� No.
�������
���� 1      ���� 2
15 3        12 3
5 11 1      1 10 3
����� 1     ����� 2
1 3         2 3
5 3         10 1
            1 2

 ������ ��������� �������������     
 https://education.yandex.ru/handbook/algorithms/article/zadacha-razmen
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void readInput(int& L, int& N, vector<int>& coins, const string& inputFile) {
    ifstream inFile(inputFile);
    inFile >> L >> N;
    coins.resize(N);
    for (int i = 0; i < N; ++i) {
        inFile >> coins[i];
    }
    inFile.close();
}

void sortCoins(vector<int>& coins) {
    sort(coins.rbegin(), coins.rend());
}

void fillDP(vector<int>& dp, vector<int>& prev, const vector<int>& coins, int L) {
    dp[0] = 0;
    for (int i = 1; i <= L; ++i) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                prev[i] = coin;
            }
        }
    }
}

bool isChangePossible(const vector<int>& dp, int L) {
    return dp[L] != INT_MAX;
}

vector<pair<int, int>> restoreSolution(const vector<int>& prev, int L) {
    vector<pair<int, int>> result;
    int remaining = L;
    while (remaining > 0) {
        int coin = prev[remaining];
        int count = 0;
        while (remaining >= coin && prev[remaining] == coin) {
            remaining -= coin;
            count++;
        }
        result.push_back({ coin, count });
    }
    return result;
}

void printOutput(const vector<pair<int, int>>& result, int totalCoins, const string& outputFile) {
    ofstream outFile(outputFile);
    if (result.empty()) {
        outFile << "No" << endl;
    }
    else {
        outFile << result.size() << " " << totalCoins << endl;
        for (const auto& p : result) {
            outFile << p.first << " " << p.second << endl;
        }
    }
    outFile.close();
}

int main() {
    int L, N;
    vector<int> coins;
    readInput(L, N, coins, "INPUT.TXT");
    sortCoins(coins);

    vector<int> dp(L + 1, INT_MAX);
    vector<int> prev(L + 1, -1);
    fillDP(dp, prev, coins, L);

    if (!isChangePossible(dp, L)) {
        printOutput({}, 0, "OUTPUT.TXT");
        return 0;
    }

    vector<pair<int, int>> result = restoreSolution(prev, L);
    printOutput(result, dp[L], "OUTPUT.TXT");

    return 0;
}