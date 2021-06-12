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
		sf::Texture* grassTexture = new sf::Texture();
		if (!(*grassTexture).loadFromFile("../sources/Grass.png"))
		{
			std::cout << "Error" << std::endl;
		}
		sf::Texture* nodeTextureCol = new sf::Texture();
		if (!(*nodeTextureCol).loadFromFile("../sources/Ant.png"))
		{
			std::cout << "Error while loading the ant from the file" << std::endl;
		};
		nodeSprite.push_back(sf::Sprite());
		nodeSprite[0].setScale({ 0.1, 0.1 });
		nodeSprite[0].setTexture(*nodeTextureCol);
		for (size_t i = 1; i < 10; ++i) {
			nodeSprite.push_back(sf::Sprite());
			sf::Texture* nodeTexture = new sf::Texture();
			if (!(*nodeTexture).loadFromFile("../sources/Aphid-"+std::to_string(i)+".png"))
			{
				std::cout << "Error while loading the ant from the file" << std::endl;
			};
			nodeSprite[i].setScale({ 0.1, 0.1 });
			nodeSprite[i].setTexture(*nodeTexture);
		}
		
		grassSprite.setTexture(*grassTexture);
		grassSprite.setPosition((window.getSize().x / 23) * 0.5, (window.getSize().y / 10));
		grassSprite.setTextureRect(sf::IntRect(0, 0, static_cast<double>((window.getSize().x / 3) * 2), static_cast<double>((window.getSize().y / 10) * 8)));
	}
	void drawWindow(const core::AppState& state) {
		//window setup
		auto desktop = sf::VideoMode::getDesktopMode();
		window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

		if (state == core::AppState::state_started) {
			//white background
			//Button btn1("Click", { 10,10 }, { 100,100 }, sf::Color::White, sf::Color::Black, 2, font_1, 14, sf::Color::Black);

			Button btn1 = Button::builder().setString(L"Начать").setSize({ 180, 50 }).setOutlineColor(sf::Color::Black).setOutlineThickness(2).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).build();

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
					drawNode(&el);
				}
				btn1.drawTo(window);
				
				window.display();
			}
			/*window.clear();
			textbox1.drawTo(window);
			window.display();*/
		};
		if (state == core::AppState::state_nodes) {
			Button btn1 = Button::builder().setString(L"Далее").setOutlineThickness(2).setOutlineColor(sf::Color::Black).setSize({ 180, 50 }).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).build();
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
							if (core::nodes.size() > 1) return;
							btn1.setFill(sf::Color::Red);
						}
						if (isOverGrass((sf::Vector2f)sf::Mouse::getPosition(window))) {
							if (core::nodes.size() == 10) continue;
							sf::Vector2f vec = getRightCoordinates((sf::Vector2f)sf::Mouse::getPosition(window));
							core::nodes.push_back(core::Node{ vec.x, vec.y, (unsigned)(core::nodes.size()) });
							drawNode(&core::nodes[core::nodes.size() - 1]);
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
					drawNode(&el);
				}
				//textbox1.drawTo(window);
				btn1.drawTo(window);

				window.display();
			}
		};
		if (state == core::AppState::state_ants) {
			sf::Text text;
			text.setFillColor(sf::Color::Black);
			text.setCharacterSize(25);
			text.setFont(font_1);
			text.setPosition({ (float)(window.getSize().x * 0.72), (float)(window.getSize().y * 0.65) });
			text.setString(L"Кол-во муравьев (1-9): ");
			TextBox tb(30, sf::Color::Black, true);
			tb.setPosition({ (float)(window.getSize().x * 0.94), (float)(window.getSize().y * 0.63) });
			tb.setFont(font_1);
			Button btn1 = Button::builder().setString(L"Далее").setOutlineColor(sf::Color::Black).setOutlineThickness(2).setSize({ 180, 50 }).setPosition({ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.4) }).build();
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
							if (tb.getText().length() == 1)
							{
								core::numberOfAnts = stoi(tb.getText());
								return;
							} 
							btn1.setFill(sf::Color::Red);
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
					drawNode(&el);
				}
				tb.drawTo(window);
				window.draw(text);
				btn1.drawTo(window);
				window.display();
				}
		}
		if (state == core::AppState::state_execution) {				// нужно перенести отрисовку поля, узлов и т.д в отдельную функцию, чтобы вызывать при каждом стейте

			sf::Text bestPathText;
			bestPathText.setFont(font_1);
			bestPathText.setString(L"Кратчайшая длина: ");
			bestPathText.setCharacterSize(20);
			bestPathText.setPosition(window.getSize().x * 0.7, window.getSize().y * 0.8);
			bestPathText.setFillColor(sf::Color::Black);

			sf::Text bestPathText2;
			bestPathText2.setFont(font_1);
			bestPathText2.setString(L"Лучший путь: \n");
			bestPathText2.setCharacterSize(20);
			bestPathText2.setPosition(window.getSize().x * 0.7, window.getSize().y * 0.85);
			bestPathText2.setFillColor(sf::Color::Black);

			sf::Text bestPathText3;
			bestPathText3.setFont(font_1);
			bestPathText3.setString(L" ");
			bestPathText3.setCharacterSize(20);
			bestPathText3.setPosition(window.getSize().x * 0.7, window.getSize().y * 0.89);
			bestPathText3.setFillColor(sf::Color::Black);

	
			//white background
			window.clear(sf::Color::White);

			Button btnStop = Button::builder().setString(L"Стоп").setSize({ 180, 50 }).setPosition(sf::Vector2f{ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.3) }).setOutlineColor(sf::Color::Black).setOutlineThickness(1).build();

			Button btnStats = Button::builder().setString(L"Логи").setSize({ 180, 50 }).setPosition(sf::Vector2f{ (float)(window.getSize().x * 0.8), (float)(window.getSize().y * 0.5) }).setOutlineColor(sf::Color::Black).setOutlineThickness(1).build();

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
						drawNode(&el);
					}
					core::bestPath.mut.lock();
					if (!core::bestPath.route.empty()) {
						
						bestPathText.setString(L"Кратчайшая длина: " + std::to_wstring((int)std::round(core::bestPath.len)) + L" пикс.");
						sf::String str = L"";
						for (auto& el : core::bestPath.route) {
							str += std::to_wstring(el) + L"->";
						}
						str.erase(str.getSize() - 2, 2);
						bestPathText3.setString(str);

					}
					core::bestPath.mut.unlock();
					//textbox1.drawTo(window);
					btnStop.drawTo(window);
					btnStats.drawTo(window);
					window.draw(bestPathText);
					window.draw(bestPathText2);
					window.draw(bestPathText3);

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
	void drawNode(const core::Node* node) {
		sf::Vector2u size = nodeSprite[node->getId()].getTexture()->getSize();

		nodeSprite[node->getId()].setPosition((float)node->getX() - size.x / 20, (float)node->getY() - size.y / 20);		// scale муравья 0.1 <=> texture.size/10
																					// мы хотим, чтобы картинка располагалась по центру (size / 2) выходит texture.size/10/2
		window.draw(nodeSprite[node->getId()]);
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
		static float rBound = posx + grx - nodeSprite[1].getTexture()->getSize().x / 10;
		static float lBound = posx + nodeSprite[1].getTexture()->getSize().x / 10;
		static float tBound = posy + nodeSprite[1].getTexture()->getSize().y / 10;
		static float bBound = posy + gry - nodeSprite[1].getTexture()->getSize().y / 10;
		if (clickPos.x < rBound && clickPos.x > lBound && clickPos.y > tBound && clickPos.y < bBound) {
			return clickPos;
		}
		else {
			if (clickPos.x < lBound && clickPos.y < tBound)	// 1
			{
				return sf::Vector2f{ lBound - nodeSprite[1].getTexture()->getSize().x / 20, tBound - nodeSprite[1].getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x < lBound && clickPos.y > bBound) // 2
			{
				return sf::Vector2f{ lBound - nodeSprite[1].getTexture()->getSize().x / 20, bBound + nodeSprite[1].getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x < lBound) // 3
			{
				return sf::Vector2f{ lBound - nodeSprite[1].getTexture()->getSize().x / 20, clickPos.y };
			} else
			if (clickPos.x > rBound && clickPos.y < tBound) // 4
			{
				return sf::Vector2f{ rBound + nodeSprite[1].getTexture()->getSize().x / 20, tBound - nodeSprite[1].getTexture()->getSize().y / 20 };
			} else
			if (clickPos.x > rBound && clickPos.y > bBound) // 5
			{
				return sf::Vector2f{rBound + nodeSprite[1].getTexture()->getSize().x / 20, bBound + nodeSprite[1].getTexture()->getSize().y / 20};
			} else
			if (clickPos.x > rBound) // 6
			{
				return sf::Vector2f{ rBound + nodeSprite[1].getTexture()->getSize().x / 20, clickPos.y };
			} else
			if (clickPos.y < tBound) // 7
			{
				return sf::Vector2f{ clickPos.x, tBound - nodeSprite[1].getTexture()->getSize().y / 20 };
			} else
			if (clickPos.y > bBound)  // 8
			{
				return sf::Vector2f{ clickPos.x, bBound + nodeSprite[1].getTexture()->getSize().y / 20 };
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
