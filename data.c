#include "data.h"

void data_load(){
  struct node_struct * node, * n1, * n2;
  struct attribute_struct * attribute;
  struct base_struct * base;
  struct relation_struct * r;

  base=base_new();//create a base
    
  attribute=attribute_new("name", "personen");//create an attribute(for the base)
  
  base->attributes=dll_add(base->attributes, attribute);//add the attribute to the (list of attributes of the) base
  bases=dll_add(bases, base);//add the base to the list of bases 

  node=node_new(); //create a node
  attribute=attribute_new("voornaam", "martijn");//create an attribute (for the node)
  node->attributes=dll_add(node->attributes, attribute);//add the attribute to the (list of attributes of the) node
  attribute=attribute_new("achternaam", "bos");
  node->attributes=dll_add(node->attributes, attribute);
  
  base->nodes=dll_add(base->nodes, node);//finally add newly created node to the (list of nodes of the) base
  
  node=node_new(); //create a node
  attribute=attribute_new("voornaam", "marlies");//create an attribute (for the node)
  node->attributes=dll_add(node->attributes, attribute);//add the attribute to the (list of attributes of the) node
  attribute=attribute_new("achternaam", "kamp");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geslacht", "vrouwlijk");//create an attribute (for the node)
  node->attributes=dll_add(node->attributes, attribute);//add the attribute to the (list of attributes of the) node
  attribute=attribute_new("geboorte datum", "1974/06/18");//create an attribute (for the node)
  node->attributes=dll_add(node->attributes, attribute);//add the attribute to the (list of attributes of the) node

  base->nodes=dll_add(base->nodes, node);//finally add newly created node to the (list of nodes of the) base

  base=base_new();//create another base
  attribute=attribute_new("naam", "recepten");//add dome attributes to it
  base->attributes=dll_add(base->attributes, attribute);
  attribute=attribute_new("gecreeerd", "2024/10/22");
  base->attributes=dll_add(base->attributes, attribute);

  bases=dll_add(bases, base);//add the base to the list of bases

  base=base_search_by_swid(0);
  n1=node_search_by_swid(base,2);
  n2=node_search_by_swid(base,5);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","partner");
  r->attributes=dll_add(r->attributes, attribute);

  r=relation_new(n1);
  n2->relations=dll_add(n2->relations,r);
  attribute=attribute_new("type","partner");
  r->attributes=dll_add(r->attributes, attribute);

  base=base_search_by_swid(0);

  node=node_new();
  attribute=attribute_new("voornaam", "ruben");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("achternaam", "bos");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geboorte datum", "2005/11/30");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geslacht", "mannelijk");
  node->attributes=dll_add(node->attributes, attribute);
  base->nodes=dll_add(base->nodes, node);

  node=node_new();
  attribute=attribute_new("voornaam", "sara");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("achternaam", "bos");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geboorte datum", "2008/06/13");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geslacht", "vrouwlijk");
  node->attributes=dll_add(node->attributes, attribute);
  base->nodes=dll_add(base->nodes, node);

  node=node_new();
  attribute=attribute_new("voornaam", "eva");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("achternaam", "bos");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geboorte datum", "2013/04/13");
  node->attributes=dll_add(node->attributes, attribute);
  attribute=attribute_new("geslacht", "vrouwlijk");
  node->attributes=dll_add(node->attributes, attribute);
  base->nodes=dll_add(base->nodes, node);

  base=base_search_by_swid(0);
  n1=node_search_by_swid(base,2);
  n2=node_search_by_swid(base,17);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","vader");
  r->attributes=dll_add(r->attributes, attribute);
  
  n2=node_search_by_swid(base,22);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","vader");
  r->attributes=dll_add(r->attributes, attribute);
  
  n2=node_search_by_swid(base,27);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","vader");
  r->attributes=dll_add(r->attributes, attribute);



  base=base_search_by_swid(0);
  n1=node_search_by_swid(base,5);
  n2=node_search_by_swid(base,17);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","moeder");
  r->attributes=dll_add(r->attributes, attribute);
  
  n2=node_search_by_swid(base,22);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","moeder");
  r->attributes=dll_add(r->attributes, attribute);
  
  n2=node_search_by_swid(base,27);
  r=relation_new(n2);
  n1->relations=dll_add(n1->relations,r);
  attribute=attribute_new("type","moeder");
  r->attributes=dll_add(r->attributes, attribute);
  
}
