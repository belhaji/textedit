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

#include "editor.h"
#include <gtksourceview/gtksourceview.h>
#include "callback.h"


Editor * editor_create(CSIde_app *app){
	GtkSourceBuffer *buffer;
	PangoFontDescription *fontDesc;
	gchar *font_name,*filename;
	filename =(gchar*) g_malloc(sizeof(gchar)*100);
	sprintf(filename,"%s/"CONFIG_FILE,g_get_home_dir());

	Editor *editor  = (Editor*) g_slice_new(Editor);

	editor->scrolled_window = gtk_scrolled_window_new (NULL,NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(editor->scrolled_window ),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	buffer  = gtk_source_buffer_new (NULL);
	g_signal_connect(buffer,"changed",G_CALLBACK(buffer_changed),app);
	editor->buffer = buffer;
	editor->source_view = gtk_source_view_new_with_buffer (buffer);
	gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW(editor->source_view),TRUE);
	gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW(editor->source_view),TRUE);
	gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW(editor->source_view),TRUE);

	if(g_file_test (filename,G_FILE_TEST_EXISTS)){
		g_file_get_contents (filename,&font_name,NULL,NULL);
		fontDesc = pango_font_description_from_string (font_name);
		gtk_widget_override_font (editor->source_view,fontDesc);
		pango_font_description_free (fontDesc);
		g_free(font_name);
	}else{
		fontDesc = pango_font_description_from_string ("Monospace 13");
		gtk_widget_override_font (editor->source_view,fontDesc);
		pango_font_description_free (fontDesc);
	}
	g_free(filename);
	gtk_source_buffer_set_highlight_syntax (buffer,TRUE);
	gtk_container_add (GTK_CONTAINER(editor->scrolled_window),editor->source_view);

	return editor;
}




















