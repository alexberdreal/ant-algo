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

// ��� �������� ����� � Source.cpp
static double tempX, tempY;

namespace Visual {

	inline sf::Font font_1;
	inline sf::RenderWindow window(sf::VideoMode(1400, 768), "SFML works!");
	inline sf::Sprite nodeSprite;
	inline sf::Sprite grassSprite;

	class Slider {
		sf::Vector2f handSize;
		sf::Vector2f lineSize;
		sf::Vector2f handPos;
		sf::Vector2f linePos;
		sf::RectangleShape handShape;
		sf::RectangleShape lineShape;
		bool inTarget;
	public:
		Slider() : inTarget(false) {
			handSize.x = 5.0;
			handSize.y = 20.0;
			lineSize.x = 100.0;
			lineSize.y = 3.0;
			linePos.x = window.getSize().x * 0.8;
			linePos.y = window.getSize().y * 0.5;
			handPos.x = (float)(linePos.x + lineSize.x / 2 - handSize.x / 2);
			handPos.y = (float)(linePos.y) - handSize.y / 2;

			handShape.setFillColor(sf::Color::Blue);
			handShape.setSize(handSize);
			lineShape.setFillColor(sf::Color::Black);
			lineShape.setSize(lineSize);
			lineShape.setPosition(linePos);
			handShape.setPosition(handPos);
		}
		void setPos(float x) {
			if (handPos.x != x) {
				handPos.x = x;
				if (x < linePos.x) handPos.x = linePos.x;
				if (x > linePos.x + lineSize.x) handPos.x = linePos.x + lineSize.x;
				handShape.setPosition(handPos.x, handPos.y);
			}
		}
		void draw(sf::RenderWindow& wind) {
			wind.draw(lineShape);
			wind.draw(handShape);
		}
		bool isSliderOver(float x, float y) {
			if (inTarget) {
				return (x <= linePos.x + lineSize.x) && (x >= linePos.x);
			}
			else {
				return (y <= handPos.y + handSize.y) && (y >= handPos.y) && (x <= linePos.x + lineSize.x) && (x >= linePos.x);
			}
		}
		void setInTarget(bool is) {
			inTarget = is;
		}
		bool isInTarget() {
			return inTarget;
		}
		bool isMouseOver(sf::RenderWindow& win) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			return isSliderOver(x, y);
		}
	};

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
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::Black);
			text.setFont(font_1);
			window.draw(text);
		}

	private:
		sf::RectangleShape button;
		sf::Text text;
	};

	class Button::builder { //definition
	public:
		builder& setPosition(sf::Vector2f pos) {
			button.setPosition(pos);
			float xPos = pos.x + button.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2;
			float yPos = pos.y + button.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2;
			text.setPosition(xPos, yPos); 
			return *this; 
		};
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

	//�������� ������� � �������
	void prepareVisual();

	// ��������� �������� ���� � ��� ����������� �����������
	void drawWindow(const core::AppState& state);

	// ���������� ���������� ������ ����
	void updateStatistics();

	// ��������� ������ ����� (����������� � ����)
	void drawNode(double x, double y);

	// ��������� ���� p1 --> p2
	void drawPath(sf::Vector2f p1, sf::Vector2f p2);

	// ��������� ������� ����� �� ��������� A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2);

	// �������� �������
	core::AppEvent waitForEvent();

	// ������� ����, �������� ����������
	void clean();
}



#endif