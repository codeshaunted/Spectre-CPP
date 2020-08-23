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


namespace spectre {

void World::WorldLoop() {
	//const auto logical_processor_count = std::thread::hardware_concurrency();
	//std::vector<std::thread> threads;
	auto last_time = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::high_resolution_clock::now();

	/*for (int i = 0; i < logical_processor_count; ++i) {
		std::thread update_thread(&World::UpdateThread, this, i);
		threads.push_back(std::move(update_thread));
	}

	for (int i = 0; i < logical_processor_count; ++i) {
		component_stacks_.push_back(std::stack<std::shared_ptr<Component>>());
	}

	for (std::thread& thread : threads) {
		thread.detach();
	}*/

	while (true) {
		const auto current_time = std::chrono::high_resolution_clock::now();
		current_delta_time_ = std::chrono::duration<float>(current_time - last_time).count();
		last_time = current_time;

		// TODO: make multi-threading optional
		GetObjectManager().Update(current_delta_time_);

	//	// TODO: make a smarter load-balancer
	//	int processor_iterator = 0;
	//	for (int i = 0; i < update_queue_.size(); ++i) {
	//		if (processor_iterator == logical_processor_count) processor_iterator = 0;
	//		component_stacks_[processor_iterator].push(update_queue_[i]);
	//		++processor_iterator;
	//	}

	//	update_queue_.clear();

	//	for (std::stack<std::shared_ptr<Component>> component_stack : component_stacks_) {
	//		while (!component_stack.empty()); // wait for threads to finish to continue
	//	}
	}
}

void World::UpdateThread(int component_stack) {
	while (true) {
		if (component_stacks_[component_stack].empty()) continue;
		component_stacks_[component_stack].top()->Update(current_delta_time_);
		component_stacks_[component_stack].pop();
	}
}

} // namespace spectre