/*
 * Copyright 2018-2021 Redis Labs Ltd. and Contributors
 *
 * This file is available under the Redis Labs Source Available License Agreement
 */

#pragma once

#include "op.h"
#include "../runtime_execution_plan.h"

typedef struct {
	RT_OpBase op;
	unsigned int limit;     // Max number of records to consume.
	AR_ExpNode *limit_exp;  // Expression evaluated to limit.
	unsigned int consumed;  // Number of records consumed so far.
} RT_OpLimit;

// Limits number of produced records
RT_OpBase *RT_NewLimitOp(const RT_ExecutionPlan *plan, AR_ExpNode *limit_exp);
