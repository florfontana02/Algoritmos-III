#include <iostream>
#include <vector>
using namespace std;

class Test {

public:
    Test(int K, vector<int> puestos) {
        _K = K;
        _puestos = puestos;
    }
    int K();
    vector<int>& puestos();

private:
    int _K;
    vector<int> _puestos;
};

int Test::K() {
    return _K;
}

vector<int> &Test::puestos() {
    return _puestos;
}

int maxPos;
long INF = 1e9;
vector<int> puestos;
vector<vector<vector<pair<int, vector<int>>>>> memo;
pair<int, vector<int>> UNDEFINED;

pair<int, vector<int>> minC(int actual, int k, int ultProv) {
    if(actual > maxPos && k == 0) {
        return make_pair(0, (vector<int>){});
    } else if(actual <= maxPos && k > 0) {
        if(memo[actual][k][ultProv + 1] != UNDEFINED) {
            return memo[actual][k][ultProv + 1];
        }
        pair<int, vector<int>> poniendo = minC(actual + 1, k - 1, actual);
        pair<int, vector<int>> siguiendo = minC(actual + 1, k, ultProv);

        int suma = 0;
        for(int puestoId = ultProv; puestoId < actual; puestoId++) {
            if(ultProv >= 0 && puestoId >= 0) {
                suma+=min(abs(puestos[puestoId] - puestos[ultProv]), abs(puestos[puestoId] - puestos[actual]));
            } else if(ultProv < 0 && puestoId >= 0) {
                suma+=abs(puestos[puestoId] - puestos[actual]);
            }
        }

        if(poniendo.first + suma <= siguiendo.first) {
            vector<int> res = poniendo.second;
            res.push_back(puestos[actual]);
            memo[actual][k][ultProv + 1] = make_pair(poniendo.first + suma, res);
        } else {
            memo[actual][k][ultProv + 1] = siguiendo;
        }
    } else if(actual <= maxPos && k == 0) {
        if(memo[actual][k][ultProv + 1] != UNDEFINED) {
            return memo[actual][k][ultProv + 1];
        }
        pair<int, vector<int>> siguiendo = minC(actual + 1, k, ultProv);
        memo[actual][k][ultProv + 1] = make_pair(siguiendo.first + abs(puestos[ultProv] - puestos[actual]), siguiendo.second);
    } else return make_pair(INF, (vector<int>){});

    return memo[actual][k][ultProv + 1];
}

int main() {
    UNDEFINED = make_pair(-1, (vector<int>){});

    vector<Test> tests;

    int cantTests;
    cin >> cantTests;

    for(int t = 0; t < cantTests; t++) {
        vector<int> puestos = {};
        int N;
        int K;
        cin >> N;
        cin >> K;
        for (int i = 0; i < N; i++){
            int puesto;
            cin >> puesto;
            puestos.push_back(puesto);
        }
        tests.push_back(Test(K, puestos));
    }

    for(int t = 0; t < cantTests; t++) {
        Test test = tests[t];

        if(!memo.empty()) memo.clear();

        maxPos = test.puestos().size()-1;
        puestos = test.puestos();

        for(int i = 0; i < test.puestos().size(); i++) {
            vector<vector<pair<int, vector<int>>>> v;
            for(int k = 0; k <= test.K(); k++) {
                vector<pair<int, vector<int>>> m;
                for(int j = 0; j <= test.puestos().size(); j++) {
                    m.push_back(UNDEFINED);
                }
                v.push_back(m);
            }
            memo.push_back(v);
        }

        auto res = minC(0, test.K(), -1);

        cout << res.first << endl;
        for(int i = res.second.size()-1; i >= 0; i--) {
            cout << res.second[i] << " ";
        }

        cout << endl;
    }

    return 0;
}

