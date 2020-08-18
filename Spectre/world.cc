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
#include <vector>
#include <thread>
#include <algorithm>

#include "transform_component.h"

namespace spectre {

void World::WorldLoop() {
	const auto logical_processor_count = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	auto last_time = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::high_resolution_clock::now();

	while (true) {
		const auto current_time = std::chrono::high_resolution_clock::now();
		float delta_time = std::chrono::duration<float>(current_time - last_time).count();
		last_time = current_time;

		std::vector<std::stack<std::shared_ptr<Component>>> component_stacks;

		// TODO: make multi-threading optional

		GetObjectManager().Update(delta_time);

		for (int i = 0; i < logical_processor_count; ++i) {
			component_stacks.push_back(std::stack<std::shared_ptr<Component>>());
		}

		// TODO: make a smarter load-balancer
		int processor_iterator = 0;
		for (int i = 0; i < update_queue_.size(); ++i) {
			if (processor_iterator == logical_processor_count) processor_iterator = 0;
			component_stacks[processor_iterator].push(update_queue_[i]);
			++processor_iterator;
		}

		for (int i = 0; i < logical_processor_count; ++i) {
			std::thread update_thread(&World::UpdateThread, this, component_stacks[i], delta_time);
			threads.push_back(std::move(update_thread));
		}


		for (std::thread& thread : threads) {
			thread.join();
		}

		threads.clear();

		update_queue_.clear();
	}
}

void World::UpdateThread(std::stack<std::shared_ptr<Component>> components, float delta_time) {
	while (!components.empty()) {
		components.top()->Update(delta_time);
		components.pop();
	}
}

} // namespace spectre