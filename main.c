#include "passes.h"

int main()
{
    HashMap *labels = create_hashmap(16);
    first_pass("test.txt", labels);
}