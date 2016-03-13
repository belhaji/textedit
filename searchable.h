#ifndef SW
#define SW

#include "textedit.h"

typedef struct 
{
	gchar 	*word;
	gint  	len;
	gint 	lineNumber;
	gint	columnNumber;
	
} SearchableWord;



LinkedList* find_all_searchable_words(CSIde_app *app);

void replace_all_searchable_words(CSIde_app *app, LinkedList* swList);

SearchableWord* get_searchable(GtkMark* mark);


#endif SW 