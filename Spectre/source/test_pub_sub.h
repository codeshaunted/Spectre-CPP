//TEMP FILE
//USED ONLY FOR TESTING

#ifndef TEST_PUB_SUB_H_
#define TEST_PUB_SUB_H_

#include "world.h"

namespace spectre {

class TestPubSub : public Component {
 public:
  void Awake() override;

  void Update(float delta_time) override;
 private:
  std::shared_ptr<Topic> awakeTopic_;
};

}
#endif //TEST_PUB_SUB_H_