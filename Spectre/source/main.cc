// main.cc
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

#include "object.h"
#include "component.h"
#include "object_manager.h"
#include "command.h"
#include "transform_component.h"
#include "logger.h"
#include "game_variables.h"
#include "test_pub_sub.h"

#ifdef _WIN32
#include <windows.h>

typedef int(__cdecl* f_game_main)();
#endif

int main(int argc, char** argv) {
  /*
  // TODO: Make a real CLI argument parser
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << std::endl;
    if (argv[i] == "-game") {
      if (argv[i + 1] != NULL) {
#ifdef _WIN32
        std::string dll_name = argv[i + 1];
        dll_name += ".dll";

        wchar_t *game_name = new wchar_t[dll_name.length()];
        size_t out_size;
        mbstowcs_s(&out_size, game_name, dll_name.length(), dll_name.c_str(), dll_name.length() - 1);
        HINSTANCE game_dll = LoadLibrary(game_name);
        delete[] game_name;

        f_game_main game_main = (f_game_main)GetProcAddress(game_dll, "game_main");
#endif
        if (!game_main) {
          spectre::World::Instance().GetLogger().Log(spectre::Logger::kError, "Failed to locate game_main function!");
          return EXIT_FAILURE;
        }
        else {
          (game_main);
        }
      }
    }
  }

  return EXIT_SUCCESS;*/

  /*
  std::shared_ptr<spectre::Object> obj = std::make_shared<spectre::Object>(spectre::Object());
  obj->AddComponent<spectre::TransformComponent>(spectre::TransformComponent());
  spectre::World::Instance().GetObjectManager().AddObject(obj);

  spectre::SetPosition set_pos(obj->GetID(), 0, 0, 0);
  spectre::GetPosition get_pos(obj->GetID());

  spectre::World::Instance().GetObjectManager().ExecuteCommand(std::make_shared<spectre::SetPosition>(set_pos));
  spectre::World::Instance().GetObjectManager().ExecuteCommand(std::make_shared<spectre::GetPosition>(get_pos));
  return EXIT_SUCCESS;
  */

  /*spectre::World::Instance().GetGameVariables().SetVariable("test", std::string("test"));

  std::string test = "";

  if (spectre::World::Instance().GetGameVariables().VariableExists("test")) {
    test = std::any_cast<std::string>(spectre::World::Instance().GetGameVariables().GetVariable("test"));
  }

  spectre::World::Instance().GetLogger().Log(spectre::Logger::Level::kInfo, test);*/

  /*Wren example:
  test_import.wren:
    import "other_script"
    system.print("Hello world from test_import.wren!")
  other_script.wren:
    system.print("Hello world from other_script.wren!")
  
  std::shared_ptr<spectre::Object> obj = std::make_shared<spectre::Object> (spectre::Object());
  obj->AddComponent<spectre::WrenComponent>(
    std::make_shared<spectre::WrenComponent>(spectre::WrenComponent("test_import"))
  );
  spectre::World::Instance().GetObjectManager().addOjbect(obj);
  */
  
  spectre::World::Instance().WorldLoop();

  return EXIT_SUCCESS;
}
