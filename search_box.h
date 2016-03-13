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

#ifndef SEARCH_BOX_H
#define SEARCH_BOX_H

#include "textedit.h"


typedef struct 
{
	GtkWidget *find_entry;		
	GtkWidget *replace_entry;
	CSIde_app *app;		
}SearchBox;

void search_box(CSIde_app *app);

void search_btn_clicked(GtkWidget *wid,gpointer data);

void replace_btn_clicked(GtkWidget *wid,gpointer data);

void replace_all_btn_clicked(GtkWidget *wid,gpointer data);

#endif /* SEARCH_BOX_H */