#include<stdio.h>

typedef enum {NEVER, EVERY, LAST} occurence;

struct Config {
    occurence og_between_hundreds_and_up;
    occurence e_after_thousand;
    occurence e_after_hundred;
    occurence et_before_thousand;
    occurence et_before_hundred;
};

void dansketal(int n, char *s, struct Config *cfg) {
    char* ones[] = {"", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
    char* teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};
    char* tens[] = {"", "ti", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};
    char* hundred = cfg->e_after_hundred == EVERY || cfg->e_after_hundred == LAST ? "hundrede" : "hundred";
    char* thousand = cfg->e_after_thousand == EVERY || cfg->e_after_thousand == LAST ? "tusinde" : "tusind"; 
    char* million = "million";
    char* billion = "milliard";
    char* millions = "millioner";
    char* billions = "milliarder";
    char* and = "og";
    char* space = " ";

    if (n == 0) {
        sprintf(s, "nul");
        return;
    }

    if (n < 10) {
        sprintf(s, "%s", ones[n]);
        return;
    }

    if (n < 20) {
        sprintf(s, "%s", teens[n-10]);
        return;
    }

    int o = n % 10;
    int t = (n / 10) % 10;
    int h = (n / 100) % 10;
    int th = (n / 1000) % 10;
    int m = (n / 1000000) % 1000;
    int b = (n / 1000000000) % 1000;

    char *o_str = ones[o];
    char *t_str = tens[t];
    char t_str_complete[50] = "";
    if(t > 0 && o > 0) {
        sprintf(t_str_complete, "%s%s%s", o_str,and, t_str);
        o_str = "";
    } else if(t > 0) {
        sprintf(t_str_complete, "%s", t_str);
    }
    
    // Hundreds
    char *h_str = h == 1 && (cfg->et_before_hundred == EVERY || cfg->et_before_hundred == LAST) ? "et" : ones[h];
    char h_str_complete[50] = "";
    if(h > 0) {
        sprintf(h_str_complete, "%s%s", h_str, hundred);
    }
    
    // Thousands
    char *th_str = th == 1 && (cfg->et_before_thousand || cfg->et_before_thousand == LAST) ? "et" : ones[th];
    char th_str_complete[50] = "";
    if(th > 0) {
        sprintf(th_str_complete, "%s%s", th_str, thousand);
    }
    
    // Millions
    char *m_str = ones[m];
    char m_str_complete[50] = "";
    if(m > 1) {
        sprintf(m_str_complete, "%s%s%s", m_str, space, millions);
    } else if(m > 0) {
        sprintf(m_str_complete, "%s%s%s", m_str, space, million);
    }
    
    // Billions
    char *b_str = ones[b];
    char b_str_complete[50] = "";
    if(b > 1) {
        sprintf(b_str_complete, "%s%s", b_str, billions);
    } else if(b > 0) {
        sprintf(b_str_complete, "%s%s", b_str, billion);
    }

    switch (cfg->og_between_hundreds_and_up)
    {
    case NEVER:
        sprintf(s, "%s%s%s%s%s%s%s%s%s%s", 
            b_str_complete, 
            space,
            m_str_complete, 
            space,
            th_str_complete, 
            space,
            h_str_complete, 
            space,
            t_str_complete, 
            o_str
        );
        break;
    case EVERY:
        char* bspace = b > 0 ? space : "";
        char* band = b > 0 ? and : "";
        char* mspace = m > 0 ? space : "";
        char* mand = m > 0 ? and : "";
        char* thspace = th > 0 ? space : "";
        char* thand = th > 0 ? and : "";
        char* hspace = h > 0 ? space : "";
        char* hand = h > 0 ? and : "";
        sprintf(s, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
            b_str_complete,
            bspace,
            band, 
            bspace,
            m_str_complete, 
            mspace,
            mand, 
            mspace,
            th_str_complete, 
            thspace,
            thand, 
            thspace,
            h_str_complete, 
            hspace,
            hand, 
            hspace,
            t_str_complete, 
            o_str
        );
        break;
    case LAST:
        sprintf(s, "%s%s%s%s%s%s%s%s%s%s%s%s", 
            b_str_complete, 
            space,
            m_str_complete, 
            space,
            th_str_complete, 
            space,
            h_str_complete, 
            space,
            and,
            space,
            t_str_complete, 
            o_str
        );
    default:
        break;
    }
}