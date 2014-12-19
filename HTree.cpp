#include "HTree.h"

tree::tree()
{
    m_root = 0;
}
void tree::append(Node *node)
{
    m_root = node;
}
QByteArray tree::treeRepresentation(Node *node, QVector<QByteArray> &cod)
{
   if(!node->left && !node->right)
      {
        QByteArray ret;
        if(node->content == 0x21)
        {
            ret.append(0x2A);
            ret.append(0x21);
        }
        else if(node->content == 0x2A)
        {
            ret.append(0x2A);
            ret.append(0x2A);
        }
        else
            ret.append(node->content);
        cod[node->content] = node->code;
        return ret;
      }
   else
   {
       QByteArray codd(node->code);
       node->left->code = codd.append("0");
       codd.remove(codd.size() - 1, 1);
       node->right->code = codd.append("1");
   }
   return QByteArray().append(0x21).append(treeRepresentation(node->left, cod)).append(treeRepresentation(node->right, cod));
}

QByteArray tree::treeRepresentation(QVector<QByteArray> &cod)
{
    return treeRepresentation(m_root, cod);
}

void tree::buildDecTree(Node *node, QByteArray x)
{
    if(x[0] == 0x21)
    {
        node->left = new Node;
        node->right = new Node;
        int y = 1, pos = 2;
        while(y < pos)
        {
            if(x[y] == 0x21)
                pos = pos + 2;
            else if(x[y] == 0x2A)
            {
                ++pos;
                ++y;
            }
            ++y;
        }
        x.remove(0,1);
        buildDecTree(node->left, x);
        x.remove(0, pos - 1);
        buildDecTree(node->right, x);
    }
    else if(x[0] == 0x2A)
        node->content = x[1];
    else
        node->content = x[0];
}
Node *tree::getTree()
{
    return m_root;
}
