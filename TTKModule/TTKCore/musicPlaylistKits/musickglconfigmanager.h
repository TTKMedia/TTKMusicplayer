#ifndef MUSICKGLCONFIGMANAGER_H
#define MUSICKGLCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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
 ================================================= */

#include "musicabstractxml.h"
#include "musicplaylistinterface.h"

/*! @brief The class of the kugou playlist Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_CORE_EXPORT MusicKGLConfigManager : public MusicAbstractXml, public MusicPlaylistInterface
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicKGLConfigManager)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicKGLConfigManager(QObject *parent = nullptr);

    /*!
     * Read datas from config file.
     */
    virtual bool readPlaylistData(MusicSongItems &items) override;
    /*!
     * Write datas into config file.
     */
    virtual bool writePlaylistData(const MusicSongItems &items, const QString &path) override;

};

#endif // MUSICKGLCONFIGMANAGER_H