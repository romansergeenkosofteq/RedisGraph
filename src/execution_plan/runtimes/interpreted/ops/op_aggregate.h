/*
* Copyright 2018-2021 Redis Labs Ltd. and Contributors
*
* This file is available under the Redis Labs Source Available License Agreement
*/

#pragma once

#include "op.h"
#include "../runtime_execution_plan.h"
#include "../../../../grouping/group_cache.h"
#include "../../../../arithmetic/arithmetic_expression.h"

typedef struct {
	RT_OpBase op;
	uint *record_offsets;               // record IDs for key and aggregate exps
	AR_ExpNode **key_exps;              // array of expressions used to calculate the group key
	AR_ExpNode **aggregate_exps;        // array of expressions that aggregate data for each key
	rax *groups;                        // map of all groups built by this operation
	Group *group;                       // last accessed group
	SIValue *group_keys;                // array of values that represent a key associated with a Group of aggregations
	CacheGroupIterator *group_iter;     // iterator for walking all groups
	uint key_count;                     // number of key expressions
	uint aggregate_count;               // number of aggregating expressions
	bool should_cache_records;          // records should be cached if we're sorting after aggregation
} RT_OpAggregate;

RT_OpBase *RT_NewAggregateOp(const RT_ExecutionPlan *plan, AR_ExpNode **exps, uint key_count, bool should_cache_records);
