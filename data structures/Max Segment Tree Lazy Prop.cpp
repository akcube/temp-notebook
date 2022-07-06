const ll INF = 1e16;

class MaxSegmentTree {
private:
	struct node {
		ll val;
		ll lazy;
	};
	
	vector<node> tree; int n;
	
	void push(int p, int c1, int c2) {
		ll toadd = tree[p].lazy;
		tree[c1].lazy += toadd; tree[c2].lazy += toadd;
		tree[c1].val += toadd; tree[c2].val += toadd;
		tree[p].lazy = 0;
	}
	
	void update(int i, ll val, int l, int r, int p) {
		if (l > i or r < i) return;
		if (l == r) {
			tree[p].val = val;
			return;
		}
		
		int mid = (l + r) / 2;
		int c1 = 2*p+1, c2 = 2*p+2;
		if (tree[p].lazy) push(p, c1, c2);
		
		update(i, val, l, mid, c1); update(i, val, mid+1, r, c2);
		tree[p].val = max(tree[c1].val, tree[c2].val);
	}
	
	void add(int i, int j, ll val, int l, int r, int p) {
		if (l > j or r < i) return;
		if (l >= i and r <= j) {
			tree[p].val += val, tree[p].lazy += val;
			return;
		}
		
		int mid = (l + r) / 2;
		int c1 = 2*p+1, c2 = 2*p+2;
		if (tree[p].lazy) push(p, c1, c2);
		
		add(i, j, val, l, mid, c1); add(i, j, val, mid+1, r, c2);
		tree[p].val = max(tree[c1].val, tree[c2].val);
	}
	
	ll mx(int i, int j, int l, int r, int p) {
		if (l > j or r < i) return -INF;
		if (l >= i and r <= j) return tree[p].val;
		
		int mid = (l + r) / 2;
		int c1 = 2*p+1, c2 = 2*p+2;
		if (tree[p].lazy) push(p, c1, c2);
		
		return max(mx(i, j, l, mid, c1), mx(i, j, mid+1, r, c2));
	}

public:
	MaxSegmentTree(int _n) {
		n = _n;
		tree.assign(4*n, {-INF, 0});
	}
	
	ll mx(int i, int j) {
		return mx(i, j, 0, n-1, 0);
	}
	
	void update(int i, ll val) {
		update(i, val, 0, n-1, 0);
	}
	
	void add(int i, int j, ll val) {
		add(i, j, val, 0, n-1, 0);
	}
};