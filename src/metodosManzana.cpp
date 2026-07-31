#include <SFML/Graphics.hpp>
#include <iostream>
#include "prototipos.hpp"

using namespace std;

void Manzana::imprimir(sf::RenderWindow &window){
	sf::CircleShape apple (CELL_SIZE/2);
	apple.setFillColor(sf::Color::Red);
	apple.setPosition(
		coordX * CELL_SIZE, 
		coordY * CELL_SIZE
	);
	window.draw(apple);
}

void Manzana::reubicar(const vector<Segmento>& cuerpo) {
    do {
        coordX = rand() % (LIM_DER - LIM_IZQ - 1) + LIM_IZQ + 1;
        coordY = rand() % (LIM_INF - LIM_SUP - 1) + LIM_SUP + 1;
    } 
	while (find(cuerpo.begin(), cuerpo.end(), Segmento{coordX, coordY}) != cuerpo.end());
}

int Manzana::getCoordX() const{ return coordX; }
int Manzana::getCoordY() const{ return coordY; }