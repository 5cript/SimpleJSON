#ifndef INTEGER_OF_SIZE_H_INCLUDED
#define INTEGER_OF_SIZE_H_INCLUDED

#include <cstdint>

template <unsigned s>
struct int_of_size
{
    typedef int type;
};

template <unsigned s>
struct uint_of_size
{
    typedef int type;
};

#define __I_OF_SIZE(SIZE, TYPE)     \
template <>                         \
struct int_of_size<(SIZE)>          \
{                                   \
    typedef TYPE type;              \
};                                  \
                                    \
template <>                         \
struct uint_of_size<(SIZE)>         \
{                                   \
    typedef u##TYPE type;           \
};
// END OF MAKRO


__I_OF_SIZE(sizeof(int8_t), int8_t)
__I_OF_SIZE(sizeof(int16_t), int16_t)
__I_OF_SIZE(sizeof(int32_t), int32_t)
__I_OF_SIZE(sizeof(int64_t), int64_t)

#endif // INTEGER_OF_SIZE_H_INCLUDED
