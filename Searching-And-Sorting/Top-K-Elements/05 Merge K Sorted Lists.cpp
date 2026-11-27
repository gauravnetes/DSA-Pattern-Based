#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto lambda = [] (ListNode* node1, ListNode* node2) {
            return node1->val > node2->val; 
        }; 

        priority_queue<ListNode*, vector<ListNode*>, decltype(lambda)> pq(lambda); 

        for(ListNode* node : lists) {
            if(node)    
                pq.push(node); 
        }

        if(pq.empty()) 
            return NULL; 

        ListNode* head = pq.top(); 
        pq.pop(); 

        if(head->next)
            pq.push(head->next); 

        ListNode* tail = head; 
        while(!pq.empty()) {
            ListNode* currNode = pq.top(); 
            pq.pop(); 
            tail->next = currNode; 
            tail = tail->next; 
            if(currNode->next)
                pq.push(currNode->next); 
        }
        return head; 
    }
};