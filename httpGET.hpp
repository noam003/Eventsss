// Copyright 2022 Maximilian Dittgen, myd4@cornell.edu

#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
using json = nlohmann::json;
using std::string;
using std::vector;

vector<int> getTime(int adj) {
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

string getTomorrow(){
        vector<int> currTime = getTime(86400);
        string month = std::to_string(currTime.at(1) + 1);
        if (month.length() == 1) month = "0" + month;
        string day = std::to_string(currTime.at(2));
        if (day.length() == 1) day = "0" + day;
        string year = std::to_string(currTime.at(0));
        string res = month + "/" + day + "/" + year;
        return res;
}


string removeQuotes(string s){
    if (s.at(0) == '\"'){
        s.erase(s.begin());
    }
    if (s.at(s.length() - 1) == '\"'){
        s.erase(s.end()-1);
    }
    return s;
}

string replaceSpaces(string s){
    for (int i = 0; i < s.length(); i++){
        if (s.at(i) == ' '){
            s.at(i) = '+';
        }
    }
    return s;
}


// take a vector of MM/DD/YYYY date, city, radius, cost, keyword; returns the events
// return a vector of strings: year, month, day, hour, min, duration, name, address
vector<vector<string>> getEvents(vector<string> req){
    vector<vector<string>> results{};

    // read in values from the vector
    string date = req.at(0);
    string city = replaceSpaces(req.at(1));
    string radius = req.at(2);
    string cost = req.at(3);
    string keyword = replaceSpaces(req.at(4));
    string month, day, year, start_date, end_date;
    month=day=year=start_date=end_date="";
    if (date == "-1"){
        date = getTomorrow();
    }
    if (date != "-1"){
        month = date.substr(0,2);
        day = date.substr(3,2);
        year = date.substr(6,4);
        start_date = year + "-" + month + "-" + day + "T00:00:00Z";
        end_date = year + "-" + month + "-" + day + "T23:59:59Z";
    }

    
    // build the api request
    string apiRequestUrl = "https://app.ticketmaster.com/discovery/v2/events.json?countryCode=US" +
        ((date != "-1") ? ("&startDateTime=" + start_date + "&endDateTime=" + end_date) : "") +
        ((city != "-1") ? ("&city={" + city + "}") : "") +
        ((radius != "-1") ? ("&radius=" + radius) : "") +
        ((keyword != "-1") ? ("&keyword=" + keyword) : "") +
        ((date != "-1") ? "&sort=relevance,desc" : "") +  // sort by date if no date provided
        "&apikey=aiNsqoCFarMdeGcZSpGSzAmaViG775KR";

    auto r = cpr::Get(cpr::Url{apiRequestUrl});
    json result = json::parse(r.text);

    json events;

    // see if anything is available
    try{
        result = result.at("_embedded");
        events = result.at("events");  
    }
    catch (...) {
        return results;
    }


    for (auto& elem : events){

        auto eventDates = elem["dates"];
        auto eventStart = eventDates["start"];


        // try to get the price
        // string eventPrice = "";
        // try{
        //     auto eventPrices = elem.at("priceRanges");
        //     auto firstEntry = eventPrices[0];
        //     eventPrice = "Starting at: $" + removeQuotes(firstEntry["min"].dump());
        // }
        // catch (...) {
        //     eventPrice = "Check online for Starting Price.";
        // }
        string address = "";
        auto embedded = elem["_embedded"];
        auto venues = embedded["venues"];
        auto firstEntry = venues[0];
        auto place = firstEntry["address"];
        address = removeQuotes(place["line1"].dump());
        auto eventCity = firstEntry["city"];
        address = address +  ", " + removeQuotes(eventCity["name"].dump());
        auto eventState = firstEntry["state"];
        address = address +  ", " + removeQuotes(eventState["stateCode"].dump());
        address = removeQuotes(firstEntry["name"].dump()) + ": " + address;



        string eventName = removeQuotes(elem["name"].dump());
        string eventDate = removeQuotes(eventStart["localDate"].dump());
        string eventTime = removeQuotes(eventStart["localTime"].dump());


        // push eveything into a vector
        vector<string> outputEvent{eventDate.substr(0,4), eventDate.substr(5,2), 
            eventDate.substr(8,2), eventTime.substr(0,2), eventTime.substr(3,2), "150",
            eventName, address};
        results.push_back(outputEvent);
    }
    return results;
}
