/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Copyright (C) 2008 - 2009 Novell, Inc.
 * Copyright (C) 2009 - 2011 Red Hat, Inc.
 * Copyright (C) 2011 Google, Inc.
 */

#ifndef MM_BROADBAND_MODEM_H
#define MM_BROADBAND_MODEM_H

#include <glib.h>
#include <glib-object.h>

#include <ModemManager.h>

#include "mm-base-modem.h"

#define MM_TYPE_BROADBAND_MODEM            (mm_broadband_modem_get_type ())
#define MM_BROADBAND_MODEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_BROADBAND_MODEM, MMBroadbandModem))
#define MM_BROADBAND_MODEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  MM_TYPE_BROADBAND_MODEM, MMBroadbandModemClass))
#define MM_IS_BROADBAND_MODEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_BROADBAND_MODEM))
#define MM_IS_BROADBAND_MODEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  MM_TYPE_BROADBAND_MODEM))
#define MM_BROADBAND_MODEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MM_TYPE_BROADBAND_MODEM, MMBroadbandModemClass))

typedef struct _MMBroadbandModem MMBroadbandModem;
typedef struct _MMBroadbandModemClass MMBroadbandModemClass;
typedef struct _MMBroadbandModemPrivate MMBroadbandModemPrivate;

struct _MMBroadbandModem {
    MMBaseModem parent;
    MMBroadbandModemPrivate *priv;
};

struct _MMBroadbandModemClass {
    MMBaseModemClass parent;

    /* Setup ports, e.g. to setup unsolicited response handlers.
     * Plugins which need specific setups should chain up parent's port setup
     * as well. */
    void (* setup_ports) (MMBroadbandModem *self);

    /* First and last initialization steps.
     * Actually, this is not really the first step, setup_ports() is */
    void     (* initialization_started)        (MMBroadbandModem *self,
                                                GAsyncReadyCallback callback,
                                                gpointer user_data);
    gpointer (* initialization_started_finish) (MMBroadbandModem *self,
                                                GAsyncResult *res,
                                                GError **error);
    gboolean (* initialization_stopped)        (MMBroadbandModem *self,
                                                gpointer started_context,
                                                GError **error);

    /* First enabling step */
    void     (* enabling_started)        (MMBroadbandModem *self,
                                          GAsyncReadyCallback callback,
                                          gpointer user_data);
    gboolean (* enabling_started_finish) (MMBroadbandModem *self,
                                          GAsyncResult *res,
                                          GError **error);

    /* Last disabling step */
    gboolean (* disabling_stopped) (MMBroadbandModem *self,
                                    GError **error);
};

GType mm_broadband_modem_get_type (void);

MMBroadbandModem *mm_broadband_modem_new (const gchar *device,
                                          const gchar **drivers,
                                          const gchar *plugin,
                                          guint16 vendor_id,
                                          guint16 product_id);

/* Convert the given string, which comes in the charset currently set in the
 * modem, to UTF-8. Given in the API so that subclasses can also use it directly.
 */
gchar *mm_broadband_modem_take_and_convert_to_utf8 (MMBroadbandModem *self,
                                                    gchar *str);

/* Convert the given string, which comes in UTF-8, to the charset currently set
 * in the modem. Given in the API so that subclasses can also use it directly.
 */
gchar *mm_broadband_modem_take_and_convert_to_current_charset (MMBroadbandModem *self,
                                                               gchar *str);

/* Create a unique device identifier string using the ATI and ATI1 replies and some
 * additional internal info */
gchar *mm_broadband_modem_create_device_identifier (MMBroadbandModem *self,
                                                    const gchar *ati,
                                                    const gchar *ati1);

/* Locking/unlocking SMS storages */
void     mm_broadband_modem_lock_sms_storages        (MMBroadbandModem *self,
                                                      MMSmsStorage mem1, /* reading/listing/deleting */
                                                      MMSmsStorage mem2, /* storing/sending */
                                                      GAsyncReadyCallback callback,
                                                      gpointer user_data);
gboolean mm_broadband_modem_lock_sms_storages_finish (MMBroadbandModem *self,
                                                      GAsyncResult *res,
                                                      GError **error);
void     mm_broadband_modem_unlock_sms_storages      (MMBroadbandModem *self,
                                                      gboolean mem1,
                                                      gboolean mem2);

#endif /* MM_BROADBAND_MODEM_H */
