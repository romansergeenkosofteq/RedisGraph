/*
* Copyright 2018-2021 Redis Labs Ltd. and Contributors
*
* This file is available under the Redis Labs Source Available License Agreement
*/

#include "op_index_scan.h"
#include "../../query_ctx.h"
#include "shared/print_functions.h"
#include "../../filter_tree/ft_to_rsq.h"

// forward declarations
static void IndexScanFree(OpBase *opBase);

static void IndexScanToString(const OpBase *ctx, sds *buf) {
	IndexScan *op = (IndexScan *)ctx;
	return ScanToString(ctx, buf, op->n.alias, op->n.label);
}

OpBase *NewIndexScanOp(const ExecutionPlan *plan, NodeScanCtx n,
		FT_FilterNode *filter) {
	// validate inputs
	ASSERT(plan   != NULL);
	ASSERT(filter != NULL);

	IndexScan *op = rm_malloc(sizeof(IndexScan));
	op->n                    =  n;
	op->filter               =  filter;

	// Set our Op operations
	OpBase_Init((OpBase *)op, OPType_INDEX_SCAN, "Index Scan",
		IndexScanToString, IndexScanFree, false, plan);

	return (OpBase *)op;
}

static void IndexScanFree(OpBase *opBase) {
	IndexScan *op = (IndexScan *)opBase;
	if(op->filter) {
		FilterTree_Free(op->filter);
		op->filter = NULL;
	}
}
