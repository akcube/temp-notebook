int n;
vector<vector<array<ll, 2>>> adjList;
vi removed, subtreeSize, centroid;
vector<ll> whiteDist;
vector<vector<ll>> centroidDist;
const ll INF = 1e15;

void dfs(int p, int parent) {
	for (auto i: adjList[p]) if (i[0] != parent) {
			dfs(i[0], p);
			subtreeSize[p] += subtreeSize[i[0]];
		}
	
	subtreeSize[p] += 1;
}

void noteCentroidDist(int p, int parent) {
	ll d = centroidDist[p].back();
	for (auto i: adjList[p]) if (!removed[i[0]] and i[0] != parent) {
			centroidDist[i[0]].push_back(d+i[1]);
			noteCentroidDist(i[0], p);
		}
}

void decompose(int p, int c) {
	int invalidChild = -1, sizeLimit = (subtreeSize[p] >> 1);
	for (auto i: adjList[p]) if (!removed[i[0]] and subtreeSize[i[0]] > sizeLimit) {
			invalidChild = i[0];
			break;
		}
	
	if (invalidChild != -1) {
		subtreeSize[p] -= subtreeSize[invalidChild];
		subtreeSize[invalidChild] += subtreeSize[p];
		return decompose(invalidChild, c);
	}
	
	removed[p] = true;
	centroid[p] = c;
	
	centroidDist[p].push_back(0);
	noteCentroidDist(p, p);
	
	for (auto i: adjList[p]) if (!removed[i[0]]) {
			centroid[i[0]] = p;
			decompose(i[0], p);
		}
}

vi updated;
int pt = 0;

void update(int p) {
	int v = p, cpt = (int) centroidDist[p].size() - 1;
	while (v != -1) {
		ll d = centroidDist[p][cpt--];
		whiteDist[v] = min(whiteDist[v], d);
		updated[pt++] = v;
		v = centroid[v];
	}
}

ll ans(int p) {
	ll val = INF;
	int v = p,  cpt = (int) centroidDist[p].size() - 1;
	while (v != -1) {
		val = min(val, whiteDist[v] + centroidDist[p][cpt--]);
		v = centroid[v];
	}
	return (val == 1e9 ? -1 : val);
}

void Init(int N, int A[], int B[], int D[]) {
	n = N;
	adjList.resize(n); subtreeSize.resize(n); removed.resize(n); centroid.resize(n, -1); whiteDist.resize(n, INF); updated.resize(10*n); centroidDist.resize(n);
	for_(i, 0, n-1) {
		int a = A[i], b = B[i]; ll w = D[i];
		adjList[a].push_back({b, w});
		adjList[b].push_back({a, w});
	}
	
	dfs(0, 0);
	decompose(0, -1);
}

ll Query(int S, int X[], int T, int Y[]) {
	pt = 0;
	
	for_(i, 0, S) update(X[i]);
	ll val = INF;
	for_(i, 0, T) val = min(val, ans(Y[i]));
	for_(i, 0, pt) whiteDist[updated[i]] = INF;
	
	return val;
}

int main() {
	freopen("test.in", "r", stdin);
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int N, q;
	cin >> N >> q;
	int A[100], B[100], D[100];
	for_(i, 0, N - 1) {
		int a, b, w;
		cin >> a >> b >> w;
		A[i] = a;
		B[i] = b;
		D[i] = w;
	}
 
	Init(N, A, B, D);
 
	int X[100], Y[100];
	while (q--) {
		int S, T;
		cin >> S >> T;
		for_(i, 0, S) cin >> X[i];
		for_(i, 0, T) cin >> Y[i];
		cout << Query(S, X, T, Y) << endl;
	}
 
	return 0;
}