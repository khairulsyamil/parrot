/* objects.h
 *  Copyright (C) 2001-2003, The Perl Foundation.
 *  SVN Info
 *     $Id$
 *  Overview:
 *     Parrot class and object header stuff
 *  Data Structure and Algorithms:
 *  History:
 *  Notes:
 *  References:
 */

#ifndef PARROT_OBJECTS_H_GUARD
#define PARROT_OBJECTS_H_GUARD

#include "parrot/parrot.h"

#define PARROT_NAMESPACE_SEPARATOR "\0"
#define PARROT_NAMESPACE_SEPARATOR_LENGTH 1

typedef enum {
    PCD_PARENTS,        /* An array of immediate parents */
    PCD_CLASS_NAME,     /* A String PMC */
    PCD_ATTRIBUTES,      /* class::attrib => offset hash */
    PCD_CLASS_ATTRIBUTES, /* Class attribute array */
    PCD_OBJECT_VTABLE,   /* Vtable PMC that holds the vtable for
                            objects of this class */
    PCD_MAX
} PARROT_CLASS_DATA_ENUM;

/* HEADERIZER BEGIN: src/objects.c */

PARROT_API
INTVAL Parrot_add_attribute( PARROT_INTERP, PMC* _class, STRING* attr )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_add_parent( PARROT_INTERP, PMC *_class, PMC *parent )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_class_lookup( PARROT_INTERP, STRING *class_name )
        __attribute__nonnull__(1);

PARROT_API
INTVAL Parrot_class_offset( PARROT_INTERP, PMC *object, STRING *_class )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_ComposeRole( PARROT_INTERP,
    PMC *role,
    PMC *exclude,
    int got_exclude,
    PMC *alias,
    int got_alias,
    PMC *methods_hash,
    PMC *roles_list )
        __attribute__nonnull__(1);

PARROT_API
PMC* Parrot_ComputeMRO_C3( PARROT_INTERP, PMC *_class )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_find_class_constructor( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_find_class_destructor( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_find_class_fallback( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_find_method_direct( PARROT_INTERP,
    PMC *_class,
    STRING *method_name )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_find_method_with_cache( PARROT_INTERP,
    PMC *_class,
    NOTNULL(STRING *method_name) )
        __attribute__nonnull__(1)
        __attribute__nonnull__(3);

PARROT_API
PMC* Parrot_find_vtable_meth( PARROT_INTERP, NOTNULL(PMC *pmc), STRING *meth )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

PARROT_API
PMC * Parrot_get_attrib_by_num( PARROT_INTERP, PMC *object, INTVAL attrib )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_get_attrib_by_str( PARROT_INTERP, PMC *object, STRING *attr )
        __attribute__nonnull__(1);

PARROT_API
INTVAL Parrot_get_vtable_index( PARROT_INTERP, NOTNULL(const STRING *name) )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

PARROT_API
void Parrot_instantiate_object( PARROT_INTERP, PMC *object )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_instantiate_object_init( PARROT_INTERP, PMC *object, PMC *init )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_invalidate_method_cache( PARROT_INTERP,
    STRING *_class,
    STRING *meth )
        __attribute__nonnull__(1);

PARROT_API
INTVAL Parrot_MMD_method_idx( SHIM_INTERP, const char *name )
        __attribute__warn_unused_result__
        __attribute__pure__;

PARROT_API
const char* Parrot_MMD_method_name( SHIM_INTERP, INTVAL idx )
        __attribute__warn_unused_result__
        __attribute__pure__;

PARROT_API
PMC * Parrot_multi_subclass( PARROT_INTERP,
    PMC *base_class_array,
    STRING *child_class_name )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_new_class( PARROT_INTERP, PMC *_class, PMC *name )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_new_method_cache( PARROT_INTERP )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_note_method_offset( PARROT_INTERP, UINTVAL offset, PMC *method )
        __attribute__nonnull__(1);

PARROT_API
INTVAL Parrot_object_isa( PARROT_INTERP, PMC *pmc, PMC *_class )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_remove_parent( PARROT_INTERP,
    PMC *removed_class,
    PMC *existing_class )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_set_attrib_by_num( PARROT_INTERP,
    PMC *object,
    INTVAL attrib,
    PMC *value )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_set_attrib_by_str( PARROT_INTERP,
    PMC *object,
    STRING *attr,
    PMC *value )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_set_class_constructor( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken,
    STRING *method )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_set_class_destructor( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken,
    STRING *method )
        __attribute__nonnull__(1);

PARROT_API
void Parrot_set_class_fallback( PARROT_INTERP,
    STRING *_class,
    INTVAL classtoken,
    STRING *method )
        __attribute__nonnull__(1);

PARROT_API
PMC * Parrot_single_subclass( PARROT_INTERP,
    PMC *base_class,
    NULLOK(PMC *name) )
        __attribute__nonnull__(1);

PARROT_API
STRING* readable_name( PARROT_INTERP, NOTNULL(PMC *name) )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

void destroy_object_cache( PARROT_INTERP )
        __attribute__nonnull__(1);

void init_object_cache( PARROT_INTERP )
        __attribute__nonnull__(1);

void mark_object_cache( PARROT_INTERP )
        __attribute__nonnull__(1);

PMC * Parrot_class_lookup_p( PARROT_INTERP, PMC *class_name )
        __attribute__nonnull__(1);

/* HEADERIZER END: src/objects.c */

/* Objects, classes and PMCarrays all use the same data scheme:
 * PMC_data() holds a malloced array, PMC_int_val() is the size of it
 * this simplifies DOD mark a lot
 *
 * The active destroy flag is necessary to free the malloced array.
 */
#define SLOTTYPE PMC*
#define get_attrib_num(x, y)    ((PMC **)x)[y]
#define set_attrib_num(o, x, y, z) \
    do { \
        DOD_WRITE_BARRIER(interp, o, ((PMC **)x)[y], z); \
        ((PMC **)x)[y] = z; \
    } while (0)
#define get_attrib_count(x)     PMC_int_val2(x)
#define new_attrib_array() Dont_use
#define set_attrib_flags(x) do { \
        PObj_data_is_PMC_array_SET(x); \
        PObj_active_destroy_SET(x); \
    } while (0)
#define set_attrib_array_size(o, y) do { \
    PMC_data(o) = mem_sys_allocate_zeroed((sizeof (PMC *)*(y))); \
    PMC_int_val(o) = y; \
} while (0)

#define resize_attrib_array(o, y) do { \
    PMC_data(o) = mem_sys_realloc(PMC_data(o), (sizeof (PMC *)*(y))); \
    PMC_int_val(o) = y; \
} while (0)

/*
 * class macros
 */

#  define CLASS_ATTRIB_COUNT(cl) PMC_int_val2(cl)
#  define SET_CLASS(arr, obj, cl) \
       obj->vtable->pmc_class = cl
#  define GET_CLASS(arr, obj) \
       obj->vtable->pmc_class

#endif /* PARROT_OBJECTS_H_GUARD */

/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */
