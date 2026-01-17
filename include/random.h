#pragma once
#include "../include/base.h"

void random_seed();

u64 random_uint(u64 min, u64 max);
i64 random_int(i64 min, i64 max);

f32 uniform_standard();
f32 uniform(f32 min, f32 max);

f32 normal_standard();
f32 normal_dist(f32 mean, f32 std_dev);
