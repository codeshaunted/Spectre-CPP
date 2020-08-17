// world.cc
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

#include "world.h"

#include <chrono>

#include "logger.h"
#include "object_manager.h"
#include "transform_component.h"

namespace spectre {

void World::WorldLoop() {
	auto last_time = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::high_resolution_clock::now();

	while (true) {
		const auto current_time = std::chrono::high_resolution_clock::now();
		float delta_time = std::chrono::duration<float>(current_time - last_time).count();
		last_time = current_time;

		/* test code
		std::shared_ptr<Object> obj = std::make_shared<Object>(Object());
		GetObjectManager().AddObject(obj);
		std::shared_ptr<TransformComponent> transform_component = std::make_shared<TransformComponent>(TransformComponent());
		obj->AddComponent<TransformComponent>(transform_component);*/

		GetObjectManager().Update(delta_time);
	}
}

} // namespace spectre