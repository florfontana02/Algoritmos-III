#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    Graph(int vertices) {
        V = vertices;
        ady.resize(vertices);
    }

    void agregarArista(int v, int w, int peso) {
        ady[v].push_back(make_pair(w, peso));

    }



    vector<vector<pair<int, int>>>& getAdy() {
        return ady;
    }

private:
    int V; // cantidad de vertices
    vector<vector<pair<int, int>>> ady; // listas de adyacencia con pesos
};


const int INF = 1000000000;



void dijkstra(int s, vector<int> & d,  vector<vector<pair<int, int>>> & adj ) {
    int n = adj.size();
    d.assign(n, INF);

    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;

            }
        }

    }
}

int main() {
    int tests;
    cin >> tests;
    for(int i = 1; i <= tests; i++) {
        int N;
        int M;
        cin >> N;
        cin >> M;
        vector<pair<int,int>> pasadizos;

        for (int i = 0; i < M; i++){
            int v, w;
            cin >> v >> w;
            pasadizos.push_back(make_pair(v,w));
        }
        //modelo el problema con un grafo de 4(N+1) vértices, dividido en 3 "niveles"
        //cuando uso un pasadizo bajo un nivel, y no puedo volver a subir
        //creo el grafo con los 3 pisos y voy agregando las aristas de peso 1 entre los consecutivos


        Graph grafo(4*(N + 1));

        for (int i = 0; i < N; i++) {
            grafo.agregarArista(i, i + 1, 1);
        }
        for (int i = N+1; i < 2*(N + 1)-1; i++) {
            grafo.agregarArista(i, i + 1, 1);
        }
        for (int i = 2*N+2; i < 3*(N + 1)-1; i++) {
            grafo.agregarArista(i, i + 1, 1);
        }
        for (int i = 3*N+3; i < 4*(N + 1)-1; i++) {
            grafo.agregarArista(i, i + 1, 1);
        }

        //aristas con peso 0 de los bordes
        grafo.agregarArista(0,(N+1), 0);
        grafo.agregarArista((N+1),2*(N+1), 0);
        grafo.agregarArista(2*(N+1),3*(N+1), 0);

        grafo.agregarArista((N+1)-1,2*(N+1)-1, 0);
        grafo.agregarArista(2*(N+1)-1,3*(N+1)-1, 0);
        grafo.agregarArista(3*(N+1)-1,4*(N+1)-1, 0);

        //pasadizos
        for (int i = 0; i < M; i++){
            int v = pasadizos[i].first;
            int w = pasadizos[i].second;
            grafo.agregarArista(v,w+N+1,2);
            grafo.agregarArista(v+N+1,w+2*(N+1),2);
            grafo.agregarArista(v+2*(N+1),w+3*(N+1),2);
        }

        vector<vector<pair<int, int>>> adj = grafo.getAdy();
        vector<int> d;

        dijkstra(0, d, adj);

        int res =  d[4*(N+1)-1];

        cout << res << endl;

    }



    return 0;
}
