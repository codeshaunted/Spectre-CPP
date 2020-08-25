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

namespace spectre {
  void PhysicsComponent::Start() {
    collision_shape = std::shared_ptr<btCollisionShape>(new btSphereShape(5));
    btTransform Transform;
    Transform.setIdentity();
    std::shared_ptr<btDefaultMotionState> motion(new btDefaultMotionState(Transform));
    collision_shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rigid_body_info(mass, motion.get(), collision_shape.get(), inertia);
    rigid_body = std::make_shared<btRigidBody>(rigid_body_info);
  }

  void PhysicsComponent::Update(float delta_time) {

  }

  bool PhysicsComponent::ExecuteCommand(std::shared_ptr<BaseCommand> command, std::shared_ptr<Object> caller) {
    switch (command->command_id_) {
      case CommandID::kUpdatePhysics: {
        std::shared_ptr<UpdatePhysics> physics_commmand = std::static_pointer_cast<UpdatePhysics>(command);
        if (this->rigid_body != nullptr) {
          btTransform Transform;
          Transform.setIdentity();
          Transform.setOrigin(physics_commmand->vector_.GetbtVector3());
          Transform.setRotation(physics_commmand->quaternion_.GetbtQuaternion());
          this->rigid_body->setWorldTransform(Transform);
          this->rigid_body->getMotionState()->setWorldTransform(Transform);
        }
      }
      default: {
        return false;
      }
    }
    return true;
  }

}
