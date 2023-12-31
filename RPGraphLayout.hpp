/*
 ==============================================================================

 RPGraphLayout.cpp
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

#ifndef RPGraphLayout_hpp
#define RPGraphLayout_hpp

#include "RPGraph.hpp"
#include "RPCommon.hpp"
#include <string>
//Modify for z coordinate- 14th November
namespace RPGraph
{/*
    class GraphLayout
    {
    private:
        Coordinate *coordinates;

    protected:
        float width, height;
        float minX(), minY(), maxX(), maxY();

    public:
        GraphLayout(RPGraph::UGraph &graph,
                    float width = 10000, float height = 10000);
        ~GraphLayout();

        UGraph &graph; // to lay-out

        // randomize the layout position of all nodes.
        void randomizePositions();

        float getX(nid_t node_id), getY(nid_t node_id);
        float getXRange(), getYRange(), getSpan();
        float getDistance(nid_t n1, nid_t n2);
        Real2DVector getDistanceVector(nid_t n1, nid_t n2);
        Real2DVector getNormalizedDistanceVector(nid_t n1, nid_t n2);
        Coordinate getCoordinate(nid_t node_id);
        Coordinate getCenter();


        void setX(nid_t node_id, float x_value), setY(nid_t node_id, float y_value);
        void moveNode(nid_t, Real2DVector v);
        void setCoordinates(nid_t node_id, Coordinate c);
        void writeToPNG(const int image_w, const int image_h, std::string path);
        void writeToCSV(std::string path);
        void writeToBin(std::string path);*/


    class GraphLayout
    {
    private:
        Coordinate *coordinates;

    protected:
        float width, height, depth; // Added depth for 3D
        float minX(), minY(), minZ(), maxX(), maxY(), maxZ(); // Added minZ() and maxZ()

    public:
        GraphLayout(RPGraph::UGraph &graph, float width = 10000, float height = 10000, float depth = 10000); // Added depth parameter
        ~GraphLayout();

        UGraph &graph; // to lay-out

        // Randomize the layout position of all nodes.
        void randomizePositions();

        float getX(nid_t node_id), getY(nid_t node_id), getZ(nid_t node_id); // Added getZ
        float getXRange(), getYRange(), getZRange(), getSpan(); // Added getZRange
        float getDistance(nid_t n1, nid_t n2);
        Real3DVector getDistanceVector(nid_t n1, nid_t n2); // Changed to Real3DVector
        Real3DVector getNormalizedDistanceVector(nid_t n1, nid_t n2); // Changed to Real3DVector
        Coordinate getCoordinate(nid_t node_id);
        Coordinate getCenter();

        void setX(nid_t node_id, float x_value), setY(nid_t node_id, float y_value), setZ(nid_t node_id, float z_value); // Added setZ
        void moveNode(nid_t, Real3DVector v); // Changed to Real3DVector
        void setCoordinates(nid_t node_id, Coordinate c);
        void writeToPNG(const int image_w, const int image_h, std::string path);
        void writeToCSV(std::string path);
        void writeToBin(std::string path);


    };
}

#endif /* RPGraphLayout_hpp */
