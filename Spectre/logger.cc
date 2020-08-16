// logger.cc
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

#include "logger.h"

#include <chrono>
#include <iostream>
#include <filesystem>
#include <sstream>

// TODO: extend the logger

namespace spectre {

const std::string Logger::logger_level_strings_[] = {
  "DEBUG",
  "INFO",
  "WARNING",
  "ERROR"
};

Logger::Logger() {
  if (!std::filesystem::exists(output_directory_)) std::filesystem::create_directory(output_directory_);

  if (std::filesystem::exists(output_directory_ + "/" + latest_log_ + "." + file_extension_)) {
    // Read previous log
    std::string previous_log_data;

    file_stream_.open(output_directory_ + "/" + latest_log_ + "." + file_extension_);
    file_stream_.seekg(0, std::ios::end);
    previous_log_data.reserve(file_stream_.tellg());
    file_stream_.seekg(0, std::ios::beg);
    previous_log_data.assign((std::istreambuf_iterator<char>(file_stream_)), std::istreambuf_iterator<char>());
    file_stream_.close();

    // Write to previous log file
    file_stream_.open(output_directory_ + "/" + previous_log_ + "." + file_extension_, std::ios::out, std::ios::trunc);
    file_stream_.write(previous_log_data.c_str(), previous_log_data.size());
    file_stream_.close();
  }

  // Open current log file
  file_stream_.open(output_directory_ + "/" + latest_log_ + "." + file_extension_, std::ios::out, std::ios::trunc);
}

Logger::~Logger() {
  if (file_stream_.is_open()) file_stream_.close();
}

void Logger::Log(Level level, std::string message) {
  auto current_time = std::chrono::system_clock::now();
  time_t time = std::chrono::system_clock::to_time_t(current_time);
  struct tm local_time;

  #ifdef __unix__
      localtime_r(&time, &local_time);
  #elif _WIN32
      localtime_s(&local_time, &time);
  #else
      local_time = *localtime(&time); // this is BAD because localtime is NOT threadsafe, hence the preprocessor directive for the win32/*nix alternatives
  #endif

  char time_string [70];
  strftime(time_string, sizeof(time_string), "%d-%m-%y %H:%M:%S", &local_time);

  std::stringstream log_message;
  log_message << time_string << " [" << logger_level_strings_[level] << "] " << message << std::endl;

  std::cout << log_message.str();
  file_stream_.write(log_message.str().c_str(), log_message.str().size());
}

} // namespace spectre