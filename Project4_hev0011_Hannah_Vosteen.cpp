/*
 * Project 4
 * Author: Hannah Vosteen
 * Username: hev0011
 * Filename: project4.cpp
 * Compilation: g++ -o project4 project4.cpp
 * Execution: ./project4
 * 
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;


//tests to see if the numbers are valid
bool isValidNum(const string& str) {
    if (str.empty())
        return false;
    bool hasDecimal = false;
    bool hasDigit = false;
    int start = 0;
    if (str[0] == '-' || str[0] == '+') {
        start = 1;
    }

    for (int i = start; i < str.length(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            hasDigit = true;
        }
        else if (c == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        }
        else {
            return false;
        }
    }
    return hasDigit;
}


//reads the file that the use inputs
bool readFile(const string& filename, vector<double>& values) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    vector<double> tempVal;
    bool isEmpty = true;
    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty()) continue;
        isEmpty = false;
        if (!isValidNum(line)) {
            file.close();
            return false;
        }
        try {
            double value = stod(line);
            tempVal.push_back(value);
        }
        catch (...) {
            file.close();
            return false;
        }
    }
    file.close();

    if (isEmpty || tempVal.empty()) {
        return false;
    }
    values = tempVal;
    return true;
}

//registers number of files user inputs
int getNumOfFiles() {
    int numFiles;
    while (true) {
        cout << "Enter the number of files to read: ";
        cin >> numFiles;
        if (cin.fail() || numFiles <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        else {
            cin.ignore();
            return numFiles;
        }
    }
}

//gets file from device
string getValidFilename(int fileNum) {
    string filename;
    vector<double> values;
    while (true) {
        cout << "Enter the filename for file " << fileNum << ": ";
        getline(cin, filename);
        if (readFile(filename, values)) {
            cout << "The list of " << values.size() << " values in file " << filename << " is: " << endl;
            for (double value : values) {
                cout << fixed << setprecision(4) << value << endl;
            }
            return filename;
        }
        else {
            cout << "Not an input file. Illegal content/structure detected. Please try again. " << endl;
        }
    }
}

// mean
double calculateMean(const vector<double>& values) {
    double sum = 0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

//median
double calculateMedian(vector<double> values) {
    sort(values.begin(), values.end());
    int n = values.size();
    if (n % 2 == 0) {
        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    }
    else {
        return values[n / 2];
    }
}

//mode
double calculateMode(const vector<double>& values) {
    map<double, int> frequency;
    for (double value : values) {
        frequency[value]++;
    }
    int maxFreq = 0;
    for (const auto& pair : frequency) {
        maxFreq = max(maxFreq, pair.second);
    }
    vector<double> modes;
    for (const auto& pair : frequency) {
        if (pair.second == maxFreq) {
            modes.push_back(pair.first);
        }
    }
    double sum = 0;
    for (double mode : modes) {
        sum += mode;
    }
    return sum / modes.size();
}

string getValidOutputFilename() {
    string filename;
    while (true) {
        cout << "Enter the output filename to save: ";
        getline(cin, filename);
        ofstream testFile(filename);
        if (testFile.is_open()) {
            testFile.close();
            return filename;
        }
        else {
            cout << "Cannot write to file. Please try again." << endl;
        }
    }
}

bool writeToCSV(const string& filename, const vector<double>& sortedValues, double mean, double median, double mode) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    for (int i = 0; i < sortedValues.size(); i++) {
        if (i > 0) file << ", ";
        file << fixed << setprecision(4) << sortedValues[i];
    }
    file << endl;

    file << "mean, " << fixed << setprecision(4) << mean << endl;
    file << "median, " << fixed << setprecision(4) << median << endl;
    file << "mode, " << fixed << setprecision(4) << mode << endl;
    file.close();
    return true;
}

//this is my main function
int main() {
    cout << "*** Welcome to Hannah's Data Analyzer ***" << endl;
    int numFiles = getNumOfFiles();
    vector<double> allValues;
    for (int i = 1; i <= numFiles; i++) {
        string filename = getValidFilename(i);
        vector<double> fileValues;
        readFile(filename, fileValues);
        allValues.insert(allValues.end(), fileValues.begin(), fileValues.end());
    }
    vector<double> sortedValues = allValues;
    sort(sortedValues.begin(), sortedValues.end());

    double mean = calculateMean(allValues);
    double median = calculateMedian(allValues);
    double mode = calculateMode(allValues);
    cout << "*** Summarized Statistics ***" << endl;
    cout << "The orderly sorted list of " << sortedValues.size() << " values is: " << endl;

    for (int i = 0; i < sortedValues.size(); i++) {
        if (i > 0) cout << " ";
        cout << fixed << setprecision(4) << sortedValues[i];
    }
    cout << endl;

    cout << "The mean is " << fixed << setprecision(4) << mean << endl;
    cout << "The median is " << fixed << setprecision(4) << median << endl;
    cout << "The mode is " << fixed << setprecision(4) << mode << endl;


    // for project 4
    string outputFilename = getValidOutputFilename();
    if (writeToCSV(outputFilename, sortedValues, mean, median, mode)) {
        cout << "*** File " << outputFilename << " has been written to disk ***" << endl;
    }
    else {
        cout << "Error writing to file" << endl;
    }
    cout << "*** Goodbye ***" << endl;
    return 0;
}
