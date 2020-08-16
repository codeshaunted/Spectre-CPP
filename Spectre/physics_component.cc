// physics_component.cc
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

#include "physics_component.h"

#include <iostream>

#include "command_id.h"
#include "command.h"

namespace spectre {

bool PhysicsComponent::ExecuteCommand(std::shared_ptr<Command> command) { 
  switch (command->command_id_) {
    case CommandID::kGetPosition: {
      std::cout << "SET POS!!!" << std::endl;
      break;
    }
    case CommandID::kSetPosition: {
      break;
    }
    default: {
      return false;
    }
  }
  return true;
}

} // namespace spectre
