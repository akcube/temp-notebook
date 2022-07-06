const ll MAXN = 1000001, mod = 1e9+7;
ll numInv[MAXN+10], facInv[MAXN+10], fac[MAXN+10];

void pre() {
	numInv[0] = numInv[1] = 1;
	for (int i = 2; i <= MAXN; i++) numInv[i] = numInv[mod % i] * (mod - mod / i) % mod;

	facInv[0] = facInv[1] = 1;
	for (int i = 2; i <= MAXN; i++) facInv[i] = (numInv[i] * facInv[i - 1]) % mod;

	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) fac[i] = (fac[i - 1] * i) % mod;
}

ll nCr(ll n, ll r) {
	return ((fac[n] * facInv[r]) % mod * facInv[n - r]) % mod; 
}
