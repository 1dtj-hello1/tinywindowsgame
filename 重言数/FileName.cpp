#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include <functional>
#define MAXN 12
using namespace std;


//class Solution {
//private:
//    map<string,bool> m;
//    map<vector<string>, double> eqMap;
//	unordered_multimap<string, vector<string>> graph;
//public:
//    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
//		graph.find("a");
//        vector<int> a;
//		find(a.begin(), a.end(), 1);
//		a.erase(remove(a.begin(), a.end(), 1), a.end());
//        for (int i = 0; i < equations.size(); i++) {
//            vector<string> eq = equations[i], ep = { equations[i][1], equations[i][0] };
//            m[equations[i][1]] = true;
//            m[equations[i][0]] = true;
//            eqMap[eq] = values[i];
//            eqMap[ep] = 1.0 / values[i];
//        }
//        vector<double> res;
//        for (auto& q : queries) {
//            if (m.find(q[0]) != m.end() && m.find(q[1]) != m.end())
//            {
//                int old = 0;
//                int ned = 0;
//				double val = 1.0;
//                while (old)
//                {
//                    while(find)
//                }
//                res.push_back(eqMap[q]);
//            }
//            else
//                res.push_back(-1.0);
//        }
//        return res;
//    }
class Solution {
private:
	bool check(unordered_map<char, int>& mp)
	{
		for (auto it : mp)
			if (it.second > 0)
				return false;
		return true;
	}
public:
	string minWindow(string s, string t) {
		if (s.size() < t.size())
			return "";
		int n = size(s);
		unordered_map<char, int> mp;
		for (auto it : t)
			mp[it]++;
		string res = "";
		string ans = "";
		int len = INT32_MAX, slow = 0, fast = 0;
		while (fast < n) {
			while (fast < n && !check(mp)) {
				if (mp.find(s[fast]) != mp.end())
					mp[s[fast]]--;
				res += s[fast];
				fast++;
			}
			while(slow<fast)
			{
				if (mp.find(s[slow]) == mp.end())
				{
					res.erase(0, 1);
					slow++;
				}
				else if (slow < fast && mp[s[slow]] < 0)
				{
					res.erase(0, 1);
					mp[s[slow]]++;
					slow++;
				}
				else
					break;
			}
			if (len > fast - slow&&check(mp)) {
				len = fast - slow;
				ans = s.substr(slow, len);
			}
			while (slow < fast&&check(mp)) {
				if (mp.find(s[slow]) != mp.end())
					mp[s[slow]]++;
				res.erase(0, 1);
				slow++;
			}
			while (slow<fast&&mp.find(s[slow]) == mp.end())
			{
				res.erase(0, 1);
				slow++;
			}
		}
		return ans;
	}
};
int main()
{
	string s = "a", t = "b";
    Solution sol;
    auto result = sol.minWindow(s, t);
    return 0;
}
