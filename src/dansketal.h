#ifndef DANSKETAL_H
#define DANSKETAL_H
typedef enum {NEVER, EVERY, LAST} occurence;
struct Config {
    occurence og_between_hundreds_and_up;
    occurence e_after_thousand;
    occurence e_after_hundred;
    occurence et_before_thousand;
    occurence et_before_hundred;
};
void dansketal(int, char *, struct Config *cfg);
#endif