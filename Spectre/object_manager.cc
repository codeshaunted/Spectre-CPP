// object_manager.cc
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

#include "object_manager.h"

#include "object.h"
#include "command.h"

namespace spectre {

ObjectManager::ObjectManager()
{
  next_id_ = 0;
}

void ObjectManager::AddObject(std::shared_ptr<Object> object) {
  ObjectID id = GetNewID();
  object->SetID(id);
  objects_.insert({ id, object });
}

std::shared_ptr<Object> ObjectManager::GetObject(ObjectID id)
{
  return objects_[id];
}

bool ObjectManager::ExecuteCommand(std::shared_ptr<BaseCommand> command)
{
  return GetObject(command->target_id_)->ExecuteCommand(command);
}

void ObjectManager::RemoveObject(ObjectID id) {
  objects_.erase(id);
}

ObjectID ObjectManager::GetNewID()
{
  ++next_id_;
  return next_id_;
}

} // namespace spectre