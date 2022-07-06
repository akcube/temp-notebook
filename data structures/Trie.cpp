class Trie {
	static const int MXN = 1e6, MXV = 26; // max node count (worst case: max sequence length * count), max sequence value
	int node = 1, child[MXN+1][MXV+1], ct[MXN+1];

	public:
	void insert(vi s) {
		int p = 0;
		for (int i: s) {
			if (!child[p][i]) child[p][i] = node++;
			p = child[p][i];
			ct[p] += 1;
		}
	}

	int countPref(vi s) {
		int ans = 0, p = 0;
		for (int i: s) {
			if (!child[p][i]) return 0;
			p = child[p][i];
			ans = ct[p];
		}

		return ans;
	}
} trie;

// convert string to sequence of integers
vi stov(string s) {
	vi ans(s.size());
	for_(i, 0, s.size()) ans[i] = s[i]-'a';
	return ans;
}
