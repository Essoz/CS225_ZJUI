/* The structure of the Node is
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
};
*/

// An Iterative Approach 
Node* insertToAVL(Node* node, int data)
{
    //Your code here
    bool mode = false;
    Node* newnode = new Node(data);
    newnode->data = data;
    newnode->height = 0;
    newnode->left = newnode->right = NULL;
    
    if (node == 0) // if the tree was empty
    {
        return newnode;
    } else {
        Node* pt = node;
        stack <pair<Node*,int>*> path;
        while (pt != NULL){
        // traverse through the tree from the root three cases
            pair<Node*, int>* Pair = new pair <Node*, int>;
            Pair->first = pt;
            if(data == pt->data){
                // nothing needs to be done.
                // breakdown all previously allocated pairs and exit
            
            
                /* to be filled here
                
                
                */
                
                delete newnode;
                
                return node;
            }
            if(data < pt->data){
                Pair->second = 0;
                pt = pt->left;
                path.push(Pair);
            } else {
                Pair->second = 1;
                pt = pt->right;
                path.push(Pair);
            }
        }
        
        // now first do the actual insertion
        pair<Node*, int>* Pair = path.top();
        path.pop();
        int newbal;
        Node* bchild = path.top()->first;
        Node* bgrandchild = Pair->first;
        if(Pair->second = 0){
            Pair->first->left = newnode;
            Pair->first->height--; //I can directly modify the height since the first successor will not be adjusted.
        } else {
            Pair->first->right = newnode;
            Pair->first->height++;
        }
        while(path.empty() != 0){
            Pair = path.top();
            path.pop();
            newbal = Pair->first->height;
            if(Pair->second == 0){
                newbal--;
            } else {
                newbal++;
            }
            if (newbal == 0){
                // no adjustment is needed, exit the program.
                Pair->first->height = newbal;
                return node;
            }
            
            if (newbal <= 1 && newbal >= -1){
                Pair->first->height = newbal;
                bgrandchild = bchild;
                if(Pair->second){
                    bchild = Pair->first->right; 
                }else{
                    bchild = Pair->first->left;
                }
                
            } else {
                // the tree needs to be adjusted at current location
                
                // a right rotation is needed
                if (newbal < -1){
                    if (bchild->left == bgrandchild){
                        //a single right rotation will suffice
                        Pair->first->left = bchild->right;
                        Pair->first->height = 0;
                        bchild->right = Pair->first;
                        bchild->height = 0;
                        if (path.empty()){
                            return bchild;
                        } else {
                            if(path.top()->second){
                                path.top()->first->right = bchild;
                            } else {
                                path.top()->first->left = bchild;
                            }
                            return node;
                        }
                    } else {
                        // first we need a left rotation


                        //TODO: height needs to be done!!!
                        // left rotation
                        int c = 0, n = 0;
                        if (data < (*bgrandchild).data)
                            n = 1;
                        else if (data > (*bgrandchild).data)
                            c = -1;
                        bchild->right = bgrandchild->left;
                        bchild->height = c;
                        bgrandchild->left = bchild;
                        bgrandchild->height = 0;   //it will have height 0 after rotation

                        Node* temp = bgrandchild;
                        bgrandchild = bchild;
                        bchild = temp;
                        // right rotation
                        Pair->first->left = bchild->right;
                        Pair->first->height = n;
                        bchild->right = Pair->first;
                        bchild->height = 0;
                        if (path.empty()){
                            return bchild;
                        } else {
                            if(path.top()->second){
                                path.top()->first->right = bchild;
                            } else {
                                path.top()->first->left = bchild;
                            }
                            return node;
                        }
                    }
                } else {
                        // do left rotation
                        if (bchild->right == bgrandchild){
                            //a single left rotation will suffice
                            Pair->first->right = bchild->left;
                            Pair->first->height = 0;
                            bchild->left = Pair->first;
                            bchild->height = 0;
                            if (path.empty()){
                                return bchild;
                            } else {
                                if(path.top()->second){
                                    path.top()->first->right = bchild;
                                } else {
                                    path.top()->first->left = bchild;
                                }
                                return node;
                            }
                        } else {
                            // first rotate right, then rotate left
                            // left rotation
                            int c = 0, n = 0;
                            if (data < (*bgrandchild).data)
                                c = 1;
                            else if (data > (*bgrandchild).data)
                                n = -1;
                            bchild->left = bgrandchild->right;
                            bchild->height = c;
                            bgrandchild->right = bchild;
                            bgrandchild->height = 0;   //it will have height 0 after rotation

                            Node* temp = bgrandchild;
                            bgrandchild = bchild;
                            bchild = temp;
                            // left rotation
                            Pair->first->right = bchild->left;
                            Pair->first->height = n;
                            bchild->left = Pair->first;
                            bchild->height = 0;
                            if (path.empty()){
                                return bchild;
                            } else {
                                if(path.top()->second){
                                    path.top()->first->right = bchild;
                                } else {
                                    path.top()->first->left = bchild;
                                }
                                return node;
                            }
                        }
                    }
                } 
            }
        }
    }