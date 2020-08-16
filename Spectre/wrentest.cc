

#include "wren.hpp"
#include <iostream>
#include <string>

std::string getWrenScript(std::string scriptName) {
    std::cout << "WARNING: getWrenScript not inplementing. Returning hello world." << std::endl;
    return "System.print(\"I am running in a VM and this is coming from a not implemented function!\")";
}

void writeFn(WrenVM* vm, const char* text) {
    std::cout << text;
}

void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, 
            const int line, const char* msg) {
    switch (errorType) {
        case WREN_ERROR_COMPILE: {
            std::cerr << "WREN COMPILE ERROR:" << std::endl;
            std::cerr << "Module: " << module << " Line: " << line << "Msg:" << std::endl;
            std::cerr << msg << std::endl;
        } break;
        case WREN_ERROR_STACK_TRACE: {
            std::cerr << "WREN STACK TRACE:" << std::endl;
            std::cerr << "Module: " << module << " Line: " << line << "Msg:" << std::endl;
            std::cerr << msg << std::endl;
        } break;
        case WREN_ERROR_RUNTIME: {
            std::cerr << "WREN RUNTIME ERROR:" << std::endl;
            std::cerr << msg << std::endl;
        } break;
    }
}

int main() {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
        config.writeFn = &writeFn;
        config.errorFn = &errorFn;
    WrenVM* vm = wrenNewVM(&config);

    const std::string module = "main";
    const std::string script = getWrenScript("HelloWorld");
    
    WrenInterpretResult result = wrenInterpret(vm, module.c_str(), script.c_str());

    switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
            { std::cout << "Compile Error!" << std::endl; } break;
        case WREN_RESULT_RUNTIME_ERROR:
            { std::cout << "Runtime Error!" << std::endl; } break;
        case WREN_RESULT_SUCCESS:
            { std::cout << "Success!" << std::endl; } break;    
    }

    wrenFreeVM(vm);
}
