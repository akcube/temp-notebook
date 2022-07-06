struct Node {
	ll pref, suf, mx, sum;
};

class SegmentTree {
	private:
		vector<Node> tree; vector<ll> raw; int n;
		ll INF = 1e15;
		Node bound = {0, 0, -INF, 0};
		
		Node merge(Node a, Node b) {
			if (a.mx == -INF) return b;
			if (b.mx == -INF) return a;
			
			Node ans;
			ans.sum = a.sum + b.sum;
			ans.mx = max({a.mx, b.mx, b.pref + a.suf});
			ans.suf = max(b.suf, b.sum + a.suf);
			ans.pref = max(a.pref, a.sum + b.pref);
			return ans;
		}
		
		void buildTree(int l, int r, int p) {
			if (l == r) {
				tree[p] = {raw[l], raw[l], raw[l], raw[l]};
				return;
			}
			
			int mid = (l + r) / 2;
			int c1 = 2*p+1, c2 = 2*p+2;
			buildTree(l, mid, c1); buildTree(mid+1, r, c2);
			tree[p] = merge(tree[c1], tree[c2]);
		}
		
		void update(int i, ll val, int l, int r, int p) {
			if (l > i or r < i) return;
			if (l == r) {
				tree[p] = {val, val, val, val};
				return;
			}
			
			int mid = (l + r) / 2;
			int c1 = 2*p+1, c2 = 2*p+2;
			update(i, val, l, mid, c1); update(i, val, mid+1, r, c2);
			tree[p] = merge(tree[c1], tree[c2]);
		}
		
		Node mx(int i, int j, int l, int r, int p) {
			if (l > j or r < i) return bound;
			if (l >= i and r <= j) return tree[p];
			
			int mid = (l + r) / 2;
			int c1 = 2*p+1, c2 = 2*p+2;
			return merge(mx(i, j, l, mid, c1), mx(i, j, mid+1, r, c2));
		}
	
	public: 
		SegmentTree(vector<ll> input) {
			raw = input;
			n = raw.size();
			tree.resize(4*n);
			buildTree(0, n-1, 0);
		}
		
		ll mx(int i, int j) {
			return mx(i, j, 0, n-1, 0).mx;
		}
		
		void update(int i, ll val) {
			update(i, val, 0, n-1, 0);
		}
};
