// wren_bindings.cc
// Copyright (C) 2020 Spectre Team
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "wren_bindings.h"
#include "world.h"
#include "logger.h"


#include <string>

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace spectre {

const std::string WrenBindings::kScriptDirectory_ = "scripts";
const std::string WrenBindings::kFileExtension_ = "wren";

void WrenBindings::WrenPrint(WrenVM* vm, const char* text) {
  std::string textString = std::string(text);
  // Remove trailing whitespace.
  // note: this is mostly here because when system.print() is called in wren,
  // it calls this method once for the message and again with just a "\n".
  // This eats that newline because Logger.Log adds a newline already.
  if(!textString.empty() && textString[textString.length()-1] == '\n') {
    textString.erase(textString.length()-1);
  }
  
  if(!textString.empty())
    World::Instance().GetLogger().Log(Logger::LogLevel::kScript, std::string(text));
}

void WrenBindings::WrenError(WrenVM* vm, WrenErrorType errorType, 
                              const char* module, const int line, const char* msg) {
  std::string error;
  switch (errorType) {
    case WREN_ERROR_COMPILE: {
      error = std::string("WREN COMPILE ERROR:\n [") + 
              module + std::string(" line ") + 
              std::to_string(line) + std::string("]: \n") + msg;
    } break;
    case WREN_ERROR_RUNTIME: {
      // If there is a runtime error, this is called once without a line or 
      // module, then this is called again with WREN_ERROR_STACK_TRACE once per 
      // line of the stack trace.
      error = std::string("WREN RUNTIME ERROR: \n") + msg;
    } break;
    case WREN_ERROR_STACK_TRACE: {
      error = std::string("[") + module + std::string(" line ") + 
              std::to_string(line) + std::string("] in ") + msg;
    } break;
  }
  World::Instance().GetLogger().Log(Logger::LogLevel::kError, error);
}

char* WrenBindings::WrenLoadModule(WrenVM* vm, const char* name) {
  if(!std::filesystem::exists(kScriptDirectory_))
    return NULL;
  
  std::string path = kScriptDirectory_ + "/" + std::string(name) + ".wren";
  //check if the file exists
  if(!std::filesystem::exists(path)) {
    return NULL;
  }
  else {
    std::ifstream file = std::ifstream(path);
    std::string contents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    // NOTE: THIS MUST USE THE SAME ALLOCATOR AS WREN USES INTERNALLY.
    // If the config's reallocateFn is set up with a different allocator or
    // something, this needs to use the same thing or bad things will happen.
    char* mem = (char*)calloc(contents.size() + 1, sizeof(char));
    
    strcpy(mem, contents.c_str());
    return mem;
  }
}

}