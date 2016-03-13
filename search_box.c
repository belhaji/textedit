/*
 * Copyright (C) 2014 adil belhaji <belhaji.dev@gmail.com>
 * 
 * textedit is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * textedit is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "search_box.h"

GtkTextIter iStart,iBegin,iEnd;
gboolean isFound;


void search_box(CSIde_app *app){
	SearchBox *search =(SearchBox*) g_slice_new(SearchBox);
	GtkWidget *search_dialog,
			  *area,
			  *grid,
			  *btn_find,
			  *btn_replace,
			  *btn_replace_all;
	search_dialog = gtk_dialog_new_with_buttons ("search box",
                             GTK_WINDOW(app->main_window),
                             GTK_DIALOG_DESTROY_WITH_PARENT,
                             "Close",
                             GTK_RESPONSE_CANCEL,
                             NULL);

	search->find_entry = gtk_search_entry_new();
	search->replace_entry = gtk_entry_new();
	search->app = app;

	btn_find = gtk_button_new_with_label("Find");
	g_signal_connect(btn_find,"clicked",G_CALLBACK(search_btn_clicked),(gpointer) search);
	btn_replace = gtk_button_new_with_label("Replace");
	g_signal_connect(btn_replace,"clicked",G_CALLBACK(replace_btn_clicked),(gpointer) search);
	btn_replace_all = gtk_button_new_with_label("Replace all");
	g_signal_connect(btn_replace_all,"clicked",G_CALLBACK(replace_all_btn_clicked),(gpointer) search);


	area = gtk_dialog_get_content_area(GTK_DIALOG(search_dialog));
	gtk_container_set_border_width(GTK_CONTAINER(area),10);
	grid = gtk_grid_new();
	gtk_container_set_focus_child (GTK_CONTAINER(grid),search->find_entry);
	//gtk_grid_set_row_homogeneous(GTK_GRID(grid),TRUE);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
	gtk_grid_set_row_spacing (GTK_GRID(grid),10);
	gtk_grid_set_column_spacing (GTK_GRID(grid),10);

	gtk_box_pack_start (GTK_BOX(area),grid,TRUE,TRUE,0);
	gtk_grid_attach (GTK_GRID(grid),btn_find,1,1,5,1);
	gtk_grid_attach (GTK_GRID(grid),search->find_entry,6,1,6,1);
	gtk_grid_attach (GTK_GRID(grid),btn_replace,1,3,5,1);
	gtk_grid_attach (GTK_GRID(grid),search->replace_entry,6,3,6,1);
	gtk_grid_attach (GTK_GRID(grid),btn_replace_all,1,5,5,1);
	gtk_widget_show_all(grid);

	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(search->app->editor->buffer),&iStart);


	switch(gtk_dialog_run(GTK_DIALOG(search_dialog))){
		case GTK_RESPONSE_CANCEL :
			gtk_widget_destroy(search_dialog);
			g_slice_free(SearchBox,search);
			break;

	}

}

void search_btn_clicked(GtkWidget *wid,gpointer data){
	SearchBox *search = (SearchBox*) data;
	gchar const *txt_to_find;
	txt_to_find = gtk_entry_get_text(GTK_ENTRY(search->find_entry));
	if(gtk_text_iter_forward_search (&iStart, (gchar*)txt_to_find ,0,&iBegin, &iEnd, NULL)){
		gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(search->app->editor->source_view),&iStart,0,TRUE,0.5,0.5);
		gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER(search->app->editor->buffer),&iBegin);
		gtk_text_buffer_select_range (GTK_TEXT_BUFFER(search->app->editor->buffer),&iBegin,&iEnd);
		iStart = iEnd;
		isFound = TRUE;
	}else{
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(search->app->editor->buffer),&iStart);	
		isFound = FALSE;
	}

}


void replace_btn_clicked(GtkWidget *wid,gpointer data){
	SearchBox *search = (SearchBox*) data;
	gchar const *txt_to_replace;
	if(isFound){	
	txt_to_replace = gtk_entry_get_text(GTK_ENTRY(search->replace_entry));
	gtk_text_buffer_delete (GTK_TEXT_BUFFER(search->app->editor->buffer),&iBegin,&iEnd);
	gtk_text_buffer_insert (GTK_TEXT_BUFFER(search->app->editor->buffer),&iBegin,txt_to_replace,-1);
	iStart = iBegin;
	isFound = FALSE;
	search_btn_clicked(NULL,data);
	}
}


void replace_all_btn_clicked(GtkWidget *wid,gpointer data){
	while(isFound)
		replace_btn_clicked(NULL,data);	
}







