// Ask for sum 1 -> n for full (one based indexing)
class BIT {
	private: vector<vector<ll>> tree; int n, m;
	int LSOne(int x) {
		return x&(-x);
	}

	public:
		BIT(int r, int c) {
			n = r, m = c;
			tree.resize(n+1, vector<ll>(m+1));
		}
		ll sum(int x, int y) {
			ll sum = 0;
			for (; x > 0; x -= LSOne(x)) for (int yy = y; yy > 0; yy -= LSOne(yy)) sum += tree[x][yy];
			return sum;
		}
		ll sum(int x1, int y1, int x2, int y2) {
			ll a = sum(x2, y2);
			if (x1 > 1) a -= sum(x1-1, y2);
			if (y1 > 1) a -= sum(x2, y1-1);
			if (x1 > 1 and y1 > 1) a += sum(x1-1, y1-1);
			return a;
		}
		void update(int x, int y, ll v) {
			for (; x < n+1; x += LSOne(x)) for (int yy = y; yy < m+1; yy += LSOne(yy)) tree[x][yy] += v;
		}
};
