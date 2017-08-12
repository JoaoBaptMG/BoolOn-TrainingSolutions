#include <cstdio>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int n;
char map[27][27];

static const int os[4][2] = { { 1, 1 }, { 1, -1 }, { -1, -1, }, { -1, 1 } };

int countwhites(int x, int y)
{	
	int curmax = 0;
	
	for (int i = 0; i < 4; i++)
	{
		if (x + 2*os[i][0] < 0 || x + 2*os[i][0] >= n) continue;
		if (y + 2*os[i][1] < 0 || y + 2*os[i][1] >= n) continue;
		
		if (map[y + os[i][1]][x + os[i][0]] == 'W' && map[y + 2*os[i][1]][x + 2*os[i][0]] == '_')
		{
			map[y + os[i][1]][x + os[i][0]] = '_';
			int cur = 1 + countwhites(x + 2*os[i][0], y + 2*os[i][1]);
			map[y + os[i][1]][x + os[i][0]] = 'W';
			
			if (curmax < cur) curmax = cur;
			if (curmax == n) return curmax;
		}
	}

	return curmax;
}

int main()
{
	while (scanf("%d", &n) != EOF)
	{
	    for (int i = 0; i < n; i++)
		    scanf("%s", map[i]);
        
        int num = 0;
	    int x = -1, y = -1;
	
	    int ws = 0;
	    for (int j = 0; j < n; j++)
		    for (int i = 0; i < n; i++)
			    if (map[j][i] == 'W') ws++;
			
	    for (int j = 0; j < n; j++)
		    for (int i = 0; i < n; i++)
		    {
			    if (map[j][i] == 'B')
			    {
			    	map[j][i] = '_';
				    int c = countwhites(i, j);
				    map[j][i] = 'B';
				    
				    if (c == ws)
				    {
					    x = i, y = j;
					    num++;
				    }
			    }
		    }
		
	    if (num == 0) puts("None");
	    else if (num > 1) puts("Multiple");
	    else printf("%c%d\n", 'a' + x, n - y);
    }
}
