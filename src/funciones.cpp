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

int imprimirPuntaje(sf::RenderWindow &window, int puntos){ 
    sf::Font font;
	if (!font.loadFromFile("../resources/DejaVuSans.ttf")){
		std::cerr << "No se pudo cargar la fuente. (Puntaje)\n";
		return -1;
	}
	sf::Text texto;
	texto.setFont(font);
	texto.setString("Puntaje: "+std::to_string(puntos));
	texto.setCharacterSize(15);
	texto.setFillColor(sf::Color::White);
	texto.setPosition(LIM_IZQ*CELL_SIZE, (LIM_SUP-1)*CELL_SIZE);
    window.draw(texto);
    return 0;
}

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

int imprimirMejorPuntaje(sf::RenderWindow &window, int mejor){
    sf::Font font;
	if (!font.loadFromFile("../resources/DejaVuSans.ttf")){
		std::cerr << "No se pudo cargar la fuente. (High-score)\n";
		return -1;
	}
	sf::Text texto;
	texto.setFont(font);
	texto.setString("Mejor: "+std::to_string(mejor));
	texto.setCharacterSize(15);
	texto.setFillColor(sf::Color::White);
	texto.setPosition((LIM_DER-5)*CELL_SIZE, (LIM_SUP-1)*CELL_SIZE);
    window.draw(texto);
    return 0;
}