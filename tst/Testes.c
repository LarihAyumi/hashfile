#include <stdio.h>
#include "../src/HashFile.h"

int main() {

    HashFile* h = createFile("teste");

    int v;

    insertRegister(h, 1, 100);
    insertRegister(h, 2, 200);
    insertRegister(h, 3, 300);
    insertRegister(h, 4, 400); // pra dar split

    if (searchRegister(h, 3, &v) == 0)
        printf("Encontrou: %d\n", v);

    removeRegister(h, 3);

    if (searchRegister(h, 3, &v) != 0)
        printf("Removido com sucesso\n");

    closeFile(h);

    return 0;
}