// internal_types.cc
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

#include "internal_types.h"

namespace spectre {
  // Constructors

  Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
  Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

  Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Quaternion::Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

  Vector3::Vector3(const Vector3 &incomingVector) : x(incomingVector.x), y(incomingVector.y), z(incomingVector.z) { ; }
  Quaternion::Quaternion(const Quaternion &incomingQuaternion) : x(incomingQuaternion.x), y(incomingQuaternion.y), z(incomingQuaternion.z),  w(incomingQuaternion.w) {;}

  Vector3::Vector3(float array[3]) : x(array[0]), y(array[1]), z(array[2]) {}
  Quaternion::Quaternion(float array[4]) : x(array[0]), y(array[1]), z(array[2]), w(array[3]) {}


  Vector3::Vector3(btVector3 btValue) : x(btValue.getX()), y(btValue.getY()), z(btValue.getZ()) {}
  Quaternion::Quaternion(btQuaternion btValue) : x(btValue.getX()), y(btValue.getY()), z(btValue.getZ()), w(btValue.getW()) {}

  btVector3 Vector3::GetbtVector3() const { return btVector3(this->x, this->y, this->z); }
  btQuaternion Quaternion::GetbtQuaternion() { return btQuaternion(this->x, this->y, this->z, this->w); }

  // Operator functions

  // Equals Operator
  bool Vector3::operator==(const Vector3 &other) const {
    return fabs(this->x - other.x) <= ((fabs(this->x) > fabs(other.x) ? fabs(other.x) : fabs(this->x)) * std::numeric_limits<float>::epsilon())
      && fabs(this->y - other.y) <= ((fabs(this->y) > fabs(other.y) ? fabs(other.y) : fabs(this->y)) * std::numeric_limits<float>::epsilon())
      && fabs(this->z - other.z) <= ((fabs(this->z) > fabs(other.z) ? fabs(other.z) : fabs(this->z)) * std::numeric_limits<float>::epsilon());
  }
  bool Quaternion::operator==(const Quaternion &other) const {
    return fabs(this->x - other.x) <= ((fabs(this->x) > fabs(other.x) ? fabs(other.x) : fabs(this->x)) * std::numeric_limits<float>::epsilon())
           && fabs(this->y - other.y) <= ((fabs(this->y) > fabs(other.y) ? fabs(other.y) : fabs(this->y)) * std::numeric_limits<float>::epsilon())
           && fabs(this->z - other.z) <= ((fabs(this->z) > fabs(other.z) ? fabs(other.z) : fabs(this->z)) * std::numeric_limits<float>::epsilon())
           && fabs(this->w - other.w) <= ((fabs(this->w) > fabs(other.w) ? fabs(other.w) : fabs(this->w)) * std::numeric_limits<float>::epsilon());
  }

  // Not Equals Operator
  bool Vector3::operator!=(const Vector3& other) const { return !(this->operator==(other)); }
  bool Quaternion::operator!=(const Quaternion &other) const { return !(this->operator==(other)); }


}