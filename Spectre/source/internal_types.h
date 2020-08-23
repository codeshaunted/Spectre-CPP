// internal_types.h
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

#ifndef SPECTRE_INTERNAL_TYPES_H
#define SPECTRE_INTERNAL_TYPES_H

#include "../third_party/bullet3/src/btBulletDynamicsCommon.h"
#include <cmath>

namespace spectre {
  class Vector3 {
  public:
    btScalar x = 0.0f; // Replace these with Floats when removing bullet
    btScalar y = 0.0f;
    btScalar z = 0.0f;


    Vector3();
    Vector3(float _x, float _y, float _z);
    Vector3(const Vector3 &incomingVector);
    Vector3(float array[3]);
    Vector3(btVector3 btValue);

    btVector3 GetbtVector3() const;

    bool operator==(const Vector3 &other) const;
    bool operator!=(const Vector3& other) const;
  };

  class Quaternion {
  public:
    btScalar x = 0.0f;
    btScalar y = 0.0f;
    btScalar z = 0.0f;
    btScalar w = 0.0f;

    Quaternion();
    Quaternion(float _x, float _y, float _z, float _w);
    Quaternion(const Quaternion &incomingQuaternion);
    Quaternion(float array[4]);
    Quaternion(btQuaternion btValue);

    btQuaternion GetbtQuaternion();

    bool operator==(const Quaternion &other) const;
    bool operator!=(const Quaternion &other) const;
  };
}

#endif //SPECTRE_INTERNAL_TYPES_H
