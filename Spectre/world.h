// world.h
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

#include <memory>
#include <functional>
#include <stack>

#include "object_manager.h"
#include "logger.h"

namespace spectre {

class World {
 public:
  void WorldLoop();
  void UpdateThread(std::stack<std::shared_ptr<Component>> components, float delta_time);

  static World& Instance() {
    static std::shared_ptr<World> instance = std::make_shared<World>();
    return *instance;
  }

  ObjectManager& GetObjectManager() {
    if (object_manager_ == NULL) object_manager_ = std::make_shared<ObjectManager>();
    return *object_manager_;
  }

  Logger& GetLogger() {
    if (logger_ == NULL) logger_ = std::make_shared<Logger>();
    return *logger_;
  }

  /*GameVariables& GetGameVariables() {
    if (game_variables_ == NULL) game_variables_ = std::make_shared<GameVariables>();
    return *game_variables_;
  }*/

  std::vector<std::shared_ptr<Component>> update_queue_;

 private:
  static World instance_;
  std::shared_ptr<ObjectManager> object_manager_;
  std::shared_ptr<Logger> logger_;
  //std::shared_ptr<GameVariables> game_variables_;
};

} // namespace spectre