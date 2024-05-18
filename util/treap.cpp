//
// Created by Nicktohzyu on 06/03/2023.
//
#include <bits/stdc++.h>
using namespace std;
class Treap{
    // lazy update and size tracking is not necessary for this problem, but it doesn't add much complexity
    struct node{
        node *l, *r;
        const int priority, key;
        int val, sum, lazy, size;
        node(int v, int key) : val(v) , sum(v), lazy(0), size(1), priority(rand()), key(key), l(nullptr), r(nullptr){}
    };
    using pnode = node*;
    pnode root;

    static int size(pnode t){
        return t ? t->size : 0;
    }

    /** @return subtree sum or 0 if empty */
    static int eval_lazy(pnode t){
        if(!t){
            return 0;
        }
        if(t->lazy != 0){
            t->val += t->lazy;
            t->sum += t->lazy * t->size;
            if(t->l){
                t->l->lazy += t->lazy;
            }
            if(t->r){
                t->r->lazy += t->lazy;
            }
            t->lazy = 0;
        }
        return t->sum;
    }

    static void update(pnode t){
        if(!t) return;
        t->size = 1 + size(t->l) + size(t->r);
        t->sum = t->val + eval_lazy(t->l) + eval_lazy(t->r);
    }

    /** @return pair of pnode with keys in left tree strictly less than target key */
    static pair<pnode, pnode> split(const pnode t, const int key){
        pnode l, r;
        if(!t){
            l=r=nullptr;
            return {l, r};
        }
        eval_lazy(t);
        if(t->key < key){
            tie(l, r) = split(t->r, key);
            t->r = l;
            l = t;
        } else {
            tie(l, r) = split(t->l, key);
            t->l = r;
            r = t;
        }
        update(t);
        return {l, r};
    }

    static tuple<pnode, pnode, pnode> split3(const pnode t, const int key_1, const int key_2){
        pnode l, r, mid;
        tie(l, r) = split(t, key_1);
        tie(mid, r) = split(r, key_2);
        return make_tuple(l, mid, r);
    }

    static pnode merge(const pnode l, const pnode r){
        pnode t;
        eval_lazy(l);
        eval_lazy(r);
        if(!l){
            t = r;
        } else if(!r){
            t = l;
        } else if(l->priority > r->priority){
            l->r = merge(l->r, r);
            t = l;
        } else {
            r->l = merge(l, r->l);
            t = r;
        }
        update(t);
        return t;
    }

    static pnode merge3(const pnode l, const pnode mid, const pnode r){
        pnode t = merge(l, mid);
        t = merge(t, r);
        return t;
    }

public:
    void insert(int val, int key){
        pnode l, r;
        tie(l, r) = split(root, key);
        // cout << "insert key:" << key << " val: " << val << " l size: " << size(l) << " r size: " << size(r);
        pnode cur = new node(val, key);
        root = merge3(l, cur, r);
        // cout << " root size: " << size(root) << endl;
    }
    int query_range_sum(int l_pos, int r_pos){
        pnode l, r, mid;
        tie(l, mid, r) = split3(root, l_pos, r_pos+1);
        eval_lazy(mid);
        int ans = mid->sum;
        // cout << "query l:" << l_pos << " r: " << r_pos << " l size: " << size(l) << " m size: " << size(mid)  << " r size: " << size(r) << " ans: " << mid->sum << endl;
        root = merge3(l, mid, r);
        return ans;
    }
    void update_range(int l_pos, int r_pos, int diff){
        pnode l, r, mid;
        tie(l, mid, r) = split3(root, l_pos, r_pos+1);
        // cout << "update l:" << l_pos << " r: " << r_pos << " l size: " << size(l) << " m size: " << size(mid)  << " r size: " << size(r) << " mid prev value: " << mid->val << " diff: " << diff << endl;
        mid->lazy += diff;
        root = merge3(l, mid, r);
    }
};