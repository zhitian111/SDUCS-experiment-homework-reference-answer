#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", b + i);
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i] * b[i];
    }
    if (sum == 0)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}

int main()
{
    solve();
    return 0;
}