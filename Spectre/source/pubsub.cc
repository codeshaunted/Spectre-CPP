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

#include "pubsub.h"
#include "world.h"

// #include <stdexcept> // included by json.hpp
#include <set>

namespace spectre {

void Topic::SetValue(json value) {
  // Make sure it wasn't already set to avoid race condition.
  if(wasSetThisFrame_) {
    World::Instance().GetLogger().Log(Logger::LogLevel::kError, 
                            "topic " + path_ + " was already set this frame!");
    shouldUpdateValue_ = false; // do not update because of unreliable value
    return;
  }

  

  // This seems slow. Not sure how to speed it up though. Maybe make a 
  // SetValueUnsafe function as well? Do something else when building for 
  // release?
  for (auto& [key, templateValue] : messageTemplate_.items()) {
    // Cannot change topic type after creating it!
    if(value.find(key) == value.end()) {
      World::Instance().GetLogger().Log(Logger::LogLevel::kError, 
                            "topic type mismatch!");
      World::Instance().GetLogger().Log(Logger::LogLevel::kError, 
                            "given value:\n" + value.dump());
      World::Instance().GetLogger().Log(Logger::LogLevel::kError, 
                            "template:\n" + messageTemplate_.dump());
    }
  }

  // Modify the value that is not in use
  if (readFromValueA_) {
    valueB_ = value;
  } else {
    valueA_ = value;
  }

  wasSetThisFrame_ = true;
  shouldUpdateValue_ = true;
}

void Topic::SwapBuffers() {
  wasSetThisFrame_ = false;
  if(!shouldUpdateValue_)
    return;
  
  readFromValueA_ = !readFromValueA_;

  // Run callbacks
  for (auto callback : callbackList_) {
    callback(GetValue());
  }

  shouldUpdateValue_ = false;
  wasSetThisFrame_ = false;
}

std::shared_ptr<Topic> PubSub::initTopic(std::string path, json messageTemplate) {
  auto ptr = std::make_shared<Topic>(path, messageTemplate);
  topicMap_[path] = ptr;
  return ptr;
}

std::shared_ptr<Topic> PubSub::GetTopic(std::string path) {
  auto found = topicMap_.find(path);
  if(found == topicMap_.end()) {
    throw std::invalid_argument("no topic " + path + " exists!");
  } else {
    return found->second;
  }
}

void PubSub::Update() {
  for (auto element : topicMap_) {
    element.second->SwapBuffers();
  }
}

void PubSub::DumpTopicTreeToLog() {
  std::set<std::string> toPrint;
  for (auto pair : topicMap_) {
    toPrint.insert(pair.first);
  }
  std::string toPrint_s = std::string("All current topics:");
  for(std::string path : toPrint) {
    toPrint_s += "\n"+path;
  }
  World::Instance().GetLogger().Log(Logger::LogLevel::kInfo, toPrint_s);
}

}