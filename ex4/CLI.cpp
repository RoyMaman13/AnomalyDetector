#include "CLI.h"


CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    commands.push_back(new uploadCsvCommand(dio));
    commands.push_back(new algorithmSettings(dio));
    commands.push_back(new detectAnomalies(dio));
    commands.push_back(new displayResults(dio));
    commands.push_back(new uploadAnomaliesAnalyzeResults(dio));
    commands.push_back(new exitMenu(dio));
}

void CLI::start() {
    states states;
    int choice = 0;
    do {
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for (int i = 0; i < commands.size(); i++) {
            dio->write(to_string(i + 1));
            dio->write(".");
            dio->write(commands.at(i)->description);
            dio->write("\n");
        }
        choice = dio->read()[0] - '0';
        if (choice >= 1 && choice <= 6)
            commands.at(choice - 1)->execute(&states);
    } while (choice != 6);
}

CLI::~CLI() {
}

