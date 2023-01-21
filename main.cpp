
// ---- Count Lines of Code in Python, and JavaScript Files ----
// by Brendan Murphy - b-murphy.ca

#include <iostream>
#include "vector"
#include "string"
#include "algorithm"
#include "fstream"


void count_lines(std::string file_path) {

    std::cout << "\n ---------------- count_lines -------------------------- \n";
    std::cout << "File Name/Path: " << file_path;

    int code_lines = 0;
    int not_code_lines = 0;
    int only_comments = 0;
    int blank_lines = 0;
    bool doc_switch = false;

    std::string js = ".js";

    std::vector<std::string> lines;   // won't have zero but not enough slots if [] left empty
    // problem solved, do not initiate with [], and = {} is not needed

    std::string file_path_rev = file_path;    // seems to make a copy
    std::reverse(file_path_rev.begin(), file_path_rev.end());   // reverse a string
    std::string sub = file_path_rev.substr(0, 3);   // sub is the last 3 characters of file path (reverse here)
    std::reverse(sub.begin(), sub.end());  // reverse sub back to forward order

    if (sub == js) {
        std::string comm_symbol = "//";
        std::string line;
        std::ifstream rfile;
        rfile.open(file_path);      // works on string or char file path
        if (rfile.is_open()) {
            while (std::getline(rfile, line)) {
                lines.push_back(line);
            }
            rfile.close();
        }

        for (auto i: lines) {
            i.erase(remove_if(i.begin(), i.end(), isspace), i.end());  //strip white space on ends
            auto k = i;

            // Handle doc strings as comments
            std::string sub2 = k.substr(0, 2);
            if (sub2 == "/*" or doc_switch) {
                not_code_lines += 1;
                if (!k.empty()) {        // can use k != '' but this is suggested
                    only_comments += 1;
                } else {
                    blank_lines += 1;
                }
                doc_switch = true;
                if (k.find("*/") != std::string::npos) {
                    doc_switch = false;
                }
                continue;
            }

            if (!k.empty()) {
                if (sub2 != comm_symbol) {
                    code_lines += 1;
                } else {
                    not_code_lines += 1;
                    only_comments += 1;
                }
            } else {
                not_code_lines += 1;
                blank_lines += 1;
            }
        }

    } else {
        std::string comm_symbol = "#";
        std::string line;
        std::ifstream rfile;
        rfile.open(file_path);      // works on string or char file path
        if (rfile.is_open()) {
            while (std::getline(rfile, line)) {
                lines.push_back(line);
            }
            rfile.close();
        }

        for (auto i: lines) {
            i.erase(remove_if(i.begin(), i.end(), isspace), i.end());  //strip white space on ends
            auto k = i;

            // Handle doc strings as comments
            // Turn off
            std::string sub2 = k.substr(0, 3);  // as in py k[:3]

            // Have to make a sub3 for py k[3:]
            std::string sub3;
            if (k.length() >= 3) {
                sub3 = k.substr(3, k.length() - 1);  // as in py k[3:]
            }

            if (k.find("'''") != std::string::npos and doc_switch or
                    k.find(R"(""")") != std::string::npos and doc_switch) {
                doc_switch = false;
                not_code_lines += 1;
                only_comments += 1;
                continue;
            }

            // Turn on
            if (sub2 == "'''" and !doc_switch or sub2 == R"(""")" and !doc_switch) {

                if (sub3.find("'''") != std::string::npos or sub3.find(R"(""")") != std::string::npos) {
                    not_code_lines += 1;
                    only_comments += 1;
                    continue;
                } else {
                    doc_switch = true;
                }
            }

            if (doc_switch) {
                not_code_lines += 1;
                if (!k.empty()) {
                    only_comments += 1;
                } else {
                    blank_lines += 1;
                }
            } else {
                if (!k.empty()) {
                    std::string k_first = k.substr(0, 1);
                    if (k_first != comm_symbol) {
                        code_lines += 1;
                    } else {
                        not_code_lines += 1;
                        only_comments += 1;
                    }
                } else {
                    not_code_lines += 1;
                    blank_lines += 1;
                }
            }
        }

    }

    std::cout << "\nLines of Code: " << code_lines;
    std::cout << "\nLines that are not code: " << not_code_lines;
    std::cout << "\nTotal Lines: " << lines.size();
    std::cout << "\n\nBlank Lines: " << blank_lines;
    std::cout << "\nLines that are just comments: " << only_comments;
    std::cout << "\n------------------------------------------";

}

int main() {

    count_lines("path_to_file");

    return 0;
}




