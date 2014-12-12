/*
SWIGS (Shallow Water in Irregular Geometries Simulator): a software to simulate
transient or steady flows with solute transport in channels, channel networks
and rivers.

Copyright 2005-2014 Javier Burguete Tolosa.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * \file editor_cross_section.c
 * \brief Source file to define cross section editor structures and methods.
 * \authors Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014 Javier Burguete Tolosa.
 */
#include "editor_cross_section.h"

/**
 * \def EDITOR_GEOMETRY
 * \brief Macro to get the position of the geometry editor in the notebook.
 * \def EDITOR_CROSS_SECTION
 * \brief Macro to get the position of the cross section editor in the notebook.
 * \def EDITOR_TRANSIENT_SECTION
 * \brief Macro to get the position of the transient section editor in the
 *   notebook.
 */
#if TEST_EDITOR_CROSS_SECTION
	#define EDITOR_GEOMETRY 0
	char *message;
	EditorCrossSection editor[1];
	void editor_draw() {editor_cross_section_draw(editor);}
#else
	#define EDITOR_GEOMETRY 2
#endif
#define EDITOR_CROSS_SECTION (EDITOR_GEOMETRY + 1)
#define EDITOR_TRANSIENT_SECTION (EDITOR_CROSS_SECTION + 1)

/**
 * \fn void editor_control_update(EditorControl *control)
 * \brief Function to update the view of a control type cross section.
 * \param control
 * \brief editor parameters of a control type cross section.
 */
void editor_control_update(EditorControl *control)
{
	int i;
	#if DEBUG_EDITOR_CONTROL_UPDATE
		fprintf(stderr, "editor_control_update: start\n");
	#endif
	i = gtk_combo_box_get_active(GTK_COMBO_BOX(control->combo_channel));
	jbw_combo_box_set_strings
		(control->combo_section, control->section_name[i], nsections[i]);
	#if DEBUG_EDITOR_CONTROL_UPDATE
		fprintf(stderr, "editor_control_update: end\n");
	#endif
}

/**
 * \fn void editor_control_new(EditorControl *control, char **channel_name, \
 *   int nchannels, char ***section_name, int *nsections)
 * \brief Function to create the editor parameters of a control type cross
 *   section.
 * \param control
 * \brief editor parameters of a control type cross section.
 * \param channel_name
 * \brief array of channel names.
 * \param nchannels
 * \brief number of channels.
 * \param section_name
 * \brief array of arrays of cross section names.
 * \param nsections
 * \brief array of number of cross sections.
 */
void editor_control_new(EditorControl *control, char **channel_name,
	int nchannels, char ***section_name, int *nsections)
{
	int i;
	const char *array_label[N_CONTROL_TYPES] = {
		gettext("Controlled by discharge"),
		gettext("Controlled by depth"),
		gettext("Controlled by level")};
	#if DEBUG_EDITOR_CONTROL_NEW
		fprintf(stderr, "editor_control_new: start\n");
	#endif
	control->nchannels = nchannels;
	control->nsections = nsections;
	control->channel_name = channel_name;
	control->section_name = section_name;
	control->grid = (GtkGrid*)gtk_grid_new();
	control->grid_type = (GtkGrid*)gtk_grid_new();
	control->array_type[0] = NULL;
	for (i = 0; i < N_CONTROL_TYPES; ++i)
	{
		control->array_type[i]
			= (GtkRadioButton*)gtk_radio_button_new_with_label_from_widget
				(control->array_type[0], array_label[i]);
		gtk_grid_attach(control->grid_type, GTK_WIDGET(control->array_type[i]),
			0, i, 1, 1);
	}
	control->frame_type = (GtkFrame*)gtk_frame_new(gettext("Type"));
	gtk_container_add
		(GTK_CONTAINER(control->frame_type), GTK_WIDGET(control->grid_type));
	gtk_grid_attach(control->grid, GTK_WIDGET(control->frame_type), 0, 0, 2, 1);
	control->label_channel = (GtkLabel*)gtk_label_new(gettext("Channel"));
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->label_channel), 0, 1, 1, 1);
	control->combo_channel
		= jbw_combo_box_new_with_strings(channel_name, nchannels);
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->combo_channel), 1, 1, 1, 1);
	control->label_section = (GtkLabel*)gtk_label_new(gettext("Cross section"));
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->label_section), 0, 2, 1, 1);
	control->combo_section
		= jbw_combo_box_new_with_strings(section_name[0], nsections[0]);
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->combo_section), 1, 2, 1, 1);
	control->label_parameter
		= (GtkLabel*)gtk_label_new(gettext("Parameter value"));
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->label_parameter), 0, 3, 1, 1);
	control->entry_parameter
		= (GtkSpinButton*)gtk_spin_button_new_with_range(-1e6, 1e6, 1e-6);
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->entry_parameter), 1, 3, 1, 1);
	control->label_time = (GtkLabel*)gtk_label_new(gettext("Integration time"));
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->label_time), 0, 4, 1, 1);
	control->entry_time
		= (GtkSpinButton*)gtk_spin_button_new_with_range(0, 1e6, 1e-3);
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->entry_time), 1, 4, 1, 1);
	control->label_tolerance
		= (GtkLabel*)gtk_label_new(gettext("Tolerance"));
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->label_tolerance), 0, 5, 1, 1);
	control->entry_tolerance
		= (GtkSpinButton*)gtk_spin_button_new_with_range(-1e4, 1e4, 1e-6);
	gtk_grid_attach
		(control->grid, GTK_WIDGET(control->entry_tolerance), 1, 5, 1, 1);
	control->frame = (GtkFrame*)gtk_frame_new(gettext("Control"));
	gtk_container_add(GTK_CONTAINER(control->frame), GTK_WIDGET(control->grid));
	g_signal_connect_swapped(control->combo_channel, "changed",
		(void(*))&editor_control_update, control);
	#if DEBUG_EDITOR_CONTROL_NEW
		fprintf(stderr, "editor_control_new: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_update(EditorCrossSection *editor)
 * \brief Function to update the view of a cross section editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_update(EditorCrossSection *editor)
{
	int i;
	#if DEBUG_EDITOR_CROSS_SECTION_UPDATE
		fprintf(stderr, "editor_cross_section_update: start\n");
	#endif
	editor_control_update(editor->control);
	i = jbw_array_radio_buttons_get_active(editor->array_type);
	if (i) gtk_widget_show(GTK_WIDGET(editor->control->frame));
	else gtk_widget_hide(GTK_WIDGET(editor->control->frame));
	gtk_widget_set_sensitive
		(GTK_WIDGET(editor->button_remove), editor->cs->n > 0);
	#if DEBUG_EDITOR_CROSS_SECTION_UPDATE
		fprintf(stderr, "editor_cross_section_update: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_get(EditorCrossSection *editor)
 * \brief Function to get the actual cross section data from the editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_get(EditorCrossSection *editor)
{
	CrossSection *cs = editor->cs;
	#if DEBUG_EDITOR_CROSS_SECTION_GET
		fprintf(stderr, "editor_cross_section_get: start\n");
	#endif
	g_free(cs->name);
	cs->name = g_strdup(gtk_entry_get_text(editor->entry_name));
	if (!cs->name)
	{
		jbw_show_error(message);
		gtk_main_quit();
	}
	cs->x = gtk_spin_button_get_value(editor->entry_x);
	cs->y = gtk_spin_button_get_value(editor->entry_y);
	cs->angle = gtk_spin_button_get_value(editor->entry_angle);
	switch (jbw_array_radio_buttons_get_active(editor->array_type))
	{
	case 0:
		cs->type = 0;
		break;
	default:
		cs->type = 1
			+ jbw_array_radio_buttons_get_active(editor->control->array_type);
	}
	#if DEBUG_EDITOR_CROSS_SECTION_GET
		fprintf(stderr, "editor_cross_section_get: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_open(EditorCrossSection *editor)
 * \brief Function to open a cross section in the editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_open(EditorCrossSection *editor)
{
	CrossSection *cs;
	#if DEBUG_EDITOR_CROSS_SECTION_OPEN
		fprintf(stderr, "editor_cross_section_open: start\n");
	#endif
	cs = editor->cs;
	gtk_entry_set_text(editor->entry_name, cs->name);
	gtk_spin_button_set_value(editor->entry_x, cs->x);
	gtk_spin_button_set_value(editor->entry_y, cs->y);
	gtk_spin_button_set_value(editor->entry_angle, cs->angle);
	#if DEBUG_EDITOR_CROSS_SECTION_OPEN
		fprintf(stderr, "editor_cross_section_open: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_insert_transient(EditorCrossSection *editor)
 * \brief Function to insert a transient section in the actual cross section
 *   data of the editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_insert_transient(EditorCrossSection *editor)
{
	int i;
	TransientSection *ts;
	#if DEBUG_EDITOR_CROSS_SECTION_INSERT_TRANSIENT
		fprintf(stderr, "editor_cross_section_insert_transient: start\n");
	#endif
	i = gtk_combo_box_get_active(GTK_COMBO_BOX(editor->combo_transient));
	ts = editor->cs->ts + i;
	cross_section_insert_transient(editor->cs, ts, i + 1);
	gtk_combo_box_text_insert_text(editor->combo_transient, i, ts->name);
	editor_cross_section_update(editor);
	gtk_notebook_set_current_page(editor->notebook, EDITOR_TRANSIENT_SECTION);
	#if DEBUG_EDITOR_CROSS_SECTION_INSERT_TRANSIENT
		fprintf(stderr, "editor_cross_section_insert_transient: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_remove_transient(EditorCrossSection *editor)
 * \brief Function to remove a transient section in the actual cross section
 *   data of the editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_remove_transient(EditorCrossSection *editor)
{
	int i;
	#if DEBUG_EDITOR_CROSS_SECTION_REMOVE_TRANSIENT
		fprintf(stderr, "editor_cross_section_remove_transient: start\n");
	#endif
	i = gtk_combo_box_get_active(GTK_COMBO_BOX(editor->combo_transient));
	cross_section_remove_transient(editor->cs, i);
	gtk_combo_box_text_remove(editor->combo_transient, i);
	editor_cross_section_update(editor);
	#if DEBUG_EDITOR_CROSS_SECTION_REMOVE_TRANSIENT
		fprintf(stderr, "editor_cross_section_remove_transient: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_draw(EditorCrossSection *editor)
 * \brief Function to draw a cross section in a cross section editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_draw(EditorCrossSection *editor)
{
	int i, j, n, nmax;
	JBDOUBLE k1, k2;
	JBFLOAT *y, *z;
	CrossSection *cs = editor->cs;
	TransientSection *ts = cs->ts;
	JBWGraphic *graphic = editor->graphic;

	#if DEBUG_EDITOR_CROSS_SECTION_DRAW
		fprintf(stderr,"editor_cross_section_draw: start\n");
	#endif

	// Getting extreme values
	nmax = ts->n;
	jbm_varray_maxmin(&ts->sp->y, sizeof(SectionPoint2), nmax, &graphic->xmax,
		&graphic->xmin);
	jbm_varray_maxmin(&ts->sp->z, sizeof(SectionPoint2), nmax, &graphic->ymax,
		&graphic->ymin);
	for (i = 0; ++i <= cs->n;)
	{
		++ts;
		nmax = jbm_max(nmax, ts->n);
		jbm_varray_maxmin(&ts->sp->y, sizeof(SectionPoint2), ts->n, &k2, &k1);
		graphic->xmax = fmaxl(graphic->xmax, k2);
		graphic->xmin = fminl(graphic->xmin, k1);
		jbm_varray_maxmin(&ts->sp->z, sizeof(SectionPoint2), ts->n, &k2, &k1);
		graphic->ymax = fmaxl(graphic->ymax, k2);
		graphic->ymin = fminl(graphic->ymin, k1);
	}

	// Drawing labels
	jbw_graphic_labels(graphic);

	// Drawing lines
	y = (JBFLOAT*)g_malloc((++nmax) * 2 * sizeof(JBFLOAT));
	z = y + nmax;
	for (i = 0, ts = cs->ts; i <= cs->n; ++i, ++ts)
	{
		for (j = n = ts->n + 1; --j >= 0;)
			y[j] = ts->sp[j].y, z[j] = ts->sp[j].z;
		k1 = ((float)i) / (cs->n + 1);
		jbw_graphic_draw_line(graphic, 0., k1, 1. - k1, y, z, n);
	}
	g_free(y);

	// Drawing logo
	jbw_graphic_draw_logo(graphic);

	// End
	#if DEBUG_EDITOR_CROSS_SECTION_DRAW
		fprintf(stderr,"editor_cross_section_draw: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_destroy(EditorCrossSection *editor)
 * \brief Function to destroy a cross section editor.
 * \param editor
 * \brief cross section editor.
 */
void editor_cross_section_destroy(EditorCrossSection *editor)
{
	#if DEBUG_EDITOR_CROSS_SECTION_DESTROY
		fprintf(stderr, "editor_cross_section_destroy: start\n");
	#endif
	editor_transient_section_destroy(editor->editor_transient);
	gtk_widget_destroy(GTK_WIDGET(editor->grid));
	cross_section_delete(editor->cs);
	#if DEBUG_EDITOR_CROSS_SECTION_DESTROY
		fprintf(stderr, "editor_cross_section_destroy: end\n");
	#endif
}

/**
 * \fn void editor_cross_section_new(EditorCrossSection *editor, \
 *   GtkNotebook *notebook, char **channel_name, int nchannels, \
 *   char ***section_name, int *nsections)
 * \brief Function to create a new cross section editor.
 * \param editor
 * \param notebook
 * \brief GtkNotebook to pack the widgets.
 * \param channel_name
 * \brief array of channel names.
 * \param nchannels
 * \brief number of channels.
 * \param section_name
 * \brief array of arrays of cross section names.
 * \param nsections
 * \brief array of number of cross sections.
 */
void editor_cross_section_new(EditorCrossSection *editor, GtkNotebook *notebook,
	char **channel_name, int nchannels, char ***section_name, int *nsections)
{
	int i;
	const char *label_type[2] = {gettext("Normal"), gettext("Control")};
	#if DEBUG_EDITOR_CROSS_SECTION_NEW
		fprintf(stderr, "editor_cross_section_new: start\n");
	#endif
	editor->notebook = notebook;
	editor->grid = (GtkGrid*)gtk_grid_new();
	gtk_notebook_append_page(notebook, GTK_WIDGET(editor->grid),
		gtk_label_new(gettext("Cross section")));
	editor_transient_section_new(editor->editor_transient, notebook);
	editor->label_name = (GtkLabel*)gtk_label_new(gettext("Name"));
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->label_name), 0, 0, 1, 1);
	editor->entry_name = (GtkEntry*)gtk_entry_new();
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->entry_name), 1, 0, 2, 1);
	editor->grid_type = (GtkGrid*)gtk_grid_new();
	editor->array_type[0] = NULL;
	for (i = 0; i < 2; ++i)
	{
		control->array_type[i]
			= (GtkRadioButton*)gtk_radio_button_new_with_label_from_widget
				(control->array_type[0], array_label[i]);
		gtk_grid_attach(control->grid_type, GTK_WIDGET(control->array_type[i]),
			0, i, 1, 1);
		g_signal_connect_swapped(control->array_type[i], "toggled",
			(void(*))&editor_channel_update, editor);
	}
	control->frame_type = (GtkFrame*)gtk_frame_new(gettext("Type"));
	gtk_container_add
		(GTK_CONTAINER(control->frame_type), GTK_WIDGET(control->grid_type));
	gtk_grid_attach(control->grid, GTK_WIDGET(control->frame_type), 0, 1, 3, 1);
	editor->label_x = (GtkLabel*)gtk_label_new("x");
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->label_x), 0, 2, 1, 1);
	editor->entry_x
		= (GtkSpinButton*)gtk_spin_button_new_with_range(-1e6, 1e6, 0.001);
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->entry_x), 1, 2, 2, 1);
	editor->label_y = (GtkLabel*)gtk_label_new("y");
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->label_y), 0, 3, 1, 1);
	editor->entry_y
		= (GtkSpinButton*)gtk_spin_button_new_with_range(-1e6, 1e6, 0.001);
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->entry_y), 1, 3, 2, 1);
	editor->label_angle = (GtkLabel*)gtk_label_new(gettext("Angle"));
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->label_angle), 0, 4, 1, 1);
	editor->entry_angle
		= (GtkSpinButton*)gtk_spin_button_new_with_range(-360., 360., 0.001);
	gtk_grid_attach(editor->grid, GTK_WIDGET(editor->entry_angle), 1, 4, 2, 1);
	editor->button_insert = (GtkButton*)gtk_button_new_with_label
		(gettext("Insert transient section"));
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->button_insert), 0, 5, 1, 1);
	g_signal_connect_swapped(editor->button_insert, "clicked",
		(void(*))&editor_cross_section_insert_transient, editor);
	editor->button_remove = (GtkButton*)gtk_button_new_with_label
		(gettext("Remove transient section"));
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->button_remove), 1, 5, 1, 1);
	g_signal_connect_swapped(editor->button_remove, "clicked",
		(void(*))&editor_cross_section_remove_transient, editor);
	editor->button_plot
		= (GtkButton*)gtk_button_new_with_label(gettext("Update plot"));
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->button_plot), 2, 5, 1, 1);
	editor->label_transient
		= (GtkLabel*)gtk_label_new(gettext("Transient section"));
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->label_transient), 0, 6, 1, 1);
	editor->combo_transient = (GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->combo_transient), 1, 6, 2, 1);
	editor_control_new
		(editor->control, channel_name, nchannels, section_name, nsections);
	gtk_grid_attach
		(editor->grid, GTK_WIDGET(editor->control->frame), 0, 7, 3, 1);
	editor->graphic = jbw_graphic_new(NULL, 6, 6, 0, &editor_draw);
	jbw_graphic_set_title(editor->graphic, gettext("Cross section"));
	jbw_graphic_set_logo(editor->graphic, "swigs.png");
	jbw_graphic_set_xlabel(editor->graphic, "y (m)");
	jbw_graphic_set_ylabel(editor->graphic, "z (m)");
	#if DEBUG_EDITOR_CROSS_SECTION_NEW
		fprintf(stderr, "editor_cross_section_new: end\n");
	#endif
}
