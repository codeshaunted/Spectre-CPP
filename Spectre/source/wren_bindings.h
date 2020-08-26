// wren_bindings.h
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

#ifndef WREN_BINDINGS_H_
#define WREN_BINDINGS_H_

#include "wren.hpp"
#include <string>

namespace spectre {

//static
class WrenBindings {
 public:
  static void WrenPrint(WrenVM* vm, const char* text);
  static void WrenError(WrenVM* vm, WrenErrorType errorType, const char* module,
                        const int line, const char* msg);
  static char* WrenLoadModule(WrenVM* vm, const char* name);
 private:
  // Constructor is private so this is like a static class as exist in languages 
  // like java and C#
  WrenBindings();
  static const std::string kScriptDirectory_;
  static const std::string kFileExtension_;
};

}

#endif //WREN_BINDINGS_H_