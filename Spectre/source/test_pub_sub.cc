//TEMP FILE
//ONLY USED FOR TESTING

#include "test_pub_sub.h"

namespace spectre {

void TestPubSub::Awake() {
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "awake called");

  awakeTopic_ = World::Instance().GetPubSub().initTopic("test/awake", R"(
    {
      "a": true
    }
  )"_json);
  awakeTopic_->AddCallback([](json j) {
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "got callback with data: \n" + j.dump());
  });
}

void TestPubSub::Update(float delta_time) {
  int framecount = World::Instance().GetFrameCount();

  if (framecount == 1) {
    World::Instance().GetPubSub().DumpTopicTreeToLog();
    awakeTopic_->SetValue(R"(
      {
        "a": true
      }
    )"_json);
  }
}

}