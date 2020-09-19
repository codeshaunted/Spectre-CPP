// pubsub.h
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

#ifndef PUBSUB_H_
#define PUBSUB_H_

#include <nlohmann/json.hpp>

// #include <string> // This is used but json.hpp already includes it
// #include <vector> // ditto
// #include <unordered_map> // ditto
// #include <memory> //ditto

using json = nlohmann::json;

namespace spectre {

class Topic;

class PubSub {
 public:
  PubSub() : topicMap_() {}

  void Update();

  // Initialize a topic and return a shared_ptr to it. This pointer can be cached
  // or GetTopic(path) can be called to get the pointer later.
  std::shared_ptr<Topic> initTopic(std::string path, json messageTemplate);

  // Get a shared_ptr to a topic given its path. The returned shared_ptr can be
  // cached for faster access.
  std::shared_ptr<Topic> GetTopic(std::string path);

  // Print out all topics
  void DumpTopicTreeToLog();

 private:
  // Map storing topics, indexed by a string path.
  std::unordered_map<std::string, std::shared_ptr<Topic>> topicMap_;
};

class Topic {
 public:
  // Takes the path of this topic (technically optional but helpful for error
  // messages) and a template for the value to compare new values to.
  Topic(std::string path, json topicTemplate) : messageTemplate_(topicTemplate),
  valueB_(topicTemplate), valueA_(topicTemplate), path_(path) {}

  // Get a copy of the current value
  json GetValue() const {
    // return (useValueA_) ? valueA_ : valueB_;
    return json((readFromValueA_) ? valueA_ : valueB_);
  }

  // Get  a copy ofthe template. The type of data in a topic cannot change after
  // it is initialized, so if you call SetValue() with json that has the wrong 
  // data nothing will happen. Use this function to ensure a value has the right
  // data before calling SetValue if value is generated by user input or something
  // else that can change unexpectedly.
  json GetTemplate() const { return json(messageTemplate_); }

  // Set the value. Can be called only once per frame, otherwise race conditions
  // would be possible. call WasSet() to check if this topic was set already.
  //
  // If the value given has the wrong data or this topic has already been set
  // this frame, and error message will be printed and the value will stay the 
  
  // same into the next frame, e.g. the previous set will be invalidated.
  void SetValue(json value);

  // This needs to be called exactly once between frames. This facilitates double
  // bufferring, which is necessary to allow setting the value while other things
  // are reading it and not inducing a race condition.
  void SwapBuffers();

  // Test if this topic was already set this frame.
  bool WasSet() const { return wasSetThisFrame_; }

  // Adds a lambda to run with the latest value when this topic is updated
  void AddCallback(std::function<void(json)> newCallback) {
    callbackList_.push_back(newCallback);
  }

 private:
  // Two values so that this can be double-buffered
  json valueA_;
  json valueB_;
  // To keep track of which one can be changed
  bool readFromValueA_;

  // To keep track of if callbacks should be called.
  bool shouldUpdateValue_;
  // To detect multiple SetValue calls
  bool wasSetThisFrame_;

  //define what data is in this message:
  const json messageTemplate_;

  const std::string path_;

  std::vector<std::function<void(json)>> callbackList_;
};

}

#endif // PUBSUB_H_