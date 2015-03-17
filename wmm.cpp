#include "wmm.h"

using namespace std;

WMM::WMM()
{
    string line;
    string header;
    ifstream coeffFile;

    coeffFile.open("WMM.COF");
    if (coeffFile.is_open()) {
        getline(coeffFile, header);
        while (getline(coeffFile, line)) {
            if (line.substr(0,3) == "999") break;
            line.
        }
    }

}
