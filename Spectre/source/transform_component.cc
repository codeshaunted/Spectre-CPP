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


namespace spectre {

  void TransformComponent::Start() {

  }

  void TransformComponent::Update(float delta_time) {
    World::Instance().GetLogger().Log(Logger::Level::kInfo, "coming from transform component");
  }

  bool TransformComponent::ExecuteCommand(std::shared_ptr<BaseCommand> command, std::shared_ptr<Object> caller) {
  switch (command->command_id_) {
    case CommandID::kSetPosition: {
      std::shared_ptr<SetPosition> position_command = std::static_pointer_cast<SetPosition>(command);
      this->pos = Vector3(position_command->x_, position_command->y_, position_command->z_);
      caller->ExecuteCommand(std::make_shared<UpdatePhysics>(caller->GetID(), this->pos, this->rot));
      break;
    }
    case CommandID::kGetPosition: {
      std::shared_ptr<GetPosition> position_command = std::static_pointer_cast<GetPosition>(command);
      position_command->x_ = pos.x;
      position_command->y_ = pos.y;
      position_command->z_ = pos.z;
      break;
    }
    case CommandID::kSetRotation: {
        std::shared_ptr<SetRotation> rot_set_command = std::static_pointer_cast<SetRotation>(command);
        this->rot = Quaternion(rot_set_command->x_, rot_set_command->y_, rot_set_command->z_, rot_set_command->w_);
        break;
    }
    case CommandID::kGetRotation: {
      std::shared_ptr<GetRotation> rot_get_command = std::static_pointer_cast<GetRotation>(command);
      rot_get_command->x_ = rot.x;
      rot_get_command->y_ = rot.y;
      rot_get_command->z_ = rot.z;
      rot_get_command->w_ = rot.w;
      break;
    }
    default: {
      return false;
    }
  }
  return true;
  }

} // namespace spectre
