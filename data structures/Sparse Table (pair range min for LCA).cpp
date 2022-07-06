class SparseTable {
	vector<vector<ii>> st;
	int n;
	
	void buildTable(vector<ii> &raw) {
		int k = __lg(n)+1;
		st.resize(k, vector<ii>(n));
		for_(i, 0, n) st[0][i] = raw[i];
		for_(p, 1, k+1) for_(i, 0, n - (1<<p) + 1) st[p][i] = min(st[p-1][i], st[p-1][i + (1 << (p-1))]);
	}

public:
	void build(vector<ii> &nums) {
		n = nums.size();
		buildTable(nums);
	}
	
	int mn(int l, int r) {
		if (l > r) swap(l, r);
		int p = __lg(r-l+1);
		return min(st[p][l], st[p][r - (1<<p) + 1])[1];
	}
};

vector<ii> tour;

void dfs(int p, int parent, int d) {
	tin[p] = tour.size();
	tour.push_back({d, p});
	
	for (auto i: adj[p]) if (i != parent) {
		dfs(i, p, d+1);
		tour.push_back({d, p});
	}
}

function<int(int, int)> nodeDist = [&] (int a, int b) {
	int lca = st.mn(min(tin[a], tin[b]), max(tin[a], tin[b]));
	return depth[a] + depth[b] - 2 * depth[lca];
};