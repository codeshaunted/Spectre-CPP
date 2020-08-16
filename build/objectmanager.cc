// objectmanager.cc
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

#include "objectmanager.h"

namespace spectre {

ObjectManager::ObjectManager()
{
  next_id_ = 0;
}

void ObjectManager::AddObject(Object object) {
  uint64_t id = GetNewID();
  object.SetID(id);
  objects_.insert({ id, std::make_shared<Object>(object) });
}

void ObjectManager::RemoveObject(uint64_t id) {
  objects_.erase(id);
}

uint64_t ObjectManager::GetNewID()
{
  ++next_id_;
  return next_id_ - 1;
}

} // namespace spectre