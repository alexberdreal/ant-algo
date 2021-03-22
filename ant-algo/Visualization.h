#ifndef VISUALIZATION
#define VISUALIZATION

#include "Core.h"

// Для передачи узлов в Source.cpp
static double tempX, tempY; 

namespace Visual {

	// Отрисовка главного окна и его внутреннего содержимого
	void drawWindow();

	// Обновление статистики внутри окна
	void updateStatistics();

	// Отрисовка вершин графа (муравейника и пищи)
	void drawNode(double x, double y);

	// Отрисовка пути A(x1, y1) --> B(x2, y2)
	void drawPath();

	// Изменение толщины тропы из феромонов A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2); 

	// Ожидание события
	AppEvent waitForEvent();

	// Стереть граф, очистить статистику
	void clean();
}

#endif