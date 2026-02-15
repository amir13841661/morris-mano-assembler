#include "passes.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <source_file.asm>\n", argv[0]);
        return 1;
    }
    char *filepath = argv[1];
    HashMap *labels = create_hashmap(16);
    first_pass(filepath, labels);
    second_pass(filepath, labels, "output.txt");
}