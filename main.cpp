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
	// vector<string> vec{"-1", "Durham", "-1", "-1", "music"};
 //    vector<vector<string>> out = getEvents(vec);
 //    cout << out.at(0).at(7);


	MyCalendar cal{"Max's Calendar"};
	// cout << cal.getToday();
	std::thread thread_obj(&MyCalendar::runCalendar, std::ref(cal));
	thread_obj.detach();
	// cal.addEvent(2022, 6, 29, 16, 0, 180, "Test event 1", "880 Commonwealth Avenue, Boston, MA");
	// cal.addEvent(2022, 6, 30, 7, 30, 120, "Test event 2", "829 Beacon St");

	// string s;
	// cout << "enter a to add an event: ";
	// std::cin >> s;

	// cal.addEvent(2022, 7, 2, 12, 0, 210, "Test event 3", "1010 Massachussetts Avenue, Boston, MA, 02215");
	
	  RefPtr<Application> application = Application::create();
	  Form form(cal);
	  return application->run(form);


	// cout << "enter q to quit: ";
	// s = "";
	// std::cin >> s;




	return 0;
}