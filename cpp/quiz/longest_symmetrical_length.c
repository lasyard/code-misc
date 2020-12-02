#include "longest_symmetrical_length.h"

static int searchSymmetricalLength(const char *str, const char *left, const char *right)
{
    while (left >= str && *right != '\0' && *left == *right) {
        left--;
        right++;
    }
    return right - left - 1;
}

int longestSymmetricalLength(const char *str)
{
    if (str == (char *)0 || *str == '\0')
        return 0;
    int max_len = 1;
    int len;
    const char *p = str;
    while (*p != '\0') {
        len = searchSymmetricalLength(str, p, p);
        if (len > max_len)
            max_len = len;
        len = searchSymmetricalLength(str, p, p + 1);
        if (len > max_len)
            max_len = len;
        p++;
    }
    return max_len;
}
