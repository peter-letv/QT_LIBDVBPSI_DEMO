/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"

VlcVideo::VlcVideo(VlcMediaPlayer *player)
    : QObject(player),
      _vlcMediaPlayer(player->core()) { }

VlcVideo::~VlcVideo() { }

Vlc::Ratio VlcVideo::aspectRatio() const
{
    QString ratio = "";
    if (_vlcMediaPlayer) {
        ratio = libvlc_video_get_aspect_ratio(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return Vlc::Ratio(Vlc::ratio().indexOf(ratio));
}

Vlc::Ratio VlcVideo::cropGeometry() const
{
    QString crop = "";
    if (_vlcMediaPlayer) {
        crop = libvlc_video_get_crop_geometry(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return Vlc::Ratio(Vlc::ratio().indexOf(crop));
}

void VlcVideo::setAspectRatio(const Vlc::Ratio &ratio)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_aspect_ratio(_vlcMediaPlayer, Vlc::ratio()[ratio].toAscii().data());
        VlcError::errmsg();
    }
}

void VlcVideo::setCropGeometry(const Vlc::Ratio &ratio)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_crop_geometry(_vlcMediaPlayer, Vlc::ratio()[ratio].toAscii().data());
        VlcError::errmsg();
    }
}

void VlcVideo::setDeinterlace(const Vlc::Deinterlacing &filter)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_deinterlace(_vlcMediaPlayer, Vlc::deinterlacing()[filter].toAscii().data());
        VlcError::errmsg();
    }
}

void VlcVideo::setSubtitle(const int &subtitle)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_spu(_vlcMediaPlayer, subtitle);
        VlcError::errmsg();
    }
}

void VlcVideo::setSubtitleFile(const QString &subtitle)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_subtitle_file(_vlcMediaPlayer, subtitle.toAscii().data());
        VlcError::errmsg();
    }
}

void VlcVideo::setTeletextPage(const int &page)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_teletext(_vlcMediaPlayer, page);
        VlcError::errmsg();
    }
}

void VlcVideo::setTrack(const int &track)
{
    if (_vlcMediaPlayer) {
        libvlc_video_set_track(_vlcMediaPlayer, track);
        VlcError::errmsg();
    }
}

int VlcVideo::subtitle() const
{
    int subtitle = -1;
    if (_vlcMediaPlayer) {
        subtitle = libvlc_video_get_spu(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return subtitle;
}

int VlcVideo::subtitleCount() const
{
    int count = -1;
    if (_vlcMediaPlayer) {
        count = libvlc_video_get_spu_count(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return count;
}

QStringList VlcVideo::subtitleDescription() const
{
    QStringList descriptions;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_spu_description(_vlcMediaPlayer);
        VlcError::errmsg();

        descriptions << QString().fromUtf8(desc->psz_name);
        if (subtitleCount() > 1) {
            for(int i = 1; i < subtitleCount(); i++) {
                desc = desc->p_next;
                descriptions << QString().fromUtf8(desc->psz_name);
            }
        }
    }

    return descriptions;
}

int VlcVideo::teletextPage() const
{
    int page = -1;
    if (_vlcMediaPlayer) {
        page = libvlc_video_get_teletext(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return page;
}

void VlcVideo::toggleTeletextTransparency()
{
    if (_vlcMediaPlayer) {
        libvlc_toggle_teletext(_vlcMediaPlayer);
        VlcError::errmsg();
    }
}

int VlcVideo::track() const
{
    int track = -1;
    if (_vlcMediaPlayer) {
        track = libvlc_video_get_track(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return track;
}

int VlcVideo::trackCount() const
{
    int count = -1;
    if (_vlcMediaPlayer) {
        count = libvlc_video_get_track_count(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return count;
}

QStringList VlcVideo::trackDescription() const
{
    QStringList descriptions;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_track_description(_vlcMediaPlayer);
        VlcError::errmsg();

        descriptions << QString().fromUtf8(desc->psz_name);
        if (trackCount() > 1) {
            for(int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                descriptions << QString().fromUtf8(desc->psz_name);
            }
        }
    }

    return descriptions;
}

QList<int> VlcVideo::trackIds() const
{
    QList<int> ids;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_track_description(_vlcMediaPlayer);
        VlcError::errmsg();

        ids << desc->i_id;
        if (trackCount() > 1) {
            for(int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                ids << desc->i_id;
            }
        }
    }

    return ids;
}
