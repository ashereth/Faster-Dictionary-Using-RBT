#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

//constant values for red and black
const int black = 0;
const int red = 1;

// Helper Functions ---------------------------------------------

//transplant()
//used with remove for certain cases
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent==this->nil){
        this->root=v;
    }else if (u==u->parent->left)
    {
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    if(v!=nil){
        v->parent=u->parent;
    }
    
}


// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != nil) {
        if(R->color==black){
            s += R->key + "\n";
        }else{
            s += R->key + " (RED)\n";
        }
        
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R != nil && R!=N) { 
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if(R==nil){
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    /*if x == NIL or k == x.key
      return x
    else if k < x.key
      return TreeSearch(x.left, k)
    else // k > x.key
      return TreeSearch(x.right, k)*/
    if(R==nil || R->key==k){
        return R;
    }else if (k.compare(R->key)<0)
    {
        return search(R->left, k);
    }else{
        return search(R->right, k);
    }
} 

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    while(R->left!=nil){
        R=R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    while(R->right!=nil){
        R=R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    //if N is the rightmost node or nil return nil
    if(N==nil){
        return nil;
    }
    if(N->right!=nil){
        return this->findMin(N->right);
    }
    Node* y = N->parent;
    while(y!=nil && N==y->right){
        N=y;
        y=y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    //if N is the leftmost node or nil return nil
    if(N==nil){
        return nil;
    }
    if(N->left!=nil){
        return this->findMax(N->left);
    }
    Node* y = N->parent;
    while(y!=nil && N==y->left){
        N=y;
        y=y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent==this->nil){
        this->root=v;
    }else if (u==u->parent->left)
    {
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent=u->parent;
}

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* y = N->right;

    N->right = y->left;

    y->left->parent = N;
    
    y->parent=N->parent;
    if(N->parent==this->nil){
        this->root=y;
    }else if (N==N->parent->left){
        N->parent->left=y;
    }else{
        N->parent->right=y;
    }
    y->left=N;
    N->parent=y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node* y = N->left;

    N->left = y->right;

    y->right->parent=N;

    y->parent=N->parent;
    if(N->parent==this->nil){
        this->root=y;
    }else if (N==N->parent->right){
        N->parent->right=y;
    }else{
        N->parent->left=y;
    }
    
    y->right=N;
    N->parent=y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    Node* y;
    while(N->parent->color==red){
        if(N->parent==N->parent->parent->left){
            y=N->parent->parent->right;
            if(y->color==red){
                N->parent->color=black;
                y->color=black;
                N->parent->parent->color=red;
                N=N->parent->parent;
            }else{
                if(N==N->parent->right){
                    N=N->parent;
                    LeftRotate(N);
                }
                N->parent->color=black;
                N->parent->parent->color=red;
                RightRotate(N->parent->parent);
            }
        }else{
            y=N->parent->parent->left;
            if(y->color==red){
                N->parent->color=black;
                y->color=black;
                N->parent->parent->color=red;
                N=N->parent->parent;
            }else{
                if(N==N->parent->left){
                    N=N->parent;
                    RightRotate(N);
                }
                N->parent->color=black;
                N->parent->parent->color=red;
                LeftRotate(N->parent->parent);
            }
        }
    }
    this->root->color=black;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* w;
    while(N!=this->root && N->color==black){
        if(N==N->parent->left){
            w=N->parent->right;
            if(w->color==red){
                w->color=black;
                N->parent->color=red;
                LeftRotate(N->parent);
                w=N->parent->right;
            }
            if (w->left->color==black && w->right->color==black){
                w->color=red;
                N=N->parent;
            }else{
                if(w->right->color==black){
                    w->left->color=black;
                    w->color=red;
                    RightRotate(w);
                    w=N->parent->right;
                }
                w->color=N->parent->color;
                N->parent->color=black;
                w->right->color=black;
                LeftRotate(N->parent);
                N=this->root;
            }  
        }else{
            w=N->parent->left;
            if(w->color==red){
                w->color=black;
                N->parent->color=red;
                RightRotate(N->parent);
                w=N->parent->left;
            }
            if(w->right->color==black && w->left->color==black){
                w->color=red;
                N=N->parent;
            }else{
                if(w->left->color==black){
                    w->right->color=black;
                    w->color=red;
                    LeftRotate(w);
                    w=N->parent->left;
                }
                w->color=N->parent->color;
                N->parent->color=black;
                w->left->color=black;
                RightRotate(N->parent);
                N=this->root;
            }
        }
    }
    N->color=black;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    int y_original_color = y->color;
    Node* x;
    //if we are deleting the current node then set current to nil
    if(N==this->current){
        this->current=this->nil;
    }
    if(N->left==this->nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }else if (N->right==this->nil){
        x=N->left;
        RB_Transplant(N, N->left);
    }else{
        y = this->findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent==N){
            x->parent=y;
        }else{
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left=N->left;
        y->left->parent=y;
        y->color=x->color;
    }
    if(y_original_color==black){
        RB_DeleteFixUp(x);
    }
}


// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = black;
}

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->parent = nullptr;
    nil->left = nullptr;
    nil->right = nullptr;

    // Set root/current to be the nil dummy node
    root = nil;
    current = nil;

    // Set number of pairs to be 0 initially
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    Node* empty = new Node("", 0);
    empty->parent = nullptr;
    empty->left = nullptr;
    empty->right = nullptr;

    // Set root/nil/current to be the new dummy node
    root = empty;
    nil = empty;
    current = nil;

    // Set number of pairs to be 0 initially
    num_pairs = 0;
    //call preorder copy starting from D's root and going to D's nil Node
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return this->num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if(this->search(this->root, k)!=nil){
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(!this->contains(k)){
        throw std::out_of_range("getValue(): key does not exist");
    }
    Node* value = this->search(this->root, k);
    return value->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(this->current!=nil){
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(!this->hasCurrent()){
        throw std::out_of_range("currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!this->hasCurrent()){
        throw std::out_of_range("currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // If key already exists, update value
    Node* existingNode = this->search(root, k);
    
    if (existingNode != nil) {
        existingNode->val = v;
    }else {
        this->num_pairs+=1;
        Node* z = new Node(k, v);
        Node* y = this->nil;
        Node* x = this->root;
        while(x!=this->nil){
            y=x;
            if(z->key<x->key){
                x=x->left;
            }else{
                x=x->right;
            }
        }
        z->parent=y;
        if(y==this->nil){
            this->root=z;
        }else if (z->key<y->key){
            y->left=z;
            z->parent=y;
        }else{
            y->right=z;
            z->parent=y;
        }
        z->left=this->nil;
        z->right=this->nil;
        z->color=red;
        RB_InsertFixUp(z);
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(!this->contains(k)){
        throw std::out_of_range("remove(): key does not exist");
    }
    Node* z = this->search(this->root, k);
    RB_Delete(z);//call RB_delete
    //decriment num_pairs
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(num_pairs>0){
        current = this->findMin(this->root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(num_pairs>0){
        current = this->findMax(this->root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(!this->hasCurrent()){
        throw std::out_of_range("next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!this->hasCurrent()){
        throw std::out_of_range("prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string result;
    inOrderString(result, root);
    return result;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. The key order is 
// given by a pre-order tree walk. The keys stored in black Nodes will appear in
// the returned string as "key\n", and the keys stored in red Nodes will appear 
// as "key (RED)\n".  The output of this function is demonstrated in 
// /Examples/pa8/DictionaryClient-out.
std::string Dictionary::pre_string() const{
    std::string result;
    preOrderString(result, root);
    return result;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    //order of pairs doesnt matter so just 
    // inorder traverse them and compare result
    std::string thisstring = this->to_string();
    std::string thatstring = D.to_string();

    // Compare the string representations of the dictionaries
    return thisstring == thatstring;
}

// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    std::string string = D.to_string();
    stream << string;
    return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    this->clear();
    this->preOrderCopy(D.root, D.nil);
    return *this;
}

