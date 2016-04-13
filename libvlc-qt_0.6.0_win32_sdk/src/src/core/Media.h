/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_MEDIA_H_
#define VLCQT_MEDIA_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include "Enums.h"

class VlcInstance;

struct libvlc_media_t;

/*!
    \class VlcMedia Media.h vlc-qt/Media.h
    \brief Media item

    An abstract representation of a playable media.
    It consists of a media location and various optional meta data.
*/
class VlcMedia : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from a media location.

        \param location location of the media (QString)
        \param localFile true, if media is local file (bool)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const QString &location,
                      const bool &localFile,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from a remote media location.
        Provided for convenience.

        \param location remote location of the media (QString)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const QString &location,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from an existing one.

        \param media libvlc media item (libvlc_media_t *)
    */
    VlcMedia(libvlc_media_t *media);

    /*!
        \brief VlcMedia destructor
    */
    ~VlcMedia();

    /*!
        \brief libvlc media item
        \return libvlc media item (libvlc_media_t *)
    */
    libvlc_media_t *core();

    /*!
        \brief Current media location

        \return QString media location
    */
    QString currentLocation() const;

    /*!
        \brief Duplicate to file

        Duplicate video stream with desired mux.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
    */
    QString duplicate(const QString &name,
                      const QString &path,
                      const Vlc::Mux &mux) const;

    /*!
        \brief Record

        Apply recording options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const Vlc::Mux &mux) const;

    /*!
        \brief Record

        Apply recording options with desired mux and transcoding (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codex (Vlc::AudioCodec)
        \param videoCodec video codex (Vlc::VideoCodec)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const Vlc::Mux &mux,
                   const Vlc::AudioCodec &audioCodec,
                   const Vlc::VideoCodec &videoCodec) const;

    /*!
        \brief Set media option
        \param option media option (QString)
    */
    void setOption(const QString &option);

private:
    void initMedia(const QString &location,
                   const bool &localFile,
                   VlcInstance *instance);

    libvlc_media_t * _vlcMedia;
    QString _currentLocation;
};

#endif // VLCQT_MEDIA_H_
