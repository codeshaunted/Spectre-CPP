// component.h
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

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>

namespace spectre {

class BaseCommand;

enum class ComponentID : uint16_t {
  kNullComponent,
  kPhysics,
};

class Component {
 public:
  virtual void Update(float delta_time);
  virtual bool ExecuteCommand(std::shared_ptr<BaseCommand> command) { return false; }
  ComponentID component_id_ = ComponentID::kNullComponent;
};

} // namespace spectre

#endif // COMPONENT_H_