/*
 * Copyright (C) 2016 adil belhaji <belhaji.dev@gmail.com>
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


#ifndef EDIT_TEXT
#define EDIT_TEXT

#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>



/* define the application infos */

#define APP_NAME	 "textedit"

#define APP_VERSION	 "0.1"

#define AUTHOR_NAME	 "Belhaji Adil"

#define AUTHOR_EMAIL "belhaji.dev@gmail.com"

#define CONFIG_DIR	 "/.textedit/"

#define CONFIG_FILE	 ".textedit.rc"

#define APP_DIR		 "/usr/share/textedit/"

#define ICON_PATH	 APP_DIR"textedit.png"


/* define app data structure */
typedef struct {
	GtkWidget *scrolled_window;
	GtkWidget *source_view;
	GtkSourceBuffer *buffer;
}Editor;

typedef struct {
	gchar *name;
	gchar *bin_name;
	gboolean isSaved;
	gboolean isOnDisk;
}Document;


typedef struct {
	GtkWidget *main_window;
	GtkWidget *main_menu;
	GtkWidget *main_toolbar;
	Editor *editor;
	Document *doc;
} CSIde_app;


/* define app functions for initialization */

CSIde_app *cside_app_new(void);

void cside_app_free(CSIde_app *app);





#endif // EDIT_TEXT 