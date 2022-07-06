ll sum(vector<vector<ll>> &mat, int x1, int y1, int x2, int y2) {
	ll ans = mat[x2][y2];
	if (x1 > 0) ans -= mat[x1-1][y2];
	if (y1 > 0) ans -= mat[x2][y1-1];
	if (x1 > 0 and y1 > 0) ans += mat[x1-1][y1-1];
	return ans;
}

void make(vector<vector<ll>> &mat) {
	for_(i, 0, n) for_(j, 0, m) {
		if (i > 0) mat[i][j] += mat[i-1][j];
		if (j > 0) mat[i][j] += mat[i][j-1];
		if (i > 0 and j > 0) mat[i][j] -= mat[i-1][j-1];
	}
}