#include "ruby.h"

//
// Created by Matthew Alp on 2022-07-27.
//

VALUE make_tree(VALUE self, VALUE i_depth)
{
    /* ... */
    return Qnil;
}

VALUE populate(VALUE self, VALUE depth, VALUE this_node)
{
    /* ... */
    return Qnil;
}


VALUE time_construction(VALUE self, VALUE depth)
{
    /* ... */
    return Qnil;
}


VALUE num_iters(VALUE self, VALUE depth)
{
    /* ... */
    return Qnil;
}


void Init_GCBench()
{
/*
 * expose time_construction
 * num_iters, tree_size => maybe
 *
 */
//    VALUE Node;
//    VALUE klass = rb_define_class("GCBench", rb_cObject);
//    rb_define_method(klass, "time_construction", time_construction, 1);

    VALUE mGCBench = rb_define_module("GCBench");

    rb_define_module_function(mGCBench, "make_tree", make_tree, 1);
    rb_define_module_function(mGCBench, "populate", populate, 2);
    rb_define_module_function(mGCBench, "time_construction", time_construction, 1);
    rb_define_module_function(mGCBench, "num_iters", num_iters, 1);


}