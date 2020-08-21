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
    collision_shape = std::shared_ptr<btCollisionShape>(new btSphereShape(5));
    btTransform Transform;
    Transform.setIdentity();
    Transform.setOrigin(pos.GetbtVector3());
    Transform.setRotation(rot.GetbtQuaternion());
    std::shared_ptr<btDefaultMotionState> motion(new btDefaultMotionState(Transform));
    collision_shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rigid_body_info(mass, motion.get(), collision_shape.get(), inertia);
    rigid_body = std::make_shared<btRigidBody>(rigid_body_info);
  }

  void TransformComponent::Update(float delta_time) {
    World::Instance().GetLogger().Log(Logger::Level::kInfo, "coming from transform component");
  }

  void TransformComponent::UpdatePhysics() {
      if (this->rigid_body != nullptr) {
          btTransform Transform;
          Transform.setIdentity();
          Transform.setOrigin(pos.GetbtVector3());
          Transform.setRotation(rot.GetbtQuaternion());
          this->rigid_body->setWorldTransform(Transform);
          this->rigid_body->getMotionState()->setWorldTransform(Transform);
      }
  }

  bool TransformComponent::ExecuteCommand(std::shared_ptr<BaseCommand> command) {
  switch (command->command_id_) {
    case CommandID::kSetPosition: {
      World::Instance().GetLogger().Log(Logger::Level::kInfo, "SetPosition command called!");
      std::shared_ptr<SetPosition> position_command = std::static_pointer_cast<SetPosition>(command);
      this->pos = Vector3(btScalar(position_command->x_), btScalar(position_command->y_), btScalar(position_command->z_));
      this->UpdatePhysics();
      break;
    }
    case CommandID::kGetPosition: {
      World::Instance().GetLogger().Log(Logger::Level::kInfo, "GetPosition command called!");
      break;
    }
    case CommandID::kSetRotation: {
        std::shared_ptr<SetRotation> rot_set_command = std::static_pointer_cast<SetRotation>(command);
        this->rot = Quaternion(btScalar(rot_set_command->x_), btScalar(rot_set_command->y_), btScalar(rot_set_command->z_), btScalar(rot_set_command->w_));
        this->UpdatePhysics();
        break;
    }
    default: {
      return false;
    }
  }
  return true;
  }

} // namespace spectre
