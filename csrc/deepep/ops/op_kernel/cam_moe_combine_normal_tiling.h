#ifndef CAM_MOE_CMOBINE_NORMAL_TILING_H
#define CAM_MOE_CMOBINE_NORMAL_TILING_H

#include <cstdint>
#include "kernel_tiling/kernel_tiling.h"

// a3
struct CamMoeCombineNormalInfo {
    uint32_t epWorldSize;
    uint32_t tpWorldSize;
    uint32_t epRankId;
    uint32_t tpRankId;
    uint32_t expertShardType;
    uint32_t moeExpertNum;
    uint32_t moeExpertPerRankNum;
    uint32_t globalBs;
    uint32_t bs;
    uint32_t k;
    uint32_t h;
    uint32_t aivNum;
    uint64_t totalUbSize;
    uint64_t totalWinSize;
    float armAvgFactor;
    float epsilon;
};
struct CamMoeCombineNormalTilingData {
    Mc2InitTiling mc2InitTiling;
    Mc2CcTiling mc2CcTiling1;
    Mc2CcTiling mc2CcTiling2;
    CamMoeCombineNormalInfo camMoeCombineNormalInfo;
};

#endif //__MOE_CMOBINE_TILING_H__