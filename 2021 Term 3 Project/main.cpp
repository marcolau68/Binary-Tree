#include <iostream>
#include <vector>
#include <string>
 
 
struct BNode{
    std::string val;
    BNode* left;
    BNode* right;
 
};

BNode* cons_node(std::string val, BNode* left, BNode* right) {
    BNode* t;
    t = new BNode;
    
    t->val = val;
    t->left = left;
    t->right = right;
    
    return t;
}

void print_tree(BNode* t){
    if(t != NULL){
        print_tree(t->left);
        std::cout << t->val << std::endl;
        print_tree(t->right);
    }
}


BNode* build_tree(BNode* t, int layer, int i = 1) {
    
    if (i == layer + 1) {
        BNode* tmp = cons_node("0", NULL, NULL);
        
        return tmp;
    }
    else {
        std::string name = "x" + std::to_string(i);
        BNode* tmp = cons_node(name, NULL, NULL);
        
        tmp->left = build_tree(tmp->left, layer, i + 1);
        
        tmp->right = build_tree(tmp->right, layer, i + 1);
        
       return tmp;
    }
    
}

void list_leaves(BNode* t, std::vector<std::string>& leaves) {

    if (t != NULL) {
        list_leaves(t->left, leaves);

        if (t->val == "0" || t->val == "1") {
            leaves.push_back(t->val);
        }

        list_leaves(t->right, leaves);
        
      }

}

void reduce_tree(BNode*& t) {
    if (t->left != NULL) {
        reduce_tree(t->left);
        reduce_tree(t->right);

        std::vector<std::string> left_leaves = {}, right_leaves = {};

        list_leaves(t->left, left_leaves);
        list_leaves(t->right, right_leaves);

        if (left_leaves == right_leaves && t->left->val == t->right->val) {
            t = t->left;
        }
    }
}
 
// do not alter the following line that begins the function build_bt
BNode* build_bt(const std::vector<std::string>& fvalues){
    BNode* tmp;
    tmp = new BNode;
    int layer = int(fvalues[0].size());
    
    BNode* tree = build_tree(tmp, layer);

    for (int i = 0; i < fvalues.size(); i++) {

        tmp = tree;

        for (int j = 0; j < fvalues[i].size(); j++) {
          
            if (fvalues[i][j] == '0') {
                tmp = tmp->left;
            }
            else {
                tmp = tmp->right;
            }

        }

        tmp->val = "1";
    }

    reduce_tree(tree);

    return tree;
    
}
 
// do not alter the following function
// this function converts e.g. std::string "x3" to int 2
int label_to_idx(const std::string& label){
 
    std::string out;
 
    for(int i = 1; i < label.size(); i++){
        out.push_back(label[i]);
    }
 
    return std::stoi(out) - 1;
}
 
// do not alter the following function
std::string eval_bt(BNode* bt, const std::string& input){
 
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val;
    }
    else{
        int idx = label_to_idx(bt->val);
        std::string input_idx;
        input_idx.push_back(input[idx]);
 
        if(input_idx == "0"){
            return eval_bt(bt->left, input);
        }
        else{
            return eval_bt(bt->right, input);
        }
    }
}
 
// do not alter the following function
int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}

void deallocate_tree(BNode* t){
    if(t != NULL){
        deallocate_tree(t->left);
        deallocate_tree(t->right);
        delete t;
    }
}
 
class BoolTree{
public:
 
    BoolTree(const std::vector<std::string>& fvalues){
       t = build_bt(fvalues);
    }
 
    std::string eval(const std::string& s){
        return eval_bt(t, s);
    }
 
    int n_nodes(){
        return n_nodes_bt(t);
    }
    
    void print() {
        print_tree(t);
    }
 
    ~BoolTree(){
        
        deallocate_tree(t);
        
    }
 
private:
    BNode* t;
};
 
 
int main(){
 
    std::vector<std::string> fv;
    std::string row;
 
    row = "11";
    fv.push_back(row);
 
    BoolTree ft1(fv);
 
    fv.clear();
 
    row = "010";
    fv.push_back(row);
    row = "011";
    fv.push_back(row);
    row = "110";
    fv.push_back(row);
    row = "111";
    fv.push_back(row);
 
    BoolTree ft2(fv);
    // this corresponds to the f(x1, x2, x3) example shown above
 
    std::cout << ft1.n_nodes() << std::endl;
    // we expect this to print 5

    std::cout << ft2.n_nodes() << std::endl;
    // if the algorithm is such that it builds the smallest possible corresponding tree
    // for the boolean function we are considering
    // then this will print 3 (see tree diagram in the example above)

    std::cout << ft1.eval("01") << std::endl;
    // this should print "0"

    std::cout << ft1.eval("11") << std::endl;
    // this should print "1"

    std::cout << ft2.eval("001") << std::endl;
    // this should print "0"

    std::cout << ft2.eval("110") << std::endl;
    // this should print "1"
    
    std::vector<std::string> list = {"0000", "0001", "0100", "0101", "1000", "1001", "1011", "1010"};
    
    BoolTree ft3(list);
    
    std::cout << ft3.n_nodes() << std::endl;

    std::cout << ft3.eval("1001") << std::endl;

    std::cout << ft3.eval("0111") << std::endl;
    
    ft3.print();
 
}
