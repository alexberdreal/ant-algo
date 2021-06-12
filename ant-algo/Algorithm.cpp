#include "Algorithm.h"

namespace Algo {

	// Поиск следующего пункта для муравья 
	core::Node* findNext(const Node& node, std::vector<unsigned>& eaten) noexcept {																			
		if (eaten.size() == nodes.size()) {																														// возвращаемся к муравейнику, если узлы кончились
			eaten.push_back(0);
			routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[0].getX(), (float)nodes[0].getY() });
			return &nodes[0];
		}
		double r = (rand() % 100) / 100.0;																														// генерируем рандомное число
		std::multimap<double, unsigned> m;																														// контейнер {вероятность: id узла}
		double sum = 0;																																			// тау * ню (знаменатель из формулы)

		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {																	
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {
				sum += pow(it->second.pheromone, 3) / it->second.length;																						// считаем знаменатель
			}
		}	
		double res = 0;																																		
		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {																				// если пища еще не съедена
				res = pow(it->second.pheromone, 3) / it->second.length / sum;																					// сычитаем вероятность перехода node --> it->second
				m.insert(std::make_pair(res, it->first));																										// добавляем эту вероятность в контейнер {вероятность: id узла}
			}
		}

		double t = 0;																																			
		for (auto& el : m) {																																	
			t += el.first;																																		// увеличиваем сумарную вероятность (0-1)
			if (r <= t) {																																		// |--t1--------t2----------r--t--------|, где t1, t2 = t на предыдущих итерациях
				eaten.push_back(el.second);																														// помечаем пищу как съеденную
				routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[el.second].getX(), (float)nodes[el.second].getY() });					// добавляем узлы в текущий маршрут (для визуализации)
				return &nodes[el.second];																														// возвращаем найденный узел
			}
		}
		return nullptr;																																			// если следующий пункт не найден - вернуть nullptr и обработать его снаружи ф-и
	};

	// Обновить феромон для некоторого пути
	void updatePheromone(const std::vector<unsigned>& route, bool extra = false) noexcept {																		// extra - флаг для элитного муравьев
		if (!extra) {
			double sum = 0;
			for (size_t i = 0; i < route.size() - 1; ++i) {
				sum += nodes[route[i]].paths[route[i + 1]].length;																								// ищем общую длину пути
				nodes[route[i]].paths[route[i + 1]].pheromone *= 0.6;																							// умножаем предыдущее кол-во феромона на коэф.испарения
			}
				std::cout << "Сумма: " << sum << std::endl;																										// Логи
				for (size_t i = 0; i < route.size() - 1; ++i) {																									
				nodes[route[i]].paths[route[i + 1]].pheromone += 40 / sum;																						// На каждом ребре графа добавляем феромон
			}
		}
		else {
			for (size_t i = 0; i < route.size() - 1; ++i) {
				nodes[route[i]].paths[route[i + 1]].pheromone += 0.4;																							// элитный муравей просто некоторое кол-во добавляет феромона
			}
		}

	};

	// Сбросить состояние алгоритма (для состояния core::AppState::state_started)
	void reset() {
		numberOfAnts = 0;																																		// Муравьев нет
		nodes.clear();																																			// Узлов нет
		routeVec.clear();																																		// Текущий маршрут сброшен
		algoSpeed.store(95);																																	// Скорость алгоритма дефолтная
		core::bestPath.len = 100000.0;																															// Кратчайшая длина отсутствует
		core::bestPath.route.clear();																															// Лучший путь отсутствует
	};

	// Запустить алгоритм
	void start() {
		std::vector<std::vector<unsigned>> routes;																												// Вектор из маршрутов отдельных муравьев
		std::vector<unsigned> vec;																																// Маршрут текущего муравья (из id)
		int c = 1;																																				// Текущая итерация
		while (true) {
			if (toTerminate.load()) return;																														// Если main поток требует завершения потока алгоритма - завершить поток
				Node* current;																																	// Текущий узел
			for (int i = 0; i < numberOfAnts; ++i) {																											// Для всех муравьев
				current = &nodes[0];																															// Начинаем с муравейника
				vec.push_back(0);																																// Добавим муравейник как отправную точку в маршрут
				while (vec.size() != nodes.size() + 1) {																										// Пока маршрут не будет равен кол-ву всех узлов плюс путь до муравейника в конце
					current = findNext(*current, vec);																											// Ищем куда побежит муравей
					std::this_thread::sleep_for(std::chrono::milliseconds(algoSpeed.load()));																	// Ставим задержку
					if (current == nullptr) throw std::runtime_error("The next node is not defined");															// Перехватываем ошибку из findNext
				}
				for (auto it = vec.begin(); it != vec.end(); ++it) {																							// Весь путь одного муравья
					std::cout << *it << ' ';																													// Логи
				}
				std::cout << std::endl;																									
				routes.push_back(vec);																															// Добавляем текущий маршрут во все маршруты
				vec.clear();																																	// Очищаем текущий маршрут (из id узлов для алгоритма)
				routeVec.clear();																																// Очищаем текущий маршрут (из координат узлов для визуализации) 
			}
			for (size_t i = 0; i < routes.size(); ++i) {																										
				Algo::updatePheromone(routes[i]);																												// Добавляем феромоны на каждый маршрут постфактум
			}
			double minL = 10000000.f;																															// Минимальная пройденная длинна муравьем
			int minR = 0;																																		// Номер муравья, пробежавшего кратчайший маршрут
			for (size_t i = 0; i < routes.size(); ++i) {
				double curs = 0;																																// Длина маршрута отдельного муравья
				for (size_t j = 0; j < routes[i].size() - 1; ++j) {																					
					curs += nodes[routes[i].at(j)].paths[routes[i].at(j + 1)].length;																		    // Считаем отдельную длину	
				}
				if (curs < minL) {																																// Обновляем кратчайший путь
					minL = curs;
					minR = i;
				}
			}

			core::bestPath.mut.lock();																															// Блокируем мьютекс лучшего пути для передачи данных main потоку
			std::cout << "Лучшая длина: " << minL << std::endl;																									// Логи
			if (core::bestPath.len > minL) {																													// Передаем данные main потоку через структуру с мьютексом
				core::bestPath.len = minL;
				core::bestPath.route = routes[minR];
			}
			core::bestPath.mut.unlock();																														// Разблокируем мьютекс
			Algo::updatePheromone(routes[minR], true);																											// Запустим элитного муравья на самый короткий маршрут

			routes.clear();																																		// Очистим маршруты всех муравьев
			std::cout << "////// Итерация " << c << std::endl;																									// Логи
			c++;																																				// Следующая итерация
			
		}
	};
}