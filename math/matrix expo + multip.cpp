typedef vector<vector<ll>> Matrix;

const ll mod = 1e9+7;

Matrix matMul(Matrix a, Matrix b) {
	int sa = a.size(), sb = b[0].size();
	Matrix ans(sa, vector<ll> (sb));
	for_(r, 0, sa) for_(c, 0, sb) for_(i, 0, b.size()) {
		ans[r][c] = (ans[r][c] + (a[r][i] * b[i][c]) % mod);
		if (ans[r][c] >= mod) ans[r][c] -= mod;
	}
	return ans;
}

Matrix matPow(Matrix a, ll p) {
	int s = a.size();
	Matrix ans(s, vector<ll> (s));
	for_(i, 0, s) ans[i][i] = 1;

	while (p) {
		if (p & 1) ans = matMul(ans, a);
		a = matMul(a, a);
		p >>= 1;
	}
	return ans;
}
