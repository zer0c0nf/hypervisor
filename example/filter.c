/*****************************************************************************
* Model: model.qm
* File:  port_filter/filter.c
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${port_filter::filter.c} .................................................*/
#include "qpc.h"
#include "filter.h"

#define BSP_PORT_CHECK() (0)

enum {
	TIMEOUT_SIG = Q_USER_SIG
};

/*${port_filter::filter} ...................................................*/
typedef struct {
/* protected: */
    QActive super;

/* private: */
    QTimeEvt timer;
    uint32_t count;
} filter;

/* protected: */
static QState filter_initial(filter * const me, QEvt const * const e);
static QState filter_PORT_OFF(filter * const me, QEvt const * const e);
static QState filter_PORT_ON_C(filter * const me, QEvt const * const e);
static QState filter_PORT_ON(filter * const me, QEvt const * const e);
static QState filter_PORT_OFF_C(filter * const me, QEvt const * const e);


static filter l_filter;

QActive * const AO_filter = &l_filter.super;

/*${port_filter::filter_ctor} ..............................................*/
void filter_ctor(void) {
    filter * const me = &l_filter;
    QActive_ctor(&me->super, Q_STATE_CAST(&filter_initial));
    QTimeEvt_ctorX(&me->timer, &me->super, TIMEOUT_SIG, 0U);
}
/*${port_filter::filter} ...................................................*/
/*${port_filter::filter::SM} ...............................................*/
static QState filter_initial(filter * const me, QEvt const * const e) {
    /* ${port_filter::filter::SM::initial} */
    me->count = 0;
    QTimeEvt_armX(&me->timer, 0, 10);
    return Q_TRAN(&filter_PORT_OFF);
}
/*${port_filter::filter::SM::PORT_OFF} .....................................*/
static QState filter_PORT_OFF(filter * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${port_filter::filter::SM::PORT_OFF::TIMEOUT} */
        case TIMEOUT_SIG: {
            /* ${port_filter::filter::SM::PORT_OFF::TIMEOUT::[(1==BSP_PORT_CHECK())]} */
            if ((1 == BSP_PORT_CHECK())) {
                status_ = Q_TRAN(&filter_PORT_ON_C);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${port_filter::filter::SM::PORT_ON_C} ....................................*/
static QState filter_PORT_ON_C(filter * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${port_filter::filter::SM::PORT_ON_C::TIMEOUT} */
        case TIMEOUT_SIG: {
            me->count++;
            /* ${port_filter::filter::SM::PORT_ON_C::TIMEOUT::[(me->count<10)]} */
            if ((me->count < 10)) {
                /* ${port_filter::filter::SM::PORT_ON_C::TIMEOUT::[(me->count<10)]::[(0==BSP_PORT_CHECK())]} */
                if ((0 == BSP_PORT_CHECK())) {
                    me->count = 0;
                    status_ = Q_TRAN(&filter_PORT_OFF);
                }
                else {
                    status_ = Q_UNHANDLED();
                }
            }
            /* ${port_filter::filter::SM::PORT_ON_C::TIMEOUT::[else]} */
            else {
                me->count = 0;
                status_ = Q_TRAN(&filter_PORT_ON);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${port_filter::filter::SM::PORT_ON} ......................................*/
static QState filter_PORT_ON(filter * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${port_filter::filter::SM::PORT_ON::TIMEOUT} */
        case TIMEOUT_SIG: {
            /* ${port_filter::filter::SM::PORT_ON::TIMEOUT::[(0==BSP_PORT_CHECK())]} */
            if ((0 == BSP_PORT_CHECK())) {
                status_ = Q_TRAN(&filter_PORT_OFF_C);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${port_filter::filter::SM::PORT_OFF_C} ...................................*/
static QState filter_PORT_OFF_C(filter * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${port_filter::filter::SM::PORT_OFF_C::TIMEOUT} */
        case TIMEOUT_SIG: {
            me->count++;
            /* ${port_filter::filter::SM::PORT_OFF_C::TIMEOUT::[(me->count<10)]} */
            if ((me->count < 10)) {
                /* ${port_filter::filter::SM::PORT_OFF_C::TIMEOUT::[(me->count<10)]::[(1==BSP_PORT_CHECK())]} */
                if ((1 == BSP_PORT_CHECK())) {
                    me->count = 0;
                    status_ = Q_TRAN(&filter_PORT_ON);
                }
                else {
                    status_ = Q_UNHANDLED();
                }
            }
            /* ${port_filter::filter::SM::PORT_OFF_C::TIMEOUT::[else]} */
            else {
                status_ = Q_TRAN(&filter_PORT_OFF);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
