#include iostream
#include vector
#include algorithm
#include list
#include queue

using namespace std;

pairint, bool bfs(vectorlistint& ady, vectorint& tiempos, int t0, int desde, int hasta) {
    if(desde == hasta) return make_pair(0, true);
    vectorint visitado(ady.size(), 0);
    vectorint tiempo(ady.size(), -1);
    visitado[desde] = 1;
    tiempo[desde] = t0;
    queueint cola;
    cola.push(desde);
    bool camino = false;
    while(!cola.empty() && !camino) {
        int u = cola.front();
        for(int v  ady[u]) {
            if(visitado[v] == 0 && (tiempos[v] == 0  tiempos[v]  tiempo[u]+1)) {
                visitado[v] = 1;
                tiempo[v] = tiempo[u]+1;
                cola.push(v);
                if(v == hasta) {
                    camino = true;
                }
            }
        }
        cola.pop();
    }
    return make_pair(tiempo[hasta], camino);
}

int main() {
    int tests;
    cin  tests;

    for(int t = 1; t = tests; t++) {
        int n, m;

        cin  n;
        cin  m;

        vectorlistint ady(nm, listint());
        vectorint tiempos(nm, 0);

        for(int i = 0; i  n; i++) {
            for(int j = 0; j  m; j++) {
                int tij;
                cin  tij;
                tiempos[mi+j] = tij;

                if(0 = mi+j-m && mi+j-m  nm) {
                    ady[mi+j].push_back(mi+j-m);
                }

                if(0 = mi+j+m && mi+j+m  nm) {
                    ady[mi+j].push_back(mi+j+m);
                }

                if(0 = mi+j-1 && mi+j-1  nm && j  0) {
                    ady[mi+j].push_back(mi+j-1);
                }

                if(0 = mi+j+1 && mi+j+1  nm && j  m-1) {
                    ady[mi+j].push_back(mi+j+1);
                }

            }
        }

        int x1, y1, x2, y2;

        cin  x1;
        cin  y1;
        cin  x2;
        cin  y2;

        pairint, bool ida = bfs(ady, tiempos, 0, x1m+y1, x2m+y2);
        pairint, bool vuelta = bfs(ady, tiempos, ida.first, x2m+y2, x1m+y1);

        if(ida.second && vuelta.second) {
            cout  ida.first     vuelta.first  endl;
        } else {
            cout  IMPOSIBLE  endl;
        }

    }

    return 0;
}
