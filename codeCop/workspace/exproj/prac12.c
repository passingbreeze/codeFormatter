#include <stdio.h>

int acc(int n) {
    static int s = 0;
    return s += n;
}

void count(char* s, char ch) {
    int i;

    for (i = 0; !(s[i] == '\0'); ++i)
        if (s[i] == ch)
            acc(1);
}

int main(int argc, char* argv[]) {
    char* words[] = {"abc", "a1234", "aaaa", "xxx", "axaxax"};
    int num = sizeof(words) / sizeof(words[0]);
    int i;

    for (i = 0; i < argc; ++i) {
        count(argv[i], 'a');
        printf("%s\n", argv[i]);
    }
    printf("\"a\" in prog arg: %d\n\n", acc(0));

    acc(-acc(0));
    for (i = 0; i < num; ++i) {
        count(words[i], 'a');
        printf("%s\n", words[i]);
    }
    printf("\"a\" in str array: %d\n\n", acc(0));
    return 0;
}
