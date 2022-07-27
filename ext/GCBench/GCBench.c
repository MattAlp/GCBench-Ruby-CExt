#include "ruby.h"

//
// Created by Matthew Alp on 2022-07-27.
//

# define STRETCH_TREE_DEPTH 18

static VALUE cNode;

int tree_size(int depth){
    return (1 << (depth + 1)) - 1;
}

int num_iters(int depth){
    return 2 * tree_size(STRETCH_TREE_DEPTH) / tree_size(depth);
}

//VALUE tree_size(VALUE self, VALUE depth) // is this right?
//{
//    int i = NUM2INT(depth);
//    int size = (1 << (i + 1)) - 1;
//    return INT2NUM(size);
//}
//
//VALUE num_iters(VALUE self, VALUE depth)
//{
//    return INT2NUM(2 * NUM2INT(tree_size(self, STRETCH_TREE_DEPTH)) / NUM2INT(tree_size(self, depth)));
//}

VALUE node_initialize(VALUE self, VALUE left, VALUE right){
    ID iv_left = rb_intern("@left");
    ID iv_right = rb_intern("@right");
    rb_ivar_set(self, iv_left, left);
    rb_ivar_set(self, iv_right, right);
    return self;
}

VALUE make_tree(VALUE self, VALUE depth)
{
    if(NUM2INT(depth) <= 0) {
        VALUE args[2] = {Qnil, Qnil};
        return rb_class_new_instance(2, args, cNode);
    }
    else {
        VALUE left = make_tree(self, INT2NUM(NUM2INT(depth) - 1));
        VALUE right = make_tree(self, INT2NUM(NUM2INT(depth) - 1));
        VALUE args[2] = {left, right};
        return rb_class_new_instance(2, args, cNode);
    }
}

VALUE populate(VALUE self, VALUE depth, VALUE node)
{
    int i_depth = NUM2INT(depth);
    if (i_depth <= 0){
        return Qnil;
    }else{
        depth = INT2NUM(i_depth - 1);
        ID iv_left = rb_intern("@left");
        ID iv_right = rb_intern("@right");
        VALUE args[2] = {Qnil, Qnil};
        rb_ivar_set(node, iv_left, rb_class_new_instance(2, args, cNode));
        rb_ivar_set(node, iv_right, rb_class_new_instance(2, args, cNode));
        return Qnil;
    }
}

VALUE time_construction(VALUE self, VALUE depth)
{
    /* ... */
    VALUE tmp_tree;
    int i_depth = NUM2INT(depth);
    int inum_iters = num_iters(i_depth);

    for (int i = 0; i < inum_iters; i++){
        VALUE args[2] = {Qnil, Qnil};
        tmp_tree = rb_class_new_instance(2, args, cNode);
        populate(self, depth, tmp_tree);
        tmp_tree = Qnil;
    }

    for (int i = 0; i < inum_iters; i++){
        tmp_tree = make_tree(self, depth);
        tmp_tree = Qnil;
    }

    return Qnil;
}

void Init_GCBench(void)
{
    cNode = rb_define_class("Node", rb_cObject);
    rb_define_attr(cNode, "i", 1, 1);
    rb_define_attr(cNode, "j", 1, 1);
    rb_define_attr(cNode, "left", 1, 1);
    rb_define_attr(cNode, "right", 1, 1);
    rb_define_method(cNode, "initialize", node_initialize, 2);


    VALUE mGCBench = rb_define_module("GCBench");
    rb_define_module_function(mGCBench, "make_tree", make_tree, 1);
    rb_define_module_function(mGCBench, "populate", populate, 2);
    rb_define_module_function(mGCBench, "time_construction", time_construction, 1);
//    rb_define_module_function(mGCBench, "num_iters", num_iters, 1);
//    rb_define_module_function(mGCBench, "tree_size", tree_size, 1);
}