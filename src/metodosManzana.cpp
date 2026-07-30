#include <SFML/Graphics.hpp>
#include <iostream>
#include "prototipos.hpp"

void Manzana::imprimir(sf::RenderWindow &window){
	sf::CircleShape apple (CELL_SIZE/2);
	apple.setFillColor(sf::Color::Red);
	apple.setPosition(
		coordX * CELL_SIZE, 
		coordY * CELL_SIZE
	);
	window.draw(apple);
}