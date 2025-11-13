#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>     
#include "gestion.h"
#include "calcl_tams.h"

// --- Funciones de escriber en Fichero ---

void gest_escri_fichero(const char *filename, const  char *cabecera, double valor, double valor1, double resultado, int crear_txt){
    
    int existe_file=(access(filename, F_OK) == 0);
    FILE *f = NULL; 

    if(!crear_txt){
    //se quires añadir los valores
    f = fopen(filename, "a");
    
    }else{
    //se quires subre escriber 
    f = fopen(filename, "w");

    }
    if(f == NULL){
        printf("ERROR AL Abrir %s\n", filename);
        return;
    }
    if (crear_txt) {
        if (cabecera != NULL) fprintf(f, "%s", cabecera);
    } else {
        if (!existe_file && cabecera != NULL) fprintf(f, "%s", cabecera);
    }

    fprintf(f, "%f\t%f\t%.6f\n", valor, valor1, resultado);
    
    fclose(f);   
}

// --- Funciones de Test Específico ---
void gest_test_especifico_moles(double vp, double vt, double *resultado_n){

    // Límites realistas de entrada
    if (vp < 0.0 || vp > 5.0) {
        fprintf(stderr, "Error: Vp fuera de rango [0.0, 5.0] V\n");
        *resultado_n = NAN;
        return;
    }
    if (vt < 0.0 || vt > 1000.0) {
        fprintf(stderr, "Error: Vt fuera de rango [0.0, 1000.0] mV\n");
        *resultado_n = NAN;
        return;
    }

    uint8_t tams[3];
    tam_moles(tams);
    float res;

    uint32_t vp_fx = (uint32_t)round( vp * (1<<tams[0]));
    uint32_t vt_fx = (uint32_t)round( vt * (1<<tams[1]));
    uint32_t resultado_n_fx;


    calc_moles_fx(vp_fx, vt_fx, &resultado_n_fx, &res);

    *resultado_n = (double)resultado_n_fx / (double)(1 << tams[2]);


}

void gest_test_especifico_densidad(double p_in, double vt_in, double *resultado_rho){
    
    // Rango realista de presión y voltaje de temperatura
    if (p_in < 0.0 || p_in > 1e6) {
        fprintf(stderr, "Error: Presión fuera de rango [0, 1e6]\n");
        *resultado_rho = NAN;
       return;
    }
    if (vt_in < 0.0 || vt_in > 2000.0) {
        fprintf(stderr, "Error: Vt fuera de rango [0, 2000]\n");
        *resultado_rho = NAN;
        return;
    }

    uint8_t tams_dens[3];
    tam_dens(tams_dens);
    float res;

    uint32_t  p_in_fx = (uint32_t)round( p_in  * (1<<tams_dens[0]));
    uint32_t vt_in_fx = (uint32_t)round( vt_in * (1<<tams_dens[1]));
    uint32_t resultado_rho_fx;

    calc_density_fx(p_in_fx, vt_in_fx, &resultado_rho_fx, &res);

    *resultado_rho = (double)resultado_rho_fx / (double)(1 << tams_dens[2]);


}

void gest_test_especifico_energia(double a, double w, double *resultado_ek){

    // Límites razonables
    if (a < 0.0 || a > 500.0) {
        fprintf(stderr, "Error: Aceleración fuera de rango [0, 500]\n");
        *resultado_ek = NAN;
        return;
    }
    if (w < 0.0 || w > 1e8) {
        fprintf(stderr, "Error: Peso fuera de rango [0, 1e8]\n");
        *resultado_ek = NAN;
        return;
    }

    uint8_t tams_ener[3];
    tam_ener(tams_ener);
    float res;

    uint32_t  a_fx = (uint32_t)round( a * (1<<tams_ener[0]) );
    uint32_t  w_fx = (uint32_t)round( w * (1<<tams_ener[1]));
    uint32_t resultado_ek_fx;

    calc_kinetic_energy_fx(a_fx, w_fx, &resultado_ek_fx, &res);
        *resultado_ek = (double)resultado_ek_fx / (double)(1 << tams_ener[2]);

}



// --- Funciones de Test Automático --- 
void gest_test_auto_moles(const char *filename){

        gchar *command = g_strdup_printf("pytest test_moles.py %s", filename);
        g_print("Fichero seleccionado");
        system(command);
        g_free(command);

       

}

void gest_test_auto_densidad(const char *filename){

        gchar *command = g_strdup_printf("pytest test_dens.py %s", filename);
        g_print("Fichero seleccionado: %s\n", filename);
        system(command);
        g_free(command);


}

void gest_test_auto_energia(const char *filename){

        gchar *command = g_strdup_printf("pytest test_ener.py %s", filename);
        g_print("Fichero seleccionado");
        system(command);
        g_free(command);

}


// --- Funciones de Grabar Fichero ---
void gest_grabar_fichero_moles(double vp, double vt, int crear_txt, int amun_buff){

    uint8_t tams[3];
    tam_moles(tams);
    float res;
    uint32_t vp_fx = round( vp * (1<<tams[0]));
    uint32_t vt_fx = round( vt * (1<<tams[1]));
    uint32_t resultado_n_fx;
    calc_moles_fx(vp_fx, vt_fx, &resultado_n_fx, &res);
    //crear y subrescriber en txt
    //gest_escri_fichero("test_moles_generado.txt","# vp (#)\tvt (#)\tmoles ()\n", vp, vt, res, crear_txt);
    // para probar esta noche
    gest_guardar_valores_en_buf(vp, vt, res, amun_buff);
    gest_buf_flush_to_file("test_moles_generado.txt", "# vp (#)\tvt (#)\tmoles ()\n",crear_txt);
    if(crear_txt){gest_buf_free();}

}

void gest_grabar_fichero_densidad(double p, double vt, int crear_txt, int amun_buff){
    //opracion 
    uint8_t tams_des[3];
    tam_dens(tams_des);
    float res;

    uint32_t  p_in_fx = round( p * (1<<tams_des[0]));
    uint32_t vt_in_fx = round( vt * (1<<tams_des[1]));
    uint32_t resultado_rho_fx;

    calc_density_fx(p_in_fx, vt_in_fx, &resultado_rho_fx, &res);

    //crear y subrescriber en txt
    //gest_escri_fichero("test_generado_densidad.txt","# p (pscal)\tvt (ml)\tdensidad (kg/m^3)\n", p, vt, res, crear_txt);
    
    // para probar esta noche



    gest_guardar_valores_en_buf(p, vt, res, amun_buff);
    gest_buf_flush_to_file("test_generado_densidad.txt", "# p (pscal)\tvt (ml)\tdensidad (kg/m^3)\n", crear_txt);
    if(crear_txt){gest_buf_free();}

    
}

void gest_grabar_fichero_energia(double a, double w, int crear_txt, int amun_buff){

    uint8_t tams_ener[3];
    tam_ener(tams_ener);
    float res;

    uint32_t a_fx  = round(  a * (1<<tams_ener[0]));
    uint32_t w_fx  = round(  w * (1<<tams_ener[1]));
    uint32_t resultado_ek_fx;

    calc_kinetic_energy_fx(a_fx, w_fx, &resultado_ek_fx, &res);

    //crear y subrescriber en txt
    //gest_escri_fichero("test_generado_energia.txt","# A (#)\tW (#)\tEnergía cinética (J)\n", a, w, res, 1);
    gest_guardar_valores_en_buf(a, w, res, amun_buff);
    gest_buf_flush_to_file("test_generado_energia.txt","# A (#)\tW (#)\tEnergía cinética (J)\n", crear_txt);
    if(crear_txt){gest_buf_free();}
   
}

typedef struct {
        double valor_bf;
        double valor1_bf;
        double resultado_bf;
    } data_buffer_t;

  static data_buffer_t *buffer = NULL;
  static size_t count = 0;
  static size_t capacity = 0;

// foncion de guradar los valores para peude generar un txt de multipli valor
void gest_guardar_valores_en_buf(double valor, double valor1, double resultado, int amun_buff) {
    if (amun_buff) {
        if (count >= capacity) {
            size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
            data_buffer_t *tmp = realloc(buffer, new_cap * sizeof(data_buffer_t));
            if (tmp == NULL) {
                printf("Error: no se pudo ampliar el buffer\n");
                return;
            }
            buffer = tmp;
            capacity = new_cap;
        }
        buffer[count].valor_bf     = valor;
        buffer[count].valor1_bf    = valor1;
        buffer[count].resultado_bf = resultado;
        count++;
        return;
    } else {
        if (count == 0) {
            if (capacity == 0) {
                data_buffer_t *tmp = realloc(buffer, 8 * sizeof(data_buffer_t));
                if (tmp == NULL) {
                    printf("Error: no se pudo reservar el buffer\n");
                    return;
                }
                buffer = tmp;
                capacity = 8;
            }
            buffer[0].valor_bf     = valor;
            buffer[0].valor1_bf    = valor1;
            buffer[0].resultado_bf = resultado;
            count = 1;
        } else {
            buffer[count - 1].valor_bf     = valor;
            buffer[count - 1].valor1_bf    = valor1;
            buffer[count - 1].resultado_bf = resultado;
        }
        return;
    }
}


/// test
void gest_buf_flush_to_file(const char *filename, const char *cabecera, int crear_txt) {
    if (filename == NULL) return;

    FILE *f = NULL;
    if (crear_txt) {
        f = fopen(filename, "w");
    } else {
        f = fopen(filename, "a");
    }
    if (f == NULL) {
        printf("ERROR AL abrir %s\n", filename);
        return;
    }
    if (crear_txt) {
        if (cabecera != NULL) fprintf(f, "%s", cabecera);
    } else {
        long pos = ftell(f);
        if (pos == 0 && cabecera != NULL) fprintf(f, "%s", cabecera);
        fseek(f, 0, SEEK_END);
    }

    for (size_t i = 0; i < count; ++i) {
        fprintf(f, "%f\t%f\t%.6f\n",
                buffer[i].valor_bf,
                buffer[i].valor1_bf,
                buffer[i].resultado_bf);
    }

    fclose(f);

    /* vaciar buffer (mantener capacidad) */
    count = 0;
}
void gest_buf_free(void) {
    free(buffer);
    buffer = NULL;
    count = 0;
    capacity = 0;
}