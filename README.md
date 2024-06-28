# QT-Task-Scheduler
## Overview
The Task Scheduler Application is a Qt-based program designed to run in the background on a server (equipped with a desktop manager) and managed via a QSystemTrayIcon. It allows the user to periodically execute a series of tasks independent of each other with configurable periodicity. The application ensures that tasks are executed in a serialized and non-parallel manner.
## Features
* __System Tray Icon__: Manage the application through a system tray icon.
* __Periodic Task Execution__: Execute tasks at specified intervals (e.g., every 10 seconds, every 2 hours).
* __Independent Tasks__: Support for multiple independent tasks with different periodicities.
* __Serialized Execution__: Ensures that only one task executes at a time, postponing execution if another task is running.
* __Modular and Expandable__: Easily add new tasks and configure their periodicities.
## Requirements and Specifications
* __Operating System__: Windows
* __Qt Version__: 6.2.4 (with MinGW compiler)
* __No Qt Designer or QML__: The application is built using only QT C++ components
## Task Implemented
* __PrintTextTask__: Prints a chosen text to the debug output every 10 seconds.
* __FileCheckTask__: Checks for the existence of a specific file (e.g., "C:/EXAMPLE.txt") every 30 seconds and prints a notification if the file does not exist.
## Project Structure
- src
  - main.cpp
  - mainwindow.h
  - mainwindow.cpp
  - taskscheduler.h
  - taskscheduler.cpp
  - printtexttask.h
  - printtexttask.cpp
  - filechecktask.h
  - filechecktask.cpp
- resources
## Installation
## Usage
1. __System Tray Interaction__:
* The application runs in the background and can be accessed via the system tray icon.
* Right-click the system tray icon to view the currently scheduled tasks, add new tasks or exit the application.
2. __Viewing Tasks__:
* Select "View Tasks" from the system tray menu to see the list of currently scheduled tasks.
3. __Adding Tasks__:
* Select "Add Task" from the system tray menu to add a new task.
* Choose the task type (e.g., Print Text or Check File) and configure the necessary parameters.
## Code Documentation
The code is documented using Doxygen-style comments. You can generate the documentation using Doxygen to get a detailed view of the classes and methods.

