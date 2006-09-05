/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "thanks_callback.h"
#include "thanks_interface.h"
#include "glade_util.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_thanks_window (void)
{
  GtkWidget *thanks_window;
  GtkWidget *vbox;
  GtkWidget *header_frame;
  GtkWidget *header_hbox;
  GtkWidget *header_label;
  GtkWidget *header_image;
  GtkWidget *image;
  GtkWidget *main_notebook;
  GtkWidget *main_vbox_people;
  GtkWidget *main_label_people;
  GtkWidget *main_scrolledwindow_people;
  GtkWidget *textview1;
  GtkWidget *main_tab_label_people;
  GtkWidget *main_vbox_projects;
  GtkWidget *main_label_projects;
  GtkWidget *main_scrolledwindow_projects;
  GtkWidget *viewport1;
  GtkWidget *main_table_libraries;
  GtkWidget *label7;
  GtkWidget *image2;
  GtkWidget *image3;
  GtkWidget *image4;
  GtkWidget *label8;
  GtkWidget *label10;
  GtkWidget *label11;
  GtkWidget *label12;
  GtkWidget *label9;
  GtkWidget *label13;
  GtkWidget *label14;
  GtkWidget *image5;
  GtkWidget *label15;
  GtkWidget *label16;
  GtkWidget *image6;
  GtkWidget *image7;
  GtkWidget *label17;
  GtkWidget *label18;
  GtkWidget *image8;
  GtkWidget *label19;
  GtkWidget *label20;
  GtkWidget *main_tab_label_projects;
  GtkWidget *hseparator1;
  GtkWidget *dialog_hbuttonbox;
  GtkWidget *dialog_button_close;

  thanks_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (thanks_window, "thanks_window");
  gtk_window_set_title (GTK_WINDOW (thanks_window), _("KCemu: Thanks"));
  gtk_window_set_position (GTK_WINDOW (thanks_window), GTK_WIN_POS_CENTER);
  gtk_window_set_type_hint (GTK_WINDOW (thanks_window), GDK_WINDOW_TYPE_HINT_DIALOG);

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox, "vbox");
  gtk_widget_show (vbox);
  gtk_container_add (GTK_CONTAINER (thanks_window), vbox);

  header_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (header_frame, "header_frame");
  gtk_widget_show (header_frame);
  gtk_box_pack_start (GTK_BOX (vbox), header_frame, FALSE, TRUE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (header_frame), GTK_SHADOW_ETCHED_OUT);

  header_hbox = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (header_hbox, "header_hbox");
  gtk_widget_show (header_hbox);
  gtk_container_add (GTK_CONTAINER (header_frame), header_hbox);

  header_label = gtk_label_new (_("Thanks"));
  gtk_widget_set_name (header_label, "header_label");
  gtk_widget_show (header_label);
  gtk_box_pack_start (GTK_BOX (header_hbox), header_label, TRUE, TRUE, 0);
  gtk_misc_set_alignment (GTK_MISC (header_label), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (header_label), 6, 0);

  header_image = create_pixmap (thanks_window, "window-thanks.png");
  gtk_widget_set_name (header_image, "header_image");
  gtk_widget_show (header_image);
  gtk_box_pack_start (GTK_BOX (header_hbox), header_image, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (header_image), 4, 4);

  image = create_pixmap (thanks_window, "kcemu.png");
  gtk_widget_set_name (image, "image");
  gtk_widget_show (image);
  gtk_box_pack_start (GTK_BOX (vbox), image, FALSE, TRUE, 0);
  gtk_misc_set_padding (GTK_MISC (image), 20, 8);

  main_notebook = gtk_notebook_new ();
  gtk_widget_set_name (main_notebook, "main_notebook");
  gtk_widget_show (main_notebook);
  gtk_box_pack_start (GTK_BOX (vbox), main_notebook, TRUE, TRUE, 0);
  gtk_widget_set_size_request (main_notebook, 500, 250);

  main_vbox_people = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (main_vbox_people, "main_vbox_people");
  gtk_widget_show (main_vbox_people);
  gtk_container_add (GTK_CONTAINER (main_notebook), main_vbox_people);

  main_label_people = gtk_label_new (_("I'd like to say thanks to many people who helped to bring KCemu to the point where it is now. The following list just lists some of them in no particular order..."));
  gtk_widget_set_name (main_label_people, "main_label_people");
  gtk_widget_show (main_label_people);
  gtk_box_pack_start (GTK_BOX (main_vbox_people), main_label_people, FALSE, FALSE, 0);
  GTK_WIDGET_SET_FLAGS (main_label_people, GTK_CAN_FOCUS);
  gtk_label_set_line_wrap (GTK_LABEL (main_label_people), TRUE);
  gtk_label_set_selectable (GTK_LABEL (main_label_people), TRUE);
  gtk_misc_set_alignment (GTK_MISC (main_label_people), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (main_label_people), 4, 4);

  main_scrolledwindow_people = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_name (main_scrolledwindow_people, "main_scrolledwindow_people");
  gtk_widget_show (main_scrolledwindow_people);
  gtk_box_pack_start (GTK_BOX (main_vbox_people), main_scrolledwindow_people, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (main_scrolledwindow_people), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (main_scrolledwindow_people), GTK_SHADOW_IN);

  textview1 = gtk_text_view_new ();
  gtk_widget_set_name (textview1, "textview1");
  gtk_widget_show (textview1);
  gtk_container_add (GTK_CONTAINER (main_scrolledwindow_people), textview1);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview1), FALSE);
  gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW (textview1), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview1), FALSE);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview1), 4);
  gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textview1), 4);
  gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview1)), _("Marat Fayzullin\n        for the Z80 emulation core used for the main processor\n        (I needed to tweak some bits of the emulation core; see\n        src/z80core/README for the list of changes)\nMarcel de Kogel\n        for the Z80 emulation core used for the KC floppy\n        processor\nThomas Bretz\n        for the OS/2 port of KCemu (see http://www.d4m.de/)\nThomas Ludwig\n        for the great KC website at http://www.kc85emu.de/ and\n        lots of bugreports and hints how to make KCemu better\nHolger Krull\n        for providing lots of information about the LC 80\n        computer (see http://www.lc80.de/)\nKev Thacker\n        for interesting insights concerning the floppy emulation\n        (he's also the author of the KC driver for M.E.S.S. the\n        Multi-Emulator Super System, see http://mess.emuverse.com/)\nVolker Pohlers\n        for help with the windows port, technical information and\n        bugreports\nAlexander Sch\303\266n\n        for starting the windows port, lots of tips and for providing\n        a huge pile of files for use with the emulator or with\n        information about the various systems"), -1);

  main_tab_label_people = gtk_label_new (_("People"));
  gtk_widget_set_name (main_tab_label_people, "main_tab_label_people");
  gtk_widget_show (main_tab_label_people);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (main_notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (main_notebook), 0), main_tab_label_people);

  main_vbox_projects = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (main_vbox_projects, "main_vbox_projects");
  gtk_widget_show (main_vbox_projects);
  gtk_container_add (GTK_CONTAINER (main_notebook), main_vbox_projects);

  main_label_projects = gtk_label_new (_("Lots of tools and libraries made it easier to write KCemu. Many thanks to the people behind all those projects for their work..."));
  gtk_widget_set_name (main_label_projects, "main_label_projects");
  gtk_widget_show (main_label_projects);
  gtk_box_pack_start (GTK_BOX (main_vbox_projects), main_label_projects, FALSE, FALSE, 0);
  GTK_WIDGET_SET_FLAGS (main_label_projects, GTK_CAN_FOCUS);
  gtk_label_set_line_wrap (GTK_LABEL (main_label_projects), TRUE);
  gtk_label_set_selectable (GTK_LABEL (main_label_projects), TRUE);
  gtk_misc_set_alignment (GTK_MISC (main_label_projects), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (main_label_projects), 4, 4);

  main_scrolledwindow_projects = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_name (main_scrolledwindow_projects, "main_scrolledwindow_projects");
  gtk_widget_show (main_scrolledwindow_projects);
  gtk_box_pack_start (GTK_BOX (main_vbox_projects), main_scrolledwindow_projects, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (main_scrolledwindow_projects), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  viewport1 = gtk_viewport_new (NULL, NULL);
  gtk_widget_set_name (viewport1, "viewport1");
  gtk_widget_show (viewport1);
  gtk_container_add (GTK_CONTAINER (main_scrolledwindow_projects), viewport1);

  main_table_libraries = gtk_table_new (14, 2, FALSE);
  gtk_widget_set_name (main_table_libraries, "main_table_libraries");
  gtk_widget_show (main_table_libraries);
  gtk_container_add (GTK_CONTAINER (viewport1), main_table_libraries);
  gtk_container_set_border_width (GTK_CONTAINER (main_table_libraries), 6);
  gtk_table_set_row_spacings (GTK_TABLE (main_table_libraries), 4);
  gtk_table_set_col_spacings (GTK_TABLE (main_table_libraries), 16);

  label7 = gtk_label_new (_("libSDL - Simple DirectMedia Layer"));
  gtk_widget_set_name (label7, "label7");
  gtk_widget_show (label7);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label7, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label7, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label7), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label7), 0, 0.5);

  image2 = create_pixmap (thanks_window, "logo-gtk.png");
  gtk_widget_set_name (image2, "image2");
  gtk_widget_show (image2);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image2, 0, 1, 0, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (image2), 0.5, 0);

  image3 = create_pixmap (thanks_window, "logo-libsdl.png");
  gtk_widget_set_name (image3, "image3");
  gtk_widget_show (image3);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image3, 0, 1, 2, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (image3), 0.5, 0);

  image4 = create_pixmap (thanks_window, "logo-flac.png");
  gtk_widget_set_name (image4, "image4");
  gtk_widget_show (image4);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image4, 0, 1, 4, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (image4), 0.5, 0);

  label8 = gtk_label_new (_("GTK+ - The GIMP Toolkit"));
  gtk_widget_set_name (label8, "label8");
  gtk_widget_show (label8);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label8, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label8, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label8), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label8), 0, 0.5);

  label10 = gtk_label_new (_("http://www.libsdl.org/\n"));
  gtk_widget_set_name (label10, "label10");
  gtk_widget_show (label10);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label10, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label10, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label10), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label10), 0, 0.5);

  label11 = gtk_label_new (_("FLAC - Free Lossless Audio Codec"));
  gtk_widget_set_name (label11, "label11");
  gtk_widget_show (label11);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label11, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label11, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label11), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label11), 0, 0.5);

  label12 = gtk_label_new (_("http://flac.sourceforge.net/\n"));
  gtk_widget_set_name (label12, "label12");
  gtk_widget_show (label12);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label12, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label12, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label12), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label12), 0, 0.5);

  label9 = gtk_label_new (_("http://www.gtk.org/\n"));
  gtk_widget_set_name (label9, "label9");
  gtk_widget_show (label9);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label9, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  GTK_WIDGET_SET_FLAGS (label9, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label9), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label9), 0, 0.5);

  label13 = gtk_label_new (_("LAME - LAME Ain't an MP3 Encoder"));
  gtk_widget_set_name (label13, "label13");
  gtk_widget_show (label13);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label13, 1, 2, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label13, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label13), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label13), 0, 0.5);

  label14 = gtk_label_new (_("http://lame.sourceforge.net/\n"));
  gtk_widget_set_name (label14, "label14");
  gtk_widget_show (label14);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label14, 1, 2, 7, 8,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label14, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label14), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label14), 0, 0.5);

  image5 = create_pixmap (thanks_window, "logo-lame.png");
  gtk_widget_set_name (image5, "image5");
  gtk_widget_show (image5);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image5, 0, 1, 6, 8,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (image5), 0.5, 0);

  label15 = gtk_label_new (_("Open Clip Art Library"));
  gtk_widget_set_name (label15, "label15");
  gtk_widget_show (label15);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label15, 1, 2, 8, 9,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label15, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label15), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label15), 0, 0.5);

  label16 = gtk_label_new (_("http://openclipart.org/\n"));
  gtk_widget_set_name (label16, "label16");
  gtk_widget_show (label16);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label16, 1, 2, 9, 10,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label16, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label16), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label16), 0, 0.5);

  image6 = create_pixmap (thanks_window, "logo-openclipartlibrary.png");
  gtk_widget_set_name (image6, "image6");
  gtk_widget_show (image6);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image6, 0, 1, 8, 10,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (image6), 0.5, 0);

  image7 = create_pixmap (thanks_window, "logo-vorbisdotcom.png");
  gtk_widget_set_name (image7, "image7");
  gtk_widget_show (image7);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image7, 0, 1, 10, 12,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label17 = gtk_label_new (_("Ogg & Vorbis libraries"));
  gtk_widget_set_name (label17, "label17");
  gtk_widget_show (label17);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label17, 1, 2, 10, 11,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label17, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label17), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label17), 0, 0.5);

  label18 = gtk_label_new (_("http://www.vorbis.com/\n"));
  gtk_widget_set_name (label18, "label18");
  gtk_widget_show (label18);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label18, 1, 2, 11, 12,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label18, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label18), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label18), 0, 0.5);

  image8 = create_pixmap (thanks_window, "logo-libsndfile.png");
  gtk_widget_set_name (image8, "image8");
  gtk_widget_show (image8);
  gtk_table_attach (GTK_TABLE (main_table_libraries), image8, 0, 1, 12, 14,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label19 = gtk_label_new (_("libsndfile"));
  gtk_widget_set_name (label19, "label19");
  gtk_widget_show (label19);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label19, 1, 2, 12, 13,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label19, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label19), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label19), 0, 0.5);

  label20 = gtk_label_new (_("http://www.mega-nerd.com/libsndfile/\n"));
  gtk_widget_set_name (label20, "label20");
  gtk_widget_show (label20);
  gtk_table_attach (GTK_TABLE (main_table_libraries), label20, 1, 2, 13, 14,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (label20, GTK_CAN_FOCUS);
  gtk_label_set_selectable (GTK_LABEL (label20), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label20), 0, 0.5);

  main_tab_label_projects = gtk_label_new (_("Projects & Libraries"));
  gtk_widget_set_name (main_tab_label_projects, "main_tab_label_projects");
  gtk_widget_show (main_tab_label_projects);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (main_notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (main_notebook), 1), main_tab_label_projects);

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_set_name (hseparator1, "hseparator1");
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vbox), hseparator1, FALSE, TRUE, 6);

  dialog_hbuttonbox = gtk_hbutton_box_new ();
  gtk_widget_set_name (dialog_hbuttonbox, "dialog_hbuttonbox");
  gtk_widget_show (dialog_hbuttonbox);
  gtk_box_pack_start (GTK_BOX (vbox), dialog_hbuttonbox, FALSE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_hbuttonbox), 6);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_hbuttonbox), GTK_BUTTONBOX_END);

  dialog_button_close = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_set_name (dialog_button_close, "dialog_button_close");
  gtk_widget_show (dialog_button_close);
  gtk_container_add (GTK_CONTAINER (dialog_hbuttonbox), dialog_button_close);
  GTK_WIDGET_SET_FLAGS (dialog_button_close, GTK_CAN_DEFAULT);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (thanks_window, thanks_window, "thanks_window");
  GLADE_HOOKUP_OBJECT (thanks_window, vbox, "vbox");
  GLADE_HOOKUP_OBJECT (thanks_window, header_frame, "header_frame");
  GLADE_HOOKUP_OBJECT (thanks_window, header_hbox, "header_hbox");
  GLADE_HOOKUP_OBJECT (thanks_window, header_label, "header_label");
  GLADE_HOOKUP_OBJECT (thanks_window, header_image, "header_image");
  GLADE_HOOKUP_OBJECT (thanks_window, image, "image");
  GLADE_HOOKUP_OBJECT (thanks_window, main_notebook, "main_notebook");
  GLADE_HOOKUP_OBJECT (thanks_window, main_vbox_people, "main_vbox_people");
  GLADE_HOOKUP_OBJECT (thanks_window, main_label_people, "main_label_people");
  GLADE_HOOKUP_OBJECT (thanks_window, main_scrolledwindow_people, "main_scrolledwindow_people");
  GLADE_HOOKUP_OBJECT (thanks_window, textview1, "textview1");
  GLADE_HOOKUP_OBJECT (thanks_window, main_tab_label_people, "main_tab_label_people");
  GLADE_HOOKUP_OBJECT (thanks_window, main_vbox_projects, "main_vbox_projects");
  GLADE_HOOKUP_OBJECT (thanks_window, main_label_projects, "main_label_projects");
  GLADE_HOOKUP_OBJECT (thanks_window, main_scrolledwindow_projects, "main_scrolledwindow_projects");
  GLADE_HOOKUP_OBJECT (thanks_window, viewport1, "viewport1");
  GLADE_HOOKUP_OBJECT (thanks_window, main_table_libraries, "main_table_libraries");
  GLADE_HOOKUP_OBJECT (thanks_window, label7, "label7");
  GLADE_HOOKUP_OBJECT (thanks_window, image2, "image2");
  GLADE_HOOKUP_OBJECT (thanks_window, image3, "image3");
  GLADE_HOOKUP_OBJECT (thanks_window, image4, "image4");
  GLADE_HOOKUP_OBJECT (thanks_window, label8, "label8");
  GLADE_HOOKUP_OBJECT (thanks_window, label10, "label10");
  GLADE_HOOKUP_OBJECT (thanks_window, label11, "label11");
  GLADE_HOOKUP_OBJECT (thanks_window, label12, "label12");
  GLADE_HOOKUP_OBJECT (thanks_window, label9, "label9");
  GLADE_HOOKUP_OBJECT (thanks_window, label13, "label13");
  GLADE_HOOKUP_OBJECT (thanks_window, label14, "label14");
  GLADE_HOOKUP_OBJECT (thanks_window, image5, "image5");
  GLADE_HOOKUP_OBJECT (thanks_window, label15, "label15");
  GLADE_HOOKUP_OBJECT (thanks_window, label16, "label16");
  GLADE_HOOKUP_OBJECT (thanks_window, image6, "image6");
  GLADE_HOOKUP_OBJECT (thanks_window, image7, "image7");
  GLADE_HOOKUP_OBJECT (thanks_window, label17, "label17");
  GLADE_HOOKUP_OBJECT (thanks_window, label18, "label18");
  GLADE_HOOKUP_OBJECT (thanks_window, image8, "image8");
  GLADE_HOOKUP_OBJECT (thanks_window, label19, "label19");
  GLADE_HOOKUP_OBJECT (thanks_window, label20, "label20");
  GLADE_HOOKUP_OBJECT (thanks_window, main_tab_label_projects, "main_tab_label_projects");
  GLADE_HOOKUP_OBJECT (thanks_window, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (thanks_window, dialog_hbuttonbox, "dialog_hbuttonbox");
  GLADE_HOOKUP_OBJECT (thanks_window, dialog_button_close, "dialog_button_close");

  gtk_widget_grab_focus (dialog_button_close);
  gtk_widget_grab_default (dialog_button_close);
  return thanks_window;
}

