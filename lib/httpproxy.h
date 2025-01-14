/*
 * httpproxy.h - the header file of HttpProxy class
 *
 * This class enables transparent HTTP proxy that handles data transfer
 * and send/recv them via upper-level SOCKS5 proxy
 *
 * Copyright (C) 2015 Symeon Huang <hzwhuang@gmail.com>
 *
 * This file is part of the libQtShadowsocks.
 *
 * libQtShadowsocks is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libQtShadowsocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libQtShadowsocks; see the file LICENSE. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef HTTPPROXY_H
#define HTTPPROXY_H

#include <QTcpServer>
#include <QNetworkProxy>
#include "export.h"

namespace QSS {

class QSS_EXPORT HttpProxy : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpProxy(QObject *parent = 0);

    /*
     * DO NOT use listen() function, use httpListen instead
     * The socks_port is local socks proxy server port
     */
    bool httpListen(const QHostAddress &http_addr, quint16 http_port, quint16 socks_port);

signals:
    void info(const QString &);

protected:
    void incomingConnection(qintptr handle);

private:
    QNetworkProxy upstreamProxy;

private slots:
    void onSocketError(QAbstractSocket::SocketError);
    void onSocketReadyRead();
    void onProxySocketConnected();
    void onProxySocketConnectedHttps();//this function is used for HTTPS transparent proxy
    void onProxySocketReadyRead();
};

}

#endif // HTTPPROXY_H
