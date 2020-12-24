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

#ifndef INPUT_H_
#define INPUT_H_

#include <vector>
#include <memory>
#include <map>

#include "glfw3.h"

#include "pubsub.h"

namespace spectre {

class Input {
public: 
  void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  Input();
  void Update();
  //wrappers for pubsub stuff for ease of use
  bool IsKeyPressed(int key); // take a glfw key code
  bool IsKeyPressed(const char* keyname); // take a name (doesn't have the input/whatever)
  bool IsKeyJustChanged(int key);
  bool IsKeyJustChanged(const char* keyname);
 private:
  static constexpr const char* GLFWKeyToTopicName(int key);
  std::unique_ptr<std::map<const char*, std::shared_ptr<Topic>>> key_map_;
  std::unique_ptr<std::vector<const char*>> to_remove_just_changed_;
  const json default_key_topic_data_ = R"(
    {
      "pressed": false,
      "just_changed": false
    }
  )"_json;
  //helper functions to set up all the billion topics
  void InitTopic(int keycode);
  void InitTopicRange(int start_key, int end_key);
};

}

#endif //INPUT_H_