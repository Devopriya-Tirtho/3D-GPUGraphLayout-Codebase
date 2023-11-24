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


#include "RPGraphLayout.hpp"
#include "../lib/pngwriter/src/pngwriter.h"
#include <algorithm>
#include <set>
#include <fstream>
#include <cmath>
#include <limits>
#include <iostream>

namespace RPGraph
{
    GraphLayout::GraphLayout(UGraph &graph, float width, float height, float depth) //Modify for z coordinate- 16th November
        : graph(graph), width(width), height(height), depth(depth) //Modify for z coordinate- 16th November
    {
        coordinates = (Coordinate *) malloc(graph.num_nodes() * sizeof(Coordinate));
    }

    GraphLayout::~GraphLayout()
    {
        free(coordinates);
    }

    void GraphLayout::randomizePositions()
    {
        for (nid_t i = 0; i <  graph.num_nodes(); ++i)
        {
            setX(i, get_random(-width/2.0, width/2.0));
            setY(i, get_random(-height/2.0, height/2.0));
            setZ(i, get_random(-depth/2.0, depth/2.0)); // Randomize the z-coordinate //Modify for z coordinate- 16th November
        }
    }

    float GraphLayout::getX(nid_t node_id)
    {
        return coordinates[node_id].x;
    }

    float GraphLayout::getY(nid_t node_id)
    {
        return coordinates[node_id].y;
    }
    //Modify for z coordinate- 16th November
    float GraphLayout::getZ(nid_t node_id)
    {
        return coordinates[node_id].z;
    }

    float GraphLayout::minX()
    {
        float minX = std::numeric_limits<float>::max();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getX(n) < minX) minX = getX(n);
        return minX;
    }

    float GraphLayout::maxX()
    {
        float maxX = std::numeric_limits<float>::min();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getX(n) > maxX) maxX = getX(n);
        return maxX;
    }

    float GraphLayout::minY()
    {
        float minY = std::numeric_limits<float>::max();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getY(n) < minY) minY = getY(n);
        return minY;
    }

    float GraphLayout::maxY()
    {
        float maxY = std::numeric_limits<float>::min();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getY(n) > maxY) maxY = getY(n);
        return maxY;
    }

    //Modify for z coordinate- 16th November
    float GraphLayout::minZ()
    {
        float minZ = std::numeric_limits<float>::max();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getZ(n) < minZ) minZ = getZ(n);
        return minZ;
    }
    //Modify for z coordinate- 16th November
    float GraphLayout::maxZ()
    {
        float maxZ = std::numeric_limits<float>::min();
        for (nid_t n = 0; n < graph.num_nodes(); ++n)
            if (getZ(n) > maxZ) maxZ = getZ(n);
        return maxZ;
    }

    float GraphLayout::getXRange()
    {
        return maxX()- minX();
    }

    float GraphLayout::getYRange()
    {
        return maxY() - minY();
    }

    float GraphLayout::getZRange()
    {
        return maxZ() - minZ();
    }

    float GraphLayout::getSpan()
    {
        return ceil(fmaxf(fmaxf(getXRange(), getYRange()), getZRange()));//Modify for z coordinate- 16th November
    }

    float GraphLayout::getDistance(nid_t n1, nid_t n2)
    {
        const float dx = getX(n1)-getX(n2);
        const float dy = getY(n1)-getY(n2);
        const float dz = getZ(n1) - getZ(n2); // Include Z coordinate//Modify for z coordinate- 16th November
        return std::sqrt(dx*dx + dy*dy + dz*dz); // 3D distance//Modify for z coordinate- 16th November
    }

    Real3DVector GraphLayout::getDistanceVector(nid_t n1, nid_t n2)
    {
        return Real3DVector(getX(n2) - getX(n1), getY(n2) - getY(n1), getZ(n2) - getZ(n1)); // 3D distance vector
    }
//Modify for z coordinate- 16th November
    Real3DVector GraphLayout::getNormalizedDistanceVector(nid_t n1, nid_t n2)
    {
        const float x1 = getX(n1);
        const float x2 = getX(n2);
        const float y1 = getY(n1);
        const float y2 = getY(n2);
        const float z1 = getZ(n1); // Include Z coordinate
        const float z2 = getZ(n2); // Include Z coordinate
        const float dx = x2 - x1;
        const float dy = y2 - y1;
        const float dz = z2 - z1; // Include Z coordinate
        const float len = std::sqrt(dx*dx + dy*dy + dz*dz);

        return Real3DVector(dx / len, dy / len, dz / len); // Normalize 3D vector
    }
//Modify for z coordinate- 16th November
    Coordinate GraphLayout::getCoordinate(nid_t node_id)
    {
        return coordinates[node_id];
    }

    Coordinate GraphLayout::getCenter()
    {
        float x = minX() + getXRange()/2.0;
        float y = minY() + getYRange()/2.0;
        float z = minZ() + getZRange()/2.0; // Include Z coordinate
        return Coordinate(x, y, z); // Center in 3D
    }


    void GraphLayout::setX(nid_t node_id, float x_value)
    {
        coordinates[node_id].x = x_value;
    }

    void GraphLayout::setY(nid_t node_id, float y_value)
    {
        coordinates[node_id].y = y_value;
    }
//Modify for z coordinate- 16th November
    void GraphLayout::setZ(nid_t node_id, float z_value) // New method for setting Z coordinate
    {
        coordinates[node_id].z = z_value;
    }
//Modify for z coordinate- 16th November
    void GraphLayout::moveNode(nid_t n, RPGraph::Real3DVector v) // Updated to use Real3DVector
    {
        setX(n, getX(n) + v.x);
        setY(n, getY(n) + v.y);
        setZ(n, getZ(n) + v.z); // Include movement along the Z axis
    }
//Modify for z coordinate- 16th November
    void GraphLayout::setCoordinates(nid_t node_id, Coordinate c)
    {
        setX(node_id, c.x);
        setY(node_id, c.y);
        setZ(node_id, c.z); // Set Z coordinate
    }



//New Extension for Filtering Nodes and Edges
    bool shouldDisplayNode(nid_t node_id) {
        return node_id < 1259;
    }

    bool shouldDisplayEdge(nid_t source_id, nid_t target_id) {
        return (source_id < 1259) && (target_id < 1259);
    }


    // Linear interpolation function- for Continuous Coloring- 14th october
    float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    void GraphLayout::writeToPNG(const int image_w, const int image_h,
                                 std::string path)
    {
        const float xRange = getXRange();
        const float yRange = getYRange();
        const RPGraph::Coordinate center = getCenter();
        const float xCenter = center.x;
        const float yCenter = center.y;
        const float minX = xCenter - xRange/2.0;
        const float minY = yCenter - yRange/2.0;
        const float xScale = image_w/xRange;
        const float yScale = image_h/yRange;

        // Here we need to do some guessing as to what the optimal
        // opacity of nodes and edges might be, given network size.
        //const float node_opacity = 10000.0  / graph.num_nodes();
        //const float edge_opacity = 100000.0 / graph.num_edges();
        const float node_opacity = 10000.0 ;


//Inter-Chromosomal Work
/*
        //14th October,2023-Update-TO display highest 20% weighted edges for inter-chromosome edges
        std::vector<std::pair<std::pair<nid_t, nid_t>, float>> inter_chromosome_edges;
            for (nid_t n1 = 0; n1 < graph.num_nodes(); ++n1) {
                for (nid_t n2 : graph.neighbors_with_geq_id(n1)) {
                    if (shouldDisplayEdge(n1, n2) && n1 != n2) {
                        float edgeWeight = graph.get_edge_weight(n1, n2);
                        inter_chromosome_edges.push_back({{n1, n2}, edgeWeight});
                    }
                }
            }

            // Sort the edges by weight for inter-chromosome edges
            std::sort(inter_chromosome_edges.begin(), inter_chromosome_edges.end(), [](const std::pair<std::pair<nid_t, nid_t>, float>& a, const std::pair<std::pair<nid_t, nid_t>, float>& b) {
                return a.second > b.second;
            });

            // Consider only the top 25% for inter-chromosome edges
            size_t num_top_edges = inter_chromosome_edges.size() * 0.25;
            std::set<std::pair<nid_t, nid_t>> top_edges;
            for (size_t i = 0; i < num_top_edges; ++i) {
                top_edges.insert(inter_chromosome_edges[i].first);
            }

            //15th October- 2023: Taking account into 20% highest weighted edges to find the max and min from that
            float minWeight = inter_chromosome_edges[num_top_edges - 1].second;
            float maxWeight = inter_chromosome_edges[0].second;
            // If the maxWeight is 10000.0, find the next highest value that isn't 10000.0
            while (maxWeight == 10000 && !inter_chromosome_edges.empty()) {
                inter_chromosome_edges.erase(inter_chromosome_edges.begin());  // remove the top edge
                if (!inter_chromosome_edges.empty()) {
                    maxWeight = inter_chromosome_edges[0].second;  // update the maxWeight to the next top edge's weight
                    
                }
            }
            
*/

//Start of Intra-Chromosomal Setting- 30th October
        //14th October,2023-Update-TO display highest 20% weighted edges for intra-chromosome edges
        std::vector<std::pair<std::pair<nid_t, nid_t>, float>> intra_chromosome_edges;
            for (nid_t n1 = 0; n1 < graph.num_nodes(); ++n1) {
                for (nid_t n2 : graph.neighbors_with_geq_id(n1)) {
                    if (shouldDisplayEdge(n1, n2) && n1 != n2) {  // Assuming `shouldDisplayEdge` checks if n1 and n2 are from the same chromosome for intra-chromosomal edges
                        float edgeWeight = graph.get_edge_weight(n1, n2);
                        intra_chromosome_edges.push_back({{n1, n2}, edgeWeight});
                    }
                }
            }

            // Sort the edges by weight for intra-chromosome edges
            std::sort(intra_chromosome_edges.begin(), intra_chromosome_edges.end(), [](const std::pair<std::pair<nid_t, nid_t>, float>& a, const std::pair<std::pair<nid_t, nid_t>, float>& b) {
                return a.second > b.second;
            });

            // Consider only the top 25% for intra-chromosome edges
            size_t num_top_edges = intra_chromosome_edges.size() * 0.25;
            std::set<std::pair<nid_t, nid_t>> top_edges;
            for (size_t i = 0; i < num_top_edges; ++i) {
                top_edges.insert(intra_chromosome_edges[i].first);
            }

            //15th October- 2023: Taking account into 20% highest weighted edges to find the max and min from that
            float minWeight = intra_chromosome_edges[num_top_edges - 1].second;
            float maxWeight = intra_chromosome_edges[0].second;
            // If the maxWeight is 10000.0, find the next highest value that isn't 10000.0
            while (maxWeight == 10000 && !intra_chromosome_edges.empty()) {
                intra_chromosome_edges.erase(intra_chromosome_edges.begin());  // remove the top edge
                if (!intra_chromosome_edges.empty()) {
                    maxWeight = intra_chromosome_edges[0].second;  // update the maxWeight to the next top edge's weight
                }
            }
//End of Intra-Chromosomal Setting
        
        //const float edge_opacity = 0.01;
        float edge_opacity = 0.01;
        // Write to file.
        pngwriter layout_png(image_w, image_h, 0, path.c_str());
        layout_png.invert(); // set bg. to white

    for (nid_t n1 = 0; n1 < graph.num_nodes(); ++n1)
    {
            // for (nid_t n2 : graph.neighbors_with_geq_id(n1)) {
            //     // ... and edge.
            //     if (shouldDisplayEdge(n1, n2)){
            //     layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
            //                           (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
            //                           edge_opacity, 17400, 17700, 17600);}
            // }
        for (nid_t n2 : graph.neighbors_with_geq_id(n1)) {
            if (top_edges.count({n1, n2}) > 0) {
                float edgeWeight = graph.get_edge_weight(n1, n2);

                // Working on Edge Opacity
                if (edgeWeight < 10000.0) {
                    edge_opacity = edgeWeight / maxWeight * 2;

                    //15th OCtober Update- Fixing edge opacity to see if color blending works or not
                    //edge_opacity = 0.5;
                } else {
                    edge_opacity = 1;
                }

                // Scale the weight between 0 (green) and 1 (red)
                float t;
                if(edgeWeight!=10000.0){
                    t = (edgeWeight - minWeight) / (maxWeight - minWeight);
                }
                else{
                    t = 0.3;
                }
                



                

                // Calculate the RGB values based on weight
                int red = lerp(0, 65535, t);
                //std::cout << "Value of red: " << red << std::endl;
                int green = lerp(65535, 0, t);
                //std::cout << "Value of green: " << green << std::endl;
                int blue = 0;  // Constant for simplicity.
/* For Inter Chromosomal Setting- 30th October
                if ((n1 > 0 && n1 <= 558) && (n2 > 0 && n2 <= 558)) {
                    layout_png.line_blend((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
                                        (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
                                        edge_opacity, red, green, 0);
                } else if ((n1 > 1012 && n1 <= 1258) && (n2 > 1012 && n2 <= 1258)) {
                    // You can update this block and others similarly if you want different coloring based on different node ranges.
                    layout_png.line_blend((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
                                        (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
                                        edge_opacity, red, green, 0);
                } else if ((n1 > 558 && n1 <= 1012) && (n2 > 558 && n2 <= 1012)) {
                    layout_png.line_blend((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
                                        (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
                                        edge_opacity, red, green, 0);
                }
*/
//For intra-chromosomal setting- 30th October
                if ((n1> 0 && n1 <= 558) && (n2>558 && n2 <= 1012))
                {
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);

                }
                else if ((n1> 0 && n1 <= 558) && (n2>1012 && n2 <= 1258))
                {
                    // Plot edge with blue color
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);
                }
                else if ((n1> 558 && n1 <= 1012) && (n2>0 && n2 <= 558))
                {
                    // Plot edge with blue color
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);
                }
                else if ((n1> 558 && n1 <= 1012) && (n2>1012 && n2 <= 1258))
                {
                    // Plot edge with blue color
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);
                }
                else if ((n1> 1012 && n1 <= 1258) && (n2>0 && n2 <= 558))
                {
                    // Plot edge with blue color
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);
                }
                else if ((n1> 1012 && n1 <= 1258) && (n2>558 && n2 <= 1012))
                {
                    // Plot edge with blue color
                                    layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
                                      (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
                                      edge_opacity, red, green, 0);
                }
                //
            }
        }

        //         //Intra Interaction

        //         if ((n1> 0 && n1 <= 558) && (n2>0 && n2 <= 558))
        //         {
        //             // Plot edge with red color
        //             layout_png.line((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
        //                             (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
        //                             0, 0, 0);
        //         }
        //         else if ((n1> 558 && n1 <= 1012) && (n2>558 && n2 <= 1012))
        //         {
        //             // Plot edge with green color
        //             layout_png.line((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
        //                             (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
        //                             0, 0, 0);
        //         }
        //         else if ((n1> 1012 && n1 <= 1258) && (n2>1012 && n2 <= 1258))
        //         {
        //             // Plot edge with blue color
        //             layout_png.line((getX(n1) - minX) * xScale, (getY(n1) - minY) * yScale,
        //                             (getX(n2) - minX) * xScale, (getY(n2) - minY) * yScale,
        //                             0, 0, 0);
        //         }
        //     }
        // }

        if (shouldDisplayNode(n1))
        {
            // Plot node
            if (n1 <= 558)
            {            
                layout_png.filledcircle((getX(n1) - minX)*xScale,
                                       (getY(n1) - minY)*yScale,
                                       5, 6000000, 0, 0);
                           
            // Update on 20th June- Checking for edge_list_Combined_with_NewYT_normalized (Replaced bins 200 to 400)- Making these black to see 
            //what happens to the replaced bins 

            //Update on 11 July- Replaced bins at 200-400, 600-800, 1000-1200... Making black nodes for those 3 parts
            // if (n1 >=200 && n1 <=400)
            // {            
            //     layout_png.filledcircle((getX(n1) - minX)*xScale,
            //                            (getY(n1) - minY)*yScale,
            //                            5, 0, 0, 0);
                                    

            // }               

            }
            else if (n1 > 558 && n1 <= 1012)
            {
                layout_png.filledcircle((getX(n1) - minX)*xScale,
                                       (getY(n1) - minY)*yScale,
                                       5, 0, 0, 6000000);

            //     if (n1 >=600 && n1 <=800)
            // {            
            //     layout_png.filledcircle((getX(n1) - minX)*xScale,
            //                            (getY(n1) - minY)*yScale,
            //                            5, 0, 0, 0);
                                    

            // }  

            }

            else if (n1 > 1012 && n1 <= 1258)
            {
                layout_png.filledcircle((getX(n1) - minX)*xScale,
                                       (getY(n1) - minY)*yScale,
                                       5, 0, 6000000, 0);

            //     if (n1 >=1000 && n1 <=1200)
            // {            
            //     layout_png.filledcircle((getX(n1) - minX)*xScale,
            //                            (getY(n1) - minY)*yScale,
            //                            5, 0, 0, 0);
                                    

            // } 

            }

        }

        //Inter-Interaction


    }
        // Write it to disk.
        layout_png.write_png();
    }


    // void GraphLayout::writeToPNG(const int image_w, const int image_h,
    //                              std::string path)
    // {
    //     const float xRange = getXRange();
    //     const float yRange = getYRange();
    //     const RPGraph::Coordinate center = getCenter();
    //     const float xCenter = center.x;
    //     const float yCenter = center.y;
    //     const float minX = xCenter - xRange/2.0;
    //     const float minY = yCenter - yRange/2.0;
    //     const float xScale = image_w/xRange;
    //     const float yScale = image_h/yRange;

    //     // Here we need to do some guessing as to what the optimal
    //     // opacity of nodes and edges might be, given network size.
    //     const float node_opacity = 10000.0  / graph.num_nodes();
    //     //const float edge_opacity = 100000.0 / graph.num_edges();
    //     const float edge_opacity = 0.0;
    //     // Write to file.
    //     pngwriter layout_png(image_w, image_h, 0, path.c_str());
    //     layout_png.invert(); // set bg. to white

    //     for (nid_t n1 = 0; n1 < graph.num_nodes(); ++n1)
    //     {
    //         // Plot node,
    //         layout_png.filledcircle_blend((getX(n1) - minX)*xScale,
    //                                       (getY(n1) - minY)*yScale,
    //                                       3, node_opacity, 500000, 45, 200);
    //         for (nid_t n2 : graph.neighbors_with_geq_id(n1)) {
    //             // ... and edge.
    //             layout_png.line_blend((getX(n1) - minX)*xScale, (getY(n1) - minY)*yScale,
    //                                   (getX(n2) - minX)*xScale, (getY(n2) - minY)*yScale,
    //                                   edge_opacity, 45, 200, 150);
    //         }
    //     }
    //     // Write it to disk.
    //     layout_png.write_png();
    // }

//Modify for z coordinate- 16th November

    void GraphLayout::writeToCSV(std::string path)
    {
        if (is_file_exists(path.c_str()))
        {
            printf("Error: File exists at %s\n", path.c_str());
            exit(EXIT_FAILURE);
        }

        std::ofstream out_file(path);

        for (nid_t n = 0; n < graph.num_nodes(); ++n)
        {
            nid_t id = graph.node_map_r[n]; // id as found in edgelist
            out_file << id << "," << getX(n) << "," << getY(n) << "," << getZ(n) << "\n"; // Include Z coordinate
        }

        out_file.close();
    }

    void GraphLayout::writeToBin(std::string path)
    {
        if (is_file_exists(path.c_str()))
        {
            printf("Error: File exists at %s\n", path.c_str());
            exit(EXIT_FAILURE);
        }

        std::ofstream out_file(path, std::ofstream::binary);

        for (nid_t n = 0; n < graph.num_nodes(); ++n)
        {
            nid_t id = graph.node_map_r[n]; // id as found in edgelist
            float x = getX(n);
            float y = getY(n);

            out_file.write(reinterpret_cast<const char*>(&id), sizeof(id));
            out_file.write(reinterpret_cast<const char*>(&x), sizeof(x));
            out_file.write(reinterpret_cast<const char*>(&y), sizeof(y));
        }

        out_file.close();
    }

}
