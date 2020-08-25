// object.h
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

#ifndef OBJECT_H_
#define OBJECT_H_

#include <map>
#include <memory>

#include "component.h"

namespace spectre {

class BaseCommand;

typedef uint64_t ObjectID;

class Object {
 public:
  Object();
  ~Object();

  void Update(float delta_time);

  ObjectID GetID() const { return id_; }
  void SetID(ObjectID id) { id_ = id; }

  template <class T> 
  void AddComponent(std::shared_ptr<T> component);

  bool ExecuteCommand(const std::shared_ptr<BaseCommand>& command);
  bool ExecuteCommandOnComponents(const std::shared_ptr<BaseCommand>& command);

 private:
  ObjectID id_;
  std::map<ComponentID, std::shared_ptr<Component>> components_;
};

template<class T>
inline void Object::AddComponent(std::shared_ptr<T> component) {
  components_.insert({ component->component_id_, component });
}

} // namespace spectre

#endif // OBJECT_H_