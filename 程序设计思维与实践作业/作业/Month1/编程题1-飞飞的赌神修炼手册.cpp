#include <iostream>
#include <algorithm>
// #include <stdio.h>
using namespace std;

class card
{
public:
    int num;
    int type;
};
bool compare_by_num(const card& a, const card& b)
{
    return a.num < b.num;
}

bool compare_by_type(const card& a,const card& b)
{
    return a.type < b.type;
}


class hand
{
public:
    card cards[5];
    hand();
    bool straight_flush = false;
    bool four_of_a_kind = false;
    bool full_house = false;
    bool flush = false;
    bool straight = false;
    bool three_of_a_kind = false;
    bool two_pair = false;
    bool one_pair = false;
    bool high_card = false;
    int type = 0;
    void check();
    void sort_by_num();
    void sort_by_type();

    void disp() const;
    void add_card(card& c);
    void add_card(int num, int type);
    int count;
};

hand::hand()
{
    count = 0;
}

void hand::add_card(card& c)
{
    cards[count] = c;
    count++;
}

void hand::check()
{
    //reset
    straight_flush = false;
    four_of_a_kind = false;
    full_house = false;
    flush = false;
    straight = false;
    three_of_a_kind = false;
    two_pair = false;
    one_pair = false;
    high_card = true;
    type = 0;

    //check_flush
    flush = true;
    for (int i = 0; i < 4; i++)
    {
        if (cards[i].type != cards[i + 1].type)
        {
            flush = false;
            break;
        }
    }
    //check_straight
    sort_by_num();
    straight = true;
    for (int i = 0; i < 4; i++)
    {
        if (cards[i].num != cards[i + 1].num - 1)
        {
            straight = false;
            break;
        }
    }
    //check_four_of_a_kind
    if (cards[0].num == cards[1].num && cards[1].num == cards[2].num && cards[2].num == cards[3].num)
    {
        four_of_a_kind = true;
    }
    if (cards[1].num == cards[2].num && cards[2].num == cards[3].num && cards[3].num == cards[4].num)
    {
        four_of_a_kind = true;
    }
    //check_three_of_a_kind
    if (cards[0].num == cards[1].num && cards[1].num == cards[2].num)
    {
        three_of_a_kind = true;
    }
    if (cards[1].num == cards[2].num && cards[2].num == cards[3].num)
    {
        three_of_a_kind = true;
    }
    if (cards[2].num == cards[3].num && cards[3].num == cards[4].num)
    {
        three_of_a_kind = true;
    }
    //check_one_pair
    int pair_count = 0;
    if (cards[0].num == cards[1].num)
    {
        one_pair = true;
        pair_count++;
    }
    if (cards[1].num == cards[2].num)
    {
        one_pair = true;
        pair_count++;
    }
    if (cards[2].num == cards[3].num)
    {
        one_pair = true;
        pair_count++;
    }
    if (cards[3].num == cards[4].num)
    {
        one_pair = true;
        pair_count++;
    }
    //check_two_pair
    if (pair_count == 2)
    {
        two_pair = true;
    }
    //check_full_house
    if (three_of_a_kind && pair_count == 3)
    {
        full_house = true;
    }
    //check_straight_flush
    if (flush && straight)
    {
        straight_flush = true;
    }

    //change type
    if (straight_flush)
    {
        type = 8;
        // cout << "straight_flush" << endl;
    }
    else if (four_of_a_kind)
    {
        type = 7;
        // cout << "four_of_a_kind" << endl;
    }
    else if (full_house)
    {
        type = 6;
        // cout << "full_house" << endl;
    }
    else if (flush)
    {
        type = 5;
        // cout << "flush" << endl;
    }
    else if (straight)
    {
        type = 4;
        // cout << "straight" << endl;
    }
    else if (three_of_a_kind)
    {
        type = 3;
        // cout << "three_of_a_kind" << endl;
    }
    else if (two_pair)
    {
        type = 2;
        // cout << "two_pair" << endl;
    }
    else if (one_pair)
    {
        type = 1;
        // cout << "one_pair" << endl;
    }
    else
    {
        type = 0;
        // cout << "high_card" << endl;
    }
    // disp();
}

void hand::sort_by_num()
{
    sort(cards,cards+5,compare_by_num);   
}

void hand::sort_by_type()
{
    sort(cards,cards+5,compare_by_type);
}



void hand::disp() const
{
    for (auto& i : cards)
    {
        cout << i.num << " " << i.type << endl;
    }
}

void hand::add_card(int num, int type)
{
    cards[count].num = num;
    cards[count].type = type;
    count++;
}
void solve()
{

    // freopen("F:\\Homework\\程序设计思维与实践作业\\Month1\\1.in", "r", stdin);
    // freopen("F:\\Homework\\程序设计思维与实践作业\\Month1\\1.out", "w", stdout);
    // hand h;
    // for (int i = 0; i < 5; i++)
    // {
    //     card c;
    //     cin >> c.num >> c.type;
    //     h.add_card(c);
    // }
    // h.sort_by_num();
    // h.disp();
    // h.sort_by_type();
    // h.disp();
    int val_num, type_num;
    cin >> val_num >> type_num;
    hand h;
    card c1;
    cin >> c1.num >> c1.type;
    card c2;
    cin >> c2.num >> c2.type;
    h.cards[0] = c1;
    h.cards[1] = c2;
    h.count = 2;
    card cards[val_num * type_num];
    for (int i = 0; i < val_num ; i++)
    {
        for (int j = 0; j < type_num; j++)
        {
            cards[i * type_num + j].num = i;
            cards[i * type_num + j].type = j;
        }
    }

    int ans[9];
    for (int i = 0;i < 9;i++)
    {
        ans[i] = 0;
    }

    for (int i = 0; i < val_num * type_num; i++)
    {
        if (cards[i].num == c1.num && cards[i].type == c1.type)
        {
            continue;
        }

        if (cards[i].num == c2.num && cards[i].type == c2.type)
        {
            continue;
        }

        for (int j = i + 1; j < val_num * type_num; j++)
        {

            if (cards[j].num == c1.num && cards[j].type == c1.type)
            {
                continue;
            }

            if (cards[j].num == c2.num && cards[j].type == c2.type)
            {
                continue;
            }
            for (int k = j + 1; k < val_num * type_num; k++)
            {
                if (cards[k].num == c1.num && cards[k].type == c1.type)
                {
                    continue;
                }

                if (cards[k].num == c2.num && cards[k].type == c2.type)
                {
                    continue;
                }

                h.cards[2] = cards[i];
                h.cards[3] = cards[j];
                h.cards[4] = cards[k];
                // h.disp();
                h.check();
                ans[h.type]++;
                h.cards[0] = c1;
                h.cards[1] = c2;
            }
        }
    }
    for (int i = 8; i >= 0; i--)
    {
        cout << ans[i] << " ";
    }
}

int main()
{
    solve();
    return 0;
}