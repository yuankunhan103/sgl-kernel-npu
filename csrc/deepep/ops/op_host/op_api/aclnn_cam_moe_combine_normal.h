#ifndef ACLNN_CAM_MOE_COMBINE_NORMAL_H_
#define ACLNN_CAM_MOE_COMBINE_NORMAL_H_

#include "aclnn/acl_meta.h"

#ifdef __cplusplus
extern "C" {
#endif

/* funtion: aclnnMoeCombineGetWorkspaceSize
 * expandX : required
 * expandIdx : required
 * epSendCounts : required
 * expertScales : required
 * tpSendCountsOptional : optional
 * groupEp : required
 * epWorldSize : required
 * epRankId : required
 * moeExpertNum : required
 * groupTpOptional : optional
 * tpWorldSize : optional
 * tpRankId : optional
 * globalBs : optional
 * out : required
 * workspaceSize : size of workspace(output).
 * executor : executor context(output).
 */
__attribute__((visibility("default"))) aclnnStatus aclnnCamMoeCombineNormalGetWorkspaceSize(
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
                                            aclOpExecutor **executor);

/* funtion: aclnnMoeCombine
 * workspace : workspace memory addr(input).
 * workspaceSize : size of workspace(input).
 * executor : executor context(input).
 * stream : acl stream.
 */
__attribute__((visibility("default"))) aclnnStatus aclnnCamMoeCombineNormal(
                                            void *workspace,
                                            uint64_t workspaceSize,
                                            aclOpExecutor *executor,
                                            aclrtStream stream);

#ifdef __cplusplus
}
#endif

#endif