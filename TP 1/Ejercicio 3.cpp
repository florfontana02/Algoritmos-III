#include <iostream>
#include <vector>
using namespace std;

class Test {

public:
    Test(int saldoTotal, vector<int> vals) {
        _saldoTotal = saldoTotal;
        _vals = vals;
    }
    int saldoTotal();
    vector<int>& vals();
private:
    int _saldoTotal;
    vector<int> _vals;
};

int Test::saldoTotal() {
    return _saldoTotal;
}
vector<int>& Test::vals() {
    return _vals;
}

int maxSum;
vector<vector<int>> memo;
int UNDEFINED = 1e9;

bool sumanT(vector<int>& vals, int i, int T) {
    if(i == 0) {
        if(T == 0) {
            return true;
        } else return false;
    } else {
        int tPos = (T/100 < 0) ? (maxSum/100 + abs(T)/100) : (T/100);

        if(memo[i-1][tPos] != UNDEFINED) {
            return memo[i-1][tPos] == 1;
        }

        memo[i-1][tPos] = (sumanT(vals, i - 1, T - vals[i - 1]) || sumanT(vals, i - 1, T + vals[i - 1])) ? 1 : 0;
        return memo[i-1][tPos] == 1;
    }
}

void verSignos(vector<int>& vals, int T) {
    vector<char> res(vals.size(), '*');

    maxSum = 0;
    for(int i = 0; i < vals.size(); i++) {
        maxSum+=vals[i];
    }

    vector<int> fila;
    for(int t = 0; t < (((2*maxSum)/100)+1); t++) {
        fila.push_back(UNDEFINED);
    }

    for(int i = 0; i < vals.size(); i++) {
        vector<int> resto;

        for(int j = 0; j < vals.size(); j++) {
            if(j != i) resto.push_back(vals[j]);
        }

        for(int n = 0; n < resto.size(); n++) {
            memo.push_back(fila);
        }

        bool sumando = sumanT(resto, resto.size(), T - vals[i]);
        bool restando = sumanT(resto, resto.size(), T + vals[i]);

        if(sumando && restando) {
            res[i] = '?';
        } else if(sumando && !restando) {
            res[i] = '+';
        } else if(restando) {
            res[i] = '-';
        } else res[i] = '*';

        resto.clear();
        memo.clear();
    }

    for(int i = 0; i < res.size(); i++) {
        cout << res[i];
    }
    cout << endl;
}

int main() {
    vector<Test> tests;

    int cantTests;
    cin >> cantTests;

    for(int t = 0; t < cantTests; t++) {
        int cantVal;
        int saldoTotal;
        cin >> cantVal;
        cin >> saldoTotal;
        vector<int> vals;
        for (int i = 0; i < cantVal; i++){
            int val;
            cin >> val;
            vals.push_back(val);
        }
        tests.push_back(Test(saldoTotal, vals));
    }

    for(int t = 0; t < cantTests; t++) {
        Test test = tests[t];

        verSignos(test.vals(), test.saldoTotal());
    }
}
