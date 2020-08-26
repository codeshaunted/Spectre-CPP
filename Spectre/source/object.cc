// object.cc
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

#include "object.h"

#include "component.h"
#include "command.h"
#include "world.h"

namespace spectre {

Object::Object() {
  id_ = 0; // Object IDs start at 1, ensuring this default value will never occur in an ObjectManager
}

Object::~Object() = default;

void Object::Update(float delta_time) {
  for (const auto& component : components_) {
    //World::Instance().update_queue_.push_back(component.second);
    // TODO: Add option for non-multithreaded (GameVariables)
    component.second->Update(delta_time);
  }
}

bool Object::ExecuteCommand(const std::shared_ptr<BaseCommand>& command) {
  switch (command->command_id_) {
    default: {
      return ExecuteCommandOnComponents(command);
    }
  }
}

bool Object::ExecuteCommandOnComponents(const std::shared_ptr<BaseCommand>& command)
{
  bool command_handled = false;

  for (const auto& component : components_) {
    command_handled |= component.second->ExecuteCommand(command, std::shared_ptr<Object>(this));
  }

  return command_handled;
}

} // namespace spectre