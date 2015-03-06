/* simple test program to print out the utf8proc properties for a codepoint */

#include "tests.h"

int main(int argc, char **argv)
{
     int i;

     for (i = 1; i < argc; ++i) {
          int c;
          check(sscanf(argv[i],"%x",&c) == 1, "invalid hex input %s", argv[i]);
          const utf8proc_property_t *p = utf8proc_get_property(c);
          printf("U+%s:\n"
                 "  category = %d\n"
                 "  combining_class = %d\n"
                 "  bidi_class = %d\n"
                 "  decomp_type = %d\n"
                 "  uppercase_mapping = %x\n"
                 "  lowercase_mapping = %x\n"
                 "  titlecase_mapping = %x\n"
                 "  comb1st_index = %d\n"
                 "  comb2nd_index = %d\n"
                 "  bidi_mirrored = %d\n"
                 "  comp_exclusion = %d\n"
                 "  ignorable = %d\n"
                 "  control_boundary = %d\n"
                 "  boundclass = %d\n",
                 argv[i],
                 p->category,
                 p->combining_class,
                 p->bidi_class,
                 p->decomp_type,
                 p->uppercase_mapping,
                 p->lowercase_mapping,
                 p->titlecase_mapping,
                 p->comb1st_index,
                 p->comb2nd_index,
                 p->bidi_mirrored,
                 p->comp_exclusion,
                 p->ignorable,
                 p->control_boundary,
                 p->boundclass);
     }
     return 0;
}