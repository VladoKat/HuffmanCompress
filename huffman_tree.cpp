#include "huffman_tree.h"
#include<vector>
#include<stack>
#include<cmath>

std::string reconvert(unsigned char symbol){
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

// std::string reconvertWithoutFill(unsigned char symbol){
//   std::string result;
//   std::stack<unsigned char> buffer;
//   unsigned char toPush;
//   while(symbol > 0){
//     toPush = symbol % 2 + 48;
//     symbol /= 2;
//     buffer.push(toPush);
//   }
//   while(!buffer.empty()){
//     result.push_back(buffer.top());
//     buffer.pop();
//   }
//
//   return result;
// }

unsigned char convert(const std::string& str){
  unsigned char result;
  int exponent = str.length();
  for(int i = 0; i < exponent; i++){
    result += (str[i]-48)*pow(2, (exponent-i-1));
  }
  return result;
}


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
  int min = trees[0]->root->numOcc;
  HuffmanTree* minTree = trees[0];
  for(HuffmanTree* tree : trees){
    if(tree->root->numOcc < min){
      min = tree->root->numOcc;
      minTree = tree;
    }
  }
  HuffmanTree* newTree = new HuffmanTree(*minTree);
  return *newTree;
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
  HuffmanTree* toPush = new HuffmanTree(min1.root->numOcc + min2.root->numOcc,min1.root->symbol);
  toPush->root->left = copyFrom(min1.root);
  toPush->root->right = copyFrom(min2.root);
  trees.push_back(toPush);
  makeTree(trees);
}

HuffmanTree::HuffmanTree(FrequencyTable table){
  std::vector<HuffmanTree*> trees;
  for(int symb = 0; symb < table.size(); symb++){
    if(table[symb] > 0){
      trees.push_back(new HuffmanTree(table[symb], (unsigned char)symb)) ;
    }

  }
  makeTree(trees);
  root = copyFrom(trees[0]->root);
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

std::string HuffmanTree::strPrint(TreeNode* curr){
  if (!curr)
  {
    return "{}";
  }
  std::string symbol;
  symbol.push_back(curr->symbol);
  return "{" + symbol + strPrint (curr->left) + strPrint(curr->right) + "}";
}
std::ostream& operator<< (std::ostream& out, const HuffmanTree& tree){
  HuffmanTree::writeHelper(out, tree.root);
  return out;
}

HuffmanTree::TreeNode* HuffmanTree::readFromStream(std::istream& in){
  //Directly copied from Kalin's LISP print
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

std::string HuffmanTree::decompress(const std::string& txt, const std::string& lastBins){
  std::string tempRes = "";
  for(int i = 0; i < txt.size(); i++){
    tempRes = tempRes + reconvert(txt[i]);
  };
  tempRes = tempRes + lastBins;
  std::string result;
  traverse(tempRes, result);
  return result;
}

void HuffmanTree::getFromTree(TreeNode* curr, std::string& str, unsigned char& result){
  if(curr && !curr->left && !curr->right){
    result = curr->symbol;
    return;
  }
  if(str.empty() || !curr){
    if(str.empty()){
      std::cout << "smth wrong!___________________________";
    }
    if(!curr){
      std::cout << "smth other went wrong____________";
    }
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
void HuffmanTree::traverse(std::string binary,std::string& result){

  unsigned char toPush = 0;
  while(!binary.empty()){
    getFromTree(root, binary, toPush);
    result.push_back(toPush);
  }
}

std::string HuffmanTree::compress (const std::string& textToCompress){
  Map myMap(*this);
  std::string result;
  for(int i = 0; i < textToCompress.size(); i++){
    result += myMap[textToCompress[i]];
  }
  int index = 0;
  std::string realResult;
  int iterations = result.size()/8;
  for(int i = 0; i < iterations; i++){
    std::cout << ""; //no idea why. crashes otherwise
    unsigned char num = convert(result.substr(8*i, 8));
    realResult.push_back(num);
  }
  realResult = (result.substr(iterations*8, 8)) + strPrint(root) + realResult;

  return realResult;
}
