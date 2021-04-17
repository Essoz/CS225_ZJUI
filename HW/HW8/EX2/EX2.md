(i)
$$
\begin{align}
FindMin(node)&\ //start\ from\ root\ node\\while&(node\ not\ leafnode)\\&node=node->smallistSuccessor\\//now\ is&\ the\ left\ most\ leaf\ node\\minmum&=first\ element\ in\ this\ node
\end{align}
$$

$$
\begin{align}
FindMax(node)&\ //start\ from\ root\ node\\while&(node\ not\ leafnode)\\&node=node->biggestSuccessor\\//now\ is&\ the\ left\ most\ leaf\ node\\minmum&=last\ element\ in\ this\ node
\end{align}
$$

(iii)

In B+ tree, since all the keys are stored in leaf node, in order to find the pre and suc, there are 3 situations need to be specified:

first find this key in one leaf node;

if this key is the first/last element, then its pre/suc is the pre/suc leaf node's last/first element.

else the pre/suc is in the same leaf node, so just retrieve it easily; 