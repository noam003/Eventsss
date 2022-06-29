// Copyright 2022 Maximilian Dittgen, myd4@cornell.edu

#include <chrono>
#include <cstdint>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <functional>
#include "event.h" // custom struct. has a sf::RectangleShape called eventbox, and two sf::Text called eventName and eventAddr
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;





class MyCalendar{
private:
	sf::RenderWindow window;
	vector<Event> events{};
	string calendarName = "";

	static vector<int> getTime(int adj) {
	  vector<int> time{};
	  std::chrono::seconds sAdj{adj};  // create duration of adjustment

	  auto now = std::chrono::high_resolution_clock::now();
	  auto dur = now.time_since_epoch();
	  double timeSinceEpoch = dur.count() / 1000000000.0;
	  timeSinceEpoch += adj;
	  std::time_t adjDur = static_cast<time_t>(timeSinceEpoch);
	  std::tm adjTime = *std::localtime(&adjDur);
	  int year = adjTime.tm_year + 1900;
	  int mon = adjTime.tm_mon;
	  int day = adjTime.tm_mday;
	  int wday = adjTime.tm_wday;
	  int hour = adjTime.tm_hour;
	  int minute = adjTime.tm_min;
	  int second = adjTime.tm_sec;
	  time.push_back(year);
	  time.push_back(mon);
	  time.push_back(day);
	  time.push_back(wday);
	  time.push_back(hour);
	  time.push_back(minute);
	  time.push_back(second);
	  return time;
	}

// returns number of days a day is from today
	int daysAway(int month, int day, int year){
	    month -= 1;
	    year -= 1900;
	    struct std::tm target = {0, 0, 0, day, month, year};
	    time_t rawtime;
	    struct tm *info;
	    time( &rawtime );
	    info = localtime( &rawtime );
	    struct std::tm today = *info;
	    today.tm_hour=today.tm_min=today.tm_sec=0;
	    std::time_t x = std::mktime(&today);
	    std::time_t y = std::mktime(&target);
	    int difference = 0;
	    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
	    {
	        difference = std::difftime(y, x) / (60 * 60 * 24);
	    }
	    return difference;
	}

public:
	MyCalendar(string name):
	window(sf::VideoMode(900, 750), "Swag Calendar")
	{
		calendarName = name;
	}

	void createCalendar(sf::RenderWindow& window){
		// make grid
		// checker the calendar for clarity
		sf::RectangleShape horCheckerLine(sf::Vector2f(770,33.3));
		sf::Color lightGray(230,230,230);
		horCheckerLine.setFillColor(lightGray);
		for (double y = 130; y < 729; y += 66.666){
			horCheckerLine.setPosition(120, y);
			window.draw(horCheckerLine);
		}

		// make 8 vertical lines for the days
		sf::RectangleShape vertGridLine(sf::Vector2f(2, 600));
		sf::Color gray(190, 190, 190);
		vertGridLine.setFillColor(gray);
		for (int x = 120; x <=890; x += 110){
			vertGridLine.setPosition(x, 130);
			window.draw(vertGridLine);
		}

		// make 25 horizontal lines for the hours
		sf::RectangleShape horGridLine(sf::Vector2f(770, 2));
		horGridLine.setFillColor(gray);
		for (double y = 130; y <= 730; y+= 33.3){
			horGridLine.setPosition(120, y);
			window.draw(horGridLine);
		}
		// write the dates, starting with today
		vector<int> currTime{};
		currTime = getTime(0);  // return a year, month, day, wday, hour, minute, second vector
		vector<string> months{"January", "February", "March", "April",
	                          "May", "June", "July", "August", "September",
	                          "October", "November", "December"};
	    vector<string> days{"Sunday", "Monday", "Tuesday", "Wednesday",
	                        "Thursday", "Friday", "Saturday"};
		// print the month at the top of the page
	    sf::Text month;
	    sf::Font font;
	    font.loadFromFile("fonts/Ubuntu-B.ttf");
	    month.setFont(font);
	    string s = months.at(currTime.at(1));
	    month.setString(s);
	    month.setFillColor(sf::Color::Black);
	    month.setCharacterSize(24);
	    sf::FloatRect textRect = month.getLocalBounds();
		month.setOrigin(textRect.left + textRect.width/2.0f,
	               textRect.top  + textRect.height/2.0f);
		month.setPosition(sf::Vector2f(900/2.0f,750/10.0f));
	    window.draw(month);
	    // print the days
	    sf::Text temp;
	    temp.setFont(font);
	    temp.setCharacterSize(16);
	    for (int i = 0; i < 7; i++){
	    	currTime = getTime(i * 86400);
	    	if (i == 0){
	    		temp.setFillColor(sf::Color::Red);
	    	} else{
	    		temp.setFillColor(sf::Color::Black);
	    	}
	    	string s = days.at(currTime.at(3));
	    	temp.setString(s);
	    	textRect = temp.getLocalBounds();
			temp.setOrigin(textRect.left + textRect.width/2.0f,
	        textRect.top  + textRect.height/2.0f);
			temp.setPosition(sf::Vector2f(175 + i * 110,105.0f));
			window.draw(temp);  // draw the day names
			temp.setString(std::to_string(currTime.at(2)));
			textRect = temp.getLocalBounds();
			temp.setOrigin(textRect.left + textRect.width/2.0f,
	        textRect.top  + textRect.height/2.0f);
			temp.setPosition(sf::Vector2f(175 + i * 110,121.0f));
			window.draw(temp);  // draw the day numbers
	    }

	    // print the hours (6am - 12am)
	    temp.setCharacterSize(16);
	    for (int i = 0; i <= 18; i++){
	    	int hour = (i + 6) > 12 ? (i + 6 - 12) : (i + 6);
	    	string suffix = ((i + 6) >= 12 && (i + 6) % 24 != 0) ? " p.m." : " a.m.";
	        string s = std::to_string(hour) + suffix;
	        temp.setString(s);
	        textRect = temp.getLocalBounds();
	        temp.setOrigin(textRect.left + textRect.width/2.0f,
	        textRect.top  + textRect.height/2.0f);
	        temp.setPosition(sf::Vector2f(90.0f, 130 + i * 33.333));
	        window.draw(temp);
	    }
	}


		void createTitle(sf::RenderWindow& window, string s){
			sf::Text title;
			sf::Font font;
		    font.loadFromFile("fonts/Ubuntu-BI.ttf");
		    title.setFont(font);
		    title.setString(s);
		    title.setFillColor(sf::Color::White);
		    title.setOutlineColor(sf::Color::Black);
		    title.setOutlineThickness(3);
		    title.setCharacterSize(30);

		    sf::FloatRect textRect = title.getLocalBounds();
			title.setOrigin(textRect.left + textRect.width/2.0f,
		               textRect.top  + textRect.height/2.0f);
			title.setPosition(sf::Vector2f(900/2.0f,750/20.0f));

		    window.draw(title);
		}

		void resetCalendar(){
			events.clear();
		}

	void showCurrentTime(sf::RenderWindow& window){
	    vector<int> currTime = getTime(0);  // return a year, month, day, wday, hour, minute, second vector
	    int hour = currTime.at(4);
	    int min = currTime.at(5);
	    int sec = currTime.at(6);
	    int yPos = 0;
	    int xPos = 120;
	    if (hour < 6) {
	        yPos = 130;
	    } else{
	        int secTime = hour * 3600 + min * 60 + sec;
	        secTime -= 21600;  // calendar starts at 6am. subtract 6 hours from time
	        yPos = 130 + secTime / 108.0;
	    }

	    // create the bar
	    sf::RectangleShape nowBar(sf::Vector2f(112, 3));
	    nowBar.setFillColor(sf::Color::Red);
	    nowBar.setPosition(xPos, yPos);
	    window.draw(nowBar);

	    // create the text
	    string sHour = std::to_string((hour) > 12 ? (hour - 12) : (hour));
	    string sMin = min < 10 ? "0" + std::to_string(min) : std::to_string(min);
	    string sSec = sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec);
	    string suffix = ((hour) >= 12 && (hour) % 24 != 0) ? " p.m." : " a.m.";
	    string s = "Now: " + sHour + ":" + sMin + ":" + sSec + suffix;
	    sf::Text nowText;
	    sf::Font font;
	    font.loadFromFile("fonts/Ubuntu-B.ttf");
	    nowText.setFont(font);
	    nowText.setString(s);
	    nowText.setFillColor(sf::Color::Red);
	    nowText.setCharacterSize(11);
	    nowText.setPosition(xPos + 4, yPos + 3);
	    window.draw(nowText);
	}

	// returns today's date in MM/DD/YYYY format
	string getToday(){
		vector<int> currTime = getTime(0);
		string month = std::to_string(currTime.at(1) + 1);
		if (month.length() == 1) month = "0" + month;
		string day = std::to_string(currTime.at(2));
		if (day.length() == 1) day = "0" + day;
		string year = std::to_string(currTime.at(0));
		string res = month + "/" + day + "/" + year;
		return res;
	}

	// return vector of the xPos, yPos, width, and height of rectangle on calendar from start time and duration
	vector<int> timeToRect(int year, int month, int day, int hour, int min, int duration){  // duration is in minutes
	    int numDaysAway = daysAway(month, day, year);
	    if (numDaysAway > 6){
	        vector<int> res{-1};
	        return res;
	    }
	    int xPos = 122 + (numDaysAway * 110);
	    int width = 108;

	    int minTime = hour * 60 + min;
	    minTime -= 360;
	    int yPos = 130 + minTime / 1.8;
	    int height = duration / 1.8;
	    // cut the height of the rectangle at the bottom of the calendar
	    if (yPos + height > 730){
	        height = 730 - yPos;
	    }
	    vector<int> res{xPos, yPos, width, height};
	    return res;
	}

	// add event to the vector of events
	void addEvent(int year, int month, int day, int hour, int min, int duration, string name, string address){
	    vector<int> bounds = timeToRect(year, month, day, hour, min, duration);
	    int xPos = bounds.at(0);
	    int yPos = bounds.at(1);
	    int width = bounds.at(2);
	    int height = bounds.at(3);
	    
	    // debugging--delete
	    // cout << "event box debugging (xpos, ypos, width, height): " << endl;
	    // cout << xPos << endl;
	    // cout << yPos << endl;
	    // cout << width << endl;
	    // cout << height << endl;

	    // Make the box
	    sf::RectangleShape box(sf::Vector2f(width, height));
	    // choose random color
	    vector<sf::Color> colors{sf::Color::Red, sf::Color::Green, sf::Color::Yellow,
	        sf::Color::Magenta, sf::Color::Cyan};
	    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	    box.setFillColor(colors.at(std::rand() % 5));
	    // cout << std::rand() % 6 << endl;
	    box.setOutlineColor(sf::Color::Black);
	    box.setOutlineThickness(1);
	    box.setPosition(xPos, yPos);

	    // Make the title
	    sf::Font regular;
	    sf::Font bold;
	    regular.loadFromFile("fonts/Ubuntu-R.ttf");
	    bold.loadFromFile("fonts/Ubuntu-B.ttf");
	    sf::Text title;
	    title.setFont(bold);
	    title.setFillColor(sf::Color::Black);
	    title.setCharacterSize(10);
	    string s = "";
	    int titleLines = 1;
	    while (name.length() > 18){
	        // find space to place newline at
	        int spaceIndex = 0;
	        for (int i = 18; i > 0; i--){
	            if (name.at(i) == ' '){
	                spaceIndex = i;
	                break;
	            }
	        }
	        s = s + name.substr(0,spaceIndex + 1) + "\n";
	        name.erase(0,spaceIndex);
	        titleLines++;
	        if(titleLines = 3){
	        	name = "...";
	        	s.erase(s.end()-3,s.end());
	        }
	    }
	    s = s + name;
	    title.setString(s);
	    title.setPosition(xPos + 2, yPos + 2);

	    // Make the address
	    sf::Text subtitle;
	    subtitle.setFillColor(sf::Color::Black);
	    subtitle.setCharacterSize(10);
	    subtitle.setFont(regular);
	    s = "";
	    while (address.length() > 18){
	        // find space to place newline at
	        int spaceIndex = 0;
	        for (int i = 18; i > 0; i--){
	            if (address.at(i) == ' '){
	                spaceIndex = i;
	                break;
	            }
	        }
	        s = s + address.substr(0,spaceIndex + 1) + "\n";
	        address.erase(0,spaceIndex);
	    }
	    s = s + address;
	    subtitle.setString(s);
	    subtitle.setPosition(xPos + 2, yPos + 13);

	    // Make the event object
	    Event e;
	    e.eventBox = box;
	    e.eventName = title;
	    e.eventAddr = subtitle;
	    events.push_back(e);
	}

	// display events on calendar
	void displayEvents(vector<Event> events, sf::RenderWindow& window){
	    // text object doesn't store fonts, have to redeclare
	    sf::Font regular;
	    sf::Font bold;
	    regular.loadFromFile("fonts/Ubuntu-R.ttf");
	    bold.loadFromFile("fonts/Ubuntu-B.ttf");
	    for (auto e : events){
	        window.draw(e.eventBox);
	        e.eventName.setFont(bold);
	        window.draw(e.eventName);
	        e.eventAddr.setFont(regular);
	        window.draw(e.eventAddr);
	    }
	}

	void runCalendar() {
	    // add dummy events: addEvent(Event vector, year, month, day, hour, minute, duration, name, address)
	    window.setFramerateLimit(10);
	    while (window.isOpen())
	    {
	    	window.clear(sf::Color::White);
	    	createTitle(window, calendarName);
	    	createCalendar(window);
	        displayEvents(events, window);
	        showCurrentTime(window);
	        window.display();
	   	}
	    return;
	}
};