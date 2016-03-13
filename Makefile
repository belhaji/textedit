OBJ_FILES=textedit.o main_window.o main.o callback.o main_menu.o main_tool_bar.o editor.o actions.o search_box.o

CC=gcc

CFLAGS=-w `pkg-config --cflags gtk+-3.0 gtksourceview-3.0 vte-2.90`

CLIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0 vte-2.90`

textedit  :   $(OBJ_FILES)
	$(CC) -o textedit $(OBJ_FILES) $(CFLAGS) $(CLIBS)

main.o		:   main.c
	   $(CC) -c main.c $(CFLAGS) $(CLIBS)

textedit.o :   textedit.c
	   $(CC) -c textedit.c $(CFLAGS) $(CLIBS)

main_window.o		:   main_window.c
	   $(CC) -c main_window.c $(CFLAGS) $(CLIBS)

callback.o		:   callback.c
	   $(CC) -c callback.c $(CFLAGS) $(CLIBS)

main_menu.o		:   main_menu.c
	   $(CC) -c main_menu.c $(CFLAGS) $(CLIBS)

main_tool_bar.o		:   main_tool_bar.c
	   $(CC) -c main_tool_bar.c $(CFLAGS) $(CLIBS)

editor.o		:   editor.c
	   $(CC) -c editor.c $(CFLAGS) $(CLIBS)

actions.o		:   actions.c
	   $(CC) -c actions.c $(CFLAGS) $(CLIBS)

search_box.o	:   search_box.c
	   $(CC) -c search_box.c $(CFLAGS) $(CLIBS)


install 	:
	rm -rf /usr/share/textedit/
	mkdir /usr/share/textedit/
	cp -f textedit.png /usr/share/textedit/
	cp -f textedit.desktop /usr/share/applications/
	cp -f textedit /usr/bin/	
	cp -f textedit_uninstall /usr/bin/	
clean : 
	rm -rf *.o
