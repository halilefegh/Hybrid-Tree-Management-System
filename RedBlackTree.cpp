#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
    : root(nullptr)
{
}

RedBlackTree::~RedBlackTree()
{
    clear();
}

void RedBlackTree::clear()
{
    clear(root);
    root = nullptr;
}

void RedBlackTree::clear(ResearcherNode *node)
{
    //TODO:
    if (node==nullptr)
    {
        return;
    }
    clear(node->right);
    clear(node->left);
    delete node;
    node=nullptr;
    
}

ResearcherNode *RedBlackTree::findResearcher(const std::string &fullName) const
{
    return find(root, fullName);
}

ResearcherNode *RedBlackTree::find(ResearcherNode *node, const std::string &fullName) const
{

//TODO: search and find researcher by name
    if (node==nullptr)
    {
        return nullptr;
    }
    if (node->data.fullName==fullName)
    {
        return node;
    }
    else{
        if (fullName>node->data.fullName)
        {
            return find(node->right,fullName);
        }
        else{
            return find(node->left,fullName);
        }
        
    }
    
    
}

bool RedBlackTree::insertResearcher(const Researcher &researcher)
{
    //attempt to insert, erturn true if success, false otherwise
    if (findResearcher(researcher.fullName))
    {
        return false;
    }
    
    ResearcherNode* node= new ResearcherNode(researcher);
    bool inserted=false;

    if (root==nullptr)
    {
        root=node;
        root->color=BLACK;
        return true;
    }
    


    ResearcherNode* fixup = bstInsert(root,node,inserted);
    insertFixup(fixup);
    return inserted;
    
    
}

ResearcherNode *RedBlackTree::bstInsert(ResearcherNode *current, ResearcherNode *node, bool &inserted)
{
    // TODO:
    // 1) Standard BST insert by node->data.fullName.
    // 2) If tree is empty, node becomes root (set inserted = true).
    // 3) If name already exists, inserted = false and return current without inserting.
    // 4) Otherwise insert and set inserted = true.
    // 5) Do not modify colors here (node->color already RED).
    std::string currentName,nodeName;
    
    if (current==nullptr)
    {
        return nullptr;
    }
    currentName=current->data.fullName;
    nodeName=node->data.fullName;
    if (current->data.fullName==node->data.fullName)
    {
        inserted=false;
        return current;
    }
    if (nodeName>currentName)
    {
        if (current->right==nullptr)
        {
            inserted=true;
            current->right=node;
            node->parent=current;
            return node;
        }
        
        return bstInsert(current->right,node,inserted);
    }
    else{
        if (current->left==nullptr)
        {
            inserted=true;
            current->left=node;
            node->parent=current;
            return node;
        }
        
        return bstInsert(current->left,node,inserted);
    }
    
    
    
    
    
}


void RedBlackTree::insertFixup(ResearcherNode *node)
{
    
    ResearcherNode* parent=node->parent;
    if (parent==nullptr)
    {
        node->color=BLACK;
        return;
    }
    
    if (node->color==RED && parent->color==RED)
    {
        ResearcherNode* GrandParent=nullptr;
        ResearcherNode* Uncle=nullptr;
        if (parent!=nullptr)
        {
            GrandParent=parent->parent;
        }
        if (GrandParent!=nullptr)
        {
            if (parent==GrandParent->right)
            {
                Uncle=GrandParent->left;
            }
            else{
                Uncle=GrandParent->right;
            }
            
        }
        if (Uncle!=nullptr&&Uncle->color==RED)
        {   
            if (GrandParent!=nullptr)
            {
                GrandParent->color=RED;
            }
            parent->color=BLACK;
            Uncle->color=BLACK;
            return insertFixup(GrandParent);    
        }
        else{
            if (GrandParent!=nullptr)
            {
                if (parent==GrandParent->right&&node==parent->left)
                {
                    rotateRight(parent);
                }
                else if(parent==GrandParent->left&&node==parent->right){
                    rotateLeft(parent);
                }
                else if(parent==GrandParent->right){
                    GrandParent->color=RED;
                    parent->color=BLACK;
                    rotateLeft(GrandParent);
                }
                else{
                    GrandParent->color=RED;
                    parent->color=BLACK;
                    rotateRight(GrandParent);
                }
                
            }
            
        }
        


    }
    else{
        return;
    }

    
    
    
    
}
    

    
    
    


bool RedBlackTree::removeResearcher(const std::string &fullName)
{
    // TODO:
    // 1) Find node z with data.fullName == fullName.
    // 2) If not found, return false.
    // 3) Perform standard RBT delete:
    //    - Track original color of removed node.
    //    - If a black node is removed, call deleteFixup on the appropriate child.
    // 4) Free node memory.
    // 5) Return true.
    ResearcherNode *z = root;
    while (z != nullptr)
    {
        if (fullName == z->data.fullName)
        {
            break;
        }
        if (fullName < z->data.fullName)
        {
            z = z->left;
        }
        else
        {
            z = z->right;
        }
    }

    if (z == nullptr)
    {
        return false;
    }

    
    ResearcherNode *y = z; 
    ResearcherNode *x = nullptr;
    ResearcherNode *xParent = nullptr; 

    
    Color y_original_color = y->color;

    
    if (z->left == nullptr)
    {
        x = z->right;
        xParent = z->parent; 
        
        
        if (z->parent == nullptr) root = z->right;
        else if (z == z->parent->left) z->parent->left = z->right;
        else z->parent->right = z->right;
        if (z->right != nullptr) z->right->parent = z->parent;
    }
    
    else if (z->right == nullptr)
    {
        x = z->left;
        xParent = z->parent;

        if (z->parent == nullptr) root = z->left;
        else if (z == z->parent->left) z->parent->left = z->left;
        else z->parent->right = z->left;
        if (z->left != nullptr) z->left->parent = z->parent;
    }
    
    else
    {
        
        y = z->right;
        while (y->left != nullptr)
        {
            y = y->left;
        }

        y_original_color = y->color;
        x = y->right;

        
        if (y->parent == z)
        {
            xParent = y;
        }
        else
        {
            xParent = y->parent;
            if (y->parent == nullptr) root = y->right;
            else if (y == y->parent->left) y->parent->left = y->right;
            else y->parent->right = y->right;
            if (y->right != nullptr) y->right->parent = y->parent;

            y->right = z->right;
            y->right->parent = y;
        }

       
        if (z->parent == nullptr) root = y;
        else if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
        y->parent = z->parent;

        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

 
    delete z;

   
    if (y_original_color == BLACK)
    {
        deleteFixup(x, xParent);
    }

    return true;
}

void RedBlackTree::deleteFixup(ResearcherNode *node, ResearcherNode *parent)
{
    // TODO: Standard Red-Black deletion fixup.
    ResearcherNode *w = nullptr;
    while (node != root && (node == nullptr || node->color == BLACK))
    {
        if (node == parent->left)
        {
            w = parent->right; 

            
            if (w != nullptr && w->color == RED)
            {
                w->color = BLACK;
                parent->color = RED;
                rotateLeft(parent);
                w = parent->right; 
            }

            
            if ((w == nullptr) || 
               ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)))
            {
                if (w != nullptr) w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                
                if (w->right == nullptr || w->right->color == BLACK)
                {
                    if (w->left != nullptr) w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = parent->right;
                }

                
                w->color = parent->color;
                parent->color = BLACK;
                if (w->right != nullptr) w->right->color = BLACK;
                rotateLeft(parent);
                node = root; 
            }
        }
        else 
        {
            w = parent->left;

            if (w != nullptr && w->color == RED)
            {
                w->color = BLACK;
                parent->color = RED;
                rotateRight(parent);
                w = parent->left;
            }

            if ((w == nullptr) || 
               ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)))
            {
                if (w != nullptr) w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (w->left == nullptr || w->left->color == BLACK)
                {
                    if (w->right != nullptr) w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = parent->left;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->left != nullptr) w->left->color = BLACK;
                rotateRight(parent);
                node = root;
            }
        }
    }

    if (node != nullptr)
    {
        node->color = BLACK;
    }
}



ResearcherNode *RedBlackTree::minimum(ResearcherNode *node) const
{
    // TODO: Return leftmost node in subtree.
    
    if (node==nullptr)
    {
        return nullptr;
    }
    while (node->left!=nullptr)
    {
        node=node->left;
    }
    return node;
}

void RedBlackTree::rotateLeft(ResearcherNode *x)
{
    // TODO: Standard left rotation.
    ResearcherNode* y =x->right;
    ResearcherNode* xParent=x->parent;
    if (x==nullptr||y==nullptr)
    {
        return;
    }
    if (xParent!=nullptr)
    {
        if (x==xParent->left)
        {
            xParent->left=y;
        }
        else if (x==xParent->right)
        {
            xParent->right=y;
        }
        
    }
    else{
        root=y;
    }
    y->parent=xParent;
    
    x->right=y->left;
    if (y->left!=nullptr)
    {
        x->right->parent=x;
    }

    y->left=x;
    x->parent=y;
}

void RedBlackTree::rotateRight(ResearcherNode *x)
{
    // TODO: Standard right rotation.
    ResearcherNode* y=x->left;
    ResearcherNode* GrandParent=x->parent;
    if (x==nullptr||y==nullptr){return;}
    
    if (GrandParent==nullptr)
    {
        root=y;
        y->parent=nullptr;
    }
    else{
        y->parent=GrandParent;
        if (x==GrandParent->right)
        {
            GrandParent->right=y;
        }
        else{
            GrandParent->left=y;
        }
        
    }
    x->left=y->right;
    if (x->left!=nullptr)
    {
        x->left->parent=x;
    }
    y->right=x;
    x->parent=y;
}

int RedBlackTree::getResearcherCount() const
{
    return getResearcherCount(root);
}

int RedBlackTree::getResearcherCount(ResearcherNode *node) const
{
    // TODO: return size of subtree.
    if (node==nullptr)
    {
        return 0;
    }
    int right=getResearcherCount(node->right);
    int left=getResearcherCount(node->left);

    return right+left+1;    
    
    
}

int RedBlackTree::getTotalLoad() const
{
    return getTotalLoad(root);
}

int RedBlackTree::getTotalLoad(ResearcherNode *node) const
{
    // TODO: sum of data.numAssigned in subtree.
    if (node==nullptr)
    {
        return 0;
    }
    return node->data.numAssigned+getTotalLoad(node->right)+getTotalLoad(node->left);
    
    
}

void RedBlackTree::traversePreOrderForStats() const
{
    traversePreOrderForStats(root);
}

void RedBlackTree::traversePreOrderForStats(ResearcherNode *node) const
{
    // TODO:
    // Pre-order traversal (node, left, right).
    // Students will decide what exactly to print in PRINT_STATS.
    if (node==nullptr)
    {
        return;
    }
    std::cout<<node->data.fullName<<" "<<node->data.numAssigned<<" "<<node->data.capacity<<" "<<std::endl;
    traversePreOrderForStats(node->left);
    traversePreOrderForStats(node->right);

}
