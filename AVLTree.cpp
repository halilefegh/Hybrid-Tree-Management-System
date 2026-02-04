#include "AVLTree.h"

AVLTree::AVLTree()
    : root(nullptr)
{
}

AVLTree::~AVLTree()
{
    clear();
}

void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

void AVLTree::clear(ArtifactNode *node)
{
    //TODO
    if (node==nullptr)
    {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
    
}

int AVLTree::height(ArtifactNode *node) const
{
    if (node==nullptr)
    {
        return -1;
    }
    return node->height;
    
}

int AVLTree::getBalance(ArtifactNode *node) const
{
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

ArtifactNode *AVLTree::rotateLeft(ArtifactNode *x)
{
    // TODO: Standard AVL left rotation.
    //return new root
    ArtifactNode* y=x->right;
    x->right=y->left;
    y->left=x;

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

ArtifactNode *AVLTree::rotateRight(ArtifactNode *y)
{
    // TODO: Standard AVL right rotation (mirror of rotateLeft).
    ArtifactNode* x= y->left;
    y->left=x->right;
    x->right=y;
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    

    return x;
}

ArtifactNode *AVLTree::findMinNode(ArtifactNode *node) const
{
    // TODO: Return leftmost node in this subtree.
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
bool AVLTree::insertArtifact(const Artifact &artifact)
{
    bool inserted=false;
    root=insert(root,artifact,inserted);
    return inserted;
}
ArtifactNode *AVLTree::insert(ArtifactNode *node, const Artifact &artifact, bool &inserted)
{
    // TODO:
    // 1) Standard BST insert by artifactID.
    // 2) Iif duplicate ID, set nserted = false and return node unchanged.
    // 3) On actual insertion, update node->height.
    // 4) Compute balance and apply AVL rotations if needed.
    // 5) Return the (possibly new) root of this subtree.
    if (node==nullptr)
    {
        
        inserted=true;
        return new ArtifactNode(artifact);
    }
    if (node->data.artifactID>artifact.artifactID)
    {
        node->left = insert(node->left,artifact,inserted);
    }
    else if(node->data.artifactID<artifact.artifactID){
        node->right = insert(node->right,artifact,inserted);
    }
    else{
        inserted=false;
        return node;}
    
    node->height=1 + std::max(height(node->left),height(node->right));
    int balance=getBalance(node);

    if (balance > 1)
    {
        if (artifact.artifactID>node->left->data.artifactID)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else 
        {
            return rotateRight(node);
        }
        
    }
    if (balance<-1)
    {
        if (artifact.artifactID>node->right->data.artifactID)
        {
            return rotateLeft(node);
        }
        else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
    }
    

    

    return node;
    
    
    
}

ArtifactNode *AVLTree::remove(ArtifactNode *node, int artifactID, bool &removed)
{
    // TODO:
    // 1) Standard BST deletion by artifactID.
    // 2) If node not found, leave removed = false.
    // 3) Upon deletion, update heights and rebalance with rotations.
    // 4) Return (possibly new) root of this subtree.
    if (node==nullptr)

    {

        return nullptr;

    }

    if (node->data.artifactID<artifactID)

    {

        node->right=remove(node->right,artifactID,removed);

    }

    else if(node->data.artifactID>artifactID){

        node->left=remove(node->left,artifactID,removed);

    }

    else{

        removed=true;

        if (node->right==nullptr || node->left==nullptr)

        {

            if (node->right==nullptr && node->left==nullptr)

            {

                delete node;

                return nullptr;

            }

            else{

                if (node->right!=nullptr)

                {

                    ArtifactNode* temp=node->right;

                    delete node;

                    return temp;

                }

                else{

                    ArtifactNode* temp=node->left;

                    delete node;

                    return temp;

                }

               

            }

        }

        else{

            ArtifactNode* temp=findMinNode(node->right);

            node->data = temp->data;

            node->right = remove(node->right, temp->data.artifactID,removed);

           



        }

       

       







    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance=getBalance(node);

    if (balance > 1) {

        if (getBalance(node->left) >= 0) {

            return rotateRight(node);

        } else {

            node->left = rotateLeft(node->left);

            return rotateRight(node);

        }

    }



   

    if (balance < -1) {

        if (getBalance(node->right) <= 0) {

            return rotateLeft(node);

        } else {

            node->right = rotateRight(node->right);

            return rotateLeft(node);

        }

    }

   

   

    return node;
}



bool AVLTree::removeArtifact(int artifactID)
{
    bool removed = false;
    root = remove(root, artifactID, removed);
    return removed;
}

ArtifactNode *AVLTree::findArtifact(int artifactID) const
{
    return find(root, artifactID);
}

ArtifactNode *AVLTree::find(ArtifactNode *node, int artifactID) const
{
    //TODO
    if (node==nullptr)
    {
        return nullptr;
    }
    if (node->data.artifactID==artifactID)
    {
        return node;
    }
    if (node->data.artifactID<artifactID)
    {
        return find(node->right,artifactID);
    }
    return find(node->left,artifactID);
    
    
    

    return nullptr;
}
void AVLTree::printBiggers(ArtifactNode* node,int min){
    if (node==nullptr)
    {
        return;
    }
    printBiggers(node->left,min);
    printBiggers(node->right,min);
    if (node->data.rarityLevel>=min)
    {
        std::cout<<node->data.artifactID<<" "<<node->data.name<<" "<<node->data.rarityLevel<<" "<<node->data.researchValue<<"."<<std::endl;
        return;
    }
    
}
void AVLTree::startPrintBiggers(int min){
    printBiggers(root,min);
}
void AVLTree::setAssignedTo(int artifactID, const std::string &researcherName)
{
    //assign artifact to researcher
    ArtifactNode *node=findArtifact(artifactID);
    if (node==nullptr)
    {
        return;
    }
    
    node->data.assignedToName=researcherName;
    
}

void AVLTree::clearAssignedTo(int artifactID)
{
    //TODO
    
    ArtifactNode *node=findArtifact(artifactID);
    if (node==nullptr)
    {
        return;
    }
    
    node->data.assignedToName="";
    
    
    
    
}

void AVLTree::printUnassigned() const
{
    printUnassigned(root);
}

void AVLTree::printUnassigned(ArtifactNode *node) const
{
    // TODO:
    // Inorder traversal.
    // For each node with data.assignedToName == "", print in required format, e.g.:
    // <id> <name> <rarity> <value>
    if (node==nullptr)
    {
        return;
    }
    
    printUnassigned(node->left);
    if (node->data.assignedToName=="")
    {
        std::cout<<node->data.artifactID<<" "<<node->data.name<<" "<<node->data.rarityLevel<<" "<<node->data.researchValue<<std::endl;
    }
    printUnassigned(node->right);
    
    
}

int AVLTree::getArtifactCount() const
{
    return getArtifactCount(root);
}

int AVLTree::getArtifactCount(ArtifactNode *node) const
{
    // TODO: return size of subtree.
    if (node==nullptr)
    {
        return 0;
    }
    int rightCount=getArtifactCount(node->right);
    int leftCount=getArtifactCount(node->left);
    return 1+rightCount+leftCount;
}

int AVLTree::getTotalRarity() const
{
    return getTotalRarity(root);
}

int AVLTree::getTotalRarity(ArtifactNode *node) const
{
    // TODO: sum of rarityLevel over subtree.
    if (node==nullptr)
    {
        return 0;
    }
    int rightCount=getTotalRarity(node->right);
    int leftCount=getTotalRarity(node->left);

    return node->data.rarityLevel+rightCount+leftCount;
    
}

void AVLTree::traversePostOrderForStats() const
{
    traversePostOrderForStats(root);
}

void AVLTree::traversePostOrderForStats(ArtifactNode *node) const
{
    // TODO:
    // Post-order traversal (left, right, node).
    // Students will decide what exactly to print in PRINT_STATS.
    if (node == nullptr)
    {
        return;
    }

    traversePostOrderForStats(node->left);
    traversePostOrderForStats(node->right);
    std::string assignedname;
    if (node->data.assignedToName=="")
    {
        assignedname="UNASSIGNED";
    }
    else{
        assignedname=node->data.assignedToName;
    }
    
    std::cout<<node->data.artifactID<<" "<<node->data.name<<" "<<node->data.rarityLevel<<" "<<node->data.researchValue<<" "<<assignedname<<std::endl;
}
