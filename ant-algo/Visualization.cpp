#include "Visualization.h"
#include "Core.h"
#include <SFML/Graphics.hpp>

namespace Visual {

	// ��������� �������� ���� � ��� ����������� �����������
	void drawWindow(const core::AppState& state) {
		sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(shape);
			window.display();
		}
	};

	// ���������� ���������� ������ ����
	void updateStatistics() {

	};

	// ��������� ������ ����� (����������� � ����)
	void drawNode(double x, double y) {

	};

	// ��������� ���� A(x1, y1) --> B(x2, y2)
	void drawPath(double x1, double y1, double x2, double y2) {

	};

	// ��������� ������� ����� �� ��������� A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2) {

	};

	// �������� �������
	core::AppEvent waitForEvent() {
		return core::AppEvent::LAUNCH;
	};

	// ������� ����, �������� ����������
	void clean() {

	};
}