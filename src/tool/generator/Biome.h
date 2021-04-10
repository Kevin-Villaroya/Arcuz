#ifndef __BIOME_H__
#define __BIOME_H__

#include <vector>
#include "../../model/entities/tile/poseable/AbstractPoseable.h"
#include "../../model/entities/tile/Tile.h"

class Biome{
  private:
    std::vector<std::string> poseablesName;
    std::vector<float> poseableChances;

    std::vector<TypeTile> typesTiles;
    std::vector<float> typeTileChances;

    unsigned int size;
    unsigned int averageAltitude;

    unsigned int averageOccurrence;
    unsigned int averageOccurrenceLeft;

  public:
    Biome(unsigned int size, unsigned int averageOccurrence, unsigned int averageAltitude);

    void addPoseable(const std::string& poseableName, float chance);
    void addTypeTile(TypeTile type, float chance);

    unsigned int getSize();
    unsigned int getAverageAltitude();
    unsigned int getAverageOccurrence();
    unsigned int getAverageOccurrenceLeft();

    TypeTile getTypeTile();

    AbstractPoseable* getPoseable();

    void setAverageOccurrenceLeft(unsigned int occurrence);
    void incrementeSize();
    
    void reset();

    
};


#endif