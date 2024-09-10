# dansketal

***OBS*** 
gives the correct word sometimes, pretty unreliable

To build without running

```bash
./build.bash
```

To build and run

```bash
./run.bash
```


## Config

- og_between_hundreds_and_up: Bestemmer om ordet "og" skal indsættes mellem hundreder og højere enheder (tusinder, millioner osv.) eller om det kun skal være den sidste.
- e_after_thousand: Angiver om det skal være tusind/tusinde.
- e_after_hundred: Angiver om det skal være hundred/hundrede.
- et_before_thousand: Angiver om ordet "et" skal bruges før tusinde såfremt der kun er et tusinde.
- et_before_hundred: Angiver om ordet "et" skal bruges før ordet for hundrede såfremt der kun er et hundrede.

```c
struct Config {
    occurrence og_between_hundreds_and_up;
    occurrence e_after_thousand;
    occurrence e_after_hundred;
    occurrence et_before_thousand;
    occurrence et_before_hundred;
};
```

