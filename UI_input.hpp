#include <gtkmm.h>
#include <iostream>
#include "httpGET.hpp"
#include <vector>
#include <string>
#include "calendar.hpp"
#include "eventProcessor.hpp"
#include <chrono>
#include <cstdint>
#include <ctime>
#include <map>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "snake.hpp"
#include "event.h" // custom struct. has a sf::RectangleShape called eventbox, and two sf::Text called eventName and eventAddr
using std::cout;
using std::endl;
using std::map;

using namespace Glib;
using namespace Gtk;
using std::vector;
using std::string;

class Form : public Gtk::Window {
public:
  Form(MyCalendar &cal) {
    cal;
    add(scrolledWindow);
    scrolledWindow.add(fixed);
    //------------------------------------------in box 1------------
    groupBox1.set_label("Search for Events");
    fixed.add(groupBox1);
    fixed.move(groupBox1, 30, 30);
    groupBox1.set_size_request(350, 400);

    textBox1.set_text("Date");
    fixed.add(textBox1);
    fixed.move(textBox1, 90, 90);

    textBox1.signal_button_release_event().connect([&](GdkEventButton*) {
      textBox1.set_text("");
      return true;
    });

    format1.set_text("Enter Date in mm/dd/year");
    fixed.add(format1);
    fixed.move(format1, 95, 120);

    ok1.set_label("ok");
    ok1.signal_button_release_event().connect([&](GdkEventButton*) {
      search_info.at(0) = textBox1.get_text();

      if (search_info.at(0) == "")
      textBox1.set_text("Date");

      if (search_info.at(0) == "Date")
        search_info.at(0) = "-1";
      return true;
    });
    fixed.add(ok1);
    fixed.move(ok1, 310, 90);

    textBox3.set_text("City"); 
    fixed.add(textBox3);
    fixed.move(textBox3, 90, 140); ////////////////

    textBox3.signal_button_release_event().connect([&](GdkEventButton*) {
      textBox3.set_text("");
      return true;
    });

    ok3.set_label("ok");
    ok3.signal_button_release_event().connect([&](GdkEventButton*) {
        search_info.at(1) = textBox3.get_text();

        if (search_info.at(1) == "")
          textBox3.set_text("City");

        if (search_info.at(1) == "City")
          search_info.at(1) = "-1";
        return true;
    });

    fixed.add(ok3);
    fixed.move(ok3, 310, 140);

    textBox4.set_text("Radius");
    fixed.add(textBox4);
    fixed.move(textBox4, 90, 190);

    textBox4.signal_button_release_event().connect([&](GdkEventButton*) {
      textBox4.set_text("");
      return true;
    });

    ok4.set_label("ok");
    ok4.signal_button_release_event().connect([&](GdkEventButton*) {
      search_info.at(2) = textBox4.get_text();

      if (search_info.at(2) == "")
        textBox4.set_text("Radius");

      if (search_info.at(2) == "Radius")
        search_info.at(2) = "-1";

      return true;
    });
    fixed.add(ok4);
    fixed.move(ok4, 310, 190);

    textBox5.set_text("Cost");
    fixed.add(textBox5);
    fixed.move(textBox5, 90, 240);

    textBox5.signal_button_release_event().connect([&](GdkEventButton*) {
      textBox5.set_text("");
      return true;
    });

    ok5.set_label("ok");
    ok5.signal_button_release_event().connect([&](GdkEventButton*) {
      search_info.at(3) = textBox5.get_text();

      if (search_info.at(3) == "")
        textBox5.set_text("Cost");

      if (search_info.at(3) == "Cost")
        search_info.at(3) = "-1";
      return true;
    });
    fixed.add(ok5);
    fixed.move(ok5, 310, 240);

    textBox6.set_text("Keyword");
    fixed.add(textBox6);
    fixed.move(textBox6, 90, 290);

    textBox6.signal_button_release_event().connect([&](GdkEventButton*) {
      textBox6.set_text("");
      return true;
    });

    ok6.set_label("ok");
    ok6.signal_button_release_event().connect([&](GdkEventButton*) {
      search_info.at(4) = textBox6.get_text();

      if (search_info.at(4) == "")
        textBox6.set_text("Keyword");

      if (search_info.at(4) == "Keyword")
        search_info.at(4) = "-1";

      return true;
    });
    fixed.add(ok6);
    fixed.move(ok6, 310, 290);

    //---------------------------------------- in box 2-----------
    groupBox2.set_label("Enter your own Events");
    fixed.add(groupBox2);
    fixed.move(groupBox2, 450, 30);
    groupBox2.set_size_request(350, 400);

    mytextBox1.set_text("Event Name");
    fixed.add(mytextBox1);
    fixed.move(mytextBox1, 510, 90);

    mytextBox1.signal_button_release_event().connect([&](GdkEventButton*) {
      mytextBox1.set_text("");
      return true;
    });

    myok1.set_label("ok");
    myok1.signal_button_release_event().connect([&](GdkEventButton*) {
      my_info.at(0) = mytextBox1.get_text();

      if (my_info.at(0) == "")
        mytextBox1.set_text("Event Name");

      if (my_info.at(0) == "Event Name")
        my_info.at(0) = "-1";

      return true; 
    });
    fixed.add(myok1);
    fixed.move(myok1, 710, 90);//---------------------------

    mytextBox2.set_text("Date"); 
    fixed.add(mytextBox2);
    fixed.move(mytextBox2, 510, 140);

    mytextBox2.signal_button_release_event().connect([&](GdkEventButton*) {
      mytextBox2.set_text("");
      return true;
    });

    dateformat.set_text("Enter Date in mm/dd/year");
    fixed.add(dateformat);
    fixed.move(dateformat, 510, 170);

    myok2.set_label("ok");
    myok2.signal_button_release_event().connect([&](GdkEventButton*) {
      my_info.at(1) = mytextBox2.get_text();

      if (my_info.at(1) == "")
        mytextBox2.set_text("Date");

      if (my_info.at(1) == "Date")
        my_info.at(1) = "-1";

      return true;
    });
    fixed.add(myok2);
    fixed.move(myok2, 710, 140);

    mytextBox3.set_text("Location");
    fixed.add(mytextBox3);
    fixed.move(mytextBox3, 510, 190);

    mytextBox3.signal_button_release_event().connect([&](GdkEventButton*) {
      mytextBox3.set_text("");
      return true;
    });

    myok3.set_label("ok");
    myok3.signal_button_release_event().connect([&](GdkEventButton*) {
          my_info.at(2) = mytextBox3.get_text();

          if (my_info.at(2) == "")
            mytextBox3.set_text("Location");

          if (my_info.at(2) == "Location")
            my_info.at(2) = "-1";
          
          return true;
    });

    fixed.add(myok3);
    fixed.move(myok3, 710, 190);

    mytextBox4.set_text("Start Time");
    fixed.add(mytextBox4);
    fixed.move(mytextBox4, 510, 240);

    mytextBox4.signal_button_release_event().connect([&](GdkEventButton*) {
      mytextBox4.set_text("");
      return true;
    });

    start_timeformat.set_text("Enter in 24hr format");
    fixed.add(start_timeformat);
    fixed.move(start_timeformat, 510, 270);

    myok4.set_label("ok");
    myok4.signal_button_release_event().connect([&](GdkEventButton*) {
      my_info.at(3) = mytextBox4.get_text();

      if (my_info.at(3) == "")
        mytextBox4.set_text("Start Time");

      if (my_info.at(3) == "Start Time")
        my_info.at(3) = "-1";

      return true;
    });
    fixed.add(myok4);
    fixed.move(myok4, 710, 240);

    mytextBox5.set_text("Duration");
    fixed.add(mytextBox5);
    fixed.move(mytextBox5, 510, 290);

    mytextBox5.signal_button_release_event().connect([&](GdkEventButton*) {
      mytextBox5.set_text("");
      return true;
    });

    durationformat.set_text("Enter in minutes");
    fixed.add(durationformat);
    fixed.move(durationformat, 510, 320);

    myok5.set_label("ok");
    myok5.signal_button_release_event().connect([&](GdkEventButton*) {
      my_info.at(4) = mytextBox5.get_text();

      if (my_info.at(4) == "")
        mytextBox6.set_text("Duration");

      if (my_info.at(4) == "Duration")
        my_info.at(4) = "-1";
      return true;
    });
    fixed.add(myok5);
    fixed.move(myok5, 710, 290);


    // -close and submit buttons
    mybutton.set_label("Close");
    mybutton.signal_button_release_event().connect([&](GdkEventButton* event) {
      close();
      return true;
    });
    fixed.add(mybutton);
    fixed.move(mybutton, 375, 455);

    mysubmit.set_label("Submit Event");
    mysubmit.signal_button_release_event().connect([&](GdkEventButton* event) {
      my_info.at(0) = mytextBox1.get_text();
      my_info.at(1) = mytextBox2.get_text();
      my_info.at(2) = mytextBox3.get_text();
      my_info.at(3) = mytextBox4.get_text();
      my_info.at(4) = mytextBox5.get_text();
      plotCustomEvent(cal);
      return true;
    });
    fixed.add(mysubmit);
    fixed.move(mysubmit, 510, 360);

    apisubmit.set_label("Submit Search");
    apisubmit.signal_button_release_event().connect([&](GdkEventButton* event) {
      search_info.at(0) = (textBox1.get_text() == "Date") ? "-1" : textBox1.get_text();
      search_info.at(1) = (textBox3.get_text() == "City") ? "-1" : textBox3.get_text();
      search_info.at(2) = (textBox4.get_text() == "Radius") ? "-1" : textBox4.get_text();
      search_info.at(3) = (textBox5.get_text() == "Cost") ? "-1" : textBox5.get_text();
      search_info.at(4) = (textBox6.get_text() == "Keyword") ? "-1" : textBox6.get_text();
      plotAPIEvent(cal);
      return true;
    });
    fixed.add(apisubmit);
    fixed.move(apisubmit, 95, 360);

    playgame.set_label("Play a Game");
    playgame.signal_button_release_event().connect([&](GdkEventButton* event) {
        std::thread thread_obj(&Form::launchSnakeGame, this);
        thread_obj.detach();
      return true;
    });
    fixed.add(playgame);
    fixed.move(playgame, 500, 455);

    reset.set_label("Reset Calendar");
    reset.signal_button_release_event().connect([&](GdkEventButton* event) {
        cal.resetCalendar();
      return true;
    });
    fixed.add(reset);
    fixed.move(reset, 200, 455);

    //-------------------------------------------------
    
    set_title("Event Space");
    resize(850, 500);
    show_all();
  }

  void plotCustomEvent(MyCalendar &cal){
    string name = (my_info.at(0) != "-1") ? my_info.at(0) : "Custom Event";
    string date = (my_info.at(1) != "-1") ? my_info.at(1) : cal.getToday();
    string address = (my_info.at(2) != "-1") ? my_info.at(2) : "";
    string startTime = (my_info.at(3) != "-1") ? my_info.at(3) : "12:00";
    string duration = (my_info.at(4) != "-1") ? my_info.at(4) : "120";

    int year = std::stoi(date.substr(6,4));
    int month = std::stoi(date.substr(0,2));
    int day = std::stoi(date.substr(3,2));
    int hour = std::stoi(startTime.substr(0,2));
    int minute = std::stoi(date.substr(3,2));
    int intDuration = std::stoi(duration);

    cal.addEvent(year, month, day, hour, minute, intDuration, name, address);
    my_info.at(0)=my_info.at(1)=my_info.at(2)=my_info.at(3)=my_info.at(4)="-1";
  }

  void plotAPIEvent(MyCalendar &cal){
    string date = search_info.at(0);
    string city = search_info.at(1);
    string radius = search_info.at(2);
    string cost = search_info.at(3);
    string keyword = search_info.at(4);
    // string date = "07/03/2022";
    // string city = "Boston";
    // string radius = "-1";
    // string cost = "-1";
    // string keyword = "-1";

    vector<string> reqVec{date, city, radius, cost, keyword};
    vector<vector<string>> resVec = getEvents(reqVec);
    if (resVec.size() <= 0){
      std::thread thread_obj(&Form::launchSnakeGame, this);
      thread_obj.detach();
      return;
    }

    //later on you can give options
    int count = 0;
    vector<string> vec = resVec.at(count);
    bool proceed = false;
    while (!proceed){
    try{

        // see if all of the vector is filled;
        std::stoi(vec.at(0));
        std::stoi(vec.at(1));
        std::stoi(vec.at(2));
        std::stoi(vec.at(3));
        std::stoi(vec.at(4));
        std::stoi(vec.at(5));
        vec.at(6);
        vec.at(7);

        // pass into the eventProcessor
        OptionRunner o;
        char wanted = o.run_homepage(vec);
        if (wanted == 'y'){
              cal.addEvent(std::stoi(vec.at(0)),std::stoi(vec.at(1)),std::stoi(vec.at(2)),
      std::stoi(vec.at(3)),std::stoi(vec.at(4)),std::stoi(vec.at(5))
      ,vec.at(6),vec.at(7));
        }
      proceed = true;
      if (wanted == 'n'){
        proceed = false;
        if (count != resVec.size() - 1){
        count++;
        vec = resVec.at(count);
         } else{
          std::thread thread_obj(&Form::launchSnakeGame, this);
          thread_obj.detach();
        return;
       }
      }
    }
    catch(...){
      if (count != resVec.size() - 1){
        count++;
        vec = resVec.at(count);
      } else{
      std::thread thread_obj(&Form::launchSnakeGame, this);
      thread_obj.detach();
      return;
      }
    }
    }


    
    search_info.at(0)=search_info.at(1)=search_info.at(2)=search_info.at(3)=search_info.at(4)="-1";
  }

  void launchSnakeGame(){
    Engine engine;
    engine.run_homepage();
  }
  
private:
  Fixed fixed;
  ScrolledWindow scrolledWindow;
  Frame groupBox1;
  Frame groupBox2;

  Entry textBox1;
  Entry textBox3;
  Entry textBox4;
  Entry textBox5;
  Entry textBox6;
  Button button;
  // Button mysubmit;
  Button apisubmit;
  Button playgame;
  Button reset;
  Button ok1;
  Button ok2;
  Button ok3;
  Button ok4;
  Button ok5;
  Button ok6;

  vector<string> search_info = {"-1", "-1",
   "-1", "-1","-1"};

  Entry mytextBox1;
  Entry mytextBox2;
  Entry mytextBox3;
  Entry mytextBox4;
  Entry mytextBox5;
  Entry mytextBox6;
  Button mybutton;
  Button mysubmit;
  // Button apisubmit;
  Button myok1;
  Button myok2;
  Button myok3;
  Button myok4;
  Button myok5;
  Button myok6;

  vector<string> my_info = {"-1", "-1", "-1",
   "-1", "-1"}; 

   Label format1; // Date format
   Label dateformat;
   Label start_timeformat;
   Label durationformat;
};
