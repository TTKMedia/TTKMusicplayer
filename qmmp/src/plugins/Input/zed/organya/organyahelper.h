/***************************************************************************
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef ORGANYAHELPER_H
#define ORGANYAHELPER_H

#include <QMap>
#include <QFile>
#include <qmmp/qmmp.h>
#include <liborganya/organya/organya.h>
#include <liborganya/pxtone/pxtnService.h>

/*!
 * @author Greedysky <greedysky@163.com>
 */
class OrganyaHelper
{
public:
    explicit OrganyaHelper(const QString &path);
    ~OrganyaHelper();

    void deinit();
    bool initialize();

    void seek(qint64 time);
    qint64 totalTime() const;

    inline int bitrate() const { return m_bitrate; }
    inline int sampleRate() const { return 44100; }
    inline int channels() const { return 2; }
    inline int depth() const { return 16; }

    qint64 read(unsigned char *data, qint64 maxSize);

private:
    QString m_path;
    org_decoder_t *m_org = nullptr;
    pxtnService *m_pxs = nullptr;
    pxtnDescriptor *m_pxd = nullptr;

    enum Type
    {
        Organya,
        PxTone
    } m_type = Organya;

    int m_bitrate = 0;

};

#endif
