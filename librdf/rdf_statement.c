/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * rdf_statement.c - RDF Statement implementation
 *
 * $Id$
 *
 * Copyright (C) 2000-2001 David Beckett - http://purl.org/net/dajobe/
 * Institute for Learning and Research Technology - http://www.ilrt.org/
 * University of Bristol - http://www.bristol.ac.uk/
 * 
 * This package is Free Software or Open Source available under the
 * following licenses (these are alternatives):
 *   1. GNU Lesser General Public License (LGPL)
 *   2. GNU General Public License (GPL)
 *   3. Mozilla Public License (MPL)
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * full license terms.
 * 
 * 
 */


#include <rdf_config.h>

#include <stdio.h>

#include <librdf.h>
#include <rdf_node.h>
#include <rdf_statement.h>


/* class methods */

/**
 * librdf_init_statement - Initialise the librdf_statement module
 **/
void
librdf_init_statement(void) 
{
}


/**
 * librdf_finish_statement - Terminate the librdf_statement module
 **/
void
librdf_finish_statement(void) 
{
}


/**
 * librdf_new_statement - Constructor - create a new empty librdf_statement
 * 
 * Return value: a new &librdf_statement or NULL on failure
 **/
librdf_statement*
librdf_new_statement(void) 
{
  librdf_statement* new_statement=librdf_new_node();
  if(!new_statement)
    return NULL;

  librdf_node_set_type(new_statement, LIBRDF_NODE_TYPE_STATEMENT);

  return new_statement;
}


/**
 * librdf_new_statement_from_statement - Copy constructor - create a new librdf_statement from an existing librdf_statement
 * @statement: &librdf_statement to copy
 * 
 * Return value: a new &librdf_statement with copy or NULL on failure
 **/
librdf_statement*
librdf_new_statement_from_statement(librdf_statement* statement)
{
  librdf_statement* new_statement;

  if(!statement)
    return NULL;
  
  new_statement = librdf_new_statement();
  if(!new_statement)
    return NULL;

  if(LIBRDF_NODE_STATEMENT_SUBJECT(statement)) {
    LIBRDF_NODE_STATEMENT_SUBJECT(new_statement)=librdf_new_node_from_node(LIBRDF_NODE_STATEMENT_SUBJECT(statement));
    if(!LIBRDF_NODE_STATEMENT_SUBJECT(new_statement)) {
      librdf_free_statement(new_statement);
      return NULL;
    }
  }
  if(LIBRDF_NODE_STATEMENT_PREDICATE(statement)) {
    LIBRDF_NODE_STATEMENT_PREDICATE(new_statement)=librdf_new_node_from_node(LIBRDF_NODE_STATEMENT_PREDICATE(statement));
    if(!LIBRDF_NODE_STATEMENT_PREDICATE(new_statement)) {
      librdf_free_statement(new_statement);
      return NULL;
    }
  }
  if(LIBRDF_NODE_STATEMENT_OBJECT(statement)) {
    LIBRDF_NODE_STATEMENT_OBJECT(new_statement)=librdf_new_node_from_node(LIBRDF_NODE_STATEMENT_OBJECT(statement));
    if(!LIBRDF_NODE_STATEMENT_OBJECT(new_statement)) {
      librdf_free_statement(new_statement);
      return NULL;
    }
  }

  return new_statement;
}


/**
 * librdf_new_statement_from_nodes - Constructor - create a new librdf_statement from existing librdf_node objects
 * @subject: &librdf_node
 * @predicate: &librdf_node
 * @object: &librdf_node
 * 
 * The node objects become owned by the new statement (or freed on error).
 *
 * Return value: a new &librdf_statement with copy or NULL on failure
 **/
librdf_statement*
librdf_new_statement_from_nodes(librdf_node* subject,
                                librdf_node* predicate,
                                librdf_node* object)
{
  librdf_statement* new_statement;

  new_statement = librdf_new_statement();
  if(!new_statement) {
    if(subject)
      librdf_free_node(subject);
    if(predicate)
      librdf_free_node(predicate);
    if(object)
      librdf_free_node(object);
    return NULL;
  }
  
  LIBRDF_NODE_STATEMENT_SUBJECT(new_statement)=subject;
  LIBRDF_NODE_STATEMENT_PREDICATE(new_statement)=predicate;
  LIBRDF_NODE_STATEMENT_OBJECT(new_statement)=object;

  return new_statement;
}


/**
 * librdf_free_statement - Destructor - destroy a librdf_statement
 * @statement: &librdf_statement object
 * 
 **/
void
librdf_free_statement(librdf_statement* statement)
{
  if(LIBRDF_NODE_STATEMENT_SUBJECT(statement))
    librdf_free_node(LIBRDF_NODE_STATEMENT_SUBJECT(statement));
  if(LIBRDF_NODE_STATEMENT_PREDICATE(statement))
    librdf_free_node(LIBRDF_NODE_STATEMENT_PREDICATE(statement));
  if(LIBRDF_NODE_STATEMENT_OBJECT(statement))
    librdf_free_node(LIBRDF_NODE_STATEMENT_OBJECT(statement));
  LIBRDF_FREE(librdf_statement, statement);
}



/* methods */

/**
 * librdf_statement_get_subject - Get the statement subject
 * @statement: &librdf_statement object
 * 
 * Return value: a pointer to the &librdf_node of the statement subject - 
 * NOTE this is a shared copy and must be copied if used by the caller.
 **/
librdf_node*
librdf_statement_get_subject(librdf_statement *statement) 
{
  return LIBRDF_NODE_STATEMENT_SUBJECT(statement);
}


/**
 * librdf_statement_set_subject - Set the statement subject
 * @statement: &librdf_statement object
 * @node: &librdf_node of subject
 * 
 * The subject passed in becomes owned by
 * the statement object and must not be used by the caller after this call.
 **/
void
librdf_statement_set_subject(librdf_statement *statement, librdf_node *node)
{
  LIBRDF_NODE_STATEMENT_SUBJECT(statement)=node;
}


/**
 * librdf_statement_get_predicate - Get the statement predicate
 * @statement: &librdf_statement object
 * 
 * Return value: a pointer to the &librdf_node of the statement predicate - 
 * NOTE this is a shared copy and must be copied if used by the caller.
 **/
librdf_node*
librdf_statement_get_predicate(librdf_statement *statement) 
{
  return LIBRDF_NODE_STATEMENT_PREDICATE(statement);
}


/**
 * librdf_statement_set_predicate - Set the statement predicate
 * @statement: &librdf_statement object
 * @node: &librdf_node of predicate
 * 
 * The predicate passed in becomes owned by
 * the statement object and must not be used by the caller after this call.
 **/
void
librdf_statement_set_predicate(librdf_statement *statement, librdf_node *node)
{
  LIBRDF_NODE_STATEMENT_PREDICATE(statement)=node;
}


/**
 * librdf_statement_get_object - Get the statement object
 * @statement: &librdf_statement object
 * 
 * Return value: a pointer to the &librdf_node of the statement object - 
 * NOTE this is a shared copy and must be copied if used by the caller.
 **/
librdf_node*
librdf_statement_get_object(librdf_statement *statement) 
{
  return LIBRDF_NODE_STATEMENT_OBJECT(statement);
}


/**
 * librdf_statement_set_object - Set the statement object
 * @statement: &librdf_statement object
 * @node: &librdf_node of object
 * 
 * The object passed in becomes owned by
 * the statement object and must not be used by the caller after this call.
 **/
void
librdf_statement_set_object(librdf_statement *statement, librdf_node *node)
{
  LIBRDF_NODE_STATEMENT_OBJECT(statement)=node;
}


/**
 * librdf_statement_to_string - Format the librdf_statement as a string
 * @statement: the statement
 * 
 * Formats the statement as a newly allocate string that must be freed by
 * the caller.
 * 
 * Return value: the string or NULL on failure.
 **/
char *
librdf_statement_to_string(librdf_statement *statement)
{
  char *subject_string, *predicate_string, *object_string;
  char *s;
  int statement_string_len;
  char *format;
  static char *null_string="(null)";

  if(LIBRDF_NODE_STATEMENT_SUBJECT(statement)) {
    subject_string=librdf_node_to_string(LIBRDF_NODE_STATEMENT_SUBJECT(statement));
    if(!subject_string)
      return NULL;
  } else {
    subject_string=null_string;
  }

  
  if(LIBRDF_NODE_STATEMENT_PREDICATE(statement)) {
    predicate_string=librdf_node_to_string(LIBRDF_NODE_STATEMENT_PREDICATE(statement));
    if(!predicate_string) {
      if(subject_string != null_string)
        LIBRDF_FREE(cstring, subject_string);
      return NULL;
    }
  } else {
    predicate_string=null_string;
  }
  

  if(LIBRDF_NODE_STATEMENT_OBJECT(statement)) {
    object_string=librdf_node_to_string(LIBRDF_NODE_STATEMENT_OBJECT(statement));
    if(!object_string) {
      if(subject_string != null_string)
        LIBRDF_FREE(cstring, subject_string);
      if(predicate_string != null_string)
        LIBRDF_FREE(cstring, predicate_string);
      return NULL;
    }
  } else {
    object_string=null_string;
  }
  


#define LIBRDF_STATEMENT_FORMAT_STRING_LITERAL "{%s, %s, \"%s\"}"
#define LIBRDF_STATEMENT_FORMAT_RESOURCE_LITERAL "{%s, %s, %s}"
  statement_string_len=1 + strlen(subject_string) +   /* "{%s" */
                       2 + strlen(predicate_string) + /* ", %s" */
                       2 + strlen(object_string) +    /* ", %s" */
                       1 + 1;                         /* "}\0" */
  if(LIBRDF_NODE_STATEMENT_OBJECT(statement) &&
     librdf_node_get_type(LIBRDF_NODE_STATEMENT_OBJECT(statement)) == LIBRDF_NODE_TYPE_LITERAL) {
    format=LIBRDF_STATEMENT_FORMAT_STRING_LITERAL;
    statement_string_len+=2; /* Extra "" around literal */
  } else {
    format=LIBRDF_STATEMENT_FORMAT_RESOURCE_LITERAL;
  }
    
  s=(char*)LIBRDF_MALLOC(cstring, statement_string_len);
  if(s)
    sprintf(s, format, subject_string, predicate_string, object_string);

  /* always free allocated intermediate strings */
  if(subject_string != null_string)
    LIBRDF_FREE(cstring, subject_string);
  if(predicate_string != null_string)
    LIBRDF_FREE(cstring, predicate_string);
  if(object_string != null_string)
    LIBRDF_FREE(cstring, object_string);

  return s;
}

/**
 * librdf_hash_print - pretty print the statement to a file descriptor
 * @statement: the statement
 * @fh: file handle
 **/
void
librdf_statement_print(librdf_statement *statement, FILE *fh) 
{
  char *s;

  if(!statement)
    return;
  
  s=librdf_statement_to_string(statement);
  if(!s)
    return;
  fputs(s, fh);
  LIBRDF_FREE(cstring, s);
}



/**
 * librdf_statement_equals - Check if two statements are equal
 * @statement1: first &librdf_statement
 * @statement2: second &librdf_statement
 * 
 * Return value: 0 if statements are different.
 **/
int
librdf_statement_equals(librdf_statement* statement1, 
                        librdf_statement* statement2)
{
  /* FIXME: use digests? */

  if(!librdf_node_equals(LIBRDF_NODE_STATEMENT_SUBJECT(statement1), 
                         LIBRDF_NODE_STATEMENT_SUBJECT(statement2)))
      return 0;

  if(!librdf_node_equals(LIBRDF_NODE_STATEMENT_PREDICATE(statement1),
                         LIBRDF_NODE_STATEMENT_PREDICATE(statement2)))
      return 0;

  if(!librdf_node_equals(LIBRDF_NODE_STATEMENT_OBJECT(statement1),
                         LIBRDF_NODE_STATEMENT_OBJECT(statement2)))
      return 0;

  return 1;
}


/**
 * librdf_statement_match - Match a statement against a 'partial' statement
 * @statement: statement
 * @partial_statement: statement with possible empty parts
 * 
 * A partial statement is where some parts of the statement -
 * subject, predicate or object can be empty (NULL).
 * Empty parts match against any value, parts with values
 * must match exactly.  Node matching is done via librdf_node_equals()
 * 
 * Return value: non 0 on match
 **/
int
librdf_statement_match(librdf_statement* statement, 
                       librdf_statement* partial_statement)
{
  if(LIBRDF_NODE_STATEMENT_SUBJECT(partial_statement) &&
     !librdf_node_equals(LIBRDF_NODE_STATEMENT_SUBJECT(statement), 
                         LIBRDF_NODE_STATEMENT_SUBJECT(partial_statement)))
      return 0;

  if(LIBRDF_NODE_STATEMENT_PREDICATE(partial_statement) &&
     !librdf_node_equals(LIBRDF_NODE_STATEMENT_PREDICATE(statement),
                         LIBRDF_NODE_STATEMENT_PREDICATE(partial_statement)))
      return 0;

  if(LIBRDF_NODE_STATEMENT_OBJECT(partial_statement) &&
     !librdf_node_equals(LIBRDF_NODE_STATEMENT_OBJECT(statement),
                         LIBRDF_NODE_STATEMENT_OBJECT(partial_statement)))
      return 0;

  return 1;
}


/**
 * librdf_statement_encode - Serialise a statement into a buffer
 * @statement: the statement to serialise
 * @buffer: the buffer to use
 * @length: buffer size
 * 
 * Encodes the given statement in the buffer, which must be of sufficient
 * size.  If buffer is NULL, no work is done but the size of buffer
 * required is returned.
 * 
 * Return value: the number of bytes written or 0 on failure.
 **/
size_t
librdf_statement_encode(librdf_statement* statement, 
                        unsigned char *buffer, 
                        size_t length)
{

  return librdf_statement_encode_parts(statement, buffer, length,
                                       LIBRDF_STATEMENT_ALL);
}


/**
 * librdf_statement_encode_parts - Serialise parts of a statement into a buffer
 * @statement: statement to serialise
 * @buffer: the buffer to use
 * @length: buffer size
 * @fields: fields to encode
 * 
 * Encodes the given statement in the buffer, which must be of sufficient
 * size.  If buffer is NULL, no work is done but the size of buffer
 * required is returned.
 *
 * The fields values are or-ed combinations of:
 * LIBRDF_STATEMENT_SUBJECT LIBRDF_STATEMENT_PREDICATE
 * LIBRDF_STATEMENT_OBJECT LIBRDF_STATEMENT_ID LIBRDF_STATEMENT_FLAGS
 * or LIBRDF_STATEMENT_ALL for all fields
 * 
 * Return value: the number of bytes written or 0 on failure.
 **/
size_t
librdf_statement_encode_parts(librdf_statement* statement, 
                              unsigned char *buffer, size_t length,
                              int fields)
{
  size_t total_length=0;
  size_t node_len;
  unsigned char *p;

  /* min size */
  if(buffer && length < 1)
    return 0;

  p=buffer;
  /* magic number 'x' */
  if(p) {
    *p++='x';
    length--;
  }
  total_length++;

  if((fields & LIBRDF_STATEMENT_SUBJECT) && LIBRDF_NODE_STATEMENT_SUBJECT(statement)) {
    /* 's' + subject */
    if(p) {
      *p++='s';
      length--;
    }
    total_length++;

    node_len=librdf_node_encode(LIBRDF_NODE_STATEMENT_SUBJECT(statement), p, length);
    if(!node_len)
      return 0;
    if(p) {
      p += node_len;
      length -= node_len;
    }
    
    
    total_length += node_len;
  }
  
  
  if((fields & LIBRDF_STATEMENT_PREDICATE) && LIBRDF_NODE_STATEMENT_PREDICATE(statement)) {
    /* 'p' + predicate */
    if(p) {
      *p++='p';
      length--;
    }
    total_length++;

    node_len=librdf_node_encode(LIBRDF_NODE_STATEMENT_PREDICATE(statement), p, length);
    if(!node_len)
      return 0;
    if(p) {
      p += node_len;
      length -= node_len;
    }
    
    total_length += node_len;
  }
  
  if((fields & LIBRDF_STATEMENT_OBJECT) && LIBRDF_NODE_STATEMENT_OBJECT(statement)) {
    /* 'o' object */
    if(p) {
      *p++='o';
      length--;
    }
    total_length++;

    node_len= librdf_node_encode(LIBRDF_NODE_STATEMENT_OBJECT(statement), p, length);
    if(!node_len)
      return 0;
    if(p) {
      p += node_len;
      length -= node_len;
    }

    total_length += node_len;
  }

  return total_length;
}


/**
 * librdf_statement_decode - Decodes a statement from a buffer
 * @statement: the statement to deserialise into
 * @buffer: the buffer to use
 * @length: buffer size
 * 
 * Decodes the serialised statement (as created by librdf_statement_encode() )
 * from the given buffer.
 * 
 * Return value: number of bytes used or 0 on failure (bad encoding, allocation failure)
 **/
size_t
librdf_statement_decode(librdf_statement* statement, 
                        unsigned char *buffer, size_t length)
{
  unsigned char *p;
  librdf_node* node;
  unsigned char type;
  size_t total_length=0;
  
#if defined(LIBRDF_DEBUG) && LIBRDF_DEBUG > 1
    LIBRDF_DEBUG2(librdf_statement_decode, "Decoding buffer of %d bytes\n", 
                  length);
#endif


  /* absolute minimum - first byte is type */
  if(length < 1)
    return 0;

  p=buffer;
  if(*p++ != 'x')
    return 0;
  length--;
  total_length++;
  
  
  while(length>0) {
    size_t node_len;
    
    type=*p++;
    length--;
    total_length++;

    if(!length)
      return 0;
    
    node=librdf_new_node();
    if(!node)
      return 0;
    
    if(!(node_len=librdf_node_decode(node, p, length)))
      return 0;

    p += node_len;
    length -= node_len;
    total_length += node_len;
    
#if defined(LIBRDF_DEBUG) && LIBRDF_DEBUG > 1
    LIBRDF_DEBUG3(librdf_statement_decode, "Found type %c (%d bytes)\n",
                  type, node_len);
#endif
  
    switch(type) {
    case 's': /* subject */
      LIBRDF_NODE_STATEMENT_SUBJECT(statement)=node;
      break;
      
    case 'p': /* predicate */
      LIBRDF_NODE_STATEMENT_PREDICATE(statement)=node;
      break;
      
    case 'o': /* object */
      LIBRDF_NODE_STATEMENT_OBJECT(statement)=node;
      break;

    default:
      LIBRDF_FATAL2(librdf_statement_decode,
                    "Illegal statement encoding %d seen\n",
                    p[-1]);
    }
  }

  return total_length;
}



#ifdef STANDALONE

/* one more prototype */
int main(int argc, char *argv[]);


int
main(int argc, char *argv[]) 
{
  librdf_statement *statement, *statement2;
  int size, size2;
  char *program=argv[0];
  char *s, *buffer;
  
  /* initialise dependent modules */
  librdf_init_digest();
  librdf_init_hash();
  librdf_init_uri(librdf_get_digest_factory(NULL), NULL);
  librdf_init_statement();

  fprintf(stderr, "%s: Creating statement\n", program);
  statement=librdf_new_statement();

  s=librdf_statement_to_string(statement);
  fprintf(stderr, "%s: Empty statement: %s\n", program, s);
  LIBRDF_FREE(cstring, s);

  librdf_statement_set_subject(statement, librdf_new_node_from_uri_string("http://www.ilrt.bris.ac.uk/people/cmdjb/"));
  librdf_statement_set_predicate(statement, librdf_new_node_from_uri_string("http://purl.org/dc/elements/1.1/#Creator"));
  librdf_statement_set_object(statement, librdf_new_node_from_literal("Dave Beckett", NULL, 0, 0));

  s=librdf_statement_to_string(statement);
  fprintf(stderr, "%s: Resulting statement: %s\n", program, s);
  LIBRDF_FREE(cstring, s);

  size=librdf_statement_encode(statement, NULL, 0);
  fprintf(stdout, "%s: Encoding statement requires %d bytes\n", program, size);
  buffer=(char*)LIBRDF_MALLOC(cstring, size);

  fprintf(stdout, "%s: Encoding statement in buffer\n", program);
  size2=librdf_statement_encode(statement, buffer, size);
  if(size2 != size) {
    fprintf(stderr, "%s: Encoding statement used %d bytes, expected it to use %d\n", program, size2, size);
    return(1);
  }
  
    
  fprintf(stdout, "%s: Creating new statement\n", program);
  statement2=librdf_new_statement();

  fprintf(stdout, "%s: Decoding statement from buffer\n", program);
  if(!librdf_statement_decode(statement2, buffer, size)) {
    fprintf(stderr, "%s: Decoding statement failed\n", program);
    return(1);
  }
  LIBRDF_FREE(cstring, buffer);
   
  fprintf(stdout, "%s: New statement is: ", program);
  librdf_statement_print(statement2, stdout);
  fputs("\n", stdout);
 
  
  fprintf(stdout, "%s: Freeing statements\n", program);
  librdf_free_statement(statement2);
  librdf_free_statement(statement);


  librdf_finish_statement();
  librdf_finish_uri();
  librdf_finish_hash();
  librdf_finish_digest();
  
#ifdef LIBRDF_MEMORY_DEBUG 
  librdf_memory_report(stderr);
#endif
	
  /* keep gcc -Wall happy */
  return(0);
}

#endif
