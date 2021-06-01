#include "Visualization.h"
#include "Core.h"
#include <iostream>
#include <sstream>
#include <string>

namespace Visual {

	void prepareVisual() {
		if (!font_1.loadFromFile("../sources/Open_Sans/OpenSans-Light.ttf"))
		{
			std::cout << "Error while loading the font from the file" << std::endl;
		};
	}
	void drawWindow(const core::AppState& state) {
		if (&state == &core::state_started) {
			TextBox textbox1(12, sf::Color::Black, true);

			textbox1.setFont(font_1);
			textbox1.setPosition({ 10,10 });

			//window setup
			auto desktop = sf::VideoMode::getDesktopMode();
			window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

			//white background
			window.clear(sf::Color::White);


			//grass
			sf::Texture grass;
			if (!grass.loadFromFile("../sources/Grass.png"))
			{
				std::cout << "Error" << std::endl;
			}
			//sf::Sprite sprite_grass(grass, sf::IntRect(0, 0, 100, 100));

			sf::Sprite sprite_grass(grass, sf::IntRect(0, 0, static_cast<double>((window.getSize().x / 3) * 2), static_cast<double>((window.getSize().y / 10) * 8)));
			sprite_grass.setPosition((window.getSize().x / 23) * 0.5, (window.getSize().y / 10) * 1.5);

			//Button btn1("Click", { 10,10 }, { 100,100 }, sf::Color::White, sf::Color::Black, 2, font_1, 14, sf::Color::Black);

			Button btn1 = Button::builder().setPosition({ 200,200 }).build();

			sf::Texture ant;
			if (!ant.loadFromFile("../sources/Ant.png"))
			{
				std::cout << "Error" << std::endl;
			}
			sf::Sprite sprite_ant(ant, sf::IntRect(0, 0, static_cast<double>(window.getSize().x / 3), static_cast<double>((window.getSize().y / 10) * 6)));
			sprite_ant.setPosition((window.getSize().x / 23) * 0.5 * 2 + static_cast<double>((window.getSize().x / 3) * 2), (window.getSize().y / 10) * 1.5);
			sprite_ant.setScale(sf::Vector2f(0.2, 0.2));

			sf::Texture btn;
			if (!btn.loadFromFile("../sources/Button.png"))
			{
				std::cout << "Error" << std::endl;
			}
			sf::Sprite sprite_btn(btn);
			sprite_btn.setPosition((window.getSize().x / 23) * 0.5 * 2 + static_cast<double>((window.getSize().x / 3) * 2), static_cast<double>(window.getSize().y / 10));
			sprite_btn.setScale(sf::Vector2f(0.2, 0.2));
			/*window.draw(sprite_grass);
			textbox1.drawTo(window);
			btn1.drawTo(window);
			window.draw(sprite_ant);
			window.draw(sprite_btn);

			window.display();*/

			while (window.isOpen()) {
				sf::Event event;					//class Event
				while (window.pollEvent(event)) {
					switch (event.type) {			//enum type
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::TextEntered:	//enum {TextEntered}
						textbox1.typedOn(event);
						textbox1.drawTo(window);
						break;
					case sf::Event::MouseButtonPressed:
						if (btn1.isMouseOver(window)) {
							btn1.setFill(sf::Color::Yellow);
						}
						break;
					case sf::Event::MouseMoved:
						if (btn1.isMouseOver(window)) {
							btn1.setFill(sf::Color::Green);
						}
						else {
							btn1.setFill(sf::Color::White);
						}
						break;
					}

				}
				window.clear(sf::Color::White);
				window.draw(sprite_grass);
				//textbox1.drawTo(window);
				btn1.drawTo(window);
				window.draw(sprite_ant);
				window.draw(sprite_btn);
				for (size_t i = 0; i < core::nodes.size() - 1; ++i) {
					for (size_t j = i + 1; j < core::nodes.size(); ++j) {
						drawPath({ (float)core::nodes[i].getX(), (float)core::nodes[i].getY() }, { (float)core::nodes[j].getX(), (float)core::nodes[j].getY() });
					}
				}
				window.display();
			}
			/*window.clear();
			textbox1.drawTo(window);
			window.display();*/
		};
		if (&state == &core::state_nodes) {};
	};

	// Обновление статистики внутри окна
	void updateStatistics() {

	};

	// Отрисовка вершин графа (муравейника и пищи)
	void drawNode(double x, double y) {

	};

	// Отрисовка пути A(x1, y1) --> B(x2, y2)
	void drawPath(sf::Vector2f p1, sf::Vector2f p2) {

		const float len = (float)core::findLength(p1.x, p1.y, p2.x, p2.y);
		const float thickness = 3.0;

		#define TODEGREE(R) R * (180 / M_PI) 

		sf::CircleShape ss1;
		sf::CircleShape ss2;
		ss1.setFillColor(sf::Color::Red);
		ss2.setFillColor(sf::Color::Red);
		ss1.setPosition(p1);
		ss2.setPosition(p2);
		ss1.setRadius(2);
		ss2.setRadius(2);

		/////////////////////////////////////////////

		sf::RectangleShape rs;
		rs.setFillColor(sf::Color::Black);

		if (p1.y == p2.y) {
			if (p2.x < p1.x) {
				rs.setPosition(p2);
				rs.setSize({ len, thickness });
			}
			else {
				rs.setPosition(p1);
				rs.setSize({ len, thickness });
			}
		}
		else if (p1.x == p2.x) {
			if (p2.y < p1.y) {
				rs.setPosition(p2);
				rs.setSize({ thickness, len });
			}
			else {
				rs.setPosition(p1);
				rs.setSize({ thickness, len });
			}
		}
		else {
			rs.setPosition(p1);
			rs.setSize({ len, thickness });

			if (p2.x > p1.x && p1.y > p2.y) {
				rs.setRotation(-TODEGREE(atan((p1.y - p2.y) / (p2.x - p1.x))));
			}
			else if (p1.x > p2.x && p1.y > p2.y) {
				rs.setRotation(-90 - TODEGREE(atan((p1.x - p2.x) / (p1.y - p2.y))));
			}
			else if (p1.x < p2.x && p2.y > p1.y) {
				rs.setRotation(TODEGREE(atan((p2.y - p1.y) / (p2.x - p1.x))));
			}
			else if (p1.x > p2.x && p2.y > p1.y) {
				rs.setRotation(90 + TODEGREE(atan((p1.x - p2.x) / (p2.y - p1.y))));
			}
		}

		Visual::window.draw(rs);

		/////////////////////////////////////////////
		Visual::window.draw(ss1);
		Visual::window.draw(ss2);
	};

	// Изменение толщины тропы из феромонов A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2) {

	};

	// Ожидание события
	core::AppEvent waitForEvent() {
		////expecting event from window
		//while (window.isOpen())
		//{
		//	sf::Event event;
		//	while (window.pollEvent(event))  // 1.  
		//	{
		//		if (event.type == sf::Event::Closed)
		//			window.close();
		//	}
		//}
		return core::AppEvent::LAUNCH;
	};

	// Стереть граф, очистить статистику
	void clean() {

	};
}
