//TEMP FILE
//ONLY USED FOR TESTING

#include "test_pub_sub.h"

namespace spectre {

void TestPubSub::Awake() {
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
        "a": false
      }
    )"_json);
  } else if (framecount == 2) {
    auto data = awakeTopic_->GetValue();
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "got data: \n" + data.dump());
    World::Instance().GetPubSub().DumpTopicTreeToLog();
    awakeTopic_->SetValue(R"(
      {
        "a": true
      }
    )"_json);
    data = awakeTopic_->GetValue();
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "data after set: \n" + data.dump());
  } else if (framecount == 3) {
    auto data = awakeTopic_->GetValue();
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "data next frame: \n" + data.dump());
    awakeTopic_->SetValue(R"(
      {
        "a": false
      }
    )"_json);
    awakeTopic_->SetValue(R"(
      {
        "a": false
      }
    )"_json);
  } else if (framecount == 4) {
    auto data = awakeTopic_->GetValue();
    World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "data next frame: \n" + data.dump());
  }
}

}