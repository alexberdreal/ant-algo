#ifndef VISUALIZATION
#define VISUALIZATION

#include "Core.h"
#include <SFML/Graphics.hpp>
#include <windows.h> // SetConsoleOutputCP(1251); SetConsoleCP(1251);
#include <sstream>
#include <string>
#include <iostream>

//for TextBox
constexpr auto DELETE_KEY = 8;
constexpr auto ENTER_KEY = 13;
constexpr auto ESCAPE_KEY = 27;

// Для передачи узлов в Source.cpp
static double tempX, tempY;

namespace Visual {
	class Button {
	public:
		class builder;
		//Button(std::string input, sf::Vector2f pos, sf::Vector2f size, sf::Color fill, sf::Color outline, float out_thick, sf::Font &font, int textSize, sf::Color textColor) {
		//	/*button.setPosition(pos);
		//	button.setSize(size);
		//	button.setFillColor(fill);
		//	button.setOutlineColor(outline);
		//	button.setOutlineThickness(out_thick);*/

		
		//	text.setFont(font);
		//	text.setCharacterSize(textSize);
		//	text.setFillColor(textColor);
		//}
		Button(sf::RectangleShape button, sf::Text text) : button(button), text(text) {};
		void setFill(sf::Color fill) {
			button.setFillColor(fill);
		}
		/*void setOutline
		void setFont()
		void setTextSize
		void set*/

		void setPosition(sf::Vector2f pos) {
			button.setPosition(pos);

			//What is longer?
			//text.setPosition(pos.x + button.getGlobalBounds().width/2 - text.getGlobalBounds().width, pos.y + button.getGlobalBounds().height/2 - text.getGlobalBounds().height/2);
			float xPos = pos.x + button.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2;
			float yPos = pos.y + button.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2;
			text.setPosition(xPos, yPos);
		}

		bool isMouseOver(sf::RenderWindow& window) {

			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;

			float btnStartX = button.getPosition().x;
			float btnStartY = button.getPosition().y;

			float btnEndX = button.getPosition().x + button.getGlobalBounds().width;
			float btnEndY = button.getPosition().y + button.getGlobalBounds().height;

			if (x > btnStartX && x< btnEndX && y>btnStartY && y < btnEndY)
				return true;
			return false;
		}
		void drawTo(sf::RenderWindow& window) {
			window.draw(button);
			//std::cout << text.getString().getData();
			window.draw(text);

		}

	private:
		sf::RectangleShape button;
		sf::Text text;
	};

	class Button::builder { //definition
	public:
		builder& setPosition(sf::Vector2f pos) { button.setPosition(pos); return *this; };
		builder& setSize(sf::Vector2f size) { button.setSize(size); return *this; }
		builder& setFillColor(sf::Color color) { button.setFillColor(color); return *this; };
		builder& setOutlineColor(sf::Color color) { button.setOutlineColor(color); return *this; };
		builder& setOutlineThickness(int thickness) { button.setOutlineThickness(thickness); return *this; }

		//	text.setString(input);
		//	text.setFont(font);
		//	text.setCharacterSize(textSize);
		//	text.setFillColor(textColor);
		//}
		builder& setString(std::string string) { text.setString(string); return *this; };
		builder& setFont(sf::Font font) { text.setFont(font); return *this; };
		//builder& text.setCharacterSize(textSize);
		//	text.setFillColor(textColor);
		//Button btn1 = Button::builder().setPosition - internal set({ 200,200 }).build() - returns initialized object button with fields of builder;
		Button build() const
		{
			return Button(button, text);  //initializes button with button,text
		}
	private:
		sf::RectangleShape button;
		sf::Text text;
	};

	class TextBox {
	public:
		//textBox() {};
		TextBox(int size, sf::Color color, bool sel) {
			textbox.setCharacterSize(size);
			textbox.setFillColor(color);
			isSelected = sel;
			if (sel) {
				textbox.setString("_");
			}
			else textbox.setString("");
		}
		void setFont(sf::Font& font) {
			textbox.setFont(font);
		}
		void setPosition(sf::Vector2f pos) {
			textbox.setPosition(pos);
		}
		void setLimit(bool hasLimit) {
			this->hasLimit = hasLimit;
		}
		void setLimit(bool hasLimit, int limit) {
			this->hasLimit = hasLimit;
			this->limit = limit;
		}
		void setSelected(bool sel) {   //what the fuck?
			isSelected = sel;
			if (!sel) {
				std::string s = text.str();
				std::string newS = "";
				for (int i = 0; i < s.length() - 1; ++i) {
					newS += s[i];
				}
				textbox.setString(newS);
			}
		}
		std::string getText() {
			return text.str();
		}
		void drawTo(sf::RenderWindow& window) {
			window.draw(textbox);
		}
		void typedOn(sf::Event input) {
			if (isSelected) {
				int charTyped = input.text.unicode;
				if (charTyped < 128) {
					if (hasLimit) {
						if (text.str().length() <= limit) {			//why <=
							inputLogic(charTyped);
						}
						else if (text.str().length() > limit && (charTyped == DELETE_KEY)) {
							deleteLastChar();
						}
					}
					else {
						inputLogic(charTyped);
					}
				}
			}
		}


	private:
		sf::Text textbox;
		std::ostringstream text;
		bool isSelected;
		bool hasLimit;
		int limit;
		void inputLogic(int charTyped) {
			if ((charTyped != DELETE_KEY) && (charTyped != ENTER_KEY) && (charTyped != ESCAPE_KEY)) {
				text << static_cast<char>(charTyped); //write to string object

			}
			else if (charTyped == DELETE_KEY) {
				deleteLastChar();

			}
			textbox.setString(text.str() + "_");
		}
		void deleteLastChar() {
			std::string s = text.str();
			std::string newS = "";
			for (int i = 0; i < s.length() - 1; ++i) {
				newS += s[i];
			}
			text.str(""); //clean
			text << newS; //add newS to string output
			//textbox.setString(newS);
			textbox.setString(text.str() + "_");			//set the string to display
		}
	};
	
	inline sf::Font font_1;
	inline sf::RenderWindow window(sf::VideoMode(1400, 768), "SFML works!");

	//Загрузка шрифтов и текстур
	void prepareVisual();

	// Отрисовка главного окна и его внутреннего содержимого
	void drawWindow(const core::AppState& state);

	// Обновление статистики внутри окна
	void updateStatistics();

	// Отрисовка вершин графа (муравейника и пищи)
	void drawNode(double x, double y);

	// Отрисовка пути p1 --> p2
	void drawPath(sf::Vector2f p1, sf::Vector2f p2);

	// Изменение толщины тропы из феромонов A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2);

	// Ожидание события
	core::AppEvent waitForEvent();

	// Стереть граф, очистить статистику
	void clean();
}

#endif