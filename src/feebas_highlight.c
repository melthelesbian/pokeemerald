#include "global.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "main.h"
#include "wild_encounter.h"

#define NUM_FEEBAS_SPOTS    6

void HighlightFeebasSpots() {
    u16 nWaterTiles = 447;
    u16 nFeebasGenerated = 0;
    u16 nFeebasHighlighted = 0;
    u16 currentWaterTile = 0;
    u16 feebasTiles[NUM_FEEBAS_SPOTS];
    u16 x;
    u16 y;
    u8 index;

    // Seed Feebas RNG
    FeebasSeedRng(gSaveBlock1Ptr->easyChatPairs[0].unk2);
    for(nFeebasGenerated = 0; nFeebasGenerated < NUM_FEEBAS_SPOTS; nFeebasGenerated++) {
        u16 randomTile = FeebasRandom() % nWaterTiles;
        if(randomTile == 0) {
            randomTile == nWaterTiles;
        }
        if(randomTile == 0 || randomTile > 3) {
            feebasTiles[nFeebasGenerated] = randomTile;
        }
    }

    for (y = 0; y < gMapHeader.mapLayout->height; y++) {
        for (x = 0; x < gMapHeader.mapLayout->width; x++) {
            if (MetatileBehavior_IsSurfableAndNotWaterfall(MapGridGetMetatileBehaviorAt(x, y)) == TRUE) {
                currentWaterTile++;
                if(nFeebasHighlighted < NUM_FEEBAS_SPOTS) {
                    for(index = 0; index < NUM_FEEBAS_SPOTS; index++) {
                        if(currentWaterTile == feebasTiles[index]) {
                            MapGridSetMetatileIdAt(x, y, 0x147);
                            nFeebasHighlighted++;
                        }
                    }
                }
            }
        }
    }
    return;
}
