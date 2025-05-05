#include<bits/stdc++.h>

using namespace std;

class DiskScheduling {
private:
    pair<int, int> range;
    int head, n;
    vector<int> v;

    vector<pair<int, int>> fcfs(int n) {
        vector<pair<int, int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = {i + 1, v[i]};
        }
        return ans;
    }

    vector<pair<int, int>> sstf(int n) {
        vector<pair<int, int>> ans(n);
        int curr = head;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            array<int, 3> nearly = {range.second - range.first, -1, -1};
            for (int j = 0; j < n; j++) {
                if (!vis[j] && abs(curr - v[j]) < nearly[0]) {
                    nearly = {abs(curr - v[j]), j, v[j]};
                }
            }
            ans[i] = {nearly[1] + 1, nearly[2]};
            vis[nearly[1]] = 1;
            curr = nearly[2];
        }
        return ans;
    }

    vector<pair<int,int>> scan(int n, char dir){
        vector<pair<int, int>> vv(n + 1), ret;
        for(int i = 1; i <= n; i++) {
            vv[i] = {v[i - 1], i};
        }
        sort(vv.begin(), vv.end());
        if(dir == 'L'){
            int idx = (int)(lower_bound(vv.begin(), vv.end(), make_pair(head,1 + n)) - vv.begin());
            idx--;
            for(int i = idx; i >= 1; i--){
                ret.push_back(vv[i]);
            }
            ret.push_back({range.first, 0});
            for(int i = idx + 1; i <=n; i++){
                ret.push_back(vv[i]);
            }
        }
        else{
            int idx = (int)(lower_bound(vv.begin(), vv.end(), make_pair(head,0)) - vv.begin());
            for(int i = idx + 1; i <=n; i++){
                ret.push_back(vv[i]);
            }
            ret.push_back({range.second, n + 1});
            for(int i = idx; i >= 1; i--){
                ret.push_back(vv[i]);
            }
        }
        for(int i = 0; i < ret.size(); i++)
            swap(ret[i].first, ret[i].second);
        return ret;
    }

    vector<pair<int, int>> cScan(int n, bool flag = 0) {
        vector<pair<int, int>> temp;
        for (int i = 0; i < n; i++) temp.push_back({v[i], i + 1});
        sort(temp.begin(), temp.end());
        int ind = (lower_bound(temp.begin(), temp.end(), make_pair( head, 0)) - temp.begin());
        vector<pair<int, int>> res;
        for (int i = ind; i < n; i++) {
            res.push_back({temp[i].second, temp[i].first});
        }
        if (!flag) {
            res.push_back({n + 1, range.second});
            res.push_back({0, range.first});
        }
        for (int i = 0; i < ind; i++) {
            res.push_back({temp[i].second, temp[i].first});
        }
        return res;
    }

    void print(vector<pair<int,int>> res) {
        for (auto it: res) {
            cout << it.first << " " << it.second << "\n";
        }
        cout << "\n";
    }

    int totalHeadMovement(vector<pair<int,int>> v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            if (i - 1 < 0) {
                sum += abs(v[i].second - head);
            } else {
                sum += abs(v[i].second - v[i - 1].second);
            }
        }
        return sum;
    }

public:

    DiskScheduling(vector<int>v, pair<int,int>r, int head, int n) {
        this->n = n;
        this->v.resize(n);
        range = r;
        this->head = head;
        for (int i = 0; i < n; i++) {
            this->v[i] = v[i];
        }
    }

    void fcfs(){
        vector<pair<int,int>> ret = fcfs(n);
        print(ret);
        totalHeadMovement(ret);
    }

    void sstf(){
        vector<pair<int,int>>ret = sstf(n);
        print(ret);
        totalHeadMovement(ret);
    }

    void scan(char c){
        vector<pair<int,int>>ret = scan(n, c);
        print(ret);
        totalHeadMovement(ret);
    }

    void cScan() {
        vector<pair<int,int>>ret = cScan(n, 0);
        print(ret);
        totalHeadMovement(ret);
    }

    void cLook() {
        vector<pair<int,int>>ret = cScan(n, 1);
        print(ret);
        totalHeadMovement(ret);
    }
};

void solve() {
    int n;
    cin >> n;
    pair<int, int> range;
    cin >> range.first >> range.second;
    int head;
    cin >> head;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    DiskScheduling d(v, range, head, n);
    d.fcfs();
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
//    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve();
        if(i <= t - 1) cout<<"\n";
    }
}
