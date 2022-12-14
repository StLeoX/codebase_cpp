#include <algorithm>
#include <cstdio>
#include <vector>

namespace Treap {
    typedef int ll;
    struct Node;
    typedef const Node *Pointer;
    namespace Pool {
        const int RESERVE = 2e7;
        std::vector<Node> pool;
        void initial() {
            pool.reserve(RESERVE);
        }
    }
    struct Node {
        ll value;
        int cnt = 0, size, weight;
        Pointer L = nullptr, R = nullptr;
        void pushup() {
            size = cnt;
            if (L)
                size += L->size;
            if (R)
                size += R->size;
        }
        Node() {}
        Node(ll value) : value(value) {
            weight = rand();
            pushup();
        }
        Node *alloc() const {
            Pool::pool.push_back(*this);
            return &Pool::pool.back();
        }
        Node *clone() const {
            return this->alloc();
        }
    };
    enum Poset {
        le = 0,
        leq = 1
    };
    template <Poset po = le>
    std::pair<Pointer, Pointer> split(Pointer u, ll x) {
        if (u == nullptr)
            return std::make_pair(nullptr, nullptr);
        auto n = u->clone();
        if (po == le ? u->value < x : u->value <= x) {
            auto o = split<po>(u->R, x);
            n->R = o.first;
            n->pushup();
            return std::make_pair(n, o.second);
        } else {
            auto o = split<po>(u->L, x);
            n->L = o.second;
            n->pushup();
            return std::make_pair(o.first, n);
        }
    }
    Pointer merge(Pointer u, Pointer v) {
        if (!(u && v)) {
            return u ? u : v;
        }
        if (u->weight > v->weight) {
            auto n = u->clone();
            n->R = merge(u->R, v);
            n->pushup();
            return n;
        } else {
            auto n = v->clone();
            n->L = merge(u, v->L);
            n->pushup();
            return n;
        }
    }
    namespace Set {
        Pointer find(Pointer u, ll x) {
            while (u && x != u->value) {
                u = x < u->value ? u->L : u->R;
            }
            return u;
        }
        Pointer insert(Pointer root, ll value) {
            auto n = root ? root->clone() : Node(value).alloc();
            if (root == nullptr || value == root->value)
                n->cnt++, n->pushup();
            else if (value < root->value)
                n->L = insert(root->L, value), n->pushup();
            else
                n->R = insert(root->R, value), n->pushup();
            return n;
        }
        Pointer erase(Pointer root, ll value) {
            if (root == nullptr)
                return nullptr;
            if (value == root->value && root->cnt == 1)
                return merge(root->L, root->R);
            auto n = root->clone();
            if (value == root->value && root->cnt > 1)
                n->cnt--, n->pushup();
            else if (value < root->value)
                n->L = erase(root->L, value), n->pushup();
            else
                n->R = erase(root->R, value), n->pushup();
            return n;
        }
        int rankof(Pointer root, ll value) {
            auto o = split(root, value);
            return (o.first ? o.first->size : 0) + 1;
        }
        Pointer placeof(Pointer root, int kth) {
            if (kth < 1 || root->size < kth)
                return nullptr;
            for (auto x = root;;) {
                int left = x->L ? x->L->size : 0, mid = x->cnt;
                if (kth <= left) {
                    x = x->L;
                    continue;
                }
                if (kth <= left + mid) {
                    return x;
                }
                kth -= left + mid, x = x->R;
            }
        }
        Pointer pre(Pointer root, ll value) {
            if (!root)
                return nullptr;
            if (root->value < value) {
                auto r = pre(root->R, value);
                return r ? r : root;
            }
            return pre(root->L, value);
        }
        Pointer suc(Pointer root, ll value) {
            if (!root)
                return nullptr;
            if (root->value > value) {
                auto r = suc(root->L, value);
                return r ? r : root;
            }
            return suc(root->R, value);
        }
    }
}

int main() {
    Treap::Pool::initial();
    std::vector<Treap::Pointer> history(1);
    int n;
    scanf("%d", &n);
    for (int cas = 1, ver, opt; cas <= n; cas++) {
        Treap::ll val;
        scanf("%d%d%d", &ver, &opt, &val);
        auto S = history[ver];
        if (opt == 1)
            S = Treap::Set::insert(S, val);
        if (opt == 2)
            S = Treap::Set::erase(S, val);
        if (opt == 3)
            printf("%d\n", Treap::Set::rankof(S, val));
        if (opt == 4)
            printf("%d\n", Treap::Set::placeof(S, val)->value);
        if (opt == 5)
            printf("%d\n", Treap::Set::pre(S, val)->value);
        if (opt == 6)
            printf("%d\n", Treap::Set::suc(S, val)->value);
        history.push_back(S);
    }
}
