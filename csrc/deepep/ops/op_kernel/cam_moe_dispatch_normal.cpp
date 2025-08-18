#include "kernel_operator.h"
#include "cam_moe_dispatch_normal_tiling.h"
#include "cam_moe_dispatch_normal.h"

using namespace AscendC;
using namespace CamMoeDispatchNormalImpl;

extern "C" __global__ __aicore__ void cam_moe_dispatch_normal(GM_ADDR x, GM_ADDR expertIds, GM_ADDR send_offset,
    GM_ADDR send_token_idx, GM_ADDR recv_offset, GM_ADDR recv_count, GM_ADDR expandXOut, GM_ADDR dynamicScalesOut,
    GM_ADDR assist_info_for_combine, GM_ADDR workspaceGM, GM_ADDR tilingGM)
{
    REGISTER_TILING_DEFAULT(CamMoeDispatchNormalTilingData);
    TPipe pipe;
#if (ORIG_DTYPE_RECV_X == DT_BF16 || ORIG_DTYPE_RECV_X == DT_FLOAT16)
    if (TILING_KEY_IS(10000)) { // 原版moe卡
        GET_TILING_DATA_WITH_STRUCT(CamMoeDispatchNormalTilingData, tilingData, tilingGM);
        CamMoeDispatchNormal<DTYPE_X, DTYPE_RECV_X, false, false, false> op;
        op.Init(x,
            expertIds,
            send_offset,
            send_token_idx,
            recv_offset,
            recv_count,
            expandXOut,
            dynamicScalesOut,
            assist_info_for_combine,
            workspaceGM,
            &pipe,
            &tilingData);
        op.Process();
        return;
    }
#elif (ORIG_DTYPE_RECV_X == DT_INT8)
    if (TILING_KEY_IS(10002)) { // 动态量化moe卡
        GET_TILING_DATA_WITH_STRUCT(CamMoeDispatchNormalTilingData, tilingData, tilingGM);
        CamMoeDispatchNormal<DTYPE_X, DTYPE_RECV_X, true, false, false> op;
        op.Init(x,
            expertIds,
            send_offset,
            send_token_idx,
            recv_offset,
            recv_count,
            expandXOut,
            dynamicScalesOut,
            assist_info_for_combine,
            workspaceGM,
            &pipe,
            &tilingData);
        op.Process();
        return;
    }
#endif
}