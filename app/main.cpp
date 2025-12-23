#include <cmath>
#include <iostream>
#include <string>
#include "Logger.h"
#include "Project1.cpp"
#include "Project2.cpp"

void run_project1_exercise(const int exercise) {
    switch (exercise) {
        case 1: exercise1p1(); break;
        case 2: exercise2p1(); break;
        case 3: exercise3p1(); break;
        case 5: exercise5p1(); break;
        case 6: exercise6p1(); break;
        case 9: exercise9p1(); break;
        default:
            Logger::instance().log("Exercise %d not found in Project 1.", exercise);
            break;
    }
}

void run_project2_exercise(const int exercise) {
    switch (exercise) {
        case 1: exercise1p2(); break;
        case 3: exercise3p2(); break;
        default:
            Logger::instance().log("Exercise %d not found in Project 2.", exercise);
            break;
    }
}

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "en_US.UTF-8");

    int project = -1;
    int exercise = -1;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--project" && i + 1 < argc) {
            try {
                project = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Invalid project number: " << argv[i] << std::endl;
                return 1;
            }
        } else if (arg == "--exercise" && i + 1 < argc) {
            try {
                exercise = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Invalid exercise number: " << argv[i] << std::endl;
                return 1;
            }
        }
    }

    if (project == -1 || exercise == -1) {
        std::cerr << "Usage: " << argv[0] << " --project [1|2] --exercise [number]" << std::endl;
        return 1;
    }

    Logger::instance().print_separator();
    Logger::instance().log("Project %d, Exercise %d:", project, exercise);
    Logger::instance().print_separator();

    if (project == 1) {
        run_project1_exercise(exercise);
    } else if (project == 2) {
        run_project2_exercise(exercise);
    } else {
        Logger::instance().log("Project %d not found. Available projects: 1, 2", project);
    }

    Logger::instance().print_separator();
    Logger::instance().print_empty_line();

    return 0;
}
