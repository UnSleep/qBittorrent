/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef PEERLISTWIDGET_H
#define PEERLISTWIDGET_H

#include <QTreeView>
#include <QHash>
#include <QPointer>
#include <QSet>
#include <libtorrent/peer_info.hpp>
#include "qtorrenthandle.h"
#include "misc.h"

class PeerListDelegate;
class ReverseResolution;
class PropertiesWidget;

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QStandardItem;
class QStandardItemModel;
QT_END_NAMESPACE

#include <boost/version.hpp>
#if BOOST_VERSION < 103500
#include <libtorrent/asio/ip/tcp.hpp>
#else
#include <boost/asio/ip/tcp.hpp>
#endif

class PeerListWidget : public QTreeView {
  Q_OBJECT
  Q_DISABLE_COPY(PeerListWidget)

public:
  PeerListWidget(PropertiesWidget *parent);
  ~PeerListWidget();

public slots:
  void loadPeers(const QTorrentHandle &h, bool force_hostname_resolution=false);
  QStandardItem*  addPeer(QString ip, libtorrent::peer_info peer);
  void updatePeer(QString ip, libtorrent::peer_info peer);
  void handleResolved(const QString &ip, const QString &hostname);
  void updatePeerHostNameResolutionState();
  void updatePeerCountryResolutionState();
  void clear();

protected slots:
  void loadSettings();
  void saveSettings() const;
  void showPeerListMenu(QPoint);
  void limitUpRateSelectedPeers(QStringList peer_ips);
  void limitDlRateSelectedPeers(QStringList peer_ips);
  void banSelectedPeers(QStringList peer_ips);
  void handleSortColumnChanged(int col);

private:
  static QString getConnectionString(int connection_type);

private:
  QStandardItemModel *listModel;
  PeerListDelegate *listDelegate;
  QSortFilterProxyModel * proxyModel;
  QHash<QString, QStandardItem*> peerItems;
  QHash<QString, libtorrent::asio::ip::tcp::endpoint> peerEndpoints;
  QSet<QString> missingFlags;
  QPointer<ReverseResolution> resolver;
  PropertiesWidget* properties;
  bool display_flags;
};

#endif // PEERLISTWIDGET_H
