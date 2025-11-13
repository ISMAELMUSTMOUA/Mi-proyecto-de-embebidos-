#ifndef GESTION_H
#define GESTION_H

//#include "calcl_tams.h"
#include <gtk/gtk.h>
#include <stdint.h>

/*
 PROTOTIPOS DE CAPA 2 (Gestión)
*/

// --- Funciones de Test Específico ---
void gest_test_especifico_moles(double vp, double vt, double *resultado_n);
void gest_test_especifico_densidad(double p_in, double vt_in, double *resultado_rho);
void gest_test_especifico_energia(double a, double w, double *resultado_ek);

// --- Funciones de Test Automático ---
void gest_test_auto_moles(const char *filename);
void gest_test_auto_densidad(const char *filename);
void gest_test_auto_energia(const char *filename);

// --- Funciones de Grabar Fichero ---
void gest_grabar_fichero_moles(double vp, double vt, int crear_txt, int amun_buff);
void gest_grabar_fichero_densidad(double p, double vt, int crear_txt, int amun_buff);
void gest_grabar_fichero_energia(double a, double w, int crear_txt, int amun_buff);

// --- Funcione de escriber en Fichero ---
void gest_escri_fichero(const char *filename, const char *cabecera, double valor, double valor1, double resultado, int crear_txt);

// --- Funcione de guradar los valores para peuder guardar un fichero multipli valor ---
void gest_guardar_valores_en_buf(double valor, double valor1, double resultado, int amun_buff);

// --- liberar el buffer
void gest_buf_free(void);

// funcione de guradra el buffer que tengo en un txt
void gest_buf_flush_to_file(const char *filename, const char *cabecera, int crear_txt);

#endif // GESTION_H