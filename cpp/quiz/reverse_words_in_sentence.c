#include <string.h>

#include "reverse_words_in_sentence.h"

static void reverseString(char *begin, char *end)
{
    char *p, *q;
    for (p = begin, q = end - 1; p < q; p++, q--) {
        char tmp = *p;
        *p = *q;
        *q = tmp;
    }
}

void reverseWordsInSentence(char *text)
{
    if (text == NULL)
        return;
    int len = strlen(text);
    reverseString(text, text + len);
    for (char *p = text, *q; *p != '\0';) {
        if (*p == ' ') {
            p++;
            continue;
        }
        for (q = p + 1; *q != '\0' && *q != ' '; q++)
            ;
        reverseString(p, q);
        if (*q == '\0')
            break;
        p = q + 1;
    }
}
