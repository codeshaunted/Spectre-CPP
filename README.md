# Spectre
Spectre is a work in progress open source game engine written in C++.

# Fundamental Principles
By wrapping any third party features (network engine, physics engine, scripting language), we want to allow the ability for these features to be swapped out on demand. Say, you wanted to use Havok for physics, by ensuring everything is behind a wrapper, it should be relatively easy to switch the physics system to Havok.

# Current Features
* Basic entity-component system
* Basic multithreading

# Feature Roadmap
* OpenGL renderer
* Vulkan renderer
* Scripting system
* Bullet physics system
* SLikeNet networking
