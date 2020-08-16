// subject.cc
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

#include "subject.h"

namespace spectre {

void Subject::add_observer(std::shared_ptr<Observer> observer) {
  observers.push_back(observer);
}

void Subject::remove_observer(std::shared_ptr<Observer> observer) {
  std::vector<std::shared_ptr<spectre::Observer>>::iterator position = std::find(observers.begin(), observers.end(), observer);
  if (position != observers.end()) {
    observers.erase(position);
  }
}

void Subject::notify(const Object& object, spectre::EventID event)
{
  for (int i = 0; i < observers.size(); i++)
  {
    observers[i]->on_notify(object, event);
  }
}

} // namespace spectre
