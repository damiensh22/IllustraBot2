
#ifndef __MAIN_H__
#define __MAIN_H__

#include <pthread.h>
#include "easydriver.h"

#define NB_MOTORS 2

/** define pins for every motor */
char motor_pins[NB_MOTORS][2] = {
   /* {STEP, DIR} */
   {45, 44}, /* motor0: P8_11, P8_12 */
   {23, 26}, /* motor1; P8_13, P8_14 */
};
#define IDX_STEP 0
#define IDX_DIR  1

/** Motors parameters */
// steps per revolution
#define STEPS_PR 1600
#define MIN_SPEED 500
#define MAX_SPEED 40000

/**
 * Motor structure
 */
typedef struct {
   char name[10];               /**< Motor name */
   easydriver_t ed;             /**< driver structure for control data */
   int steps;                   /**< number of steps to move each time thread is unlocked */

   pthread_t thread;            /**< the motor control thread */
   pthread_mutex_t mutex;       /**< mutex to access this structure */
   pthread_cond_t cond;         /**< blocking condition of the thread */
} motor_t;


#endif /* __MAIN_H__ */