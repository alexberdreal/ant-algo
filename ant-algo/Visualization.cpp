#define _CRT_SECURE_NO_WARNINGS
#include "Visualization.h"
#include "Core.h"
#include <iostream>
#include <sstream>
#include <string>

/*
	Планы:
	1. Муравей --- тля
	2. Перекрасить в разные цвета, в зав-ти от номера
	3. Установить ограничение по количеству муравьев
	4. Спросить у Оли насчет руссификации 

*/


int v = 8;

namespace Visual {

	void cmdStateChanged() {
		static HWND cmd = GetConsoleWindow();
		showCmd= !showCmd;
		if (showCmd) {
			ShowWindow(cmd, SW_SHOW);
			return;
		}
		ShowWindow(cmd, SW_HIDE);
	}

	void prepareVisual() {
		if (!font_1.loadFromFile("../sources/Open_Sans/OpenSans-Bold.ttf"))
		{
			std::cout << "Error while loading the font from the file" << std::endl;
		};
		sf::Texture* nodeTexture = new sf::Texture();
		if (!(*nodeTexture).loadFromFile("../sources/Aphid-1.png"))
		{
			std::cout << "Error while loading the ant from the file" << std::endl;
		};
		sf::Texture* grassTexture = new sf::Texture();
		if (!(*grassTexture).loadFromFile("../sources/Grass.png"))
		{
			std::cout << "Error" << std::endl;
		}
		
		nodeSprite.setScale({ 0.1, 0.1 });
		nodeSprite.setTexture(*nodeTexture);
		grassSprite.setTexture(*grassTexture);
		grassSprite.setPosition((window.getSize().x / 23) * 0.5, (window.getSize().y / 10));
		grassSprite.setTextureRect(sf::IntRect(0, 0, static_cast<double>((window.getSize().x / 3) * 2), static_cast<double>((window.getSize().y / 10) * 8)));
	}
	void drawWindow(const core::AppState& state) {
		//window setup
		auto desktop = sf::VideoMode::getDesktopMode();
		window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

		if (&state == &core::state_started) {
			//white background
			//Button btn1("Click", { 10,10 }, { 100,100 }, sf::Color::White, sf::Color::Black, 2, font_1, 14, sf::Color::Black);

			Button btn1 = Button::builder().setString("Feed").setSize({ 180, 50 }).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).build();

			sf::Texture ant;

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
				window.clear(sf::Color::White);
				sf::Event event;					//class Event
				while (window.pollEvent(event)) {
					switch (event.type) {			//enum type
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::MouseButtonPressed:
						if (btn1.isMouseOver(window)) {
							btn1.setFill(sf::Color::Yellow);
							return;
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
				window.draw(grassSprite);
				for (auto& el : core::nodes) {
					drawNode(el.getX(), el.getY());
				}
				btn1.drawTo(window);
				
				window.display();
			}
			/*window.clear();
			textbox1.drawTo(window);
			window.display();*/
		};
		if (&state == &core::state_nodes) {
			Button btn1 = Button::builder().setString("Continue").setSize({ 180, 50 }).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).build();
			while (window.isOpen()) {
				window.clear(sf::Color::White);

				sf::Event event;					//class Event
				while (window.pollEvent(event)) {
					switch (event.type) {			//enum type
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::MouseButtonPressed:
						if (btn1.isMouseOver(window)) {
							btn1.setFill(sf::Color::Yellow);
							return;
						}
						if (isOverGrass((sf::Vector2f)sf::Mouse::getPosition(window))) {
							std::cout << "OVER" << std::endl;
							sf::Vector2f vec = getRightCoordinates((sf::Vector2f)sf::Mouse::getPosition(window));
							core::nodes.push_back(core::Node{ vec.x, vec.y, (unsigned)(core::nodes.size()) });
							drawNode(vec.x, vec.y);
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
				window.draw(grassSprite);
				for (auto& el : core::nodes) {
					drawNode(el.getX(), el.getY());
				}
				//textbox1.drawTo(window);
				btn1.drawTo(window);

				window.display();
			}
		};
		if (&state == &core::state_ants) {
			TextBox tb(30, sf::Color::Black, true);
			tb.setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.65) });
			tb.setFont(font_1);
			Button btn1 = Button::builder().setString("Continue").setSize({ 180, 50 }).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).build();
			while (window.isOpen()) {
				window.clear(sf::Color::White);

				sf::Event event;					//class Event
				while (window.pollEvent(event)) {
					switch (event.type) {			//enum type
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::MouseButtonPressed:
						if (btn1.isMouseOver(window)) {
							btn1.setFill(sf::Color::Yellow);
							core::numberOfAnts = stoi(tb.getText());
							return;
						}
						break;
					case sf::Event::TextEntered:	//enum {TextEntered}
						tb.typedOn(event);
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
				window.draw(grassSprite);
				for (auto& el : core::nodes) {
					drawNode(el.getX(), el.getY());
				}
				tb.drawTo(window);
				btn1.drawTo(window);
				window.display();
				}
		}
		if (&state == &core::state_execution) {				// нужно перенести отрисовку поля, узлов и т.д в отдельную функцию, чтобы вызывать при каждом стейте

			sf::Text bestPathText;
			bestPathText.setFont(font_1);
			bestPathText.setString("Best path: ");
			bestPathText.setCharacterSize(20);
			bestPathText.setPosition(window.getSize().x * 0.75, window.getSize().y * 0.8);
			bestPathText.setFillColor(sf::Color::Black);

			sf::Text bestPathText2;
			bestPathText2.setFont(font_1);
			bestPathText2.setString("Best path: ");
			bestPathText2.setCharacterSize(20);
			bestPathText2.setPosition(window.getSize().x * 0.75, window.getSize().y * 0.85);
			bestPathText2.setFillColor(sf::Color::Black);

	
			//white background
			window.clear(sf::Color::White);

			Button btnStop = Button::builder().setString("Stop").setSize({ 180, 50 }).setPosition(sf::Vector2f{ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.3) }).setOutlineColor(sf::Color::Black).setOutlineThickness(1).build();

			Button btnStats = Button::builder().setString("Statistics").setSize({ 180, 50 }).setPosition(sf::Vector2f{ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).setOutlineColor(sf::Color::Black).setOutlineThickness(1).build();

			//sf::Text bestRouteNodes;
			//sf::Text bestRouteLen;
			//bestRouteNodes.setFont(font_1);
			//bestRouteNodes.setString(sf::String{ "Длина лучшего маршрута: " + });

			Slider slider;

			bool b = false;

			while (window.isOpen()) {
				sf::Event event;					//class Event
				while (window.pollEvent(event)) {
					switch (event.type) {			//enum type
					case sf::Event::Closed:
						window.close();
						exit(EXIT_SUCCESS);
					case sf::Event::TextEntered:	//enum {TextEntered}
						break;
					case sf::Event::MouseButtonPressed:
						if (btnStop.isMouseOver(window)) {
							btnStop.setFill(sf::Color::Yellow);
							return;
						}
						if (btnStats.isMouseOver(window)) {
							btnStats.setFill(sf::Color::Yellow);
							cmdStateChanged();
						}
						if (slider.isMouseOver(window) && !slider.isInTarget()) {
							slider.setInTarget(true);
							slider.setPos(sf::Mouse::getPosition(window).x - slider.getHandSize().x / 2);
						}
						break;
					case sf::Event::MouseMoved:
						if (btnStop.isMouseOver(window)) {
							btnStop.setFill(sf::Color::Green);
						}
						else {
							btnStop.setFill(sf::Color::White);
						}
						if (btnStats.isMouseOver(window)) {
							btnStats.setFill(sf::Color::Green);
						}
						else {
							btnStats.setFill(sf::Color::White);
						}
						if (slider.isInTarget()) {
							slider.setPos(sf::Mouse::getPosition(window).x - slider.getHandSize().x / 2);
						}
						break;
					case sf::Event::MouseButtonReleased:
						if (slider.isInTarget()) {
							slider.setInTarget(false);
						}
						break;
					default: break;
					}
				}
					window.clear(sf::Color::White);
					window.draw(grassSprite);
					slider.draw(window);
					for (size_t i = 0; i < core::routeVec.size(); ++i) {
						
						try {
							drawPath({ core::routeVec.at(i).at(0), core::routeVec.at(i).at(1) }, { core::routeVec.at(i).at(2), core::routeVec.at(i).at(3) });
						}
						catch (...) {
							break;
						}
					}
					for (auto& el : core::nodes) {
						drawNode(el.getX(), el.getY());
					}
					core::bestPath.mut.lock();
					if (!core::bestPath.route.empty()) {
					
						bestPathText.setString("Best path len is " + std::to_string((int)std::round(core::bestPath.len)));
						sf::String str = "Route: ";
						for (auto& el : core::bestPath.route) {
							str += std::to_string(el) + "->";
						}
						str.erase(str.getSize() - 2, 2);
						bestPathText2.setString(str);

					}
					core::bestPath.mut.unlock();
					//textbox1.drawTo(window);
					btnStop.drawTo(window);
					btnStats.drawTo(window);
					window.draw(bestPathText);
					window.draw(bestPathText2);

					window.display();
					b = true;
				}
				/*window.clear();
				textbox1.drawTo(window);
				window.display();*/
			}
		};

	// Обновление статистики внутри окна
	void updateStatistics() {

	};

	bool isOverGrass(sf::Vector2f vec) {
		float grx = window.getSize().x / 3 * 2;
		float gry = window.getSize().y / 10 * 8;
		float posx = (window.getSize().x / 23) * 0.5;
		float posy = window.getSize().y / 10;
		std::cout << vec.x << "\t" << vec.y << std::endl;
		std::cout << grx << "\t" << gry << std::endl;
		return ((vec.x >= posx) &&
			(vec.x <= posx + grx) &&
			(vec.y >= posy) && (vec.y <= posy + gry));
	}

	// Отрисовка вершин графа (муравейника и пищи)
	void drawNode(double x, double y) {
		sf::Vector2u size = nodeSprite.getTexture()->getSize();

		nodeSprite.setPosition((float)x - size.x / 20, (float)y - size.y / 20);		// scale муравья 0.1 <=> texture.size/10
																					// мы хотим, чтобы картинка располагалась по центру (size / 2) выходит texture.size/10/2
		window.draw(nodeSprite);
	};

	// Отрисовка пути A(x1, y1) --> B(x2, y2)
	void drawPath(sf::Vector2f p1, sf::Vector2f p2) {

		const float len = (float)core::findLength(p1.x, p1.y, p2.x, p2.y);
		const float thickness = 4.0;

		#define TODEGREE(R) R * (180 / M_PI) 

		/*sf::CircleShape ss1;
		sf::CircleShape ss2;
		ss1.setFillColor(sf::Color::Red);
		ss2.setFillColor(sf::Color::Red);			// Точки для теста
		ss1.setPosition(p1);
		ss2.setPosition(p2);
		ss1.setRadius(2);
		ss2.setRadius(2);
		Visual::window.draw(ss1);
		Visual::window.draw(ss2);
		*/

		/////////////////////////////////////////////

		sf::RectangleShape rs;
		rs.setFillColor(sf::Color::Red);

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
	};

	sf::Vector2f getRightCoordinates(sf::Vector2f clickPos) {
		float grx = window.getSize().x / 3 * 2;
		float gry = window.getSize().y / 10 * 8;
		float posx = (window.getSize().x / 23) * 0.5;
		float posy = window.getSize().y / 10;
		static float rBound = posx + grx - nodeSprite.getTexture()->getSize().x / 10;
		static float lBound = posx + nodeSprite.getTexture()->getSize().x / 10;
		static float tBound = posy + nodeSprite.getTexture()->getSize().y / 10;
		static float bBound = posy + gry - nodeSprite.getTexture()->getSize().y / 10;
		if (clickPos.x < rBound && clickPos.x > lBound && clickPos.y > tBound && clickPos.y < bBound) {
			return clickPos;
		}
		else {
			if (clickPos.x < lBound && clickPos.y < tBound)	// 1
			{
				return sf::Vector2f{ lBound - nodeSprite.getTexture()->getSize().x / 20, tBound - nodeSprite.getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x < lBound && clickPos.y > bBound) // 2
			{
				return sf::Vector2f{ lBound - nodeSprite.getTexture()->getSize().x / 20, bBound + nodeSprite.getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x < lBound) // 3
			{
				return sf::Vector2f{ lBound - nodeSprite.getTexture()->getSize().x / 20, clickPos.y };
			} else
			if (clickPos.x > rBound && clickPos.y < tBound) // 4
			{
				return sf::Vector2f{ rBound + nodeSprite.getTexture()->getSize().x / 20, tBound - nodeSprite.getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x > rBound && clickPos.y > bBound) // 5
			{
				return sf::Vector2f{rBound + nodeSprite.getTexture()->getSize().x / 20, bBound + nodeSprite.getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x > rBound) // 6
			{
				return sf::Vector2f{ rBound + nodeSprite.getTexture()->getSize().x / 20, clickPos.y };
			} else
			if (clickPos.y < tBound) // 7
			{
				return sf::Vector2f{ clickPos.x, tBound - nodeSprite.getTexture()->getSize().y / 20 };
			} else
			if (clickPos.y > bBound)  // 8
			{
				return sf::Vector2f{ clickPos.x, bBound + nodeSprite.getTexture()->getSize().y / 20 };
			}
		}
	}

	

	// Изменение толщины тропы из феромонов A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2) {

	};

	// Стереть граф, очистить статистику
	void clean() {

	};
}
