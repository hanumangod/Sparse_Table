#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ll long long
#define ull unsigned long long
#define all(x) (x).begin(),(x).end()
#define print(x) if(x)cout<<"YES\n";else cout<<"NO\n";
#define pb push_back
#define F first
#define S second
//#define mod 1000000007
#define mod 998244353
using namespace __gnu_pbds;
using namespace std;
// ------------------ Sparse Table ------------------
struct Sparse {

	int n, LOG;
	vector<vector<int> > sparse;

	Sparse() {};

	Sparse(int n) {
		this->n = n;
		LOG = log2(n) + 2;
		sparse = vector<vector<int> > (n, vector<int> (LOG, 0));
	}

	// Change the f according to question
	int f(int x, int y) {
		return min(x, y);
	}

	void build(vector<int> &a) {
		for (int j = 0; j < LOG; j++) {
			for (int i = 0; i + (1 << j) - 1 < n; i++) {
				if (j == 0) {
					sparse[i][j] = a[i];
				} else {
					sparse[i][j] = f(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
	}

	int query(int l, int r) {
		int k = log2(r - l + 1);
		return f(sparse[l][k], sparse[r - (1 << k) + 1][k]);
	}
};
void solve() {
	vector<int> a = {8, 7, 6, 5, 4, 3, 2, 1};
	Sparse sp(8);
	sp.build(a);
	for (int i = 0; i < (int)sp.sparse.size(); i++) {
		for (int j = 0; j < (int)sp.sparse[i].size(); j++) {
			cout << sp.sparse[i][j] << " ";
		}
		cout << "\n";
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	fastio;
	int T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
}