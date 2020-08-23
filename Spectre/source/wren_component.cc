// wren_component.cc
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

#include "wren_component.h"
#include "wren_bindings.h"
#include "wren.hpp"

#include "world.h"
#include "logger.h"

namespace spectre {

WrenComponent::WrenComponent(std::string script_name) {
  wrenInitConfiguration(&config_);
  SetupCallbacks();
  vm_ = wrenNewVM(&config_);

  wrenEnsureSlots(vm_, 5);
  ensured_slots_ = wrenGetSlotCount(vm_);

  //interpret the script to define methods, classes, etc.
  WrenInterpretResult result = wrenInterpret(vm_, script_name.c_str(), 
                        WrenBindings::WrenLoadModule(vm_, script_name.c_str()));
  // I'm going to comment this and leave it since it seems to be redundant when WrenError is set up,
  // but it may be useful at some point for debugging.
  // switch (result){
  //   case WREN_RESULT_COMPILE_ERROR: {
  //     World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "didn't compile");
  //     break;
  //   }
  //   case WREN_RESULT_RUNTIME_ERROR: {
  //     World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "runtime error");
  //     break;
  //   }
  //   case WREN_RESULT_SUCCESS: {
  //     World::Instance().GetLogger().Log(Logger::LogLevel::kDebug, "success!");
  //     break;
  //   }
  // }
}

void WrenComponent::SetupCallbacks() {
  config_.writeFn = &(WrenBindings::WrenPrint);
  config_.errorFn = &(WrenBindings::WrenError);
  config_.loadModuleFn = &(WrenBindings::WrenLoadModule);
}

WrenComponent::~WrenComponent() {
  CleanupHandles();
  wrenFreeVM(vm_);
}

void WrenComponent::CleanupHandles() {}

void WrenComponent::Start() {

}

void WrenComponent::Update(float delta_time) {

}

}