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
  for (auto& [key, value] : messageTemplate_.items()) {
    // Cannot change topic type after creating it!
    assert(value.find(key) != value.end());
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
  if(!shouldUpdateValue_)
    return;
  
  readFromValueA_ = !readFromValueA_;

  // Run callbacks
  for (auto callback : callbackList_) {
    callback(GetValue());
  }
}

}