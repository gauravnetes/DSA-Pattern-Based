#include<bits/stdc++.h>
using namespace std; 

int lower_bound(vector<int> &v, int el) {
    int l = 0, h = v.size() - 1; 

    while(l < h) {
        int mid = l + (h - l) / 2; 
        if(v[mid] < el) {
            l = mid + 1; 
        } else { // v[mid] >= el 
            h = mid; 
        }
    }
    
    // if l and h both are >= el 
    // ans will be l then 
    if(v[l] >= el) 
        return l;
    return -1; // Target el is larger than the max Arr el  
}

int lower_bound1(vector<int> &v, int el) {
    int l = 0, h = v.size() - 1; 

    while(h - l > 1) {
        int mid = l + (h - l) / 2; 
        if(v[mid] < el) {
            l = mid + 1; 
        } else { // v[mid] >= el 
            h = mid; 
        }
    }
    
    // if l and h both are >= el 
    // ans will be l then 
    if(v[l] >= el)
        return l;
    if(v[h] >= el)
        return h;
    return -1;
}

int upper_bound(vector<int> &v, int el) {
    int l = 0, h = v.size() - 1; 

    while(h - l > 1) {
        int mid = l + (h - l) / 2; 
        if(v[mid] <= el) {
            l = mid + 1; 
        } else { // v[mid] >= el 
            h = mid; 
        }
    }
    
    // if l and h both are >= el 
    // ans will be l then 
    if(v[l] > el) 
        return l; 
    if(v[h] > el)
        return h; 
    return v.size(); 
}

int main() {
    int n; 
    cin >> n; 
    vector<int> v(n); 
    for(int i = 0; i < n; i++) {
        cin >> v[i]; 
    }
    
    sort(v.begin(), v.end()); 

    int el; 
    cin >> el; 
    int lbIdx = lower_bound1(v, el); 
    cout << lbIdx << " " << (lbIdx != -1 ? v[lbIdx] : -1) << endl; 
    
    int ubIdx = upper_bound(v, el); 
    cout << ubIdx << " " << (ubIdx != -1 ? v[ubIdx] : -1) << endl; 

    return 0; 
}