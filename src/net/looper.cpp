#include "looper.h"

namespace Vilin {

Looper::Looper() : quit(false), epoller(new Epoller()) {}
Looper::~Looper() {}
void Looper::start() {
	std::vector<std::shared_ptr<EventBase>> activeEventBaseList;

	while(!quit) {
		activeEventBaseList.clear();
		activeEventBaseList = epoller->poll();
		for(auto &it : activeEventBaseList) {
			it->HandleEvent();
		}
	}
}
void Looper::setQuit() {
	quit = true;
}

}