
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

    // parse commandline arguments, make sure that filenames follow after specifier
    for (int i = 1; i < argc; i++) {

        string arg = argv[i];

        if (arg == "-s") {
            // check specifier and argument after
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                cerr << "error: Missing source filename after -s." << endl;
                return 1;
            }

            if (!sourceFile.empty()) {
                cerr << "error: Multiple source files specified." << endl;
                return 1;
            }

            // skip filename and move to next specifier for the next loop
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

    // check if correct specifiers were used
    if (sourceFile.empty()) {
        cerr << "error: No source file specified. Use -s filename." << endl;
        return 1;
    }

    if (targetFiles.empty()) {
        cerr << "error: No target files specified. Use -t filename." << endl;
        return 1;
    }

    // check whether source exists
    try {
        if (!fs::exists(sourceFile)) {
            cerr << "error: Source file does not exist: " << sourceFile << endl;
            return 1;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << "error checking source file: " << e.what() << endl;
        return 1;
    }

    // check whether any target already exists
    for (const string& target : targetFiles) {

        try {
            if (fs::exists(target)) {
                cerr << "error: Target file already exists: " << target << endl;
                return 1;
            }
        }
        catch (const fs::filesystem_error& e) {
            cerr << "error checking target file " << target << ": " << e.what() << endl;
            return 1;
        }
    }




    // open source file in binary mode
    ifstream source(sourceFile, ios::binary);

    if (!source.is_open()) {
        cerr << "error: Cannot open source file: " << sourceFile << endl;
        return 1;
    }

    // check that source is a regular file
    if (!fs::is_regular_file(sourceFile)) {
        cerr << "error: Source is not a regular file: " << sourceFile << endl;
        return 1;
    }





    // loop through every target and copy source into them
    for (const string& target : targetFiles) {

        // reset source before each copy
        source.clear();
        source.seekg(0, ios::beg);

        if (!source.good()) {
            cerr << "error: Could not read source file: " << sourceFile << endl;
            return 1;
        }

        // create target file in binary mode
        ofstream destination(target, ios::binary);

        if (!destination.is_open()) {
            cerr << "error: Cannot create target file: " << target << endl;
            return 1;
        }





        // copy file contents using a buffer
        char buffer[4096];

        while (source.read(buffer, sizeof(buffer)) || source.gcount() > 0) {
            destination.write(buffer, source.gcount());
        }

        // check for read errors
        if (!source.eof()) {
            cerr << "Error: Failed to read source file: " << sourceFile << endl;

            destination.close();
            return 1;
        }

        // check for write errors
        if (!destination.good()) {
            cerr << "Error: Failed to write target file: " << target << endl;

            destination.close();
            return 1;
        }

        destination.close();

        if (destination.fail()) {
            cerr << "error: Failed to close target file: " << target << endl;
            return 1;
        }
    }

    source.close();

    return 0;
}
