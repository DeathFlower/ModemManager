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
 * Copyright (C) 2012 Google Inc.
 */

#ifndef MM_FIRMWARE_PROPERTIES_H
#define MM_FIRMWARE_PROPERTIES_H

#include <ModemManager.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define MM_TYPE_FIRMWARE_PROPERTIES            (mm_firmware_properties_get_type ())
#define MM_FIRMWARE_PROPERTIES(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_FIRMWARE_PROPERTIES, MMFirmwareProperties))
#define MM_FIRMWARE_PROPERTIES_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  MM_TYPE_FIRMWARE_PROPERTIES, MMFirmwarePropertiesClass))
#define MM_IS_FIRMWARE_PROPERTIES(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_FIRMWARE_PROPERTIES))
#define MM_IS_FIRMWARE_PROPERTIES_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  MM_TYPE_FIRMWARE_PROPERTIES))
#define MM_FIRMWARE_PROPERTIES_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MM_TYPE_FIRMWARE_PROPERTIES, MMFirmwarePropertiesClass))

typedef struct _MMFirmwareProperties MMFirmwareProperties;
typedef struct _MMFirmwarePropertiesClass MMFirmwarePropertiesClass;
typedef struct _MMFirmwarePropertiesPrivate MMFirmwarePropertiesPrivate;

/**
 * MMFirmwareProperties:
 *
 * The #MMFirmwareProperties structure contains private data and should only be accessed
 * using the provided API.
 */
struct _MMFirmwareProperties {
    /*< private >*/
    GObject parent;
    MMFirmwarePropertiesPrivate *priv;
};

struct _MMFirmwarePropertiesClass {
    /*< private >*/
    GObjectClass parent;
};

GType mm_firmware_properties_get_type (void);

MMFirmwareProperties *mm_firmware_properties_new (MMFirmwareImageType image_type,
                                                  const gchar *name,
                                                  const gchar *version);
MMFirmwareProperties *mm_firmware_properties_new_from_dictionary (GVariant *dictionary,
                                                                  GError **error);

const gchar         *mm_firmware_properties_get_name       (MMFirmwareProperties *properties);
const gchar         *mm_firmware_properties_get_version    (MMFirmwareProperties *properties);
MMFirmwareImageType  mm_firmware_properties_get_image_type (MMFirmwareProperties *properties);

GVariant *mm_firmware_properties_get_dictionary (MMFirmwareProperties *self);

G_END_DECLS

#endif /* MM_FIRMWARE_PROPERTIES_H */