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

#include "main_tool_bar.h"
#include "callback.h"


GtkWidget * createToolBar(CSIde_app *app)
{
	GtkWidget *toolBar;
	GtkToolItem *btnNew,
				*btnOpen,
				*btnSave,
				*btnUndo,
				*btnRedo,
				*btnCopy,
				*btnPaste,
				*btnCut,
				*btnDelete,
				*btnSelectAll,
				*separator,
				*btnSearch;

	toolBar			= gtk_toolbar_new ();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolBar),GTK_TOOLBAR_ICONS);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolBar),GTK_ICON_SIZE_LARGE_TOOLBAR);
	
	btnNew			= gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	btnOpen			= gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
	btnSave			= gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
	btnUndo			= gtk_tool_button_new_from_stock (GTK_STOCK_UNDO);
	btnRedo			= gtk_tool_button_new_from_stock (GTK_STOCK_REDO);
	btnCopy			= gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	btnPaste		= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	btnCut			= gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	btnDelete		= gtk_tool_button_new_from_stock (GTK_STOCK_DELETE);
	btnSelectAll	= gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
	btnSearch		= gtk_tool_button_new_from_stock (GTK_STOCK_FIND);
	

	separator = gtk_separator_tool_item_new ();
	
	g_signal_connect(G_OBJECT(btnNew),"clicked",G_CALLBACK(menu_item_new_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnOpen),"clicked",G_CALLBACK(menu_item_open_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSave),"clicked",G_CALLBACK(menu_item_save_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnUndo),"clicked",G_CALLBACK(menu_item_undo_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnRedo),"clicked",G_CALLBACK(menu_item_redo_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnCopy),"clicked",G_CALLBACK(menu_item_copy_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnPaste),"clicked",G_CALLBACK(menu_item_paste_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnCut),"clicked",G_CALLBACK(menu_item_cut_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnDelete),"clicked",G_CALLBACK(menu_item_delete_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSelectAll),"clicked",G_CALLBACK(menu_item_select_all_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSearch),"clicked",G_CALLBACK(menu_item_find_clicked),(gpointer) app);
	
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnNew,0);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnOpen,1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSave,2);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnUndo,3);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnRedo,4);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),separator,5);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCut,6);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCopy,7);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnPaste,8);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnDelete,9);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSelectAll,10);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSearch,11);
	                 
	return toolBar;
}


