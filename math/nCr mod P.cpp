ll mod = 1e9+7;
const ll MAXR = 1e6;

ll s, inv[MAXR+10];
ll nCr(ll n, ll r) {
	  if (r > n) return 0;
	  if (n - r < r) r = n - r;
	  n %= mod;
	  ll ans = 1;
	  for_(i, 0, r) {
			ans = (ans * (n - i)) % mod;
			ans = (ans * inv[i + 1]) % mod;
	  }
	  return ans;
}
 
ll modpow(ll a, ll b, ll mod) {
	ll res = 1;
	while (b) {
		if (b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}
 
void pre() {
	for (int i = 1; i <= MAXR; i++) {
		inv[i] = modpow(i, mod - 2, mod);
	}
}