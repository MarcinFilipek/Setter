/*
 * tech_exception.h
 *
 *  Created on: 3 gru 2013
 *      Author: sporysz
 */

#ifndef TECH_EXCEPTION_H_
#define TECH_EXCEPTION_H_

#include "exception_codes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __GNUC__
    /**
     * \brief Jeśli kompilowana przy użyciu GCC to definicja funkcji jest opcjonalna.
     * Jeżeli implementację kompilujemy przy uzyciu g++ należy ją opatrzeć dyrektywą extern "C".
     *
     * \param e - kod bledu z pliku exception_codes.h
     */
    extern void __attribute__ ((weak)) throwException(int e);
#else
    /**
     * \brief Jeśli kompilowana przy użyciu kompilatora innego niż GCC, definicja jest konieczna (może być pusta)
     * \param e - kod bledu z pliku exception_codes.h
     */
    extern void throwException(int e);
#endif


#ifdef __cplusplus
}
#endif

#endif /* TECH_EXCEPTION_H_ */
