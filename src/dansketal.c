#include <stdio.h>
#include <string.h>

typedef enum {NEVER, EVERY, LAST} occurrence;
char *ones[] = {"", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
char *teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};
char *tens[] = {"", "", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};

struct Config {
    occurrence og_between_hundreds_and_up;
    occurrence e_after_thousand;
    occurrence e_after_hundred;
    occurrence et_before_thousand;
    occurrence et_before_hundred;
};

// convert tens and write it to str
void convert_tens(int n, char *s) {    
    if (n < 10) {
        sprintf(s, "%s", ones[n]);
    } else if (n < 20) {
        sprintf(s, "%s", teens[n - 10]);
    } else {
        int o = n % 10;
        int t = n / 10;
        
        if (o == 0) {
            sprintf(s, "%s", tens[t]);
        } else {
            sprintf(s, "%sog%s", ones[o], tens[t]);
        }
    }
}

// convert hundreds and down and write it to str
void convert_hundreds(int n, char *s, struct Config *cfg) {
    char *hundred = (cfg->e_after_hundred == EVERY || cfg->e_after_hundred == LAST) ? "hundrede" : "hundred";
    
    if (n == 0) {
        strcpy(s, "");
        return;
    }
    
    int h = n / 100;
    int rest = n % 100;
    char rest_str[50] = "";
    convert_tens(rest, rest_str);
    
    if (h > 0) {
        if (h == 1 && cfg->et_before_hundred != NEVER) {
            sprintf(s, "et %s", hundred);
        } else if(h == 1){
            sprintf(s, "%s", hundred);
        } else {
            sprintf(s, "%s %s", ones[h], hundred);
        }
    }
    
    if (rest > 0) {
        strcat(s, " ");
        strcat(s, rest_str);
    }
}


void dansketal(int n, char *s, struct Config *cfg) {
    char billion_str[64] = "";
    char million_str[64] = "";
    char thousand_str[64] = "";
    char hundred_str[64] = "";

    if (n == 0) {
        sprintf(s, "nul");
        return;
    }

    int billions = n / 1000000000;
    int millions = (n / 1000000) % 1000 ;
    int thousands = (n / 1000) % 1000;
    int hundreds = n % 1000;
    printf("%d\n", millions);
    if (billions > 0) {
        char *billions_part = ones[billions];
        sprintf(billion_str, "%s %s", billions_part, (billions == 1) ? "milliard" : "milliarder");
    }

    if (millions > 0) {
        char millions_part[50] = "";
        convert_hundreds(millions, millions_part, cfg);
        sprintf(million_str, "%s %s", millions_part, (millions == 1) ? "million" : "millioner");
    }

    if (thousands > 0) {
        char thousands_part[50] = "";
        convert_hundreds(thousands, thousands_part, cfg);
        sprintf(thousand_str, "%s %s", thousands_part, cfg->e_after_thousand == NEVER ? "tusind" : "tusinde");
    }

    if (hundreds > 0) {
        convert_hundreds(hundreds, hundred_str, cfg);
    }
   
    switch (cfg->og_between_hundreds_and_up)
    {
    case EVERY:
        sprintf(s, "%s%s%s%s%s%s%s", 
            (strlen(billion_str) > 0 ? billion_str : ""),
            (strlen(billion_str) > 0 ? " og " : ""),
            (strlen(million_str) > 0 ? million_str : ""),
            (strlen(million_str) > 0 ? " og " : ""), 
            (strlen(thousand_str) > 0 ? thousand_str : ""), 
            (strlen(hundred_str) > 0 ? " og " : ""), 
            (strlen(hundred_str) > 0 ? hundred_str : "")
        );
        break;
    case LAST:
        sprintf(s, "%s%s%s%s%s%s%s",
            (strlen(billion_str) > 0 ? billion_str : ""), 
            (strlen(billion_str) > 0 ? " " : ""),
            (strlen(million_str) > 0 ? million_str : ""), 
            (strlen(million_str) > 0 ? " " : ""), 
            (strlen(thousand_str) > 0 ? thousand_str : ""), 
            (strlen(hundred_str) > 0 || strlen(thousand_str) > 0 || strlen(million_str) > 0 ? " og " : ""), 
            (strlen(hundred_str) > 0 ? hundred_str : "")
        );
        break;
    case NEVER:
        sprintf(s, "%s%s%s%s%s%s%s", 
            (strlen(billion_str) > 0 ? billion_str : ""),
            (strlen(billion_str) > 0 ? " " : ""),
            (strlen(million_str) > 0 ? million_str : ""), 
            (strlen(thousand_str) > 0 ? " " : ""), 
            (strlen(thousand_str) > 0 ? thousand_str : ""), 
            (strlen(hundred_str) > 0 ? " " : ""), 
            (strlen(hundred_str) > 0 ? hundred_str : "")
        );
    default:
        break;
    }
    
}
