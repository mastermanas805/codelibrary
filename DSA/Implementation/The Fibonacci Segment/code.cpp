#include <bits/stdc++.h>
using namespace std;
int main()
{
    int l, x, y, z, m = 0, n = 0;
    cin >> l;
    if (l == 1)
    {
        cin >> x;
        cout << 1 << endl;
    }
    else if (l == 2)
    {
        cin >> x >> y;
        cout << 2 << endl;
    }

    else
    {
        cin >> x >> y;
        l -= 2;
        n = 2;
        while (l--)
        {
            cin >> z;
            if (x + y == z)
                n++;
            else
            {
                m = max(m, n);
                n = 2;
            }
            x = y;
            y = z;
        }

        m = max(m, n);
        cout << m << endl;
    }
}