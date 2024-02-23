#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using JSON = nlohmann::json;

int dogFind(string mail) {
    int counter = 0;
    for (char c : mail) {
        if (c == '@') {
            counter++;
        }
    }
    return counter;
}

bool domainCheck(string mail) {
    bool isDomain = false;
    string domain = "";
    for (char c : mail) {
        if (isDomain == true) {
            domain = domain + c;
        }
        if (c == '@') {
            isDomain = true;
        }
    }
    int dotCount = 0;
    bool isDot = false;
    string afterDot = "";
    for (char d : domain) {
        if (isDot == true) {
            afterDot = afterDot + d;
        }
        if (d == '.') {
            if (dotCount == 0) {
                isDot = true;
            }
            dotCount++;
        }
    }
    if (dotCount != 1) {
        return false;
    }
    if (afterDot.size() == 1) {
        return false;
    }
    return true;
}

bool letterCheck(string mail) {
    if (mail[0] == '.' || mail[0] == '_' || mail[0] == '-') {
        return false;
    }
    if (mail.back() == '.' || mail.back() == '_' || mail.back() == '-') {
        return false;
    }
    for (char c : mail) {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)) {
            continue;
        } else if (c == '_' || c == '-' || c == '.' || c == '@') {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool check(string mail) {
    if (dogFind(mail) == 1) {
        if (letterCheck(mail) == true) {
            if (domainCheck(mail) == true) {
                cout << mail << endl;
            }
        }
    }
}

int main() {
    ifstream f("../mail.json");
    JSON data = JSON::parse(f);
    for (auto mail : data) {
        check(mail.get<string>());
    }
    return 0;
}