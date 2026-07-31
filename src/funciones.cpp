#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "prototipos.hpp"

using namespace std;

void imprimirLimites(sf::RenderWindow &window){
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

	for(int i=LIM_SUP; i<LIM_INF; i++){
		for(int j=LIM_IZQ; j<LIM_DER; j++){
		cell.setPosition(
			j * CELL_SIZE,
			i * CELL_SIZE
		);
		if( (i%2!=0&&j%2!=0) || (i%2==0&&j%2==0) )
			cell.setFillColor(sf::Color::Green);
		else 
			cell.setFillColor(sf::Color(35, 109, 42));
		window.draw(cell);
		}
	}
}

void imprimirPuntaje(int puntos){ cout<<"Puntaje: "<< puntos << endl; }

int leerMejorPuntaje() {
    ifstream file("highscore.bin", ios::binary);
    int mejorPuntaje = 0;
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&mejorPuntaje), sizeof(mejorPuntaje));
        file.close();
    }
    return mejorPuntaje;
}

void guardarMejorPuntaje(int nuevoPuntaje) {
    int mejorActual = leerMejorPuntaje();
    if (nuevoPuntaje > mejorActual) {
        ofstream file("highscore.bin", ios::binary | ios::trunc);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(&nuevoPuntaje),sizeof(nuevoPuntaje));
            file.close();
        }
    }
}

void imprimirMejorPuntaje(int mejor){ cout<<"Mejor: "<<mejor<<endl; }