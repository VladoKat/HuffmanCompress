#include "huffman_tree.h"
#include<vector>
#include<stack>



HuffmanTree::TreeNode::~TreeNode(){
  if(left)
  delete left;
  if(right)
  delete right;
}

HuffmanTree::~HuffmanTree(){
  if(root)
  delete root;
}
HuffmanTree::HuffmanTree():root(nullptr){}

void HuffmanTree::printHelper(TreeNode* curr){
  if(curr){
    std::cout << curr->symbol << " - " << curr->numOcc << "  ";
    printHelper(curr->left);
    printHelper(curr->right);
  }
}
void HuffmanTree::print(){
  printHelper(root);
  std::cout << "\n";
}

void HuffmanTree::printLeavesHelper(TreeNode* curr){
  if(curr && !curr->left && !curr->right){
    std::cout << curr->symbol << " - " << curr->numOcc << "\n";
  }
  if(!curr){
    return;
  }
  printLeavesHelper(curr->left);
  printLeavesHelper(curr->right);
}
void HuffmanTree::printLeaves(){
  printLeavesHelper(root);
  std::cout << "\n";
}
HuffmanTree::TreeNode* HuffmanTree::copyFrom(TreeNode* crr){
  if(!crr){
    return nullptr;
  }
  return new HuffmanTree::TreeNode(crr->numOcc, crr->symbol,
                      copyFrom(crr->left), copyFrom(crr->right));
}
HuffmanTree::HuffmanTree(const HuffmanTree& other){
  root = copyFrom(other.root);
}

HuffmanTree::HuffmanTree(int numOcc, char symbol) {
  root = new HuffmanTree::TreeNode(numOcc, symbol);
}

HuffmanTree HuffmanTree::findMin(std::vector<HuffmanTree*> trees){
  //std::cout << "findingMIn\n";
  int min = trees[0]->root->numOcc;
  HuffmanTree* minTree = trees[0];
  for(HuffmanTree* tree : trees){
    if(tree->root->numOcc < min){
      min = tree->root->numOcc;
      minTree = tree;
    }
  }
  return *minTree;
}

void HuffmanTree::remove(std::vector<HuffmanTree*>& trees, const HuffmanTree& toRemove){
  std::vector<HuffmanTree*> result;
  for(HuffmanTree* tree : trees){
    if(!(tree->root->numOcc == toRemove.root->numOcc &&
       tree->root->symbol == toRemove.root->symbol)){
         result.push_back(tree);
    } else {
      delete tree;
    }
  }
  trees = result;
}

void HuffmanTree::makeTree(std::vector<HuffmanTree*>& trees){
  if(trees.size() == 1){
    return;
  }
  HuffmanTree min1 = findMin(trees);
  HuffmanTree::remove(trees, min1);
  HuffmanTree min2 = findMin(trees);
  HuffmanTree::remove(trees, min2);
//  std::cout << "removed\n";
  //creating new tree
  HuffmanTree* toPush = new HuffmanTree(min1.root->numOcc + min2.root->numOcc,min1.root->symbol);
  toPush->root->left = copyFrom(min1.root);
  toPush->root->right = copyFrom(min2.root);
  //end of creating new tree
  trees.push_back(toPush);
  // for(int i = 0 ; i < trees.size(); i++){
  //   trees[i]->print();
  // }
  // std::cout << "\n\n";
  makeTree(trees);
}

HuffmanTree::HuffmanTree(FrequencyTable table){
  std::vector<HuffmanTree*> trees;
  for(int i = 0; i < table.table.size(); i++){
    trees.push_back(new HuffmanTree(table.table[i].numOcc, table.table[i].symbol)) ;
  }
  makeTree(trees);
  root = copyFrom(trees[0]->root);
  //trees[0]->printLeaves();
}

void HuffmanTree::writeHelper (std::ostream& out, TreeNode* curr){
  if (!curr)
  {
    out << "{}";
    return;
  }

  out << "{" << curr->symbol;
  writeHelper (out, curr->left);
  writeHelper (out, curr->right);
  out << "}";
}
std::ostream& operator<< (std::ostream& out, const HuffmanTree& tree){
  HuffmanTree::writeHelper(out, tree.root);
  return out;
}

HuffmanTree::TreeNode* HuffmanTree::readFromStream(std::istream& in){
  //(A(A()())(C(C(C()())(D()()))(B(B()())(R()()))))
  unsigned char nextChar;
  nextChar = in.get();//assert (nextChar == '(');
  nextChar = in.get(); // get Value
  if (nextChar == '}')
  {
    return nullptr;
  }
  unsigned char rootValue = nextChar;
  TreeNode *leftSubTree;
  leftSubTree = readFromStream (in);
  TreeNode *rightSubTree;
  rightSubTree = readFromStream (in);
  nextChar = in.get();//assert (nextChar == ')');
  return new TreeNode(0, rootValue, leftSubTree, rightSubTree);
}
void HuffmanTree::read(std::istream& input){
  this->root = readFromStream(input);
}

std::string HuffmanTree::decompress(const std::string& txt){
  std::string tempRes = "";
  for(int i = 0; i < txt.size()-1; i++){
    tempRes = tempRes + this->reconvert(txt[i]);
  }
  tempRes = tempRes + reconvertWithoutFill(txt[txt.size()-1]);
  std::cout << " binary - " << tempRes << "\n";
  std::string result = traverse(tempRes);
  return result;
}

void HuffmanTree::getFromTree(TreeNode* curr, std::string& str, unsigned char& result){
  if(curr && !curr->left && !curr->right){
    result = curr->symbol;
    return;
  }
  if(str.empty()){
    std::cout << "smth wrong!";
    return;
  }

  if(str[0] == '0'){
    str = str.substr(1, str.size());
    getFromTree(curr->left, str, result);
  } else {
    str = str.substr(1, str.size());
    getFromTree(curr->right, str, result);
  }
}
std::string HuffmanTree::traverse(std::string binary){
  //std::cout << "traversing\n";
  if(binary == ""){
    return "";
  }
  unsigned char toPush = 0;
  getFromTree(root, binary, toPush);
  std::string symb;
  symb.push_back(toPush);
  std::cout << toPush << " ";
  return symb + traverse(binary);
}

std::string HuffmanTree::reconvertWithoutFill(unsigned char symbol){
  std::string result;
  std::stack<unsigned char> buffer;
  unsigned char toPush;
  while(symbol > 0){
    toPush = symbol % 2 + 48;
    symbol /= 2;
    buffer.push(toPush);
  }
  while(!buffer.empty()){
    result.push_back(buffer.top());
    buffer.pop();
  }

  return result;
}

std::string HuffmanTree::reconvert(unsigned char symbol){
  std::string result;
  std::stack<unsigned char> buffer;
  unsigned char toPush;
  while(symbol > 0){
    toPush = symbol % 2 + 48;
    symbol /= 2;
    buffer.push(toPush);
  }
  int size = buffer.size();
  while(size < 8){
    buffer.push('0');
    size++;
  }
  while(!buffer.empty()){
    result.push_back(buffer.top());
    buffer.pop();
  }

  return result;
}
