#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <stdexcept>
#include <string>
using namespace std;

struct SintaxError : runtime_error {
    SintaxError(const char* msg) : runtime_error(msg) { }
    SintaxError(string msg) : runtime_error(msg.c_str()) { }
};

struct LexicalError : runtime_error {
    LexicalError(const char* msg) : runtime_error(msg) { }
    LexicalError(string msg) : runtime_error(msg.c_str()) { }
};

struct ParseError : runtime_error {
    ParseError(const char* msg) : runtime_error(msg) { }
    ParseError(string msg) : runtime_error(msg.c_str()) { }
};

struct SemanticalError : runtime_error {
    SemanticalError(const char* msg) : runtime_error(msg) { }
    SemanticalError(string msg) : runtime_error(msg.c_str()) { }
};


#endif
