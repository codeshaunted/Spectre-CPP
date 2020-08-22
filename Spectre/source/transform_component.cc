// transform_component.cc
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

#include "transform_component.h"

#include <iostream>

#include "command.h"
#include "logger.h"
#include "world.h"
#include "object_manager.h"

namespace spectre {

  void TransformComponent::Update(float delta_time) {
    World::Instance().GetLogger().Log(Logger::LogLogLevel::kInfo, "coming from transform component");
  }

  bool TransformComponent::ExecuteCommand(std::shared_ptr<BaseCommand> command) {
  switch (command->command_id_) {
    case CommandID::kSetPosition: {
      World::Instance().GetLogger().Log(Logger::LogLevel::kInfo, "SetPosition command called!");
      break;
    }
    case CommandID::kGetPosition: {
      World::Instance().GetLogger().Log(Logger::LogLevel::kInfo, "GetPosition command called!");
      break;
    }
    default: {
      return false;
    }
  }
  return true;
}

} // namespace spectre
