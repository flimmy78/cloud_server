#ifndef __OSA_MACROS_H__
#define __OSA_MACROS_H__


/*
 * Created by Liu Papillon, on Sep 6, 2017.
 */



#define OSA_arraySize(array)                        (sizeof(array) / sizeof((array)[0]))
#define OSA_min(x, y)                               ((x) > (y) ? (y) : (x))
#define OSA_max(x, y)                               ((x) > (y) ? (x) : (y))
#define OSA_abs(x)                                  ((x) > 0 ? (x) : (-(x)))
#define OSA_isInDeviation(x, value, dev)            ((x) >= ((value) - (dev)) && (x) <= ((value) + (dev)))
#define OSA_isInRange(x, lower, upper)              ((x) >= (lower) && (x) <= (upper))
#define OSA_roundUp(x, round)                       (((x) + (round) - 1) / (round) * (round))
#define OSA_upperLimit(x, limit)                                                \
        do {                                                                    \
            if ((x) > (limit)) (x) = (limit);                                   \
        } while (0)
#define OSA_lowerLimit(x, limit)                                                \
        do {                                                                    \
            if ((x) < (limit)) (x) = (limit);                                   \
        } while (0)
#define OSA_rangeLimit(x, lower, upper)                                         \
        do {                                                                    \
            OSA_lowerLimit((x), (lower));                                       \
            OSA_upperLimit((x), (upper));                                       \
        } while (0)



#endif  /* __OSA_MACROS_H__ */

