#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void char_copy(char *dest, char *src, int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}
 
void char_move(char *dest, char *src, int n)
{

        while (n--)
            dest[n] = src[n];
    

}
 
void test_move(char *string, int d, int s, int n, char *expected)
{
    printf("- depl. %d caracteres de \"%s\" de position %d à %d. Attendu = \"%s\"\n",
           n, string, s, d, expected);
    char * tmp = strdup(string);
    char_move(tmp + d, tmp + s, n);
    if (strcmp(tmp, expected) != 0) {
        printf("ECHEC, resultat obtenu = %s\n", tmp);
    }
    free(tmp);
}
 
 
int main()
{
    printf("# tests\n");
    test_move("abcd", 0, 0, 2, "abcd");
    test_move("abcd", 1, 0, 2, "aabd");
    test_move("abcd", 2, 0, 2, "abab");
 
    test_move("abcd", 0, 1, 2, "bccd");
    test_move("abcd", 1, 1, 2, "abcd");
    test_move("abcd", 2, 1, 2, "abbc");
 
    test_move("abcd", 0, 2, 2, "cdcd");
    test_move("abcd", 1, 2, 2, "acdd");
    test_move("abcd", 2, 2, 2, "abcd");
 
    printf("# Done\n");
    return EXIT_SUCCESS;
}