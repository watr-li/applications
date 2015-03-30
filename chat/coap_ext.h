/*
 * Copyright (C) 2015 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief       extensions to stock microcoap (might become PRs)
 *
 * @author      Lotte Steenbrink <lotte.steenbrink@haw-hamburg.de>
 *
 * @}
 */

#ifndef COAP_EXT_H
#define COAP_EXT_H

#include <stdio.h>
#include <string.h>
#include <coap.h>

/**
 * @brief   Build a PUT request.
 *          Only supports 0=text/plain payload.
 *
 * @param[in] buf      The buffer into which the resulting CoAP packet will be written.
 * @param[in] buflen   Pointer to the length of buf. After successful execution
 *                     of the function, the value buflen points to will have changed to the
 *                     length of the new data in buf.
 * @param[in] payload  The payload of the PUT request to be built.
 * @param[in] path     The resource path of the PUT request to be built.
 *
 * @return                  0 on success
 * @return                 -1 on error
 */

int coap_ext_build_PUT(uint8_t *buf, size_t *buflen, char *payload, coap_endpoint_path_t *path);

#endif /* COAP_EXT_H */
