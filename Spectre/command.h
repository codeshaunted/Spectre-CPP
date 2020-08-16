// command.h
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

#ifndef COMMAND_H_
#define COMMAND_H_

#include <cstdint>

#include "command_id.h"

namespace spectre {

class Object;

class Command {
 public:
  uint16_t command_id_ = CommandID::kNullCommand; // If you're exceeding 65535 unique messages in a game, you're doing something wrong
};

class GetPosition : public Command {
 public:
  uint16_t command_id_ = CommandID::kGetPosition;
};

class SetPosition : public Command {
 public:
  uint16_t command_id_ = CommandID::kSetPosition;
};

} // namespace spectre

#endif // COMMAND_H_