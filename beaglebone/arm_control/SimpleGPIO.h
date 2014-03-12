/*
 * SimpleGPIO.h
 *
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.eeng.dcu.ie/~molloyd/
 *
 * Based on Software by RidgeRun
 * Copyright (c) 2011, RidgeRun
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the RidgeRun.
 * 4. Neither the name of the RidgeRun nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY RIDGERUN ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RIDGERUN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SIMPLEGPIO_H_
#define SIMPLEGPIO_H_

 /****************************************************************
 * Constants
 ****************************************************************/

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (1) /* 1 ms */
#define MAX_BUF 64
#define SYSFS_OMAP_MUX_DIR "/sys/kernel/debug/omap_mux/"

typedef enum {
	INPUT_PIN=0,
	OUTPUT_PIN=1
} PIN_DIRECTION;

typedef enum {
	LOW=0,
	HIGH=1
}PIN_VALUE;

typedef struct {
   char num;            /**< gpio number */
   int fd_value;        /**< file desciptor of /sys/class/gpio/gpio<num>/value */
   int fd_direction;    /**< file desciptor of /sys/class/gpio/gpio<num>/direction */
   int fd_edge;         /**< file desciptor of /sys/class/gpio/gpio<num>/edge *///damien
} gpio_t;

/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export( gpio_t* gpio, char ngpio);
int gpio_unexport(gpio_t* gpio);
int gpio_set_dir(gpio_t* gpio, PIN_DIRECTION out_flag);
int gpio_set_value(gpio_t* gpio, PIN_VALUE value);
int gpio_get_value(gpio_t* gpio, unsigned int *value);

//int gpio_set_edge(unsigned int gpio, char *edge);
int gpio_set_edge(gpio_t* gpio, char *edge);//damien
int gpio_fd_open(unsigned int gpio);
int gpio_fd_open_g(gpio_t* gpio);//damien
int gpio_fd_close(int fd);
int gpio_omap_mux_setup(const char *omap_pin0_name, const char *mode);

#endif /* SIMPLEGPIO_H_ */
