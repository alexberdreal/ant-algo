#ifndef GENERAL
#define GENERAL
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>

constexpr double M_PI = 3.14159265358979323846;

inline std::mutex mut;

namespace core {
	template <class T, class R, class K>
	bool mapContainsKey(std::map<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	template <class T, class R, class K>
	bool mapContainsKey(std::multimap<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	// ������� ����� � �������� �� �(�1, �1) �� �(�2, �2)
	double findLength(double x1, double y1, double x2, double y2);

	struct Path {                                               // ���������, �������������� �����								
		double length;											// ����� ����� (� ��������)			
		double pheromone;										// ���������� �������� �� �����
	};

	// ~~~~~~~~~~~~~~~~~~ Node - �����, �������������� ���� ~~~~~~~~~~~~~~~~~~


	class Node {
	private:
		const unsigned id;											// ������������� ���� (id = 0, ���� ����������)
		const bool isHome;											// �������� �� ���� ������������
		const double x, y;											// ��������� ���� � ��������
	public:
		std::map<unsigned, Path> paths;									// paths[i] - ���� �� this � Node, id �������� ����� i. ���������������� ������ ������������
		
		Node();			// ����������� ��� �����������

		Node(double x, double y, unsigned id);			// ����������� ��� ����� ����

		void initPaths();

		bool operator==(const Node& toCompare);						// ������������� �������� ��������� == (���������� ���� �� id)

		unsigned getId() const;											// ������ id

		double getX() const { return x; }
		double getY() const { return y; }
	};

	inline std::vector<Node> nodes;									// inline ��� weak-internal ���������� (�����, ��� ������������																		Core.h ������������ ������� nodes)

	inline std::vector<std::vector<float>> routeVec;

	inline uint16_t numberOfAnts;

	enum class AppEvent
	{
		RESTART, LAUNCH, EXIT, DRAWNODE, FEED, CHOOSEANTS
	};

	struct AppState {
		bool toDrawField;
		bool isFieldTouchable;
		bool hasFeedBtn;
		std::string infoText;
		bool hasExecutionBtn;
		bool hasStopBtn;
		bool hasContinueBtn;
		bool hasTextField;
	};

	inline const AppState state_started{ true, false, true, "���� ��� ����������", false, false, false, false };
	inline AppState state_nodes{ false, true, false, "����������� ��� ��� ��������", false, false, true, false };
	inline AppState state_ants{ false, false, false, "������� ���������� ��������", false, false, true, true };
	inline AppState state_execution{ false, false, false, "", true, true, false, false };

	// �������, ������� ����� ������ � ����� ������� �������, ���������� ���� � ����� ��������� ������� �������
	class Ant {
	private:
		Node* curPos;								// ��������� �� ������� ����, ��� ��������� �������
		std::vector<uint16_t> nodeIds;					// ������� �������
	public:
		double entireLength;						// ���������� ����
		void updateCurrentPos(Node* position);		// �������� ������� ����, ��� ��������� �������
	};

}

#endif