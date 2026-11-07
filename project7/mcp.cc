
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    string sourceFile;
    vector<string> targetFiles;
    set<string> uniqueTargets;

    // parse commandline arguments
    for (int i = 1; i < argc; i++) {

        string arg = argv[i];

        if (arg == "-s") {

            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                cerr << "error: Missing source filename after -s." << endl;
                return 1;
            }

            if (!sourceFile.empty()) {
                cerr << "error: Multiple source files specified." << endl;
                return 1;
            }

            // skip filename and move to next specifier
            sourceFile = argv[++i]; 

        }
        else if (arg == "-t") {

            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                cerr << "error: Missing target filename after -t." << endl;
                return 1;
            }

            string target = argv[++i];

            // check for duplicate target names
            if (!uniqueTargets.insert(target).second) {
                cerr << "error: Duplicate target filename: " << target << endl;
                return 1;
            }

            targetFiles.push_back(target);

        }
        else {
            cerr << "error: Invalid argument: " << arg << endl;
            return 1;
        }
    }



    return 0;
}
