// Ask for sum 1 -> n for full (one based indexing)
class BIT {
	private: vector<ll> tree; int n;
	int LSOne(int x) {
		return x&(-x);
	}

	public:
		BIT(int x) {
			n = x;
			tree.resize(n+1);
		}
		ll sum(int a) {
			ll sum = 0;
			for (; a > 0; a -= LSOne(a)) sum += tree[a];
			return sum;
		}
		ll sum(int a, int b) {
			return sum(b) - (a == 1 ? 0 : sum(a-1));
		}
		void update(int p, ll v) {
			for (; p < n+1; p += LSOne(p)) tree[p] += v;
		}
};
