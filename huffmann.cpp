#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

class node{
    public:
    char ch;
    int val;
    node* left;
    node* right;

    node(char c, int d){
        ch = c;
        val = d;
        left = nullptr;
        right = nullptr;
    }
};

class comp{
    public:
    bool operator()(node* a,node* b){
        return a->val > b->val;
    }
};

class huff{
    public:
    int seed;
    node* root;
    map<char,string> mp;

    int hash(int i){
        return abs(29*seed*i - (i*i-seed)%999);
    }

    void inorder(node* r, string s){
        if(r->left != nullptr){
            inorder(r->left,s+'0');
        }

        if(r->right != nullptr){
            inorder(r->right,s+'1');
        }
        
        if(r->ch!='-'){
            mp[r->ch] = s;
        }
    }

    void solve(){
        priority_queue<node*, vector<node*>, comp> pq;
        for(int i=0;i<128;i++){
            char x = i;
            node* temp = new node( x,hash(i));
            pq.push(temp);
        }
        
        while(pq.size()>1){
            node* a = pq.top(); pq.pop();
            node* b = pq.top(); pq.pop();
            node* c = new node('-',a->val+b->val);
            if(a->val > b->val){
                c->left = b; c->right=a;
            }
            else{
                c->left = a; c->right=b;
            }
            pq.push(c);
        }
        
        root = pq.top();

        inorder(root,"");

    }

    string encrypt(string content){
        string s="";

        for(int i=0;i<content.length();i++){
            s+=mp[content[i]];
        }

        return s;
    }

    string decrypt(string code){
        string ans="";
        node* temp = root;

        for(int i=0;i<code.length();i++){
            if(code[i]=='0'){
                temp = temp->left;
            }
            if(code[i]=='1'){
                temp = temp->right;
            }

            if(temp->ch!='-'){
                ans+=temp->ch;
                temp = root;
            }
        }

        return ans;
    }
};

int main(){
    cout<<"enter a password for file"<<endl;
    int x;cin>>x;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    huff H;
    H.seed = 1;
    H.solve();
    cout<<"type your message"<<endl;
    string content; 
    getline(cin,content);
    string sg = H.encrypt(content);
    cout<<sg<<endl;
    string hg = H.decrypt(sg);
    cout<<hg<<endl;

    return 0;
}
