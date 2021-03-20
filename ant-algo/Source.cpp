#include "Algorithm.h"
#include <thread>

State state;

int main() {
	Visual::drawWindow();
	bool isLaunched = false;
	AppEvent ev;
	while (true) {
		ev = Visual::waitForEvent();
		switch (ev)
		{
		case AppEvent::DRAWNODE :
			Node node( tempX, tempY, false, (uint16_t)state.nodes.size());
			state.addNode(node);
			break;
		case AppEvent::CLEAR :
			Visual::clean();
			break;
		case AppEvent::LAUNCH :
			std::thread(Algo::start, NULL);
			break;
		case AppEvent::EXIT :
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
}