#include <stdio.h>

void solve()
{
    double original_price, final_price;
    scanf("%lf%lf", &original_price, &final_price);
    printf("%.3lf", (original_price - final_price) / original_price * 100.0);
}
int main()
{
    solve();
    return 0;
}