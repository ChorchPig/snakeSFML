#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

#include <vector>

constexpr int ARRIBA    = 72;
constexpr int ABAJO     = 80;
constexpr int IZQUIERDA = 75;
constexpr int DERECHA   = 77;
constexpr int ESC       = 27;

constexpr int LIM_SUP = 4;
constexpr int LIM_INF = 20;
constexpr int LIM_IZQ = 4;
constexpr int LIM_DER = 20;

constexpr int CELL_SIZE = 32;

void goToXY(int x, int y);
void ocultarCursor();
void imprimirLimites(sf::RenderWindow &window);
void imprimirPuntaje(int puntos);
int leerMejorPuntaje();
void guardarMejorPuntaje(int nuevoPuntaje);
void imprimirMejorPuntaje(int mejor);

struct Segmento {
    int x, y;
    Segmento(int _x, int _y) : x(_x), y(_y) {}
    bool operator==(const Segmento& otro) const {
        return x == otro.x && y == otro.y;
    }
    bool operator!=(const Segmento& otro) const {
        return x != otro.x && y != otro.y;
    }
};

class Manzana {
    int coordX, coordY;
public:
    Manzana(int _xInicial, int _yInicial);
    int getCoordX() const;
    int getCoordY() const;
    void reubicar(const std::vector<Segmento>&snake);
    void imprimir();
};

class Serpiente {
    int directionX, directionY;
    std::vector<Segmento> cuerpo;
public:
    Serpiente();
    void imprimirCuerpo(sf::RenderWindow &window);
    void mover(bool crecer);
    void cambiarDireccion(char tecla);
    bool choque() const;
    bool vaAComer(const Manzana& manzana) const;
    const std::vector<Segmento>& getCuerpo() const;
};

#endif