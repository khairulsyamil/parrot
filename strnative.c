/* strnative.c

   Functions for handling strings in native byte format
   "Native" in this context means the equivalent of "LANG=C": No
   fancy multi-byte stuff, this is plain old byte-at-a-time. But
   we don't make any assumptions about what those bytes *mean*.
*/

#include "parrot.h"

static IV 
string_native_compute_strlen (STRING *s) {
    return s->buflen;
}

static IV 
string_native_max_bytes (IV x) {
    return x;
}

static STRING*
string_native_concat(STRING* a, STRING* b, IV flags) {
    if (flags && a->encoding != b->encoding) {
	/* Transcode */
    }
    
    /* b is now in native format */
    string_grow(a, a->strlen + b->strlen);
    mem_sys_memcopy(a->bufstart + a->strlen, b->bufstart, b->strlen);
    a->strlen = a->bufused = a->strlen + b->strlen;
    return a;
}

static STRING*
string_native_chopn(STRING* s, IV n) {
    s->bufused -= n;
    s->strlen -= n;
    return s;
}

static STRING*
string_native_substr(STRING* src, IV offset, IV length, STRING* dest)
{
	if (dest->encoding->which != enc_native)
	    /* It is now, matey. */
	    dest->encoding = &(Parrot_string_vtable[enc_native]);
    
    /* Offset and length have already been "normalized" */
    string_grow(dest, length);
    mem_sys_memcopy(dest->bufstart, src->bufstart + offset, length);
    dest->strlen = dest->bufused = length;
    
    return dest;
}

STRING_VTABLE 
string_native_vtable (void) {
    STRING_VTABLE sv = {
	enc_native,
	string_native_compute_strlen,
	string_native_max_bytes,
	string_native_concat,
	string_native_chopn,
	string_native_substr,
    };
    return sv;
}
