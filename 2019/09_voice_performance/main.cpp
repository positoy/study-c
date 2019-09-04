#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include "dist/json/json.h"

class VoicePerformance {
private:
    const std::string filepath = "voice_performance.json";
    Json::Value root;
    bool valid;

public:
    VoicePerformance() : valid{false} {
        readFile();
    }

    void readFile() {
        std::cout << "readFile" << std::endl;
        if (Json::Reader().parse(getFileContent(), root))
            valid = true;
    }

    void writeFile() {
        std::cout << "writeFile" << std::endl;
        std::fstream file(filepath, std::fstream::out);
        if (file.is_open()) {
            file << Json::FastWriter().write(root) << std::endl;
            file.close();
        } else {
            std::cout << "writeFile open failed" << std::endl;
        }
    }


    static VoicePerformance* getInstance() {
        static VoicePerformance instance;
        return &instance;
    }

    bool log(std::string key, unsigned long long timestamp) {
        if (!valid) return false;
        root[key] = timestamp;
        return true;
    }

    bool log(std::string key) {
        if (!valid) return false;
        root[key] = getCurrentTimestamp();
        return true;
    }

    bool logFile(std::string key) {
        readFile();
        if (!valid) return false;
        root[key] = getCurrentTimestamp();
        writeFile();
        return true;
    }

    bool logFile(std::string key, unsigned long long timestamp) {
        readFile();
        if (!valid) return false;
        root[key] = timestamp;
        writeFile();
        return true;
    }


    void printLog() {
        std::map<unsigned long long, std::string> checkpoints;
        // map
        for (Json::Value::const_iterator it=root.begin(); it!=root.end(); it++) {
            if ((*it).isNumeric() && it.key().isString()) {
                std::string v = it.key().asString();
                unsigned long long k = (*it).asUInt64();
                checkpoints[k] = v;
            }
        }

        // print
        std::map<unsigned long long, std::string>::iterator it=checkpoints.begin();
        std::string prevName = it->second;
        unsigned long long prevTimestamp = it->first;

        std::string printKey;
        unsigned long long printVal;
        for (++it; it!=checkpoints.end(); it++) {
            printKey = (prevName + " ~ " + it->second + " : ");
            printVal = it->first - prevTimestamp;

            std::cout << printKey << printVal << std::endl;

            prevName = it->second;
            prevTimestamp = it->first;
        }
    }
private:
    std::string getFileContent() {
        std::string all, line;
        std::fstream file(filepath, std::fstream::in);
        if (file.is_open()) {
            while (getline(file, line)) all += line;
            file.close();
        } else {
            std::cout << "readFile open failed" << std::endl;
        }
        if (all == "") all = "{}";
        return all;
    }

    unsigned long long getCurrentTimestamp() {
        time_t t = std::time(0);
        return t;
    }

private:
    VoicePerformance(VoicePerformance&) = delete;
    VoicePerformance& operator=(VoicePerformance&) = delete;
};

int main()
{
    VoicePerformance* v = VoicePerformance::getInstance();
    v->logFile("ASR");
    sleep(1);
    v->logFile("Trigger");
    sleep(1);
    v->logFile("Ready");
    sleep(1);
    v->logFile("Recording");
    sleep(1);
    v->logFile("example",1234);
    v->printLog();
}