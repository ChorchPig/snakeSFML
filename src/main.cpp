#include <SFML/Graphics.hpp>
#include <iostream>

#pragma region imgui
	#include "imgui.h"
	#include "imgui-SFML.h"
	#include "imguiThemes.h"
#pragma endregion

#include "prototipos.hpp"

using namespace std;

int main(){
	sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML app");
	Serpiente snake;
	Manzana apple((LIM_IZQ+LIM_DER)/2, (LIM_SUP+LIM_INF)/2 + 4);
	#pragma region imgui
		ImGui::SFML::Init(window);
		imguiThemes::gray();

		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.FontGlobalScale = 2.f;
		ImGuiStyle &style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg].w = 0.5f;
		//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
	#pragma endregion

	//window.setVerticalSyncEnabled(true);	
	sf::Clock clock;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){		
			#pragma region imgui
				ImGui::SFML::ProcessEvent(window, event);
			#pragma endregion
				
			if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::Resized){
					// Adjust the viewport when the window is resized
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}
		}
		//calculate the delta time
		sf::Time deltaTime = clock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();
		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = max(deltaTimeSeconds, 0.f);

	#pragma region imgui
		ImGui::SFML::Update(window, deltaTime);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	#pragma endregion

		//game code....
		window.clear();
		imprimirLimites(window);
		apple.imprimir(window);
		snake.imprimirCuerpo(window);
	
	#pragma region imgui
		ImGui::SFML::Render(window);
	#pragma endregion
	
		window.display();
	}

#pragma region imgui
	ImGui::SFML::Shutdown();
#pragma endregion
	return 0;
}

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

Serpiente::Serpiente(){
    for(int i=0; i<3; i++){
        cuerpo.emplace_back((LIM_IZQ+LIM_DER)/2, (LIM_SUP+LIM_INF)/2 - i);
    }
    directionX=1;
    directionY=0;
}

void Serpiente::imprimirCuerpo(sf::RenderWindow &window){
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cell.setFillColor(sf::Color::Blue);
	for(int i=0; i<cuerpo.size(); i++){
		cell.setPosition(
			cuerpo[i].y * CELL_SIZE, 
			cuerpo[i].x * CELL_SIZE
		);
		window.draw(cell);
	}
}

void Manzana::imprimir(sf::RenderWindow &window){
	sf::CircleShape apple (CELL_SIZE/2);
	apple.setFillColor(sf::Color::Red);
	apple.setPosition(
		coordY * CELL_SIZE, 
		coordX * CELL_SIZE
	);
	window.draw(apple);
}