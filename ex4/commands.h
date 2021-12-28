

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class states {
public:
    float threshold;

    states() : threshold(0.9) {}

    void setThreshold(float f) {
        this->threshold = f;
    }
};

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command {
protected:
    DefaultIO *dio;
public:
    string description;

    Command(DefaultIO *dio, string description) : dio(dio), description(description) {}

    virtual void execute(states *state) = 0;

    virtual ~Command() {}
};

// implement here your command classes
class uploadCsvCommand : public Command {
public:
    uploadCsvCommand(DefaultIO *dio) : Command(dio, "upload a time series csv file") {}

    virtual void execute(states *state) {
        dio->write("Please upload your local train CSV file.\n");
        ofstream trainOut("anomalyTrain.txt");
        string s = dio->read();
        while (s != "done") {
            if (trainOut.is_open())
                trainOut << s << endl;
            s = dio->read();
        }
        trainOut.close();
        dio->write("Upload complete.\n");

        dio->write("Please upload your local test CSV file.\n");
        ofstream textOut("anomalyText.txt");
        s = dio->read();
        while (s != "done") {
            if (textOut.is_open())
                textOut << s << endl;
            s = dio->read();
        }
        textOut.close();
        dio->write("Upload complete.\n");
    }
};

class algorithmSettings : public Command {
public:
    algorithmSettings(DefaultIO *dio) : Command(dio, "algorithm settings") {}

    virtual void execute(states *state) {
        float newThreshold;
        while (true) {
            dio->write("The current correlation threshold is ");
            dio->write(to_string(state->threshold));
            dio->write("\n");
            newThreshold = stof(dio->read());
            if (newThreshold >= 0 && newThreshold <= 1) {
                state->threshold = newThreshold;
                return;
            }
            dio->write("please choose a value between 0 and 1.\n");
        }
    }
};

class detectAnomalies : public Command {
public:
    detectAnomalies(DefaultIO *dio) : Command(dio, "detect anomalies") {}

    virtual void execute(states *state) {
        dio->write(description);
    }
};

class displayResults : public Command {
public:
    displayResults(DefaultIO *dio) : Command(dio, "display results") {}

    virtual void execute(states *state) {
        dio->write(description);
    }
};

class uploadAnomaliesAnalyzeResults : public Command {
public:
    uploadAnomaliesAnalyzeResults(DefaultIO *dio) : Command(dio, "upload anomalies and analyze results") {}

    virtual void execute(states *state) {
        dio->write(description);
    }
};

class exitMenu : public Command {
public:
    exitMenu(DefaultIO *dio) : Command(dio, "exit") {}

    virtual void execute(states *state) {
        dio->write(description);
    }
};


#endif /* COMMANDS_H_ */
