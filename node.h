#ifndef node_h_INCLUDED
#define node_h_INCLUDED

enum node_type_e
{
    NODE_COMMAND,       //command type
    NODE_VAR,           //variable name
};

enum val_type_e
{
    VAL_SINT = 1,       // signed int
    VAL_UINT,           // unsigned int
    VAL_SLLONG,         // signed long long
    VAL_ULLONG,         // unsigned long long
    VAL_FLOAT,          // floating point
    VAL_LDOUBLE,        // long double
    VAL_CHR,            // char
    VAL_STR,            // str (char pointer)
};

union symval_u
{
    long sint;
    unsigned long uint;
    long long sllong;
    unsigned long long ullong;
    double sfloat;
    long double ldouble;
    char chr;
    char *str;
};

typedef struct node_s
{
    enum   node_type_e type;    //type of this node
    enum   val_type_e val_type; //type of this node's val field
    union  symval_u val;        //value of this node
    int    children;            //number of child nodes
    struct node_s *first_child; //first child node
    struct node_s *next_sibling, *prev_sibling;     //if this is a child node, keep
                                                    //pointers to prev/next siblings
} node;

node* new_node(enum node_type_e type);
void add_child_node(node* parent, node* child);
void free_node_tree(node* root);
void set_node_val_str(node* nd, char* val);
#endif //node_h_INCLUDED
