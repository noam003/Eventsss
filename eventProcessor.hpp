// Copyright 2022 Maximilian Dittgen, myd4@cornell.edu

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using std::vector;
using std::string;

class OptionRunner {
private:
	vector<int> window_res = {900,255};
	sf::RenderWindow window;
	char accept = 'c';


public:
	OptionRunner(){

	}

	void homepage() {
		// Create a window
		window.create(sf::VideoMode(window_res.at(0),window_res.at(1)),"Potential event!");
		window.setFramerateLimit(5);			
	}

	void input_homepage (){
		sf::Event event;
		// closing window
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed){

				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Y){
					accept = 'y';
					window.close();
				}

				if (event.key.code == sf::Keyboard::N)
					accept = 'n';
					window.close();	
				
		}
	}
}

// returns 'y' for accept, 'n' for next event, 'c' to close
char run_homepage(vector<string> vec) {
			homepage();
			while (window.isOpen()){

				input_homepage();

			draw_homepage(vec);
		}
		return accept;
	}

	void draw_homepage(vector<string> vec) {
		window.clear(sf::Color::White);
		
		    sf::Font regular;
  			sf::Font bold;
  			regular.loadFromFile("fonts/Ubuntu-R.ttf");
    		bold.loadFromFile("fonts/Ubuntu-B.ttf");
		sf::Text home_title;
		home_title.setFont(bold);
 		home_title.setFillColor(sf::Color::Black);
  		home_title.setCharacterSize(25);
 	 	home_title.setPosition(25, 50);
 	 	home_title.setString("Event found: press \"y\" to add to calendar, \"n\" to see next event,\nor any other key to close");

 	 	sf::Text home_text;
 	 	home_text.setFont(regular);
 		home_text.setFillColor(sf::Color::Blue);
  		home_text.setCharacterSize(23);
 	 	home_text.setPosition(25, 120);
 	 	home_text.setString(vec.at(6).length() > 72 ? vec.at(6).substr(0,69) + "..." : vec.at(6));

 	 	sf::Text home_text_2;
 	 	home_text_2.setFont(regular);
 		home_text_2.setFillColor(sf::Color::Black);
  		home_text_2.setCharacterSize(15);
 	 	home_text_2.setPosition(25, 150);
 	 	home_text_2.setString("Location: " + vec.at(7));

 	 	sf::Text home_text_3;
 	 	home_text_3.setFont(regular);
 		home_text_3.setFillColor(sf::Color::Black);
  		home_text_3.setCharacterSize(15);
 	 	home_text_3.setPosition(25, 170);
 	 	home_text_3.setString("Date: " + vec.at(1) + "/" + vec.at(2) + "/" + vec.at(0));

 	 	sf::Text home_text_4;
 	 	home_text_4.setFont(regular);
 		home_text_4.setFillColor(sf::Color::Black);
  		home_text_4.setCharacterSize(15);
 	 	home_text_4.setPosition(25, 190);
 	 	home_text_4.setString("Time: " + vec.at(3) + ":" + vec.at(4));  	 	



 	 
 	 	window.draw(home_title);
 	    window.draw(home_text);
 	    window.draw(home_text_2);
 	    window.draw(home_text_3);
 	    window.draw(home_text_4);
		window.display();
	}
  
} ;
