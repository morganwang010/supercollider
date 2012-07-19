/*
    SuperCollider Qt IDE
    Copyright (c) 2012 Jakob Leben & Tim Blechmann
    http://www.audiosynth.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef SCIDE_SESSION_MANAGER_HPP_INCLUDED
#define SCIDE_SESSION_MANAGER_HPP_INCLUDED

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QSettings>

namespace ScIDE {

class DocumentManager;

struct Session : public QSettings
{
    Session( const QString & file, Format format, QObject * parent = 0 ):
        QSettings(file, format, parent)
    {}
};

class SessionManager : public QObject
{
    Q_OBJECT

public:
    SessionManager( DocumentManager *, QObject * parent = 0 );

    QDir sessionsDir();
    QStringList availableSessions();
    QString lastSession();

    Session * openSession( const QString & name );
    void saveSession();
    Session * saveSessionAs( const QString & name );
    void closeSession();

    Session *currentSession() { return mSession; }
    const QString & currentSessionName() { return mSessionName; }

signals:
    void saveSessionRequest(Session * session);
    void loadSessionRequest(Session * session);

private:
    bool saveLastSession( const QDir & dir, const QString & file );
    DocumentManager *mDocMng;
    Session *mSession;
    QString mSessionName;
};

} // namespace ScIDE

#endif // SCIDE_SESSION_MANAGER_HPP_INCLUDED