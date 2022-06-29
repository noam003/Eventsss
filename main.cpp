// Copyright 2022 Maximilian Dittgen, myd4@cornell.edu

#include <chrono>
#include <cstdint>
#include <gtkmm.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <thread>
#include <functional>
#include "event.h" // custom struct. has a sf::RectangleShape called eventbox, and two sf::Text called eventName and eventAddr
#include "UI_input.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;


int main(int argc, char* argv[]){
     XInitThreads();

	MyCalendar cal{"EVENTsss Calendar"};
	std::thread thread_obj(&MyCalendar::runCalendar, std::ref(cal));
	thread_obj.detach();
	
	  RefPtr<Application> application = Application::create();
	  Form form(cal);
	  return application->run(form);

	return 0;
}