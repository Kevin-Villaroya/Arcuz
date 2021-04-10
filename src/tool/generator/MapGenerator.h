#ifndef __MAP_GENERATOR_H__
#define __MAP_GENERATOR_H__

#include "Biome.h"
#include "../../model/map/Map.h"
#include "../../model/entities/tile/poseable/tree/Tree.h"

class MapGenerator{
  private:
    static const float PERCENT_MAX_EXTENSION_BIOME;
    static const float PERCENT_MIN_EXTENSION_BIOME;
    static const float PERCENT_EXTENSION_CHANCE[4];

    std::vector<std::vector<int>> generatedMap;
    std::vector<std::vector<int>> alreadyVisited;//0 = false, 1 = true, 2 = temporary

    bool firstBiome;

    unsigned int sizeMin;

    std::vector<Biome> biomes;

    void initSizeMap();
    void randomizeNumberOfBiomes();

    void addOutline();
    void generatePoseables(Map& map);

    void deleteUnusedMap();
    void deleteRowMap(unsigned int row);
    void deleteColumnMap(unsigned int column);

    void setTileToBiome(sf::Vector2u posTile, Biome& biome);
    void tryToconvert(sf::Vector2u posTile, Biome& biome, float chance);

    void resetGenerator();

    void convertTemporaryTo(int value);

  public:
    MapGenerator(unsigned int sizeMin);

    void generateMap();
    void generateMapProcess();
    void addBiome(const Biome biome);

    Biome& selectRandomBiome();
    sf::Vector2u selectTileFor(Biome& biome);
    void expandBiome(Biome& biome, sf::Vector2u posTile);

    int getIdBiome(Biome& biome);

    bool allBiomesAreGenerated();
    void createMap(Map& map);

    void displayGeneratedMap();

};

#endif