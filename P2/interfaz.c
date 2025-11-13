#include <stdlib.h> 
#include <stdio.h>
#include "gestion.h"

// Declaraciones de callbacks
void on_crear_moles_fichero_clicked(GtkWidget *widget, gpointer data);
void on_anadir_moles_fichero_clicked(GtkWidget *widget, gpointer data);
void on_crear_dens_fichero_clicked(GtkWidget *widget, gpointer data);
void on_anadir_dens_fichero_clicked(GtkWidget *widget, gpointer data);
void on_crear_ener_fichero_clicked(GtkWidget *widget, gpointer data);
void on_anadir_ener_fichero_clicked(GtkWidget *widget, gpointer data);


// Botones moles
void on_test_clicked(GtkWidget *widget, gpointer data) {

    g_print("Botón presionado: %s\n", (char*)data);

}

void on_test_auto_moles_clicked(GtkWidget *widget, gpointer data) {
    
    GtkWidget *dialogo;
    GtkWindow *parent_win = GTK_WINDOW(gtk_widget_get_toplevel(widget));
    g_print("Test automático de Moles iniciado\n");
    // Argumentos: Título ventana de dialogo, clase padre, acción del diálogo (abrir, guardar, elegir, mirar FileChooserAction), nombre de botón, ID de respuesta asociada a botón, replicable, acaba en Null
    dialogo = gtk_file_chooser_dialog_new("Selecciona el fichero", parent_win, GTK_FILE_CHOOSER_ACTION_OPEN, "Seleccionar", GTK_RESPONSE_ACCEPT, NULL);
    //Ejecutar el diálogo y estudiar la respesta del dialógo  
    if(gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialogo));
        //AQUI GESTIONAR FICHERO
        gest_test_auto_moles(filename);
        g_free(filename);

    } else {
        g_print("Operación cancelada");
    }

    gtk_widget_destroy(dialogo);
}


void on_test_esp_moles_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *vp_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
        if (vp_text && vt_text && vp_text[0] && vt_text[0]) {
            double vp = atof(vp_text);
            double vt = atof(vt_text);
            double res;
            g_print("Test específico de Moles iniciado\n");
            gest_test_especifico_moles(vp, vt, &res);
            gest_escri_fichero("test_esp_moles_generado.txt","# vp (#)\tvt (#)\tmoles ()\n", vp, vt, res, 1);
            system("python3 testeo.py test_esp_moles_generado.txt");
        } else {
        printf("Ingresa valores válidos para Vp y Vt\n");
        }

}

void on_gen_moles_clicked(GtkWidget *widget, gpointer data) {

    GtkWidget *win_gen = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win_gen), "Generar fichero de Moles");
    g_signal_connect(win_gen, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_default_size(GTK_WINDOW(win_gen), 300, 200);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(win_gen), grid);

    GtkWidget *label_vp = gtk_label_new("Vp (V):");
    GtkWidget *entry_vp = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vp), "Ej: 2.35");

    GtkWidget *label_vt = gtk_label_new("Vt (mV):");
    GtkWidget *entry_vt = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vt), "Ej: 298.0");

    GtkWidget *btn_crear = gtk_button_new_with_label("Crear fichero");
    GtkWidget *btn_anadir = gtk_button_new_with_label("Añadir al fichero");

    GtkWidget **entries = g_new(GtkWidget*, 2);
    entries[0] = entry_vp;
    entries[1] = entry_vt;

    g_signal_connect(btn_crear, "clicked", G_CALLBACK(on_crear_moles_fichero_clicked), entries);
    g_signal_connect(btn_anadir, "clicked", G_CALLBACK(on_anadir_moles_fichero_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), label_vp,   0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vp,   1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_vt,   0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vt,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_crear,  0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_anadir, 1, 2, 1, 1);

    gtk_widget_show_all(win_gen);

}
void on_crear_moles_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *vp_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (vp_text && vt_text && vp_text[0] && vt_text[0]) {
        double vp = atof(vp_text);
        double vt = atof(vt_text); 
        gest_grabar_fichero_moles(vp,vt, 1, 0);
    }
    else {
        printf("Ingresa valores válidos para Vp y Vt\n");
    }
}

void on_anadir_moles_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *vp_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (vp_text && vt_text && vp_text[0] && vt_text[0]) {
        double vp = atof(vp_text);
        double vt = atof(vt_text); 
        gest_grabar_fichero_moles(vp,vt, 0, 1);
    }
    else {
        printf("Ingresa valores válidos para Vp y Vt\n");
    }
}
//Botones densidad
void on_test_auto_densidad_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialogo;
    GtkWindow *parent_win = GTK_WINDOW(gtk_widget_get_toplevel(widget));
    g_print("Test automático de Densidad iniciado\n");
    // Argumentos: Título ventana de dialogo, clase padre, acción del diálogo (abrir, guardar, elegir, mirar FileChooserAction), nombre de botón, ID de respuesta asociada a botón, replicable, acaba en Null
    dialogo = gtk_file_chooser_dialog_new("Selecciona el fichero", parent_win, GTK_FILE_CHOOSER_ACTION_OPEN, "Seleccionar", GTK_RESPONSE_ACCEPT, NULL);
    //Ejecutar el diálogo y estudiar la respesta del dialógo  
    if(gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialogo));
        //AQUI GESTIONAR FICHERO
        gest_test_auto_densidad(filename);
        g_free(filename);
        
    } else {
        g_print("Operación cancelada\n");
    }

    gtk_widget_destroy(dialogo);

}


void on_test_esp_densidad_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *p_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (p_text && vt_text && p_text[0] && vt_text[0]) {
        double p = atof(p_text);
        double vt = atof(vt_text);
        double res;
        g_print("Test específico de Densidad iniciado\n");
        gest_test_especifico_densidad(p, vt, &res);
        gest_escri_fichero("test_esp_dens_generado.txt","# p (#)\tvt (#)\tdensidad ()\n", p, vt, res, 1);
        system("python3 testeo_dens.py test_esp_dens_generado.txt");
     }  
    else {
        printf("Ingresa valores válidos para P y Vt\n");
    }
}


void on_gen_densidad_clicked(GtkWidget *widget, gpointer data) {

    GtkWidget *win_gen = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win_gen), "Generar fichero de Densidad");
    g_signal_connect(win_gen, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_default_size(GTK_WINDOW(win_gen), 300, 200);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(win_gen), grid);

    GtkWidget *label_p = gtk_label_new("P (#):");
    GtkWidget *entry_p = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_p), "Ej: 820000");

    GtkWidget *label_vt = gtk_label_new("Vt (mV):");
    GtkWidget *entry_vt = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vt), "Ej: 750.0");

    GtkWidget *btn_crear = gtk_button_new_with_label("Crear fichero");
    GtkWidget *btn_anadir = gtk_button_new_with_label("Añadir al fichero");

    GtkWidget **entries = g_new(GtkWidget*, 2);
    entries[0] = entry_p;
    entries[1] = entry_vt;

    g_signal_connect(btn_crear, "clicked", G_CALLBACK(on_crear_dens_fichero_clicked), entries);
    g_signal_connect(btn_anadir, "clicked", G_CALLBACK(on_anadir_dens_fichero_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), label_p,   0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_p,   1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_vt,  0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vt,  1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_crear,  0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_anadir, 1, 2, 1, 1);

    gtk_widget_show_all(win_gen);

}
void on_crear_dens_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *p_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (p_text && vt_text && p_text[0] && vt_text[0]) {
        double p = atof(p_text);
        double vt = atof(vt_text);
        gest_grabar_fichero_densidad(p, vt, 1, 0);
    }   
    else {
        printf("Ingresa valores válidos para P y Vt\n");
    }
}
void on_anadir_dens_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *p_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *vt_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (p_text && vt_text && p_text[0] && vt_text[0]) {
        double p = atof(p_text);
        double vt = atof(vt_text);
        gest_grabar_fichero_densidad(p, vt, 0, 1);

    }
    else {
        printf("Ingresa valores válidos para P y Vt\n");
    }
}


//Botones de la energía cinética
void on_test_auto_energia_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialogo;
    GtkWindow *parent_win = GTK_WINDOW(gtk_widget_get_toplevel(widget));

    g_print("Test automático de Energía Cinética iniciado\n");
    // Argumentos: Título ventana de dialogo, clase padre, acción del diálogo (abrir, guardar, elegir, mirar FileChooserAction), nombre de botón, ID de respuesta asociada a botón, replicable, acaba en Null
    dialogo = gtk_file_chooser_dialog_new("Selecciona el fichero", parent_win, GTK_FILE_CHOOSER_ACTION_OPEN, "Seleccionar", GTK_RESPONSE_ACCEPT, NULL);
    //Ejecutar el diálogo y estudiar la respesta del dialógo  
    if(gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialogo));
        //AQUI GESTIONAR FICHERO
        gest_test_auto_energia(filename);
        g_free(filename);
       
    } else {
        g_print("Operación cancelada");
    }

    gtk_widget_destroy(dialogo);

}


void on_test_esp_energia_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *a_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *w_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (a_text && w_text && a_text[0] && w_text[0]) {
        double a = atof(a_text);
        double w = atof(w_text);
        double res;
        gest_test_especifico_energia(a, w, &res);
        gest_escri_fichero("test_esp_ener_generado.txt","# A (#)\tW (#)\tenergia ()\n", a, w, res, 1);
        system("python3 testeo_ener.py test_esp_ener_generado.txt");
        g_print("Test específico de Energía Cinética iniciado\n");
    }
    else {
        printf("Ingresa valores válidos para A y W\n");
    }
}


void on_gen_energia_clicked(GtkWidget *widget, gpointer data) {

    GtkWidget *win_gen = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win_gen), "Generar fichero de Energía Cinética");
    g_signal_connect(win_gen, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_default_size(GTK_WINDOW(win_gen), 300, 200);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(win_gen), grid);

    GtkWidget *label_a = gtk_label_new("A (#):");
    GtkWidget *entry_a = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_a), "Ej: 256");

    GtkWidget *label_w = gtk_label_new("W (#):");
    GtkWidget *entry_w = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_w), "Ej: 8500000");

    GtkWidget *btn_crear = gtk_button_new_with_label("Crear fichero");
    GtkWidget *btn_anadir = gtk_button_new_with_label("Añadir al fichero");

    GtkWidget **entries = g_new(GtkWidget*, 2);
    entries[0] = entry_a;
    entries[1] = entry_w;

    g_signal_connect(btn_crear, "clicked", G_CALLBACK(on_crear_ener_fichero_clicked), entries);
    g_signal_connect(btn_anadir, "clicked", G_CALLBACK(on_anadir_ener_fichero_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), label_a,   0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_a,   1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_w,   0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_w,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_crear,  0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_anadir, 1, 2, 1, 1);

    gtk_widget_show_all(win_gen);

}

void on_crear_ener_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *a_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *w_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (a_text && w_text && a_text[0] && w_text[0]) {
        double a = atof(a_text);
        double w = atof(w_text);
        gest_grabar_fichero_energia(a,w, 1,0);
    }
    else {
        printf("Ingresa valores válidos para A y W\n");
    }
}

void on_anadir_ener_fichero_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *a_text = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *w_text = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    if (a_text && w_text && a_text[0] && w_text[0]) {
        double a = atof(a_text);
        double w = atof(w_text);
        gest_grabar_fichero_energia(a,w, 0, 1);
    }
    else {
        printf("Ingresa valores válidos para A y W\n");
    }
}



int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    //GtkWidget *label, *button1, *button2, *entry;
    
    gtk_init(&argc, &argv);

    // Ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculo Punto Fijo");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    // Grid
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Moles
    GtkWidget *label_moles = gtk_label_new("Moles");
    gtk_widget_set_halign(label_moles, GTK_ALIGN_START);
    
    GtkWidget *btn_test_auto = gtk_button_new_with_label("Test automático");
    g_signal_connect(btn_test_auto, "clicked", G_CALLBACK(on_test_auto_moles_clicked), "Test Auto Moles");
    
    GtkWidget *btn_test_esp = gtk_button_new_with_label("Test Específico Moles");

    GtkWidget *label_vp = gtk_label_new("Vp (V):");
    GtkWidget *entry_vp = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vp), "Ej: 2.35");
    
    GtkWidget *label_vt = gtk_label_new("Vt (mV):");
    GtkWidget *entry_vt = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vt), "Ej: 298.0");

    GtkWidget *btn_gen = gtk_button_new_with_label("Generar Fichero");
    GtkWidget **entries_moles = g_new(GtkWidget*, 2);
        entries_moles[0] = entry_vp;
        entries_moles[1] = entry_vt;
    g_signal_connect(btn_test_esp, "clicked", G_CALLBACK(on_test_esp_moles_clicked), entries_moles);
    g_signal_connect(btn_gen, "clicked", G_CALLBACK(on_gen_moles_clicked), entries_moles);
    


    gtk_grid_attach(GTK_GRID(grid), label_moles,    0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_auto,  1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_esp,   2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_vp,       3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vp,       4, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_gen,        0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_vt,       3, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vt,       4, 1, 1, 1);

    // Separador 1
    GtkWidget *separator1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_grid_attach(GTK_GRID(grid), separator1, 0, 2, 5, 1);

    // Densidad
    GtkWidget *label_densidad = gtk_label_new("Densidad");
    gtk_widget_set_halign(label_densidad, GTK_ALIGN_START);
    
    GtkWidget *btn_test_auto2 = gtk_button_new_with_label("Test automático");
    g_signal_connect(btn_test_auto2, "clicked", G_CALLBACK(on_test_auto_densidad_clicked), "Test Auto Densidad");
    
    GtkWidget *btn_test_esp2 = gtk_button_new_with_label("Test Específico Densidad");    
    GtkWidget *label_p = gtk_label_new("P (#):");
    GtkWidget *entry_p = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_p), "Ej: 820000");
    
    GtkWidget *label_vt2 = gtk_label_new("Vt (mV):");
    GtkWidget *entry_vt2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_vt2), "Ej: 750.0");

    GtkWidget *btn_gen2 = gtk_button_new_with_label("Generar Fichero");
    GtkWidget **entries_densidad = g_new(GtkWidget*, 2);
        entries_densidad[0] = entry_p;
        entries_densidad[1] = entry_vt2;
    g_signal_connect(btn_gen2, "clicked", G_CALLBACK(on_gen_densidad_clicked), entries_densidad);
        g_signal_connect(btn_test_esp2, "clicked", G_CALLBACK(on_test_esp_densidad_clicked), entries_densidad);

    gtk_grid_attach(GTK_GRID(grid), label_densidad,    0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_auto2,  1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_esp2,   2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_p,       3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_p,       4, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_gen2,        0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_vt2,       3, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_vt2,       4, 4, 1, 1);

    // Separador 2
    GtkWidget *separator2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_grid_attach(GTK_GRID(grid), separator2, 0, 5, 5, 1);

    // Energía cinética
    GtkWidget *label_energia = gtk_label_new("E. Cinética");
    gtk_widget_set_halign(label_energia, GTK_ALIGN_START);
    
    GtkWidget *btn_test_auto3 = gtk_button_new_with_label("Test automático");
    g_signal_connect(btn_test_auto3, "clicked", G_CALLBACK(on_test_auto_energia_clicked), "Test Auto E. Cinética");
    
    GtkWidget *btn_test_esp3 = gtk_button_new_with_label("Test Específico E. Cinética");
   
    GtkWidget *label_a = gtk_label_new("A (#):");
    GtkWidget *entry_a = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_a), "Ej: 256");
    
    GtkWidget *label_w = gtk_label_new("W (#):");
    GtkWidget *entry_w = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_w), "Ej: 8500000");

    GtkWidget *btn_gen3 = gtk_button_new_with_label("Generar Fichero");
        GtkWidget **entries_energia = g_new(GtkWidget*, 2);
        entries_energia[0] = entry_a;
        entries_energia[1] = entry_w;
    
    g_signal_connect(btn_test_esp3, "clicked", G_CALLBACK(on_test_esp_energia_clicked), entries_energia);
    g_signal_connect(btn_gen3, "clicked", G_CALLBACK(on_gen_energia_clicked), entries_energia);

    gtk_grid_attach(GTK_GRID(grid), label_energia,    0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_auto3,  1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_test_esp3,   2, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_a,       3, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_a,       4, 6, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_gen3,        0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_w,       3, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_w,       4, 7, 1, 1);

    gtk_widget_show_all(window);

    g_print("Interfaz iniciada\n");
    
    gtk_main();
    return 0;
}