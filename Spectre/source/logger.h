// logger.h
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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

namespace spectre {

class Logger {
 public:
  enum class LogLevel {
    kDebug,   //for debugging.
    kInfo,    //general info; used to make it clear what spectre is doing
    kWarning, //warnings
    kError,   //errors
    kScript,  //used to differentiate script output
  };

  Logger();
  ~Logger();

  void Log(LogLevel level, std::string message);

 private:
  std::fstream file_stream_;
  static const std::string kLoggerLevelStrings_[];
  // TODO: make these not hardcoded? (load from cfg?)
  const std::string kOutputDirectory_ = "logs";
  const std::string kLatestLog_ = "latest";
  const std::string kPreviousLog_ = "previous";
  const std::string kFileExtension_ = "log";
};

} // namespace spectre

#endif // LOGGER_H_