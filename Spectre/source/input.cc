// pubsub.cpp
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

#include "input.h"
#include "world.h"

namespace spectre {

void Input::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action != GLFW_REPEAT) {
    json value = R"({})"_json;
    value["pressed"] = action == GLFW_PRESS; // true if pressed, false if released
    value["just_changed"] = true;
    key_map_->find(GLFWKeyToTopicName(key))->second->SetValueUnsafe(value);
    to_remove_just_changed_->push_back(GLFWKeyToTopicName(key));
  }
}

bool Input::IsKeyPressed(int key) {
  json value = key_map_->find(GLFWKeyToTopicName(key))
                       ->second
                       ->GetValue();
  return value["pressed"];
}

bool Input::IsKeyPressed(const char* keyname) {
  std::string name_str = std::string("input/keyboard/") + std::string(keyname);
  json value = key_map_->find(name_str.c_str())
                       ->second
                       ->GetValue();
  return value["pressed"];
}

bool Input::IsKeyJustChanged(int key) {
  json value = key_map_->find(GLFWKeyToTopicName(key))
                       ->second
                       ->GetValue();
  return value["just_changed"];
}

bool Input::IsKeyJustChanged(const char* keyname) {
  std::string name_str = std::string("input/keyboard/") + std::string(keyname);
  json value = key_map_->find(name_str.c_str())
                       ->second
                       ->GetValue();
  return value["just_changed"];
}

void Input::Update() {
  for (const char* keyname : *to_remove_just_changed_) {
    json value = key_map_->find(keyname)->second->GetValue();
    if (value["just_changed"]) {
      value["just_changed"] = false;
    }
    key_map_->find(keyname)->second->SetValue(value); 
    // this should get changed only on the next frame, when the buffers are swapped.
  }
  to_remove_just_changed_->clear();
}

void Input::InitTopic(int keycode) {
  auto name = GLFWKeyToTopicName(keycode);
  auto topic = World::Instance().GetPubSub().initTopic(
    std::string(name), default_key_topic_data_
  );
  key_map_->emplace(name, topic);
}

void Input::InitTopicRange(int start_key, int end_key) {
  for(int i = start_key; i <= end_key; i++) {
    InitTopic(i);
  }
}

Input::Input() {
  to_remove_just_changed_ = std::make_unique<std::vector<const char*>>();
  key_map_ = std::make_unique<std::map<const char*, std::shared_ptr<Topic>>>();
  InitTopic(GLFW_KEY_UNKNOWN);
  InitTopic(GLFW_KEY_SPACE);
  InitTopic(GLFW_KEY_APOSTROPHE);
  InitTopicRange(GLFW_KEY_COMMA, GLFW_KEY_9);
  InitTopic(GLFW_KEY_SEMICOLON);
  InitTopic(GLFW_KEY_EQUAL);
  InitTopicRange(GLFW_KEY_A, GLFW_KEY_RIGHT_BRACKET);
  InitTopic(GLFW_KEY_GRAVE_ACCENT);
  InitTopic(GLFW_KEY_WORLD_1);
  InitTopic(GLFW_KEY_WORLD_2);
  InitTopicRange(GLFW_KEY_ESCAPE, GLFW_KEY_END);
  InitTopicRange(GLFW_KEY_CAPS_LOCK, GLFW_KEY_PAUSE);
  InitTopicRange(GLFW_KEY_F1, GLFW_KEY_F25);
  InitTopicRange(GLFW_KEY_KP_0, GLFW_KEY_KP_EQUAL);
  InitTopicRange(GLFW_KEY_LEFT_SHIFT, GLFW_KEY_MENU); // Thanks, GLFW, very cool!
}

// dummy thicc switch statment to go from GLFW key code to a topic path or whatever
constexpr const char *Input::GLFWKeyToTopicName(int key) {
  switch (key) {
  case GLFW_KEY_SPACE:
    return "input/keyboard/space";
  case GLFW_KEY_APOSTROPHE:
    return "input/keyboard/apostrophe";
  case GLFW_KEY_COMMA:
    return "input/keyboard/comma";
  case GLFW_KEY_MINUS:
    return "input/keyboard/minus";
  case GLFW_KEY_PERIOD:
    return "input/keyboard/period";
  case GLFW_KEY_SLASH:
    return "input/keyboard/slash";
  case GLFW_KEY_0:
    return "input/keyboard/0";
  case GLFW_KEY_1:
    return "input/keyboard/1";
  case GLFW_KEY_2:
    return "input/keyboard/2";
  case GLFW_KEY_3:
    return "input/keyboard/3";
  case GLFW_KEY_4:
    return "input/keyboard/4";
  case GLFW_KEY_5:
    return "input/keyboard/5";
  case GLFW_KEY_6:
    return "input/keyboard/6";
  case GLFW_KEY_7:
    return "input/keyboard/7";
  case GLFW_KEY_8:
    return "input/keyboard/8";
  case GLFW_KEY_9:
    return "input/keyboard/9";
  case GLFW_KEY_SEMICOLON:
    return "input/keyboard/semicolon";
  case GLFW_KEY_EQUAL:
    return "input/keyboard/equal";
  case GLFW_KEY_A:
    return "input/keyboard/a";
  case GLFW_KEY_B:
    return "input/keyboard/b";
  case GLFW_KEY_C:
    return "input/keyboard/c";
  case GLFW_KEY_D:
    return "input/keyboard/d";
  case GLFW_KEY_E:
    return "input/keyboard/e";
  case GLFW_KEY_F:
    return "input/keyboard/f";
  case GLFW_KEY_G:
    return "input/keyboard/g";
  case GLFW_KEY_H:
    return "input/keyboard/h";
  case GLFW_KEY_I:
    return "input/keyboard/i";
  case GLFW_KEY_J:
    return "input/keyboard/j";
  case GLFW_KEY_K:
    return "input/keyboard/k";
  case GLFW_KEY_L:
    return "input/keyboard/l";
  case GLFW_KEY_M:
    return "input/keyboard/m";
  case GLFW_KEY_N:
    return "input/keyboard/n";
  case GLFW_KEY_O:
    return "input/keyboard/o";
  case GLFW_KEY_P:
    return "input/keyboard/p";
  case GLFW_KEY_Q:
    return "input/keyboard/q";
  case GLFW_KEY_R:
    return "input/keyboard/r";
  case GLFW_KEY_S:
    return "input/keyboard/s";
  case GLFW_KEY_T:
    return "input/keyboard/t";
  case GLFW_KEY_U:
    return "input/keyboard/u";
  case GLFW_KEY_V:
    return "input/keyboard/v";
  case GLFW_KEY_X:
    return "input/keyboard/x";
  case GLFW_KEY_Y:
    return "input/keyboard/y";
  case GLFW_KEY_Z:
    return "input/keyboard/z";
  case GLFW_KEY_LEFT_BRACKET:
    return "input/keyboard/left_bracket";
  case GLFW_KEY_BACKSLASH:
    return "input/keyboard/backslash";
  case GLFW_KEY_RIGHT_BRACKET:
    return "input/keyboard/right_bracket";
  case GLFW_KEY_GRAVE_ACCENT:
    return "input/keyboard/grave";
  case GLFW_KEY_WORLD_1:
    return "input/keyboard/world-1"; // ????? i have no clue what these are lmao
  case GLFW_KEY_WORLD_2:
    return "input/keyboard/world-2";
  case GLFW_KEY_ESCAPE:
    return "input/keyboard/escape";
  case GLFW_KEY_ENTER:
    return "input/keyboard/enter";
  case GLFW_KEY_TAB:
    return "input/keyboard/tab";
  case GLFW_KEY_BACKSPACE:
    return "input/keyboard/backspace";
  case GLFW_KEY_INSERT:
    return "input/keyboard/insert";
  case GLFW_KEY_DELETE:
    return "input/keyboard/delete";
  case GLFW_KEY_RIGHT:
    return "input/keyboard/right-arrow";
  case GLFW_KEY_LEFT:
    return "input/keyboard/left-arrow";
  case GLFW_KEY_DOWN:
    return "input/keyboard/down-arrow";
  case GLFW_KEY_UP:
    return "input/keyboard/up-arrow";
  case GLFW_KEY_PAGE_UP:
    return "input/keyboard/page-up";
  case GLFW_KEY_PAGE_DOWN:
    return "input/keyboard/page-down";
  case GLFW_KEY_HOME:
    return "input/keyboard/home";
  case GLFW_KEY_END:
    return "input/keyboard/end";
  case GLFW_KEY_CAPS_LOCK:
    return "input/keyboard/caps-lock";
  case GLFW_KEY_SCROLL_LOCK:
    return "input/keyboard/scroll-lock";
  case GLFW_KEY_NUM_LOCK:
    return "input/keyboard/num-lock";
  case GLFW_KEY_PRINT_SCREEN:
    return "input/keyboard/print-screen";
  case GLFW_KEY_PAUSE:
    return "input/keyboard/pause";
  case GLFW_KEY_F1:
    return "input/keyboard/f1";
  case GLFW_KEY_F2:
    return "input/keyboard/f2";
  case GLFW_KEY_F3:
    return "input/keyboard/f3";
  case GLFW_KEY_F4:
    return "input/keyboard/f4";
  case GLFW_KEY_F5:
    return "input/keyboard/f5";
  case GLFW_KEY_F6:
    return "input/keyboard/f6";
  case GLFW_KEY_F7:
    return "input/keyboard/f7";
  case GLFW_KEY_F8:
    return "input/keyboard/f8";
  case GLFW_KEY_F9:
    return "input/keyboard/f9";
  case GLFW_KEY_F10:
    return "input/keyboard/f10";
  case GLFW_KEY_F11:
    return "input/keyboard/f11";
  case GLFW_KEY_F12:
    return "input/keyboard/f12";
  case GLFW_KEY_F13:
    return "input/keyboard/f13";
  case GLFW_KEY_F14:
    return "input/keyboard/f14";
  case GLFW_KEY_F15:
    return "input/keyboard/f15";
  case GLFW_KEY_F16:
    return "input/keyboard/f16";
  case GLFW_KEY_F17:
    return "input/keyboard/f17";
  case GLFW_KEY_F18:
    return "input/keyboard/f18";
  case GLFW_KEY_F19:
    return "input/keyboard/f19";
  case GLFW_KEY_F20:
    return "input/keyboard/f20";
  case GLFW_KEY_F21:
    return "input/keyboard/f21";
  case GLFW_KEY_F22:
    return "input/keyboard/f22";
  case GLFW_KEY_F23:
    return "input/keyboard/f23";
  case GLFW_KEY_F24:
    return "input/keyboard/f24";
  case GLFW_KEY_F25:
    return "input/keyboard/f25";
  case GLFW_KEY_KP_0:
    return "input/keyboard/numpad-0";
  case GLFW_KEY_KP_1:
    return "input/keyboard/numpad-1";
  case GLFW_KEY_KP_2:
    return "input/keyboard/numpad-2";
  case GLFW_KEY_KP_3:
    return "input/keyboard/numpad-3";
  case GLFW_KEY_KP_4:
    return "input/keyboard/numpad-4";
  case GLFW_KEY_KP_5:
    return "input/keyboard/numpad-5";
  case GLFW_KEY_KP_6:
    return "input/keyboard/numpad-6";
  case GLFW_KEY_KP_7:
    return "input/keyboard/numpad-7";
  case GLFW_KEY_KP_8:
    return "input/keyboard/numpad-8";
  case GLFW_KEY_KP_9:
    return "input/keyboard/numpad-9";
  case GLFW_KEY_KP_DECIMAL:
    return "input/keyboard/numpad-period";
  case GLFW_KEY_KP_DIVIDE:
    return "input/keyboard/numpad-slash";
  case GLFW_KEY_KP_MULTIPLY:
    return "input/keyboard/numpad-asterisk";
  case GLFW_KEY_KP_SUBTRACT:
    return "input/keyboard/numpad-minus";
  case GLFW_KEY_KP_ADD:
    return "input/keyboard/numpad-plus";
  case GLFW_KEY_KP_ENTER:
    return "input/keyboard/numpad-enter";
  case GLFW_KEY_KP_EQUAL:
    return "input/keyboard/numpad-equal";
  case GLFW_KEY_LEFT_SHIFT:
    return "input/keyboard/left-shift";
  case GLFW_KEY_LEFT_CONTROL:
    return "input/keyboard/left-control";
  case GLFW_KEY_LEFT_ALT:
    return "input/keyboard/left-alt";
  case GLFW_KEY_LEFT_SUPER:
    return "input/keyboard/left-super";
  case GLFW_KEY_RIGHT_SHIFT:
    return "input/keyboard/right-shift";
  case GLFW_KEY_RIGHT_ALT:
    return "input/keyboard/right-alt";
  case GLFW_KEY_RIGHT_SUPER:
    return "input/keyboard/right-super";
  case GLFW_KEY_MENU:
    return "input/keyboard/menu";
  default:
    return "input/keyboard/unknown-key";
  }
  // AAAAAAAAAAAAAA
}

} // namespace spectre
