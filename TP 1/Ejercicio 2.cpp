#include <iostream>
#include <algorithm>
#include <vector>
#include<cmath>
using namespace std;

typedef pair<long long, long long> parcial;

bool comparar_indices(parcial a, parcial b){
    //return (a.first/a.second) > (b.first/b.second);
    return (a.first*b.second) > (b.first*a.second);
}

int restoModm(long long n, long long div){
    if(n>= 0){
        return n%div;
    }else{
        return n%div + div;
    }
}

long long minimizarDescontento(long long C[], long long M[], long long N){
    vector<parcial> lista;

    for (long long i = 0; i < N; i++) {
        long long m = M[i];
        long long c = C[i];
        lista.push_back(make_pair(c, m));
    }

    sort(lista.begin(), lista.end(), comparar_indices);

    long long descontentoTotal = 0;
    long long t = 0;

    for (long long i = 0; i < N; i++) {
        long long descontento_i = lista[i].first % 1000000007;
        long long tiempoCorreccion_i = lista[i].second % 1000000007;

        t += tiempoCorreccion_i;
        descontentoTotal += descontento_i * t % 1000000007;
    }

    return descontentoTotal % 1000000007;
}

int main(){
    long long cantTests;
    cin >> cantTests;

    vector<long long> res;
    for(long long t = 0; t < cantTests; t++) {
        long long N;
        cin >> N;
        long long C[N], M[N];
        for (long long i = 0; i < N; i++) {
            cin >> M[i];
        }
        for (long long i = 0; i < N; i++) {
            cin >> C[i];
        }
        long long minDescontento = minimizarDescontento(C, M, N);
        res.push_back(minDescontento);
    }
    for(long long i = 0; i< res.size(); i++){
        cout << res[i] << endl;
    }
}

    

