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
    RT_OpBase *stream;     // Current stream to pull from.
    int streamIdx;      // Current stream index.
} RT_OpJoin;

RT_OpBase *RT_NewJoinOp(const RT_ExecutionPlan *plan);
