#ifndef CALCL_TAMS_H
#define CALCL_TAMS_H

#include <stdint.h>

void tam_moles(uint8_t * tams);
void calc_moles_fx(uint32_t Vp_fx,uint32_t Vt_fx,uint32_t *resultado, float *res_float);

void tam_dens(uint8_t * tams);
void calc_density_fx(uint32_t dato_P, uint32_t datoVt,uint32_t *resultado, float *res_float);


void tam_ener(uint8_t * tams);
void calc_kinetic_energy_fx(uint32_t dato_A, uint32_t dato_W,uint32_t *resultado, float *res_float) ;

#endif
