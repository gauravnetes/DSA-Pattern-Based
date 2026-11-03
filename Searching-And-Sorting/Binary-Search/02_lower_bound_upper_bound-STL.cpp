#include <bits/stdc++.h>
using namespace std; 

int main() {
    int n; 
    cin >> n; 

    set<int> st; 
    for(int i = 0; i < n; i++) {
        int x; 
        st.insert(x); 
    }

    auto it = lower_bound(st.begin(), st.end(), 5); 
    cout << (*it) << endl; 
}

int main() {
    int n; 
    cin >> n; 

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }

    sort(a.begin(), a.end()); 
    for(int i = 0; i < n; i++) {
        cout << a[i] << " "; 
    }

    cout << endl;
      
    auto it = upper_bound(a.begin(), a.end(), 64); // params: {arr, The Next address of the array location till where we want to      find, for which element we want to find the lower_bound for} 
    if(it == a.end()) {
        cout << "Not Found"; 
        return 0; 
    }
    cout << (*it) << endl; 

    return 0; 
}

int main() {
    int n; 
    cin >> n; 

    int a[n]; 
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }

    sort(a, a+n); 
    for(int i = 0; i < n; i++) {
        cout << a[i] << " "; 
    }

    cout << endl;
      
    int *ptr = lower_bound(a, a+n, 64); // params: {arr, The Next address of the array location till where we want to      find, for which element we want to find the lower_bound for} 
    if(ptr == (a + n)) {
        cout << "Not Found"; 
        return 0; 
    }
    cout << (*ptr) << endl; 

    return 0; 
}