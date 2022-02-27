#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef stack<int> si;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

class suffix
{
public:
    ll index{0};
    int suffix_val[2];
};

//Global Declarations
ll len_string{0};
char diff = 'a';

bool my_cmp(class suffix obj1, class suffix obj2)
{
    int obj1_val0 = obj1.suffix_val[0];
    int obj1_val1 = obj1.suffix_val[1];
    int obj2_val0 = obj2.suffix_val[0];
    int obj2_val1 = obj2.suffix_val[1];

    if (obj1_val0 == obj2_val0)
    {
        if (obj1_val1 < obj2_val1)
            return true;

        return false;
    }
    else
    {
        if (obj1_val0 < obj2_val0)
            return true;

        return false;
    }
}

int main()
{
    //variable declarations
    ll i{0}, k{4}, res_index{0};
    int rank{0}, prev_rank{0};

    int m;
    cin >> m;
    cin >> len_string;

    string input = "", res = "";
    cin >> input;

    // len_string = input.size();
    // cout << "len : " << len_string << endl;

    suffix suff[len_string];
    int indices[len_string];
    int *suff_arr = new int[len_string];
    ll n{2 * len_string};

    while (i < len_string)
    {
        ll index = i;
        int entry_1 = input.at(i) - diff;
        int entry_2{-1};

        if ((i + 1) < len_string)
            entry_2 = input.at(i + 1) - diff;

        //putting the entries into object
        suff[i].index = index;
        suff[i].suffix_val[0] = entry_1;
        suff[i].suffix_val[1] = entry_2;

        i += 1;
    }
    i = 1;

    sort(suff, suff + len_string, my_cmp);

    // for (auto i : suff)
    // {
    //     cout << "index : " << i.index << endl;
    //     cout << "s[0] : " << i.suffix_val[0] << endl;
    //     cout << "s[1] : " << i.suffix_val[1] << endl;
    // }

    while (k < n)
    {
        int ind{suff[0].suffix_val[0]};
        int next_ind{0};
        ll val{suff[0].index};

        int rank = 0;
        int prev_rank = ind;
        suff[0].suffix_val[0] = rank; // =rank;
        indices[val] = 0;
        // i = 1;

        for (i = 1; i < len_string;)
        {
            int obji_val0 = suff[i].suffix_val[0];
            int obji_val1 = suff[i].suffix_val[1];
            ll val{suff[i].index};

            bool check_1{prev_rank == obji_val0};
            bool check_2{suff[i - 1].suffix_val[1] == obji_val1};

            if (check_1 == true && check_2 == true)
            {
                // prev_rank = obji_val0;
                prev_rank = suff[i].suffix_val[0];
                suff[i].suffix_val[0] = rank;
            }
            else
            {
                rank++;
                // prev_rank = obji_val0;
                prev_rank = suff[i].suffix_val[0];
                suff[i].suffix_val[0] = rank;
            }
            indices[val] = i;
            i++;
        }
        i = 0;

        while (i < len_string)
        {
            next_ind = suff[i].index + (k >> 1);
            suff[i].suffix_val[1] = -1;

            if (next_ind < len_string)
            {
                int index_val = indices[next_ind];
                suff[i].suffix_val[1] = suff[index_val].suffix_val[0];
            }

            i++;
        }

        sort(suff, suff + len_string, my_cmp);

        k = k << 1;
    }
    i = 0;

    // for (auto i : suff)
    // {
    //     cout << "index : " << i.index << endl;
    //     cout << "s[0] : " << i.suffix_val[0] << endl;
    //     cout << "s[1] : " << i.suffix_val[1] << endl;
    // }

    for (; i < len_string;)
    {
        suff_arr[i] = suff[i].index;
        i++;
    }
    i = 0;

    // for (; i < len_string; i++)
    // {
    //     cout << suff_arr[i] << endl;
    // }
    // i = 0;

    ll window = (len_string - m) + 1;

    while (i < window)
    {
        string str = "";
        ll ind{i + m - 1};
        int pos_1 = suff_arr[i];
        int pos_2 = suff_arr[ind];

        // cout << "before while" << endl;
        while (pos_1 < len_string && pos_2 < len_string && input.at(pos_1) == input.at(pos_2))
        {
            // cout << "inside while" << endl;
            str += input.at(pos_1);
            pos_1++;
            pos_2++;
        }

        bool ans_size{res.length() < str.length()};

        if (ans_size == true)
            res = str;

        // cout << "RESULT : " << res << endl;

        i++;
    }

    if (res.length() > 0)
    {
        cout << res.length() << endl;
    }
    else
    {
        cout << -1 << endl;
    }

    return 0;
}