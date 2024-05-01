// Copyright 2024 Vinokurov Ivan

#include "include/objvolumes_app.h"
#include "include/objvolumes.h"
#include <sstream>
#include <cstring>

ObjVolumeApp::ObjVolumeApp() : message_("") {}

std::vector<double> parseVector(const char* input) {
    std::vector<double> result;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {
        try {
            double number = std::stod(token);
            result.push_back(number);
        }
        catch (const std::exception& e) {
            throw std::logic_error("Wrong vector format!");
            continue;
        }
    }

    return result;
}

std::string parseObjType(const char* arg) {
    std::string ot;
    if (strcmp(arg, "Sphere") == 0) {
        ot = "Sphere";
    } else if (strcmp(arg, "Cylinder") == 0) {
        ot = "Cylinder";
    } else if (strcmp(arg, "Cube") == 0) {
        ot = "Cube";
    } else {
        throw std::logic_error("Wrong object format!");
    }
    return ot;
}

std::string ObjVolumeApp::operator()(int argc, const char** argv) {
    Arguments input;

    if (!validateNumberOfArguments(argc, argv)) {
        return message_;
    }

    input.objType = parseObjType(argv[1]);
    input.arg = parseVector(argv[2]);

    std::ostringstream stream;
    if (input.objType == "Sphere") {
        if (input.arg.size() != 1) {
            return message_;
        }
        if (input.arg[0] <= 0) {
            throw std::logic_error("Wrong arguement format!");
        }
        Sphere sphere(input.arg[0]);
        stream << "Volume = " << sphere.volume();
    } else if (input.objType == "Cylinder") {
        if (input.arg.size() != 2) {
            return message_;
        }
        if (input.arg[0] <= 0 && input.arg[1] <= 0) {
            throw std::logic_error("Wrong arguement format!");
        }
        Cylinder cylinder(input.arg[0], input.arg[1]);
        stream << "Volume = " << cylinder.volume();
    } else if (input.objType == "Cube") {
        if (input.arg.size() != 1) {
            return message_;
        }
        if (input.arg[0] <= 0) {
            throw std::logic_error("Wrong arguement format!");
        }
        Cube cube(input.arg[0]);
        stream << "Volume = " << cube.volume();
    }

    message_ = stream.str();
    return message_;
}

void ObjVolumeApp::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
        "This is an object volume calculator application.\n\n" +
        "Please provide arguments in the following format:\n\n" +

        "  $ " + appname + " <objType> <arg> \n\n" +

        "Where objType is a string with of object (Sphere, Cube, Cylinder), " +
        "and <arg> is a vector with double-precision numbers \n" +
        "In the format of 1,2,3 or 1.0,2.0,3.0 \n";
}

bool ObjVolumeApp::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 3) {
        help(argv[0], "ERROR: Should be 2 arguments.\n\n");
        return false;
    }
    return true;
}

