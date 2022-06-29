
![Logo](https://i.ibb.co/Rb8WNRD/Screen-Shot-2022-06-29-at-1-33-39-PM.png)


# EVENTsss Calendar 🐍📅

#### A C++ planner application to search for and manage exciting local events on an intuitive calendar ####
**Contents:**\
[Features](#features "Goto features")\
[Installation](#Installation "Goto installation")\
[Launching the Application](#Launching-the-application "Goto Launching-the-application")\
[Screenshots](#Screenshots "Goto screenshots")\
[Authors](#Authors "Goto authors")

## Features
EVENTsss Calendar deploys the [TicketMaster Discovery API](https://developer.ticketmaster.com/products-and-docs/apis/discovery-api/v2/) over a user-friendly interface to deliver the following features:
- Search for events by date, location, keyword, or cost
- Actively accept or decline event suggestions
- Add events to personal calendar
- Ability to add custom personal events
- Intuitive search page
- Arcade-style snake game if we can't find you an event!


## Installation

**Install EVENTsss Calendar with git:**

```sh
  git clone https://github.com/maxdittgen/EVENTsss-Calendar
  cd EVENTsss-Calendar
```
#### **EVENTsss Calendar also requires the following non-standard libraries to compile:** ####
- [SFML](https://www.sfml-dev.org)
- [GTKmm](https://www.gtkmm.org/en/download.html)
- [libcpr](https://github.com/libcpr/cpr)
- [nlohmann/json](https://github.com/nlohmann/json)

**Using CMake to install dependencies (Linux):**
1. Install CMake at https://cmake.org/install
2. Install SFML:
```sh
sudo apt-get install libsfml-dev
```
3. Install GTKmm
```sh
sudo apt-get install libgtkmm-3.0-dev
```
4. Install libcpr:
```sh
git clone https://github.com/libcpr/cpr
cd cpr
mkdir build && cd build
cmake ..
make
make install
```
5. Install nlohmann/json
```sh
git clone https://github.com/nlohmann/json
cd cpr
mkdir build && cd build
cmake ..
make
make install
```
## Lauching the Application

To run this project, simply launch the pre-compiled executable after installing the necessary libraries:

```sh
cd ~/EVENTsss-calendar
main
```

To modify our program, make whatever modifications you'd like, then compile using the included Makefile:
```sh
cd ~/EVENTsss-calendar
make main
main
```

## Screenshots

**Search for events and add them to your calendar straight from the app:**
![App Screenshot](https://i.ibb.co/f9N7f65/Screen-Shot-2022-06-29-at-1-48-42-PM.png)

**Can't find anything? No worries! Stay home and play Snake:**
![App Screenshot](https://i.ibb.co/QjxnvJT/Screen-Shot-2022-06-29-at-1-56-49-PM.png)

## Authors
- [@maxdittgen](https://www.github.com/maxdittgen) [myd4@cornell.edu]
- [@noam003](https://www.github.com/noam003) [noam@bu.edu]
- [@rashidk2001](https://www.github.com/rashidk2001) [rbrk@bu.edu]
- [@sumnerward](https://www.github.com/sumnerward) [swarden@bu.edu]



