// main.cc
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

#include "world.h"
#include "object.h"
#include "objectmanager.h"
#include "command.h"
#include "physics_component.h"

int main() {
  spectre::Object object = spectre::Object();
  spectre::World::Instance().GetObjectManager().AddObject(object);
  spectre::PhysicsComponent phys_comp = spectre::PhysicsComponent();
  object.AddComponent(phys_comp);
  object.ExecuteCommand(std::make_shared<spectre::GetPosition>(spectre::GetPosition()));
  //spectre::World::Instance().GetObjectManager().RemoveObject(object.GetID());
  return 0;
}