#ifndef ALGORITHM_H_
#define ALGORITHM_H_
#include "MAX30102.h"

#include "stdint.h"

#define true 1
#define false 0
#define FS MAX30102_SAMPLES_PER_SECOND
#define BUFFER_SIZE  (MAX30102_BUFFER_LENGTH-MAX30102_SAMPLES_PER_SECOND)
#define HR_FIFO_SIZE 7
#define MA4_SIZE  4 // DO NOT CHANGE
#define HAMMING_SIZE  5// DO NOT CHANGE
#define min(x,y) ((x) < (y) ? (x) : (y))

void maxim_heart_rate_and_oxygen_saturation(volatile uint32_t *pun_ir_buffer, volatile uint32_t *pun_red_buffer, int32_t n_buffer_length, uint16_t un_offset, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t  *pch_hr_valid);
void maxim_find_peaks( int32_t *pn_locs, int32_t *pn_npks,  int32_t *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num );
void maxim_peaks_above_min_height( int32_t *pn_locs, int32_t *pn_npks,  int32_t *pn_x, int32_t n_size, int32_t n_min_height );
void maxim_remove_close_peaks( int32_t *pn_locs, int32_t *pn_npks,   int32_t  *pn_x, int32_t n_min_distance );
void maxim_sort_ascend( int32_t *pn_x, int32_t n_size );
void maxim_sort_indices_descend(  int32_t  *pn_x, int32_t *pn_indx, int32_t n_size);

#endif /* ALGORITHM_H_ */
