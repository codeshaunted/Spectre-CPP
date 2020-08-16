// subject.h
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

#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>
#include <algorithm>
#include <map>
#include <memory>

#include "event_id.h"
#include "observer.h"

namespace spectre {

class Subject {
public:
  void add_observer(std::shared_ptr<Observer> observer);
  void remove_observer(std::shared_ptr<Observer> observer);
private:
  std::vector<std::shared_ptr<spectre::Observer>> observers;
protected:
  void notify(const Object& object, spectre::EventID event);
};

} // namespace spectre

#endif // SUBJECT_H_