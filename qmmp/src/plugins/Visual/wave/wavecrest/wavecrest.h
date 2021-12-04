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

#ifndef WAVECREST_H
#define WAVECREST_H

#include <qmmp/visual.h>

/*!
 * @author Greedysky <greedysky@163.com>
 */
class WaveCrest : public Visual
{
    Q_OBJECT
public:
    explicit WaveCrest(QWidget *parent = nullptr);
    virtual ~WaveCrest();

private:
    virtual void paintEvent(QPaintEvent *e) override;

    virtual void process(float *left, float *right) override;
    void draw(QPainter *p);

    QImage m_backgroundImage;
    int m_pixPos = 0;
    int m_vis_data = 0;
    int *m_x_scale = nullptr;
    double m_analyzer_falloff = 2.2;

};

#endif
