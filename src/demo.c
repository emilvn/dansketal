#include<stdio.h>
#include "dansketal.h"

int main() {
    char s[256];
    
    struct Config cfg = {
        .e_after_hundred = EVERY,
        .e_after_thousand = EVERY,
        .et_before_hundred = EVERY,
        .et_before_thousand = EVERY,
        .og_between_hundreds_and_up = LAST,
    };

    dansketal(2122999999, s, &cfg);
    printf("%s\n", s);
}