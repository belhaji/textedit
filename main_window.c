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

#include "main_window.h"




GtkWidget* main_window_new(void){
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window),APP_NAME);
	gtk_window_set_default_size (GTK_WINDOW(window),800,600);
	if (g_file_test (APP_DIR"textedit.png",G_FILE_TEST_EXISTS))
	{
		GtkWidget *icon = gtk_image_new_from_file (APP_DIR"textedit.png");
		gtk_window_set_icon(GTK_WINDOW(window),gtk_image_get_pixbuf(GTK_IMAGE(icon)));
		gtk_window_set_default_icon(gtk_image_get_pixbuf(GTK_IMAGE(icon))); 
			
	}else if (g_file_test ("textedit.png",G_FILE_TEST_EXISTS)){
		GtkWidget *icon = gtk_image_new_from_file ("textedit.png");
		gtk_window_set_icon(GTK_WINDOW(window),gtk_image_get_pixbuf(GTK_IMAGE(icon)));
		gtk_window_set_default_icon(gtk_image_get_pixbuf(GTK_IMAGE(icon))); 
	}


	return window;
}