#include <string.h>
#include "graph/types.h"
#include "aclnn_cam_moe_combine_normal.h"
#include "aclnnInner_cam_moe_combine_normal.h"

enum NnopbaseHcclServerType {
    NNOPBASE_HCCL_SERVER_TYPE_AICPU = 0,
    NNOPBASE_HCCL_SERVER_TYPE_MTE,
    NNOPBASE_HCCL_SERVER_TYPE_END
};
extern "C" void __attribute__((weak)) NnopbaseSetHcclServerType(void *executor, NnopbaseHcclServerType sType);

#ifdef __cplusplus
extern "C" {
#endif

aclnnStatus aclnnCamMoeCombineNormalGetWorkspaceSize(
    const aclTensor *recvX,
    const aclTensor *tokenSrcInfo,
    const aclTensor *epRecvCounts,
    const aclTensor *recvTopkWeights,
    const aclTensor *tpRecvCountsOptional,
    char *epGroupName,
    int64_t epWorldSize,
    int64_t epRankId,
    char *tpGroupNameOptional,
    int64_t tpWorldSize,
    int64_t tpRankId,
    int64_t moeExpertNum,
    int64_t globalBs,
    const aclTensor *out,
    uint64_t *workspaceSize,
    aclOpExecutor **executor)
{
    return aclnnInnerCamMoeCombineNormalGetWorkspaceSize(recvX, tokenSrcInfo, epRecvCounts, recvTopkWeights,
                                                         tpRecvCountsOptional, epGroupName, epWorldSize, epRankId,
                                                         tpGroupNameOptional, tpWorldSize, tpRankId, moeExpertNum,
                                                         globalBs, out, workspaceSize, executor);
}

aclnnStatus aclnnCamMoeCombineNormal(
    void *workspace,
    uint64_t workspaceSize,
    aclOpExecutor *executor,
    aclrtStream stream)
{
    if (NnopbaseSetHcclServerType) {
        NnopbaseSetHcclServerType(executor, NNOPBASE_HCCL_SERVER_TYPE_MTE);
    }
    return aclnnInnerCamMoeCombineNormal(workspace, workspaceSize, executor, stream);
}

#ifdef __cplusplus
}
#endif