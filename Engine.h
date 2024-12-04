#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};

Engine::Engine(){
	m_Window.create(VideoMode(VideoMode::getDesktopMode()), "Particles", Style::Default);

	cout << "Width: " << VideoMode::getDesktopMode().width << " Height: " << VideoMode::getDesktopMode().height << endl;
}

void Engine::run(){
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()){
		Time t = clock.restart();
		float seconds = t.asSeconds();

		input();
		update(seconds);
		draw();
	}
}

void Engine::input(){
	Event event;
	while (m_Window.pollEvent(event)){

		if (event.type == Event::Closed){
			m_Window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			m_Window.close();
		}

		if (event.mouseButton.button == Mouse::Left){
			Vector2i mousePosition = Mouse::getPosition(m_Window);
			cout << "Mouse Pos X: " << mousePosition.x << " Mouse Pos Y: " << mousePosition.y << endl;
			for (int i = 0; i < 5; i++){
				int numPoints = (rand() % 26) + 25;
				m_particles.emplace_back(m_Window, numPoints, mousePosition);
			}
		}
	}
}

void Engine::update(float dtAsSeconds){
	for (vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end();){
		if (it->getTTL() > 0){
			it->update(dtAsSeconds);
			it++;
		}
		else {
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw(){
	m_Window.clear();

	for (const auto& p : m_particles){
		m_Window.draw(p);
	}

	m_Window.display();
}