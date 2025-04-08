#include <stdio.h>

bool is_slot()
{
    char s[3];
    scanf("%s", s);
    char c = s[0];
    for (int i = 1; i < 3; i++)
    {
        if (s[i] != c)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    if (is_slot())
    {
        printf("Won");
    }
    else
    {
        printf("Lost");
    }
}