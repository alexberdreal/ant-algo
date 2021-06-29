#ifndef GENERAL
#define GENERAL
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <mutex>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Allocator.h"

constexpr double M_PI = 3.14159265358979323846;

inline std::atomic_int algoSpeed = 95;

namespace core {

	class Node; 

	inline std::vector<Node> nodes;

	inline std::vector<std::vector<float>> routeVec;		// ������� ���� �������

	inline uint16_t numberOfAnts;							// ����� ����� �������� � �������	

	inline stalloc::StackAllocatorNoRealloc alloc;


	// ~~~~~~~~~~~~~~~~~~ c��������, �������������� ����� ~~~~~~~~~~~~~~~~~~~~		

	struct Path {                                               // ���������, �������������� �����		
		constexpr Path() : length(0), pheromone(0) {}
		constexpr Path(float l, float p) : length(l), pheromone(p) {};
		float length;											// ����� ����� (� ��������)			
		float pheromone;										// ���������� �������� �� �����
	};

	// ~~~~~~~~~~~~~~~~~~ Node - �����, �������������� ���� ~~~~~~~~~~~~~~~~~~


	// ~~~~~~~~~~~~~~~~~~ �������� - ������ ���� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	struct BestPath {
		BestPath() = delete;
		static inline std::mutex mut;
		static inline std::vector<unsigned> route;
		static inline double len = 100000.0;
	};
	
	template <class T, class R, class K>
	bool mapContainsKey(const std::map<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	template <class T, class R, class K>
	bool mapContainsKey(const std::multimap<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	// ������� ����� � �������� �� �(�1, �1) �� �(�2, �2)
	float findLength(float x1, float y1, float x2, float y2);

	enum class AppEvent
	{
		RESTART, LAUNCH, EXIT, DRAWNODE, FEED, CHOOSEANTS
	};

	enum class AppState {
		state_started,
		state_nodes,
		state_ants,
		state_execution
	};

	class Node {
	private:
		const unsigned id;											// ������������� ���� (id = 0, ���� ����������)
		const bool isHome;											// �������� �� ���� ������������
		const float x, y;											// ��������� ���� � ��������
	public:
		std::map<unsigned, Path> paths;									// paths[i] - ���� �� this � Node, id �������� ����� i. ���������������� ������ ������������

		Node() : x(150), y(190), isHome(true), id(0) { }			// ����������� ��� �����������

		Node(float x, float y, unsigned id) : x(x), y(y), isHome(false), id(id) {}			// ����������� ��� ����� ����

		void initPaths() {
			unsigned i = 0;

			for (auto& el : nodes) {
				if (mapContainsKey(nodes[i].paths, el.getId())) {
					paths.insert(std::make_pair(i, nodes[i].paths[el.getId()]));
				}
				if (el.getId() != this->id) {
					paths.insert(std::make_pair(el.getId(), Path{ findLength(x, y, el.x, el.y), 0.2 }));
				}
			}
		}

		bool operator==(const Node& toCompare) {
			return id == toCompare.id;
		}						// ������������� �������� ��������� == (���������� ���� �� id)

		unsigned getId() const { return id; }											// ������ id

		float getX() const noexcept { return x; }
		float getY() const noexcept { return y; }
	};


}

#endif