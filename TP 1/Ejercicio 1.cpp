#include <iostream>
#include <vector>

using namespace std;

class Pieza {
public:
    enum TIPO {
        I='I', L='L', CRUZ='+', VACIO='#'
    };

    enum POS {
        NINGUNA=-10,
        ABAJO=0,
        ARRIBA=1,
        DERECHA=2,
        IZQUIERDA=3,
    };

    Pieza(TIPO tipo, int giro) {
        _tipo = tipo;
        _giro = giro;
    }

    TIPO tipo();
    bool conecta(Pieza p, POS pos);
    void rotar90();
    vector<int> rotaciones();

private:
    TIPO _tipo;
    int _giro;
};

Pieza::POS opuesto(Pieza::POS p) {
    switch (p) {
        case Pieza::ARRIBA:
            return Pieza::ABAJO;
        case Pieza::ABAJO:
            return Pieza::ARRIBA;
        case Pieza::DERECHA:
            return Pieza::IZQUIERDA;
        case Pieza::IZQUIERDA:
            return Pieza::DERECHA;
        default:
            return Pieza::NINGUNA;
    }
}

Pieza::TIPO Pieza::tipo() {
    return _tipo;
}

void Pieza::rotar90() {
    _giro = (_giro + 1) % 4;
}

vector<int> Pieza::rotaciones() {
    switch (tipo()) {
        case I:
            return {0,1};
        case L:
            return {0,1,2,3};
        case CRUZ:
            return {0};
        case VACIO:
            return {0};
    }
    return {};
}

class Test {
public:
    Test(vector<vector<Pieza>>& tablero) {
        _tablero = tablero;
        _recorrido = vector<vector<int>>();

        for(int i = 0; i < _tablero.size(); i++) {
            vector<int> row;
            for(int j = 0; j < tablero[i].size(); j++) {
                row.push_back(0);
            }
            _recorrido.push_back(row);
        }
    }

    vector<vector<Pieza>>& tablero();
    vector<vector<int>>& recorrido();

private:
    vector<vector<Pieza>> _tablero;
    vector<vector<int>> _recorrido;
};

vector<vector<Pieza>> &Test::tablero() {
    return _tablero;
}

vector<vector<int>> &Test::recorrido() {
    return _recorrido;
}

//Devuelve true si la instancia conecta con la pieza p ubicada según pos respecto de la instancia.
bool Pieza::conecta(Pieza p, POS pos) {
    if(tipo() == p.tipo()) {
        if(tipo() == I) {
            switch (pos) {
                case ARRIBA:
                    return (_giro == 0 || _giro == 2) && (p._giro == 0 || p._giro == 2);
                case ABAJO:
                    return (_giro == 0 || _giro == 2) && (p._giro == 0 || p._giro == 2);
                case DERECHA:
                    return (_giro == 1 || _giro == 3) && (p._giro == 1 || p._giro == 3);
                case IZQUIERDA:
                    return (_giro == 1 || _giro == 3) && (p._giro == 1 || p._giro == 3);
            }
        } else if(tipo() == L) {
            switch(pos) {
                case ARRIBA:
                    return (_giro == 0 || _giro == 3) && (p._giro == 1 || p._giro == 2);
                case ABAJO:
                    return (p._giro == 0 || p._giro == 3) && (_giro == 1 || _giro == 2);
                case DERECHA:
                    return (_giro == 0 || _giro == 1) && (p._giro == 2 || p._giro == 3);
                case IZQUIERDA:
                    return (p._giro == 0 || p._giro == 1) && (_giro == 2 || _giro == 3);
            }
        } else if(tipo() == CRUZ) {
            return true;
        } else return false;
    } else if(tipo() == I && p.tipo() == L) {
        switch (pos) {
            case ARRIBA:
                return (_giro == 0 || _giro == 2) && (p._giro ==  1 || p._giro == 2);
            case ABAJO:
                return (_giro == 0 || _giro == 2) && (p._giro ==  0 || p._giro == 3);
            case DERECHA:
                return (_giro == 1 || _giro == 3) && (p._giro == 2 || p._giro == 3);
            case IZQUIERDA:
                return (_giro == 1 || _giro == 3) && (p._giro == 0 || p._giro == 1);
        }
    } else if(tipo() == L && p.tipo() == I) {
        switch (pos) {
            case ARRIBA:
                return (_giro == 0 || _giro == 3) && (p._giro ==  0 || p._giro == 2);
            case ABAJO:
                return (_giro == 1 || _giro == 2) && (p._giro ==  0 || p._giro == 2);
            case DERECHA:
                return (_giro == 0 || _giro == 1) && (p._giro == 1 || p._giro == 3);
            case IZQUIERDA:
                return (_giro == 2 || _giro == 3) && (p._giro == 1 || p._giro == 3);
        }
    } else if(tipo() == I && p.tipo() == CRUZ) {
        return ((_giro == 0 || _giro == 2) ? (pos == ABAJO || pos == ARRIBA) : (pos == IZQUIERDA || pos == DERECHA));
    } else if(tipo() == CRUZ && p.tipo() == I) {
        return ((p._giro == 0 || p._giro == 2) ? (pos == ARRIBA || pos == ABAJO) : (pos == DERECHA || pos == IZQUIERDA));
    } else if(tipo() == L && p.tipo() == CRUZ) {
        switch(pos) {
            case ARRIBA:
                return (_giro == 0 || _giro == 3);
            case ABAJO:
                return (_giro == 1 || _giro == 2);
            case DERECHA:
                return (_giro == 0 || _giro == 1);
            case IZQUIERDA:
                return (_giro == 2 || _giro == 3);
        }
    } else if(tipo() == CRUZ && p.tipo() == L) {
        switch(pos) {
            case ARRIBA:
                return (p._giro == 1 || p._giro == 2);
            case ABAJO:
                return (p._giro == 0 || p._giro == 3);
            case DERECHA:
                return (p._giro == 2 || p._giro == 3);
            case IZQUIERDA:
                return (p._giro == 0 || p._giro == 1);
        }
    }
    return false;
}

pair<int, int> mover(int x, int y, Pieza::POS mov, int ancho, int alto) {
    switch (mov) {
        case Pieza::ARRIBA:
            if(0 < x) {
                return make_pair(x - 1, y);
            } else return make_pair(-1,-1);
        case Pieza::ABAJO:
            if(x < alto - 1) {
                return make_pair(x + 1, y);
            } else return make_pair(-1,-1);
        case Pieza::DERECHA:
            if(y < ancho-1) {
                return make_pair(x, y+1);
            } else return make_pair(-1,-1);
        case Pieza::IZQUIERDA:
            if(y > 0) {
                return make_pair(x, y - 1);
            } else return make_pair(-1,-1);
    }
    return make_pair(-1,-1);
}

int minLong = 1e9;
int maxLong = -1;

void sendero(vector<vector<Pieza>>& tablero, vector<vector<int>>& recorrido, int x, int y, Pieza::POS mov, int lon) {
    int alto = tablero.size();
    int ancho = tablero[0].size();
    pair<int,int> sig = mover(x, y, mov, ancho, alto);
    int sig_x = sig.first;
    int sig_y = sig.second;
    if(x == alto - 1 && y == ancho  - 1) {
        minLong = min(minLong, lon);
        maxLong = max(maxLong, lon);
    } else if(!(x==0 && y==0 && mov == Pieza::NINGUNA)) {
        if(minLong < lon && maxLong == alto * ancho - 1) return;
        if(0 <= sig_x && sig_x < alto && 0 <= sig_y && sig_y < ancho) {
            if(recorrido[sig_x][sig_y] == 1) return;

            for(int i : tablero[sig_x][sig_y].rotaciones()) {
                tablero[sig_x][sig_y].rotar90();

                if(tablero[x][y].conecta(tablero[sig_x][sig_y], mov)) {
                    if((sig_x != alto - 1 || sig_y != ancho - 1)) {
                        if(((sig_x != 0) || sig_y >= y)
                              && ((sig_x != alto-1) || sig_y >= y)
                              && ((sig_y != 0) || sig_x >= x)
                              && ((sig_y != ancho-1) || sig_x >= x)) {
                            recorrido[sig_x][sig_y] = 1;
                            for(int j = 0; j < 4; j++) {
                                if(Pieza::POS(j) != opuesto(mov)) {
                                    sendero(tablero, recorrido, sig_x, sig_y, Pieza::POS(j), lon + 1);
                                }
                            }
                        }
                    } else {
                        recorrido[sig_x][sig_y] = 1;
                        sendero(tablero, recorrido, sig_x, sig_y, Pieza::NINGUNA, lon + 1);
                    }
                    recorrido[sig_x][sig_y] = 0;
                }
            }
        }
    } else {
        for(int i : tablero[0][0].rotaciones()) {
            tablero[0][0].rotar90();

            recorrido[0][0] = 1;
            sendero(tablero, recorrido, 0, 0, Pieza::ABAJO, lon);
            sendero(tablero, recorrido, 0, 0, Pieza::DERECHA, lon);
            recorrido[0][0] = 0;
        }
    }
}

int main() {
    vector<Test> tests;

    int cantTests;
    cin >> cantTests;

    for(int t = 0; t < cantTests; t++) {
        int rows;
        int cols;

        cin >> rows;
        cin >> cols;

        vector<vector<Pieza>> tablero = vector<vector<Pieza>>();
        while(tablero.size() < rows) {
            string row;
            cin >> row;
            vector<Pieza> r;
            for(char c : row) {
                r.push_back(Pieza(Pieza::TIPO(c), 0));
            }
            tablero.push_back(r);
        }

        tests.push_back(Test(tablero));
    }

    for(int t = 0 ; t < tests.size(); t++) {
        Test actual = tests[t];

        sendero(actual.tablero(), actual.recorrido(), 0, 0, Pieza::NINGUNA, 0 );

        if(minLong != 1e9 && maxLong != -1) {
            cout << "POSIBLE " << minLong << " " << maxLong << endl;
        } else cout << "IMPOSIBLE" << endl;

        minLong = 1e9;
        maxLong = -1;
    }

    return 0;
}
