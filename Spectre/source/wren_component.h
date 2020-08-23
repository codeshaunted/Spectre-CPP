// wren_component.h
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

#ifndef WREN_COMPONENT_H_
#define WREN_COMPONENT_H_

#include "script_component.h"
#include <string>

#include "wren.hpp"

namespace spectre {

class WrenComponent : public ScriptComponent {
 public:
  void Update(float delta_time);
  void Start();
  WrenComponent(std::string script_name);
  ~WrenComponent();
 private:
  void SetupCallbacks();
  void CleanupHandles();
  std::string script_name_;
  WrenVM *vm_;
  WrenConfiguration config_;
  int ensured_slots_ = 0;
};

}



#endif // WREN_COMPONENT_H_