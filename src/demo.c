#include<stdio.h>
#include "dansketal.h"

int main() {
    char s[100];
    
    struct Config cfg = {
        .e_after_hundred = EVERY,
        .e_after_thousand = EVERY,
        .et_before_hundred = NEVER,
        .et_before_thousand = NEVER,
        .og_between_hundreds_and_up = EVERY,
    };

    dansketal(99999, s, &cfg);
    printf("%s\n", s);
}