#ifndef QP_BINARYTREE_H__
#define QP_BINARYTREE_H__


template <typename T>

struct Node{
	T datum_;
	Node<T>* left_;
	Node<T>* right_;

	Node(): left_(nullptr),right_(nullptr) {};
	Node(T const& val): left_(nullptr), right_(nullptr), datum_(val) {};

	bool hasLeft(){
		return left_!=nullptr;
	}

	bool hasRight(){
		return right_!=nullptr;
	}
};


template <typename T>

struct BinaryTree{
	Node<T>* root_;

	BinaryTree(): root_(nullptr) {};


	bool empty(){
		return root_==nullptr;
	}

	void insert(T const& val){
		Node<T>* leaf=new Node<T>(val);

		if(empty())
			root_=leaf;

		else
			insert(root_,leaf);
	}

	void insert(Node <T>* root,Node<T>* leaf){
		if(leaf->datum_ > root->datum_){
			if(root->hasRight())
				insert(root->right_,leaf);
			else{
				root->right_=leaf;
				return;
			}
		}
		else{
			if(root->hasLeft())
				insert(root->left_,leaf);
			else{
				root->left_=leaf;
				return;
			}
		}
	}

	void displayIn(){
		displayIn(root_);
	}

	void displayIn(Node<T>* root){
		if(root==NULL)
			return;
	
		displayIn(root->left_);
		std::cout<<(root->datum_)<<" ";
		displayIn(root->right_);
	}

	T max(){
		return max(root_);
	}

	T max(Node<T>* root){
		Node<T>* tmp=root;

		while(tmp->hasRight())
			tmp=tmp->right_;

		return tmp->datum_;
	}

	T min(){
		return min(root_);
	}

	T min(Node<T>* root){
		Node<T>* tmp=root;

		while(tmp->hasLeft())
			tmp=tmp->left_;

		return tmp->datum_;
	}

	int maxDepth(){
		return maxDepth(root_);
	}

	int maxDepth(Node<T>* root){
		if(root==nullptr)
			return 0;
		else
			return 1+std::max(maxDepth(root->left_),maxDepth(root->right_));
	}

	bool member(T const& val){
		return member(val,root_);
	}

	bool member(T const& val, Node<T>* root){
		if(root==nullptr)
			return false;
		if(root->datum_==val)
			return true;
		if(val < root->datum_)
			return member(val,root->left_);
		else
			return member(val,root->right_);
	}
};



//ifndef QP_BINARYTREE_H_
#endif