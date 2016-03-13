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
 
#include "callback.h"
#include "actions.h"
#include "textedit.h"
#include "search_box.h"


void menu_item_new_clicked(GtkWidget *wid,gpointer data)
{
	new_file((CSIde_app*) data);
	update_title((CSIde_app*) data);
}

void menu_item_open_clicked(GtkWidget *wid,gpointer data)
{
	open_file((CSIde_app*)data);
	update_title((CSIde_app*) data);
}

void menu_item_save_clicked(GtkWidget *wid,gpointer data)
{ 
	CSIde_app *app = (CSIde_app*) data;
	if(app->doc->name != NULL && app->doc->isOnDisk == TRUE)
		save_file(app);
	else
		save_file_as(app);
	update_title(app);
}

void menu_item_save_as_clicked(GtkWidget *wid,gpointer data){
	save_file_as((CSIde_app*) data);
	update_title((CSIde_app*) data);
}

void menu_item_quit_clicked(GtkWidget *item,gpointer data){
	quit_app((CSIde_app*) data);
}


void menu_item_undo_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	if(gtk_source_buffer_can_undo (app->editor->buffer))
		gtk_source_buffer_undo (app->editor->buffer);
}

void menu_item_redo_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	if(gtk_source_buffer_can_redo (app->editor->buffer))
		gtk_source_buffer_redo (app->editor->buffer);
}


void menu_item_copy_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer =  GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_copy_clipboard (buffer, clipboard);
}

void menu_item_cut_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_cut_clipboard (buffer, clipboard,TRUE);
}

void menu_item_paste_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_paste_clipboard (buffer, clipboard, NULL, TRUE);
}

void menu_item_delete_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkTextBuffer *buffer   = GTK_TEXT_BUFFER(app->editor->buffer);
	GtkTextIter iStart,iEnd;

	gtk_text_buffer_get_selection_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_delete(buffer,&iStart,&iEnd);
}

void menu_item_select_all_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkTextBuffer *buffer   = GTK_TEXT_BUFFER(app->editor->buffer);
	GtkTextIter iStart,iEnd;
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_select_range(buffer,&iStart,&iEnd);
}

void menu_item_deselect_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	GtkTextBuffer *buffer   = GTK_TEXT_BUFFER(app->editor->buffer);
	GtkTextIter iStart,iEnd;
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_select_range(buffer,&iEnd,&iEnd);
}


void menu_item_to_upper_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gchar *text;
	GtkTextIter iStart,iEnd;
	GtkTextBuffer *buffer   = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_get_selection_bounds(buffer,&iStart,&iEnd);
	text = gtk_text_buffer_get_text (buffer,&iStart,&iEnd,FALSE);
	g_utf8_strup (text,-1);
	gtk_text_buffer_delete (buffer,&iStart,&iEnd);
	gtk_text_buffer_insert (buffer,&iStart,g_utf8_strup(text,-1),-1);	
}

void menu_item_to_lower_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gchar *text;
	GtkTextIter iStart,iEnd;
	GtkTextBuffer *buffer   = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_get_selection_bounds(buffer,&iStart,&iEnd);
	text = gtk_text_buffer_get_text (buffer,&iStart,&iEnd,FALSE);
	g_utf8_strup (text,-1);
	gtk_text_buffer_delete (buffer,&iStart,&iEnd);
	gtk_text_buffer_insert (buffer,&iStart,g_utf8_strdown(text,-1),-1);

}

void menu_item_find_clicked(GtkWidget *wid,gpointer data){
	search_box((CSIde_app*) data);
}



void menu_item_line_number_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gboolean show_numbers = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wid)); 
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(app->editor->source_view),show_numbers);
}

void menu_item_auto_indent_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gboolean auto_indent = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wid)); 
	gtk_source_view_set_auto_indent(GTK_SOURCE_VIEW(app->editor->source_view),auto_indent);
}

void menu_item_highlight_line_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gboolean highlight_line = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wid)); 
	gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(app->editor->source_view),highlight_line);
}

void menu_item_tool_bar_clicked(GtkWidget *wid,gpointer data){
	CSIde_app *app = (CSIde_app*) data;
	gboolean show_tool_bar = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(wid)); 
	if(show_tool_bar)
		gtk_widget_show(app->main_toolbar);	
	else
		gtk_widget_hide(app->main_toolbar);	
}

void menu_item_font_clicked(GtkWidget *wid,gpointer data){
	CSIde_app   *app = (CSIde_app*) data;
	PangoFontDescription *fontDesc;
	gchar *font_name;
	GtkWidget *fontDialog;
	gchar *filename;
	
	filename =(gchar*) g_malloc(sizeof(gchar)*100);
	sprintf(filename,"%s/"CONFIG_FILE,g_get_home_dir());

	fontDialog = gtk_font_chooser_dialog_new ("Choose a font",GTK_WINDOW(app->main_window));
	if(g_file_test (filename,G_FILE_TEST_EXISTS)){
		g_file_get_contents (filename,&font_name,NULL,NULL);
		gtk_font_chooser_set_font (GTK_FONT_CHOOSER(fontDialog),font_name);
		g_free(font_name);
	}


	gint result = gtk_dialog_run(GTK_DIALOG(fontDialog));
	if(result == GTK_RESPONSE_CANCEL)
		gtk_widget_destroy(fontDialog);
	else{
		font_name = gtk_font_chooser_get_font (GTK_FONT_CHOOSER(fontDialog));
		fontDesc = pango_font_description_from_string (font_name);
		gtk_widget_override_font (app->editor->source_view,fontDesc);
		pango_font_description_free (fontDesc);
		g_file_set_contents (filename,font_name,-1,NULL);
		g_free(font_name);
		gtk_widget_destroy(fontDialog);
	}
	g_free(filename);
	
}




void menu_item_about_clicked(GtkWidget *wid,gpointer data){
	CSIde_app   *app = (CSIde_app*) data;
	GtkWidget   *aboutDialog;
	const gchar		*author[] = {AUTHOR_NAME,"Achraf Hammoumi",NULL};
	aboutDialog = gtk_about_dialog_new ();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutDialog),APP_NAME);
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutDialog),APP_VERSION);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutDialog),"2014 (c) Adil Belhaji");
	gtk_about_dialog_set_license (GTK_ABOUT_DIALOG(aboutDialog),"ce programme est open source utiliser le comme vous voulez");
	gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(aboutDialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(aboutDialog),author);
	gtk_about_dialog_set_logo_icon_name (GTK_ABOUT_DIALOG(aboutDialog),ICON_PATH);
	gtk_dialog_run (GTK_DIALOG(aboutDialog));
	gtk_widget_destroy(aboutDialog);
}

gboolean mainWindowDeleteEvent(GtkWidget *wid,GdkEvent  *e,gpointer data)
{
	quit_app ((CSIde_app*) data);	
	return TRUE;
}

void buffer_changed(GtkWidget *wid,gpointer data){
	CSIde_app *app= (CSIde_app*) data;
	app->doc->isSaved = FALSE;
	update_title(app);
}










