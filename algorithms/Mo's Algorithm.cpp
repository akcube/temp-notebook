#include "bits/stdc++.h"
using namespace std;
#define for_(i, s, e) for (int i = s; i < (int) e; i++)
#define for__(i, s, e) for (ll i = s; i < e; i++)
typedef long long ll;
typedef vector<int> vi;
typedef array<int, 2> ii;
#define endl '\n'

int n, m;
int block_size = 450;
vi freq(1e6+1);
ll val = 0;
vi nums;
 
struct Query {
	int l, r, idx;
	bool operator<(Query other) const {
		int b1 = l/block_size, b2 = other.l/block_size;
		if (b1 != b2) return b1 < b2;
		else if (b1 % 2 == 0) return r < other.r;
		else return r > other.r;
	} 
};
 
void add(ll v) {
	freq[v] += 1;
}
 
void remove(ll v) {
	freq[v] -= 1;
}


int main() {
	#ifdef mlocal
	freopen("test.in", "r", stdin);
	#endif
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	nums.resize(n);
	for_(i, 0, n) cin >> nums[i];
	
	vector<Query> queries(m);
	vector<ll> ans(m);
	for_(i, 0, m) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].r -= 1; queries[i].l -= 1;
		queries[i].idx = i;
	}
	
	sort(queries.begin(), queries.end());
	
	int cur_l = 0, cur_r = -1;
	for (auto q: queries) {
		while (cur_l > q.l) {
			cur_l--;
			add(nums[cur_l]);
		}
		while (cur_r < q.r) {
			cur_r++;
			add(nums[cur_r]);
		}
		while (cur_l < q.l) {
			remove(nums[cur_l]);
			cur_l++;
		}
		while (cur_r > q.r) {
			remove(nums[cur_r]);
			cur_r--;
		}
		
		ans[q.idx] = val;
	}
}
