#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#include "../include/base.h"

void random_init() {
    srand(time(NULL));
}

u64 random_uint(u64 min, u64 max) {
    if (min >= max) {
        fprintf(stderr, "Min is less than max, not allowed.\n");
    }
    u64 num = (u64)rand();
    u64 delta = max + 1 - min;
    return (num % delta) + min;
}

i64 random_int(i64 min, i64 max) {
    if (min >= max) {
        fprintf(stderr, "Min is less than max, not allowed.\n");
    }
    i64 num = rand();
    i64 delta = max + 1 - min;
    return (num % delta) + min;
}

f32 uniform_standard() {
    // Return float in interval [0, 1) (i.e 1 not included).
    return (f32)( (f64)rand() / (f64)RAND_MAX);
}

f32 uniform(f32 min, f32 max) {
    return (uniform_standard() * (max-min) ) + min;
}

f32 normal_standard() {
    // Box Muller transform
    f64 u1 = 0.0;
    do {
        u1 = (f64)uniform_standard();
    } while (u1 <= 0.0);
    f64 u2 = (f64)uniform_standard();
    return (f32)sqrt(-2.0*log(u1)) * cos(2.0*PI*u2);
}

f32 normal_dist(f32 mean, f32 std_dev) {
    return mean + normal_standard()*std_dev;
}
