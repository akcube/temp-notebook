// is a <= b?
bool comp(ii &a, ii &b) {
	if (a[0] >= 0 and b[0] < 0) return false;
	else if (a[0] < 0 and b[0] >= 0) return true;
	
	
	if (a == b or b[1] == 0) return true;
	else if (a[1] == 0) return false;
	
	bool flip = (a[1] < 0) ^ (b[1] < 0);
	bool ans = flip ^ (a[0] * b[1] < b[0] * a[1]);
	return flip ^ (a[0] * b[1] < b[0] * a[1]);
}

void normalise(ii &f) {
	ll g = __gcd(f[0], f[1]);
	if (g) f[0] /= g, f[1] /= g;
	if (f[1] < 0) f[0] = - f[0], f[1] = -f[1];
}

// x-coordinate of intersection of lines {m1, c1} {m2, c2} -> (c2-c1)/(m1-m2).