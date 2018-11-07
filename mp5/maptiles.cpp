/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     //construct the KDTree of Dim=3 where each val in the Point is a val from HSLAPixel
     vector<Point<3>> avgColorsPoints;
     map<Point<3>, int> tile_avg_map;
     for (size_t i = 0; i < theTiles.size(); i++)
     {
       HSLAPixel avg = theTiles[i].getAverageColor();
       avg.h/=360;
       Point<3> color = Point<3>(avg.h, avg.s, avg.l);
       avgColorsPoints.push_back(color);
       tile_avg_map.insert(pair<Point<3>, int>(color, i));
     }

     KDTree<3> avgColorTree = KDTree<3>(avgColorsPoints);

     MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     for (int x = 0; x < mosaic->getRows(); x++)
     {
       for (int y = 0; y < mosaic->getColumns(); y++)
       {
         TileImage* toInsert = get_match_at_idx(avgColorTree, tile_avg_map, theTiles, theSource, x, y);
         mosaic->setTile(x, y, toInsert);
       }
     }

    return mosaic;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
