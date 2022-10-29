#include <iostream>
#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <tuple>
#include <fcntl.h>

namespace po = boost::program_options;
namespace fs = std::filesystem;
using namespace std;

std::vector<std::string> PATH;

std::string look_for_file(std::string file)
{
    bool found = false;
    std::string program;
    for (const auto& path : PATH)
        for (const auto & entry : fs::directory_iterator(path))
            if ((!found) && (fs::path(entry.path()).filename() == file)) {
                found = true;
                program = entry.path();
            }
    if (found) {
        return program;
    }
    return "";
}

 string extract_command(string input) {
    vector<string> args = po::split_unix(input); // split the string
    string command = args[0].substr(args[0].find_first_not_of(" \n\r\t\f\v"));
    return command;
}

int execute(string args) {
    
}

int main() {
    //this program tries to execute echo ../src | ls | grep .cpp
    //we fork exactly twice, create  processes that pass the output of their executino between each other
    vector<string> args = {"echo ../src", "ls", "grep .cpp"};
    string last_output = "";

    int pipefd[2];
    int pipefdtemp[2];

    for (int i = 0; i < args.size(); i++) {
        cerr << "last output " << last_output << endl;
        if ((i > 0) && \
        ((extract_command(args[i]) == "grep") || extract_command(args[i]) =="wc")) {
            if (pipe(pipefdtemp) < 0) {
                cerr << "failed to pipe" << endl;
                return -1;
            }
        }
        if (pipe(pipefd) < 0) {
            cerr << "failed to pipe" << endl;
            return -1;
        }
        cerr << "working on " << args[i] << endl;
        pid_t pid = fork();
        if (pid < 0) {
            cerr << "failed to fork" << endl;
            return -1;
        }
        else if (pid == 0) {
            
            if ((i > 0) && \
            ((extract_command(args[i]) == "grep") || extract_command(args[i]) =="wc")) {
                close(pipefdtemp[1]);
                dup2(pipefdtemp[0], STDIN_FILENO);
            } else if ((i > 0) && (i < args.size()-1)) {
                args[i] += " "+last_output;
            }
            cerr << "executing " << args[i] << endl;

            dup2(pipefd[1], STDOUT_FILENO);
            vector<string> argv = po::split_unix(args[i]);
            char* arg1[argv.size()+1];
            for (int j = 0; j < argv.size(); j++)
                arg1[j] = (char*)argv[j].c_str();
            arg1[argv.size()] = NULL;
            exit(execvp(arg1[0], arg1));
        } else {
            if ((i > 0) && (extract_command(args[i]) == "grep")) {
                cerr << "special case: grep, writing to its stdin" << endl;
                close(pipefdtemp[0]);
                write(pipefdtemp[1], last_output.c_str(), last_output.size());
                close(pipefdtemp[1]);
            }
            int status;
            waitpid(pid, &status, 0);

            close(pipefd[1]);
            cerr << "reading..." << endl;
            char inbuf[256];
            int nbytes = read(pipefd[0], inbuf, 256);
            string data(inbuf, nbytes-1);
            last_output = data;
            close(pipefd[0]);
        }
    }
    cout << last_output << endl;
    return 0;
}



