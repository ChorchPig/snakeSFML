#include <SFML/Graphics.hpp>
#include <iostream>
#include "prototipos.hpp"

#pragma region imgui
	#include "imgui.h"
	#include "imgui-SFML.h"
	#include "imguiThemes.h"
#pragma endregion

//Completamente funcional, faltaría mejorar la estética en todo caso

using namespace std;



int main(){
	sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML app");
	window.setFramerateLimit(60);
	
	Serpiente snake;
	Manzana apple((LIM_IZQ+LIM_DER)/2 + 4, (LIM_SUP+LIM_INF)/2);
	int puntos=0, mejor=leerMejorPuntaje();
	bool gameOver=false;

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

	sf::Clock clock;
	float timer=0.f;
	const float moveInterval=0.15f;

	
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){		
			#pragma region imgui
				ImGui::SFML::ProcessEvent(window, event);
			#pragma endregion
				
			if (event.type == sf::Event::Closed)
					window.close();
			else if (event.type == sf::Event::KeyPressed){
				switch (event.key.code){ //problema en cambiarDirección()
				case sf::Keyboard::Up :	
					snake.cambiarDireccion(0, -1); break;
				case sf::Keyboard::Down :
					snake.cambiarDireccion(0, 1); break;
				case sf::Keyboard::Left :
					snake.cambiarDireccion(-1, 0); break;
				case sf::Keyboard::Right :
					snake.cambiarDireccion(1, 0); break;
				default: break;
				}
			}
			else if (event.type == sf::Event::Resized){
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

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

		//game code...
		window.clear();
		imprimirLimites(window);
		apple.imprimir(window);
		snake.imprimirCuerpo(window);
		timer+=deltaTimeSeconds;
		if(!gameOver && timer>=moveInterval && !snake.choque()){
			timer-=moveInterval;
			bool crecer=snake.vaAComer(apple);
			snake.mover(crecer);
			if(crecer){
				apple.reubicar(snake.getCuerpo());
				puntos++;
			}
		}
		else if(snake.choque()){
			gameOver=true;
		}
			

	#pragma region imgui
		ImGui::SFML::Render(window);
	#pragma endregion
	imprimirMejorPuntaje(window, mejor);
	imprimirPuntaje(window, puntos);
	window.display();
	}
	guardarMejorPuntaje(puntos);

#pragma region imgui
	ImGui::SFML::Shutdown();
#pragma endregion
	return 0;
}