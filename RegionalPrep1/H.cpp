#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

struct pt { ll x, y, curMax = 0; };
bool verticalSortInv(const pt& p1, const pt& p2)
{
	return p1.y > p2.y;
} 

int main()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	ll n, r, w, h;
	
	while (cin && cin >> n >> r >> w >> h)
	{
		vector<pt> gems(n);
		for (pt& gem : gems) cin >> gem.x >> gem.y;
		sort(gems.begin(), gems.end(), verticalSortInv);
		
		map<ll,ll> maxCollections;
	
		gems.front().curMax = 1;
		maxCollections[gems.front().y] = 1;
		
		for(ll i = 0; i < n; i++)
		{
			pt& gem = gems[i];
			ll curMax = 0;
			
			ll yBound = gem.y + r * max(w - gem.x, gem.x);
			for (ll j = i-1; j >= 0 && gems[j].y < yBound; j--)
			{
			    pt& gem2 = gems[j];
				if (r * abs(gem2.x - gem.x) <= gem2.y - gem.y)
					if (curMax < gem2.curMax)
						curMax = gem2.curMax;
			}
			
			auto it = maxCollections.lower_bound(yBound);
			if (it != maxCollections.end())
			    if (curMax < it->second)
			        curMax = it->second;
			
			gem.curMax = 1 + curMax;
			if (maxCollections.begin()->second < gem.curMax)
				maxCollections[gem.y] = gem.curMax;
		}
		
		ll allMax = 0;
		for (const pt& gem : gems)
		    if (allMax < gem.curMax)
		        allMax = gem.curMax;
		        
		cout << allMax << endl;
	}
}
