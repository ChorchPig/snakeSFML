#include <iostream>
#include <SFML/Graphics.hpp>
#include "prototipos.hpp"

using namespace std;

Serpiente::Serpiente(){
    for(int i=0; i<3; i++){
        cuerpo.emplace_back((LIM_IZQ+LIM_DER)/2 - i, (LIM_SUP+LIM_INF)/2);
    }
    directionX=1;
    directionY=0;
}

void Serpiente::imprimirCuerpo(sf::RenderWindow &window){
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cell.setFillColor(sf::Color::Blue);
	for(int i=0; i<cuerpo.size(); i++){
		cell.setPosition(
			cuerpo[i].x * CELL_SIZE, 
			cuerpo[i].y * CELL_SIZE
		);
		window.draw(cell);
	}
}

void Serpiente::mover(bool crecer){
    Segmento nuevaCabeza = {
        cuerpo[0].x + directionX,
        cuerpo[0].y + directionY
    };
    cuerpo.insert(cuerpo.begin(), nuevaCabeza);
    if (!crecer)
        cuerpo.pop_back();
}

void Serpiente::cambiarDireccion(int nuevoX, int nuevoY){
    directionX=nuevoX; 
    directionY=nuevoY;
}

bool Serpiente::choque() const{
    bool choque=false;
    Segmento sigFrame = {
        cuerpo[0].x + directionX,
        cuerpo[0].y + directionY
    };

    if (sigFrame.x > LIM_DER - 1 || sigFrame.x < LIM_IZQ || sigFrame.y > LIM_INF - 1 || sigFrame.y < LIM_SUP) //colisión contra los bordes
        choque=true;
    else{ //colisión contra el cuerpo
        for (int i=0; i<cuerpo.size(); i++) {
            choque=(sigFrame==cuerpo[i]);
        }
    }
    return choque;
}

const vector<Segmento> & Serpiente::getCuerpo() const{ return cuerpo; }
