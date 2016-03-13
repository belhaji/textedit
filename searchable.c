


#include "searchable.h"



LinkedList* find_all_searchable_words(CSIde_app *app){
	LinkedList* swList = list_new();
	SearchableWord* sw;
	GTkMark * tmp;
	gchar *wordTofind = gtk_search_box_get_text(app->searchBox);
	if (wordTofind == NULL)
	{
		return NULL;
	}
	while(gtk_text_buffer_get_next(app->textBuffer,wordTofind) != NULL){
		tmp = gtk_text_buffer_get_mark(app->textBuffer);
		sw = get_searchable(mark);
		list_add(swList,sw);
	} 
	return swList;
}

void replace_all_searchable_words(CSIde_app *app, LinkedList* swList){
	if (swList == NULL)	
		return;
	int i;
	gchar* wordToReplace = gtk_search_box_get_text(app->textReplaceBuffer);
	GtkMark *mark;
	SearchableWord *sw;
	for (i = 0; i < list_size(swList); ++i)
	{
		sw = (SearchableWord*) list_get(swList,i);
		mark = gtk_text_buffer_get_mark_at(app->textBuffer,
					sw->word,
					sw->len,
					sw->lineNumber,
					sw->columnNumber);
		gtk_text_buffer_replace(app->textBuffer,mark);
	}
	
}

SearchableWord* get_searchable(GtkMark* mark){

	SearchableWord *sw =(SearchableWord*) malloc(sizeof(SearchableWord));
	sw->word = gtk_mark_get_word(mark);
	sw->len = gtk_mark_get_word_size(mark);
	sw->lineNumber = gtk_mark_get_line(mark);
	sw->columnNumber = gtk_mark_get_column(mark);
	return sw;
}

