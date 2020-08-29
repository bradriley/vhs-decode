/************************************************************************

    stacker.h

    ld-disc-stacker - Disc stacking for ld-decode
    Copyright (C) 2020 Simon Inns

    This file is part of ld-decode-tools.

    ld-disc-stacker is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

************************************************************************/

#ifndef STACKER_H
#define STACKER_H

#include <QObject>
#include <QElapsedTimer>
#include <QAtomicInt>
#include <QThread>
#include <QDebug>

#include "sourcevideo.h"
#include "lddecodemetadata.h"

class StackingPool;

class Stacker : public QThread
{
    Q_OBJECT
public:
    explicit Stacker(QAtomicInt& _abort, StackingPool& _stackingPool, QObject *parent = nullptr);

protected:
    void run() override;

private:
    // Stacking pool
    QAtomicInt& abort;
    StackingPool& stackingPool;

    QVector<LdDecodeMetaData::VideoParameters> videoParameters;

    SourceVideo::Data stackField(QVector<SourceVideo::Data> inputFields, LdDecodeMetaData::VideoParameters videoParameters, QVector<qint32> availableSourcesForFrame);
    quint16 median(QVector<quint16> v);
};

#endif // STACKER_H
