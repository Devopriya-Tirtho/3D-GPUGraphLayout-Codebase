/*
 ==============================================================================

 RPCommon.cpp
 Copyright © 2016, 2017, 2018  G. Brinkmann

 This file is part of graph_viewer.

 graph_viewer is free software: you can redistribute it and/or modify
 it under the terms of version 3 of the GNU Affero General Public License as
 published by the Free Software Foundation.

 graph_viewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with graph_viewer.  If not, see <https://www.gnu.org/licenses/>.

 ==============================================================================
*/

#include "RPCommon.hpp"
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <fstream>
#include <string>

// by http://stackoverflow.com/a/19841704
bool is_file_exists(std::string filepath)
{
    std::ifstream infile(filepath);
    return infile.good();
}

// wrap libgen basename until C++17
std::string basename(std::string filepath)
{
    char *result_p = new char[filepath.size() + 1];
    strcpy(result_p, filepath.c_str());
    std::string result = basename(result_p);
    delete[] result_p;
    return result;
}

namespace RPGraph
{
    float get_random(float lowerbound, float upperbound)
    {
        return lowerbound + (upperbound-lowerbound) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }


    /* Definitions for Real3DVector */
    Real3DVector::Real3DVector(float x, float y, float z): x(x), y(y), z(z) {}; //Modify for z coordinate- 7th November

    float Real3DVector::magnitude()
    {
        return std::sqrt(x*x + y*y + z*z); //Modify for z coordinate- 7th November
    }

    float Real3DVector::distance(RPGraph::Real3DVector to)
    {
        const float dx = (x - to.x)*(x - to.x); //Modify for z coordinate- 7th November
        const float dy = (y - to.y)*(y - to.y); //Modify for z coordinate- 7th November
        const float dz = (z - to.z)*(z - to.z); //Modify for z coordinate- 7th November
        return std::sqrt(dx*dx + dy*dy + dz*dz); //Modify for z coordinate- 7th November
    }

    // Various operators on Real3DVector
    Real3DVector Real3DVector::operator*(float b)
    {
        return Real3DVector(this->x * b, this->y * b, this->z * b); //Modify for z coordinate- 7th November
    }

    Real3DVector Real3DVector::operator/(float b)
    {
        return Real3DVector(this->x / b, this->y / b, this->z / b); //Modify for z coordinate- 7th November
    }


    Real3DVector Real3DVector::operator+(Real3DVector b)
    {
        return Real3DVector(this->x + b.x, this->y + b.y, this->z + b.z); //Modify for z coordinate- 7th November
    }


    Real3DVector Real3DVector::operator-(Real3DVector b)
    {
        return Real3DVector(this->x - b.x, this->y - b.y, this->z - b.z); //Modify for z coordinate- 7th November
    }

    void Real3DVector::operator+=(Real3DVector b)
    {
        this->x += b.x;
        this->y += b.y;
        this->z += b.z; //Modify for z coordinate- 7th November
    }

    Real3DVector Real3DVector::getNormalized()
    {
        return Real3DVector(this->x / magnitude(), this->y / magnitude(), this->z / magnitude());//Modify for z coordinate- 7th November
    }

    Real3DVector Real3DVector::normalize()
    {
        const float m = magnitude();
        this->x /= m;
        this->y /= m;//Modify for z coordinate- 7th November
        this->z /= m;
        return *this;
    }

    /* Definitions for Coordinate */
    Coordinate::Coordinate(float x, float y, float z) : x(x), y(y), z(z) {};//Modify for z coordinate- 7th November

    // Various operators on Coordinate
    Coordinate Coordinate::operator+(float b)
    {
        return Coordinate(x + b, y + b, z+b);//Modify for z coordinate- 7th November
    }

    Coordinate Coordinate::operator*(float b)
    {
        return Coordinate(this->x*b, this->y*b, this->z*b);//Modify for z coordinate- 7th November
    }

    Coordinate Coordinate::operator/(float b)
    {
        return Coordinate(this->x/b, this->y/b, this->z/b);//Modify for z coordinate- 7th November
    }

    Coordinate Coordinate::operator+(Real3DVector b)
    {
        return Coordinate(this->x + b.x, this->y + b.y, this->z + b.z);//Modify for z coordinate- 7th November
    }

    Coordinate Coordinate::operator-(Coordinate b)
    {
        return Coordinate(this->x - b.x, this->y - b.y, this->z - b.z);//Modify for z coordinate- 7th November
    }

    bool Coordinate::operator==(Coordinate b)
    {
        return (this->x == b.x && this->y == b.y && this->z == b.z);//Modify for z coordinate- 7th November
    }

    float Coordinate::distance(RPGraph::Coordinate to)
    {
        return std::sqrt((x - to.x)*(x - to.x) + (y - to.y)*(y - to.y)+ (z - to.z)*(z - to.z));//Modify for z coordinate- 7th November
    }

    float Coordinate::distance2(RPGraph::Coordinate to)
    {
        return (x - to.x)*(x - to.x) + (y - to.y)*(y - to.y) + (z - to.z)*(z - to.z);//Modify for z coordinate- 7th November
    }

    void Coordinate::operator/=(float b)
    {
        this->x /= b;
        this->y /= b;
        //Modify for z coordinate- 7th November
        this->z /= b;
    }

    void Coordinate::operator+=(RPGraph::Coordinate b)
    {
        this->x += b.x;
        this->y += b.y;
        //Modify for z coordinate- 7th November
        this->z += b.z;
    }

    void Coordinate::operator+=(RPGraph::Real3DVector b)
    {
        this->x += b.x;
        this->y += b.y;
        //Modify for z coordinate- 7th November
        this->z += b.z;
    }
/*
    int Coordinate::quadrant()
    {//Modify for z coordinate- 7th November
        if (x <= 0)
        {
            if (y >= 0) return 0;
            else        return 3;

        }
        else
        {
            if (y >= 0) return 1;
            else        return 2;
        }
    }
*/
int Coordinate::octant()
{//Modify for z coordinate - 7th November
    int octantNumber = 0;
    if (x >= 0)
    {
        if (y >= 0)
        {
            if (z >= 0) octantNumber = 1; // x >= 0, y >= 0, z >= 0
            else        octantNumber = 5; // x >= 0, y >= 0, z < 0
        }
        else
        {
            if (z >= 0) octantNumber = 4; // x >= 0, y < 0, z >= 0
            else        octantNumber = 8; // x >= 0, y < 0, z < 0
        }
    }
    else
    {
        if (y >= 0)
        {
            if (z >= 0) octantNumber = 2; // x < 0, y >= 0, z >= 0
            else        octantNumber = 6; // x < 0, y >= 0, z < 0
        }
        else
        {
            if (z >= 0) octantNumber = 3; // x < 0, y < 0, z >= 0
            else        octantNumber = 7; // x < 0, y < 0, z < 0
        }
    }
    return octantNumber;
}

    float distance(Coordinate from, Coordinate to)
    {//Modify for z coordinate- 7th November
        const float dx = from.x - to.x;
        const float dy = from.y - to.y;
        const float dz = from.z - to.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    float distance2(Coordinate from, Coordinate to)
    {//Modify for z coordinate- 7th November
        const float dx = from.x - to.x;
        const float dy = from.y - to.y;
        const float dz = from.z - to.z;
        return dx*dx + dy*dy + dz*dz;
    }

    Real3DVector normalizedDirection(Coordinate from, Coordinate to)
    {//Modify for z coordinate- 7th November
        const float dx = from.x - to.x;
        const float dy = from.y - to.y;
        const float dz = from.z - to.z;
        const float len = std::sqrt(dx*dx + dy*dy + dz*dz);
        return Real3DVector(dx/len, dy/len, dz/len);
    }

    Real3DVector direction(Coordinate from, Coordinate to)
    {//Modify for z coordinate- 7th November
        const float dx = from.x - to.x;
        const float dy = from.y - to.y;
        const float dz = from.z - to.z;
        return Real3DVector(dx, dy, dz);
    }
}
