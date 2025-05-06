/**
 * @file main.cpp
 * @brief Main entry point for the 2D Graphics Modeler application.
 * @details Initializes the QApplication and the AppDriver, then starts the application event loop.
 */

#include "../backend/AppDriver.h"
#include <QApplication> // It's good practice to include QApplication directly in main.cpp

/**
 * @brief The main function of the application.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status of the application.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Initialize the Qt application environment
    AppDriver driver;             // Create the main application driver instance

    driver.run();                 // Initialize and run the application logic
    return app.exec();            // Start the Qt event loop
}
