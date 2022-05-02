#include<bits/stdc++.h>
using namespace std;

// ------------------------------------ Sparse Table ------------------------------------
struct Sparse {

	int n, LOG;
	vector<vector<int> > sparse_minimum, sparse_maximum;

	Sparse() {};

	Sparse(int n) {
		this->n = n;
		LOG = log2(n) + 2;
		sparse_minimum = vector<vector<int> > (n, vector<int> (LOG, 0));
		sparse_maximum = vector<vector<int> > (n, vector<int> (LOG, 0));
	}

	void build(vector<int> &a) {
		for (int j = 0; j < LOG; j++) {
			for (int i = 0; i + (1 << j) - 1 < n; i++) {
				if (j == 0) {
					sparse_minimum[i][j] = a[i];
					sparse_maximum[i][j] = a[i];
				} else {
					sparse_minimum[i][j] = min(sparse_minimum[i][j - 1], sparse_minimum[i + (1 << (j - 1))][j - 1]);
					sparse_maximum[i][j] = max(sparse_maximum[i][j - 1], sparse_maximum[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
	}

	int query_minimum(int l, int r) {
		int k = log2(r - l + 1);
		return min(sparse_minimum[l][k], sparse_minimum[r - (1 << k) + 1][k]);
	}

	int query_maximum(int l, int r) {
		int k = log2(r - l + 1);
		return max(sparse_maximum[l][k], sparse_maximum[r - (1 << k) + 1][k]);
	}
};

int main() {

	string file_name;
	ifstream fp;

	map<string, int> student_roll_no_to_unique_id;
	vector<int> students_marks;

	int id = 0;

	// Reading File
	do {
		cout << "Enter the file name : ";
		cin >> file_name;
		fp.open(file_name);
		if (!fp) {
			cout << "File doesn't exists\n";
			continue;
		}
		string line;
		while (getline(fp, line)) {
			while ((int)line.size() && line.back() == ' ') line.pop_back();
			string roll_no = "";
			for (char x : line) {
				if (x == ' ') break;
				roll_no.push_back(x);
			}
			reverse(line.begin(), line.end());
			string marks = "";
			for (char x : line) {
				if (x == ' ') break;
				marks.push_back(x);
			}
			reverse(marks.begin(), marks.end());
			int mark = stoi(marks);
			student_roll_no_to_unique_id[roll_no] = id++;
			students_marks.push_back(mark);
		}
		cout << "File is read successfully\n";
		break;
	} while (true);


	Sparse sp(id);
	sp.build(students_marks);

	do {
		cout << "\nEnter 1. Get Minimum In Range\n";
		cout << "Enter 2. Get Maximum In Range\n";
		cout << "Enter 3. Exit\n";

		int ip;
		cin >> ip;

		if (ip == 1 || ip == 2) {
			cout << "Enter starting roll_no - 1 and ending roll_no - 2 : ";
			string l, r;
			cin >> l >> r;
			int id_l, id_r;
			auto left_itr = student_roll_no_to_unique_id.lower_bound(l);
			auto right_itr = student_roll_no_to_unique_id.upper_bound(r);
			if (left_itr == student_roll_no_to_unique_id.end()) {
				cout << "Roll Numbers are out of range\n";
				continue;
			}
			if (student_roll_no_to_unique_id.upper_bound(r) == student_roll_no_to_unique_id.begin()) {
				cout << "Roll Numbers are out of range\n";
				continue;
			}
			right_itr--;
			id_l = (*left_itr).second;
			id_r = (*right_itr).second;
			if (ip == 1) {
				cout << "Minimum in range is " << sp.query_minimum(id_l, id_r) << "\n";
			} else {
				cout << "Maximum in range is " << sp.query_maximum(id_l, id_r) << "\n";
			}
			continue;
		}
		if (ip == 3) {
			break;
		}
		cout << "Invalid Input\n";
	} while (true);

	return 0;
}