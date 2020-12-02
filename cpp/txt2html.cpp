// On Linux, compile it with
// g++ -Wall -std=c++0x txt2html.cpp

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

static const char *configFile = "txt2html.txt";

class T2H
{
public:
    explicit T2H(const string &str) : m_pStr(&str){};

protected:
    const string *m_pStr;
    friend ostream &operator<<(ostream &os, const T2H &obj);
};

ostream &operator<<(ostream &os, const T2H &obj)
{
    string::const_iterator p;
    for (p = obj.m_pStr->begin(); p != obj.m_pStr->end(); ++p) {
        switch (*p) {
        case '<':
            os << "&lt;";
            break;
        case '>':
            os << "&gt;";
            break;
        default:
            os << *p;
            break;
        }
    }
    return os;
}

static int convert(ifstream &in, ofstream &out)
{
    string::size_type p;
    string line, cfgLine;
    string prefix, postfix;
    string tmp;
    ifstream cfg(configFile);
    if (!cfg.is_open()) {
        cerr << "Cannot open config file " << configFile << "." << endl;
        return -1;
    }
    int lineCount = 0;
    bool bEnd = false;
    for (;;) {
        getline(cfg, cfgLine);
        if (cfg.eof())
            break;
        if (cfgLine[0] == '@') {
            cfgLine = cfgLine.substr(1);
            p = cfgLine.find_first_of(':');
            if (p == string::npos) {
                cerr << "Error in config file " << configFile << "." << endl;
                return -1;
            }
            tmp = cfgLine.substr(0, p);
            cfgLine = cfgLine.substr(p + 1);
            if (tmp == "$") {
                bEnd = true;
            } else {
                lineCount = stoi(tmp);
            }
            p = cfgLine.find("...");
            if (p == string::npos) {
                cerr << "Error in config file " << configFile << "." << endl;
                return -1;
            }
            prefix = cfgLine.substr(0, p);
            postfix = cfgLine.substr(p + 3);
            if (lineCount == 0 && !bEnd) {
                out << prefix << T2H(line) << postfix << endl;
            } else {
                for (; bEnd || lineCount > 0;) {
                    getline(in, line);
                    if (in.eof())
                        break;
                    if (line[0] != '\0') {
                        lineCount--;
                        out << prefix << T2H(line) << postfix << endl;
                    }
                }
            }
        } else {
            out << cfgLine << endl;
        }
    }
    cfg.close();
    return 0;
}

int main(int argc, char *argv[])
{
    int r = -1;
    // Get input file name and output file name
    string ifn, ofn;
    if (argc < 2) {
        cout << "Input text file name:";
        getline(cin, ifn);
    } else {
        ifn = argv[1];
    }
    ofn = ifn + ".html";
    // Open input file and create output file
    ifstream in_file(ifn.c_str());
    if (in_file.is_open()) {
        ofstream out_file(ofn.c_str());
        if (out_file.is_open()) {
            r = convert(in_file, out_file);
            out_file.close();
        } else {
            cerr << "Cannot open file " << ofn << endl;
        }
        in_file.close();
    } else {
        cerr << "Cannot open file " << ifn << endl;
    }
    return r;
}
